
// JTAGPrintCPU0Dlg.cpp : ���� ����
//

#include "stdafx.h"
#include "JTAGPrintCPU0.h"
#include "JTAGPrintCPU0Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.
UINT RunStartJTAGPrintCPU0Thread(LPVOID pParam);
UINT RunEndJTAGPrintCPU0Thread(LPVOID pParam);
UINT RunAutoSaveThread(LPVOID pParam);

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CJTAGPrintCPU0Dlg ��ȭ ����



CJTAGPrintCPU0Dlg::CJTAGPrintCPU0Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CJTAGPrintCPU0Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ECM);
}

void CJTAGPrintCPU0Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_JTAGPRINTCPU0_START, m_Btn_StartJTAGPrint);
	DDX_Control(pDX, IDC_BUTTON_JTAGPRINTCPU0_STRINGSAVE, m_Btn_Save);
	DDX_Control(pDX, IDC_BUTTON_JTAGPRINTCPU0_STRINGSTOP, m_Btn_Stop);
	DDX_Control(pDX, IDC_BUTTON_JTAGPRINTCPU0_STRINGCLEAR, m_Btn_Clear);
	DDX_Control(pDX, IDC_BUTTON_JTAGPRINTCPU0CLOSE, m_Btn_Close);
	DDX_Control(pDX, IDC_EDIT_JTAGPRINTCPU0_STRING, m_Edit_String);
	DDX_Control(pDX, IDC_BUTTON_MINIMIZE, m_Btn_Minimize);
	DDX_Control(pDX, IDC_EDIT_MAXLINE, m_Edit_MaxLine);
	DDX_Control(pDX, IDC_STATIC_AUTOSAVEPATH, m_Static_AutoSave);
	DDX_Control(pDX, IDC_BUTTON_AUTOSAVEPATH, m_Btn_OpenPath);
}

BEGIN_MESSAGE_MAP(CJTAGPrintCPU0Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_JTAGPRINTCPU0_STRINGCLEAR, &CJTAGPrintCPU0Dlg::OnBnClickedButtonJtagprintcpu0Stringclear)
	ON_BN_CLICKED(IDC_BUTTON_JTAGPRINTCPU0_START, &CJTAGPrintCPU0Dlg::OnBnClickedButtonJtagprintcpu0Start)
	ON_BN_CLICKED(IDC_BUTTON_JTAGPRINTCPU0_STRINGSAVE, &CJTAGPrintCPU0Dlg::OnBnClickedButtonJtagprintcpu0Stringsave)
	ON_BN_CLICKED(IDC_BUTTON_JTAGPRINTCPU0_STRINGSTOP, &CJTAGPrintCPU0Dlg::OnBnClickedButtonJtagprintcpu0Stringstop)
	ON_BN_CLICKED(IDC_BUTTON_JTAGPRINTCPU0CLOSE, &CJTAGPrintCPU0Dlg::OnBnClickedButtonJtagprintcpu0close)
	ON_BN_CLICKED(IDC_BUTTON_MINIMIZE, &CJTAGPrintCPU0Dlg::OnBnClickedButtonMinimize)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON_AUTOSAVEPATH, &CJTAGPrintCPU0Dlg::OnBnClickedButtonAutosavepath)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CJTAGPrintCPU0Dlg �޽��� ó����

BOOL CJTAGPrintCPU0Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	SetWindowText(DLG_JTAGPRINTCPU0);

	// ���̾�α� ������ ����
	int x = ReadIni(SEC_WININFO, KEY_JTAGPRINTCPU0DLGLEFT, DEF_JTAGPRINTCPU0DLGLEFT);
	int y = ReadIni(SEC_WININFO, KEY_JTAGPRINTCPU0DLGTOP, DEF_JTAGPRINTCPU0DLGTOP);
	this->SetWindowPos(NULL, x, y, 520, 570, SWP_NOZORDER);

	pJTAGPrintCPU0Dlg = this;

	ConnectSocket = NULL;

	// CLOSE ��ư
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
	m_Btn_Stop.SetWindowTextW(_T("��"));
	// Max Line
	//m_iMaxLine = 50000000;
	m_iMaxLine = ReadIni(SEC_JTAGPRINT0, KEY_JTAGPRINTMAXLINE, DEF_JTAGPRINTMAXLINE);
	CString m_iMaxLine_str = _T("");
	m_iMaxLine_str.Format(_T("%d"), m_iMaxLine);
	m_Edit_MaxLine.SetWindowTextW(m_iMaxLine_str);

	m_Static_AutoSave.EnableWindow(FALSE);
	m_Static_AutoSave.ShowWindow(SW_HIDE);

	// ----------------------------------------------------------------------------------------------------
	// Init Variable
	m_bStopJTAGPrint = FALSE;
	m_bRunJTAGPrint = FALSE;
	m_bClear = FALSE;
	m_bWaitClearJTAGPrint = FALSE;
	m_bAutoSave = FALSE;
	bRunStartJTAGPrintCPU0Thread = FALSE;
	bRunEndJTAGPrintCPU0Thread = FALSE;
	autosave_filename = _T("");

	// ----------------------------------------------------------------------------------------------------
	// Init Start
	int check = 0;
	check = ReadIni(SEC_SETTING, KEY_PRINTSTART, DEF_PRINTSTART);
	if (check == 1)
		OnBnClickedButtonJtagprintcpu0Start();

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

BOOL CJTAGPrintCPU0Dlg::PreTranslateMessage(MSG* pMsg)
{
	CWnd* wndFocus = GetFocus();
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
				if (wndFocus == NULL) return FALSE;
				if (wndFocus == (CWnd*)&m_Edit_String) {
					return CDialogEx::PreTranslateMessage(pMsg);
				}
				break;
				// KEYDOWN - DELETE
			case VK_DELETE:
				if (wndFocus == NULL) return FALSE;
				break;
			}
		}
	}
	/*
	else if (pMsg->message == WM_IME_COMPOSITION)
	{
		if (pMsg->hwnd == GetDlgItem(IDC_EDIT_SENDSTRING)->m_hWnd)
			return TRUE;
	}
	*/

	// Default Window Message
	if (DefaultWindowMessage(pMsg))	return TRUE;
	else							return CDialogEx::PreTranslateMessage(pMsg);
}

int CJTAGPrintCPU0Dlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetWindowLongPtr(m_hWnd, GWL_STYLE, WS_SYSMENU | WS_MINIMIZEBOX);

	RedrawWindow();

	return 0;
}


void CJTAGPrintCPU0Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CJTAGPrintCPU0Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
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

		dc.TextOutW(10, 6, DLG_JTAGPRINTCPU0);

		dc.SelectObject(pOldFont);
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CJTAGPrintCPU0Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CJTAGPrintCPU0Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetCapture();
	m_Point = point;

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CJTAGPrintCPU0Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (this == GetCapture())
	{
		CRect rcDialog;
		GetWindowRect(&rcDialog);

		int x = rcDialog.left + point.x - m_Point.x;
		int y = rcDialog.top + point.y - m_Point.y;

		SetWindowPos(NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		WriteIni(SEC_WININFO, KEY_JTAGPRINTCPU0DLGLEFT, x);
		WriteIni(SEC_WININFO, KEY_JTAGPRINTCPU0DLGTOP, y);
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void CJTAGPrintCPU0Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	ReleaseCapture();

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CJTAGPrintCPU0Dlg::OnCancel()
{
	if (bRunStartJTAGPrintCPU0Thread)
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

	CDialogEx::OnCancel();
}


// ====================================================================================================
// CJTAGPrintCPU0Dlg::EnableCtrl
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CJTAGPrintCPU0Dlg::EnableCtrl(BOOL bEnable)
{
	m_Btn_StartJTAGPrint.EnableWindow(bEnable);
	m_Edit_MaxLine.EnableWindow(bEnable);
}


void CJTAGPrintCPU0Dlg::OnBnClickedButtonJtagprintcpu0close()
{
	OnCancel();
}


void CJTAGPrintCPU0Dlg::OnBnClickedButtonMinimize()
{
	ShowWindow(SW_MINIMIZE);
}


void CJTAGPrintCPU0Dlg::OnBnClickedButtonJtagprintcpu0Start()
{
// ----------------------------------------------------------------------------------------------------
// Server ����
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
		
		// Auto Save File Name
		// Get Time
		SYSTEMTIME time;
		GetLocalTime(&time);
		autosave_filename.Format(_T("jtag_printf_cpu0_%04d%02d%02d%02d%02d%02d%03d.txt"),
			time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);

		// Start Thread
		AfxBeginThread(RunStartJTAGPrintCPU0Thread, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
	}
	else 
	{
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

		m_Edit_MaxLine.EnableWindow(TRUE);
		m_Btn_StartJTAGPrint.EnableWindow(FALSE);
		AfxBeginThread(RunEndJTAGPrintCPU0Thread, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
	}
}


// ====================================================================================================
// RunStartJTAGPrintCPU0Thread
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
UINT RunStartJTAGPrintCPU0Thread(LPVOID pParam)
{
	bRunStartJTAGPrintCPU0Thread = TRUE;

	// ----------------------------------------------------------------------------------------------------
	// JTAG Open
	pJTAGPrintCPU0Dlg->JTAGPrint();

	// ----------------------------------------------------------------------------------------------------
	// End
	if (!bRunEndJTAGPrintCPU0Thread) {
		pJTAGPrintCPU0Dlg->m_Btn_StartJTAGPrint.SetWindowTextW(_T("Start"));
		pJTAGPrintCPU0Dlg->m_Btn_StartJTAGPrint.EnableWindow(TRUE);
		pJTAGPrintCPU0Dlg->EnableCtrl(TRUE);
	}

	NetClo(ConnectSocket);
	ConnectSocket = NULL;

	Wait(10);

	bRunStartJTAGPrintCPU0Thread = FALSE;

	return 0L;
}

#define COUNT_MAX 1
// ====================================================================================================
// CJTAGPrintCPU0Dlg::JTAGPrint
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CJTAGPrintCPU0Dlg::JTAGPrint()
{
	UINT32 err = 0;
	BOOL bReturn = FALSE;
	CString strMsg = _T("");
	UINT8* memblock = NULL;

	// Init
	//if (!pJTAG->JTAGInitial(strMsg)) goto END;

	// Read JTAG Print
	//if (err |= pJTAG->read32(JTAG_PRINT_SIZE, &pJTAG->jtag_print_size, 1, JTAG_COMMON_MODULE_IDX)) {
	if (-1 == getDataFromRemote(ConnectSocket, JTAG_PRINT_SIZE, 4, JTAG_COMMON_MODULE_IDX, &jtag_print_size)) {
		strMsg.Format(_T("Fail read data"));	goto END;
	}
	jtag_print_size = jtag_htonl(jtag_print_size);
	//if (err |= pJTAG->read32(JTAG_PRINT0_START, &pJTAG->jtag_print_base_CPU0, 1, JTAG_COMMON_MODULE_IDX)) {
	if (-1 == getDataFromRemote(ConnectSocket, JTAG_PRINT0_START, 4, JTAG_COMMON_MODULE_IDX, &jtag_print_base_CPU0)) {
		strMsg.Format(_T("Fail read data"));	goto END;
	}
	jtag_print_base_CPU0 = jtag_htonl(jtag_print_base_CPU0);
	// Enable Start Button
	m_Btn_StartJTAGPrint.EnableWindow(TRUE);

	resetpos(JTAG_CPU0_MODULE_IDX);

	memblock = (UINT8*)malloc(jtag_print_size);

	int check_count = 0;
	while (m_bRunJTAGPrint){
		//Sleep(10);
		ProcessWindowMessage();
		Wait(10);

		// Stop
		if (m_bStopJTAGPrint) continue;
		
		if (check_count > COUNT_MAX)
		{
			check_count = 0;
			int state = -1;

			if (ConnectSocket != NULL)
				state = sendMsg(ConnectSocket, "rem_check ");

			char ocd_flag;
			if (state != -1)
				state = recv(ConnectSocket, &ocd_flag, sizeof(ocd_flag), 0);

			if (state != -1)
			{
				if (ocd_flag != '0')
				{
					goto END;
				}
			}
			else
				goto END;
		}
		check_count++;
		
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
		// JTAGPrint
		if (JTAGPrint_define(memblock, JTAG_CPU0_MODULE_IDX) == 0xffffffff) {
			continue;
			AfxMessageBox(_T("Fail JTAG Read!"));
			//pJTAG->JTAGClose();
			break;
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
	}

	if (memblock != NULL) free(memblock);
	m_bRunJTAGPrint = FALSE;
}


// ====================================================================================================
// RunEndJTAGPrintCPU0Thread
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
UINT RunEndJTAGPrintCPU0Thread(LPVOID pParam)
{
	bRunEndJTAGPrintCPU0Thread = TRUE;

	// ----------------------------------------------------------------------------------------------------
	// Wait
	pJTAGPrintCPU0Dlg->m_bRunJTAGPrint = FALSE;

	while (bRunStartJTAGPrintCPU0Thread) { 
		//Sleep(10); 
		ProcessWindowMessage();
		Wait(10);
	}

	// ----------------------------------------------------------------------------------------------------
	// Change control state
	pJTAGPrintCPU0Dlg->m_Btn_StartJTAGPrint.SetWindowTextW(_T("Start"));
	pJTAGPrintCPU0Dlg->m_Btn_StartJTAGPrint.EnableWindow(TRUE);
	pJTAGPrintCPU0Dlg->EnableCtrl(TRUE);

	// ----------------------------------------------------------------------------------------------------
	bRunEndJTAGPrintCPU0Thread = FALSE;

	return 0L;
}


// ====================================================================================================
// CJTAGPrintCPU0Dlg::DispString
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CJTAGPrintCPU0Dlg::DispString(UINT8 *pBuf)
{
	//m_Edit_String.SetRedraw(FALSE);
	CString strDispString = (CString)pBuf;

	int iLength = 0;

	iLength = m_Edit_String.GetWindowTextLengthW();
	m_Edit_String.SetSel(iLength, iLength);
	m_Edit_String.ReplaceSel(strDispString);

	strDispString = _T("");

	iLength = m_Edit_String.GetWindowTextLengthW();
	m_Edit_String.SetSel(iLength, iLength);

	// Clear Line
	CString str = _T("");
	int iLineCount = m_Edit_String.GetLineCount();

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
	//m_Edit_String.SetRedraw(TRUE);
}


UINT RunAutoSaveThread(LPVOID pParam)
{
	pJTAGPrintCPU0Dlg->m_Static_AutoSave.EnableWindow(TRUE);
	pJTAGPrintCPU0Dlg->m_Static_AutoSave.ShowWindow(SW_SHOW);

	CString str;

	str = _T("Log Auto Save Complete");

	pJTAGPrintCPU0Dlg->m_Static_AutoSave.SetWindowTextW(str);

	//Sleep(5000);
	Wait(5000);

	pJTAGPrintCPU0Dlg->m_Static_AutoSave.EnableWindow(FALSE);
	pJTAGPrintCPU0Dlg->m_Static_AutoSave.ShowWindow(SW_HIDE);

	return 0;
}


void CJTAGPrintCPU0Dlg::OnBnClickedButtonJtagprintcpu0Stringsave()
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


void CJTAGPrintCPU0Dlg::OnBnClickedButtonJtagprintcpu0Stringstop()
{
	if (m_bStopJTAGPrint)
	{
		m_Btn_Stop.SetWindowTextW(_T("��"));
		m_bStopJTAGPrint = FALSE;
	}
	else
	{
		m_Btn_Stop.SetWindowTextW(_T("��"));
		m_bStopJTAGPrint = TRUE;
	}
}


void CJTAGPrintCPU0Dlg::OnBnClickedButtonJtagprintcpu0Stringclear()
{
	m_Edit_String.SetSel(0, -1, TRUE);
	m_Edit_String.Clear();
}


void CJTAGPrintCPU0Dlg::SaveValue()
{
	CString m_iMaxLine_str = _T("");
	m_Edit_MaxLine.GetWindowTextW(m_iMaxLine_str);
	m_iMaxLine = _ttoi(m_iMaxLine_str);
	WriteIni(SEC_JTAGPRINT0, KEY_JTAGPRINTMAXLINE, m_iMaxLine);
}


void CJTAGPrintCPU0Dlg::OnBnClickedButtonAutosavepath()
{
	CString strPath;

	strPath = ReadIni(SEC_SETTING, KEY_PRINTSAVEPATH, DEF_PRINTSAVEPATH);

	// Ini ���Ͽ� Path�� ���°��
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


HBRUSH CJTAGPrintCPU0Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (pWnd->GetDlgCtrlID() == IDC_STATIC_AUTOSAVEPATH)
	{
		pDC->SetTextColor(RGB(255, 0, 0));
	}

	return hbr;
}
