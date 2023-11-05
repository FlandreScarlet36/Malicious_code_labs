// unpack_testDlg.cpp : implementation file
//

#include "stdafx.h"
#include "unpack_test.h"
#include "unpack_testDlg.h"


#include "init_peid_vmpack.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About


//功能：目前脱壳后壳程序善后函数
//参数：
//		pOutFileName 如果是保存文件的话，文件名
//		ppbuf 脱壳后程序开始地址的指针
//		pnlen 脱壳修复后程序长度的指针
//返回：成功0，否则-1

/*
注意：这个回调函数的写法，*ppbuf / * pnlen是脱壳完成后已经被修复PE文件所在位置和大小，
每次脱完壳，虚拟机内部回调这个函数，这个函数里面具体要干什么视需求定，我这里是生成了一个
脱壳后文件，如是杀毒这里可以直接扫描这片内存了，如果是查壳，还要继续脱壳的话，请把这片内存的内容
复制一份，因为这片内存隶属被虚拟脱壳程序的进程空间，这个回调函数执行完后，虚拟机马上会回收被脱壳程序
的进程空间，因此这片内存也消亡了，
在这里你可以重新分配内存，把分配的内存可以放到*ppbuf中，长度可以放到* pnlen
这两个指针指向的空间是你脱壳时候，传入的参数unpackInfo中的unpackInf.pOutBuf / unpackInfo.nOutBufLen
这个回调函数里申请的内存，注意要自己释放，虚拟机管不着这里

这个函数的返回值，我暂时没有从虚拟机内部返回，因此这里的返回值没有任何意义
pOutFileName这个参数可以挪为它用，它是unpackInfo.pOutFileName，默认保存的是输出文件名
*/
int write_back(char * pOutFileName, char **ppbuf, int * pnlen)
{
	CFile cfile;

	if(!cfile.Open(pOutFileName, CFile::modeWrite | CFile::modeCreate))
	{
		printf("create result file error!\n");
		return -1;
	}
	cfile.Write(*ppbuf, *pnlen);
	cfile.Close();

	return 0;
}

//功能：脱壳函数
//参数：
//		pInputFile 待脱软件全路径
//		pOutputFile 脱后软件保存全路径
//返回：成功则返回0，否则-1
int CUnpack_testDlg::unpack(char *pInputFile, char *pOutputFile)
{
	CFile cfile;
	if(!cfile.Open(pInputFile, CFile::modeRead))
	{
		AfxMessageBox("无法打开被脱壳文件!");
		return -1;
	}
	
	//读取文件信息
	long lFileLen = cfile.GetLength();
	char* lpBuffer = new char[lFileLen];
	
	cfile.Read(lpBuffer, lFileLen);
	cfile.Close();

	ProcNeedMemInfo unpackMemInfo;
	memset(&unpackMemInfo, 0, sizeof(ProcNeedMemInfo));

	UnpackInfo unpackInfo;
	unpackInfo.pMemInfo = &unpackMemInfo;
	unpackInfo.pInFileName = pInputFile;
	unpackInfo.pInBuf = lpBuffer;
	unpackInfo.nInBufLen = lFileLen;
	unpackInfo.pOutFileName = pOutputFile;
	unpackInfo.pResultFun = write_back;	//##############注意这个回调函数的设置#########
	unpackInfo.nOEPUnpack = 0;  //这个地方总是给0,因为目前不支持OEP自动寻找
	
	char * pPackerName;
	int nFunID;
	nFunID =g_peid_check((unsigned char *)lpBuffer, lFileLen, &pPackerName);

	CString strInfo;
	if(NULL != pPackerName)
	{
		strInfo.Format("%s", pPackerName);
		GetDlgItem(IDC_STATIC)->SetWindowText(strInfo);
	}
	if(0 != nFunID)
	{
		if(COMPILE_RULE != nFunID) //不是编译器信息的话,就脱壳了
		{
			if(0 == g_unpack_fun[nFunID](&unpackInfo))
			{
				GetDlgItem(IDC_STATIC)->SetWindowText("脱壳成功!");
			}
			else
			{
				GetDlgItem(IDC_STATIC)->SetWindowText("脱壳失败!");
			}
		}
	}
	else
	{
		AfxMessageBox("没有对应脱壳函数!");
	}

	delete [] lpBuffer;

	return 0;
}


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
// CUnpack_testDlg dialog

CUnpack_testDlg::CUnpack_testDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUnpack_testDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUnpack_testDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUnpack_testDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUnpack_testDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CUnpack_testDlg, CDialog)
	//{{AFX_MSG_MAP(CUnpack_testDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON, OnButton)
	ON_WM_DROPFILES()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUnpack_testDlg message handlers

BOOL CUnpack_testDlg::OnInitDialog()
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
	if(-1 == init_vmunpack_dll("./vmunpack.dll"))
	{
		AfxMessageBox("导入虚拟机接口失败!");
	}
	if(-1 == init_vmuppeid_dll("./vmuppeid.dll"))
	{
		AfxMessageBox("导入壳检测接口失败!");
	}

	//导出接口成功后,就开始初始化虚拟机CPU,加载壳特征库了
	g_init_vm(); //初始化虚拟机CPU,给虚拟CPU安装指令解析系统,寻址系统

	g_init_peid_engine(); //初始化壳检测引擎数据结构,全清0

	if(-1 == g_load_peid_rule("./PEid_Sign.txt")) //加载壳特征库
	{
		AfxMessageBox("加载壳特征失败!");
	}

	GetDlgItem(IDC_STATIC)->SetWindowText("脱壳机初始化完毕,一切正常:)");
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CUnpack_testDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CUnpack_testDlg::OnPaint() 
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
HCURSOR CUnpack_testDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//脱壳按钮
void CUnpack_testDlg::OnButton() 
{
	// TODO: Add your control notification handler code here
	CString strFileName;
	GetDlgItem(IDC_STATIC)->GetWindowText(strFileName);
	if(!strFileName.IsEmpty())
	{
		CString strTemp;
		int i = strFileName.ReverseFind('\\');
		strTemp = strFileName.Left(i);
		CString strOutFileName;
		CString strTemp1 = strFileName.Right(4);
		
		strOutFileName.Format("%s\\%s%s", strTemp, "unpacked", strTemp1);
		unpack(strFileName.GetBuffer(strFileName.GetLength() + 1), strOutFileName.GetBuffer(strOutFileName.GetLength() + 1));
	}
}


//支持拖拽代码
void CUnpack_testDlg::OnDropFiles(HDROP hDrop)
{
	// 定义一个缓冲区来存放读取的文件名信息
	char szFileName[MAX_PATH + 1] = {0};
	
	// 通过设置iFiles参数为0xFFFFFFFF,可以取得当前拖动的文件数量，
	// 当设置为0xFFFFFFFF,函数间忽略后面连个参数。
	UINT nFiles = DragQueryFile(hDrop, 0xFFFFFFFF, NULL, 0);
	
	// 通过循环依次取得拖动文件的File Name信息，并把它添加到ListBox中
	for(UINT i=0; i < 1; i++)
	{
		DragQueryFile(hDrop, i, szFileName, MAX_PATH);
		
		GetDlgItem(IDC_STATIC)->SetWindowText(szFileName);
	}
	
	// 结束此次拖拽操作，并释放分配的资源
	DragFinish(hDrop);
}

//在这里销毁脱壳机加载的资源
void CUnpack_testDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default

	//释放壳检测引擎占用的内存
	pdestroy_peid_engine();

	//释放动态导入的dll
	destroy_vmunpack_dll();
	destroy_vmuppeid_dll();
	
	CDialog::OnClose();
}
