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
   int            login;          // числовой логин клиента
   char           password[16];   // кеш от пароля
   char           phonepassword[16];
   char           name[64];       // имя
   char           group[16];      // группа
   char           country[32];    // страна
   char           city[32];       // город
   char           state[32];      // штат
   char           zipcode[16];    // индекс
   char           address[32];    // адрес
   char           phone[32];      // телефон
   char           email[32];      // емайл
   char           unused[72];
   int            leverage;       // плечо
   double         balance;        // баланс
   char           reserved[20];
  };
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
#pragma pack(1)
struct RateInfo
  {
   time_t         ctm;            // текущее время в секундах
   double         open;           // цена открытия
   double         low;            // цена low
   double         high;           // цена high
   double         close;          // цена закрытия
   int            vol;            // объем
  };
struct NewsTopic
  {
   char  ctm[20];                 // время в формате "yyyy/mm/dd hh:mm:ss"
   char  topic[256];              // заголовок
   char  keywords[256];           // ключевые слова
   int   len;                     // длина сообщения
   char *body;                    // тело сообщения (если есть)
   int   key;                     // код новости родной
   int   newkey;                  // код новости новый
  };
struct BriefUserInfo
  {
   int            login;          // логин
   int            isdemo;         // демо?
   char           name[64];       // имя
   char           company[64];    // компания
   double         balance;        // баланс
   double         equity;         // 
   double         credit;         // кредит
   double         margin;         // маржа
   double         freemargin;     // свободная маржа
   double         profit;         // прибыль
   int            marginmode;     // 
   int            margincall;     // уровень маржинкола
   char           margintype;     // тип маржинкола 0-%,1-$
   int            allow_flags;    // флаги разрешений
   int            leverage;
  };
struct SendOrderInfo              // Объединенная команда посылки ордера
  {
   char   req_code;               // код команды в протоколе
   int    order;                  // ордер
   char   symbol[8];              // инструмент
   int    volume;                 // объем
   char   cmd;                    // команда OP_BUY....OP_SELL_STOP
   double price;                  // цена исполнения
   double sl,tp;                  // стопы
   int    crc;                    // контрольная сумма
  };
#pragma pack(8)
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
struct TradeRecord
  {
   int            order;          // номер ордера
   int            login;          // кому принадлежит
   char           symbol[8];      // символ
   short          digits;         // кол-во знаков после запятой
   short          cmd;            // команда
   int            volume;         // объем

   time_t         open_time;	  // время открытия
   double         open_price;     // цена открытия
   time_t         close_time;     // время закрытия
   double         close_price;    // цена закрытия

   double         sl,tp;          // StopLoss TakeProfit

   double         commission;     // комиссия
   double         agent_commission; // агентская комиссия, финальный расчет при закрытии позиции
   double         storage;        // своп
   double         profit;         // профит
   char           comment[32];    // коментарий
  };
struct TickInfo         // котировка нормальная
  {
   time_t ctm;          // время
   char   symbol[8];    // имя инструмента
   double bid,ask;      // цена bid/ask выровненные!
  };
struct ConSession
  {
   short         open_hour,open_min;
   short         close_hour,close_min;
   short         open_hour2,open_min2;
   short         close_hour2,close_min2;
   short         open_hour3,open_min3;
   short         close_hour3,close_min3;
   int           open,close;           // расчитанные значения в минутах
   int           open2,close2;         // расчитанные значения в минутах
   int           open3,close3;         // расчитанные значения в минутах
  };
struct ConSecurity
  {
   char         name[8];               // имя 
   char         description[64];       // описание
   char         source[8];             // синоним для сбора котировок
   char         secname[16];           // название типа инструмента
   int          type;                  // тип инструмента
   int          logging;               // флаг включения логгирования
   int          indirect;              // обратный расчет прибылей
   int          filter;                // значение фильтрации (если меньше 1, фильтр выключен)
   int          trade;                 // флаг в торгах
   int          spread;                // величина спреда
   int          exemode;               // режим котирования
   int          count;                 // !!! был баланс, стал count!
   int          realtime;              // флаг использования рилтайм фидера
   int          swap_type;             // тип свопа
   double       slong,sshort;          // величина овернайт свопа
   int          digits;                // кол-во точек после запятой
   double       contract;              // величина контракта
   int          margin_mode;           // тип расчетов маржи
   double       initialmargin;         // маржевые требования
   double       maintenance;           // обязательные маржевые требования
   double       hedged;                // маржевые требования на хеджируемых позициях
   double       margin_divider;        // делитель маржи
   double       point;                 // величина пункта 1/pow(10,floats)
   double       multiply;              // величина пункта pow(10,floats)
   int          stops;                 // величина отступа стопов
   double       tickvalue;             // цена одного пункта для бида
   double       tickvalue2;            // стоимость пипса для аска
   double       ticksize;              // цена одного пункта
   time_t       starting;              // время начала торгов
   time_t       expiration;            // время истечения торгов
   ConSession   days[7];               // разрешение на доступ по часам
   int          unused[16];            // зарезервировано
   ConSecurity   *next;                // ссылка на следующий объект
  };
struct MailBoxHeader
  {
   time_t time;                        // время получения
   char   from[64];                    // от кого
   int    to;                          // кому
   char   subject[128];                // тема
   int    readed;                      // флаг прочтения
  };

//+------------------------------------------------------------------+
//| Определение импортируемых функций                                |
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
//| Возвращаемые значения функций                                    |
//+------------------------------------------------------------------+
enum { RET_OK,
       RET_OK_NONE,   // все ок
       RET_ERROR,            // просто неопознанные ошибки
       RET_INVALID_DATA,     // неверные данные
       RET_TECH_PROBLEM,     // технические проблемы на сервере
       RET_ACCOUNT_DISABLED, // счет заблокирован
       RET_BAD_ACCOUNT_INFO, 

       RET_TIMEOUT,          // истек срок ожидания совершения сделки
       RET_BAD_PRICES,       // неверные данные о ценах в ордере
       RET_MARKET_CLOSED,    // рынок закрыт
       RET_TRADE_DISABLE,    // торговля запрещена
       RET_NO_MONEY,         // недостаточно денег для совершения операции
       RET_PRICE_CHANGED,    // цены изменились
       RET_OFFQUOTES,        // нет цен
       RET_BROKER_BUSY,      // брокер занят

       RET_OLD_VERSION,      // старая версия клиентского терминала
       RET_MULTI_CONNECT,    // множественный коннект
       RET_NO_CONNECT,       // нет соединения
       RET_NOT_ENOUGH_RIGHTS,// нет прав
       RET_BAD_STOPS,        // неверный уровень стопов 
       RET_SKIPPED,          // операция пропущена из-за того что процесс занят
       RET_TOO_FREQUENT,     // слишком частые обращения
       RET_INVALID_VOLUME,   // неподходящий объем
       RET_INVALID_HANDLE,   // неверный хендл
     };
//+------------------------------------------------------------------+
//| Операции                                                         |
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
//| Периоды                                                          |
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
//| WPARAM от pumping                                                |
//+------------------------------------------------------------------+
enum { 
	   UPDATE_BIDASK, 
	   UPDATE_NEWS, 
	   UPDATE_TRADES, 
	   UPDATE_MAIL, 
	   END_PUMPING 
     };
//+------------------------------------------------------------------+
//| Класс доступа к возможностям MetaTrader API через mtapi.dll      |
//| Полностью скрывается механизм привязки функций                   |
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
