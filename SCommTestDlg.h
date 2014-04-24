// SCommTestDlg.h : header file
//
//{{AFX_INCLUDES()
#include "mscomm.h"
//}}AFX_INCLUDES

#if !defined(AFX_SCOMMTESTDLG_H__4D383AD9_F1DB_4971_ACEC_3A544A9C7691__INCLUDED_)
#define AFX_SCOMMTESTDLG_H__4D383AD9_F1DB_4971_ACEC_3A544A9C7691__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSCommTestDlg dialog

class CSCommTestDlg : public CDialog
{
// Construction
public:
	BOOL m_bAutoSend;
	char ConvertHexChar(char ch);
	int String2Hex(CString str, CByteArray &senddata);
	CSCommTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSCommTestDlg)
	enum { IDD = IDD_SCOMMTEST_DIALOG };
	CButton	m_ctrlHexDisplay;
	CButton	m_ctrlHexSend;
	CMSComm	m_ctrlComm;
	CString	m_strRXData;
	CString	m_strTXData;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCommTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSCommTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnComm();
	afx_msg void OnButtonManualsend();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCheckAutosend();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCOMMTESTDLG_H__4D383AD9_F1DB_4971_ACEC_3A544A9C7691__INCLUDED_)
