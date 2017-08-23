// DoileyGrid.h
// Copyright (C) 1997-2001 David Joffe

#ifndef _DOILEYGRID_H_
#define _DOILEYGRID_H_

/////////////////////////////////////////////////////////////////////////////
// CDoileyGrid window

class CDoileyGrid : public CWnd
{
public:
	CDoileyGrid();
	virtual ~CDoileyGrid();

	void Solve();
	void StopTimer();
	UINT StartTimer();
	BOOL IsSolved();
	void Shuffle();
	int GetSpaceY();
	int GetSpaceX();
	void SwapWithSpace(int x, int y);
	BOOL IsNextToSpace(int x, int y);

	CLEDDisplay	*m_pLEDDisplay;
	short		m_Grid[4][4];
	CSize		m_bitmapSize;
	CBitmap		m_bitmap;
	BOOL		m_bTiming;
	DWORD		m_dTime;
	BOOL		m_bStarted;
	DWORD		m_dTimeStart;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDoileyGrid)
	public:
	virtual BOOL Create(const RECT& rect, CWnd* pParentWnd, UINT nID, UINT nIDBitmapResource);
	virtual BOOL Create(const RECT& rect, CWnd* pParentWnd, UINT nID, char* pszBitmapFile);
	//}}AFX_VIRTUAL

	// Generated message map functions
protected:
	//{{AFX_MSG(CDoileyGrid)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif
