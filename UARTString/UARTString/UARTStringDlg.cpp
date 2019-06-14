
// UARTStringDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "UARTString.h"
#include "UARTStringDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HWND		hCommWnd;
// Thread
UINT	DispStringThread(LPVOID pParam);

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


// CUARTStringDlg 대화 상자



CUARTStringDlg::CUARTStringDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUARTStringDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ECM);
}

void CUARTStringDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_STRINGCLOSE, m_Btn_Close);
	DDX_Control(pDX, IDC_BUTTON_MINIMIZE, m_Btn_Minimize);
	DDX_Control(pDX, IDC_BUTTON_STRINGSAVE, m_Btn_Save);
	DDX_Control(pDX, IDC_EDIT_STRING, m_Edit_String);
	DDX_Control(pDX, IDC_EDIT_SENDSTRING, m_Edit_SendString);
	DDX_Control(pDX, IDC_BUTTON_STRINGCLEAR, m_Btn_Clear);
	DDX_Control(pDX, IDC_BUTTON_STRINGSTOP, m_Btn_Stop);
	DDX_Control(pDX, IDC_EDIT_STRINGMAXLINE, m_Edit_MaxLine);
	DDX_Control(pDX, IDC_CHECK_STRINGINFINITE, m_Chk_Infinite);
	DDX_Control(pDX, IDC_COMBO_MAINPORT, m_Cbo_Port);
	DDX_Control(pDX, IDC_COMBO_MAINBPS, m_Cbo_Bps);
	DDX_Control(pDX, IDC_BUTTON_PORTOPEN, m_Btn_PortOpen);
	DDX_Control(pDX, IDC_BUTTON_CMDLOGSHOW, m_Btn_CmdLogShow);
}

BEGIN_MESSAGE_MAP(CUARTStringDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_STRINGCLOSE, &CUARTStringDlg::OnBnClickedButtonStringclose)
	ON_BN_CLICKED(IDC_BUTTON_MINIMIZE, &CUARTStringDlg::OnBnClickedButtonMinimize)
	ON_BN_CLICKED(IDC_BUTTON_STRINGCLEAR, &CUARTStringDlg::OnBnClickedButtonStringclear)
	ON_BN_CLICKED(IDC_BUTTON_STRINGSTOP, &CUARTStringDlg::OnBnClickedButtonStringstop)
	ON_BN_CLICKED(IDC_BUTTON_STRINGSAVE, &CUARTStringDlg::OnBnClickedButtonStringsave)
	ON_BN_CLICKED(IDC_CHECK_STRINGINFINITE, &CUARTStringDlg::OnBnClickedCheckStringinfinite)
	ON_EN_UPDATE(IDC_EDIT_STRINGMAXLINE, &CUARTStringDlg::OnEnUpdateEditStringmaxline)
	ON_EN_KILLFOCUS(IDC_EDIT_STRINGMAXLINE, &CUARTStringDlg::OnEnKillfocusEditStringmaxline)
	ON_BN_CLICKED(IDC_BUTTON_PORTOPEN, &CUARTStringDlg::OnBnClickedButtonPortopen)
	ON_CBN_SELCHANGE(IDC_COMBO_MAINPORT, &CUARTStringDlg::OnCbnSelchangeComboMainport)
	ON_CBN_SELCHANGE(IDC_COMBO_MAINBPS, &CUARTStringDlg::OnCbnSelchangeComboMainbps)
	ON_EN_UPDATE(IDC_EDIT_SENDSTRING, &CUARTStringDlg::OnEnUpdateEditSendstring)
	ON_CBN_DROPDOWN(IDC_COMBO_MAINPORT, &CUARTStringDlg::OnCbnDropdownComboMainport)
	ON_BN_CLICKED(IDC_BUTTON_CMDLOGSHOW, &CUARTStringDlg::OnBnClickedButtonCmdlogshow)
END_MESSAGE_MAP()


// CUARTStringDlg 메시지 처리기

BOOL CUARTStringDlg::OnInitDialog()
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
	SetWindowText(DLG_UARTSTRING);

	hCommWnd = this->m_hWnd;

	pComPort = &m_ComPort;
	pUARTStringDlg = this;

	int x = ReadIni(SEC_WININFO, KEY_STRINGDLGLEFT, DEF_STRINGDLGLEFT);
	int y = ReadIni(SEC_WININFO, KEY_STRINGDLGTOP, DEF_STRINGDLGTOP);

	SetWindowPos(&CDialog::wndNoTopMost, x, y, DEF_STRINGDLGWIDTH, DEF_STRINGDLGHEIGHT, NULL);

// ----------------------------------------------------------------------------------------------------
// Serial Port
	m_strPort = ReadIni(SEC_UARTSTRING, KEY_PORT, CBO_PORT[DEF_PORT]);
	m_strBps = ReadIni(SEC_UARTSTRING, KEY_BPS, CBO_BPS[DEF_BPS]);
	m_strDataBit = ReadIni(SEC_UARTSTRING, KEY_DATABIT, CBO_DATABIT[DEF_DATABIT]);
	m_strParityBit = ReadIni(SEC_UARTSTRING, KEY_PARITYBIT, CBO_PARITYBIT[DEF_PARITYBIT]);
	m_strStopBit = ReadIni(SEC_UARTSTRING, KEY_STOPBIT, CBO_STOPBIT[DEF_STOPBIT]);
	m_strFlowControl = ReadIni(SEC_UARTSTRING, KEY_FLOWCONTROL, CBO_FLOWCONTROL[DEF_FLOWCONTROL]);

// ----------------------------------------------------------------------------------------------------
// Control
	m_Btn_Close.DrawBorder(FALSE);
	m_Btn_Close.SetColor(CButtonST::BTNST_COLOR_BK_OUT, DIALOGCOLOR);
	m_Btn_Close.SetColor(CButtonST::BTNST_COLOR_BK_IN, DIALOGSUBCOLOR);

	// Minimize
	m_Btn_Minimize.DrawBorder(FALSE);
	m_Btn_Minimize.SetColor(CButtonST::BTNST_COLOR_BK_OUT, DIALOGCOLOR);
	m_Btn_Minimize.SetColor(CButtonST::BTNST_COLOR_BK_IN, DIALOGSUBCOLOR);

	// String Window
	m_Edit_String.SetLimitText(0xffffffff);
	// Save
	m_Btn_Save.SetBitmaps(IDB_SAVE, RGB(255, 0, 255));
	// Stop
	m_Btn_Stop.SetWindowTextW(_T("■"));
	
	// Send String Limit Text
	// 이현제선임님 요청으로 37자
	m_Edit_SendString.SetLimitText(37);

	// Max Line
	m_Edit_MaxLine.SetLimitText(8);
	m_iMaxLine = 50000000;
	CString str = _T("");
	str.Format(_T("%d"), m_iMaxLine);
	m_Edit_MaxLine.SetWindowTextW(str);

	int i = 0;
	int iCurSel = 0;

	COMBO_ADDSTRING(pUARTStringDlg->m_strPort, NUM_PORT, m_Cbo_Port, CBO_PORT);
	COMBO_ADDSTRING(pUARTStringDlg->m_strBps, NUM_BPS, m_Cbo_Bps, CBO_BPS);

	m_Btn_Clear.EnableWindow(FALSE);
	m_Btn_Stop.EnableWindow(FALSE);
	m_Btn_Save.EnableWindow(FALSE);
	m_Edit_String.EnableWindow(FALSE);
	m_Edit_SendString.EnableWindow(FALSE);
	m_Btn_CmdLogShow.EnableWindow(FALSE);

// ----------------------------------------------------------------------------------------------------
// Init Variable
	m_strDispString = _T("");
	m_bOnChangeEditMaxLine = FALSE;
	m_bOnDispString = FALSE;
	m_bOnUpdateString = FALSE;

	// Flag
	m_bRunString = TRUE;
	g_pDispStringThread = FALSE;


// ----------------------------------------------------------------------------------------------------
// Create Sub Dialog
	CRect rect;
	this->GetWindowRect(&rect);

	m_pDlg_CmdLogShow = new CUARTStringCmdLogDlg();
	m_pDlg_CmdLogShow->Create(IDD_UARTSTRINGCMDLOG, this);
	m_pDlg_CmdLogShow->SetWindowPos(NULL, rect.right, rect.top, 0, 0, SWP_SHOWWINDOW | SWP_NOZORDER | SWP_NOSIZE);

	m_pDlg_CmdLogShow->ShowWindow(SW_HIDE);
	m_ShowDlg_CmdLog = FALSE;

// ----------------------------------------------------------------------------------------------------
// Etc..
	// Platform
	m_iPlatformSel = EN673;

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CUARTStringDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CUARTStringDlg::OnPaint()
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

		dc.TextOutW(10, 6, DLG_UARTSTRING);

		dc.SelectObject(pOldFont);
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CUARTStringDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CUARTStringDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetCapture();
	m_Point = point;

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CUARTStringDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (this == GetCapture())
	{
		CRect rcDialog;
		GetWindowRect(&rcDialog);

		int x = rcDialog.left + point.x - m_Point.x;
		int y = rcDialog.top + point.y - m_Point.y;

		SetWindowPos(NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		WriteIni(SEC_WININFO, KEY_STRINGDLGLEFT, x);
		WriteIni(SEC_WININFO, KEY_STRINGDLGTOP, y);

// ----------------------------------------------------------------------------------------------------
// Set Sub Dialog
		CRect rectCmdLog;

		pUARTStringCmdLogDlg->GetWindowRect(&rectCmdLog);
		pUARTStringCmdLogDlg->MoveWindow(rcDialog.right, rcDialog.bottom - rectCmdLog.Height(), rectCmdLog.Width(), rectCmdLog.Height(), TRUE);
	}
	CDialogEx::OnMouseMove(nFlags, point);
}


void CUARTStringDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	ReleaseCapture();
	CDialogEx::OnLButtonUp(nFlags, point);
}


BOOL CUARTStringDlg::PreTranslateMessage(MSG* pMsg)
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
				if (wndFocus == (CWnd*)&m_Edit_SendString) {
					SendString();
					return TRUE;
				}
				if (wndFocus == (CWnd*)&m_Edit_MaxLine) {
					CString str = _T("");
					m_Edit_MaxLine.GetWindowTextW(str);
					m_iMaxLine = _ttoi(str);
					return TRUE;
				}
				if (wndFocus == (CWnd*)&m_Edit_String) {
					return CDialog::PreTranslateMessage(pMsg);
				}
				break;
				// KEYDOWN - DELETE
			case VK_DELETE:
				if (wndFocus == NULL) return FALSE;
				break;
				// KEYDOWN - UP
			case VK_UP:
				if (wndFocus == NULL) return FALSE;
				if (wndFocus == (CWnd*)&m_Edit_SendString) {
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
				if (wndFocus == (CWnd*)&m_Edit_SendString) {
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
	else if (pMsg->message == WM_IME_COMPOSITION)
	{
		if (pMsg->hwnd == GetDlgItem(IDC_EDIT_SENDSTRING)->m_hWnd)
			return TRUE;
	}

	// Default Window Message
	if (DefaultWindowMessage(pMsg))	return TRUE;
	else							return CDialogEx::PreTranslateMessage(pMsg);
}


void CUARTStringDlg::OnCancel()
{
	// ini save
	SaveValue();

	// Close Port
	if (pComPort->m_bConnected) {
		pComPort->ClosePort();
	}

	m_pDlg_CmdLogShow->DestroyWindow();
	delete m_pDlg_CmdLogShow;

	CDialogEx::OnCancel();
}


void CUARTStringDlg::OnBnClickedButtonStringclose()
{
	OnCancel();
}


void CUARTStringDlg::OnBnClickedButtonMinimize()
{
	ShowWindow(SW_MINIMIZE);
}


void CUARTStringDlg::OnBnClickedButtonStringclear()
{
	m_Edit_String.SetSel(0, -1, TRUE);
	m_Edit_String.Clear();
}


void CUARTStringDlg::OnBnClickedButtonStringstop()
{
	if (m_bRunString)
	{
		m_Btn_Stop.SetWindowTextW(_T("▶"));
		m_bRunString = FALSE;
	}
	else
	{
		m_Btn_Stop.SetWindowTextW(_T("■"));
		m_bRunString = TRUE;
	}
}


void CUARTStringDlg::OnBnClickedButtonStringsave()
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

void CUARTStringDlg::OnBnClickedCheckStringinfinite()
{
	if (m_Chk_Infinite.GetCheck()) {
		m_Edit_MaxLine.EnableWindow(FALSE);
	}
	else {
		m_Edit_MaxLine.EnableWindow(TRUE);
	}
}


void CUARTStringDlg::OnEnUpdateEditStringmaxline()
{
	if (m_bOnChangeEditMaxLine) return;

	int iCur = 0;
	BOOL bEdit = FALSE;

	CString str = _T("");
	CString strEdit = _T("");
	m_Edit_MaxLine.GetWindowTextW(str);
	m_Edit_MaxLine.GetSel(iCur, iCur);

	for (int i = 0; i < str.GetLength(); i++)
	{
		if ((str.GetAt(i) >= _T('0')) && (str.GetAt(i) <= _T('9'))) {
			strEdit = strEdit + str.GetAt(i);
		}
		else {
			m_Edit_MaxLine.SetModify(TRUE);
			bEdit = TRUE;
			iCur--;
		}
	}

	if (bEdit) {
		if (m_Edit_MaxLine.GetModify()) {
			m_bOnChangeEditMaxLine = TRUE;
			m_Edit_MaxLine.SetWindowTextW(strEdit);
			m_bOnChangeEditMaxLine = FALSE;
			m_Edit_MaxLine.SetModify(FALSE);
			m_Edit_MaxLine.SetSel(iCur, iCur);
			str = strEdit;
		}
	}
}


void CUARTStringDlg::OnEnKillfocusEditStringmaxline()
{
	if (m_bOnChangeEditMaxLine) return;

	CString str = _T("");
	m_Edit_MaxLine.GetWindowTextW(str);

	m_iMaxLine = _ttoi(str);
}


void CUARTStringDlg::RxStr()
{
	if (!m_bRunString) return;

	int iPlatformSel = m_iPlatformSel; // pECMDlg->GetPlatformSel();

	int	i = 0;
	int iCnt = 0;
	int iLength = 0;
	char* ch = NULL;
	char* ch2 = NULL;
	CString str = _T("");

	switch (iPlatformSel)
	{
	case EN673:
	case EN674:
		iLength = rxData[1];
		if (!iLength) return;

		ch = new char[iLength];
		ZeroMemory(ch, iLength);

		for (i = 2; i <= iLength + 1; i++) {
			//if(rxData[i]=='\r') continue; // ListCtrl일 때는 주석 해제
			ch[iCnt] = rxData[i];
			iCnt++;
		}

		ch2 = new char[iCnt + 1];
		for (i = 0; i < iCnt; i++)
			ch2[i] = ch[i];
		ch2[iCnt] = NULL;

		str = (CString)ch2;
		//bStringFlag = FALSE;

		while (m_bOnUpdateString) { Sleep(0); };

		m_bOnUpdateString = TRUE;

		m_strDispString += str;

		m_bOnDispString = TRUE;
		m_bOnUpdateString = FALSE;
		delete[] ch2;

		break;

	default:
		iLength = rxData[1] - 1;
		if (!iLength) return;

		ch = new char[iLength];
		ZeroMemory(ch, iLength);

		for (i = 2; i <= iLength; i++, iCnt++)
			ch[iCnt] = rxData[i];

		str = (CString)ch;

		CString strTime = _T("");
		SYSTEMTIME st;
		GetLocalTime(&st);
		strTime.Format(_T("\t%02d/%02d, %02d:%02d:%02d:%03d\r\n"), st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);

		str += strTime;

		//bStringFlag = FALSE;

		while (m_bOnUpdateString) { Sleep(0); };

		m_bOnUpdateString = TRUE;

		m_strDispString += str;

		m_bOnDispString = TRUE;
		m_bOnUpdateString = FALSE;
		break;
	}

	delete[] ch;
}


void CUARTStringDlg::StartDispStringThread()
{
	g_pDispStringThread = AfxBeginThread(DispStringThread, GetSafeHwnd());
}


UINT DispStringThread(LPVOID pParam)
{
	//bStringFlag = FALSE;

	while (pComPort->m_bConnected)
	{
		if (pUARTStringDlg->m_bOnDispString) pUARTStringDlg->DispString();
		Sleep(1);
	}

	return 0L;
}


void CUARTStringDlg::DispString()
{
	if (m_bOnUpdateString == FALSE && m_bOnDispString == TRUE) {
		m_bOnUpdateString = TRUE;

		int iLength = m_Edit_String.GetWindowTextLengthW();
		m_Edit_String.SetSel(iLength, iLength);
		m_Edit_String.ReplaceSel(m_strDispString);

		m_strDispString = _T("");
		m_bOnDispString = FALSE;
		m_bOnUpdateString = FALSE;
	}
	else return;

	int iLength = m_Edit_String.GetWindowTextLengthW();
	m_Edit_String.SetSel(iLength, iLength);
	//m_Edit_String.ReplaceSel(str);

	// Clear Line
	CString str = _T("");
	int iLineCount = m_Edit_String.GetLineCount();

	if (iLineCount > m_iMaxLine) {
		for (int i = iLineCount; i > m_iMaxLine; i--) {
			m_Edit_String.GetWindowTextW(str);

			int iFind = str.Find('\n');
			if (iFind <= 81)		m_Edit_String.SetSel(0, iFind + 1);
			else				m_Edit_String.SetSel(0, 80);
			m_Edit_String.Clear();
		}
	}


	//m_Edit_String.SendMessage(WM_VSCROLL, SB_BOTTOM);
	//m_Edit_String.SetRedraw(TRUE);
}


void CUARTStringDlg::SendString()
{
	int iLength = 0;
	CString str = _T("");

	m_Edit_SendString.GetWindowText(str);
	iLength = str.GetLength();

	BYTE* SendData = new BYTE[iLength + 6];
	SendData[0] = PC_STX;		// Start
	SendData[1] = PC_CMD_STR;	// Command
	SendData[2] = iLength + 2;	// Length

	for (int i = 0; i < iLength; i++)
		SendData[i + 3] = str.GetAt(i);	// String

	SendData[iLength + 3] = ASCII_CR;	// Carriage Return
	SendData[iLength + 4] = ASCII_LF;	// Line Feed
	SendData[iLength + 5] = PC_ETX;	// End

	if (pComPort->m_bConnected)
		pComPort->WriteComm(SendData, iLength + 6);

	// Command Log
	if (str != _T(""))
		pUARTStringCmdLogDlg->m_List_CmdLog.AddString(str);

	m_Edit_SendString.SetWindowTextW(_T(""));

	delete[] SendData;
}


void CUARTStringDlg::OnEnUpdateEditSendstring()
{
	CString str;
	int nCur;
	m_Edit_SendString.GetWindowText(str);
	m_Edit_SendString.GetSel(nCur, nCur);

	for (int i = 0; i < str.GetLength(); i++)
	{
		if (!(str.GetAt(i) >= _T(' ') && str.GetAt(i) <= _T('~')))
		{
			str.Delete(i, 1);
			m_Edit_SendString.SetModify(TRUE);
			nCur--;
		}
	}

	if (m_Edit_SendString.GetModify())
	{
		m_Edit_SendString.SetWindowText(str);
		m_Edit_SendString.SetModify(FALSE);
		m_Edit_SendString.SetSel(nCur, nCur);
	}
}


int CUARTStringDlg::CommandShow(int sign)
{
	int count = pUARTStringCmdLogDlg->m_List_CmdLog.GetCount();
	int index = 0;
	CString cmd_str = _T("");
	m_Edit_SendString.GetWindowTextW(cmd_str);

	if (count)
	{
		index = pUARTStringCmdLogDlg->m_List_CmdLog.GetCurSel();

		if (index < 0 || cmd_str == _T(""))
		{
			index = pUARTStringCmdLogDlg->m_List_CmdLog.SetCurSel(0);
			pUARTStringCmdLogDlg->m_List_CmdLog.GetText(index, cmd_str);
		}
		else
		{
			if (index + sign > count - 1 || index + sign < 0)
				return -1;
			pUARTStringCmdLogDlg->m_List_CmdLog.SetCurSel(index + sign);
			pUARTStringCmdLogDlg->m_List_CmdLog.GetText(index + sign, cmd_str);
		}
		m_Edit_SendString.SetWindowTextW(cmd_str);
	}
	else
		return 0;

	return 0;
}


void CUARTStringDlg::OnBnClickedButtonPortopen()
{
	if (!pComPort->m_bConnected) PortOpen();
	else						PortClose();
}


void CUARTStringDlg::OnCbnSelchangeComboMainport()
{
	m_Cbo_Port.GetWindowTextW(m_strPort);
}


void CUARTStringDlg::OnCbnSelchangeComboMainbps()
{
	m_Cbo_Bps.GetWindowTextW(m_strBps);
}


void CUARTStringDlg::OnCbnDropdownComboMainport()
{
	HKEY hKey;
	TCHAR szData[20], szName[100];
	DWORD index = 0, dwSize = 100, dwSize2 = 20, dwType = REG_SZ;
	//시리얼 포트가 저장된 곳
	RegOpenKey(HKEY_LOCAL_MACHINE, _T("HARDWARE\\DEVICEMAP\\SERIALCOMM"), &hKey);

	memset(szData, 0x00, sizeof(szData));
	memset(szName, 0x00, sizeof(szName));
	m_Cbo_Port.ResetContent();

	while (ERROR_SUCCESS == RegEnumValue(hKey, index, szName, &dwSize, NULL, NULL, NULL, NULL))
	{
		index++;

		RegQueryValueEx(hKey, szName, NULL, &dwType, (LPBYTE)szData, &dwSize2);
		m_Cbo_Port.AddString(CString(szData));
		memset(szData, 0x00, sizeof(szData));
		memset(szName, 0x00, sizeof(szName));
		dwSize = 100;
		dwSize2 = 20;
	}

	RegCloseKey(hKey);
}


BOOL CUARTStringDlg::PortOpen()
{
	m_Cbo_Port.GetWindowTextW(m_strPort);

	if (m_strPort == _T(""))
	{
		AfxMessageBox(_T("Select Port."));
		return FALSE;
	}

	if (!pComPort->OpenPort(m_strPort, _ttoi(m_strBps), 0x01))
	{
		AfxMessageBox(_T("Fail Port Connection."));
		m_Btn_PortOpen.SetFocus();
		return FALSE;
	}

	m_Btn_PortOpen.SetWindowTextW(_T("Close"));
	EnableCtrl(TRUE);
	return TRUE;
}

// ====================================================================================================
// PortClose
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CUARTStringDlg::PortClose()
{
	pComPort->ClosePort();

	m_Btn_PortOpen.SetWindowTextW(_T("Open"));
	EnableCtrl(FALSE);
}


void CUARTStringDlg::SaveValue()
{
	// Serial Port Setting
	WriteIni(SEC_UARTSTRING, KEY_PORT, m_strPort);
	WriteIni(SEC_UARTSTRING, KEY_BPS, m_strBps);
	WriteIni(SEC_UARTSTRING, KEY_DATABIT, m_strDataBit);
	WriteIni(SEC_UARTSTRING, KEY_PARITYBIT, m_strParityBit);
	WriteIni(SEC_UARTSTRING, KEY_STOPBIT, m_strStopBit);
	WriteIni(SEC_UARTSTRING, KEY_FLOWCONTROL, m_strFlowControl);
}


void CUARTStringDlg::EnableCtrl(BOOL bEnable)
{
	m_Btn_Clear.EnableWindow(TRUE);
	m_Btn_Stop.EnableWindow(bEnable);
	m_Btn_Save.EnableWindow(TRUE);
	m_Edit_String.EnableWindow(TRUE);
	m_Edit_SendString.EnableWindow(TRUE);
	m_Btn_CmdLogShow.EnableWindow(bEnable);

	m_Cbo_Port.EnableWindow(!bEnable);
	m_Cbo_Bps.EnableWindow(!bEnable);
}

void CUARTStringDlg::OnBnClickedButtonCmdlogshow()
{
	if (!m_ShowDlg_CmdLog)
	{
		CRect rectThis;
		CRect rectCmdLog;

		this->GetWindowRect(&rectThis);
		pUARTStringCmdLogDlg->GetWindowRect(&rectCmdLog);

		pUARTStringCmdLogDlg->MoveWindow(rectThis.right, rectThis.bottom - rectCmdLog.Height(), rectCmdLog.Width(), rectCmdLog.Height(), TRUE);

		m_Btn_CmdLogShow.SetWindowTextW(_T("<<"));
		pUARTStringCmdLogDlg->ShowWindow(SW_SHOW);
		m_ShowDlg_CmdLog = TRUE;
	}
	else
	{
		pUARTStringCmdLogDlg->OnBnClickedButtonClose();
		m_Btn_CmdLogShow.SetWindowTextW(_T(">>"));
		m_ShowDlg_CmdLog = FALSE;
	}
}
