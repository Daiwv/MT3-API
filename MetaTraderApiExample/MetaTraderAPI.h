//+------------------------------------------------------------------+
//|                                           MetaTrader API Example |
//|                      Copyright c 2003, MetaQuotes Software Corp. |
//|                                         http://www.metaquotes.ru |
//+------------------------------------------------------------------+
#if !defined(AFX_METATRADERAPI_H__CCF82B67_4DC1_467E_9C7D_553616457969__INCLUDED_)
#define AFX_METATRADERAPI_H__CCF82B67_4DC1_467E_9C7D_553616457969__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>
#include <winsock.h>
#include <time.h>

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
struct DemoAccountInfo
  {
   int            login;          // �������� ����� �������
   char           password[16];   // ��� �� ������
   char           phonepassword[16];
   char           name[64];       // ���
   char           group[16];      // ������
   char           country[32];    // ������
   char           city[32];       // �����
   char           state[32];      // ����
   char           zipcode[16];    // ������
   char           address[32];    // �����
   char           phone[32];      // �������
   char           email[32];      // �����
   char           unused[72];
   int            leverage;       // �����
   double         balance;        // ������
   char           reserved[20];
  };
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
#pragma pack(1)
struct RateInfo
  {
   time_t         ctm;            // ������� ����� � ��������
   double         open;           // ���� ��������
   double         low;            // ���� low
   double         high;           // ���� high
   double         close;          // ���� ��������
   int            vol;            // �����
  };
struct NewsTopic
  {
   char  ctm[20];                 // ����� � ������� "yyyy/mm/dd hh:mm:ss"
   char  topic[256];              // ���������
   char  keywords[256];           // �������� �����
   int   len;                     // ����� ���������
   char *body;                    // ���� ��������� (���� ����)
   int   key;                     // ��� ������� ������
   int   newkey;                  // ��� ������� �����
  };
struct BriefUserInfo
  {
   int            login;          // �����
   int            isdemo;         // ����?
   char           name[64];       // ���
   char           company[64];    // ��������
   double         balance;        // ������
   double         equity;         // 
   double         credit;         // ������
   double         margin;         // �����
   double         freemargin;     // ��������� �����
   double         profit;         // �������
   int            marginmode;     // 
   int            margincall;     // ������� ����������
   char           margintype;     // ��� ���������� 0-%,1-$
   int            allow_flags;    // ����� ����������
   int            leverage;
  };
struct SendOrderInfo              // ������������ ������� ������� ������
  {
   char   req_code;               // ��� ������� � ���������
   int    order;                  // �����
   char   symbol[8];              // ����������
   int    volume;                 // �����
   char   cmd;                    // ������� OP_BUY....OP_SELL_STOP
   double price;                  // ���� ����������
   double sl,tp;                  // �����
   int    crc;                    // ����������� �����
  };
#pragma pack(8)
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
struct TradeRecord
  {
   int            order;          // ����� ������
   int            login;          // ���� �����������
   char           symbol[8];      // ������
   short          digits;         // ���-�� ������ ����� �������
   short          cmd;            // �������
   int            volume;         // �����

   time_t         open_time;	  // ����� ��������
   double         open_price;     // ���� ��������
   time_t         close_time;     // ����� ��������
   double         close_price;    // ���� ��������

   double         sl,tp;          // StopLoss TakeProfit

   double         commission;     // ��������
   double         agent_commission; // ��������� ��������, ��������� ������ ��� �������� �������
   double         storage;        // ����
   double         profit;         // ������
   char           comment[32];    // ����������
  };
struct TickInfo         // ��������� ����������
  {
   time_t ctm;          // �����
   char   symbol[8];    // ��� �����������
   double bid,ask;      // ���� bid/ask �����������!
  };
struct ConSession
  {
   short         open_hour,open_min;
   short         close_hour,close_min;
   short         open_hour2,open_min2;
   short         close_hour2,close_min2;
   short         open_hour3,open_min3;
   short         close_hour3,close_min3;
   int           open,close;           // ����������� �������� � �������
   int           open2,close2;         // ����������� �������� � �������
   int           open3,close3;         // ����������� �������� � �������
  };
struct ConSecurity
  {
   char         name[8];               // ��� 
   char         description[64];       // ��������
   char         source[8];             // ������� ��� ����� ���������
   char         secname[16];           // �������� ���� �����������
   int          type;                  // ��� �����������
   int          logging;               // ���� ��������� ������������
   int          indirect;              // �������� ������ ��������
   int          filter;                // �������� ���������� (���� ������ 1, ������ ��������)
   int          trade;                 // ���� � ������
   int          spread;                // �������� ������
   int          exemode;               // ����� �����������
   int          count;                 // !!! ��� ������, ���� count!
   int          realtime;              // ���� ������������� ������� ������
   int          swap_type;             // ��� �����
   double       slong,sshort;          // �������� �������� �����
   int          digits;                // ���-�� ����� ����� �������
   double       contract;              // �������� ���������
   int          margin_mode;           // ��� �������� �����
   double       initialmargin;         // �������� ����������
   double       maintenance;           // ������������ �������� ����������
   double       hedged;                // �������� ���������� �� ����������� ��������
   double       margin_divider;        // �������� �����
   double       point;                 // �������� ������ 1/pow(10,floats)
   double       multiply;              // �������� ������ pow(10,floats)
   int          stops;                 // �������� ������� ������
   double       tickvalue;             // ���� ������ ������ ��� ����
   double       tickvalue2;            // ��������� ����� ��� ����
   double       ticksize;              // ���� ������ ������
   time_t       starting;              // ����� ������ ������
   time_t       expiration;            // ����� ��������� ������
   ConSession   days[7];               // ���������� �� ������ �� �����
   int          unused[16];            // ���������������
   ConSecurity   *next;                // ������ �� ��������� ������
  };
struct MailBoxHeader
  {
   time_t time;                        // ����� ���������
   char   from[64];                    // �� ����
   int    to;                          // ����
   char   subject[128];                // ����
   int    readed;                      // ���� ���������
  };

//+------------------------------------------------------------------+
//| ����������� ������������� �������                                |
//+------------------------------------------------------------------+
typedef int          (*MtCreate_t)(void);
typedef int          (*MtDelete_t)(const int handle);
//---- connect/disconnect
typedef int          (*MtConnect_t)(const int handle,const char *server,const int port);
typedef int          (*MtDisconnect_t)(const int handle);
//---- �������� �� ������
typedef int          (*MtLogin_t)(const int handle,const int login,const char *password);
typedef int          (*MtOpenDemoAccount_t)(const int handle,DemoAccountInfo *info);
typedef int          (*MtChangePassword_t)(const int handle,const char *newpassword);
//---- ������������ ������
typedef RateInfo*    (*MtGetRates_t)(const int handle,const char *symbol,const int period,const time_t fromtime,int *count);
typedef TradeRecord* (*MtGetTradeHistory_t)(const int handle,const time_t from,const time_t to,int *items);
//---- �������� ��������
typedef int          (*MtGetPrices_t)(const int handle,const char *symbol,const int lots,double *bid,double *ask);
typedef int          (*MtSendOrder_t)(const int handle,const SendOrderInfo *soi);
typedef int          (*MtDeleteOrder_t)(const int handle,const int order);
typedef int          (*MtModifyOrder_t)(const int handle,const int order,const double price,const double sl,const double tp);
typedef int          (*MtCloseOrder_t)(const int handle,const int order,const double price,const int volume);
typedef int	         (*MtCloseByOrder_t)(const int handle,const int order,const int byorder);
typedef int          (*MtGetTrades_t)(const int handle);
typedef TradeRecord* (*MtGetTradeRecords_t)(const int handle,BriefUserInfo *bui,int *items);
//---- �������
typedef char*        (*MtGetNewsBody_t)(const int handle,const int key);
//---- 
typedef int          (*MtRefreshSecurities_t)(const int handle);
typedef ConSecurity* (*MtGetSecurities_t)(const int handle,int *items);
typedef int          (*MtAddSymbol_t)(const int handle,const char *symbol);
typedef int          (*MtHideSymbol_t)(const int handle,const char *symbol);
typedef int          (*MtSetPumpingMode_t)(const int handle,const HWND destwnd,const UINT eventmsg);
typedef TickInfo*    (*MtGetUpdatedTickInfo_t)(const int handle,int *items);
typedef NewsTopic*   (*MtGetLastNews_t)(const int handle,int *items);
typedef int          (*MtGetLastMail_t)(const int handle,char *path, int *lenofpath);
//---- 
typedef const char*  (*MtGetErrorDescription_t)(const int errorcode);
typedef int          (*MtSetWorkingDirectory_t)(const char *path);
//+------------------------------------------------------------------+
//| ������������ �������� �������                                    |
//+------------------------------------------------------------------+
enum { RET_OK,
       RET_OK_NONE,   // ��� ��
       RET_ERROR,            // ������ ������������ ������
       RET_INVALID_DATA,     // �������� ������
       RET_TECH_PROBLEM,     // ����������� �������� �� �������
       RET_ACCOUNT_DISABLED, // ���� ������������
       RET_BAD_ACCOUNT_INFO, 

       RET_TIMEOUT,          // ����� ���� �������� ���������� ������
       RET_BAD_PRICES,       // �������� ������ � ����� � ������
       RET_MARKET_CLOSED,    // ����� ������
       RET_TRADE_DISABLE,    // �������� ���������
       RET_NO_MONEY,         // ������������ ����� ��� ���������� ��������
       RET_PRICE_CHANGED,    // ���� ����������
       RET_OFFQUOTES,        // ��� ���
       RET_BROKER_BUSY,      // ������ �����

       RET_OLD_VERSION,      // ������ ������ ����������� ���������
       RET_MULTI_CONNECT,    // ������������� �������
       RET_NO_CONNECT,       // ��� ����������
       RET_NOT_ENOUGH_RIGHTS,// ��� ����
       RET_BAD_STOPS,        // �������� ������� ������ 
       RET_SKIPPED,          // �������� ��������� ��-�� ���� ��� ������� �����
       RET_TOO_FREQUENT,     // ������� ������ ���������
       RET_INVALID_VOLUME,   // ������������ �����
       RET_INVALID_HANDLE,   // �������� �����
     };
//+------------------------------------------------------------------+
//| ��������                                                         |
//+------------------------------------------------------------------+
enum { OP_BUY=0,
       OP_SELL,
	   OP_BUY_LIMIT,
	   OP_SELL_LIMIT,
	   OP_BUY_STOP,
	   OP_SELL_STOP,
	   OP_BALANCE,
	   OP_CREDIT 
     };
//+------------------------------------------------------------------+
//| �������                                                          |
//+------------------------------------------------------------------+
enum { PERIOD_M1=1,
       PERIOD_M5=5,
	   PERIOD_M15=15,
	   PERIOD_M30=30,
       PERIOD_H1=60,
	   PERIOD_H4=240,
	   PERIOD_D1=1440,
	   PERIOD_W1=10080
     };
//+------------------------------------------------------------------+
//| WPARAM �� pumping                                                |
//+------------------------------------------------------------------+
enum { 
	   UPDATE_BIDASK, 
	   UPDATE_NEWS, 
	   UPDATE_TRADES, 
	   UPDATE_MAIL, 
	   END_PUMPING 
     };
//+------------------------------------------------------------------+
//| ����� ������� � ������������ MetaTrader API ����� mtapi.dll      |
//| ��������� ���������� �������� �������� �������                   |
//+------------------------------------------------------------------+
class CMetaTraderAPI  
  {
protected:
   HINSTANCE               m_lib;
   int                     m_handle;
   //---- functions
   MtCreate_t              MtCreate;
   MtDelete_t              MtDelete;
   //---- connect/disconnect
   MtConnect_t             MtConnect;
   MtDisconnect_t          MtDisconnect;
   //---- �������� �� ������
   MtLogin_t               MtLogin;
   MtOpenDemoAccount_t     MtOpenDemoAccount;
   MtChangePassword_t      MtChangePassword;
   //---- ������������ ������
   MtGetRates_t            MtGetRates;
   MtGetTradeHistory_t     MtGetTradeHistory;
   //---- �������� ��������
   MtGetPrices_t           MtGetPrices;
   MtSendOrder_t           MtSendOrder;
   MtDeleteOrder_t         MtDeleteOrder;
   MtModifyOrder_t         MtModifyOrder;
   MtCloseOrder_t          MtCloseOrder;
   MtCloseByOrder_t        MtCloseByOrder;
   MtGetTrades_t           MtGetTrades;
   MtGetTradeRecords_t     MtGetTradeRecords;
   //---- �������
   MtGetNewsBody_t         MtGetNewsBody;
   //----
   MtRefreshSecurities_t   MtRefreshSecurities;
   MtGetSecurities_t       MtGetSecurities;
   MtAddSymbol_t           MtAddSymbol;
   MtHideSymbol_t          MtHideSymbol;
   MtSetPumpingMode_t      MtSetPumpingMode;
   MtGetUpdatedTickInfo_t  MtGetUpdatedTickInfo;
   MtGetLastNews_t         MtGetLastNews;
   MtGetLastMail_t         MtGetLastMail;
   //----
   MtGetErrorDescription_t MtGetErrorDescription;
   MtSetWorkingDirectory_t MtSetWorkingDirectory;

public:
                       CMetaTraderAPI(const char *path=NULL);
   virtual            ~CMetaTraderAPI();
   //----
   int                 WinsockStartup(WSADATA *wsa=NULL);
   void                WinsockCleanup(void);
   //---- connect/disconnect
   int                 Connect(const char *server,const int port=1950);
   int                 Disconnect(void);
   //---- �������� �� ������
   int                 Login(const int login,const char *password);
   int                 OpenDemoAccount(DemoAccountInfo *info);
   int                 ChangePassword(const char *newpassword);
   //---- ������������ ������
   RateInfo*           GetRates(const char *symbol,const int period,const time_t fromtime,int *count);
   TradeRecord*        GetTradeHistory(const time_t from,const time_t to,int *items);
   //---- �������� ��������
   int			       GetPrices(const char *symbol,const int lots,double *bid,double *ask);
   int                 SendOrder(const SendOrderInfo *soi);
   int                 DeleteOrder(const int order);
   int                 ModifyOrder(const int order,const double price,const double sl,const double tp);
   int                 CloseOrder(const int order,const double price,const int volume);
   int			       CloseByOrder(const int order,const int byorder);
   int                 GetTrades();
   TradeRecord*        GetTradeRecords(BriefUserInfo *bui,int *items);
   //---- �������
   char*               GetNewsBody(const int key);
   //----
   int                 RefreshSecurities();
   ConSecurity*        GetSecurities(int *items);
   int                 AddSymbol(const char * symbol);
   int                 HideSymbol(const char * symbol);
   int                 SetPumpingMode(const HWND destwnd,const UINT eventmsg);
   TickInfo*           GetUpdatedTickInfo(int *items);
   NewsTopic*          GetLastNews(int *items);
   int                 GetLastMail(char *path, int *lenofpath);
   //----
   const char*         GetErrorDescription(const int errorcode);
   int                 SetWorkingDirectory(const char* path);

protected:
   int                 Init(const char *filename);
   void                Terminate(void);
  };

#endif
//+------------------------------------------------------------------+
