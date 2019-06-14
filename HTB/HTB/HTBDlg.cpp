
// HTBDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "HTB.h"
#include "HTBDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CHTBDlg 대화 상자



CHTBDlg::CHTBDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHTBDlg::IDD, pParent)
	, m_CPU(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHTBDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_OPENDIS, m_Btn_OpenDis);
	DDX_Control(pDX, IDC_BUTTON_OPENTBP, m_Btn_OpenTbp);
	DDX_Control(pDX, IDC_BUTTON_GENERATION, m_Btn_ProfileGen);
	DDX_Radio(pDX, IDC_RADIO_JTAGSELECTCPU_CPU0, m_CPU);
	DDX_Control(pDX, IDC_EDIT_PORT, m_Edit_Port);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ctrlIPAddr);
}

BEGIN_MESSAGE_MAP(CHTBDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPENDIS, &CHTBDlg::OnBnClickedButtonOpendis)
	ON_BN_CLICKED(IDC_BUTTON_OPENTBP, &CHTBDlg::OnBnClickedButtonOpentbp)
	ON_BN_CLICKED(IDC_BUTTON_GENERATION, &CHTBDlg::OnBnClickedButtonGeneration)
	ON_BN_CLICKED(IDC_RADIO_JTAGSELECTCPU_CPU0, &CHTBDlg::OnBnClickedRadioJtagselectcpuCpu0)
	ON_BN_CLICKED(IDC_RADIO_JTAGSELECTCPU_CPU1, &CHTBDlg::OnBnClickedRadioJtagselectcpuCpu1)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CHTBDlg 메시지 처리기

BOOL CHTBDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_Edit_Port.SetWindowTextW(_T("5556"));
	m_ctrlIPAddr.SetAddress(127, 0, 0, 1);


	CButton* pButton = (CButton*)GetDlgItem(IDC_RADIO_JTAGSELECTCPU_CPU0);
	pButton->SetCheck(true);

	m_gcpu = 4;
	ConnectSocket = NULL;

	tbp_path_str = _T("");
	dis_path_str = _T("");
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CHTBDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CHTBDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}


BOOL CHTBDlg::PreTranslateMessage(MSG* pMsg)
{
	//키눌린 메시지가 들어올때 esc이거나 return  값이면
	//걍 리턴 시켜준다.
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_ESCAPE:
		case VK_RETURN:
			return TRUE;
		default:
			break;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CHTBDlg::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	NetClo(ConnectSocket);

	CDialogEx::OnClose();
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CHTBDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CHTBDlg::OnBnClickedButtonOpendis()
{
	CString strDisPath = _T("");
	CString strDefExt = _T("dis");
	CString strFilter = _T("Disassemble Files(*.dis)|*.dis||");

	// Open Dialog
	if (!ShowOpenFileDlg(&strDisPath, strDefExt, strFilter, this))
		return;

	dis_path_str = strDisPath;
}


void CHTBDlg::OnBnClickedButtonOpentbp()
{
#if 0
	TCHAR pszPathName[_MAX_PATH];
	GetCurrentDirectory(_MAX_PATH, pszPathName);

	tbp_path_str = pszPathName;

	CString module_std = _T("");
	if (m_gcpu == 4)
	{
		tbp_path_str = tbp_path_str + _T("\\cpu0.htb");
		module_std = _T("isp ");
	}
	if (m_gcpu == 5)
	{
		tbp_path_str = tbp_path_str + _T("\\cpu1.htb");
		module_std = _T("ip0 ");
	}
#endif

//--------------------------------------------------------------------------------
// Server 연결
	CString strAddr;
	CString strPort;
	//strAddr.Format(_T("192.168.0.199"));
	//strPort = _T("5556");


	int err;
	BYTE IP[4];
	err = m_ctrlIPAddr.GetAddress(IP[0], IP[1], IP[2], IP[3]);
	if (err < 4)
	{
		AfxMessageBox(_T("Please, enter IP."));
		return;
	}
	else
	{
		strAddr.Format(_T("%d.%d.%d.%d"), IP[0], IP[1], IP[2], IP[3]);
	}

	m_Edit_Port.GetWindowTextW(strPort);
	if (strPort == _T(""))
	{
		AfxMessageBox(_T("Please, enter Port."));
		return ;
	}


	char ch_ip[64];
	char ch_port[64];
	CStringA addr;
	CStringA port;
	addr = strAddr;
	port = strPort;
	strcpy(ch_ip, addr.GetBuffer(addr.GetLength()));
	strcpy(ch_port, port.GetBuffer(port.GetLength()));

	ConnectSocket = NetCon(ch_ip, ch_port);
	if (ConnectSocket <= 0)
	{
		NetClo(ConnectSocket);
		ConnectSocket = NULL;
		AfxMessageBox(_T("Server Connect Fail"));
		return;
	}

	Sleep(100);


//--------------------------------------------------------------------------------
// 명령 전송
	int state = -1;
	state = sendMsg(ConnectSocket, "rem_st ");

	Sleep(100);

	CString strHtbPath = _T("");
	CString strDefExt = _T("htb");
	CString strFilter = _T("HTB Files(*.htb)|*.htb||");
	// Open Dialog
	if (!ShowOpenFileDlg(&strHtbPath, strDefExt, strFilter, this))
		return;

	tbp_path_str = strHtbPath;

	CString module_std = _T("");
	if (m_gcpu == 4)
	{
		module_std = _T("isp ");
	}
	if (m_gcpu == 5)
	{
		module_std = _T("ip0 ");
	}


	CString cmd_str = _T("rem_tbp ");
	CStringA cmd_arr;
	char ch_cmd[256];
	cmd_str = cmd_str + module_std + tbp_path_str + _T(" ");
	cmd_arr = cmd_str;
	strcpy(ch_cmd, cmd_arr.GetBuffer(cmd_arr.GetLength()));
	state = sendMsg(ConnectSocket, ch_cmd);
}


BOOL CHTBDlg::ShowOpenFileDlg(CString* strPath, CString strDefExt, CString strFilter, CWnd* pWnd, CString strStartPath)
{
	int iDlgReturn = 0;
	_TCHAR szNowPath[MAX_PATH];

	// ----------------------------------------------------------------------------------------------------
	// 다이얼로그
	// 현재 작업 경로 얻기
	::GetCurrentDirectory(MAX_PATH, szNowPath);

	// 파일 다이얼로그 경로 설정
	CFileFind ffind;
	if (ffind.FindFile(*strPath))
		ffind.Close();
	else
		*strPath = _T("");

	// Open 다이얼로그
	CFileDialog FileDlg(TRUE, strDefExt, *strPath, OFN_HIDEREADONLY, strFilter, pWnd);

	if (strStartPath != _T(""))
		FileDlg.m_ofn.lpstrInitialDir = strStartPath;

	iDlgReturn = FileDlg.DoModal();

	// 현재 작업 경로 재설정
	::SetCurrentDirectory(szNowPath);

	// ----------------------------------------------------------------------------------------------------
	// Return
	if (iDlgReturn != IDOK)
	{
		*strPath = _T("");
		return FALSE;
	}
	else
	{
		*strPath = FileDlg.GetPathName();
		return TRUE;
	}
}

CString CHTBDlg::GetSelectFolderPath()
{
	CString strFolderPath;

	ITEMIDLIST *pidlBrowse;
	TCHAR       pszPathname[MAX_PATH];
	BROWSEINFO  BrInfo;

	BrInfo.hwndOwner = GetSafeHwnd();
	BrInfo.pidlRoot = NULL; //# Null이면 최초 위치는 "바탕화면"입니다.

	memset(&BrInfo, 0, sizeof(BrInfo));
	BrInfo.pszDisplayName = pszPathname;
	BrInfo.lpszTitle = _T("Select Directory");
	BrInfo.ulFlags = BIF_RETURNONLYFSDIRS;
	pidlBrowse = ::SHBrowseForFolder(&BrInfo);
	if (pidlBrowse != NULL)
	{
		SHGetPathFromIDList(pidlBrowse, pszPathname);
	}

	strFolderPath.Format(_T("%s"), pszPathname);

	return strFolderPath;
}


void CHTBDlg::OnBnClickedRadioJtagselectcpuCpu0()
{
	m_gcpu = 4;
}


void CHTBDlg::OnBnClickedRadioJtagselectcpuCpu1()
{
	m_gcpu = 5;
}


#define HTB_REG	0x0005dc00
void CHTBDlg::OnBnClickedButtonGeneration()
{
	TCHAR pszPathname[MAX_PATH];
	CString prf_path = _T("");

	BOOL run_flag = FALSE;
	CString ErrMsg = _T("");
	int state = -1;

	BYTE* temp = NULL;
	UINT32 data;

	CString tbp_path_str;

	EnableCtrl(FALSE);

	Sleep(100);

//--------------------------------------------------------------------------------
// 1. htb 동작여부 check
	state = getDataFromRemote(ConnectSocket, HTB_REG, 4, m_gcpu, &temp);
	if (state < 0)
	{
		ErrMsg = _T("Register Read Fail");
		goto END;
	}

	data = ntohl((UINT32)temp);
	if (data != 0x7)
	{
		ErrMsg.Format(_T("HTB off 0x%x"), data);
		if (IDNO == AfxMessageBox(ErrMsg, MB_YESNO))
		{
			goto END;
		}
	}

	Sleep(100);
//--------------------------------------------------------------------------------
// 2. bat 파일 생성 및 수정
#if 0
	if (batrun() < 0)
		goto END;
#else
	batrun();
#endif

	Sleep(100);

	run_flag = TRUE;
	AfxMessageBox(_T("Complete"));

	StrCpy(pszPathname, prf_path_str);
	PathRemoveFileSpec(pszPathname);
	prf_path = pszPathname;
	ShellExecute(NULL, _T("open"), _T("explorer"), prf_path, NULL, SW_SHOW);

END :
	if (!run_flag)
	{
		if (ErrMsg)
			AfxMessageBox(ErrMsg);
	}

	//--------------------------------------------------------------------------------
// 3. 연결 끊기
	NetClo(ConnectSocket);
	ConnectSocket = NULL;

	EnableCtrl(TRUE);
}

int CHTBDlg::batrun()
{
	CFileFind pFind;
	if (!pFind.FindFile(tbp_path_str))
	{
		AfxMessageBox((_T("%s가 존재하지 않습니다."), tbp_path_str));
		return -1;
	}

	if (!pFind.FindFile(dis_path_str))
	{
		AfxMessageBox((_T("%s가 존재하지 않습니다."), dis_path_str));
		return -1;
	}

#if 0
	// bat 파일 읽기
	CStdioFile std_file, std_tempfile;
	CFileException e;
	if (!std_file.Open(_T("run_h.bat"), CFile::modeReadWrite, &e))
	{
		e.ReportError();
		return -1;
	}
	if (!std_tempfile.Open(_T("run_h_temp.bat"), CFile::modeWrite | CFile::modeCreate, &e))
	{
		e.ReportError();
		return -1;
	}

	// 파일 작성
	CString str_cmd = _T("");
	CString str_findcmd = _T("profiler");
	CString str_writecmd = _T("");
	str_writecmd.Format(_T("profiler.exe -hz 199800000 -dis %s -htb %s -o output.prf"), dis_path_str, tbp_path_str);

	while (std_file.ReadString(str_cmd))
	{
		if ((str_cmd.Find(str_findcmd) != -1))
		{
			std_tempfile.WriteString(str_writecmd + "\n");
		}
		else
		{
			std_tempfile.WriteString(str_cmd + "\n");
		}
	}

	std_tempfile.Close();
	std_file.Close();

	::DeleteFile(_T("run_h.bat"));
	CFile::Rename(_T("run_h_temp.bat"), _T("run_h.bat"));

#endif

	CString strPrfPath = _T("");
	CString strDefExt = _T("prf");
	CString strFilter = _T("Profile Files(*.prf)|*.prf||");
	// Open Dialog
	if (!ShowOpenFileDlg(&strPrfPath, strDefExt, strFilter, this))
		return -1;

	prf_path_str = strPrfPath;

	CString str_writecmd = _T("");
	str_writecmd.Format(_T("profiler.exe -hz 199800000 -dis %s -htb %s -o %s"), dis_path_str, tbp_path_str, prf_path_str);

	Sleep(1000);

	CStringA cmd_arr;
	char ch_cmd[256];
	cmd_arr = str_writecmd;
	strcpy(ch_cmd, cmd_arr.GetBuffer(cmd_arr.GetLength()));

	system(cmd_arr);

	return 0;
}

void CHTBDlg::EnableCtrl(BOOL bEnable)
{
	m_Edit_Port.EnableWindow(bEnable);
	m_ctrlIPAddr.EnableWindow(bEnable);
	
	m_Btn_OpenDis.EnableWindow(bEnable);
	m_Btn_OpenTbp.EnableWindow(bEnable);
	m_Btn_ProfileGen.EnableWindow(bEnable);

	GetDlgItem(IDC_RADIO_JTAGSELECTCPU_CPU0)->EnableWindow(bEnable);
	GetDlgItem(IDC_RADIO_JTAGSELECTCPU_CPU1)->EnableWindow(bEnable);
}