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


//���ܣ�Ŀǰ�ѿǺ�ǳ����ƺ���
//������
//		pOutFileName ����Ǳ����ļ��Ļ����ļ���
//		ppbuf �ѿǺ����ʼ��ַ��ָ��
//		pnlen �ѿ��޸�����򳤶ȵ�ָ��
//���أ��ɹ�0������-1

/*
ע�⣺����ص�������д����*ppbuf / * pnlen���ѿ���ɺ��Ѿ����޸�PE�ļ�����λ�úʹ�С��
ÿ������ǣ�������ڲ��ص������������������������Ҫ��ʲô�����󶨣���������������һ��
�ѿǺ��ļ�������ɱ���������ֱ��ɨ����Ƭ�ڴ��ˣ�����ǲ�ǣ���Ҫ�����ѿǵĻ��������Ƭ�ڴ������
����һ�ݣ���Ϊ��Ƭ�ڴ������������ѿǳ���Ľ��̿ռ䣬����ص�����ִ�������������ϻ���ձ��ѿǳ���
�Ľ��̿ռ䣬�����Ƭ�ڴ�Ҳ�����ˣ�
��������������·����ڴ棬�ѷ�����ڴ���Էŵ�*ppbuf�У����ȿ��Էŵ�* pnlen
������ָ��ָ��Ŀռ������ѿ�ʱ�򣬴���Ĳ���unpackInfo�е�unpackInf.pOutBuf / unpackInfo.nOutBufLen
����ص�������������ڴ棬ע��Ҫ�Լ��ͷţ�������ܲ�������

��������ķ���ֵ������ʱû�д�������ڲ����أ��������ķ���ֵû���κ�����
pOutFileName�����������ŲΪ���ã�����unpackInfo.pOutFileName��Ĭ�ϱ����������ļ���
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

//���ܣ��ѿǺ���
//������
//		pInputFile �������ȫ·��
//		pOutputFile �Ѻ��������ȫ·��
//���أ��ɹ��򷵻�0������-1
int CUnpack_testDlg::unpack(char *pInputFile, char *pOutputFile)
{
	CFile cfile;
	if(!cfile.Open(pInputFile, CFile::modeRead))
	{
		AfxMessageBox("�޷��򿪱��ѿ��ļ�!");
		return -1;
	}
	
	//��ȡ�ļ���Ϣ
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
	unpackInfo.pResultFun = write_back;	//##############ע������ص�����������#########
	unpackInfo.nOEPUnpack = 0;  //����ط����Ǹ�0,��ΪĿǰ��֧��OEP�Զ�Ѱ��
	
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
		if(COMPILE_RULE != nFunID) //���Ǳ�������Ϣ�Ļ�,���ѿ���
		{
			if(0 == g_unpack_fun[nFunID](&unpackInfo))
			{
				GetDlgItem(IDC_STATIC)->SetWindowText("�ѿǳɹ�!");
			}
			else
			{
				GetDlgItem(IDC_STATIC)->SetWindowText("�ѿ�ʧ��!");
			}
		}
	}
	else
	{
		AfxMessageBox("û�ж�Ӧ�ѿǺ���!");
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
		AfxMessageBox("����������ӿ�ʧ��!");
	}
	if(-1 == init_vmuppeid_dll("./vmuppeid.dll"))
	{
		AfxMessageBox("����Ǽ��ӿ�ʧ��!");
	}

	//�����ӿڳɹ���,�Ϳ�ʼ��ʼ�������CPU,���ؿ���������
	g_init_vm(); //��ʼ�������CPU,������CPU��װָ�����ϵͳ,Ѱַϵͳ

	g_init_peid_engine(); //��ʼ���Ǽ���������ݽṹ,ȫ��0

	if(-1 == g_load_peid_rule("./PEid_Sign.txt")) //���ؿ�������
	{
		AfxMessageBox("���ؿ�����ʧ��!");
	}

	GetDlgItem(IDC_STATIC)->SetWindowText("�ѿǻ���ʼ�����,һ������:)");
	
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

//�ѿǰ�ť
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


//֧����ק����
void CUnpack_testDlg::OnDropFiles(HDROP hDrop)
{
	// ����һ������������Ŷ�ȡ���ļ�����Ϣ
	char szFileName[MAX_PATH + 1] = {0};
	
	// ͨ������iFiles����Ϊ0xFFFFFFFF,����ȡ�õ�ǰ�϶����ļ�������
	// ������Ϊ0xFFFFFFFF,��������Ժ�������������
	UINT nFiles = DragQueryFile(hDrop, 0xFFFFFFFF, NULL, 0);
	
	// ͨ��ѭ������ȡ���϶��ļ���File Name��Ϣ����������ӵ�ListBox��
	for(UINT i=0; i < 1; i++)
	{
		DragQueryFile(hDrop, i, szFileName, MAX_PATH);
		
		GetDlgItem(IDC_STATIC)->SetWindowText(szFileName);
	}
	
	// �����˴���ק���������ͷŷ������Դ
	DragFinish(hDrop);
}

//�����������ѿǻ����ص���Դ
void CUnpack_testDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default

	//�ͷſǼ������ռ�õ��ڴ�
	pdestroy_peid_engine();

	//�ͷŶ�̬�����dll
	destroy_vmunpack_dll();
	destroy_vmuppeid_dll();
	
	CDialog::OnClose();
}
