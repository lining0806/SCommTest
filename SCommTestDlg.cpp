// SCommTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SCommTest.h"
#include "SCommTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSCommTestDlg dialog

CSCommTestDlg::CSCommTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSCommTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSCommTestDlg)
	m_strRXData = _T("");
	m_strTXData = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_bAutoSend = FALSE; //m_bAutoSend为BOOL型变量，在CLASSVIEW中为CSCommTestDlg类加入，并在构造函数中初始化

}

void CSCommTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSCommTestDlg)
	DDX_Control(pDX, IDC_CHECK_HEXDISPLAY, m_ctrlHexDisplay);
	DDX_Control(pDX, IDC_CHECK_HEXSEND, m_ctrlHexSend);
	DDX_Control(pDX, IDC_MSCOMM1, m_ctrlComm);
	DDX_Text(pDX, IDC_EDIT_RXDATA, m_strRXData);
	DDX_Text(pDX, IDC_EDIT_TXDATA, m_strTXData);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSCommTestDlg, CDialog)
	//{{AFX_MSG_MAP(CSCommTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_MANUALSEND, OnButtonManualsend)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK_AUTOSEND, OnCheckAutosend)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSCommTestDlg message handlers

BOOL CSCommTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	if(m_ctrlComm.GetPortOpen())
		m_ctrlComm.SetPortOpen(FALSE);
	
	m_ctrlComm.SetCommPort(12); //选择com12
	if( !m_ctrlComm.GetPortOpen())
		m_ctrlComm.SetPortOpen(TRUE);//打开串口
	else
		AfxMessageBox("cannot open serial port");
	
	m_ctrlComm.SetSettings("9600,n,8,1"); //波特率9600，无校验，8个数据位，1个停止位 
	m_ctrlComm.SetInputMode(1); //1：表示以二进制方式检取数据
	m_ctrlComm.SetRThreshold(1); 
	//参数1表示每当串口接收缓冲区中有多于或等于1个字符时将引发一个接收数据的OnComm事件
	m_ctrlComm.SetInputLen(0); //设置当前接收区数据长度为0
	m_ctrlComm.GetInput();//先预读缓冲区以清除残留数据

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSCommTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSCommTestDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSCommTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BEGIN_EVENTSINK_MAP(CSCommTestDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CSCommTestDlg)
	ON_EVENT(CSCommTestDlg, IDC_MSCOMM1, 1 /* OnComm */, OnComm, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CSCommTestDlg::OnComm() 
{
	// TODO: Add your control notification handler code here
// 	VARIANT variant_inp;
//     COleSafeArray safearray_inp;
//     LONG len,k;
//     BYTE rxdata[2048]; //设置BYTE数组 An 8-bit integer that is not signed.
//     CString strtemp;
//     if(m_ctrlComm.GetCommEvent()==2) //事件值为2表示接收缓冲区内有字符
//     {             
// 		////////以下你可以根据自己的通信协议加入处理代码
//         variant_inp=m_ctrlComm.GetInput(); //读缓冲区
//         safearray_inp=variant_inp; //VARIANT型变量转换为ColeSafeArray型变量
//         len=safearray_inp.GetOneDimSize(); //得到有效数据长度
//         for(k=0;k<len;k++)
//             safearray_inp.GetElement(&k,rxdata+k);//转换为BYTE型数组
//         for(k=0;k<len;k++) //将数组转换为Cstring型变量
//         {
//             BYTE bt=*(char*)(rxdata+k); //字符型
//             strtemp.Format("%c",bt); //将字符送入临时变量strtemp存放
//             m_strRXData+=strtemp; //加入接收编辑框对应字符串 
//         }
//     }
//     UpdateData(FALSE); //更新编辑框内容


	
	VARIANT variant_inp;
	COleSafeArray safearray_inp;
	LONG len,k;
	BYTE rxdata[2048]; //设置BYTE数组 An 8-bit integer that is not signed.
	CString strtemp;
	if(m_ctrlComm.GetCommEvent()==2) //事件值为2表示接收缓冲区内有字符
	{
		////////以下你可以根据自己的通信协议加入处理代码
		variant_inp=m_ctrlComm.GetInput(); //读缓冲区
		safearray_inp=variant_inp; //VARIANT型变量转换为ColeSafeArray型变量
		len=safearray_inp.GetOneDimSize(); //得到有效数据长度
		for(k=0;k<len;k++)
			safearray_inp.GetElement(&k,rxdata+k);//转换为BYTE型数组
		for(k=0;k<len;k++) //将数组转换为Cstring型变量
		{
			BYTE bt=*(char*)(rxdata+k); //字符型
			if(m_ctrlHexDisplay.GetCheck())
				strtemp.Format("%02X ",bt); //将字符以十六进制方式送入临时变量strtemp存放，注意这里加入一个空隔
			else 
				strtemp.Format("%c",bt); //将字符送入临时变量strtemp存放
			
			m_strRXData+=strtemp; //加入接收编辑框对应字符串 
		}
	}
	UpdateData(FALSE); //更新编辑框内容
}

void CSCommTestDlg::OnButtonManualsend() 
{
	// TODO: Add your control notification handler code here
// 	UpdateData(TRUE); //读取编辑框内容
// 	m_ctrlComm.SetOutput(COleVariant(m_strTXData));//发送ASCII数据

	UpdateData(TRUE); //读取编辑框内容
	if(m_ctrlHexSend.GetCheck())
	{
		CByteArray hexdata;
		int len=String2Hex(m_strTXData,hexdata); //此处返回的len可以用于计算发送了多少个十六进制数
		m_ctrlComm.SetOutput(COleVariant(hexdata)); //发送十六进制数据
	}
	else 
		m_ctrlComm.SetOutput(COleVariant(m_strTXData));//发送ASCII字符数据
}

int CSCommTestDlg::String2Hex(CString str, CByteArray &senddata)
{
	//由于这个转换函数的格式限制，在发送框中的十六制字符应该每两个字符之间插入一个空隔
    //如：A1 23 45 0B 00 29
	int hexdata,lowhexdata;
	int hexdatalen=0;
	int len=str.GetLength();
	senddata.SetSize(len/2);
	for(int i=0;i<len;)
	{
		char lstr,hstr=str[i];
		if(hstr==' ')
		{
			i++;
			continue;
		}
		i++;
		if(i>=len)
			break;
		lstr=str[i];
		hexdata=ConvertHexChar(hstr);
		lowhexdata=ConvertHexChar(lstr);
		if((hexdata==16)||(lowhexdata==16))
			break;
		else 
			hexdata=hexdata*16+lowhexdata;
		i++;
		senddata[hexdatalen]=(char)hexdata;
		hexdatalen++;
	}
	senddata.SetSize(hexdatalen);
	return hexdatalen;
}


char CSCommTestDlg::ConvertHexChar(char ch)
{
	//这是一个将字符转换为相应的十六进制值的函数
    //功能：若是在0-F之间的字符，则转换为相应的十六进制字符，否则返回-1
	if((ch>='0')&&(ch<='9'))
		return ch-0x30;
	else if((ch>='A')&&(ch<='F'))
		return ch-'A'+10;
	else if((ch>='a')&&(ch<='f'))
		return ch-'a'+10;
	else return (-1);
}

void CSCommTestDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	OnButtonManualsend();
	CDialog::OnTimer(nIDEvent);
}

void CSCommTestDlg::OnCheckAutosend() 
{
	// TODO: Add your control notification handler code here
	m_bAutoSend=!m_bAutoSend;
	if(m_bAutoSend)
	{
		SetTimer(1,1000,NULL);//时间为1000毫秒
	}
	else
	{
		KillTimer(1);  //取消定时
	}

}
