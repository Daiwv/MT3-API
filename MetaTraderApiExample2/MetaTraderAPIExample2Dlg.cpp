// MetaTraderAPIExample2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "MetaTraderAPIExample2.h"
#include "MetaTraderAPIExample2Dlg.h"
#include "OpenAccountDlg.h"
#include "OrderForm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//---- Pumping сообщение
UINT g_PumpingMsg;
//---- инструменты
ConSecurity*	g_pSecs;
int				g_nSecs;
//---- текущие позиции
TradeRecord*	g_pTrades;
int				g_nTrades;

/////////////////////////////////////////////////////////////////////////////
// CMetaTraderAPIExample2Dlg dialog

CMetaTraderAPIExample2Dlg::CMetaTraderAPIExample2Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMetaTraderAPIExample2Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMetaTraderAPIExample2Dlg)
	m_sPasswd = _T("");
	m_nPort = 1950;
	m_sServer = _T("192.168.0.1");
	m_nLogin = 0;
	//}}AFX_DATA_INIT
	m_bConnected = FALSE;
	g_pSecs = NULL;
	g_nSecs = 0;
	g_pTrades = NULL;
	g_nTrades = 0;
	m_bDoOrder = FALSE;
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CMetaTraderAPIExample2Dlg::~CMetaTraderAPIExample2Dlg()
{
	// важно не забыть освободить буферы при помощи функции ::HeapFree
	if (g_pSecs != NULL)
		::HeapFree(::GetProcessHeap(), 0, g_pSecs);
	if (g_pTrades != NULL)
		::HeapFree(::GetProcessHeap(), 0, g_pTrades);
}

void CMetaTraderAPIExample2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMetaTraderAPIExample2Dlg)
	DDX_Control(pDX, IDC_STATICSUMMARY, m_stSummary);
	DDX_Control(pDX, IDC_STATICQUOTES, m_stQuotes);
	DDX_Control(pDX, IDC_BTNHIDESEC, m_btnHideSec);
	DDX_Control(pDX, IDC_BTNADDSEC, m_btnAddSec);
	DDX_Control(pDX, IDC_LISTTRADE, m_lstTrade);
	DDX_Control(pDX, IDC_LISTNEWS, m_lstNews);
	DDX_Control(pDX, IDC_LISTMAIL, m_lstMail);
	DDX_Control(pDX, IDC_LISTHIST, m_lstHist);
	DDX_Control(pDX, IDC_TAB, m_tab);
	DDX_Control(pDX, IDC_LISTMARKET, m_lstMarket);
	DDX_Control(pDX, IDC_EDITLOGIN, m_edtLogin);
	DDX_Control(pDX, IDC_EDITPORT, m_edtPort);
	DDX_Control(pDX, IDC_EDITSERVER, m_edtServer);
	DDX_Control(pDX, IDC_BNTPASSWD, m_btnPasswd);
	DDX_Control(pDX, IDC_COMBOSECS, m_cmbSecs);
	DDX_Control(pDX, IDC_BTNOPENACC, m_btnOpenAcc);
	DDX_Control(pDX, IDC_BTNDISCONNECT, m_btnDisconnect);
	DDX_Control(pDX, IDC_BTNCONNECT, m_btnConnect);
	DDX_Control(pDX, IDC_BNTLOGIN, m_btnLogin);
	DDX_Control(pDX, IDC_LISTSTATUS, m_status);
	DDX_Text(pDX, IDC_EDITPASSWD, m_sPasswd);
	DDX_Text(pDX, IDC_EDITPORT, m_nPort);
	DDX_Text(pDX, IDC_EDITSERVER, m_sServer);
	DDX_Text(pDX, IDC_EDITLOGIN, m_nLogin);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMetaTraderAPIExample2Dlg, CDialog)
	//{{AFX_MSG_MAP(CMetaTraderAPIExample2Dlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTNCONNECT, OnConnect)
	ON_BN_CLICKED(IDC_BTNDISCONNECT, OnDisconnect)
	ON_BN_CLICKED(IDC_BTNOPENACC, OnOpenacc)
	ON_BN_CLICKED(IDC_BNTLOGIN, OnBntlogin)
	ON_BN_CLICKED(IDC_BNTPASSWD, OnBntpasswd)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, OnSelchangeTab)
	ON_BN_CLICKED(IDC_BTNADDSEC, OnBtnaddsec)
	ON_BN_CLICKED(IDC_BTNHIDESEC, OnBtnhidesec)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTMAIL, OnDblclkListmail)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTNEWS, OnDblclkListnews)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTMARKET, OnDblclkListmarket)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTTRADE, OnDblclkListtrade)
	//}}AFX_MSG_MAP
	ON_REGISTERED_MESSAGE(g_PumpingMsg, OnPumpingMsg)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMetaTraderAPIExample2Dlg message handlers

BOOL CMetaTraderAPIExample2Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
//---- pumping сообщение
	g_PumpingMsg = ::RegisterWindowMessage(_T("MetaTraderAPI_Pumping_Message"));

//---- market watch
	RECT rc;
	m_lstMarket.GetClientRect(&rc);
	m_lstMarket.InsertColumn(0, _T("Symbol"), LVCFMT_LEFT, rc.right/3, 0);
	m_lstMarket.InsertColumn(1, _T("Bid"), LVCFMT_LEFT, rc.right/3, 1);
	m_lstMarket.InsertColumn(2, _T("Ask"), LVCFMT_LEFT, rc.right/3, 2);
	m_lstMarket.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

//----
	m_tab.InsertItem(0, _T("Trade"));
	m_tab.InsertItem(1, _T("Account History"));
	m_tab.InsertItem(2, _T("News"));
	m_tab.InsertItem(3, _T("Mailbox"));
	m_tab.InsertItem(4, _T("Log"));

//----
	WINDOWPLACEMENT wp;
	m_status.GetWindowPlacement(&wp);
	m_lstTrade.SetWindowPlacement(&wp);
	m_lstHist.SetWindowPlacement(&wp);
	m_lstNews.SetWindowPlacement(&wp);
	m_lstMail.SetWindowPlacement(&wp);

//----
	m_lstTrade.GetClientRect(&rc);
	int cx = ::GetSystemMetrics(SM_CXHTHUMB);
	rc.right -= cx;
	//---- trade
	m_lstTrade.InsertColumn(0, _T("Ticket"), LVCFMT_LEFT, rc.right/12, 0);
	m_lstTrade.InsertColumn(1, _T("Time"), LVCFMT_LEFT, rc.right/12, 1);
	m_lstTrade.InsertColumn(2, _T("Type"), LVCFMT_LEFT, rc.right/12, 2);
	m_lstTrade.InsertColumn(3, _T("Lots"), LVCFMT_LEFT, rc.right/12, 3);
	m_lstTrade.InsertColumn(4, _T("Symbol"), LVCFMT_LEFT, rc.right/12, 4);
	m_lstTrade.InsertColumn(5, _T("Open"), LVCFMT_LEFT, rc.right/12, 5);
	m_lstTrade.InsertColumn(6, _T("S/L"), LVCFMT_LEFT, rc.right/12, 6);
	m_lstTrade.InsertColumn(7, _T("T/P"), LVCFMT_LEFT, rc.right/12, 7);
	m_lstTrade.InsertColumn(8, _T("Curr"), LVCFMT_LEFT, rc.right/12, 8);
	m_lstTrade.InsertColumn(9, _T("Comm"), LVCFMT_LEFT, rc.right/12, 9);
	m_lstTrade.InsertColumn(10, _T("Swap"), LVCFMT_LEFT, rc.right/12, 10);
	m_lstTrade.InsertColumn(11, _T("Profit"), LVCFMT_LEFT, rc.right/12, 11);
	m_lstTrade.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//---- account history
	m_lstHist.InsertColumn(0, _T("Ticket"), LVCFMT_LEFT, rc.right/13, 0);
	m_lstHist.InsertColumn(1, _T("Time"), LVCFMT_LEFT, rc.right/13, 1);
	m_lstHist.InsertColumn(2, _T("Type"), LVCFMT_LEFT, rc.right/13, 2);
	m_lstHist.InsertColumn(3, _T("Lots"), LVCFMT_LEFT, rc.right/13, 3);
	m_lstHist.InsertColumn(4, _T("Symbol"), LVCFMT_LEFT, rc.right/13, 4);
	m_lstHist.InsertColumn(5, _T("Price"), LVCFMT_LEFT, rc.right/13, 5);
	m_lstHist.InsertColumn(6, _T("S/L"), LVCFMT_LEFT, rc.right/13, 6);
	m_lstHist.InsertColumn(7, _T("T/P"), LVCFMT_LEFT, rc.right/13, 7);
	m_lstHist.InsertColumn(8, _T("Time"), LVCFMT_LEFT, rc.right/13, 8);
	m_lstHist.InsertColumn(9, _T("Price"), LVCFMT_LEFT, rc.right/13, 9);
	m_lstHist.InsertColumn(10, _T("Comm"), LVCFMT_LEFT, rc.right/13, 10);
	m_lstHist.InsertColumn(11, _T("Swap"), LVCFMT_LEFT, rc.right/13, 11);
	m_lstHist.InsertColumn(12, _T("Profit"), LVCFMT_LEFT, rc.right/13, 12);
	m_lstHist.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//---- news
	m_lstNews.InsertColumn(0, _T("Time"), LVCFMT_LEFT, rc.right/2, 0);
	m_lstNews.InsertColumn(1, _T("Subject"), LVCFMT_LEFT, rc.right/2, 1);
	m_lstNews.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//---- mailbox
	m_lstMail.InsertColumn(0, _T("Time"), LVCFMT_LEFT, rc.right/3, 0);
	m_lstMail.InsertColumn(1, _T("From"), LVCFMT_LEFT, rc.right/3, 1);
	m_lstMail.InsertColumn(2, _T("Subject"), LVCFMT_LEFT, rc.right/3, 2);
	m_lstMail.InsertColumn(3, _T("Path"), LVCFMT_LEFT, 0, 3);
	m_lstMail.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	//----
	OnSelchangeTab(NULL, NULL);
//----
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMetaTraderAPIExample2Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMetaTraderAPIExample2Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//+------------------------------------------------------------------+
//| Коннект к серверу                                                |
//+------------------------------------------------------------------+
void CMetaTraderAPIExample2Dlg::OnConnect() 
{
	UpdateData();
	int err;
	if ((err = m_api.Connect(m_sServer, m_nPort)) > RET_OK_NONE)
	{
		MessageBox(m_api.GetErrorDescription(err), _T("Connect"), MB_OK | MB_ICONERROR);
		return;
	}
	m_status.InsertString(0, _T("Connected OK"));
	m_bConnected = TRUE;
	m_edtServer.EnableWindow(FALSE);
	m_edtPort.EnableWindow(FALSE);
	m_btnLogin.EnableWindow();
	m_btnOpenAcc.EnableWindow();
	m_btnDisconnect.EnableWindow();
}
//+------------------------------------------------------------------+
//| Дисконнект                                                       |
//+------------------------------------------------------------------+
void CMetaTraderAPIExample2Dlg::OnDisconnect() 
{
	int err;
	if ((err = m_api.Disconnect()) > RET_OK_NONE)
	{
		MessageBox(m_api.GetErrorDescription(err), _T("Disconnect"), MB_OK | MB_ICONERROR);
		return;
	}
	// важно не забыть освободить буферы при помощи функции ::HeapFree
	if (g_pSecs != NULL)
	{
		::HeapFree(::GetProcessHeap(), 0, g_pSecs);
		g_pSecs = NULL;
	}
	g_nSecs = 0;
	if (g_pTrades != NULL)
	{
		::HeapFree(::GetProcessHeap(), 0, g_pTrades);
		g_pTrades = NULL;
	}
	g_nTrades = 0;
	//----
	m_lstMarket.DeleteAllItems();
	m_lstTrade.DeleteAllItems();
	m_lstHist.DeleteAllItems();
	m_lstNews.DeleteAllItems();
	m_stSummary.SetWindowText(NULL);
	m_status.InsertString(0, _T("Disconnected OK"));
	m_bConnected = FALSE;
	m_edtServer.EnableWindow();
	m_edtPort.EnableWindow();
	m_edtLogin.EnableWindow();
	m_cmbSecs.ResetContent();
	m_btnLogin.EnableWindow(FALSE);
	m_btnOpenAcc.EnableWindow(FALSE);
	m_btnDisconnect.EnableWindow(FALSE);
	m_btnPasswd.EnableWindow(FALSE);
	m_btnAddSec.EnableWindow(FALSE);
	m_btnHideSec.EnableWindow(FALSE);
}
//+------------------------------------------------------------------+
//| Открыть демо счет                                                |
//+------------------------------------------------------------------+
void CMetaTraderAPIExample2Dlg::OnOpenacc() 
{
	COpenAccountDlg dlg;
	if (dlg.DoModal() != IDOK)
		return;
	int err;
	DemoAccountInfo acc;
	memset(&acc, 0, sizeof(acc));
	strcpy(acc.name, dlg.m_sName);
	strcpy(acc.email, dlg.m_sEmail);
	strcpy(acc.address, dlg.m_sAddress);
	strcpy(acc.city, dlg.m_sCity);
	strcpy(acc.country, dlg.m_sCountry);
	strcpy(acc.state, dlg.m_sState);
	strcpy(acc.phone, dlg.m_sPhone);
	strcpy(acc.zipcode, dlg.m_sZip);
	strcpy(acc.group, "demoforex");
	acc.balance = dlg.m_nDeposit;
	acc.leverage = dlg.m_nLeverage;
	if ((err = m_api.OpenDemoAccount(&acc)) > RET_OK_NONE)
	{
		MessageBox(m_api.GetErrorDescription(err), _T("OpenDemoAccount"), MB_OK | MB_ICONERROR);
		return;
	}
	m_status.InsertString(0, _T("Get demo account OK"));
	m_nLogin = acc.login;
	m_sPasswd = acc.password;
	UpdateData(FALSE);
	//
	OnDisconnect();
	OnConnect();
}
//+------------------------------------------------------------------+
//| Логин                                                            |
//+------------------------------------------------------------------+
void CMetaTraderAPIExample2Dlg::OnBntlogin() 
{
	int err;
	UpdateData();
	//---- логин
	if ((err = m_api.Login(m_nLogin, m_sPasswd)) > RET_OK_NONE)
	{
		MessageBox(m_api.GetErrorDescription(err), _T("Login"), MB_OK | MB_ICONERROR);
		return;
	}
	m_status.InsertString(0, _T("Login to server OK"));
	
	//---- обновим инструменты
	if ((err = m_api.RefreshSecurities()) > RET_OK_NONE)
	{
		MessageBox(m_api.GetErrorDescription(err), _T("RefreshSecurities"), MB_OK | MB_ICONERROR);
		return;
	}
	// важно не забыть освободить буферы при помощи функции ::HeapFree
	if (g_pSecs != NULL)
		::HeapFree(::GetProcessHeap(), 0, g_pSecs);
	//---- получим доступные инструменты
	g_pSecs = m_api.GetSecurities(&g_nSecs);
	m_cmbSecs.ResetContent();
	for (int i = 0; i < g_nSecs; i++)
	{
		m_cmbSecs.AddString(g_pSecs[i].name);
		AddSecurity(i);
	}
	if (g_nSecs > 0)
	{
		m_cmbSecs.SetCurSel(0);
		m_btnAddSec.EnableWindow();
		m_btnHideSec.EnableWindow();
	}

	//---- обновим историю счета
	UpdateAccountHistory();

	//---- установим pumping сообщение
	if ((err = m_api.SetPumpingMode(m_hWnd, g_PumpingMsg)) > RET_OK_NONE)
	{
		MessageBox(m_api.GetErrorDescription(err), _T("SetPumpingMode"), MB_OK | MB_ICONERROR);
		return;
	}

	//----
	m_nQuotes = 0;
	m_edtLogin.EnableWindow(FALSE);
	m_btnLogin.EnableWindow(FALSE);
	m_btnOpenAcc.EnableWindow(FALSE);
	m_btnPasswd.EnableWindow();
}
//+------------------------------------------------------------------+
//| Изменить пароль                                                  |
//+------------------------------------------------------------------+
void CMetaTraderAPIExample2Dlg::OnBntpasswd() 
{
	int err;
	//---- необходимо новое соединение
	//---- основное соединение в pumping режиме
	CMetaTraderAPI api;
	if ((err = api.Connect(m_sServer, m_nPort)) > RET_OK_NONE)
	{
		MessageBox(api.GetErrorDescription(err), _T("Connect"), MB_OK | MB_ICONERROR);
		return;
	}
	if ((err = api.Login(m_nLogin, m_sPasswd)) > RET_OK_NONE)
	{
		MessageBox(api.GetErrorDescription(err), _T("Login"), MB_OK | MB_ICONERROR);
		api.Disconnect();
		return;
	}

	CString passwd = m_sPasswd;
	//---- изменим пароль
	UpdateData();
	if ((err = api.ChangePassword(m_sPasswd)) > RET_OK_NONE)
	{
		MessageBox(api.GetErrorDescription(err), _T("ChangePassword"), MB_OK | MB_ICONERROR);
		m_sPasswd = passwd;
		UpdateData(FALSE);
		return;
	}
	m_status.InsertString(0, _T("Change password OK"));
	//----
	api.Disconnect();
}
//+------------------------------------------------------------------+
//| Обработка pumping сообщений                                      |
//+------------------------------------------------------------------+
LRESULT CMetaTraderAPIExample2Dlg::OnPumpingMsg(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case UPDATE_BIDASK:
		{
			CString sQuotes;
			sQuotes.Format(_T(" %d"), ++m_nQuotes);
			m_stQuotes.SetWindowText(sQuotes);
			//----
			int items;
			TickInfo* pti = m_api.GetUpdatedTickInfo(&items);
			for (int i = 0; i < items; i++)
			{
				int cnt = m_lstMarket.GetItemCount();
				for (int s = 0; s < cnt; s++)
				{
					CString sSymbol = m_lstMarket.GetItemText(s, 0);
					if (sSymbol == pti[i].symbol)
					{
						CString sFormat;
						sFormat.Format(_T("%%.%dlf"), g_pSecs[m_lstMarket.GetItemData(s)].digits);
						CString sPrice;
						sPrice.Format(sFormat, pti[i].bid);
						m_lstMarket.SetItemText(s, 1, sPrice);
						sPrice.Format(sFormat, pti[i].ask);
						m_lstMarket.SetItemText(s, 2, sPrice);
					}
				}
			}
			//---- обновим открытые позиции
			if (m_bDoOrder == FALSE)
				UpdateTrades();
			//----
			break;
		}
	case UPDATE_NEWS:
		{
			int items;
			NewsTopic* pnt = m_api.GetLastNews(&items);
			for (int i = 0; i < items; i++)
			{
				int idx = m_lstNews.InsertItem(m_lstNews.GetItemCount(), pnt[i].ctm);
				m_lstNews.SetItemText(idx, 1, pnt[i].topic);
				m_lstNews.SetItemData(idx, pnt[i].newkey);
			}
			//----
			if (pnt != NULL)
				::HeapFree(::GetProcessHeap(), 0, pnt);
			//----
			break;
		}
	case UPDATE_MAIL:
		{
			int err;
			char path[MAX_PATH];
			int len = MAX_PATH;
			if ((err = m_api.GetLastMail(path, &len)) > RET_OK_NONE)
			{
				m_status.InsertString(0, _T("Get last mail FAILED"));
				break;
			}
			//---- считаем заголовок
			FILE *In;
			if ((In = fopen(path,"rb")) != NULL)
			{
				MailBoxHeader mbh;
				if (fread(&mbh, sizeof(mbh), 1, In) == 1) 
				{ 
					mbh.from[63] = 0;
					mbh.subject[127] = 0;
					int idx;
					tm *tt;
					if ((tt = gmtime(&mbh.time)) != NULL) 
					{
						CString str;
						str.Format("%04d.%02d.%02d %02d:%02d", 
								1900+tt->tm_year, 1+tt->tm_mon, tt->tm_mday, 
								tt->tm_hour, tt->tm_min);
						idx = m_lstMail.InsertItem(m_lstMail.GetItemCount(), str);
					}
					else
						idx = m_lstMail.InsertItem(m_lstMail.GetItemCount(), "unknown");
					m_lstMail.SetItemText(idx, 1, mbh.from);
					m_lstMail.SetItemText(idx, 2, mbh.subject);
					m_lstMail.SetItemText(idx, 3, path);
				}
				fclose(In);
			}
			//----
			break;
		}
	case UPDATE_TRADES:
		{
			if (m_bDoOrder == FALSE)
			{
				UpdateTrades();
				UpdateAccountHistory();
			}
			break;
		}
	}
//----
	return 0;
}
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CMetaTraderAPIExample2Dlg::OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int sel = m_tab.GetCurSel();
	switch (sel)
	{
	case 0:
		m_lstTrade.ShowWindow(SW_SHOW);
		m_lstHist.ShowWindow(SW_HIDE);
		m_lstNews.ShowWindow(SW_HIDE);
		m_lstMail.ShowWindow(SW_HIDE);
		m_status.ShowWindow(SW_HIDE);
		break;
	case 1:
		m_lstTrade.ShowWindow(SW_HIDE);
		m_lstHist.ShowWindow(SW_SHOW);
		m_lstNews.ShowWindow(SW_HIDE);
		m_lstMail.ShowWindow(SW_HIDE);
		m_status.ShowWindow(SW_HIDE);
		break;
	case 2:
		m_lstTrade.ShowWindow(SW_HIDE);
		m_lstHist.ShowWindow(SW_HIDE);
		m_lstNews.ShowWindow(SW_SHOW);
		m_lstMail.ShowWindow(SW_HIDE);
		m_status.ShowWindow(SW_HIDE);
		break;
	case 3:
		m_lstTrade.ShowWindow(SW_HIDE);
		m_lstHist.ShowWindow(SW_HIDE);
		m_lstNews.ShowWindow(SW_HIDE);
		m_lstMail.ShowWindow(SW_SHOW);
		m_status.ShowWindow(SW_HIDE);
		break;
	case 4:
		m_lstTrade.ShowWindow(SW_HIDE);
		m_lstHist.ShowWindow(SW_HIDE);
		m_lstNews.ShowWindow(SW_HIDE);
		m_lstMail.ShowWindow(SW_HIDE);
		m_status.ShowWindow(SW_SHOW);
		break;
	}
	//----
	if (pResult != NULL) 
		*pResult = 0;
}
//+------------------------------------------------------------------+
//| Добавить инструмент                                              |
//+------------------------------------------------------------------+
void CMetaTraderAPIExample2Dlg::OnBtnaddsec() 
{
	CString sec;
	m_cmbSecs.GetWindowText(sec);
	int cnt = m_lstMarket.GetItemCount();
	for (int i = 0; i < cnt; i++)
	{
		if (sec == m_lstMarket.GetItemText(i, 0))
			return;
	}
	AddSecurity(m_cmbSecs.GetCurSel());
}
//+------------------------------------------------------------------+
//| Скрыть инструмент                                                |
//+------------------------------------------------------------------+
void CMetaTraderAPIExample2Dlg::OnBtnhidesec() 
{
	CString sec;
	m_cmbSecs.GetWindowText(sec);
	int cnt = m_lstMarket.GetItemCount();
	int i;
	for (i = 0; i < cnt; i++)
	{
		if (sec == m_lstMarket.GetItemText(i, 0))
			break;
	}
	if (i == cnt)
		return;
	int err;
	if ((err = m_api.HideSymbol(sec)) > RET_OK_NONE)
	{
		MessageBox(m_api.GetErrorDescription(err), _T("HideSymbol"), MB_OK | MB_ICONERROR);
		return;
	}
	//---- unused[0] сигнализирует о том, что сивол скрыт
	g_pSecs[m_lstMarket.GetItemData(i)].unused[0] = 0;
	//----
	m_lstMarket.DeleteItem(i);
	m_status.InsertString(0, _T("Hide symbol OK"));
}
//+------------------------------------------------------------------+
//| Показать письмо                                                  |
//+------------------------------------------------------------------+
void CMetaTraderAPIExample2Dlg::OnDblclkListmail(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int sel = m_lstMail.GetNextItem(-1, LVNI_SELECTED);
	if (sel < 0)
		return;
	//----
	FILE *In;
	if ((In = fopen(m_lstMail.GetItemText(sel, 3), "rb")) == NULL) 
		return;
	//----
	fseek(In, 0, SEEK_END); 
	int len = ftell(In) - sizeof(MailBoxHeader); 
	if(len>0)
	{
		fseek(In, sizeof(MailBoxHeader), SEEK_SET);
		char *buf = new char[len+1];
		fread(buf, len, 1, In); 
		buf[len] = 0;
		MessageBox(buf, _T("Mail"));
		delete[] buf;
	}
	fclose(In);
	//----
	*pResult = 0;
}
//+------------------------------------------------------------------+
//| Показать новость                                                 |
//+------------------------------------------------------------------+
void CMetaTraderAPIExample2Dlg::OnDblclkListnews(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int sel = m_lstNews.GetNextItem(-1, LVNI_SELECTED);
	if (sel < 0)
		return;
	int err;
	//---- необходимо новое соединение
	//---- основное соединение в pumping режиме
	CMetaTraderAPI api;
	if ((err = api.Connect(m_sServer, m_nPort)) > RET_OK_NONE)
	{
		MessageBox(api.GetErrorDescription(err), _T("Connect"), MB_OK | MB_ICONERROR);
		return;
	}
	if ((err = api.Login(m_nLogin, m_sPasswd)) > RET_OK_NONE)
	{
		MessageBox(api.GetErrorDescription(err), _T("Login"), MB_OK | MB_ICONERROR);
		api.Disconnect();
		return;
	}
	//----
	char *pnb = api.GetNewsBody(m_lstNews.GetItemData(sel));
	if (pnb != NULL)
	{
		MessageBox(pnb, _T("News"));
		::HeapFree(::GetProcessHeap(), 0, pnb);
	}
	else
		MessageBox(_T("no data"), _T("News"), MB_OK);
	Invalidate();
	UpdateWindow();
	//----
	api.Disconnect();
	*pResult = 0;
}
//+------------------------------------------------------------------+
//| Обновить текущие позиции                                         |
//+------------------------------------------------------------------+
void CMetaTraderAPIExample2Dlg::UpdateTrades()
{
	static char *cmds[] = {
		"buy", "sell",
		"buy limit", "sell limit",
		"buy stop", "sell stop",
		"balance", "credit"
	};
	m_lstTrade.SetRedraw(FALSE);
	int sel = m_lstTrade.GetNextItem(-1, LVNI_SELECTED);
	m_lstTrade.DeleteAllItems();
	//----
	if (g_pTrades != NULL)
		::HeapFree(::GetProcessHeap(), 0, g_pTrades);
	BriefUserInfo bui;
	::ZeroMemory(&bui, sizeof(bui));
	g_pTrades = m_api.GetTradeRecords(&bui, &g_nTrades);
	for (int i = 0; i < g_nTrades; i++)
	{
		CString str;
		//----
		str.Format(_T("%d"), g_pTrades[i].order);
		int idx = m_lstTrade.InsertItem(m_lstTrade.GetItemCount(), str);
		//----
		tm *tt;
		if ((tt = gmtime(&g_pTrades[i].open_time)) != NULL) 
		{
			str.Format("%04d.%02d.%02d %02d:%02d", 
					1900+tt->tm_year, 1+tt->tm_mon, tt->tm_mday, 
					tt->tm_hour, tt->tm_min);
		}
		else
			str = "unknown";
		m_lstTrade.SetItemText(idx, 1, str);
		//----
		m_lstTrade.SetItemText(idx, 2, cmds[g_pTrades[i].cmd]);
		//----
		str.Format(_T("%.2lf"), g_pTrades[i].volume/100.0);
		m_lstTrade.SetItemText(idx, 3, str);
		//----
		m_lstTrade.SetItemText(idx, 4, g_pTrades[i].symbol);
		//----
		CString sFormat;
		sFormat.Format(_T("%%.%dlf"), g_pTrades[i].digits);
		str.Format(sFormat, g_pTrades[i].open_price);
		m_lstTrade.SetItemText(idx, 5, str);
		//----
		str.Format(sFormat, g_pTrades[i].sl);
		m_lstTrade.SetItemText(idx, 6, str);
		//----
		str.Format(sFormat, g_pTrades[i].tp);
		m_lstTrade.SetItemText(idx, 7, str);
		//----
		str.Format(sFormat, g_pTrades[i].close_price);
		m_lstTrade.SetItemText(idx, 8, str);
		//----
		str.Format(_T("%.2lf"), g_pTrades[i].commission);
		m_lstTrade.SetItemText(idx, 9, str);
		//----
		str.Format(_T("%.2lf"), g_pTrades[i].storage);
		m_lstTrade.SetItemText(idx, 10, str);
		//----
		str.Format(_T("%.2lf"), g_pTrades[i].profit);
		m_lstTrade.SetItemText(idx, 11, str);
		//----
		m_lstTrade.SetItemData(idx, g_pTrades[i].cmd);
	}
	m_lstTrade.SetItemState(sel, LVIS_SELECTED, LVIS_SELECTED);
	m_lstTrade.SetRedraw();
	//----
	CString sSummary;
	sSummary.Format(_T(" Balance: %.2lf  Credit: %.2lf  Equity: %.2lf  Margin: %.2lf  Free margin: %.2lf"), 
			bui.balance, bui.credit, bui.equity, bui.margin, bui.freemargin);
	m_stSummary.SetWindowText(sSummary);
}
//+------------------------------------------------------------------+
//| Обновить историю счета                                           |
//+------------------------------------------------------------------+
void CMetaTraderAPIExample2Dlg::UpdateAccountHistory()
{
	static char *cmds[] = {
		"buy", "sell",
		"buy limit", "sell limit",
		"buy stop", "sell stop",
		"balance", "credit"
	};
	int err;
	//---- необходимо новое соединение
	//---- основное соединение в pumping режиме
	CMetaTraderAPI api;
	if ((err = api.Connect(m_sServer, m_nPort)) > RET_OK_NONE)
	{
		MessageBox(api.GetErrorDescription(err), _T("Connect"), MB_OK | MB_ICONERROR);
		return;
	}
   ::Sleep(1000);
	if ((err = api.Login(m_nLogin, m_sPasswd)) > RET_OK_NONE)
	{
		MessageBox(api.GetErrorDescription(err), _T("Login"), MB_OK | MB_ICONERROR);
		api.Disconnect();
		return;
	}
	//----
	int items;
	TradeRecord* ptr = api.GetTradeHistory(0, time(NULL), &items);
	if (items > 0)
	{
		m_lstHist.SetRedraw(FALSE);
		int sel = m_lstHist.GetNextItem(-1, LVNI_SELECTED);
		m_lstHist.DeleteAllItems();
		for (int i = 0; i < items; i++)
		{
			CString str;
			//----
			str.Format(_T("%d"), ptr[i].order);
			int idx = m_lstHist.InsertItem(m_lstHist.GetItemCount(), str);
			//----
			tm *tt;
			if ((tt = gmtime(&ptr[i].open_time)) != NULL) 
			{
				str.Format("%04d.%02d.%02d %02d:%02d", 
						1900+tt->tm_year, 1+tt->tm_mon, tt->tm_mday, 
						tt->tm_hour, tt->tm_min);
			}
			else
				str = "unknown";
			m_lstHist.SetItemText(idx, 1, str);
			//----
			m_lstHist.SetItemText(idx, 2, cmds[ptr[i].cmd]);
			//----
			str.Format(_T("%.2lf"), ptr[i].volume/100.0);
			m_lstHist.SetItemText(idx, 3, str);
			//----
			m_lstHist.SetItemText(idx, 4, ptr[i].symbol);
			//----
			CString sFormat;
			sFormat.Format(_T("%%.%dlf"), ptr[i].digits);
			str.Format(sFormat, ptr[i].open_price);
			m_lstHist.SetItemText(idx, 5, str);
			//----
			str.Format(sFormat, ptr[i].sl);
			m_lstHist.SetItemText(idx, 6, str);
			//----
			str.Format(sFormat, ptr[i].tp);
			m_lstHist.SetItemText(idx, 7, str);
			//----
			if ((tt = gmtime(&ptr[i].close_time)) != NULL) 
			{
				str.Format("%04d.%02d.%02d %02d:%02d", 
						1900+tt->tm_year, 1+tt->tm_mon, tt->tm_mday, 
						tt->tm_hour, tt->tm_min);
			}
			else
				str = "unknown";
			m_lstHist.SetItemText(idx, 8, str);
			//----
			str.Format(sFormat, ptr[i].close_price);
			m_lstHist.SetItemText(idx, 9, str);
			//----
			str.Format(_T("%.2lf"), ptr[i].commission);
			m_lstHist.SetItemText(idx, 10, str);
			//----
			str.Format(_T("%.2lf"), ptr[i].storage);
			m_lstHist.SetItemText(idx, 11, str);
			//----
			str.Format(_T("%.2lf"), ptr[i].profit);
			m_lstHist.SetItemText(idx, 12, str);
		}
		m_lstHist.SetItemState(sel, LVIS_SELECTED, LVIS_SELECTED);
		m_lstHist.SetRedraw();
	}
	if (ptr != NULL)
		::HeapFree(::GetProcessHeap(), 0, ptr);
}
//+------------------------------------------------------------------+
//| Добавить инструмент                                              |
//+------------------------------------------------------------------+
void CMetaTraderAPIExample2Dlg::AddSecurity(int isec)
{
	int err;
	if ((err = m_api.AddSymbol(g_pSecs[isec].name)) > RET_OK_NONE)
	{
		MessageBox(m_api.GetErrorDescription(err), _T("AddSymbol"), MB_OK | MB_ICONERROR);
		return;
	}
	//---- unused[0] сигнализирует о том, что сивол выбран
	g_pSecs[isec].unused[0] = 1;
	//----
	int idx = m_lstMarket.InsertItem(m_lstMarket.GetItemCount(), g_pSecs[isec].name);
	m_lstMarket.SetItemData(idx, isec);
	m_status.InsertString(0, _T("Add symbol OK"));
}
//+------------------------------------------------------------------+
//| Ордер                                                            |
//+------------------------------------------------------------------+
void CMetaTraderAPIExample2Dlg::OnDblclkListmarket(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int sel = m_lstMarket.GetNextItem(-1, LVNI_SELECTED);
	if (sel < 0)
		return;
	//----
	m_bDoOrder = TRUE;
	COrderForm of(m_sServer, m_nPort, m_nLogin, m_sPasswd, m_lstMarket.GetItemData(sel), -1);
	of.DoModal();
	m_bDoOrder = FALSE;
	//----
	*pResult = 0;
}
//+------------------------------------------------------------------+
//| Закрыть позицию                                                  |
//+------------------------------------------------------------------+
void CMetaTraderAPIExample2Dlg::OnDblclkListtrade(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int sel = m_lstTrade.GetNextItem(-1, LVNI_SELECTED);
	if (sel < 0)
		return;
	//----
	m_bDoOrder = TRUE;
	COrderForm of(m_sServer, m_nPort, m_nLogin, m_sPasswd, -1, sel);
	of.DoModal();
	m_bDoOrder = FALSE;
	//----
	*pResult = 0;
}
