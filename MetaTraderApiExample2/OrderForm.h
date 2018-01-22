#if !defined(AFX_ORDERFORM_H__92EDAB7B_EE97_4B17_AE5A_6FB4C7D08DD6__INCLUDED_)
#define AFX_ORDERFORM_H__92EDAB7B_EE97_4B17_AE5A_6FB4C7D08DD6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OrderForm.h : header file
//

#include "../MetaTraderAPI.h"

/////////////////////////////////////////////////////////////////////////////
// COrderForm dialog

class COrderForm : public CDialog
{
// Construction
public:
	COrderForm(CString& server, UINT port, UINT login, CString& passwd, int isec, int itrade, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COrderForm)
	enum { IDD = IDD_ORDER_FORM };
	CButton	m_Modify;
	CButton	m_Delete;
	CComboBox	m_Command;
	CComboBox	m_CloseDeals;
	CButton	m_CloseBy;
	CButton	m_CloseDeal;
	CButton	m_Sell;
	CButton	m_Buy;
	CStatic	m_Prices;
	CComboBox	m_Lots;
	CComboBox	m_Symbols;
	double	m_fSL;
	double	m_fTP;
	double	m_fPendingPrice;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COrderForm)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COrderForm)
	virtual BOOL OnInitDialog();
	afx_msg void OnGetPrices();
	afx_msg void OnBuy();
	afx_msg void OnSell();
	afx_msg void OnCloseBy();
	afx_msg void OnCloseDeal();
	afx_msg void OnSend();
	afx_msg void OnDelete();
	afx_msg void OnModify();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void SendOrder(int cmd);
	CString			m_sServer;
	UINT			m_nPort;
	UINT			m_nLogin;
	CString			m_sPasswd;
	int				m_iSec;		// индекс в массиве g_pSecs
	int				m_iTrade;	// индекс в массиве g_pTrades
	CMetaTraderAPI	m_api;
	int				m_nLots;
	double			m_fBid;
	double			m_fAsk;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ORDERFORM_H__92EDAB7B_EE97_4B17_AE5A_6FB4C7D08DD6__INCLUDED_)
