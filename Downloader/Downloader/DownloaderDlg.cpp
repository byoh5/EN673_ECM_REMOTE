
// DownloaderDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "Downloader.h"
#include "DownloaderDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


UINT	DownFunc1Thread(LPVOID pParam);
UINT	DownFunc2Thread(LPVOID pParam);
UINT	DownFunc3Thread(LPVOID pParam);
UINT	DownFunc4Thread(LPVOID pParam);
UINT	DownFunc5Thread(LPVOID pParam);

const UINT  ID_CHECK_TIMER = 100;
const UINT  ID_CONNECT_TIMER = 200;
UINT	State_Check_Thread(LPVOID pParam);
UINT	Connect_Check_Thread(LPVOID pParam);

#define		Check_Time		1000
#define		Connect_Time	5000


int AckFromRemote(int fd, char* str);

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


// CDownloaderDlg 대화 상자



CDownloaderDlg::CDownloaderDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDownloaderDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ECM);

	m_pDlg_Output = NULL;
	m_pDlg_CompileOption673 = NULL;
	m_pDlg_DownOption673 = NULL;
	m_pDlg_DownSectionWrite673 = NULL;
}

// ====================================================================================================
// ~CDownloaderDlg
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
CDownloaderDlg::~CDownloaderDlg()
{
#if 0
	m_pDlg_Output->DestroyWindow();
	delete m_pDlg_Output;

	m_pDlg_CompileOption673->DestroyWindow();
	delete m_pDlg_CompileOption673;

	m_pDlg_DownOption673->DestroyWindow();
	delete m_pDlg_DownOption673;

	m_pDlg_DownSectionWrite673->DestroyWindow();
	delete m_pDlg_DownSectionWrite673;
#endif
}


void CDownloaderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_LIST, m_Tab_List);
	DDX_Control(pDX, IDC_BUTTON_DOWNCLOSE, m_Btn_Close);
	DDX_Control(pDX, IDC_BUTTON_MINIMIZE, m_Btn_Minimize);
	DDX_Control(pDX, IDC_BUTTON_CONNECT, m_Btn_Connect);
	DDX_Control(pDX, IDC_BUTTON_DOWNFUNC1, m_Btn_DownFunc1);
	DDX_Control(pDX, IDC_BUTTON_DOWNFUNC2, m_Btn_DownFunc2);
	DDX_Control(pDX, IDC_BUTTON_DOWNFUNC3, m_Btn_DownFunc3);
	DDX_Control(pDX, IDC_BUTTON_DOWNFUNC4, m_Btn_DownFunc4);
	DDX_Control(pDX, IDC_BUTTON_DOWNFUNC5, m_Btn_DownFunc5);
	DDX_Control(pDX, IDC_CHECK_BINUSE1, m_Chk_BinUse[0]);
	DDX_Control(pDX, IDC_CHECK_BINUSE2, m_Chk_BinUse[1]);
	DDX_Control(pDX, IDC_CHECK_BINUSE3, m_Chk_BinUse[2]);
	DDX_Control(pDX, IDC_CHECK_BINUSE4, m_Chk_BinUse[3]);
	DDX_Control(pDX, IDC_EDIT_BINPATH1, m_Edit_BinPath[0]);
	DDX_Control(pDX, IDC_EDIT_BINPATH2, m_Edit_BinPath[1]);
	DDX_Control(pDX, IDC_EDIT_BINPATH3, m_Edit_BinPath[2]);
	DDX_Control(pDX, IDC_EDIT_BINPATH4, m_Edit_BinPath[3]);
	DDX_Control(pDX, IDC_EDIT_SECTOR_BGN1, m_Edit_SectorBgn[0]);
	DDX_Control(pDX, IDC_EDIT_SECTOR_BGN2, m_Edit_SectorBgn[1]);
	DDX_Control(pDX, IDC_EDIT_SECTOR_BGN3, m_Edit_SectorBgn[2]);
	DDX_Control(pDX, IDC_EDIT_SECTOR_BGN4, m_Edit_SectorBgn[3]);
	DDX_Control(pDX, IDC_EDIT_SECTOR_END1, m_Edit_SectorEnd[0]);
	DDX_Control(pDX, IDC_EDIT_SECTOR_END2, m_Edit_SectorEnd[1]);
	DDX_Control(pDX, IDC_EDIT_SECTOR_END3, m_Edit_SectorEnd[2]);
	DDX_Control(pDX, IDC_EDIT_SECTOR_END4, m_Edit_SectorEnd[3]);
	DDX_Control(pDX, IDC_EDIT_STARTADDR1, m_Edit_StartAddr[0]);
	DDX_Control(pDX, IDC_EDIT_STARTADDR2, m_Edit_StartAddr[1]);
	DDX_Control(pDX, IDC_EDIT_STARTADDR3, m_Edit_StartAddr[2]);
	DDX_Control(pDX, IDC_EDIT_STARTADDR4, m_Edit_StartAddr[3]);
	DDX_Control(pDX, IDC_BUTTON_OPENBINPATH1, m_Btn_OpenBin[0]);
	DDX_Control(pDX, IDC_BUTTON_OPENBINPATH2, m_Btn_OpenBin[1]);
	DDX_Control(pDX, IDC_BUTTON_OPENBINPATH3, m_Btn_OpenBin[2]);
	DDX_Control(pDX, IDC_BUTTON_OPENBINPATH4, m_Btn_OpenBin[3]);
}

#define WM_CHECK_ACTIVE	(WM_USER+2)
BEGIN_MESSAGE_MAP(CDownloaderDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_LIST, &CDownloaderDlg::OnTcnSelchangeTabList)
	ON_BN_CLICKED(IDC_BUTTON_DOWNCLOSE, &CDownloaderDlg::OnBnClickedButtonDownclose)
	ON_BN_CLICKED(IDC_BUTTON_MINIMIZE, &CDownloaderDlg::OnBnClickedButtonMinimize)
	ON_BN_CLICKED(IDC_BUTTON_DOWNFUNC1, &CDownloaderDlg::OnBnClickedButtonDownfunc1)
	ON_BN_CLICKED(IDC_BUTTON_DOWNFUNC2, &CDownloaderDlg::OnBnClickedButtonDownfunc2)
	ON_BN_CLICKED(IDC_BUTTON_DOWNFUNC3, &CDownloaderDlg::OnBnClickedButtonDownfunc3)
	ON_BN_CLICKED(IDC_BUTTON_DOWNFUNC4, &CDownloaderDlg::OnBnClickedButtonDownfunc4)
	ON_BN_CLICKED(IDC_BUTTON_DOWNFUNC5, &CDownloaderDlg::OnBnClickedButtonDownfunc5)
	ON_BN_CLICKED(IDC_CHECK_BINUSE1, &CDownloaderDlg::OnBnClickedCheckBinuse1)
	ON_BN_CLICKED(IDC_CHECK_BINUSE2, &CDownloaderDlg::OnBnClickedCheckBinuse2)
	ON_BN_CLICKED(IDC_CHECK_BINUSE3, &CDownloaderDlg::OnBnClickedCheckBinuse3)
	ON_BN_CLICKED(IDC_CHECK_BINUSE4, &CDownloaderDlg::OnBnClickedCheckBinuse4)
	ON_EN_CHANGE(IDC_EDIT_BINPATH1, &CDownloaderDlg::OnEnChangeEditBinpath1)
	ON_EN_CHANGE(IDC_EDIT_BINPATH2, &CDownloaderDlg::OnEnChangeEditBinpath2)
	ON_EN_CHANGE(IDC_EDIT_BINPATH3, &CDownloaderDlg::OnEnChangeEditBinpath3)
	ON_EN_CHANGE(IDC_EDIT_BINPATH4, &CDownloaderDlg::OnEnChangeEditBinpath4)
	ON_EN_CHANGE(IDC_EDIT_SECTOR_BGN1, &CDownloaderDlg::OnEnChangeEditSectorBgn1)
	ON_EN_CHANGE(IDC_EDIT_SECTOR_BGN2, &CDownloaderDlg::OnEnChangeEditSectorBgn2)
	ON_EN_CHANGE(IDC_EDIT_SECTOR_BGN3, &CDownloaderDlg::OnEnChangeEditSectorBgn3)
	ON_EN_CHANGE(IDC_EDIT_SECTOR_BGN4, &CDownloaderDlg::OnEnChangeEditSectorBgn4)
	ON_BN_CLICKED(IDC_BUTTON_OPENBINPATH1, &CDownloaderDlg::OnBnClickedButtonOpenbinpath1)
	ON_BN_CLICKED(IDC_BUTTON_OPENBINPATH2, &CDownloaderDlg::OnBnClickedButtonOpenbinpath2)
	ON_BN_CLICKED(IDC_BUTTON_OPENBINPATH3, &CDownloaderDlg::OnBnClickedButtonOpenbinpath3)
	ON_BN_CLICKED(IDC_BUTTON_OPENBINPATH4, &CDownloaderDlg::OnBnClickedButtonOpenbinpath4)
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_ACTIVATE()
END_MESSAGE_MAP()


// CDownloaderDlg 메시지 처리기

BOOL CDownloaderDlg::OnInitDialog()
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
	SetWindowText(DLG_DOWNLOADER);

	// 다이얼로그 사이즈 조정
	int x = ReadIni(SEC_WININFO, KEY_DOWNDLGLEFT, DEF_DOWNDLGLEFT);
	int y = ReadIni(SEC_WININFO, KEY_DOWNDLGTOP, DEF_DOWNDLGTOP);

	SetWindowPos(NULL, x, y, 520, 400, NULL);
	//this->SetWindowPos(NULL, 0, 0, 520, 400, NULL);

	pDownloaderDlg = this;

// ----------------------------------------------------------------------------------------------------
// Server 연결
	CString strCmd = theApp.m_lpCmdLine;
	CString strAddr = NULL;
	CString strPort = NULL;

	AfxExtractSubString(strAddr, strCmd, 0, ' ');
	AfxExtractSubString(strPort, strCmd, 1, ' ');

#ifdef _DEBUG
	strAddr.Format(_T("192.168.0.199"));
	strPort = DEFAULT_PORT;
#endif
	if (strPort == _T(""))	strPort = DEFAULT_PORT;

	CStringA addr;
	CStringA port;
	addr = strAddr;
	port = strPort;
	strcpy(ch_ip, addr.GetBuffer(addr.GetLength()));
	strcpy(ch_port, port.GetBuffer(port.GetLength()));

	ConnectSocket = NetCon(ch_ip, ch_port);
	if (ConnectSocket <= 0)
	{
		AfxMessageBox(_T("Not Connect"));
		//exit(0);
	}

	Sleep(1);

	StateSocket = NetCon(ch_ip, ch_port);

	// Connect Check Timer Set
	Check_Timer_On();

	iPlatformSel = 0;

// ----------------------------------------------------------------------------------------------------
// Create Sub Dialog
	CRect rect;
	m_Tab_List.GetWindowRect(&rect);

	x = 2;
	y = 23;
	int cx = rect.Width() - 6;
	int cy = rect.Height() - 26;
	UINT nFlags = SWP_SHOWWINDOW | SWP_NOZORDER;

	m_pDlg_CompileOption673 = new CDownCompileOption673();
	m_pDlg_CompileOption673->Create(IDD_DOWN_COMPILEOPTION_673, &m_Tab_List);
	m_pDlg_CompileOption673->SetWindowPos(NULL, x, y, cx, cy, nFlags);

	m_pDlg_DownOption673 = new CDownDownOption673();
	m_pDlg_DownOption673->Create(IDD_DOWN_DOWNOPTION_673, &m_Tab_List);
	m_pDlg_DownOption673->SetWindowPos(NULL, x, y, cx, cy, SWP_NOZORDER);

	m_pDlg_DownSectionWrite673 = new CDownSectionWrite673();
	m_pDlg_DownSectionWrite673->Create(IDD_DOWN_SECTIONWRITE_673, &m_Tab_List);
	m_pDlg_DownSectionWrite673->SetWindowPos(NULL, x, y, cx, cy, SWP_NOZORDER);

	m_pDlg_Output = new CDownOutput();
	m_pDlg_Output->Create(IDD_DOWN_OUTPUT, &m_Tab_List);
	m_pDlg_Output->SetWindowPos(NULL, x, y, cx, cy, SWP_NOZORDER);
	
	m_Tab_List.InsertItem(0, _T("Compile Option"), 0);
	m_Tab_List.InsertItem(1, _T("Download Option"), 1);
	m_Tab_List.InsertItem(2, _T("Section Write"), 2);
	m_Tab_List.InsertItem(3, _T("Output"), 3);

	m_Tab_List.SetCurSel(0);
	m_Tab_List.RedrawWindow();


#if 0
	m_pCEN673_Configuration_GeneratorDlg = new CEN673_Configuration_GeneratorDlg();
	m_pCEN673_Configuration_GeneratorDlg->Create(IDD_EN673_CONFIGURATION_GENERATOR_DIALOG, this);
	m_pCEN673_Configuration_GeneratorDlg->SetWindowPos(NULL, rect.right, rect.top, 0, 0, SWP_SHOWWINDOW | SWP_NOZORDER | SWP_NOSIZE);

	m_pCEN673_Configuration_GeneratorDlg->ShowWindow(SW_HIDE);
	m_ShowDlg_ConfigGen = FALSE;
#endif

	int i = 0;
	// BinFile
	for (i = 0; i < BINNUM; i++)
	{
		m_BinFile[i].bBinUse = ReadIni(SEC_DOWN, KEY_BINUSE[i], DEF_BINUSE[i]);		// BinUse
		m_Chk_BinUse[i].SetCheck(m_BinFile[i].bBinUse);
		m_Edit_EnableWindow(i, m_BinFile[i].bBinUse);
		SetBinPath(i, ReadIni(SEC_DOWN, KEY_BINPATH[i], DEF_BINPATH[i]));			// BinPath
		SetSectorBgn(i, ReadIni(SEC_DOWN, KEY_BINSECBGN[i], DEF_BINSECBGN[i]));		// SectorBgn
		InitBinFileInfo(i);	// Initial
		if (m_BinFile[i].bBinUse == 1)
			m_Chk_Option(i);
	}
	
// ----------------------------------------------------------------------------------------------------
// Control
	// CLOSE 버튼
	m_Btn_Close.DrawBorder(FALSE);
	m_Btn_Close.SetColor(CButtonST::BTNST_COLOR_BK_OUT, DIALOGCOLOR);
	m_Btn_Close.SetColor(CButtonST::BTNST_COLOR_BK_IN, DIALOGSUBCOLOR);

	// Minimize
	m_Btn_Minimize.DrawBorder(FALSE);
	m_Btn_Minimize.SetColor(CButtonST::BTNST_COLOR_BK_OUT, DIALOGCOLOR);
	m_Btn_Minimize.SetColor(CButtonST::BTNST_COLOR_BK_IN, DIALOGSUBCOLOR);

	// Connect
	m_Btn_Connect.SetIcon(AfxGetApp()->LoadIcon(IDI_CONNECT), NULL);
	m_Btn_Connect.DrawTransparent(TRUE);

	// Button
	UINT uiShadeID = CShadeButtonST::SHS_NOISE;
	BYTE byGranularity = 0;
	BYTE byHighlight = 20;
	BYTE byColoring = 30;
	COLORREF crColor = DIALOGSUBCOLOR;

	m_Btn_DownFunc1.SetShade(uiShadeID, byGranularity, byHighlight, byColoring, crColor);
	m_Btn_DownFunc2.SetShade(uiShadeID, byGranularity, byHighlight, byColoring, crColor);
	m_Btn_DownFunc3.SetShade(uiShadeID, byGranularity, byHighlight, byColoring, crColor);
	m_Btn_DownFunc4.SetShade(uiShadeID, byGranularity, byHighlight, byColoring, crColor);
	m_Btn_DownFunc5.SetShade(uiShadeID, byGranularity, byHighlight, byColoring, crColor);

	m_Btn_OpenBin[0].SetBitmaps(IDB_OPEN, RGB(255, 0, 255));
	m_Btn_OpenBin[1].SetBitmaps(IDB_OPEN, RGB(255, 0, 255));
	m_Btn_OpenBin[2].SetBitmaps(IDB_OPEN, RGB(255, 0, 255));
	m_Btn_OpenBin[3].SetBitmaps(IDB_OPEN, RGB(255, 0, 255));

	m_Btn_DownFunc2.SetWindowTextW(_T(""));
	m_Btn_DownFunc2.EnableWindow(FALSE);

// ----------------------------------------------------------------------------------------------------
// Draw Background
	//DrawWinBg((CWnd*)this, &m_bmpBg, DLG_DOWNLOADER, TRUE);
// ----------------------------------------------------------------------------------------------------

// Flag
	bRunDownFunc1Thread = FALSE;
	bRunDownFunc2Thread = FALSE;
	bRunDownFunc3Thread = FALSE;
	bRunDownFunc4Thread = FALSE;
	bRunDownFunc5Thread = FALSE;
	bRunDownloadHexThread = FALSE;

	g_pDownFunc1Thread = NULL;
	g_pDownFunc2Thread = NULL;
	g_pDownFunc3Thread = NULL;
	g_pDownFunc4Thread = NULL;
	g_pDownFunc5Thread = NULL;
	g_pDownloadHexThread = NULL;

	m_bBuildOption = 0;

	m_bStopDownload = FALSE;

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}


BOOL CDownloaderDlg::PreTranslateMessage(MSG* pMsg)
{
	// Default Window Message
	if (DefaultWindowMessage(pMsg))	return TRUE;
	else							return CDialog::PreTranslateMessage(pMsg);
}


int CDownloaderDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetWindowLongPtr(m_hWnd, GWL_STYLE, WS_SYSMENU | WS_MINIMIZEBOX);

	RedrawWindow();

	return 0;
}


void CDownloaderDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDownloaderDlg::OnPaint()
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
		// Top
		CPaintDC dc(this);
		CRect rect;
		CWnd* pWnd = this;
		if (pWnd == NULL)
		{
			TRACE("pWnd == NULL");
			Trace("pWnd == NULL");
			while (1);
		}
		pWnd->GetWindowRect(rect);
		int iWidth = rect.Width();
		int iHeight = rect.Height();
		dc.FillSolidRect(0, 0, iWidth, 25, DIALOGCOLOR);

		// OutLine
		CPen NewPen(PS_SOLID, 2, DIALOGCOLOR);
		//CPen NewPen(PS_SOLID, 2, DIALOGOUTLINE);
		CPen* pOldPen = dc.SelectObject(&NewPen);
		if (pOldPen == NULL)
		{
			TRACE("pOldPen == NULL");
			Trace("pOldPen == NULL");
			while (1);
		}
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

		// Font
		LOGFONT lf;
		::ZeroMemory(&lf, sizeof(lf));
		lf.lfHeight = 15;
		lf.lfWeight = 700;
		wsprintf(lf.lfFaceName, _T("%s"), _T("Arial"));
		CFont NewFont;
		NewFont.CreateFontIndirectW(&lf);
		CFont* pOldFont = dc.SelectObject(&NewFont);
		if (pOldFont == NULL)
		{
			TRACE("pOldFont == NULL");
			Trace("pOldFont == NULL");
			while (1);
		}
		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(TITLECOLOR);

		dc.TextOutW(10, 6, DLG_DOWNLOADER);

		dc.SelectObject(pOldFont);


		pDownOutput->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
		pDownCompileOption673->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
		pDownCompileOption673->UpdateWindow();
		pDownSectionWrite673->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

		//CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CDownloaderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDownloaderDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetCapture();
	m_Point = point;

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CDownloaderDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (this == GetCapture())
	{
		CRect rcDialog;
		GetWindowRect(&rcDialog);

		int x = rcDialog.left + point.x - m_Point.x;
		int y = rcDialog.top + point.y - m_Point.y;

		SetWindowPos(NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		WriteIni(SEC_WININFO, KEY_DOWNDLGLEFT, x);
		WriteIni(SEC_WININFO, KEY_DOWNDLGTOP, y);

	// ----------------------------------------------------------------------------------------------------
	// Set Sub Dialog
		CRect rectConfigGen;

		pCEN673_Configuration_GeneratorDlg->GetWindowRect(&rectConfigGen);
		pCEN673_Configuration_GeneratorDlg->MoveWindow(rcDialog.right, rcDialog.top,
			rectConfigGen.Width(), rectConfigGen.Height(), TRUE);
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void CDownloaderDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	ReleaseCapture();

	CDialogEx::OnLButtonUp(nFlags, point);
}

void CDownloaderDlg::OnCancel()
{
	SaveValue();

	m_pDlg_Output->DestroyWindow();
	delete m_pDlg_Output;

	m_pDlg_CompileOption673->DestroyWindow();
	delete m_pDlg_CompileOption673;

	m_pDlg_DownOption673->DestroyWindow();
	delete m_pDlg_DownOption673;

	m_pDlg_DownSectionWrite673->DestroyWindow();
	delete m_pDlg_DownSectionWrite673;

	if (ConnectSocket != NULL)
	{
		NetClo(ConnectSocket);
		ConnectSocket = NULL;
	}

	if (StateSocket != NULL)
	{
		NetClo(StateSocket);
		StateSocket = NULL;
	}

	CDialogEx::OnCancel();
}


// ====================================================================================================
// CDownloaderDlg :: SetBinPath
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CDownloaderDlg::SetBinPath(int iNum, CString strPath)
{
	m_BinFile[iNum].strBinPath = strPath;
	m_Edit_BinPath[iNum].SetWindowTextW(strPath);
}

// ====================================================================================================
// CDownloaderDlg :: SetSectorBgn
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CDownloaderDlg::SetSectorBgn(int iNum, UINT uiSectorBgn)
{
	CString str = _T("");

	m_BinFile[iNum].uiSectorBgn = uiSectorBgn;

	str.Format(_T("%d"), uiSectorBgn);
	m_Edit_SectorBgn[iNum].SetWindowTextW(str);
}

// ====================================================================================================
// CDownloaderDlg :: SetSectorEnd
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CDownloaderDlg::SetSectorEnd(int iNum, UINT uiSectorEnd)
{
	CString str = _T("");

	m_BinFile[iNum].uiSectorEnd = uiSectorEnd;

	str.Format(_T("%d"), uiSectorEnd);
	m_Edit_SectorEnd[iNum].SetWindowTextW(str);
}


// ====================================================================================================
// CDownloaderDlg::ChkBins
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
BOOL CDownloaderDlg::ChkBins(int isUart)
{
	int i = 0;
	int j = 0;
	int BinListSize = 0;

	int StaSectorList[BINNUM] = { 0, };
	int EndSectorList[BINNUM] = { 0, };
	CString str = _T("");

	CFile file;
	for (i = 0; i < BINNUM; i++)
	{
		if (m_BinFile[i].bBinUse){
			if (!file.Open(m_BinFile[i].strBinPath, CFile::modeRead)) {
				// Download할 %d번째 bin파일이 없습니다.
				str.Format(_T("#%d bin file does not exist."), i + 1);
				AfxMessageBox(str);
				return FALSE;
			}
			file.Close();

			StaSectorList[BinListSize] = m_BinFile[i].uiSectorBgn;
			EndSectorList[BinListSize] = m_BinFile[i].uiSectorEnd;

			if (isUart && StaSectorList[BinListSize] == 0) {
				// Download할 %d번째 bin파일을 부트영역(Sector 0)에 UART Download할 수 없습니다.
				str.Format(_T("Fail download #%d bin file at boot area(Sector #0)."), i + 1);
				AfxMessageBox(str);
				return FALSE;
			}

			BinListSize++;
		}
	}

	for (i = 0; i < (BinListSize - 1); i++)
	{
		for (j = i + 1; j < BinListSize; j++) {
			if (StaSectorList[i] < StaSectorList[j]) {
				if (EndSectorList[i] >= StaSectorList[j]) {
					// Download할 %d번째 bin파일과 %d번째 bin파일의 Sector가 겹칩니다.
					str.Format(_T("Sector is same #%d bin file and #%d bin file to be downloaded."), i + 1, j + 1);
					AfxMessageBox(str);
					return FALSE;
				}
			}
			else {
				if (EndSectorList[j] >= StaSectorList[i]) {
					str.Format(_T("Sector is same #%d bin file and #%d bin file to be downloaded."), i + 1, j + 1);
					AfxMessageBox(str);
					return FALSE;
				}
			}
		}
	}

	return TRUE;
}

void CDownloaderDlg::OnBnClickedButtonDownclose()
{
	OnCancel();
}


void CDownloaderDlg::OnBnClickedButtonMinimize()
{
	ShowWindow(SW_MINIMIZE);
}


void CDownloaderDlg::OnBnClickedButtonDownfunc1()
{
	// ----------------------------------------------------------------------------------------------------
	// Stop Download

	if (bRunDownFunc1Thread) {
		m_Btn_DownFunc1.EnableWindow(FALSE);
		m_bStopDownload = TRUE;
		return;
	}

	if (THREAD_ON) return;

	//bin file check 부분 분석 필요...
	BOOL b = FALSE;
	for (int i = 0; i < BINNUM; i++) b |= m_BinFile[i].bBinUse;
	if (!b) return;

	// ----------------------------------------------------------------------------------------------------
	// Start Thread
	StartDownFunc1Thread();
}

// ====================================================================================================
// CDownloaderDlg :: StartDownFunc1Thread
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CDownloaderDlg::StartDownFunc1Thread()
{
	// Run DownFunc1 Thread
	g_pDownFunc1Thread = AfxBeginThread(DownFunc1Thread, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
}

// == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == ==
// DownFunc1Thread
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
UINT DownFunc1Thread(LPVOID pParam)
{
	int i = 0;

	bRunDownFunc1Thread = TRUE;

	// ----------------------------------------------------------------------------------------------------
	// 컨트롤 비활성화
	pDownloaderDlg->EnableCtrl(FALSE);

	// ----------------------------------------------------------------------------------------------------
	// JTAG Thread Hold
	sendMsg(ConnectSocket, "rem_hold ");
	pDownloaderDlg->Check_Timer_Off();
	pDownloaderDlg->Connect_Timer_Off();

	// ----------------------------------------------------------------------------------------------------
	// Check Platform & Run

	pDownloaderDlg->m_Btn_DownFunc1.SetWindowTextW(_T("Stop\r\nDownload"));
	pDownloaderDlg->m_Btn_DownFunc1.EnableWindow(TRUE);

	pDownloaderDlg->JTAGDownload673();

	pDownloaderDlg->m_Btn_DownFunc1.SetWindowTextW(_T("JTAG\nDownload(F5)"));


	// ----------------------------------------------------------------------------------------------------
	// 컨트롤 활성화
	pDownloaderDlg->EnableCtrl(TRUE);

	// ----------------------------------------------------------------------------------------------------
	// Flash Window
	pDownloaderDlg->SendMessage(WM_CHECK_ACTIVE, 0, 0);

	// ----------------------------------------------------------------------------------------------------
	// End
	pDownloaderDlg->m_bStopDownload = FALSE;
	bRunDownFunc1Thread = FALSE;
	sendMsg(ConnectSocket, "rem_release ");
	pDownloaderDlg->Check_Timer_On();
	return 0;
}


#define FLASH_BASE		0x06000000 // 673
#define JTAG_COMMON_MODULE_IDX	3
#define MAX_RETRY_NUM	100
// ====================================================================================================
// CDownloaderDlg::JTAGDownload673
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CDownloaderDlg::JTAGDownload673()
{
	int i = 0;
	int j = 0;
	int iAddress = 0;
	int iCnt = 0;
	UINT32 err = 0;
	CString strMsg = _T("");
	BOOL bReturn = FALSE;

	CString strBinPath = _T("");

	UINT32	uiStartAddress = 0;

	UCHAR * memblock = NULL;
	UINT32* memblock32 = NULL;

	// Clear Output Box
	pDownOutput->AddOutBox(_T(" > JTAG Download \r\n"), DOWNOUTPUT_CLEARALL);

	// Change Tab
	int iTabCount = m_Tab_List.GetItemCount();
	m_Tab_List.SetCurSel(iTabCount - 1);
	InitFileList(iTabCount - 1);
	Sleep(100);

	// Get Platform Information
	// 673 674 시리즈에 따라서 동작이 달라질수 있음. 따라서, platform 선택 가능해야 할 듯.
	//int iPlatformSel = GetPlatformSel();


	// Bin File 확인
	if (!ChkBins(0)){
		strMsg = _T("Failed Download");
		goto END;
	}


	// ----------------------------------------------------------------------------------------------------
	// Init JTAG
	strMsg.Format(_T("Init JTAG...... "));
	pDownOutput->AddOutBox(strMsg);

	// 네트워크 TCP 연결 상태 Check 필요.
	// 초기화 진행 x. 초기화 할 경우 이미 동작 중인 모듈에 영향을 미칠수 있음.

	/*
	pJTAG->JTAGClose();
	InitSPI();

	iCnt = 0;
	while (TRUE) {
	if ((err = EN673_JTAG_INIT(m_Platform[iPlatformSel].GetJTAGClkdiv())) == 0) break;
	if (iCnt>10) {
	strMsg.Format(_T("Fail : Can't initialize JTAG. (Error : 0x%08x)"), err);
	goto END;
	}
	iCnt++;
	Sleep(0);
	}

	// Reset CPU
	// 리셋을 안하면 flash id가 읽어지지 않음
	if (err |= pJTAG->rc()) { strMsg.Format(_T("Fail : rc (Error : 0x%08x)"), err); goto END; }
	*/

#if 1
	int state = 0;

	if (ConnectSocket != NULL)
		state = sendMsg(ConnectSocket, "rem_check ");

	if (state < 0)
	{
		strMsg.Format(_T("Fail : Can't initialize JTAG"));
		goto END;
	}

	char ocd_flag;
	state = recv(ConnectSocket, &ocd_flag, sizeof(ocd_flag), 0);

	if (state > 0)
	{
		if (ocd_flag != '0')
		{
			strMsg.Format(_T("Fail : Can't initialize JTAG"));
			goto END;
		}
	}
	else
	{
		strMsg.Format(_T("Fail : Can't initialize JTAG"));
		goto END;
	}
#endif


	strMsg.Format(_T("End\r\n"));
	pDownOutput->AddOutBox(strMsg);

	// Stall CPU
	strMsg.Format(_T("Stall..... "));
	pDownOutput->AddOutBox(strMsg);


	if (sendMsg(ConnectSocket, "rem_st ") < 0)
	{
		strMsg.Format(_T("stalled fail!"));
		goto END;
	}

	if ((errno == EAGAIN) || (errno == EWOULDBLOCK))
	{
		if (ConnectSocket)
		{
			NetClo(ConnectSocket);
			ConnectSocket = NULL;
		}

		if (StateSocket)
		{
			NetClo(StateSocket);
			StateSocket = NULL;
		}
		goto END;
	}

	/*
	UINT8 stalled = 0;
	for (UINT8 ncpu = 4; ncpu < 6; ncpu++) {
	try {
	if (err = jtag_stall_cpu(ncpu)) throw err;
	if (err = jtag_check_stalled_cpu(ncpu, &stalled)) throw err;
	if (!stalled) throw 0xffffffff;
	}
	catch (UINT32 err) {
	strMsg.Format(_T("Fail : now unstalled. (Error : 0x%08x)"), err);
	goto END;
	}
	}
	*/

	strMsg.Format(_T("Success : now stalled\r\n"));
	pDownOutput->AddOutBox(strMsg);

	Sleep(100);


#if !CHANGE_EN674
	// Watchdog
	if ((err= reset_sys_wdt()) == -1) {    // Add for Reset Watchdog!!!! Flash write will fail when watchdog enabled!
		strMsg.Format(_T("Watchdog enable fail! (Error : 0x%08x)"), err);
		goto END;
	}
#endif


	// Init Flash
	strMsg.Format(_T("Init Flash...... "));
	pDownOutput->AddOutBox(strMsg);

	iCnt = 0;
	while (TRUE) {
		if ((err = Sfls_init_quad()) == 0) break;
		if (iCnt>5) {
			strMsg.Format(_T("Fail : Can't init flash memory. (Error : 0x%08x)"), err);
			goto END;
		}
		iCnt++;
		Sleep(0);
	}

	strMsg.Format(_T("End\r\n"));
	pDownOutput->AddOutBox(strMsg);


	// Get Time
	SYSTEMTIME time;
	GetLocalTime(&time);

	strMsg.Format(_T("%04d/%02d/%02d  %02d:%02d:%02d"),	time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
	pDownOutput->AddOutBox(strMsg + _T("\r\n"));

// ----------------------------------------------------------------------------------------------------
// Start Download
	// Time
	ULONGLONG dwTimeStart = 0;
	ULONGLONG dwTimeEnd = 0;
	ULONGLONG dwTime = 0;

	for (i = 0; i < BINNUM; i++)
	{
		// Check Bin UseEnableCtrl
		if (!m_BinFile[i].bBinUse) continue;

		// Enter
		strMsg.Format(_T("\r\n--------------------------------------------------\r\n"));
		pDownOutput->AddOutBox(strMsg);

		// File Open & Error Check	
		CFile* pBinFile = new CFile;
		CFileException FileErr;

		strBinPath = m_BinFile[i].strBinPath;

		pBinFile->Open(strBinPath, CFile::modeRead, &FileErr);
		switch (FileErr.m_cause) // Error Check
		{
		case CFileException::none: // no error
			break;
		case CFileException::fileNotFound:
			strMsg = _T("The file could not be located.");
			if (pBinFile != NULL) delete[] pBinFile;
			goto END;
		case CFileException::accessDenied:
			strMsg = _T("The file could not be accessed.");
			if (pBinFile != NULL) delete[] pBinFile;
			goto END;
		default:
			strMsg = _T("Can't open file.");
			if (pBinFile != NULL) delete[] pBinFile;
			goto END;
		}

		// Read File
		UINT32 uiSize = pBinFile->GetLength();
		UINT32 uiSizeAdj = uiSize % 4 == 0 ? uiSize : ((uiSize + 4) >> 2) << 2;

		memblock = new UCHAR[uiSizeAdj];
		memset(memblock, 0, sizeof(UCHAR)*uiSizeAdj);

		if (pBinFile->Read(memblock, uiSize) != uiSize)
		{
			pBinFile->Close();
			strMsg = _T("File cannot be read.");
			if (pBinFile != NULL) delete[] pBinFile;
			goto END;
		}
		pBinFile->Close();

		// change endian fr
		memblock32 = (UINT32*)memblock;


		// Get Start Address
		uiStartAddress = m_BinFile[i].uiSectorBgn * SECTOR_SIZE;


		// Download Start
		strMsg.Format(_T("Download Start... %s \r\n"), strBinPath);
		pDownOutput->AddOutBox(strMsg);

#if 1
		// Chip Ver Check
		UINT8* memblock_c = NULL;
		memblock_c = (UINT8*)malloc(16);

		if (err |= getDataFromRemote(ConnectSocket, 0x060000a0, 12, 3, (UINT32*)memblock_c)) {
			strMsg.Format(_T("Fail : Chip Model Read (Error : 0x%08x)"), err);
			goto END;
		}

		char current_model[12];
		char download_model[12];
		CString current_str, download_str;
		for (int i = 0; i < 12; i++)
		{
			current_model[i] = memblock_c[i];
			download_model[i] = memblock[160 + i];
		}
		current_str = current_model;
		current_str = current_str.Left(12);
		if (current_str == _T(""))
			current_str = _T("NULL");
		strMsg = _T("Current Model : ") + current_str + _T("\r\n");
		pDownOutput->AddOutBox(strMsg);

		download_str = download_model;
		download_str = download_str.Left(12);
		if (download_str == _T(""))
			download_str = _T("NULL");
		strMsg = _T("Download Model : ") + download_str + _T("\r\n");
		pDownOutput->AddOutBox(strMsg);

		if (current_str != download_str)
		{
			strMsg = _T("Current Model : ") + current_str + _T("\n") + _T("Download Model : ") + download_str + _T("\n\n") + _T("Model is different.\nContinue downloading?");

			if (IDYES == AfxMessageBox(strMsg, MB_YESNO))
			{
				;
			}
			else
			{
				if (IDNO)
				{
					strMsg.Format(_T("Stop Downloader"));
					goto END;
				}
			}
		}
#endif

		// FLASH : Erase
		if (!JTAGErase(uiStartAddress, uiSizeAdj, strMsg)) {
			if (pBinFile != NULL) delete pBinFile;
			goto END;
		}

		// FLASH : Write
		if (!JTAGWrite(uiStartAddress, uiSizeAdj, (UINT32*)memblock32, strMsg)) {
			if (pBinFile != NULL) delete pBinFile;
			goto END;
		}


		// FLASH : Verify
		// Compare 4kbytes 
		// If different, write again
		if (!JTAGVerify(uiStartAddress, uiSizeAdj, memblock, strMsg)) {
			if (pBinFile != NULL) delete pBinFile;
			goto END;
		}

		strMsg.Format(_T("Download Complete!\r\n"));
		pDownOutput->AddOutBox(strMsg);

		if (memblock != NULL)	delete[] memblock;  memblock = NULL;
		if (pBinFile != NULL)	delete pBinFile;	pBinFile = NULL;
	}

	Sleep(1000);

	int count = 0;
	if( sendMsg(ConnectSocket, "rem_rst ") < 0)
	{
		while (1)
		{
			Sleep(1000);
			count++;
			if (count > 5)
			{
				strMsg.Format(_T("Reset Fail!\r\n"));
				goto END;
			}
			if (sendMsg(ConnectSocket, "rem_rst ") < 0)
				continue;
		}
	}

	bReturn = TRUE;
END:
	//m_Btn_DownFunc1.EnableWindow(FALSE);

	/*
	// Reset
	tap_reset_global0();
	pJTAG->JTAGClose();
	*/

	if (bReturn) {
	}
	else {
		if (strMsg != _T("")) {
			pDownOutput->AddOutBox(strMsg + _T("\r\n"));
			AfxMessageBox(strMsg, MB_ICONWARNING);

			NetClo(ConnectSocket);
			ConnectSocket = NULL;

			NetClo(StateSocket);
			StateSocket = NULL;
		}
	}

	// Memory 해제
	if (memblock != NULL)	delete[] memblock;
}


// ====================================================================================================
// CDownloaderDlg::JTAGErase
// ----------------------------------------------------------------------------------------------------
/*
CDownloaderDlg::JTAGDownload672()
*/
// ====================================================================================================
#define MAX_IN_STRING		256
BOOL CDownloaderDlg::JTAGErase(UINT32 uiStartAddress, UINT32 uiSize, CString& strMsg)
{
	UINT32 uiAddress = uiStartAddress;
	UINT16 uiProgress = 0;
	UINT16 uiProgressCnt = 0;
	DWORD dwTimeStart = 0;
	DWORD dwTimeEnd = 0;
	DWORD dwTime = 0;
	CString strMsgPrint = _T("");
	UINT32 err = 0;
	int state = -1;
	strMsgPrint.Format(_T("Erasing... "));
	pDownOutput->AddOutBox(strMsgPrint);

	dwTimeStart = GetTickCount();

	// Calculrate Progress
	do {
		if (((uiAddress%BLOCK_SIZE) != 0) || ((uiStartAddress + uiSize) - uiAddress) < BLOCK_SIZE)
			uiAddress += SECTOR_SIZE;
		else	uiAddress += BLOCK_SIZE;
		uiProgress++;
	} while ((uiStartAddress + uiSize) > uiAddress);

	// Erase
	uiAddress = uiStartAddress;
	do {
		if (m_bStopDownload) {
			strMsg.Format(_T("\r\nStop Download\r\n"));
			return FALSE;
		}

		if (((uiAddress%BLOCK_SIZE) != 0) ||  // 현재 Write할 주소(iAddress)가 64KB의 배수가 아닌 경우
			((uiStartAddress + uiSize) - uiAddress) < BLOCK_SIZE) { // 다운로드할 남은 파일의 크기가 64KB보다 작은 경우
			
			if (m_bStopDownload) {
				strMsg.Format(_T("\r\nStop Download\r\n"));
				return FALSE;
			}

			// Erase Sector
#if 0
			if (err |= Sfls_erase_sect(uiAddress)) {
				strMsg.Format(_T("Fail : Can't erase flash memory. (Error : 0x%08x)"), err);
				return FALSE;
			}
#else
			char instr[MAX_IN_STRING] = { 0, 0 };
			sprintf(instr, "rem_Sfls_erase %x sect ", uiAddress);
			state = sendMsg(ConnectSocket, instr);
			if (state < 0)	return FALSE;


			char ok_flag;
			state = recv(ConnectSocket, &ok_flag, 1, 0);
			if (ok_flag != '0')
			{
				strMsg.Format(_T("Fail : Can't erase flash memory."));
				return FALSE;
			}
#endif
			uiAddress += SECTOR_SIZE;
		}
		else {
			
			if (m_bStopDownload) {
				strMsg.Format(_T("\r\nStop Download\r\n"));
				return FALSE;
			}

			// Erase Block
#if 0
			if (err |= Sfls_erase_block(uiAddress)) {
				strMsg.Format(_T("Fail : Can't erase flash memory. (Error : 0x%08x)"), err);
				return FALSE;
			}
#else
			char instr[MAX_IN_STRING] = { 0, 0 };
			sprintf(instr, "rem_Sfls_erase %x block ", uiAddress);
			state = sendMsg(ConnectSocket, instr);
			if (state < 0)	return FALSE;

			char ok_flag;
			state = recv(ConnectSocket, &ok_flag, 1, 0);
			if (ok_flag != '0')
			{
				strMsg.Format(_T("Fail : Can't erase flash memory."));
				return FALSE;
			}
#endif
			uiAddress += BLOCK_SIZE;
		}
		strMsgPrint.Format(_T("Erasing... %.2f%% "), (((float)++uiProgressCnt / (float)uiProgress) * 100));
		pDownOutput->AddOutBox(strMsgPrint, 1);
		Sleep(1);
	} while ((uiStartAddress + uiSize) > uiAddress);

	dwTimeEnd = GetTickCount();
	dwTime = dwTimeEnd - dwTimeStart;

	if (dwTime == 0)		strMsgPrint.Format(_T("Erasing... %.2f%%, Time : %.2fs (%.2fKByte/s)\r\n"), 100.0, ((float)dwTime) / 1000, 0);
	else				strMsgPrint.Format(_T("Erasing... %.2f%%, Time : %.2fs (%.2fKByte/s)\r\n"), 100.0, ((float)dwTime) / 1000, (uiSize / 1024) / (((float)dwTime) / 1000));
	pDownOutput->AddOutBox(strMsgPrint, 1);

	return TRUE;
}

// ====================================================================================================
// CDownloaderDlg::JTAGWrite
// ----------------------------------------------------------------------------------------------------
/*
CDownloaderDlg::JTAGDownload673()
*/
// ====================================================================================================
#define WRITE_BUF_SIZE 1024*2
BOOL CDownloaderDlg::JTAGWrite(UINT32 uiStartAddress, UINT32 uiSize, UINT32* uiData, CString& strMsg)
{
	int i = 0;
	UINT32 uiLen = 0;
	UINT32 uiCnt = 0;
	UINT32 uiAddress = 0;
	DWORD dwTimeStart = 0;
	DWORD dwTimeEnd = 0;
	DWORD dwTime = 0;
	CString strMsgPrint = _T("");
	UINT32 err = 0;

	strMsgPrint.Format(_T("Writing... "));
	pDownOutput->AddOutBox(strMsgPrint);

	dwTimeStart = GetTickCount();

	for (i = uiSize / 4; i > 0; i -= WRITE_BUF_SIZE) {
		if (m_bStopDownload) {
			strMsg.Format(_T("\r\nStop Download\r\n"));
			return FALSE;
		}
		uiLen = i >= WRITE_BUF_SIZE ? WRITE_BUF_SIZE : i;

		// Write
		//if (err |= jtag_write_block32(FLASH_BASE + uiStartAddress + (uiAddress * 4), (UINT32*)uiData + uiAddress, uiLen, JTAG_COMMON_MODULE_IDX)) {
		if (err |= setDataFromRemote(ConnectSocket, FLASH_BASE + uiStartAddress + (uiAddress * 4), uiLen * 4, JTAG_COMMON_MODULE_IDX, (UINT32*)uiData + uiAddress)) {
			strMsg.Format(_T("Fail : Can't write flash memory. (Error : 0x%08x)"), err);
			return FALSE;
		}

		uiAddress += WRITE_BUF_SIZE;

		// Print
		uiCnt++;
		if (uiCnt % 20 == 0){
			strMsgPrint.Format(_T("Writing... %.2f%%"), ((float)(uiAddress * 4) / (float)uiSize) * 100);
			pDownOutput->AddOutBox(strMsgPrint, 1);
		}

		Sleep(1);
	}

	dwTimeEnd = GetTickCount();
	dwTime = dwTimeEnd - dwTimeStart;

	if (dwTime == 0)		strMsgPrint.Format(_T("Writing... %.2f%%, Time : %.2fs (%.2fKByte/s)\r\n"), 100.0, ((float)dwTime) / 1000, 0);
	else				strMsgPrint.Format(_T("Writing... %.2f%%, Time : %.2fs (%.2fKByte/s)\r\n"), 100.0, ((float)dwTime) / 1000, (uiSize / 1024) / (((float)dwTime) / 1000));
	pDownOutput->AddOutBox(strMsgPrint, 1);

	return TRUE;
}

// ====================================================================================================
// CDownloaderDlg::JTAGVerify
// ----------------------------------------------------------------------------------------------------
/*
CDownloaderDlg::JTAGDownload672()
*/
// ====================================================================================================
BOOL CDownloaderDlg::JTAGVerify(UINT32 uiStartAddress, UINT32 uiSize, UINT8* uiData, CString& strMsg)
{
	int i = 0;
	UINT32 uiLen = 0;
	UINT32 uiCnt = 0;
	UINT32 uiAddress = 0;
	DWORD dwTimeStart = 0;
	DWORD dwTimeEnd = 0;
	DWORD dwTime = 0;
	char * veribuf = NULL;
	char retry = 0;
	UINT32 err = 0;
	CString strMsgPrint = _T("");

	strMsgPrint.Format(_T("Verifing... "));
	pDownOutput->AddOutBox(strMsgPrint);

	veribuf = new char[BLOCK_SIZE];

	dwTimeStart = GetTickCount();

	try {
		uiCnt = 0;
		uiAddress = 0;

		for (i = uiSize; i > 0; i -= BLOCK_SIZE){
			if (m_bStopDownload) {
				strMsg.Format(_T("\r\nStop Download\r\n"));
				delete[] veribuf;
				return FALSE;
			}

			uiLen = i >= BLOCK_SIZE ? BLOCK_SIZE : i;

			// Read
			//if (err = jtag_read_block32(FLASH_BASE + uiStartAddress + uiAddress, (UINT32*)veribuf, uiLen / 4, JTAG_COMMON_MODULE_IDX)) throw err;
			if (err = getDataFromRemote(ConnectSocket, FLASH_BASE + uiStartAddress + uiAddress, uiLen, JTAG_COMMON_MODULE_IDX, (UINT32*)veribuf)) throw err;

			retry = 0;
			while (memcmp(veribuf, uiData + uiAddress, uiLen)){
				if (m_bStopDownload) {
					strMsg.Format(_T("\r\nStop Download\r\n"));
					return FALSE;
				}
				// Erase
				if (err = Sfls_erase_sect(uiStartAddress + uiAddress)) throw err;
				// Write
				if (err = Sfls_write32((UINT32*)uiData + uiAddress, uiLen / 4, uiStartAddress + uiAddress)) throw err;
				// Read
				//if (err = jtag_read_block32(FLASH_BASE + uiStartAddress + uiAddress, (UINT32*)veribuf, uiLen / 4, JTAG_COMMON_MODULE_IDX)) throw err;
				if (err = getDataFromRemote(ConnectSocket, FLASH_BASE + uiStartAddress + uiAddress, uiLen, JTAG_COMMON_MODULE_IDX, (UINT32*)veribuf)) throw err;
				// Count Retry
				retry++;
				if (retry>MAX_RETRY_NUM){
					strMsg = _T("Over Max Retry for write flash!");
					return FALSE;
				}
				Sleep(0);
			}
			uiAddress += BLOCK_SIZE;

			uiCnt++;
			if (uiCnt % 10 == 0){
				strMsgPrint.Format(_T("Verifing... %.2f%%"), ((float)uiAddress / (float)uiSize) * 100);
				pDownOutput->AddOutBox(strMsgPrint, 1);
			}

			Sleep(1);
		}
		printf("%d\n", uiCnt);
	}
	catch (UINT32 err) {
		strMsg.Format(_T("Fail : Can't verify (Error : 0x%08x)"), err);
		delete[] veribuf;
		return FALSE;
	}

	dwTimeEnd = GetTickCount();
	dwTime = dwTimeEnd - dwTimeStart;

	if (dwTime == 0)		strMsgPrint.Format(_T("Verifing... %.2f%%, Time : %.2fs (%.2fKByte/s)\r\n"), 100.0, ((float)dwTime) / 1000, 0);
	else				strMsgPrint.Format(_T("Verifing... %.2f%%, Time : %.2fs (%.2fKByte/s)\r\n"), 100.0, ((float)dwTime) / 1000, (uiSize / 1024) / (((float)dwTime) / 1000));
	pDownOutput->AddOutBox(strMsgPrint, 1);

	delete[] veribuf;

	return TRUE;
}

void CDownloaderDlg::OnBnClickedButtonDownfunc2()
{
	if (!m_ShowDlg_ConfigGen)
	{
		CRect rectThis;
		CRect rectSet;

		this->GetWindowRect(&rectThis);
		pCEN673_Configuration_GeneratorDlg->GetWindowRect(&rectSet);

		//pCExrocdDlg->MoveWindow(rectThis.right, rectThis.top, rectSet.Width(), rectSet.Height(), TRUE);
		pCEN673_Configuration_GeneratorDlg->SetWindowPos(NULL, rectThis.right, rectThis.top, rectSet.Width(), rectSet.Height(), NULL);

		pCEN673_Configuration_GeneratorDlg->ShowWindow(SW_SHOW);
		m_ShowDlg_ConfigGen = TRUE;
	}
	else
	{
		pCEN673_Configuration_GeneratorDlg->OnBnClickedButtonClose();
		m_ShowDlg_ConfigGen = FALSE;
	}
}


void CDownloaderDlg::OnBnClickedButtonDownfunc3()
{
	BOOL b = FALSE;
	for (int i = 0; i < BINNUM; i++) b |= m_BinFile[i].bBinUse;
	if (!b) return;

	StartDownFunc3Thread();
}

// ====================================================================================================
// StartDownFunc3Thread
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CDownloaderDlg::StartDownFunc3Thread()
{
	// Run DownFunc3Thread
	g_pDownFunc3Thread = AfxBeginThread(DownFunc3Thread, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
}

// ====================================================================================================
// DownFunc3Thread
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
UINT DownFunc3Thread(LPVOID pParam)
{
	
	int i = 0;

	bRunDownFunc3Thread = TRUE;

	// ----------------------------------------------------------------------------------------------------
	// 1. 컨트롤 비활성화
	pDownloaderDlg->EnableCtrl(FALSE);
	pDownloaderDlg->m_Btn_Close.EnableWindow(FALSE);
	pDownloaderDlg->Check_Timer_Off();
	pDownloaderDlg->Connect_Timer_Off();

	// ----------------------------------------------------------------------------------------------------
	// 2. Build
	switch (iPlatformSel)
	{

	case EN673:
#if INSERT_EN674
	case EN674:
#endif
		pDownloaderDlg->BuildExRISC();
		break;

	default:
		AfxMessageBox(_T("This platform is not supported."));
		break;
	}

	Sleep(100);

	// ----------------------------------------------------------------------------------------------------
	// 3. Enable Window
	pDownloaderDlg->EnableCtrl(TRUE);
	pDownloaderDlg->m_Btn_Close.EnableWindow(TRUE);
	pDownloaderDlg->Check_Timer_On();

	// ----------------------------------------------------------------------------------------------------
	// 4. Flash Window
	pDownloaderDlg->SendMessage(WM_CHECK_ACTIVE, 0, 0);

	// ----------------------------------------------------------------------------------------------------
	// 5. Flag
	bRunDownFunc3Thread = FALSE;
	
	return 0;
}

// ====================================================================================================
// CDownloaderDlg :: BuildExRISC
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CDownloaderDlg::BuildExRISC()
{
	int i = 0;
	CString strMsg = _T("");

	// Clear Output Box
	pDownOutput->AddOutBox(_T(" > Build \r\n"), DOWNOUTPUT_CLEARALL);

	// Change Tab
	int iTabCount = m_Tab_List.GetItemCount();
	m_Tab_List.SetCurSel(iTabCount - 1);
	InitFileList(iTabCount - 1);
	Sleep(100);

	// Build
	for (i = 0; i < BINNUM; i++)
	{
		// Bin Use
		if (!m_BinFile[i].bBinUse) continue;

		strMsg.Format(_T("\r\n--------------------------------------------------\r\n"));
		pDownOutput->AddOutBox(strMsg);

		strMsg.Format(_T("Build start...... %s\r\n"), m_BinFile[i].strBinPath);
		pDownOutput->AddOutBox(strMsg);

		if (RunBuildExRISC(i))	strMsg.Format(_T("Build Success!\r\n"));
		else					strMsg.Format(_T("Build Fail!\r\n"));
		pDownOutput->AddOutBox(strMsg);

		strMsg.Format(_T("End\r\n"));
		pDownOutput->AddOutBox(strMsg);
	}
}

BOOL CDownloaderDlg::RunBuildExRISC(int iNum)
{
	CString str = _T("");
	int iLen = 0;
	FILE* fp;

	CString strBinPath = _T("");
	char* szTopPath = NULL;
	CString strTopPath = _T("");
	char* szBatPath = NULL;
	CString strBatPath = _T("");
	CString strPrjPath = _T("");

	CString strApp = _T("");

	// Path
	// Bin Path
	strBinPath = m_BinFile[iNum].strBinPath;
	// Top Path
	strTopPath = strBinPath;
	// Bat Path
	strBatPath = strBinPath;
	strBatPath = strBatPath.Left(strBatPath.ReverseFind('\\')); // *.bin
	strPrjPath = strBatPath; // 뒤에서 사용하기 위해서 미리 저장
	strBatPath = strBatPath.Left(strBatPath.ReverseFind('\\')); // \output
	strBatPath = strBatPath + _T("\\") + _T("Build_ECM.bat");
	iLen = WideCharToMultiByte(CP_ACP, 0, strBatPath, -1, NULL, 0, NULL, NULL);
	szBatPath = new char[iLen + 1];
	WideCharToMultiByte(CP_ACP, 0, strBatPath, -1, szBatPath, iLen, NULL, NULL);

	// Set Bat File
	if (fopen_s(&fp, szBatPath, "w") == 0)
	{
		fprintf(fp, "@echo off\n");

		// Move Drive
		strTopPath = strTopPath.Left(2); // drive name
		iLen = WideCharToMultiByte(CP_ACP, 0, strTopPath, -1, NULL, 0, NULL, NULL);
		szTopPath = new char[iLen + 1];
		WideCharToMultiByte(CP_ACP, 0, strTopPath, -1, szTopPath, iLen, NULL, NULL);
		fprintf(fp, "%s\n", szTopPath);
		delete[] szTopPath; szTopPath = NULL;

		strTopPath = strBinPath;

		strTopPath = strTopPath.Left(strTopPath.ReverseFind('\\')); // *.bin
		strTopPath = strTopPath.Left(strTopPath.ReverseFind('\\')); // \output
		iLen = WideCharToMultiByte(CP_ACP, 0, strTopPath, -1, NULL, 0, NULL, NULL);
		szTopPath = new char[iLen + 1];
		WideCharToMultiByte(CP_ACP, 0, strTopPath, -1, szTopPath, iLen, NULL, NULL);
		fprintf(fp, "cd %s\n", szTopPath);
		delete[] szTopPath; szTopPath = NULL;

		fprintf(fp, "PATH = C:\\eyenix\\cygwin\\bin;%%PATH%%\n");

		// make
		pDownCompileOption673->m_Edit_CompileOption.GetWindowTextW(strTopPath);
		pDownCompileOption673->m_Edit_ApplicationOption.GetWindowTextW(strApp);
		pDownCompileOption673->m_Edit_CustomOption.GetWindowTextW(str);
		if (str.GetLength() > 0) {
			strTopPath = strTopPath + _T(" ") + strApp + _T(" ") + str;
		}
		else
			strTopPath = strTopPath + _T(" ") + strApp;

		iLen = WideCharToMultiByte(CP_ACP, 0, strTopPath, -1, NULL, 0, NULL, NULL);
		szTopPath = new char[iLen + 1];
		WideCharToMultiByte(CP_ACP, 0, strTopPath, -1, szTopPath, iLen, NULL, NULL);
		fprintf(fp, "%s\n", szTopPath);
		delete[] szTopPath; szTopPath = NULL;

		// etc
		fprintf(fp, "echo.\n");
		fprintf(fp, "pause\n");

		fclose(fp);

		// Run Bat File
		_spawnl(_P_WAIT, szBatPath, szBatPath, NULL);
	}

	if (szBatPath != NULL) {
		delete[] szBatPath;
		szBatPath = NULL;
	}

	InitBinFileInfo(iNum);

	// Compile 성공여부 확인
	BOOL bFail = FALSE;
	CString strBootPath = strPrjPath + _T("\\module\\boot.bin");
	CString strCpu0Path = strPrjPath + _T("\\module\\cpu0.bin");
	CString strCpu1Path = strPrjPath + _T("\\module\\cpu1.bin");

	CFileFind ffind;
	bFail += ffind.FindFile(strBinPath); ffind.Close();
	bFail += ffind.FindFile(strBootPath); ffind.Close();
	bFail += ffind.FindFile(strCpu0Path); ffind.Close();
	bFail += ffind.FindFile(strCpu1Path); ffind.Close();

	if (bFail == 4)	return TRUE;
	else			return FALSE;
}


void CDownloaderDlg::OnBnClickedButtonDownfunc4()
{
	StartDownFunc4Thread();
}

// ====================================================================================================
// StartDownFunc4Thread
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CDownloaderDlg::StartDownFunc4Thread()
{
	// Run DownFunc4 Thread
	g_pDownFunc4Thread = AfxBeginThread(DownFunc4Thread, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
}


// ====================================================================================================
// DownFunc4Thread
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
UINT DownFunc4Thread(LPVOID pParam)
{
	bRunDownFunc4Thread = TRUE;


	pDownloaderDlg->m_Btn_Close.EnableWindow(FALSE);

	// ----------------------------------------------------------------------------------------------------
	// Stop JTAG Function
	if (pDownDownOption673->m_Radio_JTAG.GetCheck())
		pDownloaderDlg->JTAGReset();

	Sleep(100);

	// ----------------------------------------------------------------------------------------------------
	// Enable Window
	pDownloaderDlg->m_Btn_Close.EnableWindow(TRUE);

	// ----------------------------------------------------------------------------------------------------
	// Flash Window
	pDownloaderDlg->SendMessage(WM_CHECK_ACTIVE, 0, 0);

	// ----------------------------------------------------------------------------------------------------
	// Flag
	bRunDownFunc4Thread = FALSE;

	return 0;
}

// ====================================================================================================
// JTAGReset
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CDownloaderDlg::JTAGReset()
{
	UINT32 err = 0;
	CString strMsg = _T("");
	BOOL bJTAGOpen = FALSE;
	BOOL bReturn = FALSE;
	int state = 0;
	// ----------------------------------------------------------------------------------------------------
	// Clear Output Box
	pDownOutput->AddOutBox(_T(""), DOWNOUTPUT_CLEARALL);

	// Change Tab
	int iTabCount = m_Tab_List.GetItemCount();
	m_Tab_List.SetCurSel(iTabCount - 1);
	InitFileList(iTabCount - 1);
	Sleep(100);

	// ----------------------------------------------------------------------------------------------------
	// Start
	pDownOutput->AddOutBox(_T("Start JTAG Reset...\r\n"));

	// Init
	pDownOutput->AddOutBox(_T("Init......\r\n"));

	/*
	pDownloaderDlg->InitSPI();

	err = EN673_JTAG_INIT(m_Platform[iPlatformSel].GetJTAGClkdiv());
	if (err) {
		strMsg.Format(_T("Failed initializing (Error : 0x%08x)"), err);
		pDownOutput->AddOutBox(strMsg + _T("\r\n"));
		AfxMessageBox(strMsg, MB_ICONWARNING);
		return;
	}
	*/

#if 1
	if (ConnectSocket != NULL)
		state = sendMsg(ConnectSocket, "rem_check ");

	if (state < 0)
	{
		strMsg.Format(_T("Fail : Can't initialize JTAG"));
		goto END;
	}

	char ocd_flag = NULL;
	state = recv(ConnectSocket, &ocd_flag, sizeof(ocd_flag), 0);

	if (ocd_flag != '0')
	{
		if (ConnectSocket)
		{
			NetClo(ConnectSocket);
			ConnectSocket = NULL;
		}

		if (StateSocket)
		{
			NetClo(StateSocket);
			StateSocket = NULL;
		}

		strMsg.Format(_T("Fail : Can't initialize JTAG"));
		goto END;
	}
#endif

	state = sendMsg(ConnectSocket, "rem_hold ");
	if (state < 0)
	{
		strMsg.Format(_T("Fail : Can't initialize JTAG"));
		goto END;
	}

	Sleep(10);

	// Reset
	pDownOutput->AddOutBox(_T("Reset......\r\n"));

	state = sendMsg(ConnectSocket, "rem_rst ");
	if (state < 0) 
	{
		strMsg.Format(_T("Failed Reset"));
		goto END;
	}

	/*
	err = tap_reset_global0();
	if (err) {
		strMsg.Format(_T("Failed Reset All (Error : 0x%08x)"), err);
		pDownOutput->AddOutBox(strMsg + _T("\r\n"));
		AfxMessageBox(strMsg, MB_ICONWARNING);
		return;
	}
	*/

	// End
	pDownOutput->AddOutBox(_T("Reset Complete!"));

	Sleep(10);

	sendMsg(ConnectSocket, "rem_release ");

	// ----------------------------------------------------------------------------------------------------
	// Start JTAG Function
	//pJTAG->StartJTAGFunction(bJTAGOpen, strMsg);
	bReturn = TRUE;

END:
	if (!bReturn)
	{
		if (ConnectSocket)
		{
			NetClo(ConnectSocket);
			ConnectSocket = NULL;
		}

		if (StateSocket)
		{
			NetClo(StateSocket);
			StateSocket = NULL;
		}

		pDownOutput->AddOutBox(strMsg + _T("\r\n"));
		AfxMessageBox(strMsg, MB_ICONWARNING);
	}
}


void CDownloaderDlg::OnBnClickedButtonDownfunc5()
{
	// ----------------------------------------------------------------------------------------------------
	// Start Section Write
	StartDownFunc5Thread();
}

// ====================================================================================================
// CDownloaderDlg :: StartDownFunc5Thread
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CDownloaderDlg::StartDownFunc5Thread()
{
	// Run DownFunc5Thread
	g_pDownFunc5Thread = AfxBeginThread(DownFunc5Thread, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
}

// ====================================================================================================
// DownFunc5Thread
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
UINT DownFunc5Thread(LPVOID pParam)
{
	bRunDownFunc5Thread = TRUE;

	// ----------------------------------------------------------------------------------------------------
	// 컨트롤 비활성화
	//pDownloaderDlg->m_Btn_Close.EnableWindow(FALSE);
	pDownloaderDlg->EnableCtrl(FALSE);

	// ----------------------------------------------------------------------------------------------------
	// Stop JTAG Function
	sendMsg(ConnectSocket, "rem_hold ");
	pDownloaderDlg->Check_Timer_Off();
	pDownloaderDlg->Connect_Timer_Off();

	// ----------------------------------------------------------------------------------------------------
	int iCheckNum = 0;
	switch (iPlatformSel)
	{
	/* ExRISC */
	case EN673:
#if INSERT_EN674
	case EN674:
#endif
		iCheckNum = pDownloaderDlg->CheckSectionWrite();
		if (iCheckNum == -1) {
			//AfxMessageBox(_T("바이너리를 하나만 선택해주세요."));
			AfxMessageBox(_T("Please select binary file."));
			break;
		}

		pDownloaderDlg->SectionWrite(iCheckNum);
		break;

	default:
		AfxMessageBox(_T("This platform is not supported."));
		break;
	}

	// ----------------------------------------------------------------------------------------------------
	// 컨트롤 활성화
	//pDownloaderDlg->m_Btn_Close.EnableWindow(TRUE);
	pDownloaderDlg->EnableCtrl(TRUE);

	// ----------------------------------------------------------------------------------------------------
	// Flash Window
ENDDOWNFUNC5THREAD:
	Sleep(500);

	pDownloaderDlg->SendMessage(WM_CHECK_ACTIVE, 0, 0);

	bRunDownFunc5Thread = FALSE;
	sendMsg(ConnectSocket, "rem_release ");
	pDownloaderDlg->Check_Timer_On();

	return 0;
}

// ====================================================================================================
// CDownloaderDlg::CheckSectionWrite
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
BOOL CDownloaderDlg::CheckSectionWrite()
{
	BOOL bBinUse = 0;
	int iCheckNum = 0;

	for (int i = 0; i < BINNUM; i++) {
		bBinUse += m_BinFile[i].bBinUse;
		if (m_BinFile[i].bBinUse) iCheckNum = i;
	}

	if ((bBinUse != 1) || (bBinUse == 0))	return -1;
	else									return iCheckNum;
}

// ====================================================================================================
// CDownloaderDlg::SectionWrite
// ----------------------------------------------------------------------------------------------------
#define MW_MAX_RETRY_NUM 100
#define MEM_WRITE_BUFFER_SIZE 1024*8

typedef enum {
	CS_LMA = 0,
	CS_RESET_LMA = 1, CS_TEXT_LMA, CS_ISPM_TEXT_LMA, CS_ISPM_DATA_LMA, CS_RODATA_LMA, CS_DATA_LMA,
	CS_RESET = 7, CS_TEXT, CS_ISPM_TEXT, CS_ISPM_DATA, CS_RODATA, CS_DATA,  		// : Code Sections
	CS_BSS, CS_STACK
} eCodeSectionIndex;

#define	CODE_SECTION_IDX(NAME) 		CS_ ## NAME
#define	CODE_SECTION_LMA_IDX(NAME)	CS_ ## NAME ##_LMA
#define	CS_NSECTIONS				(CS_RESET-CS_RESET_LMA)
#define	VMA_TO_LMA(VMA_ID)			((VMA_ID)-CS_NSECTIONS)

typedef union {
	UINT32 info[2];
	struct {
		UINT32 s, e;
	};
} tCodeSectionInfo;

typedef union {
	tCodeSectionInfo section[1 + 2 * CS_NSECTIONS];
	struct {
		tCodeSectionInfo	lma;
		tCodeSectionInfo 	reset_lma, text_lma, ispm_text_lma, ispm_data_lma, rodata_lma, data_lma;
		tCodeSectionInfo	reset, text, ispm_text, ispm_data, rodata, data;
		tCodeSectionInfo	bss, stack;
	};
} tCodeMemInfo;
// ====================================================================================================
void CDownloaderDlg::SectionWrite(int iNum)
{
	int i = 0;
	int id = 0;
	int cpu = 0;
	BOOL bJTAGOpen = FALSE;
	BOOL bReturn = FALSE;
	UINT32 addr = 0;
	UINT32 localaddr = 0;
	char* memblock = NULL;
	char* Nmemblock = NULL;
	UINT32* memblock32 = NULL;
	UINT32* Nmemblock32 = NULL;
	UINT32 module_idx = 0;
	UINT32 start_of_addr = 0;
	UINT32 err = 0;
	CFile* pBinFile = NULL;
	CFileException FileErr;
	CString strMsg = _T("");
	CString strBinPath = _T("");

	// ----------------------------------------------------------------------------------------------------
	// Stop JTAG Function
	//bJTAGOpen = pJTAG->StopJTAGFunction();

	// ----------------------------------------------------------------------------------------------------
	// Clear Output Box
	pDownOutput->AddOutBox(_T(" > Section Write \r\n"), DOWNOUTPUT_CLEARALL);

	// Change Output Tab
	int iTabCount = m_Tab_List.GetItemCount();
	m_Tab_List.SetCurSel(iTabCount - 1);
	InitFileList(iTabCount - 1);
	Sleep(100);

	// ----------------------------------------------------------------------------------------------------
	// Init JTAG
	strMsg.Format(_T("Init JTAG...... "));
	pDownOutput->AddOutBox(strMsg);
	/*
	//pJTAG->JTAGClose();
	pDownloaderDlg->InitSPI();

	int iCnt = 0;
	while (TRUE) {
		if ((err = EN673_JTAG_INIT(m_Platform[iPlatformSel].GetJTAGClkdiv())) == 0) break;
		if (iCnt>10) {
			strMsg.Format(_T("Fail : Can't initialize JTAG. (Error : 0x%08x)"), err);
			goto END;
		}
		iCnt++;
		Sleep(0);
	}
	*/
#if 1
	int state = 0;

	if (ConnectSocket != NULL)
		state = sendMsg(ConnectSocket, "rem_check ");

	if (state < 0)
	{
		strMsg.Format(_T("Fail : Can't initialize JTAG"));
		goto END;
	}

	char ocd_flag;
	state = recv(ConnectSocket, &ocd_flag, sizeof(ocd_flag), 0);

	if (state > 0)
	{
		if (ocd_flag != '0')
		{
			strMsg.Format(_T("Fail : Can't initialize JTAG"));
			goto END;
		}
	}
	else
	{
		strMsg.Format(_T("Fail : Can't initialize JTAG"));
		goto END;
	}
#endif

	strMsg.Format(_T("End\r\n"));
	pDownOutput->AddOutBox(strMsg);

	// ----------------------------------------------------------------------------------------------------
	strBinPath = m_BinFile[iNum].strBinPath;

	// File Open
	pBinFile = new CFile;

	pBinFile->Open(strBinPath, CFile::modeRead, &FileErr);
	switch (FileErr.m_cause) // Error Check
	{
	case CFileException::none: // no error
		break;
	case CFileException::fileNotFound:
		strMsg = _T("The file could not be located.");
		goto END;
	case CFileException::accessDenied:
		strMsg = _T("The file could not be accessed.");
		goto END;
	default:
		strMsg = _T("Can't open file.");
		goto END;
	}

	// Read File
	UINT32 uiSize = pBinFile->GetLength();
	UINT32 uiSizeAdj = ((uiSize + 4) >> 2) << 2;

	memblock = new char[uiSizeAdj];
	Nmemblock = new char[uiSizeAdj + 1024];
	memset(memblock, 0, sizeof(char)*uiSizeAdj);
	memset(Nmemblock, 0, sizeof(char)*(uiSizeAdj + 1024));

	if (pBinFile->Read(memblock, uiSize) != uiSize)
	{
		pBinFile->Close();
		strMsg = _T("File cannot be read.");
		goto END;
	}
	pBinFile->Close();

	// change endian fr
	memblock32 = (UINT32*)memblock;
	Nmemblock32 = (UINT32*)Nmemblock;
	for (i = 0; i < (uiSizeAdj / 4) + 1; i++){
		*(Nmemblock32 + i) = jtag_htonl((UINT32)*(memblock32 + i));
		//*(Nmemblock32 + i) = ((UINT32)*(memblock32 + i));
		Sleep(0);
	}



	// Code and data copy
	UCHAR chIncludeBoot = pDownSectionWrite673->m_Check_IncludeBoot.GetCheck();
	UCHAR chStartCnt = chIncludeBoot ? 0 : 1;

	// Reset
	// Check Section Write Mode
	if (chStartCnt == 0) {
		tCodeMemInfo *pCodeMemInfo = (tCodeMemInfo*)Nmemblock32;
		//tCodeMemInfo *pCodeMemInfo = (tCodeMemInfo*)memblock32;
		for (int i = CODE_SECTION_IDX(RESET); i <= CODE_SECTION_IDX(DATA); i++)
		{
			if (INMIDDLE(pCodeMemInfo->section[i].s, 0x06000000, 0x07000000 - 1)) {
				strMsg.Format(_T("Fail : This is not a section write binary. Please check again."));
				goto END;
			}
		}
	}

#define MAX_BOOTCOUNT	10
	UINT uiBootCount = 0;
	UINT uiBootSuccessFlag = 0;
	for (int j = chStartCnt; j < 3; j++) 
	{
	BOOTRETRY:
		if (j == 0) {
			// Reset
			//if (pJTAG->rst()) { strMsg.Format(_T("Fail : rst (Error : 0x%08x)"), err); goto END; }
			state = sendMsg(ConnectSocket, "rem_rst ");
			if (state < 0)
			{
				strMsg.Format(_T("Fail : rst"));
				goto END;
			}
			Sleep(500);
		}
		if (j == 0 || j == 1) {
			// Stall CPU
			if ((state = sendMsg(ConnectSocket, "rem_st ")) == -1)
			{ strMsg.Format(_T("Fail : now unstalled")); goto END; }
			Sleep(1000);
			/*
			UINT8 stalled = 0;
			for (UINT8 ncpu = 4; ncpu < 6; ncpu++){
				try {
					if (err = jtag_stall_cpu(ncpu)) throw err;
					if (err = pJTAG->checkstalledcpu(ncpu, &stalled)) throw err;
					if (!stalled) throw 0xffffffff;
				}
				catch (UINT32 err) {
					strMsg.Format(_T("Fail : now unstalled. (Error : 0x%08x)"), err);
					goto END;
				}
			}
			*/

			// Reset CPU
			//if (err |= pJTAG->rc()) { strMsg.Format(_T("Fail : rc (Error : 0x%08x)"), err); goto END; }
			
			if ((state = sendMsg(ConnectSocket, "rem_rc ")) == -1) 
			{ strMsg.Format(_T("Fail : rc")); goto END; }
			Sleep(1000);
		}
		if (j == 0) {
			//if (err |= pJTAG->set(0x04000000)) { strMsg.Format(_T("Fail : set pc (Error : 0x%08x)"), err); goto END; }
			//if (err |= pJTAG->urc(0)) { strMsg.Format(_T("Fail : urc (Error : 0x%08x)"), err); goto END; }
			if ((state = sendMsg(ConnectSocket, "rem_set 0x04000000 cpu0 ")) == -1)
			{ strMsg.Format(_T("Fail : set pc")); goto END; }
			Sleep(1000);
			if ((err |= sendMsg(ConnectSocket, "rem_urc cpu0 ")) == -1)
			{ strMsg.Format(_T("Fail : urc")); goto END; }
		}

		// Section Write
		if (!RunSectionWrite(j, Nmemblock32, memblock32, strMsg)) goto END;
	
#if 1
		if (j == 0) {
			//if (err |= example_write_cpu_register(0x04000100, 4)) { strMsg.Format(_T("Fail : set pc (Error : 0x%08x)"), err); goto END; }
#if 1
			if (state = sendMsg(ConnectSocket, "rem_set 0x04000100 cpu0 ") < 0) { strMsg.Format(_T("Fail : set pc")); goto END; }
#else
			sendMsg(ConnectSocket, "rem_memoryset0 ");
#endif
			Sleep(100);
			//if (err |= jtag_unstall_cpu(4)) { strMsg.Format(_T("Fail : unstall cpu (Error : 0x%08x)"), err); goto END; }
			//{strMsg.Format(_T("Fail : unstall cpu")); goto END; }
			state = sendMsg(ConnectSocket, "rem_ust cpu0 ");
			if(state < 0)
			{	strMsg.Format(_T("Fail : now stalled"));	goto END;	}

			//UINT8 stalled = 0;
			//if (err |= pJTAG->checkstalledcpu(4, &stalled)) { strMsg.Format(_T("Fail : check stall cpu (Error : 0x%08x)"), err); goto END; }
			//if (stalled) {
			//	strMsg.Format(_T("Fail : now stalled. (Error : 0x%08x)"), err);
			//	goto END;
			//}
		}

		if (j == 2) {
			for (UINT8 ncpu = 4; ncpu <= 5; ncpu++){
				//if (err |= jtag_unreset_cpu(ncpu)) { strMsg.Format(_T("Fail : unreset cpu (Error : 0x%08x)"), err); goto END; }
				//if (err |= example_write_cpu_register(0x04000100, ncpu)) { strMsg.Format(_T("Fail : set pc (Error : 0x%08x)"), err); goto END; }
#if 1
				if (ncpu == 4)
				{
					sendMsg(ConnectSocket, "rem_urc cpu0 ");
					Sleep(100);
					sendMsg(ConnectSocket, "rem_set 0x04000100 cpu0 ");
				}
				if (ncpu == 5) 	
				{
					sendMsg(ConnectSocket, "rem_urc cpu1 ");
					Sleep(100);
					sendMsg(ConnectSocket, "rem_set 0x04000100 cpu1 ");
				}
#else
				if (ncpu == 4) 	sendMsg(ConnectSocket, "rem_memoryset0 ");
				if (ncpu == 5) 	sendMsg(ConnectSocket, "rem_memoryset1 ");
#endif
				//if (err |= jtag_unstall_cpu(ncpu)) { strMsg.Format(_T("Fail : unstall cpu (Error : 0x%08x)"), err); goto END; }
				Sleep(100);
				sendMsg(ConnectSocket, "rem_ust ");
			}
		}
#endif

#if 1
		if (j == 0) 
		{
			// 부팅 대기
			Sleep(1000);
			
			/*
			// Stall CPU
			UINT8 stalled = 0;
			for (UINT8 ncpu = 4; ncpu < 6; ncpu++){
				try {
					if (err = jtag_stall_cpu(ncpu)) throw err;
					if (err = pJTAG->checkstalledcpu(ncpu, &stalled)) throw err;
					if (!stalled) throw 0xffffffff;
				}
				catch (UINT32 err) {
					strMsg.Format(_T("Fail : now unstalled. (Error : 0x%08x)"), err);
					goto END;
				}
			}
			*/

#if 1
			// Stall check 부분 필요
			// jtag_check_stalled_cpu 필요
			UINT8 stalled = 0;
			char stall_flag;
			for (UINT8 ncpu = 4; ncpu < 6; ncpu++)
			{

				if (ncpu == 4)
				{
					sendMsg(ConnectSocket, "rem_st cpu0 ");
					Sleep(100);
					if (sendMsg(ConnectSocket, "rem_cst cpu0 "));
				}
				if (ncpu == 5)
				{
					sendMsg(ConnectSocket, "rem_st cpu1 ");
					Sleep(100);
					if (sendMsg(ConnectSocket, "rem_cst cpu1 "));
				}
				state = recv(ConnectSocket, &stall_flag, sizeof(stall_flag), 0);
				if (stall_flag == '0')
				{
					strMsg.Format(_T("Fail : now unstalled."));
					goto END;
				}
			}
#endif

			// Boot Check
#define BOOT_CHECK			0x040000f0
#define BOOT_CHECK_FLAG		0x06730673

			//err = pJTAG->read32(0x040000f0, &uiBootSuccessFlag, 1, 0);
			err = getDataFromRemote(ConnectSocket, BOOT_CHECK, 4, 0, &uiBootSuccessFlag);
			uiBootSuccessFlag = ntohl(uiBootSuccessFlag);
			if (uiBootSuccessFlag != BOOT_CHECK_FLAG) {
				uiBootCount++;
				if (uiBootCount > 10) {
					strMsg.Format(_T("Fail : Write"));
					goto END;
				}
				else {
					strMsg.Format(_T("retry! (%d/10)\r\n"), uiBootCount);
					pDownOutput->AddOutBox(strMsg);
					goto BOOTRETRY;
				}
			}
			else {
				uiBootSuccessFlag = 0;
				//err = pJTAG->write32(BOOT_CHECK, &uiBootSuccessFlag, 1, 0);
				uiBootSuccessFlag = ntohl(uiBootSuccessFlag);
				err = setDataFromRemote(ConnectSocket, BOOT_CHECK, 4, 0, &uiBootSuccessFlag);
			}
		}
#endif

		strMsg.Format(_T("End\r\n"));
		pDownOutput->AddOutBox(strMsg);
	}

	sendMsg(ConnectSocket, "rem_rst ");
	//tap_reset_global(); // Tap Reset 16번. JTAG Tab, JTAG 초기화

	strMsg.Format(_T("Write Complete!\r\n"));
	pDownOutput->AddOutBox(strMsg);

	bReturn = TRUE;

END:
	// Reset
	//tap_reset(); // Tap Reset 8번. JTAG Tab 초기화
	//tap_reset_global(); // Tap Reset 16번. JTAG Tab, JTAG 초기화
	//tap_reset_global0(); // Tap Reset 32번. JTAG Tab, JTAG, SYSTEM 초기화

	// Start JTAG Function
	//pJTAG->StartJTAGFunction(bJTAGOpen, strMsg);

	if (bReturn) {
	}
	else {
		if (strMsg != _T("")) {

			NetClo(ConnectSocket);
			ConnectSocket = NULL;
			Sleep(10);
			NetClo(StateSocket);
			ConnectSocket = NULL;

			pDownOutput->AddOutBox(strMsg + _T("\r\n"));
			AfxMessageBox(strMsg, MB_ICONWARNING);
		}
	}

	delete[] memblock;
	delete[] Nmemblock;
	delete pBinFile;
}

// iNum
// 0 : Boot
// 1 : CPU0
// 2 : CPU1
BOOL CDownloaderDlg::RunSectionWrite(int iNum, UINT32* uiData, UINT32* uiiData, CString& strMsg)
{
	int i = 0;
	int id = 0;
	int cpu = 0;
	UINT32 err = 0;

	if (iNum == 0) {
		strMsg.Format(_T("=========== Boot... "));
		pDownOutput->AddOutBox(strMsg);
		id = 0;
		cpu = 0;
		printf("=========== Boot... ");
	}
	else if (iNum == 1) {
		strMsg.Format(_T("=========== CPU0... "));
		pDownOutput->AddOutBox(strMsg);
		id = 1;
		cpu = 0;
		printf("=========== CPU0... ");
	}
	else if (iNum == 2) {
		strMsg.Format(_T("=========== CPU1... "));
		pDownOutput->AddOutBox(strMsg);
		id = 2;
		cpu = 1;
		printf("=========== CPU1... ");
	}

	// Find its FMA
	for (i = 0; i < id; i++) uiData += (*uiData >> 2);

	// Get Section Information
	tCodeMemInfo *pCodeMemInfo = (tCodeMemInfo*)uiData;
	UINT32 fma_base = (UINT32)uiiData;
	UINT32 start_of_addr = pCodeMemInfo->section[VMA_TO_LMA(CODE_SECTION_IDX(RESET))].s;

	UINT32 vma_s = 0;
	UINT32 vma_e = 0;
	UINT32 lma_s = 0;
	UINT32 len = 0;
	UINT32 remainlen = 0;
	UINT32 pos = 0;
	UINT32 addr = 0;
	UINT32 uiSizeAdj = 0;
	UINT32 localaddr = 0;
	UINT32 module_idx = 0;

	for (i = CODE_SECTION_IDX(RESET); i <= CODE_SECTION_IDX(DATA); i++) {			// $CMT-ygkim-150424: copy sections from flash to its corresponding VMA
		vma_s = pCodeMemInfo->section[i].s;
		vma_e = pCodeMemInfo->section[i].e;
		lma_s = pCodeMemInfo->section[VMA_TO_LMA(i)].s;
		len = vma_e - vma_s;

		printf("%02d vS(0x%08X) vE(0x%08X) lS(0x%08X) size(%d) startAddr(0x%08x) - ", i, vma_s, vma_e, lma_s, len, start_of_addr);

		// Setting Addr 
		addr = (UINT32)vma_s;
		uiSizeAdj = (((len + 3) >> 2) << 2);
		localaddr = (UINT32)(fma_base + (lma_s - start_of_addr));

		if ((addr & 0x0f000000) == SDRAM_BASE)	module_idx = cpu;
		else									module_idx = JTAG_COMMON_MODULE_IDX;
		printf("\nID:%d Addr:%x size:%x localAddr:%x module:%d \n", id, addr, uiSizeAdj, localaddr, module_idx);

		pos = 0;
		
		// Write
		if (len > 0) {
			//ftdx_flush();   //#important!!(for flush all write data) 
			sendMsg(ConnectSocket, "rem_ff ");
			Sleep(100);
			printf("addr + pos = 0x%08X\n", addr + pos);
			for (remainlen = uiSizeAdj; remainlen >= MEM_WRITE_BUFFER_SIZE; remainlen -= MEM_WRITE_BUFFER_SIZE){
				//UINT32 temp = ntohl(localaddr + pos);
				//if (err |= pJTAG->write32(addr + pos, (UINT32*)(localaddr + pos), MEM_WRITE_BUFFER_SIZE / 4, module_idx)) {
				if (err |= setDataFromRemote(ConnectSocket, addr + pos, MEM_WRITE_BUFFER_SIZE, module_idx, (UINT32*)(localaddr + pos))) {
					strMsg.Format(_T("Fail Write. (Error : 0x%08x)"), err);
					return FALSE;
				}
				pos += MEM_WRITE_BUFFER_SIZE;
			}

			if (remainlen){
				//if (err |= pJTAG->write32(addr + pos, (UINT32*)(localaddr + pos), (remainlen / 4) + 1, module_idx)) {
				if (err |= setDataFromRemote(ConnectSocket, addr + pos, remainlen +1 , module_idx, (UINT32*)(localaddr + pos))) {
					strMsg.Format(_T("Fail Write. (Error : 0x%08x)"), err);
					return FALSE;
				}
			}

			//Verify
			//Compare 4kbytes 
			//If different write again
			char retry = 0;
			char veribuf[MEM_WRITE_BUFFER_SIZE + 1024];
			remainlen = 0;
			pos = 0;
			for (remainlen = len; remainlen > MEM_WRITE_BUFFER_SIZE; remainlen -= MEM_WRITE_BUFFER_SIZE) {
				retry = 0;
				//if (err |= pJTAG->read32(addr + pos, (UINT32*)veribuf, MEM_WRITE_BUFFER_SIZE / 4, module_idx)) {
				if (err |= getDataFromRemote(ConnectSocket, addr + pos, MEM_WRITE_BUFFER_SIZE, module_idx, (UINT32*)veribuf)) {
					strMsg.Format(_T("Fail Verify. (Error : 0x%08x)"), err);
					return FALSE;
				}
				printf("v1");
				while (memcmp(veribuf, (char*)(localaddr + pos), MEM_WRITE_BUFFER_SIZE)){
					//if (err |= pJTAG->write32(addr + pos, (UINT32*)(localaddr + pos), MEM_WRITE_BUFFER_SIZE / 4, module_idx)) {
					if (err |= setDataFromRemote(ConnectSocket, addr + pos, MEM_WRITE_BUFFER_SIZE, module_idx, (UINT32*)(localaddr + pos))) {
						strMsg.Format(_T("Fail Verify. (Error : 0x%08x)"), err);
						return FALSE;
					}
					if (++retry > MW_MAX_RETRY_NUM){
						strMsg.Format(_T("Over Max Retry for write!"));
						return FALSE;
					}
					//if (err |= pJTAG->read32(addr + pos, (UINT32*)veribuf, MEM_WRITE_BUFFER_SIZE / 4, module_idx)) {
					if (err |= getDataFromRemote(ConnectSocket, addr + pos, MEM_WRITE_BUFFER_SIZE, module_idx, (UINT32*)veribuf)) {
						strMsg.Format(_T("Fail Verify. (Error : 0x%08x)"), err);
						return FALSE;
					}
				}
				pos += MEM_WRITE_BUFFER_SIZE;
			}

			if (remainlen){
				retry = 0;
				//if (err |= pJTAG->read32(addr + pos, (UINT32*)veribuf, remainlen / 4, module_idx)) {
				if (err |= getDataFromRemote(ConnectSocket, addr + pos, remainlen, module_idx, (UINT32*)veribuf)) {
					strMsg.Format(_T("Fail Verify. (Error : 0x%08x)"), err);
					return FALSE;
				}
				printf("v2");
				while (memcmp(veribuf, (char*)(localaddr + pos), remainlen)){
					//if (err |= pJTAG->write32(addr + pos, (UINT32*)(localaddr + pos), remainlen / 4, module_idx)) {
					if (err |= setDataFromRemote(ConnectSocket, addr + pos, remainlen, module_idx, (UINT32*)(localaddr + pos))) {
						strMsg.Format(_T("Fail Verify. (Error : 0x%08x)"), err);
						return FALSE;
					}
					if (++retry > MW_MAX_RETRY_NUM){
						strMsg.Format(_T("Over Max Retry for write!"));
						return FALSE;
					}
					//if (err |= pJTAG->read32(addr + pos, (UINT32*)veribuf, remainlen / 4, module_idx)) {
					if (err |= getDataFromRemote(ConnectSocket, addr + pos, remainlen, module_idx, (UINT32*)veribuf)) {
						strMsg.Format(_T("Fail Verify. (Error : 0x%08x)"), err);
						return FALSE;
					}
				}
			}
			printf("\n");
		}
	}

	return TRUE;
}

// ====================================================================================================
// CDownloaderDlg::JTAGFlashTest672
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CDownloaderDlg::JTAGFlashTest672()
{
	int i = 0;
	int iCnt = 0;
	BOOL bReturn = FALSE;
	UINT32 err = 0;
	CString strMsg = _T("");

	UCHAR* memblock = NULL;
	UINT32* memblock32 = NULL;

	// Clear Output Box
	pDownOutput->AddOutBox(_T("JTAG Flash Test \r\n"), DOWNOUTPUT_CLEARALL);

	// Change Tab
	int iTabCount = m_Tab_List.GetItemCount();
	m_Tab_List.SetCurSel(iTabCount - 1);
	InitFileList(iTabCount - 1);
	Sleep(100);

	// ----------------------------------------------------------------------------------------------------
	// Init JTAG
	strMsg.Format(_T("Init JTAG...... "));
	pDownOutput->AddOutBox(strMsg);

	/*
	pDownloaderDlg->InitSPI();

	iCnt = 0;
	while (TRUE) {
	if ((err = EN673_JTAG_INIT(m_Platform[iPlatformSel].GetJTAGClkdiv())) == 0) break;
	if (iCnt>10) {
	strMsg.Format(_T("Fail : Can't initialize JTAG. (Error : 0x%08x)"), err);
	goto END;
	}
	iCnt++;
	Sleep(0);
	}

	// Reset CPU
	// 리셋을 안하면 flash id가 읽어지지 않음
	if (err |= pJTAG->rc()) { strMsg.Format(_T("Fail : rc (Error : 0x%08x)"), err); goto END; }
	*/
#if 1
	int state = 0;

	if (ConnectSocket != NULL)
		state = sendMsg(ConnectSocket, "rem_check ");

	if (state < 0)
	{
		strMsg.Format(_T("Fail : Can't initialize JTAG"));
		goto END;
	}

	char ocd_flag;
	state = recv(ConnectSocket, &ocd_flag, sizeof(ocd_flag), 0);

	if (state > 0)
	{
		if (ocd_flag != '0')
		{
			strMsg.Format(_T("Fail : Can't initialize JTAG"));
			goto END;
		}
	}
	else
	{
		strMsg.Format(_T("Fail : Can't initialize JTAG"));
		goto END;
	}
#endif

	strMsg.Format(_T("End\r\n"));
	pDownOutput->AddOutBox(strMsg);

	// Stall CPU
	strMsg.Format(_T("Stall..... "));
	pDownOutput->AddOutBox(strMsg);
	sendMsg(ConnectSocket, "rem_st ");
	/*
	UINT8 stalled = 0;
	for (UINT8 ncpu = 4; ncpu < 6; ncpu++) {
	try {
	if (err = jtag_stall_cpu(ncpu)) throw err;
	if (err = pJTAG->checkstalledcpu(ncpu, &stalled)) throw err;
	if (!stalled) throw 0xffffffff;
	}
	catch (UINT32 err) {
	strMsg.Format(_T("Fail : now unstalled. (Error : 0x%08x)"), err);
	goto END;
	}
	}
	*/

	strMsg.Format(_T("Success : now stalled\r\n"));
	pDownOutput->AddOutBox(strMsg);

#if !CHANGE_EN674
	// Watchdog
	if (err |= reset_sys_wdt()) {    // Add for Reset Watchdog!!!! Flash write will fail when watchdog enabled!
		strMsg.Format(_T("Watchdog enable fail! (Error : 0x%08x)"), err);
		goto END;
	}
#endif

	// Init Flash
	strMsg.Format(_T("Init Flash...... "));
	pDownOutput->AddOutBox(strMsg);

	iCnt = 0;
	while (TRUE) {
		if ((err = Sfls_init_quad()) == 0) break;
		if (iCnt>5) {
			strMsg.Format(_T("Fail : Can't init flash memory. (Error : 0x%08x)"), err);
			goto END;
		}
		iCnt++;
		Sleep(0);
	}

	strMsg.Format(_T("End\r\n"));
	pDownOutput->AddOutBox(strMsg);

	// ----------------------------------------------------------------------------------------------------
	// Start
	// Get Size
	UINT uiSize = 0;
	if (err = Get_device_SIZE(&uiSize)) {
		strMsg.Format(_T("Getting flash id failed."));
		goto END;
	}
	uiSize = uiSize / 8 * 1024 * 1024; // Megabit -> Byte

	// Erase
	if (!JTAGErase(0, uiSize, strMsg))
		goto END;

	// Write
	memblock = new UCHAR[uiSize];
	memset(memblock, 0, sizeof(UCHAR)*uiSize);
	memblock32 = (UINT32*)memblock;

	if (!JTAGWrite(0, uiSize, memblock32, strMsg))
		goto END;

	// Verify
	if (!JTAGVerify(0, uiSize, memblock, strMsg))
		goto END;

	strMsg.Format(_T("Flash Test Complete!\r\n"));
	pDownOutput->AddOutBox(strMsg);

	bReturn = TRUE;
END:
	// Reset
	//tap_reset_global0();

	sendMsg(ConnectSocket, "rem_rst ");

	if (bReturn) {
	}
	else {
		if (strMsg != _T("")) {
			NetClo(ConnectSocket);
			ConnectSocket = NULL;
			Sleep(10);
			NetClo(StateSocket);
			ConnectSocket = NULL;

			pDownOutput->AddOutBox(strMsg + _T("\r\n"));
			AfxMessageBox(strMsg, MB_ICONWARNING);
		}
	}

	// Memory 해제
	if (memblock != NULL)	delete[] memblock;
}

void CDownloaderDlg::OnTcnSelchangeTabList(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int iTabSel = m_Tab_List.GetCurSel();
	InitFileList(iTabSel);

	*pResult = 0;
}


void CDownloaderDlg::OnBnClickedCheckBinuse1() { OnBnClickedCheckBinuse(0); }
void CDownloaderDlg::OnBnClickedCheckBinuse2() { OnBnClickedCheckBinuse(1); }
void CDownloaderDlg::OnBnClickedCheckBinuse3() { OnBnClickedCheckBinuse(2); }
void CDownloaderDlg::OnBnClickedCheckBinuse4() { OnBnClickedCheckBinuse(3); }
void CDownloaderDlg::OnBnClickedCheckBinuse(int iNum)
{
	m_BinFile[iNum].bBinUse = m_Chk_BinUse[iNum].GetCheck();
	m_Edit_EnableWindow(iNum, m_BinFile[iNum].bBinUse);
	if(m_BinFile[iNum].bBinUse == 1)
		m_Chk_Option(iNum);
}

// ====================================================================================================
// CDownloaderDlg :: m_Edit_EnableWindow
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CDownloaderDlg::m_Edit_EnableWindow(int iNum, BOOL bEnable)
{
	m_Edit_BinPath[iNum].EnableWindow(bEnable);
	m_Edit_SectorBgn[iNum].EnableWindow(bEnable);
}

void CDownloaderDlg::m_Chk_Option(int iNum)
{
	CString strMakefilePath = _T("");
	CString strPath = _T("");

	m_Edit_BinPath[iNum].GetWindowTextW(strPath);
	if (0 < strPath.ReverseFind('\\')) {
		strPath = strPath.Left(strPath.ReverseFind('\\'));
		strPath = strPath.Left(strPath.ReverseFind('\\'));
	}
	strMakefilePath = strPath + _T("\\Makefile");

	// Config File Load
	CStdioFile makeFile;
	CString strLine = _T("");
	CString strVari = _T("");
	int intVari = 0;
	if (!makeFile.Open(strMakefilePath, CFile::modeRead))
		return;

	while (makeFile.ReadString(strLine))
	{
		if (strLine.Find(ETHSUPPORT_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 1, '=');
			if (strVari.Find(_T("y")) != -1)
				pDownCompileOption673->m_Chk_Ethernet.SetCheck(1);
			else
				pDownCompileOption673->m_Chk_Ethernet.SetCheck(0);
		}
		else if (strLine.Find(WIFISUPPORT_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 1, '=');
			if (strVari.Find(_T("y")) != -1)
				pDownCompileOption673->m_Chk_WiFi.SetCheck(1);
			else
				pDownCompileOption673->m_Chk_WiFi.SetCheck(0);
		}
		else if (strLine.Find(ONVIFSUPPORT_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 1, '=');
			if (strVari.Find(_T("y")) != -1)
				pDownCompileOption673->m_Chk_Onvif.SetCheck(1);
			else
				pDownCompileOption673->m_Chk_Onvif.SetCheck(0);
		}
		else if (strLine.Find(ACTIVEXSUPPORT_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 1, '=');
			if (strVari.Find(_T("y")) != -1)
				pDownCompileOption673->m_Chk_ActiveX.SetCheck(1);
			else
				pDownCompileOption673->m_Chk_ActiveX.SetCheck(0);
		}
	}

	pDownCompileOption673->ChangeOption();
}


void CDownloaderDlg::OnEnChangeEditBinpath1() { OnEnChangeEditBinpath(0); }
void CDownloaderDlg::OnEnChangeEditBinpath2() { OnEnChangeEditBinpath(1); }
void CDownloaderDlg::OnEnChangeEditBinpath3() { OnEnChangeEditBinpath(2); }
void CDownloaderDlg::OnEnChangeEditBinpath4() { OnEnChangeEditBinpath(3); }
void CDownloaderDlg::OnEnChangeEditBinpath(int iNum)
{
	m_Edit_BinPath[iNum].GetWindowTextW(m_BinFile[iNum].strBinPath);

	InitBinFileInfo(iNum);
	//InitFileList(iNum);
	InitFileList(m_Tab_List.GetCurSel());
}


void CDownloaderDlg::OnEnChangeEditSectorBgn1() { OnEnChangeEditSectorBgn(0); }
void CDownloaderDlg::OnEnChangeEditSectorBgn2() { OnEnChangeEditSectorBgn(1); }
void CDownloaderDlg::OnEnChangeEditSectorBgn3() { OnEnChangeEditSectorBgn(2); }
void CDownloaderDlg::OnEnChangeEditSectorBgn4() { OnEnChangeEditSectorBgn(3); }
void CDownloaderDlg::OnEnChangeEditSectorBgn(int iNum)
{
	// SectorBgn 적용
	CString strSectorBgn = _T("");
	m_Edit_SectorBgn[iNum].GetWindowTextW(strSectorBgn);
	m_BinFile[iNum].uiSectorBgn = _ttoi(strSectorBgn);

	// 파일 정보 변경
	//InitBinFileInfo(iNum);


	if (m_Tab_List.GetCurSel() == 1)
	{
		m_pDlg_Output->ShowWindow(SW_SHOW);
		RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
		return;
	}
}


void CDownloaderDlg::OnBnClickedButtonOpenbinpath1() { OnBnClickedButtonOpenbinpath(0); }
void CDownloaderDlg::OnBnClickedButtonOpenbinpath2() { OnBnClickedButtonOpenbinpath(1); }
void CDownloaderDlg::OnBnClickedButtonOpenbinpath3() { OnBnClickedButtonOpenbinpath(2); }
void CDownloaderDlg::OnBnClickedButtonOpenbinpath4() { OnBnClickedButtonOpenbinpath(3); }
void CDownloaderDlg::OnBnClickedButtonOpenbinpath(int iNum)
{
	CString strBinPath = m_BinFile[iNum].strBinPath;
	CString strDefExt = _T("bin");
	CString strFilter = _T("Binary Files(*.bin)|*.bin|Hex Files(*.hex)|*.hex|");

	if (strBinPath == _T(""))
		Trace("Bin File Open Path Null");
	else
		Trace("%s", strBinPath);



	// Open Dialog
	if (!ShowOpenFileDlg(&strBinPath, strDefExt, strFilter, this))
		return;

	// Open
	SetBinPath(iNum, strBinPath);
}


// ====================================================================================================
// CDownloaderDlg :: InitBinFileInfo
// ----------------------------------------------------------------------------------------------------
/*
// Bin File 관련이 변경되었을 때 m_BinFile 변경.
BINFILE 구조체
bBinUse -> Bin File 사용여부(빌드, 다운로드 등...). 사용자가 설정함. Ini file에 저장됨
strBinPath -> Bin File Path. 사용자가 Edit Ctrl에 직접 작성하거나 Open을 통해 열음. Ini file에 저장됨
iSectorBgn -> Sector 시작 Number. 사용자가 설정함. Ini File에 저장됨

iSectorEnd -> Sector 끝 Number. 파일용량 가지고 계산해서 설정. (SectorNum)
iSectorNum -> Sector 크기... 파일용량 가지고 계산함
// EISC
strMkPath  -> Make file path. Bin file을 토대로 찾아봄
strEpxPath -> Epx file path. Mk file을 토대로 찾아봄
// OpenRISC
strMkPath  -> makefile  / binfile 폴더의 상위폴더에 있음
strConPath -> config.mk / makefile이 있는 폴더에 같이 있음.
// Tab Text 설정
*/
// ====================================================================================================
void CDownloaderDlg::InitBinFileInfo(int iNum)
{
	// 변수
	CString strPrjName = _T("");
	CString strStartAddr = _T("");
	CFileStatus fileStatus;

	// ----------------------------------------------------------------------------------------------------
	// 1. 초기화
	SetSectorEnd(iNum, 0);
	m_Edit_StartAddr[iNum].SetWindowTextW(_T(""));
	m_BinFile[iNum].uiSectorNum = 0;
	m_BinFile[iNum].strEpxPath = _T("");
	m_BinFile[iNum].strMkPath = _T("");

	// ----------------------------------------------------------------------------------------------------
	// 2. Bin File 확인
	// 1) 비어있음 -> 아예 실패
	if (m_BinFile[iNum].strBinPath == _T(""))
	{
		m_Edit_StartAddr[iNum].SetWindowTextW(_T("No File"));
	}

	// 2) 해당하는 Bin File이 존재하지 않음 -> Project 정보 확인
	CFile file;
	if (!file.Open(m_BinFile[iNum].strBinPath, CFile::modeRead))
	{
		m_Edit_StartAddr[iNum].SetWindowTextW(_T("No File"));
		goto GETPROJECT;
	}
	ULONGLONG lgFileSize = file.GetLength(); // 파일 크기
	file.Close();

	// ----------------------------------------------------------------------------------------------------
	// 3. SectorNum, SectorEnd, StartAddr
	//CFile::GetStatus(m_BinFile[iNum].strBinPath, fileStatus);
	//ULONGLONG lgFileSize = fileStatus.m_size; // 파일 크기

	// SectorNum
	m_BinFile[iNum].uiSectorNum = (UINT)(lgFileSize / SECTOR_SIZE);

	// SectorEnd
	SetSectorEnd(iNum, m_BinFile[iNum].uiSectorNum + m_BinFile[iNum].uiSectorBgn);

	// StartAddr
	strStartAddr.Format(_T("0x%x"), m_BinFile[iNum].uiSectorBgn * SECTOR_SIZE);
	m_Edit_StartAddr[iNum].SetWindowTextW(strStartAddr);

	// ----------------------------------------------------------------------------------------------------
	// 4. Get Project (Make File, EPX File Path + Project Name Setting)
GETPROJECT:
	return;
}

// ====================================================================================================
// CDownloaderDlg :: InitFileList
// ----------------------------------------------------------------------------------------------------
// Initialize FileList
// ====================================================================================================
void CDownloaderDlg::InitFileList(int iNum) // FileList 초기화
{
	// Output View
	int iTabSel = m_Tab_List.GetCurSel();

	if (iNum == 0)
	{
		pDownCompileOption673->ShowWindow(SW_SHOW);
		pDownDownOption673->ShowWindow(SW_HIDE);
		pDownSectionWrite673->ShowWindow(SW_HIDE);
		pDownOutput->ShowWindow(SW_HIDE);
	}
	else if (iNum == 1)
	{
		pDownCompileOption673->ShowWindow(SW_HIDE);
		pDownDownOption673->ShowWindow(SW_SHOW);
		pDownSectionWrite673->ShowWindow(SW_HIDE);
		pDownOutput->ShowWindow(SW_HIDE);
	}
	else if (iNum == 2)
	{
		pDownCompileOption673->ShowWindow(SW_HIDE);
		pDownDownOption673->ShowWindow(SW_HIDE);
		pDownSectionWrite673->ShowWindow(SW_SHOW);
		pDownOutput->ShowWindow(SW_HIDE);
	}
	else if (iNum == 3)
	{
		pDownCompileOption673->ShowWindow(SW_HIDE);
		pDownDownOption673->ShowWindow(SW_HIDE);
		pDownSectionWrite673->ShowWindow(SW_HIDE);
		pDownOutput->ShowWindow(SW_SHOW);
	}


	RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
	return;
}

// ====================================================================================================
// CDownloaderDlg::EnableCtrl
// ----------------------------------------------------------------------------------------------------
// CDownloaderDlg 전체 컨트롤 Enable 설정
// Thread 시에만 사용
// ====================================================================================================
void CDownloaderDlg::EnableCtrl(BOOL bEnable)
{
/*
	<< TRUE >>
		스레드 돈 후(DownFunc1Thread, UartDownloadThread, BuildThread, JTAGFlashThread)
	<< FALSE >>
		스레드 시작하면서(DownFunc1Thread, UartDownloadThread, BuildThread, JTAGFlashThread)
*/
	int i = 0;

	// Main Download Button
	m_Btn_DownFunc1.EnableWindow(bEnable);
	m_Btn_DownFunc3.EnableWindow(bEnable);

	//m_Btn_DownFunc2.EnableWindow(bEnable == FALSE ? FALSE : TRUE);
	m_Btn_DownFunc4.EnableWindow(bEnable == FALSE ? FALSE : TRUE);
	m_Btn_DownFunc5.EnableWindow(bEnable == FALSE ? FALSE : TRUE);


	// Bin File
	for(i = 0; i < BINNUM; i++)
	{
		m_Chk_BinUse[i].EnableWindow(bEnable);
		m_Btn_OpenBin[i].EnableWindow(bEnable);
		m_Edit_EnableWindow(i, bEnable == FALSE ? FALSE : m_Chk_BinUse[i].GetCheck());
	}

	
	// Tab List
	pDownOutput->EnableWindow(bEnable);
	//pDownCompileOption673->EnableWindow(bEnable);
	pDownDownOption673->EnableWindow(bEnable);
	pDownSectionWrite673->EnableWindow(bEnable);
}

// ====================================================================================================
// CDownloaderDlg::GetDeviceSize_JTAG
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
int CDownloaderDlg::GetDeviceSize_JTAG() // Return MByte
{
	UINT32 uiSize = 0;
	BOOL bReturn = FALSE;

	// Init JTAG
	//pJTAG->JTAGClose();
	//pDownloaderDlg->InitSPI();

	//if (EN673_JTAG_INIT(0)) goto END;

	// Get Size
	UINT32 err = 0;
	UINT32 data = 0;

	data = ntohl((0x03 << WB_RDCMD) | (0x02 << WB_WRCMD));

	//err |= jtag_write32(SFLS_REG_BASE + _SFLS_WBCMD, (0x03 << WB_RDCMD) | (0x02 << WB_WRCMD), JTAG_COMMON_MODULE_IDX); // 강제로 Single로 바꾸는 부분?
	err = setDataFromRemote(ConnectSocket, SFLS_REG_BASE + _SFLS_WBCONT, 4, JTAG_COMMON_MODULE_IDX, &data);
	// QPI-Single로 바꾸는 부분?
	//err |= jtag_write32(SFLS_REG_BASE + _SFLS_WBCONT, 0xff600000, JTAG_COMMON_MODULE_IDX);
	data = ntohl(0xff600000);
	err = setDataFromRemote(ConnectSocket, SFLS_REG_BASE + _SFLS_WBCONT, 4, JTAG_COMMON_MODULE_IDX, &data);
	//err |= jtag_write32(SFLS_REG_BASE + _SFLS_CMD, 0xf0030200, JTAG_COMMON_MODULE_IDX);
	data = ntohl(0xf0030200);
	err = setDataFromRemote(ConnectSocket, SFLS_REG_BASE + _SFLS_CMD, 4, JTAG_COMMON_MODULE_IDX, &data);
	err |= sfls_wait_for_reg_request();

	//err |= jtag_read32(SFLS_REG_BASE + _SFLS_WBCONT, &uiSize, JTAG_COMMON_MODULE_IDX);
	err = getDataFromRemote(ConnectSocket, SFLS_REG_BASE + _SFLS_WBCONT, 4, JTAG_COMMON_MODULE_IDX, &uiSize);
	uiSize = ntohl(uiSize);
	uiSize = uiSize & 0x00ffffff;
	//err |= jtag_write32(SFLS_REG_BASE + _SFLS_WBCONT, uiSize | (0x9f << REG_CMD), JTAG_COMMON_MODULE_IDX);
	uiSize = ntohl(uiSize | (0x9f << REG_CMD));
	err = setDataFromRemote(ConnectSocket, SFLS_REG_BASE + _SFLS_WBCONT, 4, JTAG_COMMON_MODULE_IDX, &uiSize);
	//err |= jtag_write32(SFLS_REG_BASE + _SFLS_CMD, 0xf0021002, JTAG_COMMON_MODULE_IDX);
	data = ntohl(0xf0021002);
	err = setDataFromRemote(ConnectSocket, SFLS_REG_BASE + _SFLS_CMD, 4, JTAG_COMMON_MODULE_IDX, &data);
	err |= sfls_wait_for_reg_request();

	//err |= jtag_read32(SFLS_REG_BASE + _SFLS_DATOUT, &uiSize, JTAG_COMMON_MODULE_IDX);
	err = getDataFromRemote(ConnectSocket, SFLS_REG_BASE + _SFLS_DATOUT, 4, JTAG_COMMON_MODULE_IDX, &uiSize);
	uiSize = ntohl(uiSize);

	if (err) goto END;

	uiSize = (uiSize >> 8) & 0xff;
	switch (uiSize)
	{
	case 0x18: uiSize = 128 / 8; break;
	case 0x17: uiSize = 64 / 8; break;
	case 0x16: uiSize = 32 / 8; break;
	default: goto END;
	}

	bReturn = TRUE;

END:
	//sendMsg(ConnectSocket, "rem_rst ");

	//tap_reset_global();
	//pJTAG->JTAGClose();

	if (bReturn) return uiSize;
	else		return FALSE;
}

// ====================================================================================================
// CDownloaderDlg::SaveValue
// ----------------------------------------------------------------------------------------------------
// Save iniFile
// ====================================================================================================
void CDownloaderDlg::SaveValue()
{
	UINT i = 0;
	CString str = _T("");

	// ----------------------------------------------------------------------------------------------------
	// BinFile
	for (i = 0; i < BINNUM; i++)
	{
		WriteIni(SEC_DOWN, KEY_BINUSE[i], (int)m_BinFile[i].bBinUse);
		WriteIni(SEC_DOWN, KEY_BINPATH[i], m_BinFile[i].strBinPath);
		WriteIni(SEC_DOWN, KEY_BINSECBGN[i], (int)m_BinFile[i].uiSectorBgn);
	}

	// ----------------------------------------------------------------------------------------------------
	// Tab
	WriteIni(SEC_DOWN, KEY_TABSET, m_Tab_List.GetCurSel());

	// ----------------------------------------------------------------------------------------------------
	// EN673 Build Option
	WriteIni(SEC_DOWN, KEY_673BUILDOPTION_COMPILE, pDownCompileOption673->m_Cbo_Compile.GetCurSel());
	WriteIni(SEC_DOWN, KEY_673BUILDOPTION_MODE, pDownCompileOption673->m_Cbo_Mode.GetCurSel());

	WriteIni(SEC_DOWN, KEY_673BUILDOPTION_DISASSEMBLE, pDownCompileOption673->m_Chk_Disassemble.GetCheck());
	WriteIni(SEC_DOWN, KEY_673BUILDOPTION_SECTION, pDownCompileOption673->m_Chk_SectionWriteBoot.GetCheck());
	WriteIni(SEC_DOWN, KEY_673BUILDOPTION_ETHERNET, pDownCompileOption673->m_Chk_Ethernet.GetCheck());
	WriteIni(SEC_DOWN, KEY_673BUILDOPTION_WIFI, pDownCompileOption673->m_Chk_WiFi.GetCheck());
	WriteIni(SEC_DOWN, KEY_673BUILDOPTION_ONVIF, pDownCompileOption673->m_Chk_Onvif.GetCheck());
	WriteIni(SEC_DOWN, KEY_673BUILDOPTION_ACTIVEX, pDownCompileOption673->m_Chk_ActiveX.GetCheck());

	// ----------------------------------------------------------------------------------------------------
	// EN673 Download Option
	if (pDownDownOption673->m_Radio_JTAG.GetCheck())	WriteIni(SEC_DOWN, KEY_673DOWNOPTION_COM, 0);
	else												WriteIni(SEC_DOWN, KEY_673DOWNOPTION_COM, 1);
	WriteIni(SEC_DOWN, KEY_673DOWNOPTION_SIZE, pDownDownOption673->m_byDeviceSize);
	str.Format(_T("0x%X"), pDownDownOption673->m_uiUserAddress);
	WriteIni(SEC_DOWN, KEY_673DOWNOPTION_USERADDR, str);
	str.Format(_T("0x%X"), pDownDownOption673->m_uiBootAddress);
	WriteIni(SEC_DOWN, KEY_673DOWNOPTION_BOOTADDR, str);
	str.Format(_T("%02X:%02X:%02X:%02X:%02X:%02X"), pDownDownOption673->m_byMacAddress[0],
													pDownDownOption673->m_byMacAddress[1],
													pDownDownOption673->m_byMacAddress[2],
													pDownDownOption673->m_byMacAddress[3],
													pDownDownOption673->m_byMacAddress[4],
													pDownDownOption673->m_byMacAddress[5]);
	WriteIni(SEC_DOWN, KEY_673DOWNOPTION_MACADDR, str);
}


void CDownloaderDlg::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case ID_CHECK_TIMER:
		AfxBeginThread(State_Check_Thread, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
		break;
	case ID_CONNECT_TIMER:
		AfxBeginThread(Connect_Check_Thread, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CDownloaderDlg::Check_Timer_On()
{
	m_CheckTimerID = SetTimer(ID_CHECK_TIMER, Check_Time, NULL);
}

void CDownloaderDlg::Check_Timer_Off()
{
	if (m_CheckTimerID)
	{
		if (this->GetSafeHwnd())
			KillTimer(m_CheckTimerID);
		m_CheckTimerID = 0;
	}
}

void CDownloaderDlg::Connect_Timer_On()
{
	m_ConnectTimerID = SetTimer(ID_CONNECT_TIMER, Connect_Time, NULL);
}

void CDownloaderDlg::Connect_Timer_Off()
{
	if (m_ConnectTimerID)
	{
		if (this->GetSafeHwnd())
			KillTimer(m_ConnectTimerID);
		m_ConnectTimerID = 0;
	}
}

BOOL Invalidate_flsg = FALSE;
UINT State_Check_Thread(LPVOID pParam)
{
	int state = -1;

	if (StateSocket > 0)
		state = sendMsg(StateSocket, "rem_check ");
	else
		goto DISCONNECT;
	
	char ocd_flag;
	if (state != -1)
		state = recv(StateSocket, &ocd_flag, sizeof(ocd_flag), 0);
	else
		goto DISCONNECT;

	if ((state != -1))
	{
		if (ocd_flag == '0')
		{
			if (!Invalidate_flsg)
			{
				pDownloaderDlg->EnableCtrl(TRUE);
				pDownloaderDlg->m_Btn_Connect.SetIcon(IDI_CONNECT, NULL);

				Invalidate_flsg = TRUE;
			}

			return 0;
		}
		else
		{
			goto DISCONNECT;
		}
	}

DISCONNECT : 
	pDownloaderDlg->EnableCtrl(FALSE);
	pDownloaderDlg->m_Btn_Connect.SetIcon(IDI_DISCONNECT, NULL);

	NetClo(ConnectSocket);
	ConnectSocket = NULL;

	Sleep(1);

	NetClo(StateSocket);
	StateSocket = NULL;

	pDownloaderDlg->Check_Timer_Off();
	pDownloaderDlg->Connect_Timer_On();

	Invalidate_flsg = FALSE;

	return 0;
}


UINT Connect_Check_Thread(LPVOID pParam)
{
	ConnectSocket = NetCon(pDownloaderDlg->ch_ip, pDownloaderDlg->ch_port);
	Sleep(1);
	StateSocket = NetCon(pDownloaderDlg->ch_ip, pDownloaderDlg->ch_port);

	if (ConnectSocket <= 0 || StateSocket <= 0)
	{

		NetClo(ConnectSocket);
		ConnectSocket = NULL;

		NetClo(StateSocket);
		StateSocket = NULL;
	}
	else
	{
		Invalidate_flsg = FALSE;

		pDownloaderDlg->Connect_Timer_Off();
		pDownloaderDlg->Check_Timer_On();
	}

	return 0;
}

void CDownloaderDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialogEx::OnActivate(nState, pWndOther, bMinimized);

	if ((nState == WA_ACTIVE || nState == WA_CLICKACTIVE) && !bMinimized){ //활성화
		FLASHWINFO fi;
		fi.cbSize = sizeof(FLASHWINFO);
		fi.hwnd = this->GetSafeHwnd();
		fi.dwFlags = FLASHW_STOP;
		fi.uCount = -1;
		fi.dwTimeout = 0;
		::FlashWindowEx(&fi);
	}
	else // 최소화
	{

	}
}

int AckFromRemote(int fd, char* str)
{
	char recvbuf[10];
	int iResult = 0;
	char* buf = NULL;

	while (1){

		iResult = recv(fd, recvbuf, 10, 0);
		if (iResult > 0){
			if (iResult<10){
				recvbuf[iResult] = '\0';
				if (strcmp(recvbuf, str) == 0){
					printf("%s", recvbuf);
				}
			}
			break;
		}
		else{
			printf("iResult %d", iResult);
			return -1;
		}
		Sleep(1);
	}
	return 0;

}