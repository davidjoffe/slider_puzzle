// LEDDisplay.cpp
// Copyright (C) 1997-2001 David Joffe

#include "StdAfx.h"
#include "Doiley.h"
#include "LEDDisplay.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CLEDDisplay, CWnd)
	//{{AFX_MSG_MAP(CLEDDisplay)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLEDDisplay

CLEDDisplay::CLEDDisplay()
{
	m_cPadChar = 0;
	m_bRightJustify = TRUE;
	m_bitmapSize.cx = 0;
	m_bitmapSize.cy = 0;
	m_uDisplayWidth = 0;
	m_uBitmapWidth = 0;
	memset(m_displayBuffer, 0, sizeof(m_displayBuffer));
}

CLEDDisplay::~CLEDDisplay()
{
}

/////////////////////////////////////////////////////////////////////////////
// CLEDDisplay message handlers

BOOL CLEDDisplay::Create(const RECT& rect, CWnd * pParentWnd, UINT uIDBitmapResource, UINT uBitmapWidth, UINT uDisplayWidth, UINT uID)
{
	m_bitmapSize.cx = 0;
	m_bitmapSize.cy = 0;
	m_uBitmapWidth = uBitmapWidth;
	m_uDisplayWidth = uDisplayWidth;
	if (m_bitmap.LoadBitmap(uIDBitmapResource) == 0) {
		AfxMessageBox("Error loading LED display bitmap");
	} else {
		BITMAP bmp;
		m_bitmap.GetBitmap(&bmp);
		m_bitmapSize.cx = bmp.bmWidth;
		m_bitmapSize.cy = bmp.bmHeight;
	}
	return CWnd::Create(NULL, "LEDDisplay", WS_VISIBLE | WS_CHILD, rect, pParentWnd, uID);
}

void CLEDDisplay::SetDisplay(char* pszText)
{
	sprintf(m_displayBuffer, "%s", pszText);
}

void CLEDDisplay::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CRect rc;
	GetClientRect(&rc);

	CDC bitmapDC;
	// Create memory DC:
	bitmapDC.CreateCompatibleDC(NULL);
	// Select bitmap into it
	bitmapDC.SelectObject(&m_bitmap);

	int uGridWidth = int(float(rc.right - rc.left) / float(m_uDisplayWidth));
	int uCharWidth = (m_bitmapSize.cx / m_uBitmapWidth);
	int uGridHeight = int(float(rc.bottom - rc.top));

	UINT uOffset = 0;
	if (m_bRightJustify) uOffset = m_uDisplayWidth - strlen(m_displayBuffer);

	UINT i;

	// Draw blanks in the appropriate spots
	if (m_bRightJustify) {
		for (i = 0; i < (m_uDisplayWidth - strlen(m_displayBuffer)); i++) {
			if (m_cPadChar) {
				dc.StretchBlt(
					rc.left + i * uGridWidth, rc.top,
					uGridWidth, uGridHeight,
					&bitmapDC,
					(m_cPadChar - 1) * uCharWidth, 0,
					uCharWidth, m_bitmapSize.cy,
					SRCCOPY);
			} else {
				dc.StretchBlt(
					rc.left + i * uGridWidth, rc.top,
					uGridWidth, uGridHeight,
					&bitmapDC, 1, 1, 1, 1,
					BLACKNESS);
			}
		}
	}
	
	if (m_bitmapSize.cx) {
		for (i = 0; i < strlen(m_displayBuffer); i++) {
			if (!bitmapDC.GetCurrentBitmap()) {
				AfxMessageBox("No bmp");
			} else {  
				dc.StretchBlt(
					rc.left + (i + uOffset) * uGridWidth, rc.top,
					uGridWidth, uGridHeight,
					&bitmapDC,
					(m_displayBuffer[i] - 1) * uCharWidth, 0,
					uCharWidth, m_bitmapSize.cy,
					SRCCOPY);
			}
		}
	}
	bitmapDC.DeleteDC();
}
