//+------------------------------------------------------------------+
//|                                           MetaTrader API Example |
//|                      Copyright c 2003, MetaQuotes Software Corp. |
//|                                         http://www.metaquotes.ru |
//+------------------------------------------------------------------+
#include "stdafx.h"
#include "MetaTraderAPI.h"

//+------------------------------------------------------------------+
//| ����������� ������                                               |
//+------------------------------------------------------------------+
CMetaTraderAPI::CMetaTraderAPI(const char *path)
  {
   char tmp[256]="mtapi.dll";
//---- ��������� �������������
   m_handle=0;
   m_lib=NULL; 
   Terminate();  // ������� �������� �������
//---- �������������� ����������
   if(path!=NULL) sprintf(tmp,"%s\\mtapi.dll",path);
   Init(tmp);
//---- �������� ������
   if(MtCreate!=NULL) m_handle=MtCreate();
  }
//+------------------------------------------------------------------+
//| ����������                                                       |
//+------------------------------------------------------------------+
CMetaTraderAPI::~CMetaTraderAPI()
  {
   Terminate();
  }
//+------------------------------------------------------------------+
//| ������������� ����������                                         |
//+------------------------------------------------------------------+
int CMetaTraderAPI::Init(const char *filename)
  {
//---- ��������
   if(filename==NULL || m_lib!=NULL)       return(FALSE);
//---- ������� ��������� ����������
   if((m_lib=LoadLibrary(filename))==NULL) return(FALSE);
//---- ��������� ������� ���������� �������
   MtCreate             =reinterpret_cast<MtCreate_t>          (GetProcAddress(m_lib,"MtCreate"));
   MtDelete             =reinterpret_cast<MtDelete_t>          (GetProcAddress(m_lib,"MtDelete"));
   //----
   MtConnect            =reinterpret_cast<MtConnect_t>         (GetProcAddress(m_lib,"MtConnect"));
   MtDisconnect         =reinterpret_cast<MtDisconnect_t>      (GetProcAddress(m_lib,"MtDisconnect"));
   //----
   MtLogin              =reinterpret_cast<MtLogin_t>           (GetProcAddress(m_lib,"MtLogin"));
   MtOpenDemoAccount    =reinterpret_cast<MtOpenDemoAccount_t> (GetProcAddress(m_lib,"MtOpenDemoAccount"));
   MtChangePassword     =reinterpret_cast<MtChangePassword_t>  (GetProcAddress(m_lib,"MtChangePassword"));
   //----
   MtGetRates           =reinterpret_cast<MtGetRates_t>        (GetProcAddress(m_lib,"MtGetRates"));
   MtGetTradeHistory    =reinterpret_cast<MtGetTradeHistory_t> (GetProcAddress(m_lib,"MtGetTradeHistory"));
   //----
   MtGetPrices          =reinterpret_cast<MtGetPrices_t>       (GetProcAddress(m_lib,"MtGetPrices"));
   MtSendOrder          =reinterpret_cast<MtSendOrder_t>       (GetProcAddress(m_lib,"MtSendOrder"));
   MtDeleteOrder        =reinterpret_cast<MtDeleteOrder_t>     (GetProcAddress(m_lib,"MtDeleteOrder"));
   MtModifyOrder        =reinterpret_cast<MtModifyOrder_t>     (GetProcAddress(m_lib,"MtModifyOrder"));
   MtCloseOrder         =reinterpret_cast<MtCloseOrder_t>      (GetProcAddress(m_lib,"MtCloseOrder"));
   MtCloseByOrder       =reinterpret_cast<MtCloseByOrder_t>    (GetProcAddress(m_lib,"MtCloseByOrder"));
   MtGetTrades          =reinterpret_cast<MtGetTrades_t>       (GetProcAddress(m_lib,"MtGetTrades"));
   MtGetTradeRecords    =reinterpret_cast<MtGetTradeRecords_t> (GetProcAddress(m_lib,"MtGetTradeRecords"));
   //----
   MtGetNewsBody        =reinterpret_cast<MtGetNewsBody_t>     (GetProcAddress(m_lib,"MtGetNewsBody"));
   //----
   MtRefreshSecurities  =reinterpret_cast<MtRefreshSecurities_t> (GetProcAddress(m_lib,"MtRefreshSecurities"));
   MtGetSecurities      =reinterpret_cast<MtGetSecurities_t> (GetProcAddress(m_lib,"MtGetSecurities"));
   MtAddSymbol          =reinterpret_cast<MtAddSymbol_t> (GetProcAddress(m_lib,"MtAddSymbol"));
   MtHideSymbol         =reinterpret_cast<MtHideSymbol_t> (GetProcAddress(m_lib,"MtHideSymbol"));
   MtSetPumpingMode     =reinterpret_cast<MtSetPumpingMode_t> (GetProcAddress(m_lib,"MtSetPumpingMode"));
   MtGetUpdatedTickInfo =reinterpret_cast<MtGetUpdatedTickInfo_t> (GetProcAddress(m_lib,"MtGetUpdatedTickInfo"));
   MtGetLastNews        =reinterpret_cast<MtGetLastNews_t> (GetProcAddress(m_lib,"MtGetLastNews"));
   MtGetLastMail        =reinterpret_cast<MtGetLastMail_t> (GetProcAddress(m_lib,"MtGetLastMail"));
   //----
   MtGetErrorDescription=reinterpret_cast<MtGetErrorDescription_t> (GetProcAddress(m_lib,"MtGetErrorDescription"));
   MtSetWorkingDirectory=reinterpret_cast<MtSetWorkingDirectory_t> (GetProcAddress(m_lib,"MtSetWorkingDirectory"));
//---- �������� ������������
   if(MtCreate==NULL || MtDelete==NULL) { Terminate(); return(FALSE); }
//----
   return(TRUE);
  }
//+------------------------------------------------------------------+
//| �������� ���������� � ���������� �������� �������                |
//+------------------------------------------------------------------+
void CMetaTraderAPI::Terminate(void)
  {
//---- ������� ����������
   if(m_lib!=NULL) 
     {
      if(MtDelete!=NULL) MtDelete(m_handle); // ������� ������ ������
      FreeLibrary(m_lib); 
      m_lib=NULL; m_handle=0;
     }
//---- ������� ��� �������
   MtCreate             =NULL;
   MtDelete             =NULL;
   //----
   MtConnect            =NULL;
   MtDisconnect         =NULL;
   //----
   MtLogin              =NULL;
   MtOpenDemoAccount    =NULL;
   MtChangePassword     =NULL;
   //----
   MtGetRates           =NULL;
   MtGetTradeHistory    =NULL;
   //----
   MtGetPrices          =NULL;
   MtSendOrder          =NULL;
   MtDeleteOrder        =NULL;
   MtModifyOrder        =NULL;
   MtCloseOrder         =NULL;
   MtCloseByOrder       =NULL;
   MtGetTrades          =NULL;
   MtGetTradeRecords    =NULL;
   //----
   MtGetNewsBody        =NULL;
   //----
   MtRefreshSecurities  =NULL;
   MtGetSecurities      =NULL;
   MtAddSymbol          =NULL;
   MtHideSymbol         =NULL;
   MtSetPumpingMode     =NULL;
   MtGetUpdatedTickInfo =NULL;
   MtGetLastNews        =NULL;
   MtGetLastMail        =NULL;
   //----
   MtGetErrorDescription=NULL;
   MtSetWorkingDirectory=NULL;
//----
  }
//+------------------------------------------------------------------+
//| �������������� winsock (��������� �� ������ ������)              |
//+------------------------------------------------------------------+
int CMetaTraderAPI::WinsockStartup(WSADATA *wsa)
  {
   WSADATA lwsa;
//----
   if(wsa!=NULL)
     {
      if(WSAStartup(0x0101,wsa)!=0) return(RET_ERROR);
      return(RET_OK);
     }
//----
   if(WSAStartup(0x0101,&lwsa)!=0) return(RET_ERROR);
   return(RET_OK);
  }
//+------------------------------------------------------------------+
//| ������� winsock (��������� �� ������ ������)                     |
//+------------------------------------------------------------------+
void CMetaTraderAPI::WinsockCleanup(void) { WSACleanup(); }
//+------------------------------------------------------------------+
//| ����������� � �������                                            |
//+------------------------------------------------------------------+
int CMetaTraderAPI::Connect(const char *server,const int port)
  {
   if(MtConnect==NULL) return(RET_ERROR);
   return MtConnect(m_handle,server,port);
  }
//+------------------------------------------------------------------+
//| ����������� �� �������                                           |
//+------------------------------------------------------------------+
int CMetaTraderAPI::Disconnect(void)
  {
   if(MtDisconnect==NULL) return(RET_ERROR);
   return MtDisconnect(m_handle);
  }
//+------------------------------------------------------------------+
//| ����������� �� �������                                           |
//+------------------------------------------------------------------+
int CMetaTraderAPI::Login(const int login,const char *password)
  {
   if(MtLogin==NULL) return(RET_ERROR);
   return MtLogin(m_handle,login,password);
  }
//+------------------------------------------------------------------+
//| �������� ������������� ����                                      |.
//| ��� ������� ������������ ������ RET_OK � � ����� info->login     |
//| � info->password ����� ��������� ���������� �������              |
//+------------------------------------------------------------------+
int CMetaTraderAPI::OpenDemoAccount(DemoAccountInfo *info)
  {
   if(MtOpenDemoAccount==NULL) return(RET_ERROR);
   return MtOpenDemoAccount(m_handle,info);
  }
//+------------------------------------------------------------------+
//| ����� ������ � ������������                                      |
//+------------------------------------------------------------------+
int CMetaTraderAPI::ChangePassword(const char *newpassword)
  {
   if(MtChangePassword==NULL) return(RET_ERROR);
   return MtChangePassword(m_handle,newpassword);
  }
//+------------------------------------------------------------------+
//| �������� ������������ ��������� �� ������                        |
//+------------------------------------------------------------------+
RateInfo* CMetaTraderAPI::GetRates(const char *symbol,const int period,const time_t lasttime,int *count)
  {
   if(MtGetRates==NULL) return(*count=0,NULL);
   return MtGetRates(m_handle,symbol,period,lasttime,count);
  }
//+------------------------------------------------------------------+
//| �������� ������� �������� ����� �� ������                        |
//+------------------------------------------------------------------+
TradeRecord* CMetaTraderAPI::GetTradeHistory(const time_t from,const time_t to,int *items)
  {
   if(MtGetTradeHistory==NULL) return(*items=0,NULL);
   return MtGetTradeHistory(m_handle,from,to,items);
  }
//+------------------------------------------------------------------+
//| �������� ���� Bid � Ask                                          |
//+------------------------------------------------------------------+
int CMetaTraderAPI::GetPrices(const char *symbol,const int lots,double *bid,double *ask)
  {
   if(MtGetPrices==NULL) return(RET_ERROR);
   return MtGetPrices(m_handle,symbol,lots,bid,ask);
  }
//+------------------------------------------------------------------+
//| ������� order                                                    |
//+------------------------------------------------------------------+
int CMetaTraderAPI::SendOrder(const SendOrderInfo *soi)
  {
   if(MtSendOrder==NULL) return(RET_ERROR);
   return MtSendOrder(m_handle,soi);
  }
//+------------------------------------------------------------------+
//| ������� order                                                    |
//+------------------------------------------------------------------+
int CMetaTraderAPI::DeleteOrder(const int order)
  {
   if(MtDeleteOrder==NULL) return(RET_ERROR);
   return MtDeleteOrder(m_handle,order);
  }
//+------------------------------------------------------------------+
//| �������� order                                                   |
//+------------------------------------------------------------------+
int CMetaTraderAPI::ModifyOrder(const int order,const double price,const double sl,const double tp)
  {
   if(MtModifyOrder==NULL) return(RET_ERROR);
   return MtModifyOrder(m_handle,order,price,sl,tp);
  }
//+------------------------------------------------------------------+
//| ������� �������                                                  |
//+------------------------------------------------------------------+
int CMetaTraderAPI::CloseOrder(const int order,const double price,const int volume)
  {
   if(MtCloseOrder==NULL) return(RET_ERROR);
   return MtCloseOrder(m_handle,order,price,volume);
  }
//+------------------------------------------------------------------+
//| ������� ������� ��� ������ ������ �������                        |
//+------------------------------------------------------------------+
int	CMetaTraderAPI::CloseByOrder(const int order,const int byorder)
  {
   if(MtCloseByOrder==NULL) return(RET_ERROR);
   return MtCloseByOrder(m_handle,order,byorder);
  }
//+------------------------------------------------------------------+
//| �������� ������ ������� �������� ������� � �������               |
//+------------------------------------------------------------------+
int CMetaTraderAPI::GetTrades()
  {
   if(MtGetTrades==NULL) return(RET_ERROR);
   return MtGetTrades(m_handle);
  }
//+------------------------------------------------------------------+
//| �������� ����� ������� �������� �������                          |
//+------------------------------------------------------------------+
TradeRecord* CMetaTraderAPI::GetTradeRecords(BriefUserInfo *bui,int *items)
  {
   if(MtGetTradeRecords==NULL) return(*items=0,NULL);
   return MtGetTradeRecords(m_handle,bui,items);
  }
//+------------------------------------------------------------------+
//| �������� ���� �������                                            |
//+------------------------------------------------------------------+
char* CMetaTraderAPI::GetNewsBody(const int key)
  {
   if(MtGetNewsBody==NULL) return(NULL);
   return MtGetNewsBody(m_handle,key);
  }
//+------------------------------------------------------------------+
//| �������� ������ ��������� ������������                           |
//+------------------------------------------------------------------+
int CMetaTraderAPI::RefreshSecurities()
  {
   if(MtRefreshSecurities==NULL) return(RET_ERROR);
   return MtRefreshSecurities(m_handle);
  }
//+------------------------------------------------------------------+
//| �������� ������ ��������� ������������                           |
//+------------------------------------------------------------------+
ConSecurity* CMetaTraderAPI::GetSecurities(int *items)
  {
   if(MtGetSecurities==NULL) return(*items=0,NULL);
   return MtGetSecurities(m_handle,items);
  }
//+------------------------------------------------------------------+
//| �������� ������                                                  |
//+------------------------------------------------------------------+
int CMetaTraderAPI::AddSymbol(const char * symbol)
  {
   if(MtAddSymbol==NULL) return(RET_ERROR);
   return MtAddSymbol(m_handle,symbol);
  }
//+------------------------------------------------------------------+
//| ������ ������                                                    |
//+------------------------------------------------------------------+
int CMetaTraderAPI::HideSymbol(const char * symbol)
  {
   if(MtHideSymbol==NULL) return(RET_ERROR);
   return MtHideSymbol(m_handle,symbol);
  }
//+------------------------------------------------------------------+
//| ���������� pumping ���� � ���������                              |
//+------------------------------------------------------------------+
int CMetaTraderAPI::SetPumpingMode(const HWND destwnd,const UINT eventmsg)
  {
   if(MtSetPumpingMode==NULL) return(RET_ERROR);
   return MtSetPumpingMode(m_handle,destwnd,eventmsg);
  }
//+------------------------------------------------------------------+
//| �������� ���                                                     |
//+------------------------------------------------------------------+
TickInfo* CMetaTraderAPI::GetUpdatedTickInfo(int *items)
  {
   if(MtGetUpdatedTickInfo==NULL) return(*items=0,NULL);
   return MtGetUpdatedTickInfo(m_handle,items);
  }
//+------------------------------------------------------------------+
//| �������� ��������� �������                                       |
//+------------------------------------------------------------------+
NewsTopic* CMetaTraderAPI::GetLastNews(int *items)
  {
   if(MtGetLastNews==NULL) return(*items=0,NULL);
   return MtGetLastNews(m_handle,items);
  }
//+------------------------------------------------------------------+
//| �������� ��������� ������                                        |
//+------------------------------------------------------------------+
int CMetaTraderAPI::GetLastMail(char *path, int *lenofpath)
  {
   if(MtGetLastMail==NULL) return(RET_ERROR);
   return MtGetLastMail(m_handle,path,lenofpath);
  }
//+------------------------------------------------------------------+
//| �������� �������� ������                                         |
//+------------------------------------------------------------------+
const char* CMetaTraderAPI::GetErrorDescription(const int errorcode)
  {
   if(MtGetErrorDescription==NULL) return(NULL);
   return MtGetErrorDescription(errorcode);
  }
//+------------------------------------------------------------------+
//| ���������� ������� ����������                                    |
//+------------------------------------------------------------------+
int CMetaTraderAPI::SetWorkingDirectory(const char* path)
  {
   if(MtSetWorkingDirectory==NULL) return(RET_ERROR);
   return MtSetWorkingDirectory(path);
  }
