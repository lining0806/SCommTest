; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSCommTestDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SCommTest.h"

ClassCount=3
Class1=CSCommTestApp
Class2=CSCommTestDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_SCOMMTEST_DIALOG

[CLS:CSCommTestApp]
Type=0
HeaderFile=SCommTest.h
ImplementationFile=SCommTest.cpp
Filter=N

[CLS:CSCommTestDlg]
Type=0
HeaderFile=SCommTestDlg.h
ImplementationFile=SCommTestDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CSCommTestDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=SCommTestDlg.h
ImplementationFile=SCommTestDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_SCOMMTEST_DIALOG]
Type=1
Class=CSCommTestDlg
ControlCount=7
Control1=IDC_MSCOMM1,{648A5600-2C6E-101B-82B6-000000000014},1342242816
Control2=IDC_EDIT_RXDATA,edit,1352728580
Control3=IDC_EDIT_TXDATA,edit,1350631552
Control4=IDC_BUTTON_MANUALSEND,button,1342242816
Control5=IDC_CHECK_HEXSEND,button,1342242819
Control6=IDC_CHECK_HEXDISPLAY,button,1342242819
Control7=IDC_CHECK_AUTOSEND,button,1342242819

