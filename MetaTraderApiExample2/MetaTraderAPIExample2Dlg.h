// MetaTraderAPIExample2Dlg.h : header file
//

#if !defined(AFX_METATRADERAPIEXAMPLE2DLG_H__FB5CBA2C_8056_459F_8807_07E3CE4364E0__INCLUDED_)
#define AFX_METATRADERAPIEXAMPLE2DLG_H__FB5CBA2C_8056_459F_8807_07E3CE4364E0__INCLUDED_

#include "../MetaTraderAPI.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../MetaTraderAPI.h"

// Pumping сообщение
extern UINT g_PumpingMsg;

/////////////////////////////////////////////////////////////////////////////
// CMetaTraderAPIExample2Dlg dialog

class CMetaTraderAPIExample2Dlg : public CDialog
{
// Construction
public:
	CMetaTraderAPIExample2Dlg(CWnd* pParent = NULL);	// standard constructor
	~CMetaTraderAPIExample2Dlg();						// desctuctor

// Dialog Data
	//{{AFX_DATA(CMetaTraderAPIExample2Dlg)
	enum { IDD = IDD_METATRADERAPIEXAMPLE2_DIALOG };
	CStatic	m_stSummary;
	CStatic	m_stQuotes;
	CButton	m_btnHideSec;
	CButton	m_btnAddSec;
	CListCtrl	m_lstTrade;
	CListCtrl	m_lstNews;
	CListCtrl	m_lstMail;
	CListCtrl	m_lstHist;
	CTabCtrl	m_tab;
	CListCtrl	m_lstMarket;
	CEdit	m_edtLogin;
	CEdit	m_edtPort;
	CEdit	m_edtServer;
	CButton	m_btnPasswd;
	CComboBox	m_cmbSecs;
	CButton	m_btnOpenAcc;
	CButton	m_btnDisconnect;
	CButton	m_btnConnect;
	CButton	m_btnLogin;
	CListBox	m_status;
	CString	m_sPasswd;
	UINT	m_nPort;
	CString	m_sServer;
	UINT	m_nLogin;
	//}}AFX_DATA
	BOOL			m_bConnected;
	int				m_nQuotes;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMetaTraderAPIExample2Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMetaTraderAPIExample2Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnConnect();
	afx_msg void OnDisconnect();
	afx_msg void OnOpenacc();
	afx_msg void OnBntlogin();
	afx_msg void OnBntpasswd();
	afx_msg void OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnaddsec();
	afx_msg void OnBtnhidesec();
	afx_msg void OnDblclkListmail(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListnews(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListmarket(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListtrade(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	afx_msg LRESULT OnPumpingMsg(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
private:
	CMetaTraderAPI	m_api;
	BOOL			m_bDoOrder;
	void UpdateTrades();
	void AddSecurity(int isec);
	void UpdateAccountHistory();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_METATRADERAPIEXAMPLE2DLG_H__FB5CBA2C_8056_459F_8807_07E3CE4364E0__INCLUDED_)
