//+------------------------------------------------------------------+
//|                                                   MetaTrader API |
//|                      Copyright � 2003, MetaQuotes Software Corp. |
//|                                         http://www.metaquotes.ru |
//+------------------------------------------------------------------+

#ifndef MTAPI_HEADER
#define MTAPI_HEADER
#include <time.h>

#define MT_API __declspec(dllimport)

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
   int    volume;                 // ����� (���������� �����, ���������� �� 100)
   char   cmd;                    // ������� OP_BUY....OP_SELL_STOP
   double price;                  // ���� ����������
   double sl;                     // StopLoss
   double tp;                     // TakeProfit
   int    crc;                    // ����������� �����
  };
#pragma pack(8)

struct StockBriefInfo      // information from MarketWatch (only in Pumping Mode!!!)
  {
   char   name[8];         // symbol
   int    digits;          // 
   short  count;           // 
   int    direction;       // 
   int    updateflag;      // 
   time_t ctm;             // last time
   double bid,ask;         // bid/ask
   double high,low;        // high/low
   //----
   int    spread;          // 
  };

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
struct TradeRecord
  {
   int            order;          // ����� ������
   int            login;          // ���� �����������
   char           symbol[8];      // ������
   short          digits;         // ���-�� ������ ����� �������
   short          cmd;            // �������
   int            volume;         // ����� (���������� �����, ���������� �� 100)

   time_t         open_time;	  // ����� ��������
   double         open_price;     // ���� ��������
   time_t         close_time;     // ����� ��������
   double         close_price;    // ���� ��������

   double         sl;             // StopLoss
   double         tp;             // TakeProfit

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
   double bid;          // ���� bid
   double ask;          // ���� ask
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
//| ������������ �������� �������                                    |
//+------------------------------------------------------------------+
enum { RET_OK,
       RET_OK_NONE,          // ��� ��
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
       RET_INSTANTEXECUTION  // ���������� � ������ IE
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
//| ����� ����������� ����������� (�� ������� ���� instant execution)|
//+------------------------------------------------------------------+
enum { EXE_REQUEST, EXE_MARKET };

//+------------------------------------------------------------------+
//| ����������� ������������� �������                                |
//+------------------------------------------------------------------+
MT_API int          MtGetVersion(void);
MT_API int          MtSetWorkingDirectory( const char * path );
MT_API int          MtCreate(void);
MT_API int          MtDelete(const int handle);
MT_API int          MtConnect(const int handle,const char *server,const int port);
MT_API int          MtDisconnect(const int handle);
MT_API int          MtLogin(const int handle,const int login,const char *password);
MT_API int          MtOpenDemoAccount(const int handle,DemoAccountInfo *info);
MT_API int          MtChangePassword(const int handle,char *newpass);
MT_API RateInfo*    MtGetRates(const int handle,char *symbol,int period,time_t lasttime,int *counter);
MT_API int          MtGetTrades(const int handle);
MT_API TradeRecord* MtGetTradeRecords(const int handle,BriefUserInfo *bui,int *items);
MT_API TradeRecord* MtGetTradeHistory(const int handle,time_t from,time_t to,int *items);
MT_API char*        MtGetNewsBody(const int handle,int key);
MT_API int          MtGetPrices(const int handle,char *symbol,int lots,double *bid,double *ask);
MT_API int          MtSendOrder(const int handle,SendOrderInfo *soi);
MT_API int          MtDeleteOrder(const int handle,int order);
MT_API int          MtModifyOrder(const int handle,int order,double price,double sl,double tp);
MT_API int          MtCloseOrder(const int handle,int order,double price,int volume);
MT_API int          MtCloseByOrder(const int handle,int order,int byorder);
MT_API int          MtRefreshSecurities(const int handle);
MT_API ConSecurity* MtGetSecurities(const int handle,int *items);
MT_API int          MtAddSymbol(const int handle,const char *symbol);
MT_API int          MtHideSymbol(const int handle,const char *symbol);
MT_API int          MtGetSymbol(const int handle,StockBriefInfo *sbi);
MT_API int          MtSetPumpingMode(const int handle,const HWND destwnd,const UINT eventmsg);
MT_API TickInfo*    MtGetUpdatedTickInfo(const int handle,int *items);
MT_API NewsTopic*   MtGetLastNews(const int handle,int *items);
MT_API int          MtGetLastMail(const int handle,char *path,int *lenofpath);
MT_API const char*  MtGetErrorDescription(const int errorcode);

#endif
//+------------------------------------------------------------------+
