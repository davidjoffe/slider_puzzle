// Doiley.cpp
// Copyright (C) 1997-2001 David Joffe

#include "StdAfx.h"
#include "Doiley.h"
#include "DoileyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDoileyApp

BEGIN_MESSAGE_MAP(CDoileyApp, CWinApp)
	//{{AFX_MSG_MAP(CDoileyApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDoileyApp construction

CDoileyApp::CDoileyApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDoileyApp object

CDoileyApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDoileyApp initialization

BOOL CDoileyApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CDoileyDlg dlg;
	m_pMainWnd = &dlg;
	TRACE("before dlg.DoModal()\n");
	int nResponse = dlg.DoModal();
	TRACE("After! (response = %d)\n", nResponse);
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

BOOL CDoileyApp::OnIdle(LONG lCount) 
{
	return CWinApp::OnIdle(lCount);
}

