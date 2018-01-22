//+------------------------------------------------------------------+
//|                                           MetaTrader API Example |
//|                      Copyright c 2003, MetaQuotes Software Corp. |
//|                                         http://www.metaquotes.ru |
//+------------------------------------------------------------------+
#include "stdafx.h"
#include "../metatraderapi.h"

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
int main(int argc, char* argv[])
  {
//---- heap процесса, необходим для освобождения буферов цен,
//---- открытых позиций и истории операций счета
   HANDLE hHeap=::GetProcessHeap();
//----
   int err;
   int i;
   printf("MetaTrader API example!\n");

//----
   CMetaTraderAPI api;

//---- инициализируем winsock
   api.WinsockStartup();

//---- подключаемся к серверу
   if((err=api.Connect("192.168.0.15",1950))!=RET_OK)
     {
      printf("Error connecting to server: %s\n",api.GetErrorDescription(err));
      return(-1);
     }
   printf("1. connected to server\n");

//---- выделим себе демо-счет
//---- необходимо запонить все значимые поля структуры DemoAccountInfo
   DemoAccountInfo acc;
   memset(&acc,0,sizeof(acc));
   strcpy(acc.name,"John Smith");
   strcpy(acc.email,"john@smith.com");
   strcpy(acc.address,"some address");
   strcpy(acc.city,"Moscow");
   strcpy(acc.country,"Russia");
   strcpy(acc.state,"none");
   strcpy(acc.phone,"777777777");
   strcpy(acc.zipcode,"123456");
   strcpy(acc.group, "demoforex");
   acc.balance=5000;
   acc.leverage=100;
   if((err=api.OpenDemoAccount(&acc))!=RET_OK)
     {
      printf("Error allocating demo account: %s\n",api.GetErrorDescription(err));
      return(-1);
     }

   //---- специально закроем соединение
   api.Disconnect(); 
   printf("2. demo account %d:%s (connection is closed)\n",acc.login,acc.password);

//---- подключимся под новым аккаунтом
   if((err=api.Connect("192.168.0.15",1950))!=RET_OK)
     {
      printf("Error connecting to server: %s\n",api.GetErrorDescription(err));
      return(-1);
     }
   printf("3. connected to server\n");
   if((err=api.Login(acc.login,acc.password))!=RET_OK)
     {
      printf("Error logging as '%d': %s\n",acc.login,api.GetErrorDescription(err));
      return(-1);
     }
   printf("4. login as '%d'\n",acc.login);

//---- сменим пароль на другой
   if((err=api.ChangePassword("mynewpassword"))!=RET_OK)
     {
      printf("Error changing the password: %s\n",api.GetErrorDescription(err));
      return(-1);
     }
   printf("5. password changed to 'mynewpassword'\n");

//---- получим котировки за последние 2 дня
   int count=0;
   RateInfo* pri=api.GetRates("USDCHF",PERIOD_H1,time(NULL)-172800,&count);
   printf("6. got rates for USDCHF H1: %d pieces\n", count);
   for(i=0;i<count;i++)
	 {
      tm* tt=gmtime(&pri[i].ctm);
      printf("\t%04d.%02d.%02d %02d:%02d",1900+tt->tm_year,tt->tm_mon+1,tt->tm_mday,tt->tm_hour,tt->tm_min);
      printf("\t%.4f\t%.4f\t%.4f\t%.4f\t%d\n",pri[i].open,pri[i].high,pri[i].low,pri[i].close,pri[i].vol);
	 }
   
   //---- буфер цен необходимо освободить
   //---- при помощи функции HeapFree
   if(pri!=NULL) ::HeapFree(hHeap,0,pri);

//---- получим цены
   double bid,ask;
   if((err=api.GetPrices("USDCHF",100,&bid,&ask))!=RET_OK)
     {
      printf("Error getting prices: %s\n",api.GetErrorDescription(err));
      return(-1);
     }
   printf("7. got prices for USDCHF\n");
   printf("\tbid: %.4f\task: %.4f\n",bid,ask);

//---- откроем позицию, перед тем как отослать ордер должны быть запрошены цены
   SendOrderInfo soi;
   ::ZeroMemory(&soi,sizeof(soi));
   strcpy(soi.symbol,"USDCHF");
   soi.cmd=OP_BUY;
   soi.volume=100;
   soi.price=ask;
   if((err=api.SendOrder(&soi))!=RET_OK)
     {
      printf("Error sending order: %s\n",api.GetErrorDescription(err));
      return(-1);
     }
   printf("8. long position opened\n");

//---- изменим StopLoss, TakeProfit = 50 пунктов

   //---- получим список открытых позиций
   if((err=api.GetTrades())!=RET_OK)
     {
      printf("Error getting trades: %s\n",api.GetErrorDescription(err));
      return(-1);
     }
   BriefUserInfo bui;
   int items=0;
   TradeRecord* ptr = api.GetTradeRecords(&bui,&items);
   if(items<1)
     {
      printf("Error getting trades...\n");
      return(-1);
     }

   //---- изменяем первую позицию
   ::ZeroMemory(&soi,sizeof(soi));
   soi.order=ptr[0].order;
   strcpy(soi.symbol,ptr[0].symbol);
   soi.volume=ptr[0].volume;
   soi.price=ptr[0].open_price;

   //---- буфер открытых позиций необходимо освободить
   //---- при помощи функции HeapFree
   ::HeapFree(hHeap,0,ptr);

   //---- изменим ордер
   ::Sleep(5000);
   if((err=api.ModifyOrder(soi.order,soi.price,ask-0.0050,ask+0.0050))!=RET_OK)
     {
      printf("Error modifying order: %s\n",api.GetErrorDescription(err));
      return(-1);
     }
   printf("9. order %d modified\n",soi.order);
   
//---- закроем позицию

   //---- перед закрытием позиции необходимо запросить цены
   if((err=api.GetPrices(soi.symbol,soi.volume,&bid,&ask))!=RET_OK)
     {
      printf("Error getting prices: %s\n",api.GetErrorDescription(err));
      return(-1);
     }

   //---- закроем позицию
   ::Sleep(5000);
   if((err=api.CloseOrder(soi.order,bid,soi.volume))!=RET_OK)
     {
      printf("Error closing order: %s\n",api.GetErrorDescription(err));
      return(-1);
     }
   printf("10. order %d closed\n",soi.order);

//---- откроем отложенный ордер
   ::ZeroMemory(&soi,sizeof(soi));
   strcpy(soi.symbol,"GBPUSD");
   soi.cmd=OP_SELL_LIMIT;
   soi.volume=100;
   soi.price=1.9870;
   soi.sl=1.9920;
   soi.tp=1.9700;
   ::Sleep(5000);
   if((err=api.SendOrder(&soi))!=RET_OK)
     {
      printf("Error sending order: %s\n",api.GetErrorDescription(err));
      return(-1);
     }
   printf("11. pending order sent\n");

//---- удалим отложенный ордер

   //---- получим список открытых позиций
   if((err=api.GetTrades())!=RET_OK)
     {
      printf("Error getting trades: %s\n",api.GetErrorDescription(err));
      return(-1);
     }
   ptr = api.GetTradeRecords(&bui,&items);
   if(items<1)
     {
      printf("Error getting trades...\n");
      return(-1);
     }

   //---- удаляем первую позицию
   soi.order=ptr[0].order;

   //---- буфер открытых позиций необходимо освободить
   //---- при помощи функции HeapFree
   ::HeapFree(hHeap,0,ptr);

   //---- удалим ордер
   ::Sleep(5000);
   if((err=api.DeleteOrder(soi.order))!=RET_OK)
     {
      printf("Error deleting order: %s\n",api.GetErrorDescription(err));
      return(-1);
     }
   printf("12. order %d deleted\n",soi.order);

//---- откроем две позиции и закроем их

   //---- открываем первую позицию
   ::Sleep(5000);
   ::ZeroMemory(&soi,sizeof(soi));
   strcpy(soi.symbol,"USDCHF");
   soi.cmd=OP_BUY;
   soi.volume=100;

   //---- запросим цены
   if((err=api.GetPrices(soi.symbol,soi.volume,&bid,&ask))!=RET_OK)
     {
      printf("Error getting prices: %s\n",api.GetErrorDescription(err));
      return(-1);
     }

   //---- отправим ордер
   soi.price=ask;
   if((err=api.SendOrder(&soi))!=RET_OK)
     {
      printf("Error sending order: %s\n",api.GetErrorDescription(err));
      return(-1);
     }

   //---- открываем вторую позицию
   ::Sleep(5000);
   SendOrderInfo soi2;
   ::ZeroMemory(&soi2,sizeof(soi2));
   strcpy(soi2.symbol,"USDCHF");
   soi2.cmd=OP_SELL;
   soi2.volume=100;

   //---- запросим цены
   if((err=api.GetPrices(soi2.symbol,soi2.volume,&bid,&ask))!=RET_OK)
     {
      printf("Error getting prices: %s\n",api.GetErrorDescription(err));
      return(-1);
     }

   //---- отправим ордер
   soi2.price=bid;
   if((err=api.SendOrder(&soi2))!=RET_OK)
     {
      printf("Error sending order: %s\n",api.GetErrorDescription(err));
      return(-1);
     }

   //---- получим список открытых позиций
   if((err=api.GetTrades())!=RET_OK)
     {
      printf("Error getting trades: %s\n",api.GetErrorDescription(err));
      return(-1);
     }
   ptr = api.GetTradeRecords(&bui,&items);
   if(items<1)
     {
      printf("Error getting trades...\n");
      return(-1);
     }
   soi.order=ptr[0].order;
   soi2.order=ptr[1].order;

   //---- буфер открытых позиций необходимо освободить
   //---- при помощи функции HeapFree
   ::HeapFree(hHeap,0,ptr);

   //---- закрываем
   ::Sleep(5000);
   if((err=api.CloseByOrder(soi.order,soi2.order))!=RET_OK)
     {
      printf("Error closing order by order: %s\n",api.GetErrorDescription(err));
      return(-1);
     }
   printf("13. order %d closed by order %d\n",soi.order,soi2.order);

//---- запросим историю операций счета
   ptr=api.GetTradeHistory(0,time(NULL),&items);
   printf("14. got trade history, trades: %d\n",items);
   for(i=0;i<items;i++)
	 {
	  printf("\t%d\n\t",ptr[i].order);
	  printf("\t%d\t%s",ptr[i].login,ptr[i].symbol);
	  char* scmd[] = { "buy", "sell", "buy limit", "sell limit", "buy stop", "sell stop", "balance", "credit" };
	  printf("\t%s\t%.2lf\n\t",scmd[ptr[i].cmd],ptr[i].volume/100.0);
      tm* tt=gmtime(&ptr[i].open_time);
      printf("\t%04d.%02d.%02d %02d:%02d",1900+tt->tm_year,tt->tm_mon+1,tt->tm_mday,tt->tm_hour,tt->tm_min);
	  printf("\t%.4f",ptr[i].open_price);
      tt=gmtime(&ptr[i].close_time);
      printf("\t%04d.%02d.%02d %02d:%02d",1900+tt->tm_year,tt->tm_mon+1,tt->tm_mday,tt->tm_hour,tt->tm_min);
	  printf("\t%.4f\n\t",ptr[i].close_price);
	  printf("\t%.4f\t%.4f\n\t",ptr[i].sl,ptr[i].tp);
	  printf("\t%.2f\t%.2f",ptr[i].commission,ptr[i].agent_commission);
	  printf("\t%.2f\t%.2f\t%s\n",ptr[i].storage,ptr[i].profit,ptr[i].comment);
	 }

   //---- буфер истории операций счета необходимо освободить
   //---- при помощи функции HeapFree
   if(ptr!=NULL) ::HeapFree(hHeap,0,ptr);

//---- обновим список доступных инструментов
   if((err=api.RefreshSecurities())>RET_OK_NONE)
     {
      printf("Error refreshing securities\n");
      return(-1);
     }
   printf("15. securities refreshed\n");

//---- получим список доступных инструментов
   ::Sleep(5000);
   ConSecurity* psec = api.GetSecurities(&items);
   printf("16. got securities: %d\n",items);
   for(i=0;i<items;i++)
	 {
	  printf("\t%s\t%s\n",psec[i].name,psec[i].description);
	 }

   //---- буфер доступных инструментов необходимо освободить
   //---- при помощи функции HeapFree
   if(psec!=NULL) ::HeapFree(hHeap,0,psec);

//---- закрываем winsock
   api.WinsockCleanup();

//----
   return 0;
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+

