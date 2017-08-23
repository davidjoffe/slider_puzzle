// Doiley.h
// Copyright (C) 1997-2001 David Joffe

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"
#include "LEDDisplay.h"

/////////////////////////////////////////////////////////////////////////////
// CDoileyApp:
// See Doiley.cpp for the implementation of this class
//

class CDoileyApp : public CWinApp
{
public:
	CDoileyApp();

	CLEDDisplay* m_pLEDDisplay;
	DWORD* m_pdTimeStart;
	BOOL* m_pbTiming;
	DWORD* m_pdTime;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDoileyApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL OnIdle(LONG lCount);
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDoileyApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
