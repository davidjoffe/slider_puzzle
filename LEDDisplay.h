// LEDDisplay.h
// Copyright (C) 1997-2001 David Joffe

#ifndef _LEDDISPLAY_H_
#define _LEDDISPLAY_H_

// LEDDisplay.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLEDDisplay window

class CLEDDisplay : public CWnd
{
public:
	CLEDDisplay();
	virtual ~CLEDDisplay();

	void SetPadChar(char cPadChar) { m_cPadChar = cPadChar; }
	void SetRightJustify(BOOL bRightJustify) { m_bRightJustify = bRightJustify; }
	void SetDisplay(char* pszText);

protected:
	char m_cPadChar;
	BOOL m_bRightJustify;
	UINT m_uDisplayWidth;
	CSize m_bitmapSize;
	UINT m_uBitmapWidth;
	char m_displayBuffer[256];
	CBitmap m_bitmap;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLEDDisplay)
	public:
	virtual BOOL Create(const RECT& rect, CWnd* pParentWnd, UINT uIDBitmapResource, UINT uBitmapWidth, UINT uDisplayWidth, UINT uID);
	//}}AFX_VIRTUAL

	// Generated message map functions
protected:
	//{{AFX_MSG(CLEDDisplay)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif
