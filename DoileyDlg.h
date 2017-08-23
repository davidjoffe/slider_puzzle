// DoileyDlg.h
// Copyright (C) 1997-2001 David Joffe

#include "DoileyGrid.h"
#include "LEDDisplay.h"

/////////////////////////////////////////////////////////////////////////////
// CDoileyDlg dialog

class CDoileyDlg : public CDialog
{
// Construction
public:
	CDoileyGrid m_doileyGrid;
	CLEDDisplay m_LEDDisplay;
	CDoileyDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDoileyDlg)
	enum { IDD = IDD_DOILEY_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDoileyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDoileyDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnAbout();
	afx_msg void OnShuffle();
	virtual void OnCancel();
	afx_msg void OnSolve();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
