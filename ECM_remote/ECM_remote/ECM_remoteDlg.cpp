
// ECM_remoteDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "ECM_remote.h"
#include "ECM_remoteDlg.h"
#include "afxdialogex.h"
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <io.h>		//access
#include "SettingDlg.h"

#include <WtsApi32.h>
#pragma comment(lib, "Wtsapi32.lib")

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "WS2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#pragma warning(disable:4996)

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const UINT  ID_CHECK_TIMER = 200;
const UINT  ID_CONNECT_TIMER = 300;

#define		Check_Time		1000
#define		Connect_Time	5000

UINT ExeState(LPVOID pParam);
UINT State_Check_Thread(LPVOID pParam);
UINT Connect_Check_Thread(LPVOID pParam);

BOOL SafeTerminateProcess(HANDLE hProcess, UINT uExitCode);

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


// CECM_remoteDlg 대화 상자



CECM_remoteDlg::CECM_remoteDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CECM_remoteDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ECM);
}

void CECM_remoteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDCANCEL, m_Btn_Close);
	DDX_Control(pDX, IDC_BUTTON_MINIMIZE, m_Btn_Minimize);
	DDX_Control(pDX, IDC_BUTTON_SETTING, m_Btn_Setting);
	DDX_Control(pDX, IDC_BUTTON_RESET, m_Btn_Reset);
	DDX_Control(pDX, IDC_BUTTON_STALL, m_Btn_Stall);
	DDX_Control(pDX, IDC_EDIT1, m_Edit_Port);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ctrlIPAddr);
	DDX_Control(pDX, IDC_BUTTON_SERVER, m_Bt_Server);
	DDX_Control(pDX, IDC_BUTTON_SERVERSTATE, m_Bt_ServerState);
	DDX_Control(pDX, IDC_BUTTON_ECMSEARCH, m_Bt_ECMSearch);
	DDX_Control(pDX, IDC_BUTTON_DOWNLOADER, m_Bt_Downloader);
	DDX_Control(pDX, IDC_BUTTON_PARAMETER, m_Bt_Parameter);
	DDX_Control(pDX, IDC_BUTTON_VIEWER, m_Bt_Viewer);
	DDX_Control(pDX, IDC_BUTTON_JTAGPRINT0, m_Bt_JTAGPrint0);
	DDX_Control(pDX, IDC_BUTTON_JTAGPRINT1, m_Bt_JTAGPrint1);
	DDX_Control(pDX, IDC_BUTTON_JTAGPRINT, m_Bt_JTAGPrint);
	DDX_Control(pDX, IDC_BUTTON_DEBUGGER, m_Bt_JTAGDebugger);
	DDX_Control(pDX, IDC_BUTTON_ANALYZER, m_Bt_Analyzer);
	DDX_Control(pDX, IDC_BUTTON_ISP, m_Bt_ISP);
	DDX_Control(pDX, IDC_BUTTON_GAMMA, m_Bt_Gamma);
	DDX_Control(pDX, IDC_BUTTON_COLORMAP, m_Bt_ColorMap);
	DDX_Control(pDX, IDC_BUTTON_KEY, m_Bt_Key);
	DDX_Control(pDX, IDC_BUTTON_UARTSTRING, m_Bt_UartString);
	DDX_Control(pDX, IDC_BUTTON_LUA, m_Bt_Lua);
	DDX_Control(pDX, IDC_BUTTON_IPCAMSEARCH, m_Bt_IPCamSearch);
	DDX_Control(pDX, IDC_BUTTON_SHSPECIAL, m_Btn_Special);
}

BEGIN_MESSAGE_MAP(CECM_remoteDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDCANCEL, &CECM_remoteDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_MINIMIZE, &CECM_remoteDlg::OnBnClickedButtonMinimize)
	ON_BN_CLICKED(IDC_BUTTON_SETTING, &CECM_remoteDlg::OnBnClickedButtonSetting)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CECM_remoteDlg::OnBnClickedButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_STALL, &CECM_remoteDlg::OnBnClickedButtonStall)
	ON_BN_CLICKED(IDC_BUTTON_SERVER, &CECM_remoteDlg::OnBnClickedButtonServer)
	ON_BN_CLICKED(IDC_BUTTON_SERVERSTATE, &CECM_remoteDlg::OnBnClickedButtonServerstate)
	ON_BN_CLICKED(IDC_BUTTON_ECMSEARCH, &CECM_remoteDlg::OnBnClickedButtonEcmsearch)
	ON_BN_CLICKED(IDC_BUTTON_DOWNLOADER, &CECM_remoteDlg::OnBnClickedButtonDownloader)
	ON_BN_CLICKED(IDC_BUTTON_PARAMETER, &CECM_remoteDlg::OnBnClickedButtonParameter)
	ON_BN_CLICKED(IDC_BUTTON_VIEWER, &CECM_remoteDlg::OnBnClickedButtonViewer)
	ON_BN_CLICKED(IDC_BUTTON_JTAGPRINT0, &CECM_remoteDlg::OnBnClickedButtonJtagprint0)
	ON_BN_CLICKED(IDC_BUTTON_JTAGPRINT1, &CECM_remoteDlg::OnBnClickedButtonJtagprint1)
	ON_BN_CLICKED(IDC_BUTTON_JTAGPRINT, &CECM_remoteDlg::OnBnClickedButtonJtagprint)
	ON_BN_CLICKED(IDC_BUTTON_DEBUGGER, &CECM_remoteDlg::OnBnClickedButtonDebugger)
	ON_BN_CLICKED(IDC_BUTTON_ANALYZER, &CECM_remoteDlg::OnBnClickedButtonAnalyzer)
	ON_BN_CLICKED(IDC_BUTTON_ISP, &CECM_remoteDlg::OnBnClickedButtonIsp)
	ON_BN_CLICKED(IDC_BUTTON_GAMMA, &CECM_remoteDlg::OnBnClickedButtonGamma)
	ON_BN_CLICKED(IDC_BUTTON_COLORMAP, &CECM_remoteDlg::OnBnClickedButtonColormap)
	ON_BN_CLICKED(IDC_BUTTON_KEY, &CECM_remoteDlg::OnBnClickedButtonKey)
	ON_BN_CLICKED(IDC_BUTTON_UARTSTRING, &CECM_remoteDlg::OnBnClickedButtonUartstring)
	ON_BN_CLICKED(IDC_BUTTON_LUA, &CECM_remoteDlg::OnBnClickedButtonLua)
	ON_BN_CLICKED(IDC_BUTTON_SHSPECIAL, &CECM_remoteDlg::OnBnClickedButtonShspecial)
	ON_WM_MOVE()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BUTTON_IPCAMSEARCH, &CECM_remoteDlg::OnBnClickedButtonIpcamsearch)
	ON_WM_TIMER()
	ON_EN_KILLFOCUS(IDC_EDIT1, &CECM_remoteDlg::OnEnKillfocusEdit1)
	ON_EN_SETFOCUS(IDC_EDIT1, &CECM_remoteDlg::OnEnSetfocusEdit1)
END_MESSAGE_MAP()

// CECM_remoteDlg 메시지 처리기

BOOL CECM_remoteDlg::OnInitDialog()
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
	int x = ReadIni(SEC_WININFO, KEY_MAINDLGLEFT, DEF_MAINDLGLEFT);
	int y = ReadIni(SEC_WININFO, KEY_MAINDLGTOP, DEF_MAINDLGTOP);
	SetWindowPos(NULL, x, y, 0, 0, SWP_NOSIZE);
	
	pRemoteDlg = this;

	// IP 주소 초기화
	Addr = ReadIni(SEC_ECMREMOTE, KEY_IPADDR, _T(""));
	CString temp_str[4];
	int temp[4];
	if (Addr == _T(""))
	{
		//Addr = GetMyIPAddress();
		Addr = _T("127.0.0.1");
	}

	for (int i = 0; i < 4; i++)
	{
		AfxExtractSubString(temp_str[i], Addr, i, '.');
		temp[i] = _ttoi(temp_str[i]);
		IP[i] = (BYTE)temp[i];
	}
	m_ctrlIPAddr.SetAddress(IP[0], IP[1], IP[2], IP[3]);

	// Port 초기화
	Port = ReadIni(SEC_ECMREMOTE, KEY_PORT, _T(""));
	if (Port != _T(""))
		m_Edit_Port.SetWindowTextW(Port);
	else
		m_Edit_Port.SetWindowTextW(_T("5556"));

// ----------------------------------------------------------------------------------------------------
// Create Sub Dialog
	CRect rect;
	this->GetWindowRect(&rect);

	m_pDlg_Server = new CServerDlg();
	m_pDlg_Server->Create(IDD_EXROCD, this);
	m_pDlg_Server->SetWindowPos(NULL, rect.right, rect.top, 0, 0, SWP_SHOWWINDOW | SWP_NOZORDER | SWP_NOSIZE);

	m_pDlg_Server->ShowWindow(SW_HIDE);

#if ECMSEARCHUSER
	m_pDlg_Server->GetWindowRect(&rect);
	m_pDlg_ECMSearch = new CECMSearchDlg();
	m_pDlg_ECMSearch->Create(IDD_ECMSEARCH, this);
	m_pDlg_ECMSearch->SetWindowPos(NULL, rect.right, rect.top, 0, 0, SWP_SHOWWINDOW | SWP_NOZORDER | SWP_NOSIZE);

	m_pDlg_ECMSearch->ShowWindow(SW_HIDE);
#endif

// ----------------------------------------------------------------------------------------------------
// 버튼 초기화
	InitEnableCtrl();

	m_Btn_Close.DrawBorder(FALSE);
	m_Btn_Close.SetColor(CButtonST::BTNST_COLOR_BK_OUT, DIALOGCOLOR);
	m_Btn_Close.SetColor(CButtonST::BTNST_COLOR_BK_IN, DIALOGSUBCOLOR);

	m_Btn_Minimize.DrawBorder(FALSE);
	m_Btn_Minimize.SetColor(CButtonST::BTNST_COLOR_BK_OUT, DIALOGCOLOR);
	m_Btn_Minimize.SetColor(CButtonST::BTNST_COLOR_BK_IN, DIALOGSUBCOLOR);

	m_Bt_Server.SetShade(CShadeButtonST::SHS_NOISE, 0, 20);
	m_Bt_ECMSearch.SetShade(CShadeButtonST::SHS_NOISE, 0, 20);
	m_Bt_Downloader.SetShade(CShadeButtonST::SHS_NOISE, 0, 20);
	m_Bt_Parameter.SetShade(CShadeButtonST::SHS_NOISE, 0, 20);
	m_Bt_Viewer.SetShade(CShadeButtonST::SHS_NOISE, 0, 20);
	m_Bt_JTAGPrint0.SetShade(CShadeButtonST::SHS_NOISE, 0, 20);
	m_Bt_JTAGPrint1.SetShade(CShadeButtonST::SHS_NOISE, 0, 20);
	m_Bt_JTAGPrint.SetShade(CShadeButtonST::SHS_NOISE, 0, 20);
	m_Bt_JTAGDebugger.SetShade(CShadeButtonST::SHS_NOISE, 0, 20);
	m_Bt_Analyzer.SetShade(CShadeButtonST::SHS_NOISE, 0, 20);
	m_Bt_ISP.SetShade(CShadeButtonST::SHS_NOISE, 0, 20);
	m_Bt_Gamma.SetShade(CShadeButtonST::SHS_NOISE, 0, 20);
	m_Bt_ColorMap.SetShade(CShadeButtonST::SHS_NOISE, 0, 20);
	m_Bt_Key.SetShade(CShadeButtonST::SHS_NOISE, 0, 20);
	m_Bt_UartString.SetShade(CShadeButtonST::SHS_NOISE, 0, 20);
	m_Bt_Lua.SetShade(CShadeButtonST::SHS_NOISE, 0, 20);
	m_Bt_IPCamSearch.SetShade(CShadeButtonST::SHS_NOISE, 0, 20);

	// Setting
	m_Btn_Setting.SetBitmaps(IDB_SETTING, RGB(255, 0, 255));

	// Reset
	m_Btn_Reset.SetShade(CShadeButtonST::SHS_NOISE, 0, 20);

	// Stall
	m_Btn_Stall.SetShade(CShadeButtonST::SHS_NOISE, 0, 20);

	pRemoteDlg->m_Btn_Reset.EnableWindow(FALSE);
	pRemoteDlg->m_Btn_Stall.EnableWindow(FALSE);

#if ECMSEARCHUSER
	m_Bt_ECMSearch.EnableWindow(TRUE);
#else
	m_Bt_ECMSearch.EnableWindow(FALSE);
#endif

// ----------------------------------------------------------------------------------------------------
// flag 초기화
	flag_close				= FALSE;

	m_ShowDlg_Server		= FALSE;
	m_ShowDlg_ECMSearch		= FALSE;
	m_ShowDlg_Downloader	= FALSE;
	m_ShowDlg_Parameter		= FALSE;
	m_ShowDlg_Viewer		= FALSE;
	m_ShowDlg_JTAGPrint0	= FALSE;
	m_ShowDlg_JTAGPrint1	= FALSE;
	m_ShowDlg_JTAGPrint		= FALSE;
	m_ShowDlg_JTAGDebugger	= FALSE;
	m_ShowDlg_Analyzer		= FALSE;
	m_ShowDlg_ISP			= FALSE;
	m_ShowDlg_Gamma			= FALSE;
	m_ShowDlg_ColorMap		= FALSE;
	m_ShowDlg_Key			= FALSE;
	m_ShowDlg_UartString	= FALSE;
	m_ShowDlg_Lua			= FALSE;
	m_ShowDlg_IPCamSearch	= FALSE;

	if(ReadIni(SEC_ECMREMOTE, KEY_SHOWSPECIAL, DEF_SHOWSPECIAL))	m_ShowSpecial_flag = TRUE;
	else															m_ShowSpecial_flag = FALSE;

	ShowSpecial(m_ShowSpecial_flag);
	
	server_flag = NULL;
	preserver_flag = NULL;

	// Server 실행
	//pRemoteDlg->m_Bt_Server.SetColor(CButtonST::BTNST_COLOR_BK_OUT, RGB(0xFF, 0x00, 0x00));
	//pRemoteDlg->m_Bt_Server.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(0xFF, 0x00, 0x00));

	OnBnClickedButtonServerstate();
	//m_Bt_EXROCD.EnableWindow(FALSE);

	Sleep(1000);

	GetIP();
	GetPort();
	CStringA addr;
	CStringA port;
	addr = Addr;
	port = Port;
	strcpy(ch_ip, addr.GetBuffer(addr.GetLength()));
	strcpy(ch_port, port.GetBuffer(port.GetLength()));

	ConnectSocket = NetCon(ch_ip, ch_port);
	if (ConnectSocket <= 0)
	{
		//AfxMessageBox(_T("Not Connect"));
		Sleep(100);
		//OnBnClickedButtonExroxdstate();
		//m_Bt_EXROCD.EnableWindow(FALSE);
		//exit(0);
	}

	// Connect Check Timer Set
#if 0
	Check_Timer_On();
#else
	pRemoteDlg->m_Bt_ServerState.SetColor(CButtonST::BTNST_COLOR_BK_OUT, RGB(0xFF, 0x02, 0x00));
	pRemoteDlg->m_Bt_ServerState.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(0xFF, 0x02, 0x00));
	Connect_Timer_On();
#endif
	wVersionRequested = MAKEWORD(2, 2);
	WSAStartup(wVersionRequested, &wsaData);

// ====================================================================================================
// 실행파일 동작 check & 버튼 활성화
	g_pExeState = AfxBeginThread(ExeState, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CECM_remoteDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	// 최소화
	if ((nID & 0xFFF0) == SC_MINIMIZE)
	{
		OnBnClickedButtonMinimize();
	}

	// 최소화 복원
	if ((nID & 0xFFF0) == SC_RESTORE)
	{
		// 외부 실행파일 최소화 복원
#if 0
		EXEControl(DLG_DOWNLOADER, BT_RESTORE);
		EXEControl(DLG_PARAMETER, BT_RESTORE);
		EXEControl(DLG_VIEWER, BT_RESTORE);
		EXEControl(DLG_JTAGPRINTCPU0, BT_RESTORE);
		EXEControl(DLG_JTAGPRINTCPU1, BT_RESTORE);
		EXEControl(DLG_JTAGDEBUGGER, BT_RESTORE);
		EXEControl(DLG_ANALYZE, BT_RESTORE);
		EXEControl(DLG_REG, BT_RESTORE);
		EXEControl(DLG_GAMMA, BT_RESTORE);
		EXEControl(DLG_COLORMAP, BT_RESTORE);
		EXEControl(DLG_KEY, BT_RESTORE);
		EXEControl(DLG_UARTSTRING, BT_RESTORE);
		EXEControl(DLG_LUA, BT_RESTORE);
		EXEControl(DLG_IPCAMSEARCH, BT_RESTORE);
#else
		EXEControl(ECMSearch, BT_RESTORE);
		EXEControl(Downloader, BT_RESTORE);
		EXEControl(Parameter, BT_RESTORE);
		EXEControl(Viewer, BT_RESTORE);
		EXEControl(JTAGPrintCPU0, BT_RESTORE);
		EXEControl(JTAGPrintCPU1, BT_RESTORE);
		EXEControl(JTAGDebugger, BT_RESTORE);
		EXEControl(Analyzer, BT_RESTORE);
		EXEControl(ISP, BT_RESTORE);
		EXEControl(Gamma, BT_RESTORE);
		EXEControl(ColorMap, BT_RESTORE);
		EXEControl(Key, BT_RESTORE);
		EXEControl(UartString, BT_RESTORE);
		EXEControl(Lua, BT_RESTORE);
		EXEControl(IPCamSearch, BT_RESTORE);
#endif
	}

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

BOOL CECM_remoteDlg::PreTranslateMessage(MSG* pMsg)
{
	switch (pMsg->wParam)
	{
	case VK_ESCAPE:
	case VK_RETURN:
		return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CECM_remoteDlg::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
#
	if (IsIconic())
	{
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
		// Top
		CRect rect;
		CWnd* pWnd = this;
		pWnd->GetWindowRect(rect);
		int iWidth = rect.Width();
		int iHeight = rect.Height();
		dc.FillSolidRect(0, 0, iWidth, 25, DIALOGCOLOR);

		// OutLine
		CPen NewPen(PS_SOLID, 2, DIALOGCOLOR);
		//CPen NewPen(PS_SOLID, 2, DIALOGOUTLINE);
		CPen* pOldPen = dc.SelectObject(&NewPen);
		/*
		dcBg.MoveTo(0,0);
		dcBg.LineTo(iWidth-1,0);
		dcBg.LineTo(iWidth-1,iHeight-1);
		dcBg.LineTo(0,iHeight-1);
		dcBg.LineTo(0,0);
		*/
		dc.MoveTo(1, 1);
		dc.LineTo(iWidth - 1, 1);
		dc.LineTo(iWidth - 1, iHeight - 1);
		dc.LineTo(1, iHeight - 1);
		dc.LineTo(1, 1);

		CPen NewPen2(PS_SOLID, 1, DIALOGOUTLINE);
		dc.SelectObject(NewPen2);

		dc.MoveTo(0, 0);
		dc.LineTo(iWidth - 1, 0);
		dc.LineTo(iWidth - 1, iHeight - 1);
		dc.LineTo(0, iHeight - 1);
		dc.LineTo(0, 0);

		dc.SelectObject(pOldPen);

		// logo
		CDC dcLogo;
		dcLogo.CreateCompatibleDC(&dc);

		CBitmap bmpLogo;
		bmpLogo.LoadBitmapW(IDB_ECM);

		CBitmap* pOldBitmap = dcLogo.SelectObject(&bmpLogo);

		dc.TransparentBlt(4, 5, 18, 18, &dcLogo, 0, 0, 18, 18, RGB(255, 0, 255));

		dcLogo.SelectObject(pOldBitmap);

		// Font
		LOGFONT lf;
		::ZeroMemory(&lf, sizeof(lf));
		lf.lfHeight = 15;
		lf.lfWeight = 700;
		wsprintf(lf.lfFaceName, _T("%s"), _T("Arial"));
		CFont NewFont;
		NewFont.CreateFontIndirectW(&lf);
		CFont* pOldFont = dc.SelectObject(&NewFont);

		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(TITLECOLOR);

		dc.TextOutW(30, 6, DLG_ECMREMOTE);
	}
}

int CECM_remoteDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	this->GetWindowRect(&initRect);
	initRect_Width = initRect.Width();
	initRect_Height = initRect.Height();


	SetWindowLongPtr(m_hWnd, GWL_STYLE, WS_SYSMENU | WS_MINIMIZEBOX);

	RedrawWindow();
	return 0;
}


// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CECM_remoteDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CECM_remoteDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetCapture();
	m_Point = point;

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CECM_remoteDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (this == GetCapture())
	{
		CRect rcDialog;
		GetWindowRect(&rcDialog);

		int x = rcDialog.left + point.x - m_Point.x;
		int y = rcDialog.top + point.y - m_Point.y;

		SetWindowPos(NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		WriteIni(SEC_WININFO, KEY_MAINDLGLEFT, x);
		WriteIni(SEC_WININFO, KEY_MAINDLGTOP, y);


		// ----------------------------------------------------------------------------------------------------
		// Set Sub Dialog
		CRect rectServer;
		CRect rectECMSearch;

		pCServerDlg->GetWindowRect(&rectServer);
		pCServerDlg->MoveWindow(rcDialog.right, rcDialog.top,
			rectServer.Width(), rectServer.Height(), TRUE);

#if ECMSEARCHUSER
		pCECMSearchDlg->GetWindowRect(&rectECMSearch);
		pCECMSearchDlg->MoveWindow(rectServer.left, rectServer.bottom,
			rectECMSearch.Width(), rectECMSearch.Height(), TRUE);
#endif

	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void CECM_remoteDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	ReleaseCapture();

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CECM_remoteDlg::OnBnClickedCancel()
{
	flag_close = TRUE;


	NetClo(ConnectSocket);
	ConnectSocket = NULL;

	// 외부 프로그램 종료
	DWORD exitcode = 0;
	int i;
	for (i = 0; i < MAUE_NUM + 1; i++)
	{
		if (m_sInfo[i].hProcess)
		{
			GetExitCodeProcess(m_sInfo[i].hProcess, &exitcode);
			if (exitcode == STILL_ACTIVE)
			{
				switch (i)
				{
				case Server:
					TerminateProcess(m_sInfo[i].hProcess, 0);
					ZeroMemory(&m_sInfo[i], sizeof(SHELLEXECUTEINFO));
					CloseHandle(m_sInfo[i].hProcess);
					SafeTerminateProcess(m_sInfo[i].hProcess, 0);
					break;
				case ECMSearch:
					pCECMSearchDlg->OnBnClickedCancel();
					//EXEControl(ECMSearch, BT_CLOSE);
					break;
				case Downloader :
					//EXEControl(DLG_DOWNLOADER, BT_CLOSE);
					EXEControl(Downloader, BT_CLOSE);
					break;
				case Parameter :
					//EXEControl(DLG_PARAMETER, BT_CLOSE);
					EXEControl(Parameter, BT_CLOSE);
					break;
				case Viewer :
					//EXEControl(DLG_VIEWER, BT_CLOSE);
					EXEControl(Viewer, BT_CLOSE);
					break;
				case JTAGPrintCPU0 :
					//EXEControl(DLG_JTAGPRINTCPU0, BT_CLOSE);
					EXEControl(JTAGPrintCPU0, BT_CLOSE);
					break;
				case JTAGPrintCPU1 :
					//EXEControl(DLG_JTAGPRINTCPU1, BT_CLOSE);
					EXEControl(JTAGPrintCPU1, BT_CLOSE);
					break;
				case JTAGDebugger :
					//EXEControl(DLG_JTAGDEBUGGER, BT_CLOSE);
					EXEControl(JTAGDebugger, BT_CLOSE);
					break;
				case Analyzer :
					//EXEControl(DLG_ANALYZE, BT_CLOSE);
					EXEControl(Analyzer, BT_CLOSE);
					break;
				case ISP :
					//EXEControl(DLG_REG, BT_CLOSE);
					EXEControl(ISP, BT_CLOSE);
					break;
				case Gamma :
					//EXEControl(DLG_GAMMA, BT_CLOSE);
					EXEControl(Gamma, BT_CLOSE);
					break;
				case ColorMap :
					//EXEControl(DLG_COLORMAP, BT_CLOSE);
					EXEControl(ColorMap, BT_CLOSE);
					break;
				case Key :
					//EXEControl(DLG_KEY, BT_CLOSE);
					EXEControl(Key, BT_CLOSE);
					break;
				case UartString :
					//EXEControl(DLG_UARTSTRING, BT_CLOSE);
					EXEControl(UartString, BT_CLOSE);
					break;
				case Lua :
					//EXEControl(DLG_LUA, BT_CLOSE);
					EXEControl(Lua, BT_CLOSE);
					break;
				case IPCamSearch:
					//EXEControl(DLG_IPCAMSEARCH, BT_CLOSE);
					EXEControl(IPCamSearch, BT_CLOSE);
					break;
				}
			}
		}
	}

	// ini 저장
	GetIP();
	GetPort();
	m_pDlg_Server->m_Edit_ServerCommand.GetWindowTextW(Command);

	WriteIni(SEC_ECMREMOTE, KEY_IPADDR, Addr);
	WriteIni(SEC_ECMREMOTE, KEY_PORT, Port);
	WriteIni(SEC_ECMREMOTE, KEY_COMMAND, Command);
	WriteIni(SEC_ECMREMOTE, KEY_SHOWSPECIAL, (int)m_ShowSpecial_flag);

	m_pDlg_Server->OnBnClickedCancel();
	m_pDlg_Server->DestroyWindow();
	delete m_pDlg_Server;

#if ECMSEARCHUSER
	m_pDlg_ECMSearch->OnBnClickedCancel();
	m_pDlg_ECMSearch->DestroyWindow();
	delete m_pDlg_ECMSearch;
#endif

	WSACleanup();

	CDialogEx::OnCancel();
}

void CECM_remoteDlg::OnBnClickedButtonMinimize()
{
	// 외부 실행파일 최소화
#if 1
#if 0
	EXEControl(DLG_DOWNLOADER, BT_MINIMIZE);
	EXEControl(DLG_PARAMETER, BT_MINIMIZE);
	EXEControl(DLG_VIEWER, BT_MINIMIZE);
	EXEControl(DLG_JTAGPRINTCPU0, BT_MINIMIZE);
	EXEControl(DLG_JTAGPRINTCPU1, BT_MINIMIZE);
	EXEControl(DLG_JTAGDEBUGGER, BT_MINIMIZE);
	EXEControl(DLG_ANALYZE, BT_MINIMIZE);
	EXEControl(DLG_REG, BT_MINIMIZE);
	EXEControl(DLG_GAMMA, BT_MINIMIZE);
	EXEControl(DLG_COLORMAP, BT_MINIMIZE);
	EXEControl(DLG_KEY, BT_MINIMIZE);
	EXEControl(DLG_UARTSTRING, BT_MINIMIZE);
	EXEControl(DLG_LUA, BT_MINIMIZE);
	EXEControl(DLG_IPCAMSEARCH, BT_MINIMIZE);
#else
	EXEControl(ECMSearch, BT_MINIMIZE);
	EXEControl(Downloader, BT_MINIMIZE);
	EXEControl(Parameter, BT_MINIMIZE);
	EXEControl(Viewer, BT_MINIMIZE);
	EXEControl(JTAGPrintCPU0, BT_MINIMIZE);
	EXEControl(JTAGPrintCPU1, BT_MINIMIZE);
	EXEControl(JTAGDebugger, BT_MINIMIZE);
	EXEControl(Analyzer, BT_MINIMIZE);
	EXEControl(ISP, BT_MINIMIZE);
	EXEControl(Gamma, BT_MINIMIZE);
	EXEControl(ColorMap, BT_MINIMIZE);
	EXEControl(Key, BT_MINIMIZE);
	EXEControl(UartString, BT_MINIMIZE);
	EXEControl(Lua, BT_MINIMIZE);
	EXEControl(IPCamSearch, BT_MINIMIZE);
#endif
#endif
	// 최소화
	ShowWindow(SW_MINIMIZE);
}


void CECM_remoteDlg::OnBnClickedButtonServer()
{ 
	if (!m_ShowDlg_Server)
	{
		CRect rectThis;
		CRect rectSet;

		this->GetWindowRect(&rectThis);
		pCServerDlg->GetWindowRect(&rectSet);

		//pCServerDlg->MoveWindow(rectThis.right, rectThis.top, rectSet.Width(), rectSet.Height(), TRUE);
		pCServerDlg->SetWindowPos(NULL, rectThis.right, rectThis.top, rectSet.Width(), rectSet.Height(), NULL);

		pCServerDlg->ShowWindow(SW_SHOW);
		m_ShowDlg_Server = TRUE;
	}
	else
	{
		pCServerDlg->OnBnClickedCancel();
		m_ShowDlg_Server = FALSE;
	}
}


void CECM_remoteDlg::OnBnClickedButtonServerstate()
{
	Connect_Timer_Off();
	pCServerDlg->OnBnClickedServerrun();
	Connect_Timer_On();
}


void CECM_remoteDlg::OnBnClickedButtonEcmsearch()
{
#if 0
	if (m_ShowDlg_ECMSearch)
	{
		//EXEControl(DLG_DOWNLOADER, BT_CLOSE);
		EXEControl(ECMSearch, BT_CLOSE);
		ActiveCtrl(ECMSearch, FALSE);
	}
	else
	{
		int err;

		// ECMSearch.exe 실행
		err = ExeFunc(ECMSearch, ECMSEARCH);
		if (err < 0)
		{
			AfxMessageBox(_T("ECMSearch.exe Fail"));
			return;
		}

		ActiveCtrl(ECMSearch, TRUE);

		// 버튼 비활성화
		//EnableCtrl(ECMSearch, FALSE);
	}
#else
	if (m_ShowDlg_ECMSearch)
	{
		//pCECMSearchDlg->OnBnClickedCancel();
		pCECMSearchDlg->ShowWindow(SW_HIDE);
		ActiveCtrl(ECMSearch, FALSE);
		//m_ShowDlg_ECMSearch = FALSE;
	}
	else
	{

		//ActiveCtrl(ECMSearch, TRUE);
		CRect rectThis;
		CRect recServer;
		CRect rectSet;

		this->GetWindowRect(&rectThis);
		pCServerDlg->GetWindowRect(&recServer);
		pCECMSearchDlg->GetWindowRect(&rectSet);

		//pCECMSearchDlg->MoveWindow(rectSet.left, recExrocd.bottom, rectSet.Width(), rectSet.Height(), TRUE);
		pCECMSearchDlg->SetWindowPos(NULL, rectThis.right, rectThis.top + recServer.Height(), rectSet.Width(), rectSet.Height(), NULL);

		pCECMSearchDlg->ShowWindow(SW_SHOW);
		ActiveCtrl(ECMSearch, TRUE);
		//m_ShowDlg_ECMSearch = TRUE;

	}
#endif
}


void CECM_remoteDlg::OnBnClickedButtonDownloader()
{
	if (m_ShowDlg_Downloader)
	{
		//EXEControl(DLG_DOWNLOADER, BT_CLOSE);
		EXEControl(Downloader, BT_CLOSE);
		ActiveCtrl(Downloader, FALSE);
	}
	else
	{
		int err;
		// IP Address 얻기
		err = GetIP();
		if (err < 0)
		{
			AfxMessageBox(_T("Check the IP."));
			return;
		}

		// PORT 번호 얻기
		err = GetPort();
		if (err < 0)
		{
			AfxMessageBox(_T("Check the Port Number."));
			return;
		}

		// Downloader.exe 실행
		err = ExeFunc(Downloader, DOWNLOADER);
		if (err < 0)
		{
			AfxMessageBox(_T("Downloader.exe Fail"));
			return;
		}

		ActiveCtrl(Downloader, TRUE);
		
		// 버튼 비활성화
		//EnableCtrl(Downloader, FALSE);
	}
}


void CECM_remoteDlg::OnBnClickedButtonParameter()
{
	if (m_ShowDlg_Parameter)
	{
		//EXEControl(DLG_PARAMETER, BT_CLOSE);
		EXEControl(Parameter, BT_CLOSE);
		ActiveCtrl(Parameter, FALSE);
	}
	else
	{
		int err;
		// IP Address 얻기
		err = GetIP();
		if (err < 0)
		{
			AfxMessageBox(_T("Check the IP."));
			return;
		}

		// PORT 번호 얻기
		err = GetPort();
		if (err < 0)
		{
			AfxMessageBox(_T("Check the Port Number."));
			return;
		}

		// Parameter.exe 실행
		err = ExeFunc(Parameter, PARAMETER);
		if (err < 0)
		{
			AfxMessageBox(_T("Parameter.exe Fail"));
			return;
		}

		ActiveCtrl(Parameter, TRUE);

		// 버튼 비활성화
		//EnableCtrl(Parameter, FALSE);
	}
}


void CECM_remoteDlg::OnBnClickedButtonViewer()
{
	if (m_ShowDlg_Viewer)
	{
		//EXEControl(DLG_VIEWER, BT_CLOSE);
		EXEControl(Viewer, BT_CLOSE);
		ActiveCtrl(Viewer, FALSE);
	}
	else
	{
		int err;
		// IP Address 얻기
		err = GetIP();
		if (err < 0)
		{
			AfxMessageBox(_T("Check the IP."));
			return;
		}

		// PORT 번호 얻기
		err = GetPort();
		if (err < 0)
		{
			AfxMessageBox(_T("Check the Port Number."));
			return;
		}

		// Viewer.exe 실행
		err = ExeFunc(Viewer, VIEWER);
		if (err < 0)
		{
			AfxMessageBox(_T("Viewer.exe Fail"));
			return;
		}

		ActiveCtrl(Viewer, TRUE);

		// 버튼 비활성화
		//EnableCtrl(Viewer, FALSE);
	}
}


void CECM_remoteDlg::OnBnClickedButtonJtagprint0()
{
	if (m_ShowDlg_JTAGPrint0)
	{
		//EXEControl(DLG_JTAGPRINTCPU0, BT_CLOSE);
		EXEControl(JTAGPrintCPU0, BT_CLOSE);
		ActiveCtrl(JTAGPrintCPU0, FALSE);
	}
	else
	{
		int err;
		// IP Address 얻기
		err = GetIP();
		if (err < 0)
		{
			AfxMessageBox(_T("Check the IP."));
			return;
		}

		// PORT 번호 얻기
		err = GetPort();
		if (err < 0)
		{
			AfxMessageBox(_T("Check the Port Number."));
			return;
		}

		err = ExeFunc(JTAGPrintCPU0, JTAGPRINTCPU0);
		if (err < 0)
		{
			AfxMessageBox(_T("JTAGPrintCPU0.exe Fail"));
			return;
		}

		ActiveCtrl(JTAGPrintCPU0, TRUE);

		// 버튼 비활성화
		//EnableCtrl(JTAGPrintCPU0, FALSE);m_ShowDlg_JTAGPrint1
	}
}


void CECM_remoteDlg::OnBnClickedButtonJtagprint1()
{
	if (m_ShowDlg_JTAGPrint1)
	{
		//EXEControl(DLG_JTAGPRINTCPU1, BT_CLOSE);
		EXEControl(JTAGPrintCPU1, BT_CLOSE);
		ActiveCtrl(JTAGPrintCPU1, FALSE);
	}
	else
	{
		int err;
		// IP Address 얻기
		err = GetIP();
		if (err < 0)
		{
			AfxMessageBox(_T("Check the IP."));
			return;
		}

		// PORT 번호 얻기
		err = GetPort();
		if (err < 0)
		{
			AfxMessageBox(_T("Check the Port Number."));
			return;
		}

		// JTAGPrint.exe 실행
		err = ExeFunc(JTAGPrintCPU1, JTAGPRINTCPU1);
		if (err < 0)
		{
			AfxMessageBox(_T("JTAGPrintCPU1.exe Fail"));
			return;
		}

		ActiveCtrl(JTAGPrintCPU1, TRUE);

		// 버튼 비활성화
		//EnableCtrl(JTAGPrintCPU1, FALSE);
	}
}


void CECM_remoteDlg::OnBnClickedButtonJtagprint()
{
	if (m_ShowDlg_JTAGPrint0 && m_ShowDlg_JTAGPrint1)
	{
		OnBnClickedButtonJtagprint0();
		Sleep(10);
		OnBnClickedButtonJtagprint1();
	}
	else
	{
		if (!m_ShowDlg_JTAGPrint0)
			OnBnClickedButtonJtagprint0();
		if (!m_ShowDlg_JTAGPrint1)
			OnBnClickedButtonJtagprint1();
	}
}


void CECM_remoteDlg::OnBnClickedButtonDebugger()
{
	if (m_ShowDlg_JTAGDebugger)
	{
		//EXEControl(DLG_JTAGDEBUGGER, BT_CLOSE);
		EXEControl(JTAGDebugger, BT_CLOSE);
		ActiveCtrl(JTAGDebugger, FALSE);
	}
	else
	{
		int err;
		// IP Address 얻기
		err = GetIP();
		if (err < 0)
		{
			AfxMessageBox(_T("Check the IP."));
			return;
		}

		// PORT 번호 얻기
		err = GetPort();
		if (err < 0)
		{
			AfxMessageBox(_T("Check the Port Number."));
			return;
		}

		// JTAGDebugger.exe 실행
		err = ExeFunc(JTAGDebugger, JTAGDEBUGGER);
		if (err < 0)
		{
			AfxMessageBox(_T("JTAGDebugger.exe Fail"));
			return;
		}

		ActiveCtrl(JTAGDebugger, TRUE);

		// 버튼 비활성화
		//EnableCtrl(JTAGDebugger, FALSE);
	}
}


void CECM_remoteDlg::OnBnClickedButtonAnalyzer()
{
	if (m_ShowDlg_Analyzer)
	{
		//EXEControl(DLG_ANALYZE, BT_CLOSE);
		EXEControl(Analyzer, BT_CLOSE);
		ActiveCtrl(Analyzer, FALSE);
	}
	else
	{
		int err;
		// IP Address 얻기
		err = GetIP();
		if (err < 0)
		{
			AfxMessageBox(_T("Check the IP."));
			return;
		}

		// PORT 번호 얻기
		err = GetPort();
		if (err < 0)
		{
			AfxMessageBox(_T("Check the Port Number."));
			return;
		}

		// Analyze.exe 실행
		err = ExeFunc(Analyzer, ANALYZER);
		if (err < 0)
		{
			AfxMessageBox(_T("Analyzer.exe Fail"));
			return;
		}

		ActiveCtrl(Analyzer, TRUE);

		// 버튼 비활성화
		//EnableCtrl(Analyzer, FALSE);
	}
}


void CECM_remoteDlg::OnBnClickedButtonIsp()
{
	if (m_ShowDlg_ISP)
	{
		//EXEControl(DLG_REG, BT_CLOSE);
		EXEControl(ISP, BT_CLOSE);
		ActiveCtrl(ISP, FALSE);
	}
	else
	{
		int err;
		// IP Address 얻기
		err = GetIP();
		if (err < 0)
		{
			AfxMessageBox(_T("Check the IP."));
			return;
		}

		// PORT 번호 얻기
		err = GetPort();
		if (err < 0)
		{
			AfxMessageBox(_T("Check the Port Number."));
			return;
		}

		// ISP.exe 실행
		err = ExeFunc(ISP, ISPCONTROL);
		if (err < 0)
		{
			AfxMessageBox(_T("ISP.exe Fail"));
			return;
		}

		ActiveCtrl(ISP, TRUE);

		// 버튼 비활성화
		//EnableCtrl(ISP, FALSE);
	}
}


void CECM_remoteDlg::OnBnClickedButtonGamma()
{
	if (m_ShowDlg_Gamma)
	{
		//EXEControl(DLG_GAMMA, BT_CLOSE);
		EXEControl(Gamma, BT_CLOSE);
		ActiveCtrl(Gamma, FALSE);
	}
	else
	{
		int err;
		// IP Address 얻기
		err = GetIP();
		if (err < 0)
		{
			AfxMessageBox(_T("Check the IP."));
			return;
		}

		// PORT 번호 얻기
		err = GetPort();
		if (err < 0)
		{
			AfxMessageBox(_T("Check the Port Number."));
			return;
		}

		// Gamma.exe 실행
		err = ExeFunc(Gamma, GAMMA);
		if (err < 0)
		{
			AfxMessageBox(_T("Gamma.exe Fail"));
			return;
		}

		ActiveCtrl(Gamma, TRUE);

		// 버튼 비활성화
		//EnableCtrl(Gamma, FALSE);
	}
}


void CECM_remoteDlg::OnBnClickedButtonColormap()
{
	if (m_ShowDlg_ColorMap)
	{
		//EXEControl(DLG_COLORMAP, BT_CLOSE);
		EXEControl(ColorMap, BT_CLOSE);
		ActiveCtrl(ColorMap, FALSE);
	}
	else
	{
		int err;
		// IP Address 얻기
		err = GetIP();
		if (err < 0)
		{
			AfxMessageBox(_T("Check the IP."));
			return;
		}

		// PORT 번호 얻기
		err = GetPort();
		if (err < 0)
		{
			AfxMessageBox(_T("Check the Port Number."));
			return;
		}

		// ColorMap.exe 실행
		err = ExeFunc(ColorMap, COLORMAP);
		if (err < 0)
		{
			AfxMessageBox(_T("Color Map.exe Fail"));
			return;
		}

		ActiveCtrl(ColorMap, TRUE);

		// 버튼 비활성화
		//EnableCtrl(ColorMap, FALSE);
	}
}


void CECM_remoteDlg::OnBnClickedButtonKey()
{
	if (m_ShowDlg_Key)
	{
		//EXEControl(DLG_KEY, BT_CLOSE);
		EXEControl(Key, BT_CLOSE);
		ActiveCtrl(Key, FALSE);
	}
	else
	{
		int err;
		// IP Address 얻기
		err = GetIP();
		if (err < 0)
		{
			AfxMessageBox(_T("Check the IP."));
			return;
		}

		// PORT 번호 얻기
		err = GetPort();
		if (err < 0)
		{
			AfxMessageBox(_T("Check the Port Number."));
			return;
		}

		// Key.exe 실행
		err = ExeFunc(Key, KEY);
		if (err < 0)
		{
			AfxMessageBox(_T("Key.exe Fail"));
			return;
		}

		ActiveCtrl(Key, TRUE);

		// 버튼 비활성화
		//EnableCtrl(Key, FALSE);
	}
}


void CECM_remoteDlg::OnBnClickedButtonUartstring()
{
	if (m_ShowDlg_UartString)
	{
		//EXEControl(DLG_UARTSTRING, BT_CLOSE);
		EXEControl(UartString, BT_CLOSE);
		ActiveCtrl(UartString, FALSE);
	}
	else
	{
		int err;

		// UARTString.exe 실행
		err = ExeFunc(UartString, UARTSTRING);
		if (err < 0)
		{
			AfxMessageBox(_T("UARTString.exe Fail"));
			return;
		}

		ActiveCtrl(UartString, TRUE);

		// 버튼 비활성화
		//EnableCtrl(Key, FALSE);
	}
}


void CECM_remoteDlg::OnBnClickedButtonLua()
{
	if (m_ShowDlg_Lua)
	{
		//EXEControl(DLG_LUA, BT_CLOSE);
		EXEControl(Lua, BT_CLOSE);
		ActiveCtrl(Lua, FALSE);
	}
	else
	{
		int err;

		// Lua.exe 실행
		err = ExeFunc(Lua, LUA);
		if (err < 0)
		{
			AfxMessageBox(_T("Lua.exe Fail"));
			return;
		}

		ActiveCtrl(Lua, TRUE);

		// 버튼 비활성화
		//EnableCtrl(Key, FALSE);
	}
}


void CECM_remoteDlg::OnBnClickedButtonIpcamsearch()
{
	if (m_ShowDlg_IPCamSearch)
	{
		//EXEControl(DLG_IPCAMSEARCH, BT_CLOSE);
		EXEControl(IPCamSearch, BT_CLOSE);
		ActiveCtrl(IPCamSearch, FALSE);
	}
	else
	{
		int err;

		// IPCamSearch.exe 실행
		err = ExeFunc(IPCamSearch, IPCAMSEARCH);
		if (err < 0)
		{
			AfxMessageBox(_T("IPCamSearch.exe Fail"));
			return;
		}

		ActiveCtrl(IPCamSearch, TRUE);

		// 버튼 비활성화
		//EnableCtrl(Key, FALSE);
	}
}


void CECM_remoteDlg::OnBnClickedButtonShspecial()
{
	ShowSpecial(!m_ShowSpecial_flag);
}


void CECM_remoteDlg::OnBnClickedButtonSetting()
{
	CSettingDlg	m_SettingDlg;
	INT_PTR nResponse = m_SettingDlg.DoModal();
}


void CECM_remoteDlg::OnBnClickedButtonReset()
{
	sendMsg(ConnectSocket, "rem_rst ");
}


void CECM_remoteDlg::OnBnClickedButtonStall()
{
	int state = 0;
	state = sendMsg(ConnectSocket, "rem_st ");
	if (state < 0)
	{
		NetClo(ConnectSocket);
		ConnectSocket = NULL;
	}
}


CString CECM_remoteDlg::GetMyIPAddress()
{
	char name[255];
	CString ip; // 여기에 lcoal ip가 저장됩니다.
	PHOSTENT hostinfo;

	//WORD wVersionRequested;
	//WSADATA wsaData;
	//wVersionRequested = MAKEWORD(2, 2);
	if (WSAStartup(wVersionRequested, &wsaData) == 0)
	{
		if (gethostname(name, sizeof(name)) == 0)
		{
			if ((hostinfo = gethostbyname(name)) != NULL)
			{
				ip = inet_ntoa(*(struct in_addr *)*hostinfo->h_addr_list);
			}
		}
		//WSACleanup();
	}

	return ip;
}


int CECM_remoteDlg::GetIP()
{
	int err;
	err = m_ctrlIPAddr.GetAddress(IP[0], IP[1], IP[2], IP[3]);
	if (err < 4)
	{
		if (flag_close)
			Addr.Format(_T("%d.%d.%d.%d"), 0, 0, 0, 0);
		else
			AfxMessageBox(_T("Please, enter IP."));
		return -1;
	}
	else
	{
		Addr.Format(_T("%d.%d.%d.%d"), IP[0], IP[1], IP[2], IP[3]);
		return 0;
	}
}

int CECM_remoteDlg::GetPort()
{
	m_Edit_Port.GetWindowTextW(Port);
	if (Port == _T(""))
	{
		if (!flag_close)
			AfxMessageBox(_T("Please, enter Port."));
		return -1;
	}
	return 0;
}


// ====================================================================================================
// ExeFunc
// ----------------------------------------------------------------------------------------------------
// EXE 파일 실행
// ====================================================================================================
int CECM_remoteDlg::ExeFunc(int func, const CString& strTitle)
{
	CString strNowPath = GetNowPath();
	CString strUsbdosPath = strTitle;
	strUsbdosPath = RelativeToAbsolute(strUsbdosPath, strNowPath); // 상대경로 -> 절대경로
	strUsbdosPath.Replace(_T("\\"), _T("/"));
	GetIP();
	GetPort();

	// 전달 인자
	//if (func == Exrocd)		pCExrocdDlg->m_Edit_ServerCommand.GetWindowTextW(Command);	// command = _T("ft2232");  //command = _T("-d bsdl ft2232");
	if (func == Server)
	{
		//pCExrocdDlg->m_Edit_ServerCommand.GetWindowTextW(Command);
		Command = _T("");
		int clkdiv = ReadIni(SEC_SETTING, KEY_JTAGCLKDIV, DEF_JTAGCLKDIV);
		CString str_clkdiv = _T("");
		str_clkdiv.Format(_T(" %d "), clkdiv);
		if (pCServerDlg->m_Radio_ChA.GetCheck())
			Command = Port + str_clkdiv + _T("A");
		if (pCServerDlg->m_Radio_ChB.GetCheck())
			Command = Port + str_clkdiv + _T("B");
	}
	else					
		Command = Addr + _T(" ") + Port;

	ZeroMemory(&m_sInfo[func], sizeof(SHELLEXECUTEINFO));
	m_sInfo[func].cbSize = sizeof(SHELLEXECUTEINFO);
	m_sInfo[func].lpFile = strUsbdosPath;				//프로세스 경로
	m_sInfo[func].lpParameters = Command;				//전달 인자
#if 1
	if (func == Server)
	{
		if (ReadIni(SEC_SETTING, KEY_EXROCD, DEF_EXROCD))
			m_sInfo[func].nShow = SW_HIDE;				//실행시 최소화
		else
			m_sInfo[func].nShow = SW_SHOWNORMAL;
	}
	else
#endif
		m_sInfo[func].nShow = SW_SHOWNORMAL;
	m_sInfo[func].lpVerb = _T("open");					//_T("runas"); //관리자 권한 실행
	m_sInfo[func].fMask = SEE_MASK_NOCLOSEPROCESS;		//프로세스 핸들값 사용

	if (ShellExecuteEx(&m_sInfo[func]))
	{
		TRACE("ShellExecuteEx Success\n");
		return 0;
	}
	else
	{
		TRACE("ShellExecuteEx Failed\n");
		return -1;
	}
}


void CECM_remoteDlg::InitEnableCtrl()
{
	CFileStatus status;
	CString strNowPath = GetNowPath();
	CString strUsbdosPath;
	
	BOOL cpu0 = FALSE;
	BOOL cpu1 = FALSE;
	
	// SERVER
	strUsbdosPath = SERVER;
	strUsbdosPath = RelativeToAbsolute(strUsbdosPath, strNowPath); // 상대경로 -> 절대경로
	if (CFile::GetStatus(strUsbdosPath, status))
	{
		m_Bt_Server.EnableWindow(TRUE);
		m_Bt_ServerState.EnableWindow(TRUE);
	}
	else
	{
		m_Bt_Server.EnableWindow(FALSE);
		m_Bt_ServerState.EnableWindow(FALSE);
	}

	// ECM Search
	strUsbdosPath = ECMSEARCH;
	strUsbdosPath = RelativeToAbsolute(strUsbdosPath, strNowPath); // 상대경로 -> 절대경로
	if (CFile::GetStatus(strUsbdosPath, status))		m_Bt_ECMSearch.EnableWindow(TRUE);
	else												m_Bt_ECMSearch.EnableWindow(FALSE);

	// DOWNLOADER
	strUsbdosPath = DOWNLOADER;
	strUsbdosPath = RelativeToAbsolute(strUsbdosPath, strNowPath); // 상대경로 -> 절대경로
	if (CFile::GetStatus(strUsbdosPath, status))		m_Bt_Downloader.EnableWindow(TRUE);
	else												m_Bt_Downloader.EnableWindow(FALSE);

	// PARAMETER
	strUsbdosPath = PARAMETER;
	strUsbdosPath = RelativeToAbsolute(strUsbdosPath, strNowPath); // 상대경로 -> 절대경로
	if (CFile::GetStatus(strUsbdosPath, status))		m_Bt_Parameter.EnableWindow(TRUE);
	else												m_Bt_Parameter.EnableWindow(FALSE);
	
	// VIEWER
	strUsbdosPath = VIEWER;
	strUsbdosPath = RelativeToAbsolute(strUsbdosPath, strNowPath); // 상대경로 -> 절대경로
	if (CFile::GetStatus(strUsbdosPath, status))		m_Bt_Viewer.EnableWindow(TRUE);
	else												m_Bt_Viewer.EnableWindow(FALSE);
	
	// JTAGPRINTCPU0
	strUsbdosPath = JTAGPRINTCPU0;
	strUsbdosPath = RelativeToAbsolute(strUsbdosPath, strNowPath); // 상대경로 -> 절대경로
	if (CFile::GetStatus(strUsbdosPath, status))
	{
		m_Bt_JTAGPrint0.EnableWindow(TRUE);
		cpu0 = TRUE;
	}
	else												m_Bt_JTAGPrint0.EnableWindow(FALSE);

	// JTAGPRINTCPU1
	strUsbdosPath = JTAGPRINTCPU1;
	strUsbdosPath = RelativeToAbsolute(strUsbdosPath, strNowPath); // 상대경로 -> 절대경로
	if (CFile::GetStatus(strUsbdosPath, status))
	{
		m_Bt_JTAGPrint1.EnableWindow(TRUE);
		cpu1 = TRUE;
	}
	else												m_Bt_JTAGPrint1.EnableWindow(FALSE);
	
	// JTAGPRINT
	if (cpu0 && cpu1)									m_Bt_JTAGPrint.EnableWindow(TRUE);
	else												m_Bt_JTAGPrint.EnableWindow(FALSE);


	// JTAGDEBUGGER
	strUsbdosPath = JTAGDEBUGGER;
	strUsbdosPath = RelativeToAbsolute(strUsbdosPath, strNowPath); // 상대경로 -> 절대경로
	if (CFile::GetStatus(strUsbdosPath, status))		m_Bt_JTAGDebugger.EnableWindow(TRUE);
	else												m_Bt_JTAGDebugger.EnableWindow(FALSE);

	// ANALYZER
	strUsbdosPath = ANALYZER;
	strUsbdosPath = RelativeToAbsolute(strUsbdosPath, strNowPath); // 상대경로 -> 절대경로
	if (CFile::GetStatus(strUsbdosPath, status))		m_Bt_Analyzer.EnableWindow(TRUE);
	else												m_Bt_Analyzer.EnableWindow(FALSE);

	// ISPCONTROL
	strUsbdosPath = ISPCONTROL;
	strUsbdosPath = RelativeToAbsolute(strUsbdosPath, strNowPath); // 상대경로 -> 절대경로
	if (CFile::GetStatus(strUsbdosPath, status))		m_Bt_ISP.EnableWindow(TRUE);
	else												m_Bt_ISP.EnableWindow(FALSE);

	// GAMMA
	strUsbdosPath = GAMMA;
	strUsbdosPath = RelativeToAbsolute(strUsbdosPath, strNowPath); // 상대경로 -> 절대경로
	if (CFile::GetStatus(strUsbdosPath, status))		m_Bt_Gamma.EnableWindow(TRUE);
	else												m_Bt_Gamma.EnableWindow(FALSE);

	// COLORMAP
	strUsbdosPath = COLORMAP;
	strUsbdosPath = RelativeToAbsolute(strUsbdosPath, strNowPath); // 상대경로 -> 절대경로
	if (CFile::GetStatus(strUsbdosPath, status))		m_Bt_ColorMap.EnableWindow(TRUE);
	else												m_Bt_ColorMap.EnableWindow(FALSE);

	// KEY
	strUsbdosPath = KEY;
	strUsbdosPath = RelativeToAbsolute(strUsbdosPath, strNowPath); // 상대경로 -> 절대경로
	if (CFile::GetStatus(strUsbdosPath, status))		m_Bt_Key.EnableWindow(TRUE);
	else												m_Bt_Key.EnableWindow(FALSE);

	// UARTSTRING
	strUsbdosPath = UARTSTRING;
	strUsbdosPath = RelativeToAbsolute(strUsbdosPath, strNowPath); // 상대경로 -> 절대경로
	if (CFile::GetStatus(strUsbdosPath, status))		m_Bt_UartString.EnableWindow(TRUE);
	else												m_Bt_UartString.EnableWindow(FALSE);

	// LUA
	strUsbdosPath = LUA;
	strUsbdosPath = RelativeToAbsolute(strUsbdosPath, strNowPath); // 상대경로 -> 절대경로
	if (CFile::GetStatus(strUsbdosPath, status))		m_Bt_Lua.EnableWindow(TRUE);
	else												m_Bt_Lua.EnableWindow(FALSE);
	
	// IPCAMSEARCH
	strUsbdosPath = IPCAMSEARCH;
	strUsbdosPath = RelativeToAbsolute(strUsbdosPath, strNowPath); // 상대경로 -> 절대경로
	if (CFile::GetStatus(strUsbdosPath, status))		m_Bt_IPCamSearch.EnableWindow(TRUE);
	else												m_Bt_IPCamSearch.EnableWindow(FALSE);
}


void CECM_remoteDlg::EnableCtrl(int i, BOOL state)
{
	switch (i)
	{
	case Server:
		m_CServerDlg = FALSE;
		pCServerDlg->m_Btn_ServerRun.SetWindowTextW(_T("Run"));
		//pCServerDlg->m_Btn_ServerRun.EnableWindow(state);
		pRemoteDlg->m_Bt_Server.EnableWindow(state);
		// SERVER 동작 확인
		pRemoteDlg->m_Bt_ServerState.SetColor(CButtonST::BTNST_COLOR_BK_OUT, RGB(0xFF, 0x00, 0x00));
		pRemoteDlg->m_Bt_ServerState.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(0xFF, 0x00, 0x00));
		// PORT & Server IP 활성화
		pRemoteDlg->m_Edit_Port.EnableWindow(TRUE);
		pRemoteDlg->m_ctrlIPAddr.EnableWindow(TRUE);
		break;
	case ECMSearch:
		pRemoteDlg->m_Bt_ECMSearch.EnableWindow(state);
		break;
	case Downloader:
		pRemoteDlg->m_Bt_Downloader.EnableWindow(state);
		break;
	case Parameter:
		pRemoteDlg->m_Bt_Parameter.EnableWindow(state);
		break;
	case Viewer:
		pRemoteDlg->m_Bt_Viewer.EnableWindow(state);
		break;
	case JTAGPrintCPU0:
		pRemoteDlg->m_Bt_JTAGPrint0.EnableWindow(state);
		break;
	case JTAGPrintCPU1:
		pRemoteDlg->m_Bt_JTAGPrint1.EnableWindow(state);
		break;
	case JTAGDebugger:
		pRemoteDlg->m_Bt_JTAGDebugger.EnableWindow(state);
		break;
	case Analyzer:
		pRemoteDlg->m_Bt_Analyzer.EnableWindow(state);
		break;
	case ISP:
		pRemoteDlg->m_Bt_ISP.EnableWindow(state);
		break;
	case Gamma:
		pRemoteDlg->m_Bt_Gamma.EnableWindow(state);
		break;
	case ColorMap:
		pRemoteDlg->m_Bt_ColorMap.EnableWindow(state);
		break;
	case Key:
		pRemoteDlg->m_Bt_Key.EnableWindow(state);
		break;
	case UartString:
		pRemoteDlg->m_Bt_UartString.EnableWindow(state);
		break;
	case Lua:
		pRemoteDlg->m_Bt_Lua.EnableWindow(state);
		break;
	case IPCamSearch:
		pRemoteDlg->m_Bt_IPCamSearch.EnableWindow(state);
		break;
	}
}


void CECM_remoteDlg::ActiveCtrl(int i, BOOL state)
{
	switch (i)
	{
	case Server:
		m_ShowDlg_Server = state;
		if (state)
			m_Bt_Server.SetShade(CShadeButtonST::SHS_NOISE, 0, 20, 15, DIALOGBTNCOLOR);
		else
			m_Bt_Server.SetShade(CShadeButtonST::SHS_NOISE, 0, 20);
		break;
	case ECMSearch:
		m_ShowDlg_ECMSearch = state;
		if (state)
			m_Bt_ECMSearch.SetShade(CShadeButtonST::SHS_NOISE, 0, 20, 15, DIALOGBTNCOLOR);
		else
			m_Bt_ECMSearch.SetShade(CShadeButtonST::SHS_NOISE, 0, 20);
		break;
	case Downloader:
		m_ShowDlg_Downloader = state;
		if (state)
			m_Bt_Downloader.SetShade(CShadeButtonST::SHS_NOISE, 0, 20, 15, DIALOGBTNCOLOR);
		else
			m_Bt_Downloader.SetShade(CShadeButtonST::SHS_NOISE, 0, 20);
		break;
	case Parameter:
		m_ShowDlg_Parameter = state;
		if (state)
			m_Bt_Parameter.SetShade(CShadeButtonST::SHS_NOISE, 0, 20, 15, DIALOGBTNCOLOR);
		else
			m_Bt_Parameter.SetShade(CShadeButtonST::SHS_NOISE, 0, 20);
		break;
	case Viewer:
		m_ShowDlg_Viewer = state;
		if (state)
			m_Bt_Viewer.SetShade(CShadeButtonST::SHS_NOISE, 0, 20, 15, DIALOGBTNCOLOR);
		else
			m_Bt_Viewer.SetShade(CShadeButtonST::SHS_NOISE, 0, 20);
		break;
	case JTAGPrintCPU0:
		m_ShowDlg_JTAGPrint0 = state;
		if (state)
		{
			m_Bt_JTAGPrint0.SetShade(CShadeButtonST::SHS_NOISE, 0, 20, 15, DIALOGBTNCOLOR);
			if (m_ShowDlg_JTAGPrint1)
				m_Bt_JTAGPrint.SetShade(CShadeButtonST::SHS_NOISE, 0, 20, 15, DIALOGBTNCOLOR);
		}
		else
		{
			m_Bt_JTAGPrint0.SetShade(CShadeButtonST::SHS_NOISE, 0, 20);
			m_Bt_JTAGPrint.SetShade(CShadeButtonST::SHS_NOISE, 0, 20);
		}
		break;
	case JTAGPrintCPU1:
		m_ShowDlg_JTAGPrint1 = state;
		if (state)
		{
			m_Bt_JTAGPrint1.SetShade(CShadeButtonST::SHS_NOISE, 0, 20, 15, DIALOGBTNCOLOR);
			if (m_ShowDlg_JTAGPrint0)
				m_Bt_JTAGPrint.SetShade(CShadeButtonST::SHS_NOISE, 0, 20, 15, DIALOGBTNCOLOR);
		}
		else
		{
			m_Bt_JTAGPrint1.SetShade(CShadeButtonST::SHS_NOISE, 0, 20);
			m_Bt_JTAGPrint.SetShade(CShadeButtonST::SHS_NOISE, 0, 20);
		}
		break;
	case JTAGDebugger:
		m_ShowDlg_JTAGDebugger = state;
		if (state)
			m_Bt_JTAGDebugger.SetShade(CShadeButtonST::SHS_NOISE, 0, 20, 15, DIALOGBTNCOLOR);
		else
			m_Bt_JTAGDebugger.SetShade(CShadeButtonST::SHS_NOISE, 0, 20);
		break;
	case Analyzer:
		m_ShowDlg_Analyzer = state;
		if (state)
			m_Bt_Analyzer.SetShade(CShadeButtonST::SHS_NOISE, 0, 20, 15, DIALOGBTNCOLOR);
		else
			m_Bt_Analyzer.SetShade(CShadeButtonST::SHS_NOISE, 0, 20);
		break;
	case ISP:
		m_ShowDlg_ISP = state;
		if (state)
			m_Bt_ISP.SetShade(CShadeButtonST::SHS_NOISE, 0, 20, 15, DIALOGBTNCOLOR);
		else
			m_Bt_ISP.SetShade(CShadeButtonST::SHS_NOISE, 0, 20);
		break;
	case Gamma:
		m_ShowDlg_Gamma = state;
		if (state)
			m_Bt_Gamma.SetShade(CShadeButtonST::SHS_NOISE, 0, 20, 15, DIALOGBTNCOLOR);
		else
			m_Bt_Gamma.SetShade(CShadeButtonST::SHS_NOISE, 0, 20);
		break;
	case ColorMap:
		m_ShowDlg_ColorMap = state;
		if (state)
			m_Bt_ColorMap.SetShade(CShadeButtonST::SHS_NOISE, 0, 20, 15, DIALOGBTNCOLOR);
		else
			m_Bt_ColorMap.SetShade(CShadeButtonST::SHS_NOISE, 0, 20);;
		break;
	case Key:
		m_ShowDlg_Key = state;
		if (state)
			m_Bt_Key.SetShade(CShadeButtonST::SHS_NOISE, 0, 20, 15, DIALOGBTNCOLOR);
		else
			m_Bt_Key.SetShade(CShadeButtonST::SHS_NOISE, 0, 20);
		break;
	case UartString:
		m_ShowDlg_UartString = state;
		if (state)
			m_Bt_UartString.SetShade(CShadeButtonST::SHS_NOISE, 0, 20, 15, DIALOGBTNCOLOR);
		else
			m_Bt_UartString.SetShade(CShadeButtonST::SHS_NOISE, 0, 20);
		break;
	case Lua:
		m_ShowDlg_Lua = state;
		if (state)
			m_Bt_Lua.SetShade(CShadeButtonST::SHS_NOISE, 0, 20, 15, DIALOGBTNCOLOR);
		else
			m_Bt_Lua.SetShade(CShadeButtonST::SHS_NOISE, 0, 20);
		break;
	case IPCamSearch:
		m_ShowDlg_IPCamSearch = state;
		if (state)
			m_Bt_IPCamSearch.SetShade(CShadeButtonST::SHS_NOISE, 0, 20, 15, DIALOGBTNCOLOR);
		else
			m_Bt_IPCamSearch.SetShade(CShadeButtonST::SHS_NOISE, 0, 20);
		break;
	}
	Invalidate(FALSE);
}


UINT ExeState(LPVOID pParam)
{
	int i = 0;
	DWORD exitcode = 0;
	
	while (1)
	{
		if (pRemoteDlg->flag_close)
			return 0;

		for (i = 0; i < MAUE_NUM; i++)
		{
			if (i == ECMSearch)
				continue;
			if (pRemoteDlg->m_sInfo[i].hProcess)
			{
				GetExitCodeProcess(pRemoteDlg->m_sInfo[i].hProcess, &exitcode);
				if (exitcode != STILL_ACTIVE)
				{
					pRemoteDlg->m_Edit_Port.EnableWindow(TRUE);
					pRemoteDlg->m_ctrlIPAddr.EnableWindow(TRUE);

					ZeroMemory(&pRemoteDlg->m_sInfo[i], sizeof(SHELLEXECUTEINFO));
					pRemoteDlg->ActiveCtrl(i, FALSE);
				}
				else
				{
					if (i > 0)
					{
						pRemoteDlg->m_Edit_Port.EnableWindow(FALSE);
						pRemoteDlg->m_ctrlIPAddr.EnableWindow(FALSE);
					}
				}
			}
		}
		Sleep(10);
	}
	return 0;
}


BOOL SafeTerminateProcess(HANDLE hProcess, UINT uExitCode)

{
	DWORD dwTID, dwCode, dwErr = 0;
	HANDLE hProcessDup = INVALID_HANDLE_VALUE;
	HANDLE hRT = NULL;
	HINSTANCE hKernel = GetModuleHandle(_T("Kernel32"));
	BOOL bSuccess = FALSE;
	BOOL bDup = DuplicateHandle(GetCurrentProcess(),
		hProcess,
		GetCurrentProcess(),
		&hProcessDup,
		PROCESS_ALL_ACCESS,
		FALSE,
		0);
	if (GetExitCodeProcess((bDup) ? hProcessDup : hProcess, &dwCode)
		&& (dwCode == STILL_ACTIVE))
	{
		FARPROC pfnExitProc;
		pfnExitProc = GetProcAddress(hKernel, "ExitProcess");
		hRT = CreateRemoteThread((bDup) ? hProcessDup : hProcess,
			NULL,
			0,
			(LPTHREAD_START_ROUTINE)pfnExitProc,
			(PVOID)uExitCode, 0, &dwTID);
		if (hRT == NULL) dwErr = GetLastError();
	}
	else
	{
		dwErr = ERROR_PROCESS_ABORTED;
	}

	if (hRT)
	{
		WaitForSingleObject((bDup) ? hProcessDup : hProcess, INFINITE);
		CloseHandle(hRT);
		bSuccess = TRUE;
	}

	if (bDup)
		CloseHandle(hProcessDup);

	if (!bSuccess)
		SetLastError(dwErr);

	return bSuccess;
}


ULONG ProcIDFromWnd(HWND hwnd) // 윈도우 핸들로 프로세스 아이디 얻기
{
	ULONG idProc;
	GetWindowThreadProcessId(hwnd, &idProc);
	return idProc;
}

HWND GetWinHandle(ULONG pid) // 프로세스 아이디로 윈도우 핸들 얻기
{
	HWND tempHwnd = FindWindow(NULL, NULL); // 최상위 윈도우 핸들 찾기

	while (tempHwnd != NULL)
	{
		if (GetParent(tempHwnd) == NULL) // 최상위 핸들인지 체크, 버튼 등도 핸들을 가질 수 있으므로 무시하기 위해
			if (pid == ProcIDFromWnd(tempHwnd))
				return tempHwnd;
		tempHwnd = GetWindow(tempHwnd, GW_HWNDNEXT); // 다음 윈도우 핸들 찾기
	}
	return NULL;
}


void CECM_remoteDlg::EXEControl(CString dlgname, CString buttonname)
{
	// X버튼 클릭으로 종료
	CWnd* hWndDlg = NULL;
	CWnd* hWndButton = NULL;
	hWndDlg = FindWindow(NULL, dlgname);

	DWORD Pro_pid = GetProcessId(m_sInfo[2].hProcess);
	HWND Pro_hWnd = GetWinHandle(Pro_pid);

	if (hWndDlg)
	{
		if (BT_CLOSE == buttonname)
		{
#if 0
			hWndButton = FindWindowEx(hWndDlg->m_hWnd, NULL, _T("Button"), buttonname);
			if (hWndButton)
			{
				::SendMessage(hWndButton->m_hWnd, BM_CLICK, NULL, NULL);
			}
#else
			//::SendMessage(hWndDlg->m_hWnd, WM_CLOSE, NULL, NULL);
			::SendMessage(Pro_hWnd, WM_CLOSE, NULL, NULL);
#endif
		}
		else if (BT_MINIMIZE == buttonname)
		{
			::ShowWindow(hWndDlg->m_hWnd, SW_MINIMIZE);
		}
		else if (BT_RESTORE == buttonname)
		{
			::ShowWindow(hWndDlg->m_hWnd, SW_RESTORE);
		}
	}
}


void CECM_remoteDlg::EXEControl(int dlgnum, CString buttonname)
{
	DWORD Pro_pid = GetProcessId(m_sInfo[dlgnum].hProcess);
	HWND Pro_hWnd = GetWinHandle(Pro_pid);

	if (Pro_hWnd)
	{
		if (BT_CLOSE == buttonname)
		{
			::SendMessage(Pro_hWnd, WM_CLOSE, NULL, NULL);
		}
		else if (BT_MINIMIZE == buttonname)
		{
			::ShowWindow(Pro_hWnd, SW_MINIMIZE);
		}
		else if (BT_RESTORE == buttonname)
		{
			::ShowWindow(Pro_hWnd, SW_RESTORE);
		}
	}
}

#if 0
void CECM_remoteDlg::ShowSpecial(BOOL bFlag)
{
	if (!bFlag)
	{
		m_Btn_Special.SetWindowTextW(_T("▼"));


		m_Bt_Analyzer.ShowWindow(SW_HIDE);
		m_Bt_Parameter.ShowWindow(SW_HIDE);
		m_Bt_ISP.ShowWindow(SW_HIDE);
		m_Bt_Gamma.ShowWindow(SW_HIDE);
		m_Bt_ColorMap.ShowWindow(SW_HIDE);
		m_Bt_Viewer.ShowWindow(SW_HIDE);
		m_Bt_JTAGDebugger.ShowWindow(SW_HIDE);
		m_Bt_Lua.ShowWindow(SW_HIDE);
		m_Bt_IPCamSearch.ShowWindow(SW_HIDE);


		CRect rect;
		CRect mainrect;
		this->GetWindowRect(mainrect);
		m_Bt_Analyzer.GetWindowRect(rect);
		int iParTop = rect.top - mainrect.top;

		SetWindowPos(NULL, 0, 0, mainrect.Width(), iParTop, SWP_NOMOVE);

		m_ShowSpecial_flag = FALSE;
	}
	else
	{
		m_Btn_Special.SetWindowTextW(_T("▲"));


		m_Bt_Analyzer.ShowWindow(SW_SHOW);
		m_Bt_Parameter.ShowWindow(SW_SHOW);
		m_Bt_ISP.ShowWindow(SW_SHOW);
		m_Bt_Gamma.ShowWindow(SW_SHOW);
		m_Bt_ColorMap.ShowWindow(SW_SHOW);
		m_Bt_Viewer.ShowWindow(SW_SHOW);
		m_Bt_JTAGDebugger.ShowWindow(SW_SHOW);
		m_Bt_Lua.ShowWindow(SW_SHOW);
		m_Bt_IPCamSearch.ShowWindow(SW_SHOW);

		SetWindowPos(NULL, 0, 0, initRect.Width(), initRect.Height(), SWP_NOMOVE);

		m_ShowSpecial_flag = TRUE;
	}

	RedrawWindow();
}
#else

void CECM_remoteDlg::ShowSpecial(BOOL bFlag)
{
	CRect rect;
	CRect thisRect;
	this->GetWindowRect(thisRect);
	m_Bt_Analyzer.GetWindowRect(rect);
	int iParTop = rect.top - thisRect.top;

	if (!bFlag)
	{
		m_Btn_Special.SetWindowTextW(_T("▼"));


		m_Bt_Analyzer.ShowWindow(SW_HIDE);
		m_Bt_Parameter.ShowWindow(SW_HIDE);
		m_Bt_ISP.ShowWindow(SW_HIDE);
		m_Bt_Gamma.ShowWindow(SW_HIDE);
		m_Bt_ColorMap.ShowWindow(SW_HIDE);
		m_Bt_Viewer.ShowWindow(SW_HIDE);
		m_Bt_JTAGDebugger.ShowWindow(SW_HIDE);
		m_Bt_Lua.ShowWindow(SW_HIDE);
		m_Bt_IPCamSearch.ShowWindow(SW_HIDE);

		SetWindowPos(NULL, thisRect.left, thisRect.top, thisRect.Width(), iParTop, NULL);

		m_ShowSpecial_flag = FALSE;
	}
	else
	{
		m_Btn_Special.SetWindowTextW(_T("▲"));


		m_Bt_Analyzer.ShowWindow(SW_SHOW);
		m_Bt_Parameter.ShowWindow(SW_SHOW);
		m_Bt_ISP.ShowWindow(SW_SHOW);
		m_Bt_Gamma.ShowWindow(SW_SHOW);
		m_Bt_ColorMap.ShowWindow(SW_SHOW);
		m_Bt_Viewer.ShowWindow(SW_SHOW);
		m_Bt_JTAGDebugger.ShowWindow(SW_SHOW);
		m_Bt_Lua.ShowWindow(SW_SHOW);
		m_Bt_IPCamSearch.ShowWindow(SW_SHOW);

		SetWindowPos(NULL, thisRect.left, thisRect.top, initRect.Width(), initRect.Height(), NULL);

		m_ShowSpecial_flag = TRUE;
	}

	RedrawWindow();
}
#endif

void CECM_remoteDlg::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case ID_CHECK_TIMER :
		AfxBeginThread(State_Check_Thread, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
		//State_Check();
		break;
	case ID_CONNECT_TIMER :
		AfxBeginThread(Connect_Check_Thread, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
		//Connect_Check();
		break;
	}
}


void CECM_remoteDlg::Check_Timer_On()
{
	m_CheckTimerID = SetTimer(ID_CHECK_TIMER, Check_Time, NULL);
}

void CECM_remoteDlg::Check_Timer_Off()
{
	if (m_CheckTimerID)
	{
		if (this->GetSafeHwnd())
			KillTimer(m_CheckTimerID);
		m_CheckTimerID = 0;
	}
}

void CECM_remoteDlg::Connect_Timer_On()
{
	m_ConnectTimerID = SetTimer(ID_CONNECT_TIMER, Connect_Time, NULL);
}

void CECM_remoteDlg::Connect_Timer_Off()
{
	if (m_ConnectTimerID)
	{
		if (this->GetSafeHwnd())
			KillTimer(m_ConnectTimerID);
		m_ConnectTimerID = 0;
	}
}


BOOL Invalidate_connect_flsg = FALSE;
BOOL Invalidate_error_flsg = FALSE;
BOOL Invalidate_disconnect_flsg = FALSE;
int error_count = 0;
UINT State_Check_Thread(LPVOID pParam)
{
	int state = -1;

	if (ConnectSocket != NULL)
		state = sendMsg(ConnectSocket, "rem_check ");

	recv(ConnectSocket, &pRemoteDlg->server_flag, sizeof(pRemoteDlg->server_flag), 0);
	
	if (state != -1)
	{
		if (pRemoteDlg->server_flag == '0')
		{
			if (Invalidate_connect_flsg)	return 0;
			pRemoteDlg->m_Bt_ServerState.SetColor(CButtonST::BTNST_COLOR_BK_OUT, RGB(0x00, 0xFF, 0x00));
			pRemoteDlg->m_Bt_ServerState.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(0x00, 0xFF, 0x00));
			Invalidate_connect_flsg = TRUE;
			Invalidate_error_flsg = FALSE;
			error_count = 0;
		}
		else
		{
			if (pRemoteDlg->preserver_flag == pRemoteDlg->server_flag)
				error_count++;
			else
				error_count = 0;
			pRemoteDlg->preserver_flag = pRemoteDlg->server_flag;
			
			if (error_count == 5)
			{
				if (pRemoteDlg->server_flag == '1')
					AfxMessageBox(_T("Please check your PC and DONGLE connection."), MB_TOPMOST);
				else if (pRemoteDlg->server_flag == '2')
					AfxMessageBox(_T("Please check the following.\n1. Board and DONGLE connection state.\n2. Power On/Off state of the board.\n3. Abnormal behavior after download.\nIf it does not work after downloading, please STALL it immediately after RESET and retry download."), MB_TOPMOST);
				else if (pRemoteDlg->server_flag == '3')
				{
					if (IDYES == AfxMessageBox(_T("CRC error has occurred.\n Do you want to RESET?"), MB_YESNO | MB_TOPMOST))
						pRemoteDlg->OnBnClickedButtonReset();
				}
				else
				{
					if (IDYES == AfxMessageBox(_T("Please RESET or restart the server.\n Do you want to RESET?"), MB_YESNO | MB_TOPMOST))
						pRemoteDlg->OnBnClickedButtonReset(); 
				}
			}

			if (Invalidate_error_flsg)	return 0;
			pRemoteDlg->m_Bt_ServerState.SetColor(CButtonST::BTNST_COLOR_BK_OUT, RGB(0xFF, 0xF2, 0x00));
			pRemoteDlg->m_Bt_ServerState.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(0xFF, 0xF2, 0x00));
			Invalidate_connect_flsg = FALSE;
			Invalidate_error_flsg = TRUE;
		}
	}
	else
	{
		if (Invalidate_disconnect_flsg)	return 0;
		pRemoteDlg->m_Bt_ServerState.SetColor(CButtonST::BTNST_COLOR_BK_OUT, RGB(0xFF, 0x02, 0x00));
		pRemoteDlg->m_Bt_ServerState.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(0xFF, 0x02, 0x00));
		Invalidate_disconnect_flsg = TRUE;

		if (ConnectSocket)
		{
			NetClo(ConnectSocket);
			ConnectSocket = NULL;
		}

		AfxMessageBox(_T("Please check the Server running."));

		pRemoteDlg->m_Btn_Reset.EnableWindow(FALSE);
		pRemoteDlg->m_Btn_Stall.EnableWindow(FALSE);

		pRemoteDlg->Check_Timer_Off();
		pRemoteDlg->Connect_Timer_On();
	}
	return 0;
}


UINT Connect_Check_Thread(LPVOID pParam)
{
	// IP Address 얻기
	pRemoteDlg->GetIP();

	// PORT 번호 얻기
	pRemoteDlg->GetPort();

	CStringA addr;
	CStringA port;
	addr = pRemoteDlg->Addr;
	port = pRemoteDlg->Port;
	strcpy(pRemoteDlg->ch_ip, addr.GetBuffer(addr.GetLength()));
	strcpy(pRemoteDlg->ch_port, port.GetBuffer(port.GetLength()));

	ConnectSocket = NetCon(pRemoteDlg->ch_ip, pRemoteDlg->ch_port);

	if (ConnectSocket <= 0)
	{
		NetClo(ConnectSocket);
		ConnectSocket = NULL;

		if (m_CServerDlg)
			pRemoteDlg->OnBnClickedButtonServerstate();
	}
	else
	{
		Invalidate_connect_flsg = FALSE;
		Invalidate_error_flsg = FALSE;
		Invalidate_disconnect_flsg = FALSE;

		pRemoteDlg->m_Btn_Reset.EnableWindow(TRUE);
		pRemoteDlg->m_Btn_Stall.EnableWindow(TRUE);

		pRemoteDlg->Connect_Timer_Off();
		pRemoteDlg->Check_Timer_On();
	}
	return 0;
}


void CECM_remoteDlg::OnEnSetfocusEdit1()
{
	m_Edit_Port.GetWindowTextW(FocusOnPort);
}


void CECM_remoteDlg::OnEnKillfocusEdit1()
{
	m_Edit_Port.GetWindowTextW(FocusOffPort);
	if (FocusOnPort != FocusOffPort)
	{
		NetClo(ConnectSocket);
		ConnectSocket = NULL;
	}
}