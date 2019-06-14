
// JTAGPrintCPU1Dlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "JTAGPrintCPU1.h"
#include "JTAGPrintCPU1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

UINT RunStartJTAGPrintCPU1Thread(LPVOID pParam);
UINT RunEndJTAGPrintCPU1Thread(LPVOID pParam);
UINT RunShellCommandThread(LPVOID pParam);
UINT RunAutoSaveThread(LPVOID pParam);

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


// CJTAGPrintCPU1Dlg 대화 상자



CJTAGPrintCPU1Dlg::CJTAGPrintCPU1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CJTAGPrintCPU1Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ECM);
}

void CJTAGPrintCPU1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_JTAGPRINTCPU1_START, m_Btn_StartJTAGPrint);
	DDX_Control(pDX, IDC_BUTTON_JTAGPRINTCPU1_STRINGSAVE, m_Btn_Save);
	DDX_Control(pDX, IDC_BUTTON_JTAGPRINTCPU1_STRINGSTOP, m_Btn_Stop);
	DDX_Control(pDX, IDC_BUTTON_JTAGPRINTCPU1_STRINGCLEAR, m_Btn_Clear);
	DDX_Control(pDX, IDC_BUTTON_JTAGPRINTCPU1CLOSE, m_Btn_Close);
	DDX_Control(pDX, IDC_EDIT_JTAGPRINTCPU1_STRING, m_Edit_String);
	DDX_Control(pDX, IDC_EDIT_JTAGSHELLCOMMAND, m_Edit_RxShellCommand);
	DDX_Control(pDX, IDC_BUTTON_MINIMIZE, m_Btn_Minimize);
	DDX_Control(pDX, IDC_EDIT_MAXLINE, m_Edit_MaxLine);
	DDX_Control(pDX, IDC_STATIC_AUTOSAVEPATH, m_Static_AutoSave);
	DDX_Control(pDX, IDC_BUTTON_AUTOSAVEPATH, m_Btn_OpenPath);
	DDX_Control(pDX, IDC_BUTTON_CMDLOGSHOW, m_Btn_CmdLogShow);

}

BEGIN_MESSAGE_MAP(CJTAGPrintCPU1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_JTAGPRINTCPU1CLOSE, &CJTAGPrintCPU1Dlg::OnBnClickedButtonJtagprintcpu1close)
	ON_BN_CLICKED(IDC_BUTTON_JTAGPRINTCPU1_START, &CJTAGPrintCPU1Dlg::OnBnClickedButtonJtagprintcpu1Start)
	ON_BN_CLICKED(IDC_BUTTON_JTAGPRINTCPU1_STRINGSAVE, &CJTAGPrintCPU1Dlg::OnBnClickedButtonJtagprintcpu1Stringsave)
	ON_BN_CLICKED(IDC_BUTTON_JTAGPRINTCPU1_STRINGSTOP, &CJTAGPrintCPU1Dlg::OnBnClickedButtonJtagprintcpu1Stringstop)
	ON_BN_CLICKED(IDC_BUTTON_JTAGPRINTCPU1_STRINGCLEAR, &CJTAGPrintCPU1Dlg::OnBnClickedButtonJtagprintcpu1Stringclear)
	ON_BN_CLICKED(IDC_BUTTON_MINIMIZE, &CJTAGPrintCPU1Dlg::OnBnClickedButtonMinimize)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON_AUTOSAVEPATH, &CJTAGPrintCPU1Dlg::OnBnClickedButtonAutosavepath)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_CMDLOGSHOW, &CJTAGPrintCPU1Dlg::OnBnClickedButtonCmdlogshow)
END_MESSAGE_MAP()


// CJTAGPrintCPU1Dlg 메시지 처리기

BOOL CJTAGPrintCPU1Dlg::OnInitDialog()
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
	SetWindowText(DLG_JTAGPRINTCPU1);

	// 다이얼로그 사이즈 조정
	int x = ReadIni(SEC_WININFO, KEY_JTAGPRINTCPU1DLGLEFT, DEF_JTAGPRINTCPU1DLGLEFT);
	int y = ReadIni(SEC_WININFO, KEY_JTAGPRINTCPU1DLGTOP, DEF_JTAGPRINTCPU1DLGTOP);
	this->SetWindowPos(NULL, x, y, 520, 570, SWP_NOZORDER);

	pJTAGPrintCPU1Dlg = this;

	ConnectSocket = NULL;

	// CLOSE 버튼
	m_Btn_Close.DrawBorder(FALSE);
	m_Btn_Close.SetColor(CButtonST::BTNST_COLOR_BK_OUT, DIALOGCOLOR);
	m_Btn_Close.SetColor(CButtonST::BTNST_COLOR_BK_IN, DIALOGSUBCOLOR);

	// Minimize
	m_Btn_Minimize.DrawBorder(FALSE);
	m_Btn_Minimize.SetColor(CButtonST::BTNST_COLOR_BK_OUT, DIALOGCOLOR);
	m_Btn_Minimize.SetColor(CButtonST::BTNST_COLOR_BK_IN, DIALOGSUBCOLOR);

	// Auto Save Path Open
	m_Btn_OpenPath.SetBitmaps(IDB_OPEN, RGB(255, 0, 255));

	// Control
	// String Window
	m_Edit_String.SetLimitText(0xffffffff);
	// Save
	m_Btn_Save.SetBitmaps(IDB_SAVE, RGB(255, 0, 255));
	// Stop
	m_Btn_Stop.SetWindowTextW(_T("■"));
	// Max Line
	//m_iMaxLine = 50000000;
	m_iMaxLine = ReadIni(SEC_JTAGPRINT1, KEY_JTAGPRINTMAXLINE, DEF_JTAGPRINTMAXLINE);
	CString m_iMaxLine_str = _T("");
	m_iMaxLine_str.Format(_T("%d"), m_iMaxLine);
	m_Edit_MaxLine.SetWindowTextW(m_iMaxLine_str);

	m_Static_AutoSave.EnableWindow(FALSE);
	m_Static_AutoSave.ShowWindow(SW_HIDE);

	// Send String Limit Text 37자
	m_Edit_RxShellCommand.SetLimitText(37);

	// ----------------------------------------------------------------------------------------------------
	// Init Variable
	m_bStopJTAGPrint = FALSE;
	m_bRunJTAGPrint = FALSE;
	m_bClear = FALSE;
	m_bCommand = FALSE;
	m_bWaitClearJTAGPrint = FALSE;
	m_bAutoSave = FALSE;
	bRunStartJTAGPrintCPU1Thread = FALSE;
	bRunEndJTAGPrintCPU1Thread = FALSE;

	autosave_filename = _T("");

// ----------------------------------------------------------------------------------------------------
// Init Start
	int check = 0;
	check = ReadIni(SEC_SETTING, KEY_PRINTSTART, DEF_PRINTSTART);
	if (check == 1)
		OnBnClickedButtonJtagprintcpu1Start();

// ----------------------------------------------------------------------------------------------------
// Create Sub Dialog
	CRect rect;
	this->GetWindowRect(&rect);

	m_pDlg_CmdLogShow = new CJTAGPrintCmdLogDlg();
	m_pDlg_CmdLogShow->Create(IDD_JTAGPRINTCMDLOG, this);
	m_pDlg_CmdLogShow->SetWindowPos(NULL, rect.right, rect.top, 0, 0, SWP_SHOWWINDOW | SWP_NOZORDER | SWP_NOSIZE);

	m_pDlg_CmdLogShow->ShowWindow(SW_HIDE);
	m_ShowDlg_CmdLog = FALSE;

//	m_csJTAGPrint = new CCriticalSection();
	


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

#define OLD_PRESSED     0x40000000

BOOL CJTAGPrintCPU1Dlg::PreTranslateMessage(MSG* pMsg)
{
	CWnd* wndFocus = GetFocus();
	LPARAM lParam = pMsg->lParam;

	if (pMsg->message == WM_KEYDOWN)
	{
		if ((GetKeyState(VK_RCONTROL) & 0x8000) ||
			(GetKeyState(VK_LCONTROL) & 0x8000))
		{
			switch (pMsg->wParam)
			{
				// KEYDOWN - Ctrl + A
			case VK_A:
				if (wndFocus == (CWnd*)&m_Edit_String) {
					m_Edit_String.SetSel(0, -1);
					return TRUE;
				}
				break;

				// KEYDOWN - Ctrl + C
			case VK_C:
				if (wndFocus == NULL) return FALSE;
				break;
			}
		}
		else {
			switch (pMsg->wParam)
			{
				// KEYDOWN - ENTER
			case VK_RETURN:
				if ((lParam & OLD_PRESSED) != OLD_PRESSED)
				{
					if (wndFocus == NULL) return FALSE;
					if (wndFocus == (CWnd*)&m_Edit_RxShellCommand) {
						if (m_bRunJTAGPrint)
						{
							if (m_bCommand)
								RxShellCommand();
						}
						return TRUE;
					}
					if (wndFocus == (CWnd*)&m_Edit_String) {
						return CDialogEx::PreTranslateMessage(pMsg);
					}
				}
				break;
				// KEYDOWN - DELETE
			case VK_DELETE:
				if (wndFocus == NULL) return FALSE;
				break;
				// KEYDOWN - UP
			case VK_UP:
				if (wndFocus == NULL) return FALSE;
				if (wndFocus == (CWnd*)&m_Edit_RxShellCommand) {
					CommandShow(-1);
					return TRUE;
				}
				if (wndFocus == (CWnd*)&m_Edit_String) {
					return CDialogEx::PreTranslateMessage(pMsg);
				}
				break;
				// KEYDOWN - DOWN
			case VK_DOWN:
				if (wndFocus == NULL) return FALSE;
				if (wndFocus == (CWnd*)&m_Edit_RxShellCommand) {
					CommandShow(1);
					return TRUE;
				}
				if (wndFocus == (CWnd*)&m_Edit_String) {
					return CDialogEx::PreTranslateMessage(pMsg);
				}
				break;
			}
		}
	}

	// Default Window Message
	if (DefaultWindowMessage(pMsg))	return TRUE;
	else							return CDialogEx::PreTranslateMessage(pMsg);


}


int CJTAGPrintCPU1Dlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetWindowLongPtr(m_hWnd, GWL_STYLE, WS_SYSMENU | WS_MINIMIZEBOX);

	RedrawWindow();

	return 0;
}


void CJTAGPrintCPU1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CJTAGPrintCPU1Dlg::OnPaint()
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

		dc.TextOutW(10, 6, DLG_JTAGPRINTCPU1);

		dc.SelectObject(pOldFont);
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CJTAGPrintCPU1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CJTAGPrintCPU1Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetCapture();
	m_Point = point;

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CJTAGPrintCPU1Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (this == GetCapture())
	{
		CRect rcDialog;
		GetWindowRect(&rcDialog);

		int x = rcDialog.left + point.x - m_Point.x;
		int y = rcDialog.top + point.y - m_Point.y;

		SetWindowPos(NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		WriteIni(SEC_WININFO, KEY_JTAGPRINTCPU1DLGLEFT, x);
		WriteIni(SEC_WININFO, KEY_JTAGPRINTCPU1DLGTOP, y);

// ----------------------------------------------------------------------------------------------------
// Set Sub Dialog
		CRect rectCmdLog;

		pJTAGPrintCmdLogDlg->GetWindowRect(&rectCmdLog);
		pJTAGPrintCmdLogDlg->MoveWindow(rcDialog.right, rcDialog.bottom - rectCmdLog.Height(),	rectCmdLog.Width(), rectCmdLog.Height(), TRUE);
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void CJTAGPrintCPU1Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	ReleaseCapture();

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CJTAGPrintCPU1Dlg::OnCancel()
{
	if (bRunStartJTAGPrintCPU1Thread)
	{
		m_bRunJTAGPrint = FALSE;
		Wait(100);
	}

	SaveValue();

	if (m_bAutoSave)
	{
		AutoSave_Re();
	}
	m_bAutoSave = FALSE;

	if (ConnectSocket != NULL)
	{
		NetClo(ConnectSocket);
		ConnectSocket = NULL;
	}

	m_pDlg_CmdLogShow->DestroyWindow();
	delete m_pDlg_CmdLogShow;

	CDialogEx::OnCancel();
}

// ====================================================================================================
// CJTAGPrintCPU1Dlg::EnableCtrl
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CJTAGPrintCPU1Dlg::EnableCtrl(BOOL bEnable)
{
	m_Btn_StartJTAGPrint.EnableWindow(bEnable);
	m_Edit_MaxLine.EnableWindow(bEnable);
}


void CJTAGPrintCPU1Dlg::OnBnClickedButtonJtagprintcpu1close()
{
	OnCancel();
}


void CJTAGPrintCPU1Dlg::OnBnClickedButtonMinimize()
{
	ShowWindow(SW_MINIMIZE);
}


void CJTAGPrintCPU1Dlg::OnBnClickedButtonJtagprintcpu1Start()
{
// ----------------------------------------------------------------------------------------------------
// Server 연결
	if (!ConnectSocket)
	{
		CString strCmd = theApp.m_lpCmdLine;
		CString strAddr;
		CString strPort;

		AfxExtractSubString(strAddr, strCmd, 0, ' ');
		AfxExtractSubString(strPort, strCmd, 1, ' ');

#ifdef _DEBUG
		strAddr.Format(_T("192.168.0.199"));
		strPort = DEFAULT_PORT;
#endif
		if (strPort == _T(""))	strPort = DEFAULT_PORT;

		CStringA addr;
		CStringA port;
		char ch_ip[64];
		char ch_port[64];
		addr = strAddr;
		port = strPort;
		strcpy(ch_ip, addr.GetBuffer(addr.GetLength()));
		strcpy(ch_port, port.GetBuffer(port.GetLength()));

		ConnectSocket = NetCon(ch_ip, ch_port);
		if (ConnectSocket <= 0)
		{
			AfxMessageBox(_T("Not Connect"));
			ConnectSocket = NULL;
			return;
			//exit(0);
		}

		//Sleep(10);
		Wait(10);
	}

	if (!m_bRunJTAGPrint) {
		// Change control state
		m_Btn_StartJTAGPrint.SetWindowTextW(_T("Stop"));
		m_Btn_StartJTAGPrint.EnableWindow(FALSE);
		EnableCtrl(FALSE);

		CString m_iMaxLine_str = _T("");
		m_Edit_MaxLine.GetWindowTextW(m_iMaxLine_str);
		m_iMaxLine = _ttoi(m_iMaxLine_str);

		m_bRunJTAGPrint = TRUE;
		m_bCommand = TRUE;

		// Auto Save File Name
		// Get Time
		SYSTEMTIME time;
		GetLocalTime(&time);
		autosave_filename.Format(_T("jtag_printf_cpu1_%04d%02d%02d%02d%02d%02d%03d.txt"),
			time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);

		// Start Thread
		AfxBeginThread(RunStartJTAGPrintCPU1Thread, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
	}
	else {
		if (m_bAutoSave)
		{
			AutoSave_Re();
		}
		m_bAutoSave = FALSE;

		m_Edit_MaxLine.EnableWindow(TRUE);
		m_Btn_StartJTAGPrint.EnableWindow(FALSE);
		AfxBeginThread(RunEndJTAGPrintCPU1Thread, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
	}

}


// ====================================================================================================
// RunStartJTAGPrintCPU1Thread
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
UINT RunStartJTAGPrintCPU1Thread(LPVOID pParam)
{
	bRunStartJTAGPrintCPU1Thread = TRUE;

	// ----------------------------------------------------------------------------------------------------
	// JTAG Open
	pJTAGPrintCPU1Dlg->JTAGPrint();

	// ----------------------------------------------------------------------------------------------------
	// End
	if (!bRunEndJTAGPrintCPU1Thread) {
		pJTAGPrintCPU1Dlg->m_Btn_StartJTAGPrint.SetWindowTextW(_T("Start"));
		pJTAGPrintCPU1Dlg->m_Btn_StartJTAGPrint.EnableWindow(TRUE);
		pJTAGPrintCPU1Dlg->EnableCtrl(TRUE);
	}

	NetClo(ConnectSocket);
	ConnectSocket = NULL;
	
	Wait(10);

	bRunStartJTAGPrintCPU1Thread = FALSE;

	return 0L;
}

#define COUNT_MAX 10
// ====================================================================================================
// CJTAGPrintCPU1Dlg::JTAGPrint
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CJTAGPrintCPU1Dlg::JTAGPrint()
{
	UINT32 err = 0;
	BOOL bReturn = FALSE;
	CString strMsg = _T("");
	UINT8* memblock = NULL;

	DWORD dwResult = 0;

	// Init
	//if (!pJTAG->JTAGInitial(strMsg)) goto END;

	// Read JTAG Print
	//if (err |= pJTAG->read32(JTAG_PRINT_SIZE, &pJTAG->jtag_print_size, 1, JTAG_COMMON_MODULE_IDX)) {
	if (-1 == getDataFromRemote(ConnectSocket, JTAG_PRINT_SIZE, 4, JTAG_COMMON_MODULE_IDX, &jtag_print_size)) {
		strMsg.Format(_T("Fail read data (Error : 0x%08x)"), err);	goto END;
	}
	jtag_print_size = jtag_htonl(jtag_print_size);
	//if (err |= pJTAG->read32(JTAG_PRINT1_START, &pJTAG->jtag_print_base_CPU1, 1, JTAG_COMMON_MODULE_IDX)) {
	if (-1 == getDataFromRemote(ConnectSocket, JTAG_PRINT1_START, 4, JTAG_COMMON_MODULE_IDX, &jtag_print_base_CPU1)) {
		strMsg.Format(_T("Fail read data (Error : 0x%08x)"), err);	goto END;
	}
	jtag_print_base_CPU1 = jtag_htonl(jtag_print_base_CPU1);

	// Enable Start Button
	m_Btn_StartJTAGPrint.EnableWindow(TRUE);

	resetpos(JTAG_CPU1_MODULE_IDX);

	memblock = (UINT8*)malloc(jtag_print_size);
	
	int check_count = 0;
	while (m_bRunJTAGPrint){
		ProcessWindowMessage();
		int state = -1;
		// Stop
		if (m_bStopJTAGPrint) continue;

		if (m_bCommand)
		{
			if (check_count > COUNT_MAX)
			{
				check_count = 0;
				if (ConnectSocket != NULL)
					state = sendMsg(ConnectSocket, "rem_check ");
				else
					goto END;

				if (state == -1)
					goto END;

				char ocd_flag;
				if (ConnectSocket > 0)
					state = recv(ConnectSocket, &ocd_flag, 1, 0);

				if (state > 0)
				{
					if (ocd_flag == '1')
					{
						goto END;
					}
				}
				else
					goto END;
			}
			check_count++;
		}
#if 0
		// Clear
		if (m_bClear) {
			m_bWaitClearJTAGPrint = TRUE;
			while (m_bClear) {

				//Sleep(1); 
				ProcessWindowMessage();
				Wait(1);

			}
			m_bWaitClearJTAGPrint = FALSE;
		}
#endif

		// JTAGPrint
		if (JTAGPrint_define(memblock, JTAG_CPU1_MODULE_IDX) < 0) {
			continue;
			AfxMessageBox(_T("Fail JTAG Read!"));
			//pJTAG->JTAGClose();
			goto END;
		}
		//Sleep(10);
		Wait(10);
	}

	bReturn = TRUE;
END:
	if (bReturn) {
	}
	else {
		if (strMsg != _T("")) {
			AfxMessageBox(strMsg);
			//pJTAG->JTAGClose();
		}

		NetClo(ConnectSocket);
		ConnectSocket = NULL;
	}

	if (memblock != NULL) free(memblock);
	m_bRunJTAGPrint = FALSE;
}

// ====================================================================================================
// RunEndJTAGPrintCPU1Thread
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
UINT RunEndJTAGPrintCPU1Thread(LPVOID pParam)
{
	bRunEndJTAGPrintCPU1Thread = TRUE;

	// ----------------------------------------------------------------------------------------------------
	// Wait
	pJTAGPrintCPU1Dlg->m_bRunJTAGPrint = FALSE;
	int count = 0;
	while (bRunStartJTAGPrintCPU1Thread) { 
		//Sleep(1); 
		ProcessWindowMessage();
		Wait(1);
		if (count++ > 5000)
			break;
	}

	// thread 강제종료
	// 변수 초기화
	if (ConnectSocket != NULL)
	{
		NetClo(ConnectSocket);
		ConnectSocket = NULL;
	}


	// ----------------------------------------------------------------------------------------------------
	// Change control state
	pJTAGPrintCPU1Dlg->m_Btn_StartJTAGPrint.SetWindowTextW(_T("Start"));
	pJTAGPrintCPU1Dlg->m_Btn_StartJTAGPrint.EnableWindow(TRUE);
	pJTAGPrintCPU1Dlg->EnableCtrl(TRUE);


	// ----------------------------------------------------------------------------------------------------
	bRunEndJTAGPrintCPU1Thread = FALSE;
	return 0L;
}


// ====================================================================================================
// CJTAGPrintCPU1Dlg::DispString
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CJTAGPrintCPU1Dlg::DispString(UINT8 *pBuf)
{
	//m_csJTAGDis.Lock(); // Critical Section Lock
	m_csJTAGPrint.Lock();
	TRACE("DispString 1\r\n");
	CString strDispString = (CString)pBuf;

	int iLength = 0;
	//TRACE(strDispString);
	TRACE("DispString GetWindowTextLength %d W\r\n", strDispString.GetLength());
	if (strDispString.GetLength() < 20)
		TRACE("DispString GetWindowTextLength %s W\r\n", strDispString.GetBuffer());
	
	//up.Format(_T("test"));

#if 0
	CPoint mTempPoint = m_Edit_String.GetCaretPos();

	TRACE("DispString m_Edit_String.GetCaretPos \r\n");
	TRACE("DispString m_Edit_String.GetCaretPos x %d y %d \r\n", mTempPoint.x, mTempPoint.y);

	int mTempW = m_Edit_String.GetDlgItemTextW();
	TRACE("DispString m_Edit_String.GetDlgItemTextW mTempW %d \r\n", mTempW);
#endif
	ProcessWindowMessage();
	iLength = m_Edit_String.GetWindowTextLengthW();
	TRACE("DispString GetWindowTextLengthW\r\n");
	m_Edit_String.SetSel(iLength, iLength);
	TRACE("DispString SetSel\r\n");

	m_Edit_String.ReplaceSel(strDispString);
	TRACE("DispString 2 %d \r\n", iLength);
	strDispString = _T("");

	iLength = m_Edit_String.GetWindowTextLengthW();
	m_Edit_String.SetSel(iLength, iLength);
	TRACE("DispString 3 %d \r\n", iLength);
	// Clear Line

#if 1
	CString str = _T("");
	int iLineCount = m_Edit_String.GetLineCount();
	TRACE("DispString 4 %d \r\n", iLineCount);
	
	if (iLineCount > m_iMaxLine) {
		if (ReadIni(SEC_SETTING, KEY_PRINTAUTOSAVE, DEF_PRINTAUTOSAVE))
		{
			m_bAutoSave = TRUE;
			AutoSave();
			AfxBeginThread(RunAutoSaveThread, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
		}
		for (int i = iLineCount; i > m_iMaxLine*REMOVE_RATE + 1; i--) {
			m_Edit_String.GetWindowTextW(str);

			int iFind = str.Find('\n');
			if (iFind <= 81)		m_Edit_String.SetSel(0, iFind + 1);
			else				m_Edit_String.SetSel(0, 80);
			m_Edit_String.Clear();
		}
	}
#endif
	TRACE("DispString 5\r\n");
	m_bCommand = TRUE;
	//m_csJTAGDis.Unlock(); // Critical Section Unlock
	m_csJTAGPrint.Unlock();
}


UINT RunAutoSaveThread(LPVOID pParam)
{
	pJTAGPrintCPU1Dlg->m_Static_AutoSave.EnableWindow(TRUE);
	pJTAGPrintCPU1Dlg->m_Static_AutoSave.ShowWindow(SW_SHOW);

	CString str;

	str = _T("Log Auto Save Complete");

	pJTAGPrintCPU1Dlg->m_Static_AutoSave.SetWindowTextW(str);

	//Sleep(5000);
	Wait(5000);

	pJTAGPrintCPU1Dlg->m_Static_AutoSave.EnableWindow(FALSE);
	pJTAGPrintCPU1Dlg->m_Static_AutoSave.ShowWindow(SW_HIDE);

	return 0;
}


void CJTAGPrintCPU1Dlg::OnBnClickedButtonJtagprintcpu1Stringsave()
{
	if (m_Edit_String.GetWindowTextLengthW() <= 0) {
		AfxMessageBox(_T("Fail Save : No items"));
		return;
	}

	CString strTxtFile = _T("");
	CString strDefExt = _T("txt");
	CString strFilter = _T("Text File(*.txt)|*.txt||");

	// Save Dialog
	if (!ShowSaveFileDlg(&strTxtFile, strDefExt, strFilter, this))
		return;

	// Save
	CStdioFile file;

	if (!file.Open(strTxtFile, CFile::modeWrite | CFile::modeCreate)) return;

	CString str = _T("");
	m_Edit_String.GetWindowTextW(str);
	file.WriteString(str);

	file.Close();

	AfxMessageBox(_T("Save Complete!"));
}


void CJTAGPrintCPU1Dlg::OnBnClickedButtonJtagprintcpu1Stringstop()
{
	if (m_bStopJTAGPrint)
	{
		m_Btn_Stop.SetWindowTextW(_T("■"));
		m_bStopJTAGPrint = FALSE;
		m_bCommand = TRUE;
	}
	else
	{
		m_Btn_Stop.SetWindowTextW(_T("▶"));
		m_bStopJTAGPrint = TRUE;
		m_bCommand = FALSE;
	}
}


void CJTAGPrintCPU1Dlg::OnBnClickedButtonJtagprintcpu1Stringclear()
{
	m_Edit_String.SetSel(0, -1, TRUE);
	m_Edit_String.Clear();
}


// ====================================================================================================
// CJTAGPrintCPU1Dlg::RxShellCommand
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CJTAGPrintCPU1Dlg::RxShellCommand()
{
	TRACE("bRunStartJTAGPrintCPU1Thread = %d\r\n", bRunStartJTAGPrintCPU1Thread);

	if (!bRunStartJTAGPrintCPU1Thread)			return;
	else										AfxBeginThread(RunShellCommandThread, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
}


UINT RunShellCommandThread(LPVOID pParam)
{
	TRACE(_T("RxShellCommand Start\r\n"));

	m_csJTAGPrint.Lock(); // Critical Section Lock
	//m_csJTAGDis.Lock();
	//m_csJTAG.Unlock(100);
	TRACE("Lock %x \r\n", m_csJTAGPrint);

	pJTAGPrintCPU1Dlg->m_bCommand = FALSE;

	int i = 0;
	UINT32 err = 0;
	CString str = _T("");

	UINT32 shell_noty = 0;
	UINT32 irq = 0;

	TRACE(_T("1\r\n"));

	char chtemp[JTAGCOMMAND_SIZE] = { 0, };
	UINT32 temp[JTAGCOMMAND_SIZE / 4] = { 0, };
	
	pJTAGPrintCPU1Dlg->m_Edit_RxShellCommand.GetWindowText(str);
	pJTAGPrintCPU1Dlg->m_Edit_RxShellCommand.SetWindowTextW(_T(""));

	TRACE(_T("2\r\n"));

	// char ��ȯ
	for (i = 0; i < str.GetLength(); i++) {
		chtemp[i] = LPSTR(LPCTSTR(str.Mid(i, 1)))[0];
	}
	strcat((char*)temp, chtemp);

	TRACE(_T("3\r\n"));

	// Write Shell Command
	//if (err |= pJTAG->write32(pJTAG->JTAG_COMMAND, (UINT32*)n_temp, JTAGCOMMAND_SIZE / 4, JTAG_COMMON_MODULE_IDX)) goto END;
	if (err |= setDataFromRemote(ConnectSocket, JTAG_COMMAND, JTAGCOMMAND_SIZE, JTAG_COMMON_MODULE_IDX, (UINT32*)temp))	goto END;

	TRACE(_T("4\r\n"));
	// Shell Notify
	shell_noty = JTAG_SHELL_NOTIFY_;
	//shell_noty = htonl(JTAG_SHELL_NOTIFY);
	//if (err |= pJTAG->write32(JTAG_SHELL_NOTIFY_ADDR, &shell_noty, 1, JTAG_COMMON_MODULE_IDX)) goto END;
	if (err |= setDataFromRemote(ConnectSocket, JTAG_SHELL_NOTIFY_ADDR, 4, JTAG_COMMON_MODULE_IDX, &shell_noty))	goto END;

	TRACE(_T("5\r\n"));
	// IRQ
	irq = JTAG_CPU_IRQ1_;
	//irq = htonl(JTAG_CPU_IRQ1);
	//if (err |= pJTAG->write32(JTAG_CPU_IRQ_ADDR, &irq, 1, JTAG_COMMON_MODULE_IDX)) goto END;
	if (err |= setDataFromRemote(ConnectSocket, JTAG_CPU_IRQ_ADDR, 4, JTAG_COMMON_MODULE_IDX, &irq))	goto END;
	//bReturn = TRUE;
	TRACE(_T("6\r\n"));
	// Command Log
	if (str != _T(""))
		pJTAGPrintCmdLogDlg->m_List_CmdLog.AddString(str);
	TRACE(_T("7\r\n"));
END:
	m_csJTAGPrint.Unlock(); // Critical Section Lock
	//m_csJTAGDis.Lock();
	//m_csJTAG.Unlock();
	TRACE("UnLock %x \r\n", m_csJTAGPrint);
	if (err != 0)	return -1;
	else			return 0;
}




void CJTAGPrintCPU1Dlg::SaveValue()
{
	CString m_iMaxLine_str = _T("");
	m_Edit_MaxLine.GetWindowTextW(m_iMaxLine_str);
	m_iMaxLine = _ttoi(m_iMaxLine_str);
	WriteIni(SEC_JTAGPRINT1, KEY_JTAGPRINTMAXLINE, m_iMaxLine);
}

void CJTAGPrintCPU1Dlg::OnBnClickedButtonAutosavepath()
{
	CString strPath;

	strPath = ReadIni(SEC_SETTING, KEY_PRINTSAVEPATH, DEF_PRINTSAVEPATH);

	// Ini 파일에 Path가 없는경우
	if (strPath == _T(""))
	{
		// Get 'My Document'
		TCHAR szPath[MAX_PATH];
		SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, 0, szPath);

		// Create ecm folder
		CString strDirectory = _T("");
		strDirectory.Format(_T("%s\\ecm_retome"), szPath);
		CreateDirectory(strDirectory, NULL);

		// Create Analyze folder
		strDirectory.Format(_T("%s\\ecm_retome\\jtagprint"), szPath);
		CreateDirectory(strDirectory, NULL);

		strPath = strDirectory;
	}

	strPath.Format(_T("%s"), strPath);

	ShellExecute(NULL, _T("open"), _T("explorer"), strPath, NULL, SW_SHOW);
}


HBRUSH CJTAGPrintCPU1Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (pWnd->GetDlgCtrlID() == IDC_STATIC_AUTOSAVEPATH)
	{
		pDC->SetTextColor(RGB(255, 0, 0));
	}

	return hbr;
}


void CJTAGPrintCPU1Dlg::OnBnClickedButtonCmdlogshow()
{
	if (!m_ShowDlg_CmdLog)
	{
		CRect rectThis;
		CRect rectCmdLog;

		this->GetWindowRect(&rectThis);
		pJTAGPrintCmdLogDlg->GetWindowRect(&rectCmdLog);

		pJTAGPrintCmdLogDlg->MoveWindow(rectThis.right, rectThis.bottom - rectCmdLog.Height(), rectCmdLog.Width(), rectCmdLog.Height(), TRUE);
		
		m_Btn_CmdLogShow.SetWindowTextW(_T("<<"));
		pJTAGPrintCmdLogDlg->ShowWindow(SW_SHOW);
		m_ShowDlg_CmdLog = TRUE;
	}
	else
	{
		pJTAGPrintCmdLogDlg->OnBnClickedButtonJtagprintcmdlogClose();
		m_Btn_CmdLogShow.SetWindowTextW(_T(">>"));
		m_ShowDlg_CmdLog = FALSE;
	}
}


int CJTAGPrintCPU1Dlg::CommandShow(int sign)
{
	int count = pJTAGPrintCmdLogDlg->m_List_CmdLog.GetCount();
	int index = 0;
	CString cmd_str = _T("");
	m_Edit_RxShellCommand.GetWindowTextW(cmd_str);

	if (count)
	{
		index = pJTAGPrintCmdLogDlg->m_List_CmdLog.GetCurSel();
		
		if (index < 0 || cmd_str == _T(""))
		{
			index = pJTAGPrintCmdLogDlg->m_List_CmdLog.SetCurSel(0);
			pJTAGPrintCmdLogDlg->m_List_CmdLog.GetText(index, cmd_str);
		}
		else
		{
			if (index + sign > count - 1 || index + sign < 0)
				return -1;
			pJTAGPrintCmdLogDlg->m_List_CmdLog.SetCurSel(index + sign);
			pJTAGPrintCmdLogDlg->m_List_CmdLog.GetText(index + sign, cmd_str);
		}
		m_Edit_RxShellCommand.SetWindowTextW(cmd_str);
	}
	else
		return 0;

	return 0;
}