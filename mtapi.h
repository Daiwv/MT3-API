//+------------------------------------------------------------------+
//|                                                   MetaTrader API |
//|                      Copyright © 2003, MetaQuotes Software Corp. |
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
   int    volume;                 // объем (количество лотов, умноженное на 100)
   char   cmd;                    // команда OP_BUY....OP_SELL_STOP
   double price;                  // цена исполнения
   double sl;                     // StopLoss
   double tp;                     // TakeProfit
   int    crc;                    // контрольная сумма
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
struct TradeRecord
  {
   int            order;          // номер ордера
   int            login;          // кому принадлежит
   char           symbol[8];      // символ
   short          digits;         // кол-во знаков после запятой
   short          cmd;            // команда
   int            volume;         // объем (количество лотов, умноженное на 100)

   time_t         open_time;	  // время открытия
   double         open_price;     // цена открытия
   time_t         close_time;     // время закрытия
   double         close_price;    // цена закрытия

   double         sl;             // StopLoss
   double         tp;             // TakeProfit

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
   double bid;          // цена bid
   double ask;          // цена ask
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
//| Возвращаемые значения функций                                    |
//+------------------------------------------------------------------+
enum { RET_OK,
       RET_OK_NONE,          // все ок
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
       RET_INSTANTEXECUTION  // инструмент в режиме IE
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
//| режим котирования инструмента (по запросу либо instant execution)|
//+------------------------------------------------------------------+
enum { EXE_REQUEST, EXE_MARKET };

//+------------------------------------------------------------------+
//| Определение импортируемых функций                                |
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
