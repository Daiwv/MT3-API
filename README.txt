MetaTrader application program interface.


The whole API consist of 29 functions of the MetaTrader client terminal
implemented in the mtapi.dll.
Access to the API functions can be processed as its shown in the source file
MetaTraderAPI.cpp. Definitions of functions as well as necessary structures of
the data located in the file MetaTraderAPI.h. For the static linkage there are
2 additional files - mtapi.lib and mtapi.h.


Client's functions:


int MtGetVersion( void );
Returns MTAPI version number as composed number in which major 3 digits are
version number of the API compatible client terminal. Minor 3 digits are
version number of this API.


int MtSetWorkingDirectory(const char * path); 
Assignment of the directory in which will be stored log-files coming from server, as well as some other
working files. As a parameter it is necessary to specify existing directories. If as parameter will
specify in NULL, then working directory will be appointed as the one from where the exe-file of the
client is running (by default the working directories are those containing mtapi.dll).
Returns one of return codes. Return codes are defined in the header file MetaTraderAPI.h.
All the functions below return one of return codes if another function's return is not specified.


int MtCreate(void); 
Socket object creation for the connection with MetaTrader server. Returns handle of opened socket
(internal socket number) in case of success. Or -1 in case of a mistake. There is a restriction on
quantity of simultaneously existing socket objects.


int MtDelete(const int handle); 
Deleting of the earlier created socket objects. As parameter it transfers handle returned from the
create socket object function.


int MtConnect(const int handle,const char *server,const int port); 
Establishment of connection with the server. Parameters:
handle – socket handle, in which it is necessary to establish connection;
server – the Internet address of the server (IP-address or domain name);
port – the port number(it is usually 1950).


int MtDisconnect(const int handle); 
Break of earlier established connection with the server. As parameter it passes socket handle.


int MtLogin( const int handle, const int login, const char *password ); 
Requesting the server to connect as an authorized client.
handle – socket handle through which connection with the server already established;
login – login number of the client (The real account number which the assigned client operates);
password – password for logging into the system.


int MtOpenDemoAccount( const int handle, DemoAccountInfo *info ); 
Request to the server for opening demo account and rights reception on managing this account.
handle – socket handle, through which connection with the server already established;
info – pointer to the variable of the DemoAccountInfo structure in which are filled all the fields
       necessary for registration on the server.
If the function succeeds account and password fields of the DemoAccountInfo structure will be filled
with valid values. After opening the account, the connection through the given socket will be necessary
to close using the function MtDisconnect and then to reopen again using the function MtConnect.


int MtChangePassword( const int handle, const char *newpass ); 
Request to the server for changing of the existing (current) password.
handle – socket handle through which connection with the server already established and the login
         into the system is made as an authorized client (hereafter 'socket handle');
newpass – the new password for the next login into the system.


RateInfo* MtGetRates( const int handle, const char *symbol, const int period, const time_t lasttime, int *counter ); 
Request to the server to getting prices history.
handle – socket handle;
symbol – the name of the security on which it is needed to receive quotations;
period – the period of quotations (PERIOD_M1, PERIOD_M5, PERIOD_M15, PERIOD_M30, PERIOD_H1,
         PERIOD_H4, PERIOD_D1, PERIOD_W1);
lasttime – time (in seconds since 1st January, 1970 ) starting of needed quotations;
counter – pointer to the int variable where the quantity of returned quotations will be written down.
returns RateInfo structures' array with *counter size or NULL in case of failure.
After using this array should be freed by the HeapFree function.
(example: HeapFree( GetProcessHeap(), 0, pRates );)


int MtGetTrades( const int handle ); 
Request to the server for receiving the list of open positions.
handle – socket handle.
The list of open positions received from the server are kept in socket object and can be obtained
using the function MtGetTradeRecords.


TradeRecord* MtGetTradeRecords( const int handle, BriefUserInfo *bui, int *items ); 
Obtain the list of opened positions.
handle – socket handle;
bui – pointer to the variable of BriefUserInfo structure where the information about the client
      will be written down;
items – pointer to the int variable where the quantity of opened positions will be written down.
Returns the array of the TradeRecord structures containing the list of opened positions. The array
of opened positions should be released using the function HeapFree.


TradeRecord* MtGetTradeHistory( const int handle, const time_t from, const time_t to, int *items ); 
Request to the server for receiving the history of trading operations.
handle – socket handle;
from, to – a range of time (in seconds since 1st January, 1970 ) of which required the carried out
           trading operations of the current account;
items – pointer to the int variable where the quantity of trading operations will be written down.
Returns the array of the TradeRecord structures containing the history of trading operations or NULL
in case of failure. The array of trading operations should be released using the function HeapFree.


char* MtGetNewsBody( const int handle, const int key ); 
Request to the server for receiving of news defined under its number.
handle – socket handle;
key – the news number.
Returns the symbolical string that contains newsbody or NULL in case of failure.
The string containing news should be released using the function HeapFree.


int MtGetPrices( const int handle, const char *symbol, const int lots, double *bid, double *ask ); 
Request to the server for receiving prices of the specified instrument.
handle – socket handle;
symbol – the name of the instrument of which price is required;
lots – quantity of lots;
bid – pointer to the variable of the double type in which the price bid will be written down;
ask – pointer to the variable of the double type in which the price ask will be written down.

Important note. If the instrument of which price is required is in Instant
Execution mode then it is strongly recommended to take last quotes of the
requested instrument. How to define the instrument which switched in an
Instant Execution mode. In the array of the ConSecurity structures which can
be received using the function MtGetSecurities the appropriate instrument has
in the field exemode the value EXE_MARKET.


int MtSendOrder( const int handle, const SendOrderInfo *soi ); 
Request to the server about open some position or placing some pending order.
handle – socket handle;
soi – pointer to the variable of the SendOrderInfo structure in which the client should fill-in
      the necessary fields.
The list of orders can be received with the help to call MtGetTrades and MtGetTradeRecords.
If socket was transferred in pumping mode of the data, then the list of orders will be updated
automatically and can be received with help of MtGetTradeRecords (without preliminary call MtGetTrades).


int MtDeleteOrder( const int handle, const int order ); 
Request to the server for deleting one of pending orders.
handle – socket handle;
order – ticket of pending order.


int MtModifyOrder(const int handle, const int order, const double price, const double sl, const double tp ); 
Request to the server for editing orders (changing orders characteristics).
handle – socket handle;
order – order's ticket;
price – new value of the price;
sl – new value of the Stop Loss;
tp – new value of the Take Profit.


int MtCloseOrder( const int handle, const int order, const double price, const int volume ); 
Request to the server for closing of some position.
handle – socket handle;
order – order's ticket;
price – value of the price;
volume – the size of a closed position (as well possibility of partial closing of position -
         will appear the new order with remained volume).


int MtCloseByOrder( const int handle, const int order, const int byorder ); 
Request to the server for closing one opened position with another opened position of the same symbol
but of different direction (sell closes buy and vice versa). After this operation one of orders can be
splitted.
handle – socket handle;
order – order's ticket required to be closed;
byorder – ticket of the order that will close.


int MtRefreshSecurities( const int handle ); 
Request to the server for updating list of accessible instruments. This function works with the file
securities.dat created in the working directory. Having this existing file with the actual list of
instruments considerably allows minimizing the traffic during the procedure on updating the list.
The list of accessible instruments received is written into a file, and saved in a socket object
and it can be prohibited using the function MtGetSecurities
handle – socket handle through which is already made the entrance into the system as an authorized client.


ConSecurity* MtGetSecurities( const int handle, int *items ); 
Receiving the list of accessible instruments.
handle – socket handle;
items – pointer to the int variable where it will be written the quantity of accessible instruments.
Returns the array of the ConSecurity structures that contains the list of instruments. The array of
accessible instruments should be released using the function HeapFree.


int MtAddSymbol( const int handle, const char * symbol ); 
Adding of some instrument to the list of selected instruments for getting streaming prices in pumping
mode. List of selected instruments saved in socket object.
handle – socket handle;
symbol – name of the instrument required to be added.


int MtHideSymbol( const int handle, const char * symbol ); 
Deleting instruments from the list of selected instruments. The quotations' stream in the pumping
mode for this symbol will be stopped.
handle – socket handle;
symbol – name of the instrument required to delete.


int MtSetPumpingMode( const int handle, const HWND destwnd, const UINT eventmsg ); 
Request to the server to set data pumping mode (passive mode). This mode assumes a reduction of
traffic as the server without additional inquiries of the client, will send the new data. This mode
assumes more operative to receive data, quotations, news, changes of opened positions and changes
on the account.
=====================================================================================================
Important! After transferring of the socket object in pumping mode of the data it is inadmissible
"not allowed" to request the server through the given socket any inquiries except for inquiries about
break on connection MtDisconnect. It is possible to call the following functions: MtGetTradeRecords,
MtGetSecurities, MtAddSymbol, MtHideSymbol, MtGetUpdatedTickInfo, MtGetLastNews, MtGetLastMail.
=====================================================================================================
handle – socket handle;
destwnd – window handle to which there will come messages on receipt of the new data from a server;
eventmsg – the identifier of the message which will be sent to the window. As parameter WPARAM one
           of values can be passed: UPDATE_BIDASK, UPDATE_NEWS, UPDATE_TRADES, UPDATE_MAIL or
           END_PUMPING. As parameter LPARAM will be passed the handle socket object that sent the message.


TickInfo* MtGetUpdatedTickInfo( const int handle, int *items ); 
Receiving list of last prices "quotations". Usually can be called after receiving the event
UPDATE_BIDASK. Because quotations come during data pumping, the list of the changed quotations
is to be requested at that socket object which is in pumping mode and has sent the appropriate message.
handle – socket handle;
items – pointer to the int variable where it will be written the quantity of quotations.
Returns the array of the structures TickInfo that contains the list of quotations. Quotations array
should be released using the function HeapFree.


NewsTopic* MtGetLastNews( const int handle, int *items ); 
ÏReceiving list of last news. Could be called after receiving the event UPDATE_ NEWS. List of last
news should be asked from that socket object, which is in pumping mode and sends appropriate message.
handle – socket handle;
items – pointer to the int variable where it will be written the quantity of news heads.
Returns array of the structures NewsTopic that contains list of news. Array of news should be
released using the function HeapFree.


int MtGetLastMail( const int handle, char * path, int *lenofpath ); 
Receiving file name in which was saved the previous letter from the server.
handle – handle of the socket transferred in pumping mode of data and sending the message UPDATE_MAIL;
path – the string of symbols for receiving the file name;
lenofpath – pointer to the int variable in which length of the string is written. If the name of the
            file (including terminating zero in the end) is more than the string length then in the
            passed string should be written a zero length and in the pointer address of the int variable
            lenofpath enters the needed length of the string which is necessary for receiving the file name.


TradeRecord* MtGetTradeRecords( const int handle, BriefUserInfo *bui, int *items ); 
This function is already described above. Addition is needed for the socket object, transferred in
pumping mode of the data: the list of open positions is necessary to request from that socket object
which has sent the message UPDATE_TRADES.


const char* MtGetErrorDescription( const int errorcode ); 
Returns the symbolical description of mistakes. As a parameter it use the return code from any
above described function.