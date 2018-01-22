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
#include "mtapi.h"

//+------------------------------------------------------------------+
//| ќпределение импортируемых функций                                |
//+------------------------------------------------------------------+
typedef int          (*MtCreate_t)(void);
typedef int          (*MtDelete_t)(const int handle);
//---- connect/disconnect
typedef int          (*MtConnect_t)(const int handle,const char *server,const int port);
typedef int          (*MtDisconnect_t)(const int handle);
//---- операции со счетом
typedef int          (*MtLogin_t)(const int handle,const int login,const char *password);
typedef int          (*MtOpenDemoAccount_t)(const int handle,DemoAccountInfo *info);
typedef int          (*MtChangePassword_t)(const int handle,const char *newpassword);
//---- исторические данные
typedef RateInfo*    (*MtGetRates_t)(const int handle,const char *symbol,const int period,const time_t fromtime,int *count);
typedef TradeRecord* (*MtGetTradeHistory_t)(const int handle,const time_t from,const time_t to,int *items);
//---- торговые операции
typedef int          (*MtGetPrices_t)(const int handle,const char *symbol,const int lots,double *bid,double *ask);
typedef int          (*MtSendOrder_t)(const int handle,const SendOrderInfo *soi);
typedef int          (*MtDeleteOrder_t)(const int handle,const int order);
typedef int          (*MtModifyOrder_t)(const int handle,const int order,const double price,const double sl,const double tp);
typedef int          (*MtCloseOrder_t)(const int handle,const int order,const double price,const int volume);
typedef int	         (*MtCloseByOrder_t)(const int handle,const int order,const int byorder);
typedef int          (*MtGetTrades_t)(const int handle);
typedef TradeRecord* (*MtGetTradeRecords_t)(const int handle,BriefUserInfo *bui,int *items);
//---- новости
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
//|  ласс доступа к возможност€м MetaTrader API через mtapi.dll      |
//| ѕолностью скрываетс€ механизм прив€зки функций                   |
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
   //---- операции со счетом
   MtLogin_t               MtLogin;
   MtOpenDemoAccount_t     MtOpenDemoAccount;
   MtChangePassword_t      MtChangePassword;
   //---- исторические данные
   MtGetRates_t            MtGetRates;
   MtGetTradeHistory_t     MtGetTradeHistory;
   //---- торговые операции
   MtGetPrices_t           MtGetPrices;
   MtSendOrder_t           MtSendOrder;
   MtDeleteOrder_t         MtDeleteOrder;
   MtModifyOrder_t         MtModifyOrder;
   MtCloseOrder_t          MtCloseOrder;
   MtCloseByOrder_t        MtCloseByOrder;
   MtGetTrades_t           MtGetTrades;
   MtGetTradeRecords_t     MtGetTradeRecords;
   //---- новости
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
   //---- операции со счетом
   int                 Login(const int login,const char *password);
   int                 OpenDemoAccount(DemoAccountInfo *info);
   int                 ChangePassword(const char *newpassword);
   //---- исторические данные
   RateInfo*           GetRates(const char *symbol,const int period,const time_t fromtime,int *count);
   TradeRecord*        GetTradeHistory(const time_t from,const time_t to,int *items);
   //---- торговые операции
   int			       GetPrices(const char *symbol,const int lots,double *bid,double *ask);
   int                 SendOrder(const SendOrderInfo *soi);
   int                 DeleteOrder(const int order);
   int                 ModifyOrder(const int order,const double price,const double sl,const double tp);
   int                 CloseOrder(const int order,const double price,const int volume);
   int			       CloseByOrder(const int order,const int byorder);
   int                 GetTrades();
   TradeRecord*        GetTradeRecords(BriefUserInfo *bui,int *items);
   //---- новости
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
