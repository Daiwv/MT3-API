#if !defined(AFX_OPENACCOUNTDLG_H__89B4FB17_7C58_482C_ACE1_5A7A3A48B65B__INCLUDED_)
#define AFX_OPENACCOUNTDLG_H__89B4FB17_7C58_482C_ACE1_5A7A3A48B65B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OpenAccountDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COpenAccountDlg dialog

class COpenAccountDlg : public CDialog
{
// Construction
public:
	COpenAccountDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COpenAccountDlg)
	enum { IDD = IDD_OPENACCOUNT };
	CComboBox	m_cmbLeverage;
	CComboBox	m_cmbDeposit;
	CString	m_sAddress;
	CString	m_sCity;
	CString	m_sCountry;
	CString	m_sEmail;
	CString	m_sName;
	CString	m_sPhone;
	CString	m_sState;
	CString	m_sZip;
	//}}AFX_DATA
	int		m_nLeverage;
	int		m_nDeposit;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COpenAccountDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COpenAccountDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPENACCOUNTDLG_H__89B4FB17_7C58_482C_ACE1_5A7A3A48B65B__INCLUDED_)
