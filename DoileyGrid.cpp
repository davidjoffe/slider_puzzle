// DoileyGrid.cpp
// Copyright (C) 1997-2001 David Joffe

#include "StdAfx.h"
#include "Doiley.h"
#include "DoileyGrid.h"
#include "LEDDisplay.h"

#include <winbase.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define SPACECHAR (15)

/////////////////////////////////////////////////////////////////////////////
// CDoileyGrid

CDoileyGrid::CDoileyGrid()
{
	m_pLEDDisplay = NULL;
	int c = 0;
	int i,j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			m_Grid[j][i] = c;
			c++;
		}
	}
	((CDoileyApp*)(AfxGetApp()))->m_pdTime = &m_dTime;
	((CDoileyApp*)(AfxGetApp()))->m_pbTiming = &m_bTiming;
	((CDoileyApp*)(AfxGetApp()))->m_pdTimeStart = &m_dTimeStart;
	m_bitmapSize.cx = 0;
	m_bitmapSize.cy = 0;
	m_bStarted = FALSE;
	m_bTiming = FALSE;
	m_dTime = 0;
	m_dTimeStart = 0;
}

CDoileyGrid::~CDoileyGrid()
{
}


BEGIN_MESSAGE_MAP(CDoileyGrid, CWnd)
	//{{AFX_MSG_MAP(CDoileyGrid)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDoileyGrid message handlers

void CDoileyGrid::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CRect rc;
	GetClientRect(&rc);

	int i,j;
	int uGridWidth = int(float(rc.right - rc.left) / 4.0f);
	int uGridHeight = int(float(rc.bottom - rc.top) / 4.0f);
	CDC bitmapDC;
	// Create memory DC:
	bitmapDC.CreateCompatibleDC(NULL);
	// Select bitmap into it
	bitmapDC.SelectObject(&m_bitmap);

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (m_bitmapSize.cx) {
				if (!bitmapDC.GetCurrentBitmap()) {
					AfxMessageBox("No bmp");
				} else {
					dc.StretchBlt(
						rc.left + j * uGridWidth, rc.top + i * uGridHeight,
						uGridWidth, uGridHeight,
						&bitmapDC,
						m_Grid[j][i] * (m_bitmapSize.cx / 16), 0,
						(m_bitmapSize.cx / 16), (m_bitmapSize.cy),
						SRCCOPY);
				}
			}
		}
	}
	bitmapDC.DeleteDC();

	// Do not call CWnd::OnPaint() for painting messages
}

BOOL CDoileyGrid::Create(const RECT& rect, CWnd* pParentWnd, UINT nID, char* pszBitmapFile)
{
	m_bitmapSize.cx = 0;
	m_bitmapSize.cy = 0;
	if (m_bitmap.LoadBitmap(pszBitmapFile) == 0) {
		AfxMessageBox("Error loading bitmap");
	} else {
		BITMAP bmp;
		m_bitmap.GetBitmap(&bmp);
		m_bitmapSize.cx = bmp.bmWidth;
		m_bitmapSize.cy = bmp.bmHeight;
	}
	return CWnd::Create(NULL, "Doiley", WS_VISIBLE | WS_CHILD, rect, pParentWnd, nID);
}

BOOL CDoileyGrid::Create(const RECT& rect, CWnd* pParentWnd, UINT nID, UINT nIDBitmapResource)
{
	m_bitmapSize.cx = 0;
	m_bitmapSize.cy = 0;
	if (m_bitmap.LoadBitmap(nIDBitmapResource) == 0) {
		AfxMessageBox("Error loading bitmap");
	} else {
		BITMAP bmp;
		m_bitmap.GetBitmap(&bmp);
		m_bitmapSize.cx = bmp.bmWidth;
		m_bitmapSize.cy = bmp.bmHeight;
	}
	return CWnd::Create(NULL, "Doiley", WS_VISIBLE | WS_CHILD, rect, pParentWnd, nID);
}

void CDoileyGrid::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if (!m_bStarted) {
		Shuffle();
		RedrawWindow();
		return;
	}

	CRect rc;
	GetClientRect(&rc);
	
	int iPressedX = int((float(point.x) / float(rc.right - rc.left)) * 4);
	int iPressedY = int((float(point.y) / float(rc.bottom - rc.top)) * 4);
	TRACE("[%d, %d] Clicked: [%d, %d]\n", int(point.x), int(point.y), iPressedX, iPressedY);

	TRACE("Is next to space? [%d]\n", int(IsNextToSpace(iPressedX, iPressedY)));
	if (IsNextToSpace(iPressedX, iPressedY)) {
		SwapWithSpace(iPressedX, iPressedY);
		RedrawWindow();
		if (IsSolved()) {
			char buffer[256];
			StopTimer();
			sprintf(buffer, "Well done! Your time was %3.1f seconds", float(m_dTime) / 1000.0f);
			AfxMessageBox(buffer);
			m_bStarted = FALSE;
		}
		return;
	}

	CWnd::OnLButtonDown(nFlags, point);
}

BOOL CDoileyGrid::IsNextToSpace(int x, int y)
{
	if (x != 0) {
		if (m_Grid[x - 1][y] == SPACECHAR) return TRUE;
	}
	if (x != 3) {
		if (m_Grid[x + 1][y] == SPACECHAR) return TRUE;
	}
	if (y != 0) {
		if (m_Grid[x][y - 1] == SPACECHAR) return TRUE;
	}
	if (y != 3) {
		if (m_Grid[x][y + 1] == SPACECHAR) return TRUE;
	}
	return FALSE;
}

void CDoileyGrid::SwapWithSpace(int x, int y)
{
	m_Grid[GetSpaceX()][GetSpaceY()] = m_Grid[x][y];
	m_Grid[x][y] = SPACECHAR;
}

int CDoileyGrid::GetSpaceX()
{
	int i,j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (m_Grid[j][i] == SPACECHAR) return j;
		}
	}
	return -1;
}

int CDoileyGrid::GetSpaceY()
{
	int i,j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (m_Grid[j][i] == SPACECHAR) return i;
		}
	}
	return -1;
}

void CDoileyGrid::Shuffle()
{
	// Seed the random number generator
	srand((unsigned)timeGetTime());
	int i,n,xd,yd;
	
	// Place the pieces where they should be
	for (i = 0; i < 16; i++) {
		m_Grid[i % 4][i >> 2] = i;
	}

	// Move the space (empty piece) randomly 10000 times
	for (i = 0; i < 10000; i++) {
		n = (rand() % 4);
		switch (n) {
		case 0:
			xd = -1;
			yd = 0;
			break;
		case 1:
			xd = 1;
			yd = 0;
			break;
		case 2:
			xd = 0;
			yd = -1;
			break;
		case 3:
			xd = 0;
			yd = 1;
			break;
		}
		if (GetSpaceX() + xd < 0) continue;
		if (GetSpaceX() + xd > 3) continue;
		if (GetSpaceY() + yd < 0) continue;
		if (GetSpaceY() + yd > 3) continue;
		SwapWithSpace(GetSpaceX() + xd, GetSpaceY() + yd);

		// Redraw every so often to give visual shuffling effect
		if ((i%100)==0)
		{
			RedrawWindow();
			Sleep(1);
		}
	}
	// Initialize timer
	m_bStarted = TRUE;
	m_dTime = 0;
	StartTimer();
}

BOOL CDoileyGrid::IsSolved()
{
	int i;
	BOOL bSolved = TRUE;
	for (i = 0; ((i < 16) && (bSolved == TRUE)); i++) {
		if (m_Grid[i % 4][i >> 2] != i) bSolved = FALSE;
	}
	return bSolved;
}

UINT CDoileyGrid::StartTimer()
{
	m_bTiming = TRUE;
	m_dTimeStart = timeGetTime();
	  
	SetTimer(12345, 100, NULL);

	return 0;
}

void CDoileyGrid::StopTimer()
{
	if (m_bTiming) {
		KillTimer(12345);
		m_bTiming = FALSE;
	}
}

void CDoileyGrid::OnTimer(UINT nIDEvent) 
{
	if (!m_bTiming) {
		AfxMessageBox("Error: timer handler should not be installed");
		return;
	}
	if (nIDEvent == 12345) {
		m_dTime = timeGetTime() - m_dTimeStart;
		char buffer[100];
		sprintf(buffer, "%3.1f", float(m_dTime) / 1000.0f);
		UINT i;
		for (i = 0; i < strlen(buffer); i++) {
			if (buffer[i] == '.') {
				buffer[i] = '\x00B';
			} else {
				buffer[i] = buffer[i] - 47;
			}
		}
		if (m_pLEDDisplay) {
			m_pLEDDisplay->SetDisplay(buffer);
			m_pLEDDisplay->RedrawWindow();
		}
		if (m_dTime > 999000) StopTimer();
	}

	CWnd::OnTimer(nIDEvent);
}

void CDoileyGrid::Solve()
{
	StopTimer();

	m_bStarted = FALSE;

	int i;

	// Place the pieces where they should be
	for (i = 0; i < 16; i++) {
		m_Grid[i % 4][i >> 2] = i;
	}

	RedrawWindow();

	if (m_pLEDDisplay) {
		m_pLEDDisplay->SetDisplay("");
		m_pLEDDisplay->RedrawWindow();
	}

}
