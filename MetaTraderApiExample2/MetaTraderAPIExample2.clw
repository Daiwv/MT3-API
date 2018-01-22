; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=COrderForm
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MetaTraderAPIExample2.h"

ClassCount=4
Class1=CMetaTraderAPIExample2App
Class2=CMetaTraderAPIExample2Dlg

ResourceCount=5
Resource2=IDD_METATRADERAPIEXAMPLE2_DIALOG
Resource3=IDD_ORDER_FORM
Resource1=IDR_MAINFRAME
Class3=COpenAccountDlg
Resource4=IDD_OPENACCOUNT
Class4=COrderForm
Resource5=IDD_METATRADERAPIEXAMPLE2_DIALOG (English (U.S.))

[CLS:CMetaTraderAPIExample2App]
Type=0
HeaderFile=MetaTraderAPIExample2.h
ImplementationFile=MetaTraderAPIExample2.cpp
Filter=N

[CLS:CMetaTraderAPIExample2Dlg]
Type=0
HeaderFile=MetaTraderAPIExample2Dlg.h
ImplementationFile=MetaTraderAPIExample2Dlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_STATICSUMMARY



[DLG:IDD_METATRADERAPIEXAMPLE2_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CMetaTraderAPIExample2Dlg

[DLG:IDD_METATRADERAPIEXAMPLE2_DIALOG (English (U.S.))]
Type=1
Class=CMetaTraderAPIExample2Dlg
ControlCount=27
Control1=IDCANCEL,button,1342242816
Control2=IDC_EDITPORT,edit,1350631552
Control3=IDC_EDITLOGIN,edit,1350631552
Control4=IDC_EDITPASSWD,edit,1350631584
Control5=IDC_STATIC,static,1342308354
Control6=IDC_STATIC,static,1342308354
Control7=IDC_STATIC,static,1342308354
Control8=IDC_STATIC,static,1342308354
Control9=IDC_EDITSERVER,edit,1350631552
Control10=IDC_BTNCONNECT,button,1342242816
Control11=IDC_BTNDISCONNECT,button,1476460544
Control12=IDC_BTNOPENACC,button,1476460544
Control13=IDC_LISTSTATUS,listbox,1084293379
Control14=IDC_BNTLOGIN,button,1476460544
Control15=IDC_COMBOSECS,combobox,1344339971
Control16=IDC_BNTPASSWD,button,1476460544
Control17=IDC_LISTMARKET,SysListView32,1350631437
Control18=IDC_TAB,SysTabControl32,1342177282
Control19=IDC_LISTMAIL,SysListView32,1082195973
Control20=IDC_LISTNEWS,SysListView32,1082195973
Control21=IDC_LISTHIST,SysListView32,1082195973
Control22=IDC_LISTTRADE,SysListView32,1082195973
Control23=IDC_BTNADDSEC,button,1476460544
Control24=IDC_BTNHIDESEC,button,1476460544
Control25=IDC_STATICQUOTES,static,1342308352
Control26=IDC_STATIC,static,1342308354
Control27=IDC_STATICSUMMARY,static,1342308352

[DLG:IDD_OPENACCOUNT]
Type=1
Class=COpenAccountDlg
ControlCount=21
Control1=IDOK,button,1342242817
Control2=IDC_EDITNAME,edit,1350631552
Control3=IDC_EDITCOUNTRY,edit,1350631552
Control4=IDC_EDITCITY,edit,1350631552
Control5=IDC_EDITSTATE,edit,1350631552
Control6=IDC_EDITZIP,edit,1350631552
Control7=IDC_EDITADDRESS,edit,1350631552
Control8=IDC_EDITPHONE,edit,1350631552
Control9=IDC_EDITEMAIL,edit,1350631552
Control10=IDC_STATIC,static,1342308354
Control11=IDC_STATIC,static,1342308354
Control12=IDC_STATIC,static,1342308354
Control13=IDC_STATIC,static,1342308354
Control14=IDC_STATIC,static,1342308354
Control15=IDC_STATIC,static,1342308354
Control16=IDC_STATIC,static,1342308354
Control17=IDC_STATIC,static,1342308354
Control18=IDC_COMBOLEVERAGE,combobox,1344339971
Control19=IDC_COMBODEPOSIT,combobox,1344339971
Control20=IDC_STATIC,static,1342308354
Control21=IDC_STATIC,static,1342308354

[CLS:COpenAccountDlg]
Type=0
HeaderFile=OpenAccountDlg.h
ImplementationFile=OpenAccountDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=COpenAccountDlg

[DLG:IDD_ORDER_FORM]
Type=1
Class=COrderForm
ControlCount=27
Control1=IDC_STATIC,button,1342242823
Control2=IDC_STATIC,static,1342373890
Control3=IDC_SYMBOLS,combobox,1344339971
Control4=IDC_STATIC,static,1342373890
Control5=IDC_LOTS,combobox,1344339970
Control6=IDC_STATIC,static,1342308354
Control7=IDC_STOPLOSS,edit,1350631552
Control8=IDC_STATIC,static,1342308354
Control9=IDC_TAKEPROFIT,edit,1350631552
Control10=IDC_MARKET,button,1342242823
Control11=IDC_PRICES,static,1342378497
Control12=IDC_GET_PRICES,button,1342242816
Control13=IDC_SELL,button,1476460544
Control14=IDC_BUY,button,1476460544
Control15=IDC_CLOSE_DEAL,button,1476460544
Control16=IDC_CLOSE_BY,button,1476460544
Control17=IDC_CLOSE_DEALS,combobox,1478557955
Control18=IDC_STATIC,button,1342242823
Control19=IDC_STATIC,static,1342373890
Control20=IDC_COMMAND,combobox,1344339971
Control21=IDC_STATIC,static,1342373890
Control22=IDC_IDLE_PRICE,edit,1350631552
Control23=IDC_SEND,button,1342242816
Control24=IDCANCEL,button,1342242817
Control25=IDC_DELETE,button,1476460544
Control26=IDC_MODIFY,button,1476460544
Control27=IDC_STATIC,button,1342177287

[CLS:COrderForm]
Type=0
HeaderFile=OrderForm.h
ImplementationFile=OrderForm.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_MODIFY
VirtualFilter=dWC

