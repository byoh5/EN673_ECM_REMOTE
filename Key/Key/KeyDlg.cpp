
// KeyDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "Key.h"
#include "KeyDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const UINT  ID_CHECK_TIMER = 100;
const UINT  ID_CONNECT_TIMER = 200;
UINT	State_Check_Thread(LPVOID pParam);
UINT	Connect_Check_Thread(LPVOID pParam);

#define		Check_Time		1000
#define		Connect_Time	2000
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


// CKeyDlg 대화 상자



CKeyDlg::CKeyDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CKeyDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ECM);
}

void CKeyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_KEYCLOSE, m_Btn_Close);
	DDX_Control(pDX, IDC_BUTTON_MINIMIZE, m_Btn_Minimize);
	DDX_Control(pDX, IDC_BUTTON_CONNECT, m_Btn_Connect);
	DDX_Control(pDX, IDC_BUTTON_KEYUP, m_Btn_Up);
	DDX_Control(pDX, IDC_BUTTON_KEYDOWN, m_Btn_Down);
	DDX_Control(pDX, IDC_BUTTON_KEYLEFT, m_Btn_Left);
	DDX_Control(pDX, IDC_BUTTON_KEYRIGHT, m_Btn_Right);
	DDX_Control(pDX, IDC_BUTTON_KEYENTER, m_Btn_Enter);
	DDX_Control(pDX, IDC_BUTTON_EXIT, m_Btn_Exit);
}

BEGIN_MESSAGE_MAP(CKeyDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_KEYCLOSE, &CKeyDlg::OnBnClickedButtonKeyclose)
	ON_BN_CLICKED(IDC_BUTTON_MINIMIZE, &CKeyDlg::OnBnClickedButtonMinimize)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CKeyDlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_KEYUP, &CKeyDlg::OnBnClickedButtonKeyup)
	ON_BN_CLICKED(IDC_BUTTON_KEYLEFT, &CKeyDlg::OnBnClickedButtonKeyleft)
	ON_BN_CLICKED(IDC_BUTTON_KEYENTER, &CKeyDlg::OnBnClickedButtonKeyenter)
	ON_BN_CLICKED(IDC_BUTTON_KEYRIGHT, &CKeyDlg::OnBnClickedButtonKeyright)
	ON_BN_CLICKED(IDC_BUTTON_KEYDOWN, &CKeyDlg::OnBnClickedButtonKeydown)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CKeyDlg::OnBnClickedButtonExit)
	ON_MESSAGE(WM_COMM_KEY, &CKeyDlg::OnCtrlCamKey)
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_ACTIVATE()
END_MESSAGE_MAP()


// CKeyDlg 메시지 처리기

BOOL CKeyDlg::OnInitDialog()
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
	SetWindowText(DLG_KEY);

	int x = ReadIni(SEC_WININFO, KEY_KEYDLGLEFT, DEF_KEYDLGLEFT);
	int y = ReadIni(SEC_WININFO, KEY_KEYDLGTOP, DEF_KEYDLGTOP);
	SetWindowPos(NULL, x, y, 0, 0, SWP_NOSIZE);

	pKeyDlg = this;

// ----------------------------------------------------------------------------------------------------
// Server 연결
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

	//Sleep(1);
	Wait(1);

	StateSocket = NetCon(ch_ip, ch_port);

	// Connect Check Timer Set
	Check_Timer_On();

// ----------------------------------------------------------------------------------------------------
// Control
	// Close
	m_Btn_Close.DrawBorder(FALSE);
	m_Btn_Close.SetColor(CButtonST::BTNST_COLOR_BK_OUT, DIALOGCOLOR);
	m_Btn_Close.SetColor(CButtonST::BTNST_COLOR_BK_IN, DIALOGSUBCOLOR);

	// Minimize
	m_Btn_Minimize.DrawBorder(FALSE);
	m_Btn_Minimize.SetColor(CButtonST::BTNST_COLOR_BK_OUT, DIALOGCOLOR);
	m_Btn_Minimize.SetColor(CButtonST::BTNST_COLOR_BK_IN, DIALOGSUBCOLOR);

	// Connect
	m_Btn_Connect.SetIcon(IDI_CONNECT, NULL);
	m_Btn_Connect.DrawTransparent(TRUE);
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CKeyDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CKeyDlg::OnPaint()
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

		dc.TextOutW(10, 6, DLG_KEY);

		dc.SelectObject(pOldFont);
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CKeyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CKeyDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
			// KEYDOWN - UP
		case VK_UP:
			m_Btn_Up.SetState(TRUE);
			::SendMessage(m_hWnd, WM_COMM_KEY, ON_CTRLCAM_UP, 0);
			return TRUE;
			// KEYDOWN - DOWN
		case VK_DOWN:
			m_Btn_Down.SetState(TRUE);
			::SendMessage(m_hWnd, WM_COMM_KEY, ON_CTRLCAM_DOWN, 0);
			return TRUE;
			// KEYDOWN - LEFT
		case VK_LEFT:
			m_Btn_Left.SetState(TRUE);
			::SendMessage(m_hWnd, WM_COMM_KEY, ON_CTRLCAM_LEFT, 0);
			return TRUE;
			// KEYDOWN - RIGHT
		case VK_RIGHT:
			m_Btn_Right.SetState(TRUE);
			::SendMessage(m_hWnd, WM_COMM_KEY, ON_CTRLCAM_RIGHT, 0);
			return TRUE;
			// KEYDOWN - RETURN
		case VK_RETURN: // Enter
			m_Btn_Enter.SetState(TRUE);
			::SendMessage(m_hWnd, WM_COMM_KEY, ON_CTRLCAM_ENTER, 0);
			return TRUE;
			// KEYDOWN - E, e
		case 'E':
		case 'e':
			// KEYDOWN - ESC
		case VK_ESCAPE:
			m_Btn_Exit.SetState(TRUE);
			::SendMessage(m_hWnd, WM_COMM_KEY, ON_CTRLCAM_EXIT, 0);
			return TRUE;
#if 0
			// KEYDOWN - ESC
		case VK_ESCAPE:
			return TRUE;
#endif
		}
	}
	else if (pMsg->message == WM_KEYUP)
	{
		switch (pMsg->wParam)
		{
		case VK_UP:
			m_Btn_Up.SetState(FALSE);
			return TRUE;
			break;

		case VK_DOWN:
			m_Btn_Down.SetState(FALSE);
			return TRUE;
			break;

		case VK_LEFT:
			m_Btn_Left.SetState(FALSE);
			//m_Btn_Left.SetFocus();
			return TRUE;
			break;

		case VK_RIGHT:
			m_Btn_Right.SetState(FALSE);
			return TRUE;
			break;

		case VK_RETURN:											// Enter Key
			m_Btn_Enter.SetState(FALSE);
			return TRUE;
			break;

		case VK_ESCAPE:
		case 'E':
		case 'e':
			m_Btn_Exit.SetState(FALSE);
			return TRUE;
			break;
		}
	}
	else if (pMsg->message == WM_SYSKEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_UP:
			m_Btn_Up.SetState(TRUE);
			::SendMessage(m_hWnd, WM_COMM_KEY, ON_CTRLCAM_UP, 0);
			return TRUE;
			break;

		case VK_DOWN:
			m_Btn_Down.SetState(TRUE);
			::SendMessage(m_hWnd, WM_COMM_KEY, ON_CTRLCAM_DOWN, 0);
			return TRUE;
			break;

		case VK_LEFT:
			m_Btn_Left.SetState(TRUE);
			::SendMessage(m_hWnd, WM_COMM_KEY, ON_CTRLCAM_LEFT, 0);
			return TRUE;
			break;

		case VK_RIGHT:
			m_Btn_Right.SetState(TRUE);
			::SendMessage(m_hWnd, WM_COMM_KEY, ON_CTRLCAM_RIGHT, 0);
			return TRUE;
			break;

		case VK_RETURN: // Enter
			m_Btn_Enter.SetState(TRUE);
			::SendMessage(m_hWnd, WM_COMM_KEY, ON_CTRLCAM_ENTER, 0);
			return TRUE;
			break;

		case VK_ESCAPE:
		case 'E':
		case 'e':
			m_Btn_Exit.SetState(TRUE);
			::SendMessage(m_hWnd, WM_COMM_KEY, ON_CTRLCAM_EXIT, 0);
			return TRUE;
			break;
		}
	}
	else if (pMsg->message == WM_SYSKEYUP)
	{
		switch (pMsg->wParam)
		{
		case VK_UP:;
			m_Btn_Up.SetState(FALSE);
			return TRUE;
			break;

		case VK_DOWN:
			m_Btn_Down.SetState(FALSE);
			return TRUE;
			break;

		case VK_LEFT:
			m_Btn_Left.SetState(FALSE);
			return TRUE;
			break;

		case VK_RIGHT:
			m_Btn_Right.SetState(FALSE);
			return TRUE;
			break;

		case VK_RETURN:											// Enter Key
			m_Btn_Enter.SetState(FALSE);
			return TRUE;
			break;

		case VK_ESCAPE:
		case 'E':
		case 'e':
			m_Btn_Exit.SetState(FALSE);
			return TRUE;
			break;
		}
	}


	return CDialogEx::PreTranslateMessage(pMsg);
}


int CKeyDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetWindowLongPtr(m_hWnd, GWL_STYLE, WS_SYSMENU | WS_MINIMIZEBOX);

	RedrawWindow();

	return 0;
}


void CKeyDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetCapture();
	m_Point = point;

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CKeyDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (this == GetCapture())
	{
		CRect rcDialog;
		GetWindowRect(&rcDialog);

		int x = rcDialog.left + point.x - m_Point.x;
		int y = rcDialog.top + point.y - m_Point.y;

		SetWindowPos(NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		WriteIni(SEC_WININFO, KEY_KEYDLGLEFT, x);
		WriteIni(SEC_WININFO, KEY_KEYDLGTOP, y);
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void CKeyDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	ReleaseCapture();

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CKeyDlg::OnCancel()
{
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


void CKeyDlg::OnBnClickedButtonKeyclose()
{
	OnCancel();
}


void CKeyDlg::OnBnClickedButtonMinimize()
{
	ShowWindow(SW_MINIMIZE);
}


void CKeyDlg::OnBnClickedButtonConnect()
{
#if 0
	UINT32 read = 0;
	int state = -1;

	if (ConnectSocket)
	{
		state = getDataFromRemote(ConnectSocket, 0x06fff004, 4, WBCOM, &read);
	}
	if ((state < 0) || !ConnectSocket)
	{
		ConnectSocket = NetCon(ch_ip, ch_port);
		if (ConnectSocket <= 0)
			ConnectSocket = NULL;
	}

	if (ConnectSocket) {
		EnableCtrl(TRUE);
		m_Btn_Connect.SetIcon(IDI_CONNECT, NULL);
	}
	else {
		EnableCtrl(FALSE);
		m_Btn_Connect.SetIcon(IDI_DISCONNECT, NULL);
	}
#endif
}


void CKeyDlg::OnBnClickedButtonKeyup()
{
	OnCtrlCamKey(ON_CTRLCAM_UP, 0);
}


void CKeyDlg::OnBnClickedButtonKeyleft()
{
	OnCtrlCamKey(ON_CTRLCAM_LEFT, 0);
}


void CKeyDlg::OnBnClickedButtonKeyenter()
{
	OnCtrlCamKey(ON_CTRLCAM_ENTER, 0);
}


void CKeyDlg::OnBnClickedButtonKeyright()
{
	OnCtrlCamKey(ON_CTRLCAM_RIGHT, 0);
}


void CKeyDlg::OnBnClickedButtonKeydown()
{
	OnCtrlCamKey(ON_CTRLCAM_DOWN, 0);
}


void CKeyDlg::OnBnClickedButtonExit()
{
	OnCtrlCamKey(ON_CTRLCAM_EXIT, 0);
}


void CKeyDlg::EnableCtrl(BOOL bEnable)
{
	m_Btn_Up.EnableWindow(bEnable);
	m_Btn_Down.EnableWindow(bEnable);
	m_Btn_Left.EnableWindow(bEnable);
	m_Btn_Right.EnableWindow(bEnable);
	m_Btn_Enter.EnableWindow(bEnable);
	m_Btn_Exit.EnableWindow(bEnable);
}

afx_msg LRESULT CKeyDlg::OnCtrlCamKey(WPARAM wParam, LPARAM lParam)
{
	int state = -1;

#if 0
	if (ConnectSocket != NULL)
		state = sendMsg(ConnectSocket, "rem_check ");
	else
	{
		AfxMessageBox(_T("Connect Error\n"));
		return 0L;
	}

	char ocd_flag;
	recv(ConnectSocket, &ocd_flag, sizeof(ocd_flag), 0);

	if (state < 0)
	{
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

			AfxMessageBox(_T("Connect Error\n"));
			return 0L;
		}
	}
#endif

	UINT32 key = 0;

	switch(wParam)
	{
	case ON_CTRLCAM_UP:
		//state = TxCtrlKey(ON_CTRLCAM_UP);
		key = 0x00000001;
		break;

	case ON_CTRLCAM_DOWN:
		//state = TxCtrlKey(ON_CTRLCAM_LEFT);
		key = 0x00000002;
		break;

	case ON_CTRLCAM_ENTER:
		//state = TxCtrlKey(ON_CTRLCAM_ENTER);
		key = 0x00000010;
		break;

	case ON_CTRLCAM_RIGHT:
		//state = TxCtrlKey(ON_CTRLCAM_RIGHT);
		key = 0x00000004;
		break;

	case ON_CTRLCAM_LEFT:
		//state = TxCtrlKey(ON_CTRLCAM_DOWN);
		key = 0x00000008;
		break;

	case ON_CTRLCAM_EXIT:
		//state = TxCtrlKey(ON_CTRLCAM_EXIT);
		key = 0x00000020;
		break;
	}

	key = (ntohl(key));

	state = setDataFromRemote(ConnectSocket, KEYADDR, 4, WBCOM, (UINT32 *)&key);
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
	}

	if (state < 0)
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

		EnableCtrl(FALSE);
		m_Btn_Connect.SetIcon(IDI_DISCONNECT, NULL);
	}

	return 0L;
}


void CKeyDlg::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case ID_CHECK_TIMER :
		AfxBeginThread(State_Check_Thread, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
		break;
	case ID_CONNECT_TIMER:
		AfxBeginThread(Connect_Check_Thread, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CKeyDlg::Check_Timer_On()
{
	m_CheckTimerID = SetTimer(ID_CHECK_TIMER, Check_Time, NULL);
}

void CKeyDlg::Check_Timer_Off()
{
	if (m_CheckTimerID)
	{
		if (this->GetSafeHwnd())
			KillTimer(m_CheckTimerID);
		m_CheckTimerID = 0;
	}
}

void CKeyDlg::Connect_Timer_On()
{
	m_ConnectTimerID = SetTimer(ID_CONNECT_TIMER, Connect_Time, NULL);
}

void CKeyDlg::Connect_Timer_Off()
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
				pKeyDlg->EnableCtrl(TRUE);
				pKeyDlg->m_Btn_Connect.SetIcon(IDI_CONNECT, NULL);

				Invalidate_flsg = TRUE;
			}

			return 0;
		}
		else
		{
			goto DISCONNECT;
		}
	}

DISCONNECT:
	pKeyDlg->EnableCtrl(FALSE);
	pKeyDlg->m_Btn_Connect.SetIcon(IDI_DISCONNECT, NULL);

	NetClo(ConnectSocket);
	ConnectSocket = NULL;

	Wait(1);

	NetClo(StateSocket);
	StateSocket = NULL;

	pKeyDlg->Check_Timer_Off();
	pKeyDlg->Connect_Timer_On();

	Invalidate_flsg = FALSE;

	return 0;
}


UINT Connect_Check_Thread(LPVOID pParam)
{
	ConnectSocket = NetCon(pKeyDlg->ch_ip, pKeyDlg->ch_port);
	//Sleep(1);
	Wait(1);
	StateSocket = NetCon(pKeyDlg->ch_ip, pKeyDlg->ch_port);

	if (ConnectSocket <= 0 || StateSocket <= 0)
	{
		ConnectSocket = NULL;
		StateSocket = NULL;
	}
	else
	{
		Invalidate_flsg = FALSE;

		pKeyDlg->Connect_Timer_Off();
		pKeyDlg->Check_Timer_On();
	}
	return 0;
}

void CKeyDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
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
