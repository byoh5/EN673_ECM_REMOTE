
// ParameterDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "Parameter.h"
#include "ParameterDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CParameterDlg 대화 상자
UINT			ReadAllThread_Par(LPVOID pParam);
UINT			WriteAllThread_Par(LPVOID pParam);
UINT			EEPROMReadAllThread(LPVOID pParam);
UINT			EEPROMWriteAllThread(LPVOID pParam);
UINT			LoadingThreadParameter(LPVOID pParam);
UINT			SaveHexThread(LPVOID pParam);
UINT			EnableParameterThread(LPVOID pParam);

const UINT  ID_CHECK_TIMER = 100;
const UINT  ID_CONNECT_TIMER = 200;
UINT	State_Check_Thread(LPVOID pParam);
UINT	Connect_Check_Thread(LPVOID pParam);

#define		Check_Time		1000
#define		Connect_Time	5000

CParameterDlg::CParameterDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CParameterDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ECM);
}

void CParameterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_PARFILE, m_Edit_ParFile);
	DDX_Control(pDX, IDC_BUTTON_OPENPAR, m_Btn_OpenPar);
	DDX_Control(pDX, IDC_BUTTON_SAVEPAR, m_Btn_SavePar);
	DDX_Control(pDX, IDC_BUTTON_PARAMETERKEYSET, m_Btn_ParKeyEnable);
	DDX_Control(pDX, IDC_EDIT_PARDESCRIPTION, m_Edit_Description);
	DDX_Control(pDX, IDC_COMBO_PARMOVENAME, m_Cbo_Movename);
	DDX_Control(pDX, IDC_STATIC_PARTXVALUE, m_Static_TxValue);
	DDX_Control(pDX, IDC_SPIN_PARVALUE, m_Spin_TxValue);
	DDX_Control(pDX, IDC_BUTTON_PARREAD, m_Btn_Read);
	DDX_Control(pDX, IDC_SPIN_READPAR, m_Spin_ReadPar);
	DDX_Control(pDX, IDC_COMBO_PARREADSTART, m_Cbo_ReadStart);
	DDX_Control(pDX, IDC_COMBO_PARREADEND, m_Cbo_ReadEnd);
	DDX_Control(pDX, IDC_BUTTON_PARREADALL, m_Btn_ReadAll);
	DDX_Control(pDX, IDC_BUTTON_EEPREAD_PAR, m_Btn_EepRead);
	DDX_Control(pDX, IDC_BUTTON_PARWRITE, m_Btn_Write);
	DDX_Control(pDX, IDC_SPIN_WRITEPAR, m_Spin_WritePar);
	DDX_Control(pDX, IDC_COMBO_PARWRITESTART, m_Cbo_WriteStart);
	DDX_Control(pDX, IDC_COMBO_PARWRITEEND, m_Cbo_WriteEnd);
	DDX_Control(pDX, IDC_BUTTON_PARWRITEALL, m_Btn_WriteAll);
	DDX_Control(pDX, IDC_BUTTON_EEPWRITE_PAR, m_Btn_EepWrite);
	DDX_Control(pDX, IDC_CHECK_FDBACKREADPAR, m_Chk_FeedBackRead);
	DDX_Control(pDX, IDC_CHECK_FDBACKWRITEPAR, m_Chk_FeedBackWrite);
	DDX_Control(pDX, IDC_BUTTON_PARCLEARRX, m_Btn_ClearRx);
	DDX_Control(pDX, IDC_BUTTON_SAVEHEX, m_Btn_SaveHex);
	DDX_Control(pDX, IDC_PROGRESS_LOADING, m_Progress_Loading);
	DDX_Control(pDX, IDC_BUTTON_PARAMETERCLOSE, m_Btn_Close);
	DDX_Control(pDX, IDC_LOADING_PAR, m_PicLoading);
	DDX_Control(pDX, IDC_BUTTON_MINIMIZE, m_Btn_Minimize);
	DDX_Control(pDX, IDC_BUTTON_CONNECT, m_Btn_Connect);
}

BEGIN_MESSAGE_MAP(CParameterDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_PARAMETERCLOSE, &CParameterDlg::OnBnClickedButtonParameterclose)
	ON_BN_CLICKED(IDC_BUTTON_OPENPAR, &CParameterDlg::OnBnClickedButtonOpenpar)
	ON_BN_CLICKED(IDC_BUTTON_SAVEPAR, &CParameterDlg::OnBnClickedButtonSavepar)
	ON_BN_CLICKED(IDC_BUTTON_PARAMETERKEYSET, &CParameterDlg::OnBnClickedButtonParameterkeyset)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_PARVALUE, &CParameterDlg::OnDeltaposSpinParvalue)
	ON_BN_CLICKED(IDC_BUTTON_PARREAD, &CParameterDlg::OnBnClickedButtonParread)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_READPAR, &CParameterDlg::OnDeltaposSpinReadpar)
	ON_BN_CLICKED(IDC_BUTTON_PARREADALL, &CParameterDlg::OnBnClickedButtonParreadall)
	ON_BN_CLICKED(IDC_BUTTON_EEPREAD_PAR, &CParameterDlg::OnBnClickedButtonEepreadPar)
	ON_BN_CLICKED(IDC_BUTTON_PARWRITE, &CParameterDlg::OnBnClickedButtonParwrite)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_WRITEPAR, &CParameterDlg::OnDeltaposSpinWritepar)
	ON_BN_CLICKED(IDC_BUTTON_PARWRITEALL, &CParameterDlg::OnBnClickedButtonParwriteall)
	ON_BN_CLICKED(IDC_BUTTON_EEPWRITE_PAR, &CParameterDlg::OnBnClickedButtonEepwritePar)
	ON_BN_CLICKED(IDC_BUTTON_PARCLEARRX, &CParameterDlg::OnBnClickedButtonParclearrx)
	ON_BN_CLICKED(IDC_BUTTON_SAVEHEX, &CParameterDlg::OnBnClickedButtonSavehex)
	ON_CBN_SELCHANGE(IDC_COMBO_PARMOVENAME, &CParameterDlg::OnCbnSelchangeComboParmovename)
	ON_EN_CHANGE(IDC_EDIT_PARDESCRIPTION, &CParameterDlg::OnEnChangeEditPardescription)
	ON_NOTIFY(TVN_BEGINLABELEDIT, IDC_PARAMETERTREELIST, &CParameterDlg::OnBeginLabelEditTreelist)
	ON_NOTIFY(TVN_SELCHANGED, IDC_PARAMETERTREELIST, &CParameterDlg::OnSelChangedTreelist)
	ON_NOTIFY(TVN_ENDLABELEDIT, IDC_PARAMETERTREELIST, &CParameterDlg::OnEndLabelEditTreelist)
	ON_WM_MOVE()
	ON_BN_CLICKED(IDC_BUTTON_MINIMIZE, &CParameterDlg::OnBnClickedButtonMinimize)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CParameterDlg::OnBnClickedButtonConnect)
	ON_WM_TIMER()
	ON_MESSAGE(WM_PAR_ENDLABELEDIT, &CParameterDlg::OnParEndLabelEdit)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CParameterDlg 메시지 처리기

BOOL CParameterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	SetWindowText(DLG_PARAMETER);

	int x = ReadIni(SEC_WININFO, KEY_PARAMETERDLGLEFT, DEF_PARAMETERDLGLEFT);
	int y = ReadIni(SEC_WININFO, KEY_PARAMETERDLGTOP, DEF_PARAMETERDLGTOP);
	this->SetWindowPos(NULL, x, y, DEF_PARAMETERDLGWIDTH, DEF_PARAMETERDLGHEIGHT, NULL);

	//this->SetWindowPos(NULL, 0, 0, DEF_PARAMETERDLGWIDTH, DEF_PARAMETERDLGHEIGHT, NULL);
	pParameterDlg = this;
	
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
		ConnectSocket = NULL;
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
	// CLOSE 버튼
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

	// Button
	m_Btn_OpenPar.SetBitmaps(IDB_OPEN, RGB(255, 0, 255));
	m_Btn_SavePar.SetBitmaps(IDB_SAVE, RGB(255, 0, 255));


// ----------------------------------------------------------------------------------------------------
// Draw Background
	DrawWinBg((CWnd*)this, &m_bmpBg, DLG_PARAMETER);

// ----------------------------------------------------------------------------------------------------
// Value
	m_Edit_ParFile.SetWindowTextW(_T(""));

	// Addr
	m_iAddr = 0;

	// Data
	m_Des = NULL;

	// Update
	m_bUpdatePar = FALSE;

	// Tree Item Handle
	m_hItem = NULL;
	m_hSelItem = NULL;
	m_hOldItem = NULL;

	// Select
	m_iSelCol = 0;
	m_strSelTx = _T("");
	m_strBeforeTx = _T("");

	m_bLoading = FALSE;

	m_bESC = FALSE;
	m_bEnter = FALSE;
	m_bEdit = FALSE;
	m_bLabelEdit = FALSE;
	m_bPressedCtrl = FALSE;
	m_iEditAddr = 0;

	m_bSaveHex = FALSE;
	m_dwCommAddr = 0;
	m_dwCommData = 0;

	m_bParameterKey = FALSE;

// ----------------------------------------------------------------------------------------------------
// TreeList
	CRect	sRect;
	CPoint	sPoint;

	GetDlgItem(IDC_PARAMETERLISTFRAME)->GetWindowRect(sRect);
	ClientToScreen(&sPoint);

	sRect.left -= sPoint.x;
	sRect.right -= sPoint.x;
	sRect.top -= sPoint.y;
	sRect.bottom -= sPoint.y;

	DWORD	dwStyle = TVS_LINESATROOT |
		TVS_FULLROWSELECT |
		TVS_EDITLABELS;

	DWORD	dwExStyle = TVS_EX_FULLROWMARK |
		TVS_EX_ITEMLINES |
		TVS_EX_SUBSELECT |
		TVS_EX_AUTOHSCROLL |
		TVS_EX_GRAYEDDISABLE |
		TVS_EX_NOCOLUMNRESIZE |
		TVS_EX_NOCHARSELCET |
		TVS_EX_EDITCLICK;

	m_List_Parameter.Create(dwStyle | WS_CHILD | WS_VISIBLE | WS_BORDER, sRect, this, IDC_PARAMETERTREELIST);
	m_List_Parameter.SetExtendedStyle(dwExStyle);

	// Set Column
	m_List_Parameter.InsertColumn(TC_PAR_ADDR, _T("Addr"), LVCFMT_CENTER, 50);
	m_List_Parameter.InsertColumn(TC_PAR_NAME, _T("Name"), 0);
	m_List_Parameter.InsertColumn(TC_PAR_BYTE, _T("Byte"), 0, 35);
	m_List_Parameter.InsertColumn(TC_PAR_RX, _T("Rx"), 0, 65);
	m_List_Parameter.InsertColumn(TC_PAR_TX, _T("Tx"), 0, 65);

	m_List_Parameter.SetColumnAutoEdit(TC_PAR_TX, TVAE_EDIT | TVAE_DBLCLICK);

	// Progress Bar
	m_Progress_Loading.ShowWindow(SW_HIDE);

#if 0
// ----------------------------------------------------------------------------------------------------
// Load Par, Option
	// Par
	m_Edit_ParFile.SetWindowTextW(ReadIni(SEC_PARAMETER, KEY_PARFILE, _T("")));

	// Feedback
	m_Chk_FeedBackRead.SetCheck(ReadIni(SEC_PARAMETER, KEY_PARFDBACKREAD, DEF_PARFDBACKREAD));
	m_Chk_FeedBackWrite.SetCheck(ReadIni(SEC_PARAMETER, KEY_PARFDBACKWRITE, DEF_PARFDBACKWRITE));

	// Key
	OpenKeyFile();
#else
	// Par
	//m_Edit_ParFile.SetWindowTextW(_T(""));
	m_Edit_ParFile.SetWindowTextW(ReadIni(SEC_PARAMETER, KEY_PARFILE, _T("")));

	// Feedback
	m_Chk_FeedBackRead.SetCheck(TRUE);
	m_Chk_FeedBackWrite.SetCheck(FALSE);

	// Key
	//OpenKeyFile();
	// default
	//m_strKey = ReadIni(SEC_SETTING, KEY_PARAMETERKEY, DEF_PARAMETERKEY);
#endif

// ----------------------------------------------------------------------------------------------------
// etc
	m_Cbo_ReadStart.InsertString(0, _T("0"));
	m_Cbo_ReadStart.SetCurSel(0);
	m_Cbo_ReadEnd.InsertString(0, _T("0"));
	m_Cbo_ReadEnd.SetCurSel(0);
	m_Cbo_WriteStart.InsertString(0, _T("0"));
	m_Cbo_WriteStart.SetCurSel(0);
	m_Cbo_WriteEnd.InsertString(0, _T("0"));
	m_Cbo_WriteEnd.SetCurSel(0);

	// Thread Flag
	g_pParLoadingThread = NULL;
	g_pParReadAllThread = NULL;
	g_pParWriteAllThread = NULL;
	g_pEEPReadAllThread = NULL;
	g_pEEPWriteAllThread = NULL;

	bRunParLoadingThread = FALSE;
	bRunParReadAllThread = FALSE;
	bRunParWriteAllThread = FALSE;
	bRunEEPReadThread = FALSE;
	bRunEEPWriteThread = FALSE;
	bRunSaveHexThread = FALSE;

	m_bSuccessEEPRead = FALSE;
	m_bSuccessEEPWrite = FALSE;

	m_bStopAll = FALSE;

	EnableCtrl(FALSE);

	clock_t before;
	double result;
	before = clock();
	// Open Par
	CString strParFile = _T("");
	strParFile = ReadIni(SEC_PARAMETER, KEY_PARFILE, strParFile);
	if (OpenPar(strParFile))
		m_Edit_ParFile.SetWindowTextW(strParFile);
	else
		m_Edit_ParFile.SetWindowTextW(_T(""));
	result = (double)(clock() - before) / CLOCKS_PER_SEC;
	TRACE(_T("%f\n"), result);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

BOOL CParameterDlg::PreTranslateMessage(MSG* pMsg)
{
	int i = 0;
	CString str = 0;
	CEdit* edit = NULL;
	HTREEITEM hItem = NULL;
	CWnd* wndFocus = GetFocus();

	if (pMsg->message == WM_KEYDOWN) {
		if ((GetKeyState(VK_LCONTROL) & 0x8000) ||
			(GetKeyState(VK_RCONTROL) & 0x8000))
		{
			switch (pMsg->wParam)
			{
			case VK_A: // KEYDOWN - Ctrl + A
				if (wndFocus == NULL) return FALSE;
				if (wndFocus == (CWnd*)&m_Edit_Description)
				{
					m_Edit_Description.SetSel(0, m_Edit_Description.GetWindowTextLengthW());
					return TRUE;
				}
				break;
			case VK_C: // KEYDOWN - Ctrl + C
				if (wndFocus == NULL) return FALSE;
				if (wndFocus == m_List_Parameter.GetEditControl()) // TX Edit창
				{
					edit = m_List_Parameter.GetEditControl();
					edit->GetWindowTextW(str);
					copyClipboard(str);
					return TRUE;
				}
				else if (wndFocus == (CWnd*)&m_List_Parameter) // 선택중인 아이템
				{
					if (m_hSelItem == NULL) return FALSE;
					copyClipboard(m_List_Parameter.GetItemText(m_hSelItem, m_iSelCol));
					return TRUE;
				}
				break;
			case VK_Z: // KEYDOWN - Ctrl + Z
				if (THREAD_ON) return 0L;
				OnCtrlZ();
				break;
			case VK_UP: // KEYDOWN - Ctrl + UP
				if (THREAD_ON) return 0L;
				if (ConnectSocket && (m_hSelItem != NULL))
				{
					NMUPDOWN nmUpDn;
					nmUpDn.iDelta = -1;
					nmUpDn.iPos = m_Spin_TxValue.GetPos();
					nmUpDn.hdr.code = UDN_DELTAPOS;
					nmUpDn.hdr.hwndFrom = m_Spin_TxValue.m_hWnd;
					nmUpDn.hdr.idFrom = ::GetDlgCtrlID(m_Spin_TxValue.m_hWnd);

					m_bPressedCtrl = TRUE;
					::SendMessage(::GetParent(m_Spin_TxValue.m_hWnd), WM_NOTIFY, WPARAM(nmUpDn.hdr.idFrom), LPARAM(&nmUpDn));
					return TRUE;
				}
				break;
			case VK_DOWN: // KEYDOWN - Ctrl + DOWN
				if (THREAD_ON) return 0L;
				if (ConnectSocket && (m_hSelItem != NULL))
				{
					NMUPDOWN nmUpDn;
					nmUpDn.iDelta = 1;
					nmUpDn.iPos = m_Spin_TxValue.GetPos();
					nmUpDn.hdr.code = UDN_DELTAPOS;
					nmUpDn.hdr.hwndFrom = m_Spin_TxValue.m_hWnd;
					nmUpDn.hdr.idFrom = ::GetDlgCtrlID(m_Spin_TxValue.m_hWnd);

					m_bPressedCtrl = TRUE;
					::SendMessage(::GetParent(m_Spin_TxValue.m_hWnd), WM_NOTIFY, WPARAM(nmUpDn.hdr.idFrom), LPARAM(&nmUpDn));
					return TRUE;
				}
				break;
			}
		}
		switch (pMsg->wParam)
		{
		case VK_RETURN: // KEYDOWN - Enter
			// Edit Control
			if (wndFocus == NULL) return FALSE;
			if (wndFocus == m_List_Parameter.GetEditControl())
			{
				m_bEnter = TRUE;
				return CDialog::PreTranslateMessage(pMsg);
			}
			// TreeList Control
			else if (wndFocus->m_hWnd == m_List_Parameter.m_hWnd)
			{
				if (m_List_Parameter.GetSelectionColumn())
					i = m_List_Parameter.GetSelectionColumn();

				switch (i)
				{
				case TC_PAR_ADDR:
				case TC_PAR_NAME:
				case TC_PAR_BYTE:
				case TC_PAR_RX:
				case TC_PAR_TX:
					//m_List_Parameter.EditLabel(m_hSelItem, TC_PAR_TX);
					PostMessage(VK_RETURN);
					OnBnClickedButtonParwrite();
					break;
				}
				return TRUE;
			}
			break;
			// KEYDOWN - UP
		case VK_UP:
			if (wndFocus == NULL) return FALSE;
			if (wndFocus == m_List_Parameter.GetEditControl()){
				m_List_Parameter.EndEditLabelNow(TRUE);
				OnParEndLabelEdit(NULL, NULL);
				hItem = m_List_Parameter.GetPrevVisibleItem(m_hSelItem);
				if (hItem != NULL)
					m_List_Parameter.SelectItem(hItem, m_iSelCol);
				return TRUE;
			}
			break;

			// KEYDOWN - DOWN
		case VK_DOWN:
			if (wndFocus == NULL) return FALSE;
			if (wndFocus == m_List_Parameter.GetEditControl()){
				m_List_Parameter.EndEditLabelNow(TRUE);
				OnParEndLabelEdit(NULL, NULL);
				hItem = m_List_Parameter.GetNextVisibleItem(m_hSelItem);
				if (hItem != NULL)
					m_List_Parameter.SelectItem(hItem, m_iSelCol);
				return TRUE;
			}
			break;
			// KEYDOWN - ESC
		case VK_ESCAPE:
			if (wndFocus == NULL) return FALSE;
			if (wndFocus == m_List_Parameter.GetEditControl())
			{
				m_bESC = TRUE;
				m_List_Parameter.EndEditLabelNow(TRUE);
			}
			return TRUE;
			// KEYDOWN - Page Up
		case VK_PRIOR:
			if (wndFocus == NULL) return FALSE;
			if (wndFocus == m_List_Parameter.GetEditControl())
			{
				m_bESC = TRUE;
				m_List_Parameter.EndEditLabelNow(TRUE);
				return CDialog::PreTranslateMessage(pMsg);
			}
			break;
			// KEYDOWN - Page Down
		case VK_NEXT:
			if (wndFocus == NULL) return FALSE;
			if (wndFocus == m_List_Parameter.GetEditControl())
			{
				m_bESC = TRUE;
				m_List_Parameter.EndEditLabelNow(TRUE);
				return CDialog::PreTranslateMessage(pMsg);
			}
			break;
		}
	}
	// Mouse Wheel
	else if (pMsg->message == WM_MOUSEWHEEL)
	{
		if (wndFocus == NULL) return FALSE;
		if (wndFocus->m_hWnd == m_List_Parameter.m_hWnd)
		{
			return CDialog::PreTranslateMessage(pMsg);
		}
		else if (wndFocus->m_hWnd == m_Spin_ReadPar.m_hWnd ||
			wndFocus->m_hWnd == m_Spin_TxValue.m_hWnd ||
			wndFocus->m_hWnd == m_Spin_WritePar.m_hWnd ||
			wndFocus->m_hWnd == m_Btn_Read.m_hWnd ||
			wndFocus->m_hWnd == m_Btn_Write.m_hWnd ||
			wndFocus->m_hWnd == m_Static_TxValue.m_hWnd)
		{
			m_List_Parameter.SetFocus();
			return TRUE;
		}
		else if (wndFocus == m_List_Parameter.GetEditControl())
		{
			m_List_Parameter.EndEditLabelNow(FALSE);
			return TRUE;
		}
		else
		{
			return TRUE;
		}
	}

	// Default Window Message
	if (DefaultWindowMessage(pMsg))	return TRUE;
	else							return CDialogEx::PreTranslateMessage(pMsg);
}


int CParameterDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetWindowLongPtr(m_hWnd, GWL_STYLE, WS_SYSMENU | WS_MINIMIZEBOX);

	RedrawWindow();

	return 0;
}


void CParameterDlg::OnPaint()
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


// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CParameterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CParameterDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetCapture();
	m_Point = point;

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CParameterDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (this == GetCapture())
	{
		CRect rcDialog;
		GetWindowRect(&rcDialog);

		int x = rcDialog.left + point.x - m_Point.x;
		int y = rcDialog.top + point.y - m_Point.y;

		SetWindowPos(NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		WriteIni(SEC_WININFO, KEY_PARAMETERDLGLEFT, x);
		WriteIni(SEC_WININFO, KEY_PARAMETERDLGTOP, y);
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void CParameterDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	ReleaseCapture();

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CParameterDlg::OnCancel()
{
	m_List_Parameter.DeleteAllItems();
	if (m_hItem != NULL)
	{
		delete[] m_hItem;
		m_hItem = NULL;
	}

	if (m_Des != NULL)
	{
		delete[] m_Des;
		m_Des = NULL;
	}

	SaveValue();

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


void CParameterDlg::OnBnClickedButtonParameterclose()
{
	OnCancel();
}


void CParameterDlg::OnBnClickedButtonMinimize()
{
	ShowWindow(SW_MINIMIZE);
}


// ====================================================================================================
// CParameterDlg :: OnSelChangedTreelist
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CParameterDlg::OnSelChangedTreelist(NMHDR *pNmHdr, LRESULT *pResult)
{
	// ----------------------------------------------------------------------------------------------------
	// 1. 멤버변수 설정
	m_hSelItem = m_List_Parameter.GetSelectedItem();
	m_iSelCol = m_List_Parameter.GetSelectionColumn();
	m_strBeforeTx = m_List_Parameter.GetItemText(m_hSelItem, TC_PAR_TX);

	if (!m_hSelItem) return;

	// ----------------------------------------------------------------------------------------------------
	// 2. 선택한 아이템(m_hSelItem)에 Bold체 적용, 이전에 선택한 아이템(m_hOldItem) Bold체 취소
	if (!m_bEnter)
	{
		SetBoldItem(m_hOldItem, TC_NAME, FALSE);
		SetBoldItem(m_hSelItem, TC_NAME, TRUE);

		m_hOldItem = m_hSelItem;
	}

	// ----------------------------------------------------------------------------------------------------
	// 3. Display Edit Label
	CString strAddr = m_List_Parameter.GetItemText(m_hSelItem, TC_PAR_ADDR);
	if (CheckHex(strAddr))
	{
		CString strByte = m_List_Parameter.GetItemText(m_hSelItem, TC_PAR_BYTE);
		if (!CheckDec(strByte)) return;

		switch (m_iSelCol)
		{
		case TC_PAR_TX:
			m_strSelTx = m_List_Parameter.GetItemText(m_hSelItem, TC_PAR_TX);
			m_List_Parameter.EditLabel(m_hSelItem, TC_PAR_TX);
			break;
		}
	}

	// ----------------------------------------------------------------------------------------------------
	DispDes();

	//EnableCtrl(TRUE);

	m_List_Parameter.RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

// ====================================================================================================
// CParameterDlg :: OnBeginLabelEditTreelist
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CParameterDlg::OnBeginLabelEditTreelist(NMHDR* pNMHDR, LRESULT* pResult)
{
	CString strAddr = m_List_Parameter.GetItemText(m_hSelItem, TC_PAR_ADDR);
	if (strAddr == _T("*")) return;

	int iLimit = 8;

	CEdit* edit = m_List_Parameter.GetEditControl();
	CString strByte = m_List_Parameter.GetItemText(m_hSelItem, TC_PAR_BYTE);

	if (!CheckDec(strByte)){
		if (!INMIDDLE(_ttoi(strByte), 1, 4))
			iLimit = _ttoi(strByte) * 2;
	}

	edit->SetLimitText(iLimit);

	m_bEdit = TRUE;
}

#define PAR_WARNING		FALSE	// 기본 16진수 확인... 이런거 빼고 전부 다.
// ====================================================================================================
// CParameterDlg :: OnEndLabelEditTreelist
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CParameterDlg::OnEndLabelEditTreelist(NMHDR* pNMHDR, LRESULT* pResult)
{
	TV_DISPINFO*	pTVDispInfo = (TV_DISPINFO*)pNMHDR;

	int i = 0;
	int	iCngS = 0;
	int	iCngE = 0;
	int	iForS = 0;
	int	iForE = 0;
	int	iByte = 0;
	int iSelCol = m_List_Parameter.GetSelectionColumn();
	int	iParNum = m_List_Parameter.GetCount();
	CString	str = _T("");
	CString	strTx = _T(""); // 바뀐 문자.
	CString	strAddr = _T("");
	CString	strByte = _T("");
	CString	strOldTx = m_List_Parameter.GetItemText(m_hSelItem, TC_PAR_TX);

	CEdit* edit = m_List_Parameter.GetEditControl();
	edit->GetWindowTextW(strTx);

	m_bEdit = FALSE;

	// ESC를 눌렀을 경우 수정하지 않음.
	if (m_bESC)
	{
		m_bESC = FALSE;
		pTVDispInfo->item.pszText = (LPWSTR)(LPCWSTR)m_strSelTx;
		return;
	}

	// Enter를 눌렀거나, 그 외 Edit창이 닫히는 경우에서 값이 변경되었을 때만 변경/적용
	if (!m_bEnter)
	{
		if (m_strSelTx == strTx)
		{
			pTVDispInfo->item.pszText = (LPWSTR)(LPCWSTR)m_strSelTx;
			return;
		}
		m_bEnter = TRUE;
	}
	// 이 함수가 끝난 후 무조건 OnRegEndLabelEdit가 호출되기 때문에
	// m_bEnter에 따라 적용/전송하게 됨.

	// ----------------------------------------------------------------------------------------------------
	// 검사
	strAddr = m_List_Parameter.GetItemText(m_hSelItem, TC_PAR_ADDR);
	strByte = m_List_Parameter.GetItemText(m_hSelItem, TC_PAR_BYTE);

	// Addr (16)
	if (!CheckHex(strAddr))
	{
		m_bEnter = FALSE;
		pTVDispInfo->item.pszText = (LPWSTR)(LPCWSTR)m_strSelTx;
		return;
	}

	// Byte (10)
	if (!CheckDec(strByte))
	{
		m_bEnter = FALSE;
		pTVDispInfo->item.pszText = (LPWSTR)(LPCWSTR)m_strSelTx;
		return;
	}

	// Byte (1~4)
	if (!INMIDDLE(_ttoi(strByte), 1, 4))
	{
		m_bEnter = FALSE;
		pTVDispInfo->item.pszText = (LPWSTR)(LPCWSTR)m_strSelTx;
		return;
	}

	// Tx(16)
	if (!CheckHex(strTx))
	{
		AfxMessageBox(_T("Please, input hex value."));

		m_bEnter = FALSE;
		pTVDispInfo->item.pszText = (LPWSTR)(LPCWSTR)m_strSelTx;
		return;
	}

	if (strTx.GetLength() > _ttoi(strByte) * 2)
	{
		AfxMessageBox(_T("Byte is too big than Tx value."));

		m_bEnter = FALSE;
		pTVDispInfo->item.pszText = (LPWSTR)(LPCWSTR)m_strSelTx;
		return;
	}

	// 적용
	m_List_Parameter.SetItemText(m_hSelItem, strTx, TC_PAR_TX);

	m_strBeforeTx = strOldTx;
	m_bLabelEdit = TRUE;
	m_iEditAddr = HexToDec(strAddr);
}


void CParameterDlg::OnBnClickedButtonOpenpar()
{
	int iMsgBoxReturn = 0;
	CString strParFile = _T("");
	CString strDefExt = _T("par");
	CString strFilter = _T("Parameter File(*.par)|*.par||");

	m_Edit_ParFile.GetWindowTextW(strParFile);

	// Save Par File
	if (m_bUpdatePar)
	{
		iMsgBoxReturn = AfxMessageBox(_T("Parameter file is modified. Do you want to save?"), MB_YESNOCANCEL);
		if (iMsgBoxReturn == IDCANCEL)
		{
			return;
		}
		else if (iMsgBoxReturn == IDNO)
		{
			// X
		}
		else if (iMsgBoxReturn == IDYES)
		{
			if (ShowSaveFileDlg(&strParFile, strDefExt, strFilter, this))
				SavePar(strParFile);
		}
	}

	// Open Dialog
	if (!ShowOpenFileDlg(&strParFile, strDefExt, strFilter, this))
		return;

	// Open
	if (!OpenPar(strParFile))
	{
		AfxMessageBox(_T("Fail file open."));
		return;
	}

	// ----------------------------------------------------------------------------------------------------
	// Display Description Infomation
	DispDes();
}


// ====================================================================================================
// CParameterDlg::OpenPar
// ----------------------------------------------------------------------------------------------------
/*
- 확장자	: *.par
- 형식		: ADDR NAME BYTE TX DESCRIPTION
시간 걸리면 로딩스레드!
*/
// ====================================================================================================
BOOL CParameterDlg::OpenPar(CString strPath)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int iS = 0;
	int iE = 0;
	int iAddrNum = 0;
	int iParNum = 0;
	PAR* parData = NULL;
	BOOL bReturn = FALSE;
	CString str = _T("");
	CString strLine = _T("");
	CString strData[5];
	CStdioFile parFile;
	HTREEITEM hItem = NULL;

	// ----------------------------------------------------------------------------------------------------
	// 1. 설정, 초기화
	// m_List_Parameter의 모든 아이템 삭제
	m_List_Parameter.DeleteAllItems();
	m_Edit_Description.SetWindowTextW(_T(""));
	for (i = m_Cbo_Movename.GetCount() - 1; i >= 0; i--)
		m_Cbo_Movename.DeleteString(i);

	// 파일 검사/오픈
	if (!parFile.Open(strPath, CFile::modeRead)) goto ENDOPENPAR;
	// 파일 검사, iParNum
	while (parFile.ReadString(strLine))
	{
		strLine.Trim();
		k = strLine.FindOneOf(_T("\t "));

		if (k == -1) {
			if (!strLine.GetString()) continue;
			goto ENDOPENPAR;
		}

		if ((!CheckHex(strLine.Left(k))) && (!(strLine.Left(k) == _T("*"))))
			goto ENDOPENPAR;

		iParNum++;
	}

	// 초기화, 할당
	parData = new PAR[iParNum];
	for (i = 0; i < iParNum; i++)
	{
		parData[i].strAddr = _T("");
		parData[i].strName = _T("");
		parData[i].strByte = _T("");
		parData[i].strTx = _T("");
		parData[i].strDescription = _T("");
	}

	i = 0;	// Line
	j = 0;	// Level	// 0 : ADDR
	// 1 : NAME
	// 2 : BYTE
	// 3 : TX
	// 4 : DESCRIPTION
	k = 0;	// Find space

	parFile.SeekToBegin();
	while (parFile.ReadString(strLine))
	{
		// 임시 배열
		// 초기화
		for (j = 0; j < 5; j++) strData[j] = _T("");
		// 디폴드값 설정
		strData[3] = _T("0");

		// 문자 확인
		// 공백 제거
		strLine = strLine.Trim(_T("\t "));
		// 문자 유무 확인
		if (!strLine.GetLength()) continue;

		// 분리
		for (j = 0; j < 5; j++)
		{
			// 문자 유무 확인
			if (!strLine.GetLength())
			{
				if (j <= 2) goto ENDOPENPAR;	// 0 ~ 2 필수, 없으면 오류
				if (j >= 3) break;				// 3 ~ 4 선택, 없으면 종료
			}

			// 공백 유무 확인
			if (j == 4) // Description
			{
				str = strLine;
			}
			else
			{
				k = strLine.FindOneOf(_T("\t "));
				if (k >= 0)	str = strLine.Left(k);	// 공백 O
				else		str = strLine;			// 공백 X
			}

			// Check
			if (j == 0)			// 0 ADDR : Hex or *
			{
				if (!(CheckHex(str) || (str == _T("*")))) goto ENDOPENPAR;

				if (HexToDec(str) > iAddrNum)
					iAddrNum = HexToDec(str);

			}
			else if (j == 1)		// 1 NAME : ADDRESS 가 * 이면 break
			{
				if (strData[0] == _T("*"))
				{
					str.Replace(_T("¡¡"), _T("  "));
					strData[1] = str;
					break;
				}
			}
			else if (j == 2)		// 2 BYTE : Dec, 1 ~ 4
			{
				if (!CheckDec(str)) goto ENDOPENPAR;
				if (!INMIDDLE(_ttoi(str), 1, 4)) goto ENDOPENPAR;
			}
			else if (j == 3)		// 3 TX : Hex, BYTE범위
			{
				if (!CheckHex(str)) goto ENDOPENPAR;
				if (!(str.GetLength() <= (_ttoi(strData[2]) * 2))) goto ENDOPENPAR;
			}

			// 저장
			strData[j] = str;

			// 제거
			if (k == -1) // 끝
			{
				strLine = _T("");
			}
			else // 남아있음
			{
				strLine = strLine.Right(strLine.GetLength() - k - 1);
				strLine.TrimLeft(_T("\t "));
			}
		}

		parData[i].strAddr = strData[0];
		parData[i].strName = strData[1];
		parData[i].strByte = strData[2];
		parData[i].strTx = strData[3];
		parData[i].strDescription = strData[4];

		i++;
	}

	// Close File
	parFile.Close();

	// Display
	// Init Description
	m_iAddr = iAddrNum;

	if (m_hItem != NULL)
	{
		delete[] m_hItem;
		m_hItem = NULL;
	}
	m_hItem = new HTREEITEM[iAddrNum + 1];
	for (i = 0; i < iAddrNum + 1; i++)
		m_hItem[i] = NULL;

	if (m_Des != NULL)
	{
		delete[] m_Des;
		m_Des = NULL;
	}
	m_Des = new CString[iAddrNum + 1];
	for (i = 0; i < iAddrNum + 1; i++)
		m_Des[i] = _T("");

	j = 0; // ComboBox Count

	// Display Parameter
	for (i = 0; i < iParNum; i++)
	{
		hItem = m_List_Parameter.InsertItem(_T(""));
		m_List_Parameter.SetItemText(hItem, parData[i].strAddr, TC_PAR_ADDR);
		m_List_Parameter.SetItemText(hItem, parData[i].strName, TC_PAR_NAME);

		if (CheckHex(parData[i].strAddr))
		{
			// m_hItem 추가
			m_hItem[HexToDec(parData[i].strAddr)] = hItem;
		}
		else
		{
			// Bookmark
			// Move Name 추가
			m_Cbo_Movename.InsertString(j, parData[i].strName);

			m_List_Parameter.SetItemBkColor(hItem, 0, ROOTCOLOR);
			m_List_Parameter.SetItemBkColor(hItem, 1, ROOTCOLOR);
			m_List_Parameter.SetItemBkColor(hItem, 2, ROOTCOLOR);
			m_List_Parameter.SetItemBkColor(hItem, 3, ROOTCOLOR);
			m_List_Parameter.SetItemBkColor(hItem, 4, ROOTCOLOR);

			j++;
			continue;
		}

		m_List_Parameter.SetItemText(hItem, parData[i].strByte, TC_PAR_BYTE);
		m_List_Parameter.SetItemText(hItem, parData[i].strTx, TC_PAR_TX);

		m_Des[HexToDec(parData[i].strAddr)] = parData[i].strDescription;
	}

	m_strBeforeTx = strData[3];

	if (m_Cbo_Movename.GetCount() > 0)
		m_Cbo_Movename.SetCurSel(0);
	else if (m_Cbo_Movename.GetCount() == 0)
		m_Cbo_Movename.EnableWindow(FALSE);

	m_Cbo_Movename.RedrawWindow();

	bReturn = TRUE;

	// ----------------------------------------------------------------------------------------------------
ENDOPENPAR:
	if (!bReturn)
	{
		// 할당 해제, 초기화
		m_hSelItem = NULL;
		m_hOldItem = NULL;

		m_iSelCol = TC_PAR_NAME;
		m_strSelTx = _T("");
		m_strBeforeTx = _T("");

		m_List_Parameter.DeleteAllItems();
		m_Edit_ParFile.SetWindowTextW(_T(""));
	}
	else
	{
		m_hSelItem = m_List_Parameter.GetFirstItem();

		m_iSelCol = TC_PAR_NAME;
		m_List_Parameter.SelectItem(m_hSelItem, m_iSelCol);
		m_List_Parameter.EnsureVisible(m_hSelItem, m_iSelCol);
		m_List_Parameter.SetFocusItem(m_hSelItem, m_iSelCol);
		m_Edit_ParFile.SetWindowTextW(strPath);
	}

	InitComboBox();

	if (parData != NULL)
		delete[] parData;

	m_bUpdatePar = FALSE;

	EnableCtrl(TRUE);

	return bReturn;
}

void CParameterDlg::OnBnClickedButtonSavepar()
{
	if (m_List_Parameter.GetCount() == 0) return;

	CString	strParFile = _T("");
	CString strDefExt = _T("par");
	CString strFilter = _T("Parameter File(*.par)|*.par||");

	// Save Dialog
	if (!ShowSaveFileDlg(&strParFile, strDefExt, strFilter, this))
		return;

	// Save
	if (!SavePar(strParFile))
	{
		AfxMessageBox(_T("Fail file save."));
		return;
	}

	m_bUpdatePar = FALSE;

	m_Edit_ParFile.SetWindowTextW(strParFile);
}

BOOL CParameterDlg::SavePar(CString strPath)
{
	int iCnt = m_List_Parameter.GetCount();
	if (!iCnt) return FALSE;

	CString str[5];
	CString strLine = _T("");
	HTREEITEM hItem = m_List_Parameter.GetFirstItem();
	CStdioFile parFile;
	if (!parFile.Open(strPath, CFile::modeCreate | CFile::modeWrite)) return FALSE;

	for (UINT i = 0; i < m_List_Parameter.GetCount(); i++)
	{
		for (UINT j = 0; j < 5; j++) str[0] = _T("");

		str[0] = m_List_Parameter.GetItemText(hItem, TC_PAR_ADDR);
		str[1] = m_List_Parameter.GetItemText(hItem, TC_PAR_NAME);
		str[2] = m_List_Parameter.GetItemText(hItem, TC_PAR_BYTE);
		str[3] = m_List_Parameter.GetItemText(hItem, TC_PAR_TX);
		if (CheckHex(str[0])) str[4] = m_Des[HexToDec(str[0])];

		str[1].Replace(_T("  "), _T("¡¡"));
		str[1].Replace(_T(" "), _T("_"));

		if (CheckHex(str[0]))
			strLine.Format(_T("%s\t%s\t%s\t%s\t%s\n"), str[0], str[1], str[2], str[3], str[4]);
		else
			strLine.Format(_T("%s\t%s\t%s\t%s\n"), str[0], str[1], str[2], str[3]);

		parFile.WriteString(strLine);

		hItem = m_List_Parameter.GetNextItem(hItem);
	}

	parFile.Close();

	return TRUE;
}


void CParameterDlg::OnBnClickedButtonParameterkeyset()
{
	if (ConnectSocket)
		AfxBeginThread(EnableParameterThread, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
	else
		pParameterDlg->EnableParameter(FALSE);
}

UINT EnableParameterThread(LPVOID pParam)
{
	pParameterDlg->OpenKeyFile();

	if (TxParameterKey())	pParameterDlg->EnableParameter(TRUE);
	else					pParameterDlg->EnableParameter(FALSE);

	return TRUE;
}

void CParameterDlg::EnableParameter(BOOL bEnable)
{
	if (bEnable)	m_Btn_ParKeyEnable.SetWindowTextW(_T("Parameter Enable On"));
	else			m_Btn_ParKeyEnable.SetWindowTextW(_T("Parameter ID Error"));

	EnableCtrl(bEnable);

	m_Btn_ParKeyEnable.EnableWindow(TRUE);
	m_List_Parameter.EnableWindow(TRUE);
}

void CParameterDlg::OnDeltaposSpinParvalue(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	int state = -1;

	m_Static_TxValue.SetFocus();

	if (m_hSelItem == NULL) return;
	if (m_bEdit) return;

	CString	strAddr = m_List_Parameter.GetItemText(m_hSelItem, TC_PAR_ADDR);
	CString	strByte = m_List_Parameter.GetItemText(m_hSelItem, TC_PAR_BYTE);
	CString strTx = m_List_Parameter.GetItemText(m_hSelItem, TC_PAR_TX);

	if (strAddr == _T("*")) return;

	if (!CheckHex(strAddr)) { AfxMessageBox(_T("Selected address is wrong.")); return; }
	if (!CheckDec(strByte)) { AfxMessageBox(_T("Byte is wrong.")); return; }

	DWORD dwAddr = HexToDec(strAddr);
	int iByte = _ttoi(strByte);

	// 1. Max Value
	DWORD64 dwMax = 0;
	DWORD64 dwValue = HexToDec(strTx);

	dwMax = pow((double)2, (iByte * 8));

	// 2. 값 계산
	if (pNMUpDown->iDelta < 0)
	{
		dwValue++;
		if (dwValue >= dwMax)
			dwValue = 0;
	}
	else if (pNMUpDown->iDelta > 0)
	{
		dwValue--;
		if (dwValue < 0)
			dwValue = dwMax;
	}

	// 3. 값 적용
	CString strValue = _T("");
	strValue.Format(_T("%x"), dwValue);
	strValue = strValue.Right(iByte * 2);

	// 4. Display Tx Value
	DispFullTxPar(m_hSelItem, HexToDec(strValue));

	// 5. Write
	//if (pComPort->m_bConnected)
	//	pUART->WriteParameter(dwAddr, iByte, HexToDec(strValue));
	if (ConnectSocket)
		state = WriteParameter(dwAddr, iByte, HexToDec(strValue));

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
		AfxMessageBox(_T("Write Fail"));
		return;
	}

	// Check Feedback
	if (pParameterDlg->m_Chk_FeedBackWrite.GetCheck())
		pParameterDlg->DispRxPar(dwAddr, HexToDec(strValue));

	// 6. Focus
	if (m_bPressedCtrl)
	{
		m_bPressedCtrl = FALSE;
		m_List_Parameter.SetFocus();
	}

	*pResult = 0;
}


// ====================================================================================================
// CParameterDlg :: OnParEndLabelEdit
// ----------------------------------------------------------------------------------------------------
/*
TreeListWnd.cpp 내에서 WM_PAR_ENDLABELEDIT 메세지를 받고 호출하는 함수
OnEndLabelEditTreelist를 끝낸 후에,
TreeListWnd.cpp의 TreeListEndLabelEdit 함수를 호출해야 TreeList에 작성되기 때문에
TreeListEndLabelEdit 함수 끝에 PostMessage를 추가하여 이 함수를 호출하여 동작 수행.
*/
// ====================================================================================================
LRESULT CParameterDlg::OnParEndLabelEdit(WPARAM wParam, LPARAM lParam)
{
	CString strByte = m_List_Parameter.GetItemText(m_hOldItem, TC_PAR_BYTE);
	CString strTx = m_List_Parameter.GetItemText(m_hOldItem, TC_PAR_TX);

	if (!m_bEnter) return 0L;
	m_bEnter = FALSE;

	SetBoldItem(m_hOldItem, TC_NAME, FALSE);
	SetBoldItem(m_hSelItem, TC_NAME, TRUE);

	m_hOldItem = m_hSelItem;

	// 표시 (이렇게까진 안해도 되는데... 되도록 CRegDlg이랑 통일시키기 위함
	DispFullTxPar(m_iEditAddr, HexToDec(strTx));

	// 전송
	if (ConnectSocket)
		WriteParameter(m_iEditAddr, _ttoi(strByte), HexToDec(strTx));

	return 0L;
}


void CParameterDlg::OnBnClickedButtonParread()
{
	int state = -1;

	if (!ConnectSocket) return;

	CString strAddr = m_List_Parameter.GetItemText(m_hSelItem, TC_PAR_ADDR);
	CString strByte = m_List_Parameter.GetItemText(m_hSelItem, TC_PAR_BYTE);

	if (strAddr == _T("*")) return;

	if (!CheckHex(strAddr))
	{
		AfxMessageBox(_T("Selected address is wrong."));
		return;
	}
	if (!CheckDec(strByte))
	{
		AfxMessageBox(_T("Selected byte is wrong."));
		return;
	}
	if (!INMIDDLE(_ttoi(strByte), 1, 4))
	{
		AfxMessageBox(_T("Byte value is 1 ~ 4."));
		return;
	}

	//pUART->ReadParameter(HexToDec(strAddr), _ttoi(strByte));
	state = ReadParameter(HexToDec(strAddr), _ttoi(strByte));
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
		AfxMessageBox(_T("Read Fail"));
		return;
	}
}


void CParameterDlg::OnDeltaposSpinReadpar(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	int state = -1;

	m_Btn_Read.SetFocus();

	HTREEITEM hItem = m_hSelItem;
	if (hItem == NULL) return;

	// Down
	if (pNMUpDown->iDelta > 0)
		hItem = m_List_Parameter.GetNextItem(hItem);
	// Up
	else if (pNMUpDown->iDelta < 0)
		hItem = m_List_Parameter.GetPrevSiblingItem(hItem);

	if (hItem == NULL) return;

	// 위치 이동
	m_List_Parameter.SelectItem(hItem, m_iSelCol);
	m_List_Parameter.EnsureVisible(hItem, m_iSelCol);

	// 포트가 닫혀있으면 이 이상 동작하지 않음.
	if (!ConnectSocket) return;

	CString	strAddr = m_List_Parameter.GetItemText(hItem, TC_PAR_ADDR);
	CString strByte = m_List_Parameter.GetItemText(hItem, TC_PAR_BYTE);

	if (strAddr == _T("*")) return;

	if (!CheckHex(strAddr))
	{
		AfxMessageBox(_T("Selected address is wrong."));
		return;
	}
	if (!CheckDec(strByte))
	{
		AfxMessageBox(_T("Selected byte is wrong."));
		return;
	}
	if (!INMIDDLE(_ttoi(strByte), 1, 4))
	{
		AfxMessageBox(_T("Byte value is 1 ~ 4."));
		return;
	}

	//pUART->ReadParameter(HexToDec(strAddr), _ttoi(strByte));
	state = ReadParameter(HexToDec(strAddr), _ttoi(strByte));
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
		AfxMessageBox(_T("Read Fail"));
		return;
	}
	*pResult = 0;
}


void CParameterDlg::OnBnClickedButtonParreadall()
{
	if (!ConnectSocket) return;

	// 동작 멈춤
	if (bRunParReadAllThread) {
		m_bStopAll = TRUE;
		return;
	}

	CString	strStart = _T("");
	CString	strEnd = _T("");

	m_Cbo_ReadStart.GetWindowTextW(strStart);
	m_Cbo_ReadEnd.GetWindowTextW(strEnd);

	if (!CheckHex(strStart))
	{
		AfxMessageBox(_T("Read start value is wrong."));
		return;
	}
	if (!CheckHex(strEnd))
	{
		AfxMessageBox(_T("Read End value is wrong."));
		return;
	}
	if (HexToDec(strStart) > HexToDec(strEnd))
	{
		AfxMessageBox(_T("Start address is too big than End address."));
		return;
	}

	StartReadAllThread();
}


// ====================================================================================================
// CParameterDlg::StartReadAllThread
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CParameterDlg::StartReadAllThread()
{
	// ----------------------------------------------------------------------------------------------------
	// Run Parameter Loading Thread
	g_pParLoadingThread = AfxBeginThread(LoadingThreadParameter, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);

	// ----------------------------------------------------------------------------------------------------
	// Run Parameter Read All Thread
	g_pParReadAllThread = AfxBeginThread(ReadAllThread_Par, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
}


// ====================================================================================================
// ReadAllThread_Par
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
UINT ReadAllThread_Par(LPVOID pParam)
{
	bRunParReadAllThread = TRUE;

	int i = 0;
	int j = 0;
	int iS = 0;
	int iE = 0;
	int iCnt = 0;
	int iByte = 0;
	int iListCnt = pParameterDlg->m_List_Parameter.GetCount();
	DWORD dwAddr = 0;
	DWORD dwData = 0;
	BYTE* addr = NULL;
	BYTE* data = NULL;
	CString str = _T("");
	CString strAddr = _T("");
	CString strByte = _T("");
	HTREEITEM hItem = pParameterDlg->m_List_Parameter.GetFirstItem();
	HTREEITEM hLastItem = hItem;

	int state = -1;

	g_iRxAddress = -1;

	// On Stop
	pParameterDlg->m_Btn_ReadAll.SetWindowTextW(_T("Stop"));
	pParameterDlg->m_Btn_ReadAll.EnableWindow(TRUE);

	// Start, End Area
	pParameterDlg->m_Cbo_ReadStart.GetWindowTextW(str);
	iS = HexToDec(str);
	pParameterDlg->m_Cbo_ReadEnd.GetWindowTextW(str);
	iE = HexToDec(str);

	if (!hItem)
	{
		AfxMessageBox(_T("Fail Read Value!"));
		goto ENDPARREADALL;
	}

	// Set ProgressCtrl
	pParameterDlg->m_Progress_Loading.ShowWindow(SW_SHOW);
	pParameterDlg->m_Progress_Loading.SetRange(0, iListCnt);
	pParameterDlg->m_Progress_Loading.SetPos(0);

	// ----------------------------------------------------------------------------------------------------
	// Read
	for (i = 0; i < iListCnt; i++)
	{
		if (pParameterDlg->m_bStopAll) goto ENDPARREADALL;			// Stop Read All
		if (hItem == NULL)
		{
			pParameterDlg->m_List_Parameter.SelectItem(hLastItem);
			pParameterDlg->m_List_Parameter.EnsureVisible(hLastItem);
			goto ENDPARREADALL;
		}

		pParameterDlg->m_List_Parameter.SelectItem(hItem);
		strAddr = pParameterDlg->m_List_Parameter.GetItemText(hItem, TC_PAR_ADDR);
		strByte = pParameterDlg->m_List_Parameter.GetItemText(hItem, TC_PAR_BYTE);

		// 검사
		if (!CheckHex(strAddr) || !CheckDec(strByte))
		{
			hItem = pParameterDlg->m_List_Parameter.GetNextItem(hItem);
			continue;
		}
		iByte = _ttoi(strByte);

		if (!INMIDDLE(iByte, 1, 4))
		{
			hItem = pParameterDlg->m_List_Parameter.GetNextItem(hItem);
			continue;
		}

		dwAddr = HexToDec(strAddr);

		if (iS>dwAddr)
		{
			hItem = pParameterDlg->m_List_Parameter.GetNextItem(hItem);
			continue;
		}

		if (iE<dwAddr)
		{
			pParameterDlg->m_List_Parameter.SelectItem(hLastItem);
			pParameterDlg->m_List_Parameter.EnsureVisible(hLastItem);
			goto ENDPARREADALL;
		}

		hLastItem = hItem;
		pParameterDlg->m_List_Parameter.EnsureVisible(hItem);

#if 0
		// Byte Loop
		for (j = 0; j < iByte; j++)
		{
			ReadParameter(dwAddr + j);

			iCnt = 0;
			while ((int)(dwAddr + j) > g_iRxAddress)
			{
				if (iCnt == 1000)
				{
					str.Format(_T("Fail Read Value (Address : %x)"), dwAddr + j);
					AfxMessageBox(str);
					pParameterDlg->m_List_Parameter.SelectItem(hItem);
					goto ENDPARREADALL;
				}
				iCnt++;
				Sleep(1);
			}
		}
#endif
		state = ReadParameter(dwAddr, iByte);
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
			pParameterDlg->EnableCtrl(FALSE);
			pParameterDlg->m_Btn_Connect.SetIcon(IDI_DISCONNECT, NULL);
			str.Format(_T("Fail Read Value (Address : %x)"), dwAddr);
			AfxMessageBox(str);
			pParameterDlg->m_List_Parameter.SelectItem(hItem);
			goto ENDPARREADALL;
		}
		hItem = pParameterDlg->m_List_Parameter.GetNextItem(hItem);

		pParameterDlg->m_Progress_Loading.SetStep(1);
		pParameterDlg->m_Progress_Loading.StepIt();
	}

	pParameterDlg->m_List_Parameter.SelectItem(hLastItem);
	pParameterDlg->m_List_Parameter.EnsureVisible(hLastItem);

	// ----------------------------------------------------------------------------------------------------
	// End
ENDPARREADALL:
	pParameterDlg->m_Btn_ReadAll.SetWindowTextW(_T("Read All"));
	pParameterDlg->m_bStopAll = FALSE;

	pParameterDlg->m_bLoading = FALSE;
	bRunParReadAllThread = FALSE;

	pParameterDlg->m_Progress_Loading.ShowWindow(SW_HIDE);
	
	//::CloseHandle(g_pParReadAllThread->m_hThread);
	return 0;
}


void CParameterDlg::OnBnClickedButtonEepreadPar()
{
	CString str = _T("");

	// 포트 연결
	if (!ConnectSocket)
	{
		AfxMessageBox(_T("Check Server Connection!"));
		return;
	}

	// 동작 멈춤
	if (bRunEEPReadThread) {
		m_bStopAll = TRUE;
		return;
	}


	// 파일
	m_Edit_ParFile.GetWindowTextW(str);
	CFileFind ffind;
	if (!ffind.FindFile(str))
	{
		AfxMessageBox(_T("Please open parameter file."));
		return;
	}
	ffind.Close();

	StartEEPReadThread();
}

// ====================================================================================================
// CParameterDlg::StartEEPReadThread
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CParameterDlg::StartEEPReadThread()
{
	// ----------------------------------------------------------------------------------------------------
	// Run Parameter Loading Thread
	g_pParLoadingThread = AfxBeginThread(LoadingThreadParameter, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);

	// ----------------------------------------------------------------------------------------------------
	// Run EEP Read All Thread
	g_pEEPReadAllThread = AfxBeginThread(EEPROMReadAllThread, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
}

// ====================================================================================================
// EEPROMReadAllThread
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
UINT EEPROMReadAllThread(LPVOID pParam)
{
	bRunEEPReadThread = TRUE;
	
	// On Stop
	pParameterDlg->m_Btn_EepRead.SetWindowTextW(_T("Stop"));
	pParameterDlg->m_Btn_EepRead.EnableWindow(TRUE);
	
	ReadEEPROMAll();

	pParameterDlg->m_Btn_EepRead.SetWindowTextW(_T("ROM Read All"));
	pParameterDlg->m_bStopAll = FALSE;

	pParameterDlg->m_bLoading = FALSE;
	bRunEEPReadThread = FALSE;
	pParameterDlg->m_Progress_Loading.ShowWindow(SW_HIDE);

	//::CloseHandle(g_pEEPReadAllThread->m_hThread);
	return 0L;
}

void CParameterDlg::OnBnClickedButtonParwrite()
{
	int state = -1;

	if (!ConnectSocket) return;

	int i = 0;
	CString strAddr = m_List_Parameter.GetItemText(m_hSelItem, TC_PAR_ADDR);
	CString strByte = m_List_Parameter.GetItemText(m_hSelItem, TC_PAR_BYTE);
	CString strTx = m_List_Parameter.GetItemText(m_hSelItem, TC_PAR_TX);

	if (strAddr == _T("*")) return;

	if (!CheckHex(strAddr))
	{
		AfxMessageBox(_T("Selected address is wrong."));
		return;
	}
	if (!CheckDec(strByte))
	{
		AfxMessageBox(_T("Selected byte is wrong."));
		return;
	}
	if (!INMIDDLE(_ttoi(strByte), 1, 4))
	{
		AfxMessageBox(_T("Byte value is 1 ~ 4."));
		return;
	}
	if (!CheckHex(strTx))
	{
		AfxMessageBox(_T("Selected Tx value is wrong."));
		return;
	}

	//pUART->WriteParameter(HexToDec(strAddr), _ttoi(strByte), HexToDec(strTx));
	state = WriteParameter(HexToDec(strAddr), _ttoi(strByte), HexToDec(strTx));
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
		AfxMessageBox(_T("Write Fail"));
	}
}


void CParameterDlg::OnDeltaposSpinWritepar(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	int state = -1;

	m_Btn_Read.SetFocus();

	if (m_bEdit) return;

	HTREEITEM hItem = m_hSelItem;
	if (hItem == NULL) return;

	// Down
	if (pNMUpDown->iDelta > 0)
		hItem = m_List_Parameter.GetNextItem(hItem);
	// Up
	else if (pNMUpDown->iDelta < 0)
		hItem = m_List_Parameter.GetPrevSiblingItem(hItem);

	if (hItem == NULL) return;

	m_List_Parameter.SelectItem(hItem, m_iSelCol);
	m_List_Parameter.EnsureVisible(hItem, m_iSelCol);

	if (!ConnectSocket) return;

	CString strAddr = m_List_Parameter.GetItemText(hItem, TC_PAR_ADDR);
	CString strByte = m_List_Parameter.GetItemText(hItem, TC_PAR_BYTE);
	CString strTx = m_List_Parameter.GetItemText(hItem, TC_PAR_TX);

	if (strAddr == _T("*")) return;

	if (!CheckHex(strAddr))
	{
		AfxMessageBox(_T("Selected address is wrong."));
		return;
	}
	if (!CheckDec(strByte))
	{
		AfxMessageBox(_T("Selected byte is wrong."));
		return;
	}
	if (!INMIDDLE(_ttoi(strByte), 1, 4))
	{
		AfxMessageBox(_T("Byte value is 1 ~ 4."));
		return;
	}
	if (!CheckHex(strTx))
	{
		AfxMessageBox(_T("Selected Tx value is wrong."));
		return;
	}

	//pUART->WriteParameter(HexToDec(strAddr), _ttoi(strByte), HexToDec(strTx));
	state = WriteParameter(HexToDec(strAddr), _ttoi(strByte), HexToDec(strTx));
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
		AfxMessageBox(_T("Write Fail"));
		return;
	}
	*pResult = 0;
}


void CParameterDlg::OnBnClickedButtonParwriteall()
{
	if (!ConnectSocket) return;

	// 동작 멈춤
	if (bRunParWriteAllThread) {
		m_bStopAll = TRUE;
		return;
	}

	CString strStart	= _T("");
	CString	strEnd		= _T("");

	m_Cbo_WriteStart.GetWindowTextW(strStart);
	m_Cbo_WriteEnd.GetWindowTextW(strEnd);

	if(!CheckHex(strStart))
	{
		AfxMessageBox(_T("Write start value is wrong."));
		return;
	}

	if(!CheckHex(strEnd))
	{
		AfxMessageBox(_T("Write end value is wrong."));
		return;
	}

	if(HexToDec(strStart) > HexToDec(strEnd))
	{
		AfxMessageBox(_T("Start address is too big than End address."));
		return;
	}

	StartWriteAllThread();
}

// ====================================================================================================
// CParameterDlg::StartWriteAllThread
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CParameterDlg::StartWriteAllThread()
{
	// ----------------------------------------------------------------------------------------------------
	// Run Parameter Loading Thread
	g_pParLoadingThread = AfxBeginThread(LoadingThreadParameter, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);

	// ----------------------------------------------------------------------------------------------------
	// Run Parameter Write All Thread
	g_pParWriteAllThread = AfxBeginThread(WriteAllThread_Par, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
}

// ====================================================================================================
// WriteAllThread_Par
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
UINT WriteAllThread_Par(LPVOID pParam)
{
	bRunParWriteAllThread = TRUE;

	int i = 0;
	int j = 0;
	int iS = 0;
	int iE = 0;
	int	iCnt = 0;
	int iByte = 0;
	int iListCnt = pParameterDlg->m_List_Parameter.GetCount();
	BYTE	byData[6] = { 0, };
	byData[0] = PC_STX;
	byData[1] = PC_CMD_PARW;
	byData[5] = PC_ETX;
	DWORD dwAddr = 0;
	DWORD dwData = 0;
	CString str = _T("");
	CString strAddr = _T("");
	CString strByte = _T("");
	CString strTx = _T("");
	HTREEITEM hItem = pParameterDlg->m_List_Parameter.GetFirstItem();
	HTREEITEM hLastItem = NULL;

	int state = -1;

	g_iRxAddress = -1;

	// On Stop
	pParameterDlg->m_Btn_WriteAll.SetWindowTextW(_T("Stop"));
	pParameterDlg->m_Btn_WriteAll.EnableWindow(TRUE);

	// Start, End Area
	pParameterDlg->m_Cbo_WriteStart.GetWindowTextW(str);
	iS = HexToDec(str);
	pParameterDlg->m_Cbo_WriteEnd.GetWindowTextW(str);
	iE = HexToDec(str);

	if (!hItem)
	{
		AfxMessageBox(_T("Fail Write Value!"));
		goto ENDPARWRITEALL;
	}

	// Set ProgressCtrl
	pParameterDlg->m_Progress_Loading.ShowWindow(SW_SHOW);
	pParameterDlg->m_Progress_Loading.SetRange(0, iListCnt);
	pParameterDlg->m_Progress_Loading.SetPos(0);

	// ----------------------------------------------------------------------------------------------------
	// Write
	for (i = 0; i < iListCnt; i++)
	{
		if (pParameterDlg->m_bStopAll) break;			// Stop Write All
		if (hItem == NULL)
		{
			pParameterDlg->m_List_Parameter.SelectItem(hLastItem);
			pParameterDlg->m_List_Parameter.EnsureVisible(hLastItem);
			goto ENDPARWRITEALL;
		}

		pParameterDlg->m_List_Parameter.SelectItem(hItem);
		strAddr = pParameterDlg->m_List_Parameter.GetItemText(hItem, TC_PAR_ADDR);
		strByte = pParameterDlg->m_List_Parameter.GetItemText(hItem, TC_PAR_BYTE);
		strTx = pParameterDlg->m_List_Parameter.GetItemText(hItem, TC_PAR_TX);

		// 검사
		if (!CheckHex(strAddr) || !CheckDec(strByte) || !CheckHex(strTx))
		{
			hItem = pParameterDlg->m_List_Parameter.GetNextItem(hItem);
			continue;
		}
		iByte = _ttoi(strByte);

		if (!INMIDDLE(iByte, 1, 4))
		{
			hItem = pParameterDlg->m_List_Parameter.GetNextItem(hItem);
			continue;
		}

		dwAddr = HexToDec(strAddr);
		dwData = HexToDec(strTx);
		//if (!INMIDDLE(dwAddr, iS, iE))
		{
			if (iS>dwAddr)
			{
				hItem = pParameterDlg->m_List_Parameter.GetNextItem(hItem);
				continue;
			}

			if (iE<dwAddr)
			{
				pParameterDlg->m_List_Parameter.SelectItem(hLastItem);
				pParameterDlg->m_List_Parameter.EnsureVisible(hLastItem);
				goto ENDPARWRITEALL;
			}
		}

		hLastItem = hItem;
		pParameterDlg->m_List_Parameter.EnsureVisible(hItem);

#if 0
		// Byte Loop
		for (j = 0; j < iByte; j++)
		{
			//pUART->WriteParameter(dwAddr + j, (BYTE)((dwData >> (j * 8)) & 0x00ff));
			WriteParameter(dwAddr + j, (BYTE)((dwData >> (j * 8)) & 0x00ff));

			iCnt = 0;
			while ((int)(dwAddr + j) > g_iRxAddress)
			{
				if (iCnt == 1000)
				{
					str.Format(_T("Fail Write Value (Address : %x) "), dwAddr + j);
					AfxMessageBox(str);
					pParameterDlg->m_List_Parameter.SelectItem(hItem);
					goto ENDPARWRITEALL;
				}
				iCnt++;
				Sleep(1);
			}

			// Check Feedback
			if (pParameterDlg->m_Chk_FeedBackWrite.GetCheck())
				pParameterDlg->DispRxPar(dwAddr, dwData);
		}
#endif
		state = WriteParameter(dwAddr, iByte, dwData);
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
			pParameterDlg->EnableCtrl(FALSE);
			pParameterDlg->m_Btn_Connect.SetIcon(IDI_DISCONNECT, NULL);
			str.Format(_T("Fail Write Value (Address : %x) "), dwAddr + j);
			AfxMessageBox(str);
			pParameterDlg->m_List_Parameter.SelectItem(hItem);
			goto ENDPARWRITEALL;
		}

		hItem = pParameterDlg->m_List_Parameter.GetNextItem(hItem);

		pParameterDlg->m_Progress_Loading.SetStep(1);
		pParameterDlg->m_Progress_Loading.StepIt();
	}

	pParameterDlg->m_List_Parameter.SelectItem(hLastItem);
	pParameterDlg->m_List_Parameter.EnsureVisible(hLastItem);

ENDPARWRITEALL:
	pParameterDlg->m_Btn_WriteAll.SetWindowTextW(_T("Write All"));
	pParameterDlg->m_bStopAll = FALSE;

	pParameterDlg->m_bLoading = FALSE;
	bRunParWriteAllThread = FALSE;

	pParameterDlg->m_Progress_Loading.ShowWindow(SW_HIDE);
	
	//::CloseHandle(g_pParWriteAllThread->m_hThread);
	return 0;
}


void CParameterDlg::OnBnClickedButtonEepwritePar()
{
	if (!ConnectSocket) return;

	// 동작 멈춤
	if (bRunEEPWriteThread) {
		m_bStopAll = TRUE;
		return;
	}

	StartEEPWriteThread();
	return;
}


// ====================================================================================================
// CParameterDlg::StartEEPWriteThread
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CParameterDlg::StartEEPWriteThread()
{
	// ----------------------------------------------------------------------------------------------------
	// Run Paramater Loading Thread
	g_pParLoadingThread = AfxBeginThread(LoadingThreadParameter, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);

	// ----------------------------------------------------------------------------------------------------
	// Run EEP Write All Thread
	g_pEEPWriteAllThread = AfxBeginThread(EEPROMWriteAllThread, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
}


// ====================================================================================================
// EEPROMWriteAllThread
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
UINT EEPROMWriteAllThread(LPVOID pParam)
{
	bRunEEPWriteThread = TRUE;

	// On Stop
	pParameterDlg->m_Btn_EepRead.SetWindowTextW(_T("Stop"));
	pParameterDlg->m_Btn_EepRead.EnableWindow(TRUE);

	WriteEEPROMAll();

	pParameterDlg->m_Btn_EepRead.SetWindowTextW(_T("ROM Write All"));
	pParameterDlg->m_bStopAll = FALSE;

	pParameterDlg->m_bLoading = FALSE;
	bRunEEPWriteThread = FALSE;
	pParameterDlg->m_Progress_Loading.ShowWindow(SW_HIDE);
	
	//::CloseHandle(g_pEEPWriteAllThread->m_hThread);
	return 0L;
}


void CParameterDlg::OnBnClickedButtonParclearrx()
{
	int i = 0;
	CString str = _T("");

	int iCnt = m_List_Parameter.GetCount();
	HTREEITEM hItem = m_List_Parameter.GetFirstItem();

	for (i = 0; i < iCnt; i++)
	{
		str = m_List_Parameter.GetItemText(hItem, TC_PAR_ADDR);
		if (str == _T("*"))
		{
			hItem = m_List_Parameter.GetNextItem(hItem);
			continue;
		}

		m_List_Parameter.SetItemText(hItem, _T(""), TC_PAR_RX);
		hItem = m_List_Parameter.GetNextItem(hItem);
	}
}


void CParameterDlg::OnBnClickedButtonSavehex()
{
	if (!ConnectSocket) return;

	StartSaveHexThread();
}


void CParameterDlg::StartSaveHexThread()
{
	// ----------------------------------------------------------------------------------------------------
	// Run Parameter Loading Thread
	g_pParLoadingThread = AfxBeginThread(LoadingThreadParameter, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);

	// ----------------------------------------------------------------------------------------------------
	// Run Save Hex Thread
	g_pParReadAllThread = AfxBeginThread(SaveHexThread, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
}

UINT SaveHexThread(LPVOID pParam)
{
	bRunSaveHexThread = TRUE;

	CString strHexFile = _T("");
	CString strDefExt = _T("hex");
	CString strFilter = _T("Binary File(*.hex)|*.hex||");

	// Save Dialog
	if (ShowSaveFileDlg(&strHexFile, strDefExt, strFilter, pParameterDlg))
	{
		// Save
		pParameterDlg->SaveHex(strHexFile);
	}

	pParameterDlg->m_bLoading = FALSE;
	bRunSaveHexThread = FALSE;

	return 0L;
}


// ====================================================================================================
// CParameterDlg::SaveHex(CString strPath)
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CParameterDlg::SaveHex(CString strPath)
{
	m_bSaveHex = TRUE;

	UINT i = 0;
	UINT j = 0;

	DWORD dwAddr = 0;
	int iByte = 0;

	int iTx = 0;
	DWORD dwMaxAddr = 0;

	BYTE by = 0;
	BYTE* byData = NULL;
	CString str = _T("");
	CString strAddr = _T("");
	CString strByte = _T("");
	CString strTx = _T("");
	HTREEITEM hItem = NULL;
	BYTE * addr = NULL;

	// Read 준비
	int iCnt = 0;
	int iiCnt = 0;
	int state = -1;
	pParameterDlg->m_bRunCmd = TRUE;

	BYTE SendData[5] = { 0, };
	SendData[0] = PC_STX;
	SendData[1] = PC_CMD_PARR;
	SendData[4] = PC_ETX;

	// ----------------------------------------------------------------------------------------------------
	// START_ID
	// 초기화
	g_iRxAddress = -1;

	m_dwCommAddr = 0;
	m_dwCommData = 0;

	// Send
	SendData[2] = (BYTE)(m_dwCommAddr >> 8);
	SendData[3] = (BYTE)(m_dwCommAddr);

	//pComPort->WriteComm(SendData, 5);
	state = WriteComm(SendData, 5);
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
		AfxMessageBox(_T("Fail file save."));
		m_bSaveHex = FALSE;
		return;
	}

	do {
		//Sleep(10);
		//ProcessWindowMessage();
		Wait(10);
		state = getDataFromRemote(ConnectSocket, tx_addr, 4, WBCOM, &addr);
		if (state < 0 | iCnt > RETRY)
		{
			AfxMessageBox(_T("Fail file save."));
			m_bSaveHex = FALSE;
			return;
		}
		if ((((UINT32)addr & 0X0000ffff) == 0xd002) | iiCnt == RETRY)
		{
			iiCnt = 0;
			iCnt++;
			state = WriteComm(SendData, 5);
		}
		iiCnt++;
	} while ((((UINT32)addr) & 0x000ffff) != 0x5802);
	g_iRxAddress = (ntohl((UINT32)addr) & 0x0000ffff);
	

	BYTE bySTART_ID = (BYTE)m_dwCommData;

	// ----------------------------------------------------------------------------------------------------
	// END_ID
	// 초기화
	g_iRxAddress = -1;

	m_dwCommAddr = 0xffff;
	m_dwCommData = 0;

	// Send
	SendData[2] = (BYTE)(m_dwCommAddr >> 8);
	SendData[3] = (BYTE)(m_dwCommAddr);

	//pComPort->WriteComm(SendData, 5);
	state = WriteComm(SendData, 5);
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
		AfxMessageBox(_T("Fail file save."));
		m_bSaveHex = FALSE;
		return;
	}
	
	iCnt = 0;
	iiCnt = 0;
	do {
		//Sleep(10);
		//ProcessWindowMessage();
		Wait(10);
		state = getDataFromRemote(ConnectSocket, tx_addr, 4, WBCOM, &addr);
		if (state < 0 | iCnt > RETRY)
		{
			AfxMessageBox(_T("Fail file save."));
			m_bSaveHex = FALSE;
			return;
		}
		if ((((UINT32)addr & 0X0000ffff) == 0xd002) | iiCnt == RETRY)
		{
			iiCnt = 0;
			iCnt++;
			state = WriteComm(SendData, 5);
		}
		iiCnt++;
	} while ((((UINT32)addr) & 0x000ffff) != 0x5802);
	g_iRxAddress = (ntohl((UINT32)addr) & 0x0000ffff);


	DWORD dwENDIDAddr = g_iRxAddress;
	BYTE byEND_ID = (BYTE)m_dwCommData;

	// ----------------------------------------------------------------------------------------------------
	// 검사
	// Check Max Addr
	hItem = m_List_Parameter.GetFirstItem();
	for (i = 0; i < m_List_Parameter.GetCount(); i++)
	{
		//ProcessWindowMessage();
		if (hItem == NULL) break;

		strAddr = m_List_Parameter.GetItemText(hItem, TC_PAR_ADDR);
		strByte = m_List_Parameter.GetItemText(hItem, TC_PAR_BYTE);
		strTx = m_List_Parameter.GetItemText(hItem, TC_PAR_TX);

		if (!CheckHex(strAddr)){ hItem = m_List_Parameter.GetNextItem(hItem); continue; }
		if (!CheckDec(strByte)) { hItem = m_List_Parameter.GetNextItem(hItem); continue; }
		if (!CheckHex(strTx)) { hItem = m_List_Parameter.GetNextItem(hItem); continue; }
		dwAddr = HexToDec(strAddr);
		iByte = _ttoi(strByte);
		iTx = HexToDec(strTx);

		if (!INMIDDLE(iByte, 1, 4)) { hItem = m_List_Parameter.GetNextItem(hItem); continue; }
		if (!(HexToDec(strTx) < pow((double)2, (iByte * 8)))) { hItem = m_List_Parameter.GetNextItem(hItem); continue; }

		if (dwMaxAddr < dwAddr + iByte - 1)
			dwMaxAddr = dwAddr + iByte - 1;

		hItem = m_List_Parameter.GetNextItem(hItem);
	}

	// 저장할 수 있는 게 없는 경우 중단
	if (!dwMaxAddr)
	{
		AfxMessageBox(_T("Fail file save."));
		m_bSaveHex = FALSE;
		return;
	}

	DWORD dwMaxData = (dwMaxAddr > dwENDIDAddr ? dwMaxAddr : dwENDIDAddr) + 1;

	byData = new BYTE[dwMaxData];
	memset(byData, 0xff, sizeof(BYTE)*dwMaxData);
	// 초기화잘되어있는지 확인.

	// ----------------------------------------------------------------------------------------------------
	// Write
	// Open
	CFile file;
	file.Open(strPath, CFile::typeBinary | CFile::modeCreate | CFile::modeWrite);

	// Write Flag
	BYTE flag[4] = { 0xfe, 0xff, 0xff, 0xff };
	file.Write(flag, 4);

	// Write START_ID
	byData[0] = bySTART_ID;

	// Write Data
	hItem = m_List_Parameter.GetFirstItem();
	for (i = 0; i < m_List_Parameter.GetCount(); i++)
	{
		//ProcessWindowMessage();
		if (hItem == NULL) break;

		strAddr = m_List_Parameter.GetItemText(hItem, TC_PAR_ADDR);
		strByte = m_List_Parameter.GetItemText(hItem, TC_PAR_BYTE);
		strTx = m_List_Parameter.GetItemText(hItem, TC_PAR_TX);

		// 검사
		if (!CheckHex(strAddr))	{ hItem = m_List_Parameter.GetNextItem(hItem); continue; }
		if (!CheckDec(strByte))	{ hItem = m_List_Parameter.GetNextItem(hItem); continue; }
		if (!CheckHex(strTx))	{ hItem = m_List_Parameter.GetNextItem(hItem); continue; }
		dwAddr = HexToDec(strAddr);
		iByte = _ttoi(strByte);
		iTx = HexToDec(strTx);

		if (!INMIDDLE(iByte, 1, 4)){ hItem = m_List_Parameter.GetNextItem(hItem); continue; }
		if (!(iTx < pow((double)2, (iByte * 8)))){ hItem = m_List_Parameter.GetNextItem(hItem); continue; }

		for (j = 0; j < iByte; j++)
		{
			by = (BYTE)(iTx >> (j * 8));
			byData[dwAddr + j] = by;
		}

		hItem = m_List_Parameter.GetNextItem(hItem);
	}

	byData[dwENDIDAddr] = byEND_ID;

	file.Write(byData, dwMaxData);

	delete[]byData;
	file.Close();

	m_bSaveHex = FALSE;
}


void CParameterDlg::OnCbnSelchangeComboParmovename()
{
	int i = 0;

	if (m_hSelItem == NULL) return;

	UINT uiParNum = m_List_Parameter.GetCount();
	if (uiParNum == 0) return;

	CString strSelectName = _T("");
	m_Cbo_Movename.GetLBText(m_Cbo_Movename.GetCurSel(), strSelectName);

	HTREEITEM hItem = m_List_Parameter.GetFirstItem();
	HTREEITEM hLastItem = m_List_Parameter.GetLastVisibleItem();

	for (i = 0; i < uiParNum; i++)
	{
		//ProcessWindowMessage();
		CString	strAddr = m_List_Parameter.GetItemText(hItem, TC_PAR_ADDR);

		if (strAddr != _T("*")){
			hItem = m_List_Parameter.GetNextItem(hItem);
			continue;
		}

		CString	strName = m_List_Parameter.GetItemText(hItem, TC_PAR_NAME);
		if (strName == strSelectName)
		{
			m_List_Parameter.EnsureVisible(hLastItem);
			m_List_Parameter.SelectItem(hItem);
			m_List_Parameter.EnsureVisible(hItem);
			return;
		}

		hItem = m_List_Parameter.GetNextItem(hItem);
	}
}


void CParameterDlg::OnEnChangeEditPardescription()
{
	if (m_hSelItem == NULL) return;

	CString	strAddr = m_List_Parameter.GetItemText(m_hSelItem, TC_PAR_ADDR);
	CString strDescription = _T("");

	if (!CheckHex(strAddr)) return;

	m_Edit_Description.GetWindowTextW(strDescription);

	m_Des[HexToDec(strAddr)] = strDescription;
}


// ====================================================================================================
// CParameterDlg::EnableCtrl
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CParameterDlg::EnableCtrl(BOOL bEnable)
{
	BOOL b = bEnable;
	CFileFind ffind;
	BOOL bFileOpen = (m_List_Parameter.GetCount() > 0);

	CString strKey = _T("");
	m_Btn_ParKeyEnable.GetWindowTextW(strKey);
	BOOL bKey = (strKey == _T("Parameter Enable On") ? TRUE : FALSE);

	if (!bEnable)
		b = FALSE;
	else
	{
		//if (!pComPort->m_bConnected) {
		if (!ConnectSocket) {
			b = FALSE;
		}
		else {
			if (!bKey) {
				b = FALSE;
			}
			else {
				if (bFileOpen)	b = TRUE;
				else			b = FALSE;
			}
		}
	}

	// Bookmark
	BOOL bBookmark;
	if (m_hSelItem == NULL) {
		bBookmark = b;
	}
	else {
		CString strAddr = m_List_Parameter.GetItemText(m_hSelItem, TC_PAR_ADDR);
		if (CheckHex(strAddr)) {
			bBookmark = TRUE;
		}
		else {
			bBookmark = FALSE;
		}
	}

	// ----------------------------------------------------------------------------------------------------
	// Enable
	// Key
	if ((bRunParLoadingThread == TRUE) || (ConnectSocket == NULL))
		m_Btn_ParKeyEnable.EnableWindow(FALSE);
	else
		m_Btn_ParKeyEnable.EnableWindow(TRUE);

	// Read
	m_Btn_Read.EnableWindow(b);
	m_Spin_ReadPar.EnableWindow(b);
	m_Cbo_ReadStart.EnableWindow(b);
	m_Cbo_ReadEnd.EnableWindow(b);
	m_Btn_ReadAll.EnableWindow(b);
	m_Btn_EepRead.EnableWindow(b);

	// Write
	m_Btn_Write.EnableWindow(b);
	m_Spin_WritePar.EnableWindow(b);
	m_Cbo_WriteStart.EnableWindow(b);
	m_Cbo_WriteEnd.EnableWindow(b);
	m_Btn_WriteAll.EnableWindow(b);
	m_Btn_EepWrite.EnableWindow(b);
	m_Spin_TxValue.EnableWindow(b);

	// FeedBack
	m_Chk_FeedBackRead.EnableWindow(b);
	m_Chk_FeedBackWrite.EnableWindow(b);

	// File
	if (m_bLoading)
	{
		m_Btn_OpenPar.EnableWindow(bEnable);
		m_Btn_SavePar.EnableWindow(bEnable && bFileOpen);
		m_Btn_SaveHex.EnableWindow(b);
	}
	else
	{
		m_Btn_OpenPar.EnableWindow(TRUE);
		m_Btn_SavePar.EnableWindow(TRUE && bFileOpen);
		m_Btn_SaveHex.EnableWindow(TRUE);
	}

	// Bookmark
	m_Edit_Description.EnableWindow(bEnable&&bBookmark);

	// etc
	//m_Btn_ParKeyEnable.EnableWindow(bEnable&&pComPort->m_bConnected);

	m_Cbo_Movename.EnableWindow(bEnable && bFileOpen && (m_Cbo_Movename.GetCount() > 0));
	m_Btn_ClearRx.EnableWindow(b);	// && bFileOpen);

	if (!m_bStopAll)
	{
		if (bRunParReadAllThread)
			m_Btn_ReadAll.EnableWindow(TRUE);
		if (bRunParWriteAllThread)
			m_Btn_WriteAll.EnableWindow(TRUE);
		if (bRunEEPReadThread)
			m_Btn_EepRead.EnableWindow(TRUE);
		if (bRunEEPWriteThread)
			m_Btn_EepWrite.EnableWindow(TRUE);
	}
}

// ====================================================================================================
// CParameterDlg::DispDes
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CParameterDlg::DispDes()
{
	BOOL bEnableDescription = FALSE;

	CString strDescription = _T("");

	if (m_hSelItem == NULL)
		goto ENDDESCRIPTION;
	else
	{
		CString strAddr = m_List_Parameter.GetItemText(m_hSelItem, TC_PAR_ADDR);
		if (!CheckHex(strAddr)) goto ENDDESCRIPTION;

		int iAddr = HexToDec(strAddr);
		
		if (m_Des == NULL)	return;
		
		strDescription = m_Des[iAddr];
		bEnableDescription = TRUE;
	}

ENDDESCRIPTION:
	m_Edit_Description.SetWindowTextW(strDescription);
	m_Edit_Description.EnableWindow(bEnableDescription);
}

// ====================================================================================================
// CParameterDlg::InitComboBox
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CParameterDlg::InitComboBox()
{
	int i = 0;
	int j = 0;
	CString strAddr = _T("");
	HTREEITEM hItem = NULL;

	for (i = m_Cbo_ReadStart.GetCount() - 1; i >= 0; i--)
		m_Cbo_ReadStart.DeleteString(i);
	for (i = m_Cbo_ReadEnd.GetCount() - 1; i >= 0; i--)
		m_Cbo_ReadEnd.DeleteString(i);
	for (i = m_Cbo_WriteStart.GetCount() - 1; i >= 0; i--)
		m_Cbo_WriteStart.DeleteString(i);
	for (i = m_Cbo_WriteEnd.GetCount() - 1; i >= 0; i--)
		m_Cbo_WriteEnd.DeleteString(i);

	int iCnt = m_List_Parameter.GetCount();
	if (iCnt == 0)
	{
		m_Cbo_ReadStart.InsertString(0, _T("0"));
		m_Cbo_ReadEnd.InsertString(0, _T("0"));
		m_Cbo_WriteStart.InsertString(0, _T("0"));
		m_Cbo_WriteEnd.InsertString(0, _T("0"));
	}
	else
	{
		hItem = m_List_Parameter.GetFirstItem();
		for (i = 0; i < m_List_Parameter.GetCount(); i++)
		{
			if (hItem == NULL) break;

			strAddr = m_List_Parameter.GetItemText(hItem, TC_PAR_ADDR);
			if (!CheckHex(strAddr))
			{
				hItem = pParameterDlg->m_List_Parameter.GetNextItem(hItem);
				continue;
			}

			m_Cbo_ReadStart.InsertString(j, strAddr);
			m_Cbo_ReadEnd.InsertString(j, strAddr);
			m_Cbo_WriteStart.InsertString(j, strAddr);
			m_Cbo_WriteEnd.InsertString(j, strAddr);
			j++;
			//Sleep(0);
			Wait(0);

			hItem = m_List_Parameter.GetNextItem(hItem);
		}
	}

	m_Cbo_ReadStart.SetCurSel(0);
	m_Cbo_ReadEnd.SetCurSel(m_Cbo_ReadEnd.GetCount() - 1);
	m_Cbo_WriteStart.SetCurSel(0);
	m_Cbo_WriteEnd.SetCurSel(m_Cbo_WriteEnd.GetCount() - 1);
}

// ====================================================================================================
// CParameterDlg::SetBoldItem
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CParameterDlg::SetBoldItem(HTREEITEM hItem, int iCol, BOOL bFlag)
{
	UINT iState = m_List_Parameter.GetItemState(hItem, TVIS_BOLD, iCol);

	if (bFlag)
		iState |= TVIS_BOLD;
	else
		iState ^= TVIS_BOLD;

	m_List_Parameter.SetItemState(hItem, iCol, iState, TVIS_BOLD);
}

// ====================================================================================================
// CParameterDlg::DispTxPar
// ----------------------------------------------------------------------------------------------------
/*
dwAddr에 맞게 iData를 추가해서 Tx에 표시
*/
// ====================================================================================================
void CParameterDlg::DispTxPar(DWORD dwAddr, DWORD dwData)
{
	UINT i = 0;
	UINT j = 0;

	int iByte = 0;
	DWORD64 dwTx = 0;
	BOOL		bFlag = FALSE;
	BYTE*		byData;
	CString		strAddr = _T("");
	CString		strByte = _T("");
	CString		strTx = _T("");
	HTREEITEM	hItem = m_List_Parameter.GetFirstItem();

	for (i = 0; i < m_List_Parameter.GetCount(); i++)
	{
		//ProcessWindowMessage();
		if (hItem == NULL) break;

		strAddr = m_List_Parameter.GetItemText(hItem, TC_PAR_ADDR);
		strByte = m_List_Parameter.GetItemText(hItem, TC_PAR_BYTE);

		if (!CheckHex(strAddr) || !CheckDec(strByte))
		{
			hItem = m_List_Parameter.GetNextItem(hItem); continue;
		}
		if (!INMIDDLE(_ttoi(strByte), 1, 4))
		{
			hItem = m_List_Parameter.GetNextItem(hItem); continue;
		}

		if (INMIDDLE(dwAddr, HexToDec(strAddr), HexToDec(strAddr) + _ttoi(strByte) - 1))
		{
			bFlag = TRUE;
			break;
		}

		hItem = m_List_Parameter.GetNextItem(hItem);
	}

	// 매칭되는 주소를 찾지 못했으면 동작 취소
	if (!bFlag) return;

	CString strOldTx = m_List_Parameter.GetItemText(hItem, TC_PAR_TX);

	// 적용
	iByte = _ttoi(strByte);
	byData = new BYTE[iByte];
	memset(byData, 0, sizeof(BYTE)*iByte);

	i = dwAddr - HexToDec(strAddr);

	strTx = strOldTx;
	if (CheckHex(strTx))
	{
		for (j = 0; j < iByte; j++)
			byData[j] = (BYTE)(HexToDec(strTx) >> (j * 8));
	}
	byData[i] = dwData;

	for (j = 0; j < iByte; j++)
		dwTx += byData[j] << (j * 8);

	strTx.Format(_T("%x"), dwTx);

	m_List_Parameter.SetItemText(hItem, strTx, TC_PAR_TX);
	delete[]byData;

	// 수정한 아이템이 선택중인 아이템일 경우 m_strSelTx, m_strBeforeTx 설정
	CString strSelAddr = m_List_Parameter.GetItemText(m_hSelItem, TC_PAR_ADDR);
	if (strSelAddr == strAddr)
	{
		if (m_bLabelEdit)
			m_bLabelEdit = FALSE;
		else
			m_strBeforeTx = strOldTx;

		m_strSelTx = m_List_Parameter.GetItemText(m_hSelItem, TC_PAR_TX);
	}

	m_bUpdatePar = TRUE;
}

// ====================================================================================================
// CParameterDlg::DispFullTxPar
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
BOOL CParameterDlg::DispFullTxPar(int iAddr, DWORD64 dwData)
{
	if (m_hItem == NULL) return FALSE;
	HTREEITEM hItem = m_hItem[iAddr];
	if (hItem == NULL) return FALSE;

	int i = 0;

	// Addr
	CString strAddr = m_List_Parameter.GetItemText(hItem, TC_PAR_ADDR);

	// Byte
	CString strByte = m_List_Parameter.GetItemText(hItem, TC_PAR_BYTE);

	// Tx
	CString strOldTx = m_List_Parameter.GetItemText(hItem, TC_PAR_TX);
	CString strTx = _T("");
	strTx.Format(_T("%x"), dwData);
	m_List_Parameter.SetItemText(hItem, strTx, TC_PAR_TX);

	// 수정한 아이템이 선택중인 아이템일 경우 m_strSelTx, m_strBeforeTx 설정
	CString strSelAddr = m_List_Parameter.GetItemText(m_hSelItem, TC_PAR_ADDR);
	if (strSelAddr == strAddr)
	{
		if (m_bLabelEdit)
			m_bLabelEdit = FALSE;
		else
			m_strBeforeTx = strOldTx;

		m_strSelTx = m_List_Parameter.GetItemText(m_hSelItem, TC_PAR_TX);
	}

	m_bUpdatePar = TRUE;

	return TRUE;
}

// ====================================================================================================
// CParameterDlg::DispFullTxPar
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
BOOL CParameterDlg::DispFullTxPar(HTREEITEM hItem, DWORD64 dwData)
{
	CString strAddr = m_List_Parameter.GetItemText(hItem, TC_PAR_ADDR);

	CString strOldTx = m_List_Parameter.GetItemText(hItem, TC_PAR_TX);

	CString strTx = _T("");
	strTx.Format(_T("%x"), dwData);
	m_List_Parameter.SetItemText(hItem, strTx, TC_PAR_TX);

	CString strSelAddr = m_List_Parameter.GetItemText(m_hSelItem, TC_PAR_ADDR);
	if (strSelAddr == strAddr)
	{
		if (m_bLabelEdit)
			m_bLabelEdit = FALSE;
		else
			m_strBeforeTx = strOldTx;

		m_strSelTx = m_List_Parameter.GetItemText(m_hSelItem, TC_PAR_TX);
	}

	m_bUpdatePar = TRUE;

	return TRUE;
}

// ====================================================================================================
// CParameterDlg::DispRxPar
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CParameterDlg::DispRxPar(DWORD dwAddr, DWORD dwData)
{
	UINT i = 0;
	UINT j = 0;
	UINT iByte = 0;
	BOOL bFlag = FALSE;
	BYTE* byData = NULL;
	UINT uiParNum = m_List_Parameter.GetCount();
	DWORD64 dwRx = 0;
	CString	str = _T("");
	CString	strAddr = _T("");
	CString	strByte = _T("");
	CString	strRx = _T("");
	HTREEITEM hItem = NULL;

	hItem = m_List_Parameter.GetFirstItem();

	for (i = 0; i < uiParNum; i++)
	{
		//ProcessWindowMessage();
		if (hItem == NULL) break; // Item이 없으면 끝.

		strAddr = m_List_Parameter.GetItemText(hItem, TC_PAR_ADDR);
		strByte = m_List_Parameter.GetItemText(hItem, TC_PAR_BYTE);

		if (!CheckHex(strAddr) || !CheckDec(strByte))
		{
			hItem = m_List_Parameter.GetNextItem(hItem); continue;
		}
		if (!INMIDDLE(_ttoi(strByte), 1, 4))
		{
			hItem = m_List_Parameter.GetNextItem(hItem); continue;
		}

		if (INMIDDLE(dwAddr, HexToDec(strAddr), HexToDec(strAddr) + _ttoi(strByte) - 1))
		{
			bFlag = TRUE;
			break;
		}

		hItem = m_List_Parameter.GetNextItem(hItem);
	}

	// 받아온 값이 목록의 Addr중에 있으면 bFlag==TRUE, Rx에 표시.
	if (bFlag)
	{
		iByte = _ttoi(strByte);
		byData = new BYTE[iByte];
		memset(byData, 0, sizeof(BYTE)*iByte);

		i = dwAddr - HexToDec(strAddr); // 위치(strAddr+i-1이 자기 주소. 0,1,2,3 중 하나)

		strRx = m_List_Parameter.GetItemText(hItem, TC_PAR_RX);
		if (CheckHex(strRx))
		{
			for (j = 0; j < iByte; j++)
				byData[j] = (BYTE)(HexToDec(strRx) >> (j * 8));
		}

		byData[i] = dwData;

		for (j = 0; j < iByte; j++)
			dwRx += byData[j] << (j * 8);

		strRx.Format(_T("%x"), dwRx);

		m_List_Parameter.SetItemText(hItem, strRx, TC_PAR_RX);
		delete[]byData;
	}

	SetItemText(hItem, RGB(0, 0, 0));
}

// ====================================================================================================
// CParameterDlg :: SetItemText
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CParameterDlg::SetItemText(HTREEITEM hItem, COLORREF uColor)
{
	m_List_Parameter.SetItemTextColor(hItem, TC_PAR_ADDR, uColor);
	m_List_Parameter.SetItemTextColor(hItem, TC_PAR_NAME, uColor);
	m_List_Parameter.SetItemTextColor(hItem, TC_PAR_BYTE, uColor);
	m_List_Parameter.SetItemTextColor(hItem, TC_PAR_RX, uColor);
	m_List_Parameter.SetItemTextColor(hItem, TC_PAR_TX, uColor);
}

// 주소로 Parameter 아이템 구하는 함수.
// ====================================================================================================
// CParameterDlg :: GetItemToAddress
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
BOOL CParameterDlg::GetItemToAddress(DWORD dwAddr, HTREEITEM* phItem)
{
	HTREEITEM hItem = m_List_Parameter.GetFirstItem();
	if (hItem == NULL) return FALSE;

	UINT i = 0;
	int iByte = 0;
	DWORD dwAddrCnt = 0;
	CString strAddr = _T("");
	CString strByte = _T("");

	for (i = 0; i < m_List_Parameter.GetCount(); i++)
	{
		//ProcessWindowMessage();
		if (hItem == NULL) return FALSE;

		strAddr = m_List_Parameter.GetItemText(hItem, TC_PAR_ADDR);
		if (!CheckHex(strAddr) || !CheckDec(strByte))
		{
			hItem = m_List_Parameter.GetNextItem(hItem);
			continue;
		}
		dwAddrCnt = HexToDec(strAddr);
		iByte = _ttoi(strByte);
		if (!INMIDDLE(iByte, 1, 4))
		{
			hItem = m_List_Parameter.GetNextItem(hItem);
			continue;
		}

		if (INMIDDLE(dwAddr, dwAddrCnt, dwAddrCnt + iByte - 1))
		{
			phItem = &hItem;
			return TRUE;
		}

		hItem = m_List_Parameter.GetNextItem(hItem);
	}

	return FALSE;
}


// ====================================================================================================
// LoadingThreadParameter
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
UINT LoadingThreadParameter(LPVOID pParam)
{
	// JTAG Thread Hold
	sendMsg(ConnectSocket, "rem_hold ");

	int i = 0;

	// 1. 플래그 설정
	bRunParLoadingThread = TRUE;
	pParameterDlg->m_bLoading = TRUE;

	// 2. 컨트롤 비활성화
	pParameterDlg->EnableCtrl(FALSE);
	pParameterDlg->m_Btn_Close.EnableWindow(FALSE);

	// 3. 로딩 이미지 재생
	if (pParameterDlg->m_PicLoading.Load(MAKEINTRESOURCE(IDR_LOADING), _T("GIF")))
	{
		pParameterDlg->m_PicLoading.ShowWindow(SW_SHOW);
		pParameterDlg->m_PicLoading.Draw();
	}

	// 4. 대기
	while (pParameterDlg->m_bLoading) { 
		//Sleep(50); 
		//ProcessWindowMessage();
		Wait(50);
	}

	// 5. 로딩 이미지 종료
	pParameterDlg->m_PicLoading.Stop();
	pParameterDlg->m_PicLoading.ShowWindow(SW_HIDE);

	// 6. 플래그 설정
	bRunParLoadingThread = FALSE;

	// 7. 컨트롤 활성화
	pParameterDlg->EnableCtrl(TRUE);
	pParameterDlg->m_Btn_Close.EnableWindow(TRUE);


	// JTAG Thread Hold
	sendMsg(ConnectSocket, "rem_release ");

	return 0L;
}

// ====================================================================================================
// CParameterDlg::SaveValue()
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CParameterDlg::SaveValue()
{
	// Par File
	CString strParFile = _T("");
	m_Edit_ParFile.GetWindowTextW(strParFile);

	WriteIni(SEC_PARAMETER, KEY_PARFILE, strParFile);

	// FeedBack
	WriteIni(SEC_PARAMETER, KEY_PARFDBACKREAD, m_Chk_FeedBackRead.GetCheck());
	WriteIni(SEC_PARAMETER, KEY_PARFDBACKWRITE, m_Chk_FeedBackWrite.GetCheck());

	// Key
	//SaveKeyFile();
}


void CParameterDlg::OnBnClickedButtonConnect()
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


// ====================================================================================================
// CParameterDlg::OnCtrlZ()
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CParameterDlg::OnCtrlZ()
{
	CString strAddr = m_List_Parameter.GetItemText(m_hSelItem, TC_PAR_ADDR);
	CString strByte = m_List_Parameter.GetItemText(m_hSelItem, TC_PAR_BYTE);
	CString strTx = m_List_Parameter.GetItemText(m_hSelItem, TC_PAR_TX);

	if (!CheckHex(strAddr)) return;
	DWORD dwAddr = HexToDec(strAddr);
	if (!CheckDec(strByte)) return;
	int iByte = _ttoi(strByte);
	if (!INMIDDLE(iByte, 1, 4)) return;

	if (m_strBeforeTx == _T("")) return;
	if (m_strBeforeTx == strTx) return;
	if (!CheckHex(strTx)) return;

	CString str = _T("");

	// Swap Tx
	str = m_strBeforeTx;
	m_strBeforeTx = strTx;
	strTx = str;
	DispFullTxPar(dwAddr, HexToDec(strTx));

	// Write
	if (ConnectSocket)
		WriteParameter(dwAddr, _ttoi(strByte), HexToDec(strTx));
}


void CParameterDlg::OpenKeyFile()
{
	DWORD64 dwKeyPw = 0;
	CString strKeyFile = ReadIni(SEC_SETTING, KEY_PARAMETERKEY, DEF_PARAMETERKEY);
	CString strPath = _T("");
	CString str = _T("");
	CString strKeyPw = _T("");
	CString strKey = _T("");

	if (strKeyFile != _T("NULL"))
	{
		// 랜덤 Key값
		dwKeyPw = _ttoi(strKeyFile);

		// 파일 오픈
		TCHAR cDir[256];
		::GetWindowsDirectory(cDir, 256);
		strPath.Format(_T("%s\\Temp\\TFP%x.tmp"), cDir, dwKeyPw);

		CStdioFile strFile;
		if (!strFile.Open(strPath, CFile::modeRead))
			goto ERRORKEY;

		// 변환
		strFile.ReadString(str);
		strFile.Close();

		// 떼서붙임
		str = str.Right(4) + str.Left(str.GetLength() - 4);

		// 16진수 확인
		if (!CheckHex(str))
			goto ERRORKEY;

		// 16진수 -> 10진수
		DWORD64 dwKey = HexToDec(str);

		// KeyPassword 추출
		strKeyPw = str.Mid(0, 1) + str.Mid(5, 1) + str.Mid(10, 1);

		strKey = str.Mid(1, 4) + str.Mid(6, 4);
		if (!CheckHex(strKey))
			goto ERRORKEY;

		if (dwKeyPw == _ttoi(strKeyPw))
		{
			m_strKey = strKey;
			m_strKeyPw = strKeyPw;
			return;
		}
		else
			goto ERRORKEY;
	}

ERRORKEY:
	// strKeyPw
	srand((unsigned int)time(NULL));
	m_strKeyPw.Format(_T("%d"), rand() % 999 + 100); // 랜덤적용

	// default
	m_strKey = _T("12345678");
}

// ====================================================================================================
// CParameterDlg::SaveKeyFile
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CParameterDlg::SaveKeyFile()
{
	CString str = _T("");

	TCHAR cDir[256];
	::GetWindowsDirectory(cDir, 256);
	CString strPath = _T("");

	// ----------------------------------------------------------------------------------------------------
	// 변환
	// 1. KeyPw 추가
	// Key(Hex) : @
	// KeyPw(Dec) : *
	// *@@@@*@@@@*
	CString strKey = m_strKeyPw.Mid(0, 1) + m_strKey.Left(4) + m_strKeyPw.Mid(1, 1) + m_strKey.Right(4) + m_strKeyPw.Mid(2, 1);

	// 2. 떼서붙임
	str = strKey.Right(strKey.GetLength() - 4) + strKey.Left(4);

	// ----------------------------------------------------------------------------------------------------
	// 저장
	// 파일
	DWORD dwKeyPw = _ttoi(m_strKeyPw);
	strPath.Format(_T("%s\\Temp\\TFP%x.tmp"), cDir, dwKeyPw);
	CStdioFile strFile;

	if (strFile.Open(strPath, CFile::modeReadWrite | CFile::modeCreate))
	{
		strFile.WriteString(str);

		strFile.Close();
	}

	// ecm.ini
	WriteIni(SEC_SETTING, KEY_PARAMETERKEY, m_strKeyPw);
}

void CParameterDlg::OnTimer(UINT_PTR nIDEvent)
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


void CParameterDlg::Check_Timer_On()
{
	m_CheckTimerID = SetTimer(ID_CHECK_TIMER, Check_Time, NULL);
}

void CParameterDlg::Check_Timer_Off()
{
	if (m_CheckTimerID)
	{
		if (this->GetSafeHwnd())
			KillTimer(m_CheckTimerID);
		m_CheckTimerID = 0;
	}
}

void CParameterDlg::Connect_Timer_On()
{
	m_ConnectTimerID = SetTimer(ID_CONNECT_TIMER, Connect_Time, NULL);
}

void CParameterDlg::Connect_Timer_Off()
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
				pParameterDlg->EnableCtrl(TRUE);
				pParameterDlg->m_Btn_Connect.SetIcon(IDI_CONNECT, NULL);

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
	NetClo(ConnectSocket);
	ConnectSocket = NULL;

	Wait(1);

	NetClo(StateSocket);
	StateSocket = NULL;

	pParameterDlg->EnableCtrl(FALSE);
	pParameterDlg->m_Btn_Connect.SetIcon(IDI_DISCONNECT, NULL);

	pParameterDlg->Check_Timer_Off();
	pParameterDlg->Connect_Timer_On();

	Invalidate_flsg = FALSE;

	return 0;
}



UINT Connect_Check_Thread(LPVOID pParam)
{
	ConnectSocket = NetCon(pParameterDlg->ch_ip, pParameterDlg->ch_port);
	//Sleep(1);
	Wait(1);
	StateSocket = NetCon(pParameterDlg->ch_ip, pParameterDlg->ch_port);

	if (ConnectSocket <= 0 || StateSocket <= 0)
	{
		ConnectSocket = NULL;
		StateSocket = NULL;
	}
	else
	{
		Invalidate_flsg = FALSE;

		pParameterDlg->Connect_Timer_Off();
		pParameterDlg->Check_Timer_On();
	}
	return 0;
}

BOOL CParameterDlg::OnEraseBkgnd(CDC* pDC)
{
	CDC dcBg;
	dcBg.CreateCompatibleDC(pDC);
	CBitmap* pOldBmpBg = (CBitmap*)dcBg.SelectObject(&m_bmpBg);

	CRect thisRect;
	GetWindowRect(thisRect);

	pDC->BitBlt(0, 0, thisRect.Width(), thisRect.Height(), &dcBg, 0, 0, SRCCOPY);
	dcBg.SelectObject(pOldBmpBg);

	return TRUE;

	//return CDialogEx::OnEraseBkgnd(pDC);
}
