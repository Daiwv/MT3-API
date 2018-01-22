// OpenAccountDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MetaTraderAPIExample2.h"
#include "OpenAccountDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COpenAccountDlg dialog


COpenAccountDlg::COpenAccountDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COpenAccountDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COpenAccountDlg)
	m_sAddress = _T("some address");
	m_sCity = _T("Moscow");
	m_sCountry = _T("Russia");
	m_sEmail = _T("john@smith.com");
	m_sName = _T("John Smith");
	m_sPhone = _T("777777777");
	m_sState = _T("none");
	m_sZip = _T("123456");
	//}}AFX_DATA_INIT
	m_nLeverage = 100;
	m_nDeposit = 5000;
}


void COpenAccountDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COpenAccountDlg)
	DDX_Control(pDX, IDC_COMBOLEVERAGE, m_cmbLeverage);
	DDX_Control(pDX, IDC_COMBODEPOSIT, m_cmbDeposit);
	DDX_Text(pDX, IDC_EDITADDRESS, m_sAddress);
	DDX_Text(pDX, IDC_EDITCITY, m_sCity);
	DDX_Text(pDX, IDC_EDITCOUNTRY, m_sCountry);
	DDX_Text(pDX, IDC_EDITEMAIL, m_sEmail);
	DDX_Text(pDX, IDC_EDITNAME, m_sName);
	DDX_Text(pDX, IDC_EDITPHONE, m_sPhone);
	DDX_Text(pDX, IDC_EDITSTATE, m_sState);
	DDX_Text(pDX, IDC_EDITZIP, m_sZip);
	//}}AFX_DATA_MAP
	if (pDX->m_bSaveAndValidate)
	{
		m_nLeverage = m_cmbLeverage.GetItemData(m_cmbLeverage.GetCurSel());
		m_nDeposit = m_cmbDeposit.GetItemData(m_cmbDeposit.GetCurSel());
	}
}


BEGIN_MESSAGE_MAP(COpenAccountDlg, CDialog)
	//{{AFX_MSG_MAP(COpenAccountDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COpenAccountDlg message handlers

BOOL COpenAccountDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_cmbLeverage.SetCurSel(5);
	m_cmbDeposit.SetCurSel(1);

	int i;
	CString sItem;
	int data;
	for (i = 0; i < m_cmbLeverage.GetCount(); i++)
	{
		m_cmbLeverage.GetLBText(i, sItem);
		sItem = sItem.Right(sItem.GetLength()-2);
		sscanf(sItem, "%d", &data);
		m_cmbLeverage.SetItemData(i, data);
	}
	for (i = 0; i < m_cmbDeposit.GetCount(); i++)
	{
		m_cmbDeposit.GetLBText(i, sItem);
		sscanf(sItem, "%d", &data);
		m_cmbDeposit.SetItemData(i, data);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
