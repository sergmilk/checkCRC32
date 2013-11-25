; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCheckDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Check.h"

ClassCount=3
Class1=CCheckApp
Class2=CCheckDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX (English (U.S.))
Resource4=IDD_CHECK_DIALOG
Resource5=IDR_MENU_MAIN

[CLS:CCheckApp]
Type=0
HeaderFile=Check.h
ImplementationFile=Check.cpp
Filter=N
LastObject=CCheckApp

[CLS:CCheckDlg]
Type=0
HeaderFile=CheckDlg.h
ImplementationFile=CheckDlg.cpp
Filter=D
LastObject=IDC_BUTTON_WRITE_REPORT
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=CheckDlg.h
ImplementationFile=CheckDlg.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg


[DLG:IDD_CHECK_DIALOG]
Type=1
Class=CCheckDlg
ControlCount=3
Control1=IDC_BUTTON_WRITE_REPORT,button,1342251008
Control2=IDC_BUTTON_CHECK_ARCHIVE,button,1342251008
Control3=IDC_RICHEDIT_INFORMATION_BOX,RICHEDIT,1353777348

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MENU_MAIN]
Type=1
Class=CCheckDlg
Command1=ID_START_CHOOSESOURCEFOLDER
Command2=ID_START_CHOOSEDESTINATIONFOLDER
CommandCount=2

