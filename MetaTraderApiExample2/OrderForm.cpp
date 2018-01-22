// OrderForm.cpp : implementation file
//

#include "stdafx.h"
#include "MetaTraderAPIExample2.h"
#include "OrderForm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//---- �����������
extern ConSecurity*	g_pSecs;
extern int			g_nSecs;
//---- ������� �������
extern TradeRecord*	g_pTrades;
extern int			g_nTrades;

/////////////////////////////////////////////////////////////////////////////
// COrderForm dialog


COrderForm::COrderForm(CString& server, UINT port, UINT login, CString& passwd, int isec, int itrade, CWnd* pParent /*=NULL*/)
	: CDialog(COrderForm::IDD, pParent)
{
	m_sServer = server;
	m_nPort = port;
	m_nLogin = login;
	m_sPasswd = passwd;
	if (isec < 0)
		m_iSec = 0;
	else
		m_iSec = isec;
	m_iTrade = itrade;
	m_fBid = m_fAsk = 0.0;
	//{{AFX_DATA_INIT(COrderForm)
	m_fSL = 0.0;
	m_fTP = 0.0;
	m_fPendingPrice = 0.0;
	//}}AFX_DATA_INIT
}


void COrderForm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COrderForm)
	DDX_Control(pDX, IDC_MODIFY, m_Modify);
	DDX_Control(pDX, IDC_DELETE, m_Delete);
	DDX_Control(pDX, IDC_COMMAND, m_Command);
	DDX_Control(pDX, IDC_CLOSE_DEALS, m_CloseDeals);
	DDX_Control(pDX, IDC_CLOSE_BY, m_CloseBy);
	DDX_Control(pDX, IDC_CLOSE_DEAL, m_CloseDeal);
	DDX_Control(pDX, IDC_SELL, m_Sell);
	DDX_Control(pDX, IDC_BUY, m_Buy);
	DDX_Control(pDX, IDC_PRICES, m_Prices);
	DDX_Control(pDX, IDC_LOTS, m_Lots);
	DDX_Control(pDX, IDC_SYMBOLS, m_Symbols);
	DDX_Text(pDX, IDC_STOPLOSS, m_fSL);
	DDX_Text(pDX, IDC_TAKEPROFIT, m_fTP);
	DDX_Text(pDX, IDC_IDLE_PRICE, m_fPendingPrice);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COrderForm, CDialog)
	//{{AFX_MSG_MAP(COrderForm)
	ON_BN_CLICKED(IDC_GET_PRICES, OnGetPrices)
	ON_BN_CLICKED(IDC_BUY, OnBuy)
	ON_BN_CLICKED(IDC_SELL, OnSell)
	ON_BN_CLICKED(IDC_CLOSE_BY, OnCloseBy)
	ON_BN_CLICKED(IDC_CLOSE_DEAL, OnCloseDeal)
	ON_BN_CLICKED(IDC_SEND, OnSend)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_MODIFY, OnModify)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COrderForm message handlers

BOOL COrderForm::OnInitDialog() 
{
	static char *cmds[] = {
		"buy", "sell",
		"buy limit", "sell limit",
		"buy stop", "sell stop",
		"balance", "credit"
	};
	CDialog::OnInitDialog();
	//---- ���������� ����� ����������
	//---- �������� ���������� � pumping ������
	int err;
	if ((err = m_api.Connect(m_sServer, m_nPort)) > RET_OK_NONE)
	{
		MessageBox(m_api.GetErrorDescription(err), _T("Connect"), MB_OK | MB_ICONERROR);
		return FALSE;;
	}
	if ((err = m_api.Login(m_nLogin, m_sPasswd)) > RET_OK_NONE)
	{
		MessageBox(m_api.GetErrorDescription(err), _T("Login"), MB_OK | MB_ICONERROR);
		m_api.Disconnect();
		return FALSE;
	}
	//---- symbols
	for (int i = 0; i < g_nSecs; i++)
	{
		//---- unused[0] ������������� ������ �� symbol
		if (g_pSecs[i].unused[0] == 1)
		{
			int idx = m_Symbols.AddString(g_pSecs[i].name);
			m_Symbols.SetItemData(idx, i);
		}
	}
	int idx;
	if ((idx = m_Symbols.FindStringExact(-1, g_pSecs[m_iSec].name)) == LB_ERR) 
		idx = 0;
	m_Symbols.SetCurSel(idx);
	//---- ����
	m_Lots.SetCurSel(3);
	//---- ������ �� ����������� �������
	if (m_iTrade >= 0 && g_pTrades[m_iTrade].order > 0 && g_pTrades[m_iTrade].cmd < OP_BUY_LIMIT)
	{
		//----
		idx = m_Symbols.FindStringExact(-1, g_pTrades[m_iTrade].symbol);
		m_Symbols.SetCurSel(idx);
		m_iSec = m_Symbols.GetItemData(idx);
		//----
		m_fSL = g_pTrades[m_iTrade].sl;
		m_fTP = g_pTrades[m_iTrade].tp;
		UpdateData(FALSE);
		//----
		CString sClose;
		sClose.Format("Close #%d %s %.2lf %s &at ...", 
				g_pTrades[m_iTrade].order, 
				cmds[g_pTrades[m_iTrade].cmd], 
				g_pTrades[m_iTrade].volume/100.0, 
				g_pTrades[m_iTrade].symbol);
		m_CloseDeal.SetWindowText(sClose);
		//----
		for (int i = 0; i < g_nTrades; i++)
		{
			if (strcmp(g_pTrades[i].symbol, g_pTrades[m_iTrade].symbol) == 0 
					&& g_pTrades[i].cmd < OP_BUY_LIMIT 
					&& g_pTrades[i].cmd != g_pTrades[m_iTrade].cmd)
			{
				sClose.Format("#%d", g_pTrades[i].order);
				m_CloseDeals.AddString(sClose);
			}
		}
		if (m_CloseDeals.GetCount() > 0)
		{
			sClose.Format("Close #%d &by ...", g_pTrades[m_iTrade].order);
			m_CloseBy.SetWindowText(sClose);
			m_CloseBy.EnableWindow(TRUE);
			m_CloseDeals.EnableWindow(TRUE);
			m_CloseDeals.SetCurSel(0);
		}
	}
	//---- ������ �� ����������� ������
	if (m_iTrade >= 0 && g_pTrades[m_iTrade].order > 0 && g_pTrades[m_iTrade].cmd >= OP_BUY_LIMIT)
	{
		//----
		idx = m_Symbols.FindStringExact(-1, g_pTrades[m_iTrade].symbol);
		m_Symbols.SetCurSel(idx);
		m_iSec = m_Symbols.GetItemData(idx);
		//----
		m_Command.SetCurSel(g_pTrades[m_iTrade].cmd - OP_BUY_LIMIT);
		m_fPendingPrice = g_pTrades[m_iTrade].open_price;
		m_fSL = g_pTrades[m_iTrade].sl;
		m_fTP = g_pTrades[m_iTrade].tp;
		UpdateData(FALSE);
		//----
		CString sDelete;
		sDelete.Format(_T("Delete #%d"), g_pTrades[m_iTrade].order);
		m_Delete.SetWindowText(sDelete);
		m_Delete.EnableWindow();
	}
	//---- ��������� S/L & T/P & ���� ��� ����������� ������
	if (m_iTrade >= 0 && g_pTrades[m_iTrade].order > 0)
	{
		CString sModify;
		sModify.Format(_T("Modify #%d"), g_pTrades[m_iTrade].order);
		m_Modify.SetWindowText(sModify);
		m_Modify.EnableWindow();
	}
	//---- ���������� ������
	m_Command.SetCurSel(0);
	m_Command.SetItemData(0, OP_BUY_LIMIT);
	m_Command.SetItemData(1, OP_SELL_LIMIT);
	m_Command.SetItemData(2, OP_BUY_STOP);
	m_Command.SetItemData(3, OP_SELL_STOP);
	//----
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
//+------------------------------------------------------------------+
//| ������ ���                                                       |
//+------------------------------------------------------------------+
void COrderForm::OnGetPrices() 
{
	static char *cmds[] = {
		"buy", "sell",
		"buy limit", "sell limit",
		"buy stop", "sell stop",
		"balance", "credit"
	};
	int err;
	CString sLots;
	m_CloseDeal.EnableWindow(FALSE);
	//---- symbol
	m_iSec = m_Symbols.GetItemData(m_Symbols.GetCurSel());
	//---- ����
	m_Lots.GetWindowText(sLots);
	m_nLots = (int)(atof(sLots)/0.01);
	//---- ������
	if ((err = m_api.GetPrices(g_pSecs[m_iSec].name, m_nLots, &m_fBid, &m_fAsk)) > RET_OK_NONE)
	{
        m_Prices.SetWindowText(m_api.GetErrorDescription(err));
		return;
	}
	//---- �������� ����
	CString sFormat;
	sFormat.Format(_T("%%.%dlf / %%.%dlf"), g_pSecs[m_iSec].digits, g_pSecs[m_iSec].digits);
	CString sPrices;
	sPrices.Format(sFormat, m_fBid, m_fAsk);
	m_Prices.SetWindowText(sPrices);
	//---- ����� ��������/���������
	m_Buy.EnableWindow(TRUE);
	m_Sell.EnableWindow(TRUE);
	//---- ����� ���������
	if (m_iTrade >= 0 
			&& g_pTrades[m_iTrade].order > 0 
			&& g_pTrades[m_iTrade].cmd < OP_BUY_LIMIT 
			&& strcmp(g_pTrades[m_iTrade].symbol, g_pSecs[m_iSec].name) == 0 
			&& m_nLots <= g_pTrades[m_iTrade].volume)
	{
		sFormat.Format(_T("%%.%dlf"), g_pSecs[m_iSec].digits, g_pSecs[m_iSec].digits);
		if (g_pSecs[m_iSec].indirect == FALSE)
			sPrices.Format(sFormat, g_pTrades[m_iTrade].cmd == OP_BUY ? m_fBid : m_fAsk);
		else                   
			sPrices.Format(sFormat, g_pTrades[m_iTrade].cmd == OP_BUY ? m_fAsk : m_fBid);
		CString sClose;
		sClose.Format("Close #%d %s %.2lf %s at %s",
				g_pTrades[m_iTrade].order,
				cmds[g_pTrades[m_iTrade].cmd],
				m_nLots/100.0,
				g_pTrades[m_iTrade].symbol,
				sPrices);
		m_CloseDeal.SetWindowText(sClose);
		m_CloseDeal.EnableWindow(TRUE);
	}
}

//+------------------------------------------------------------------+
//| �������                                                          |
//+------------------------------------------------------------------+
void COrderForm::OnBuy() 
{
	SendOrder(OP_BUY);
}
//+------------------------------------------------------------------+
//| �������                                                          |
//+------------------------------------------------------------------+
void COrderForm::OnSell() 
{
	SendOrder(OP_SELL);
}
//+------------------------------------------------------------------+
//| �������/�������                                                  |
//+------------------------------------------------------------------+
void COrderForm::SendOrder(int cmd)
{
	SendOrderInfo soi;
	::ZeroMemory(&soi, sizeof(soi));
	//----
	strcpy(soi.symbol, g_pSecs[m_iSec].name);
	soi.volume = m_nLots;
	soi.cmd = cmd;
	if(g_pSecs[m_iSec].indirect == FALSE) 
		soi.price = (cmd == OP_BUY ? m_fAsk : m_fBid);
	else
		soi.price = (cmd == OP_BUY ? m_fBid : m_fAsk);
	//---- S/L & T/P
	UpdateData();
	soi.sl = m_fSL;
	soi.tp = m_fTP;
	//---- �������� �����
	int err;
	if ((err = m_api.SendOrder(&soi)) > RET_OK_NONE)
	{
        m_Prices.SetWindowText(m_api.GetErrorDescription(err));
		return;
	}
	//---- ����� ��������
	OnOK();
}
//+------------------------------------------------------------------+
//| Close By                                                         |
//+------------------------------------------------------------------+
void COrderForm::OnCloseBy() 
{
	// by order
	CString sOrder;
	m_CloseDeals.GetWindowText(sOrder);
	int order;
	sscanf(sOrder, "#%d", &order);
	//---- �������� �����
	int err;
	if ((err = m_api.CloseByOrder(g_pTrades[m_iTrade].order, order)) > RET_OK_NONE)
	{
        m_Prices.SetWindowText(m_api.GetErrorDescription(err));
		return;
	}
	//---- ����� ��������
	OnOK();
}
//+------------------------------------------------------------------+
//| ������� �������                                                  |
//+------------------------------------------------------------------+
void COrderForm::OnCloseDeal() 
{
	double fPrice;
	if (g_pSecs[m_iSec].indirect == FALSE) 
		fPrice = (g_pTrades[m_iTrade].cmd == OP_BUY ? m_fBid : m_fAsk);
	else                   
		fPrice = (g_pTrades[m_iTrade].cmd == OP_BUY ? m_fAsk : m_fBid);
	//---- �������� �����
	int err;
	if ((err = m_api.CloseOrder(g_pTrades[m_iTrade].order, fPrice, m_nLots)) > RET_OK_NONE)
	{
        m_Prices.SetWindowText(m_api.GetErrorDescription(err));
		return;
	}
	//---- ����� ��������
	OnOK();
}
//+------------------------------------------------------------------+
//| ���������� �����                                                 |
//+------------------------------------------------------------------+
void COrderForm::OnSend() 
{
	SendOrderInfo soi;
	::ZeroMemory(&soi, sizeof(soi));
	//---- symbol
	m_iSec = m_Symbols.GetItemData(m_Symbols.GetCurSel());
	strcpy(soi.symbol, g_pSecs[m_iSec].name);
	//---- ����
	CString sLots;
	m_Lots.GetWindowText(sLots);
	m_nLots = (int)(atof(sLots)/0.01);
	soi.volume = m_nLots;
	//---- command
	soi.cmd = (char)m_Command.GetItemData(m_Command.GetCurSel());
	//---- ����
	UpdateData();
	soi.price = m_fPendingPrice;
	//---- S/L & T/P
	soi.sl = m_fSL;
	soi.tp = m_fTP;
	//---- �������� �����
	int err;
	if ((err = m_api.SendOrder(&soi)) > RET_OK_NONE)
	{
        m_Prices.SetWindowText(m_api.GetErrorDescription(err));
		return;
	}
	//---- ����� ��������
	OnOK();
}
//+------------------------------------------------------------------+
//| ������� ���������� �����                                         |
//+------------------------------------------------------------------+
void COrderForm::OnDelete() 
{
	//---- �������� �����
	int err;
	if ((err = m_api.DeleteOrder(g_pTrades[m_iTrade].order)) > RET_OK_NONE)
	{
        m_Prices.SetWindowText(m_api.GetErrorDescription(err));
		return;
	}
	//---- ����� ��������
	OnOK();
}
//+------------------------------------------------------------------+
//| �������� S/L, T/P � ���� (��� ����������� ������)                |
//+------------------------------------------------------------------+
void COrderForm::OnModify() 
{
	UpdateData();
	double fPrice;
	if (g_pTrades[m_iTrade].cmd <= OP_SELL)
		fPrice = g_pTrades[m_iTrade].open_price;
	else
		fPrice = m_fPendingPrice;
	//---- �������� �����
	int err;
	if ((err = m_api.ModifyOrder(g_pTrades[m_iTrade].order, fPrice, m_fSL, m_fTP)) > RET_OK_NONE)
	{
        m_Prices.SetWindowText(m_api.GetErrorDescription(err));
		return;
	}
	//---- ����� ��������
	OnOK();
}
