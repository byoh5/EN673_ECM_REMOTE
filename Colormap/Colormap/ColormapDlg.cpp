
// ColormapDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "Colormap.h"
#include "ColormapDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

UINT	LoadingThreadColormap(LPVOID pParam);

UINT	ColormapReadThread(LPVOID pParam);
UINT	ColormapWriteThread(LPVOID pParam);
UINT	ColormapApplyThread(LPVOID pParam);
UINT	AwbWindowWriteThread(LPVOID pParam);
UINT	AwbBypassWriteThread(LPVOID pParam);

const UINT  ID_CHECK_TIMER = 100;
const UINT  ID_CONNECT_TIMER = 200;
UINT	State_Check_Thread(LPVOID pParam);
UINT	Connect_Check_Thread(LPVOID pParam);

#define		Check_Time		1000
#define		Connect_Time	5000

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


// CColormapDlg 대화 상자



CColormapDlg::CColormapDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CColormapDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ECM);
}

void CColormapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_COLORMAPCLOSE, m_Btn_Close);
	DDX_Control(pDX, IDC_STATIC_COLORMAP, m_Colormap);
	DDX_Control(pDX, IDC_BUTTON_COLORMAPREAD, m_Btn_Read);
	DDX_Control(pDX, IDC_RADIO_COLORMAPSPOT, m_Radio_Spot);
	DDX_Control(pDX, IDC_RADIO_COLORMAPFULL, m_Radio_Full);
	DDX_Control(pDX, IDC_CHECK_COLORMAPBYPASS, m_Check_Bypass);
	DDX_Control(pDX, IDC_EDIT_COLORMAPYCLIP, m_Edit_YClip);
	DDX_Control(pDX, IDC_EDIT_COLORMAPYSLICE, m_Edit_YSlice);
	DDX_Control(pDX, IDC_BUTTON_COLORMAPAPPLY, m_Btn_Apply);
	DDX_Control(pDX, IDC_BUTTON_COLORMAPWRITE, m_Btn_Write);
	DDX_Control(pDX, IDC_BUTTON_COLORMAPRESET, m_Btn_Reset);
	DDX_Control(pDX, IDC_BUTTON_COLORMAPSAVE, m_Btn_Save);
	DDX_Control(pDX, IDC_BUTTON_MINIMIZE, m_Btn_Minimize);
	DDX_Control(pDX, IDC_BUTTON_CONNECT, m_Btn_Connect);
	DDX_Control(pDX, IDC_PROGRESS_LOADING, m_Progress_Loading);
}

BEGIN_MESSAGE_MAP(CColormapDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_COLORMAPREAD, &CColormapDlg::OnBnClickedButtonColormapread)
	ON_BN_CLICKED(IDC_BUTTON_COLORMAPAPPLY, &CColormapDlg::OnBnClickedButtonColormapapply)
	ON_BN_CLICKED(IDC_BUTTON_COLORMAPWRITE, &CColormapDlg::OnBnClickedButtonColormapwrite)
	ON_BN_CLICKED(IDC_BUTTON_COLORMAPRESET, &CColormapDlg::OnBnClickedButtonColormapreset)
	ON_BN_CLICKED(IDC_BUTTON_COLORMAPSAVE, &CColormapDlg::OnBnClickedButtonColormapsave)
	ON_BN_CLICKED(IDC_BUTTON_COLORMAPCLOSE, &CColormapDlg::OnBnClickedButtonColormapclose)
	ON_BN_CLICKED(IDC_RADIO_COLORMAPSPOT, &CColormapDlg::OnBnClickedRadioColormapspot)
	ON_BN_CLICKED(IDC_RADIO_COLORMAPFULL, &CColormapDlg::OnBnClickedRadioColormapfull)
	ON_BN_CLICKED(IDC_CHECK_COLORMAPBYPASS, &CColormapDlg::OnBnClickedCheckColormapbypass)
	ON_EN_CHANGE(IDC_EDIT_COLORMAPYCLIP, &CColormapDlg::OnEnChangeEditColormapyclip)
	ON_EN_CHANGE(IDC_EDIT_COLORMAPYSLICE, &CColormapDlg::OnEnChangeEditColormapyslice)
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_MINIMIZE, &CColormapDlg::OnBnClickedButtonMinimize)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CColormapDlg::OnBnClickedButtonConnect)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CColormapDlg 메시지 처리기

BOOL CColormapDlg::OnInitDialog()
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

	SetWindowText(DLG_COLORMAP);

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

	int x = ReadIni(SEC_WININFO, KEY_COLORMAPDLGLEFT, DEF_COLORMAPDLGLEFT);
	int y = ReadIni(SEC_WININFO, KEY_COLORMAPDLGTOP, DEF_COLORMAPDLGTOP);
	SetWindowPos(NULL, x, y, 520, 620, NULL);
	//this->SetWindowPos(NULL, 0, 0, 520, 600, NULL);

// ----------------------------------------------------------------------------------------------------
// Control
	// Close
	pColormapDlg = this;
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

	// Save
	m_Btn_Save.SetWindowTextW(_T(""));
	m_Btn_Save.SetBitmaps(IDB_SAVE, RGB(255, 0, 255));

	// Progress Bar
	m_Progress_Loading.ShowWindow(SW_HIDE);

	int i = 0;
// ----------------------------------------------------------------------------------------------------
// Variable
	// Pointer
	m_bColormap = NULL;
	m_bColormapReset = NULL;
	m_dwCommColormap = NULL;

	// Flag
	m_iOldPoint = -1;

	// Colormap
	m_bColormap = new BOOL[COLORMAPSIZE*COLORMAPSIZE];
	for (i = 0; i < COLORMAPSIZE*COLORMAPSIZE; i++)
		m_bColormap[i] = 0;

	m_bColormapReset = new BOOL[COLORMAPSIZE*COLORMAPSIZE];
	for (i = 0; i < COLORMAPSIZE*COLORMAPSIZE; i++)
		m_bColormapReset[i] = 0;

	// m_dwCommColormap : 필요할 때에만 할당, 사용 끝나면 그때그때 반환

	// Value
	m_bAwbWindow = 1; // 기본은 Full
	m_uiAwbWinHsp = 0;
	m_uiAwbWinHw = 0;
	m_uiAwbWinVsp = 0;
	m_uiAwbWinVw = 0;
	m_bBypass = 0;
	m_uiYClip = 0;
	m_uiYSlice = 0;

	// Tx/Rx
	m_iAddrMin = COLORMAPTABLE_STARTADDR_EN673;
	m_iAddrMax = COLORMAPTABLE_STARTADDR_EN673 + COLORMAPSIZE - 1;
#if INSERT_EN674
	m_iAddrMin[EN674] = 0;
	m_iAddrMax[EN674] = 0;
#endif

	m_pwRxData = NULL;
	m_bColormapISP = FALSE;

	// Flag
	m_bColormapClick = FALSE; // 마우스 클릭
	bRunColormapLoadingThread = FALSE; // Tx/Rx Thread Flag

	// ----------------------------------------------------------------------------------------------------
	// Initialize Colormap Bitmap
	CDC* pDC = m_Colormap.GetWindowDC();

	// Create Bitmap
	m_bmpColormap.CreateCompatibleBitmap(pDC, COLORMAPWIDTH, COLORMAPHEIGHT);

	CDC dcColormap;
	dcColormap.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap = (CBitmap*)dcColormap.SelectObject(&m_bmpColormap);

	// Draw
	dcColormap.FillSolidRect(0, 0, COLORMAPWIDTH, COLORMAPHEIGHT, ::GetSysColor(COLOR_3DFACE));

	// Release
	dcColormap.SelectObject(pOldBitmap);
	m_Colormap.ReleaseDC(pDC);

	// Draw Background
	DrawColormap();

// ----------------------------------------------------------------------------------------------------
// etc
	m_bAwbInitial = FALSE;

	m_bSetAwbWin = FALSE;
	m_bSetBypass = FALSE;
	m_bSetYClip = FALSE;
	m_bSetYSlice = FALSE;
	SetAwbWindowMode(TRUE); // Full
	SetBypass(FALSE);
	SetYClip(0);
	SetYSlice(0);

	SetColormapReset();

	RxCheck_flag = TRUE;

	m_dwEN673BaseAdr = 0xf1100000;		// EN673 Dongle Base Address

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CColormapDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

BOOL CColormapDlg::PreTranslateMessage(MSG* pMsg)
{
	// Default Window Message
	if (DefaultWindowMessage(pMsg))	return TRUE;
	else							return CDialog::PreTranslateMessage(pMsg);
}

int CColormapDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetWindowLongPtr(m_hWnd, GWL_STYLE, WS_SYSMENU | WS_MINIMIZEBOX);

	RedrawWindow();

	return 0;
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CColormapDlg::OnPaint()
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
		// 아웃 라인
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

		dc.TextOutW(10, 6, DLG_COLORMAP);

		dc.SelectObject(pOldFont);

		// color map
		//CPaintDC dc(this); // device context for painting

		// Draw Colormap
		CDC* pDC = m_Colormap.GetWindowDC();

		CDC dcColormap;
		dcColormap.CreateCompatibleDC(pDC);
		CBitmap* pOldBitmap = (CBitmap*)dcColormap.SelectObject(&m_bmpColormap);

		pDC->BitBlt(1, 1, COLORMAPWIDTH - 2, COLORMAPHEIGHT - 2, &dcColormap, 1, 1, SRCCOPY);

		dcColormap.SelectObject(pOldBitmap);
		m_Colormap.ReleaseDC(pDC);
	}
}


void CColormapDlg::OnCancel()
{
	if (m_bColormap != nullptr)
		delete[] m_bColormap;
	m_bColormap = NULL;

	if (m_bColormapReset != nullptr)
		delete[] m_bColormapReset;
	m_bColormapReset = NULL;

	if (m_dwCommColormap != NULL)
		delete[] m_dwCommColormap;
	m_dwCommColormap = NULL;

	NetClo(ConnectSocket);
	ConnectSocket = NULL;
	
	NetClo(StateSocket);
	StateSocket = NULL;

	CDialogEx::OnCancel();
}


// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CColormapDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CColormapDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRect thisRect;
	CRect colormapRect;
	GetWindowRect(&thisRect);
	m_Colormap.GetWindowRect(&colormapRect);

	int iLeft = colormapRect.left - thisRect.left;
	int iTop = colormapRect.top - thisRect.top;

	BOOL bX = INMIDDLE(point.x, iLeft, iLeft + COLORMAPWIDTH - 2);
	BOOL bY = INMIDDLE(point.y, iTop + 1, iTop + COLORMAPHEIGHT - 2);

	if (bX && bY)
	{
		if (!bRunColormapLoadingThread)
		{
			SetCapture();
			m_bColormapClick = MK_LBUTTON;

			ClickColormap(point.x - COLORMAP_HSP, point.y - COLORMAP_VSP, TRUE);
			DrawColormap();

			// Save Point
			m_iOldPoint = ((point.x - COLORMAP_HSP) / COLORMAPSPACE) + (((point.y - COLORMAP_VSP) / COLORMAPSPACE)*COLORMAPSIZE);
		}
	}

	SetCapture();
	m_Point = point;

	CDialogEx::OnLButtonDown(nFlags, point);
}


// ====================================================================================================
// CColormapDlg::ClickColormap
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CColormapDlg::ClickColormap(CPoint* point, BOOL b)
{
	ClickColormap(point->x, point->y, b);
}

// ====================================================================================================
// CColormapDlg::ClickColormap
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CColormapDlg::ClickColormap(int iX, int iY, BOOL b)
{
	int i = 0;

	iX = iX / COLORMAPSPACE;
	iY = iY / COLORMAPSPACE;

	if (m_iOldPoint == -1)
	{
		SetColormapTable(iX, iY, b);
	}
	else
	{
		int iOldY = m_iOldPoint / COLORMAPSIZE;
		int iOldX = m_iOldPoint%COLORMAPSIZE;

		int iXGap = iX - iOldX;
		int iYGap = iY - iOldY;

		int iXSign = iXGap >= 0 ? 1 : -1; // 부호
		int iYSign = iYGap >= 0 ? 1 : -1; // 부호

		if (abs(iXGap) > abs(iYGap))
		{
			for (i = 1; i < abs(iXGap); i++)
				SetColormapTable(iOldX + (i*iXSign), iOldY + ((((float)abs(iYGap) / (float)abs(iXGap))*i)*iYSign), b);
		}
		else if (abs(iXGap) < abs(iYGap))
		{
			for (i = 1; i < abs(iYGap); i++)
				SetColormapTable(iOldX + ((((float)abs(iXGap) / (float)abs(iYGap))*i)*iXSign), iOldY + (i*iYSign), b);
		}
		else if (abs(iXGap) == abs(iYGap))
		{
			for (i = 1; i < abs(iXGap); i++)
				SetColormapTable(iOldX + (i*iXSign), iOldY + (i*iYSign), b);
		}

		SetColormapTable(iX, iY, b);
	}
}

// ====================================================================================================
// CColormapDlg::SetColormapTable
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CColormapDlg::SetColormapTable(int iX, int iY, BOOL b)
{
	m_bColormap[(iY*COLORMAPSIZE) + iX] = b;
}


void CColormapDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	CRect rect;
	GetClientRect(&rect);

	BOOL bX = INMIDDLE(point.x, COLORMAP_HSP + 1, COLORMAP_HSP + COLORMAPWIDTH - 2);
	BOOL bY = INMIDDLE(point.y, COLORMAP_VSP + 1, COLORMAP_VSP + COLORMAPHEIGHT - 2);

	if (m_bColormapClick)
	{
		if (bX && bY)
		{
			if (!bRunColormapLoadingThread)
			{
				if (m_bColormapClick == MK_LBUTTON)		ClickColormap(point.x - COLORMAP_HSP, point.y - COLORMAP_VSP, TRUE);
				else if (m_bColormapClick == MK_RBUTTON)		ClickColormap(point.x - COLORMAP_HSP, point.y - COLORMAP_VSP, FALSE);

				DrawColormap(); // Draw

				m_iOldPoint = ((point.x - COLORMAP_HSP) / COLORMAPSPACE) + (((point.y - COLORMAP_VSP) / COLORMAPSPACE)*COLORMAPSIZE); // Save Point
			}
		}
		else {
			m_iOldPoint = -1;
		}
	}
	else
	{
		if (this == GetCapture())
		{
			CRect rcDialog;
			GetWindowRect(&rcDialog);

			int x = rcDialog.left + point.x - m_Point.x;
			int y = rcDialog.top + point.y - m_Point.y;

			SetWindowPos(NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

			WriteIni(SEC_WININFO, KEY_COLORMAPDLGLEFT, x);
			WriteIni(SEC_WININFO, KEY_COLORMAPDLGTOP, y);
		}
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void CColormapDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_bColormapClick)
	{
		m_bColormapClick = FALSE;
		m_iOldPoint = -1;
	}

	ReleaseCapture();

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CColormapDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	CRect thisRect;
	CRect colormapRect;
	GetWindowRect(&thisRect);
	m_Colormap.GetWindowRect(&colormapRect);

	int iLeft = colormapRect.left - thisRect.left;
	int iTop = colormapRect.top - thisRect.top;

	BOOL bX = INMIDDLE(point.x, iLeft, iLeft + COLORMAPWIDTH - 2);
	BOOL bY = INMIDDLE(point.y, iTop + 1, iTop + COLORMAPHEIGHT - 2);

	if (bX && bY)
	{
		if (!bRunColormapLoadingThread)
		{
			SetCapture();
			m_bColormapClick = MK_RBUTTON;

			ClickColormap(point.x - COLORMAP_HSP, point.y - COLORMAP_VSP, FALSE);
			DrawColormap();
		}
	}

	CDialogEx::OnRButtonDown(nFlags, point);
}


void CColormapDlg::OnRButtonUp(UINT nFlags, CPoint point)
{
	if (m_bColormapClick)
	{
		m_bColormapClick = FALSE;
		m_iOldPoint = -1;
	}

	ReleaseCapture();

	CDialogEx::OnRButtonUp(nFlags, point);
}


void CColormapDlg::OnBnClickedButtonColormapclose()
{
	CColormapDlg::OnCancel();
}


void CColormapDlg::OnBnClickedButtonMinimize()
{
	ShowWindow(SW_MINIMIZE);
}


// ====================================================================================================
// LoadingThreadColormap
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
UINT LoadingThreadColormap(LPVOID pParam)
{
	sendMsg(ConnectSocket, "rem_hold ");
	// ----------------------------------------------------------------------------------------------------
	// 1. 플래그 설정
	bRunColormapLoadingThread = TRUE;
	pColormapDlg->m_bLoading = TRUE;

	// ----------------------------------------------------------------------------------------------------
	// 2. 컨트롤 비활성화

	pColormapDlg->m_Btn_Close.EnableWindow(FALSE);
	pColormapDlg->EnableCtrl(FALSE);

	// ----------------------------------------------------------------------------------------------------
	// 3. 로딩 이미지... 없음 보류

	// ----------------------------------------------------------------------------------------------------
	// 4. 대기
	while (pColormapDlg->m_bLoading){ 
		//Sleep(10);
		ProcessWindowMessage();  
		Wait(10); 
	}

	// ----------------------------------------------------------------------------------------------------
	// 5. 로딩 종료... 없음 보류

	// ----------------------------------------------------------------------------------------------------
	// 6. 컨트롤 활성화
	pColormapDlg->m_Btn_Close.EnableWindow(TRUE);
	pColormapDlg->EnableCtrl(TRUE);
	pColormapDlg->m_Progress_Loading.ShowWindow(SW_HIDE);
	// ----------------------------------------------------------------------------------------------------
	// 7. 플래그 설정
	bRunColormapLoadingThread = FALSE;

	sendMsg(ConnectSocket, "rem_release ");
	return 0L;
}


void CColormapDlg::OnBnClickedButtonColormapread()
{
	if (!ConnectSocket) return;

	StartColormapReadThread();
}


// ====================================================================================================
// CColormapDlg::StartColormapReadThread
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CColormapDlg::StartColormapReadThread()
{
	// ----------------------------------------------------------------------------------------------------
	// Run Loading Thread
	AfxBeginThread(LoadingThreadColormap, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);

	// ----------------------------------------------------------------------------------------------------
	// Run Colormap Read Thread
	AfxBeginThread(ColormapReadThread, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
}


// ====================================================================================================
// ColormapReadThread
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
UINT ColormapReadThread(LPVOID pParam)
{
	int i = 0;
	BOOL bSuccess = FALSE;

	// ----------------------------------------------------------------------------------------------------
	// Colormap Flag On
	pColormapDlg->m_bColormapISP = TRUE;
	bSuccess = pColormapDlg->ReadColormap_EN673();

	if (bSuccess)
	{
		pColormapDlg->m_bAwbInitial = TRUE;

		// AWB Window
		pColormapDlg->SetAwbWindowMode(pColormapDlg->m_bAwbWinMode);
		pColormapDlg->SetBypass(pColormapDlg->m_bBypass);
		pColormapDlg->SetYClip(pColormapDlg->m_uiYClip);
		pColormapDlg->SetYSlice(pColormapDlg->m_uiYSlice);

		// Initial Colormap
		if(pColormapDlg->m_bColormap == nullptr)
			pColormapDlg->m_bColormap = new BOOL[COLORMAPSIZE*COLORMAPSIZE];
		for (i = 0; i < COLORMAPSIZE*COLORMAPSIZE; i++)
			pColormapDlg->m_bColormap[i] = 0;

		// Convert
		pColormapDlg->ConvertToDrawTable(pColormapDlg->m_bColormap, pColormapDlg->m_dwCommColormap);

		// Save Reset Point
		pColormapDlg->SetColormapReset();
	}
	else
	{
		// Return Reset Point
		pColormapDlg->ResetColormapData();
	}

	// m_dwCommColormap 해제
	if (pColormapDlg->m_dwCommColormap != NULL)
		delete[] pColormapDlg->m_dwCommColormap;
	pColormapDlg->m_dwCommColormap = NULL;

	// Draw Colormap
	pColormapDlg->DrawColormap();

END:
	// ----------------------------------------------------------------------------------------------------
	// Colormap Flag Off
	pColormapDlg->m_bColormapISP = FALSE;

	// ----------------------------------------------------------------------------------------------------
	// End Loading
	pColormapDlg->m_bLoading = FALSE;

	return 0L;
}


// ====================================================================================================
// CColormapDlg::ReadColormap_EN673
// ----------------------------------------------------------------------------------------------------
/*
가로 64개 (Data Register 64개, Start Point/End Point 구성)
EN673, EN771
*/
// ====================================================================================================
BOOL CColormapDlg::ReadColormap_EN673()
{
	int i = 0;
	int uiAwbWinHsp = 0;
	int uiAwbWinHw = 0;
	int uiAwbWinVsp = 0;
	int uiAwbWinVw = 0;
	int uiAwbWinHspSpot = 0;
	int uiAwbWinHwSpot = 0;
	int uiAwbWinVspSpot = 0;
	int uiAwbWinVwSpot = 0;

	BOOL bReturn = FALSE;
	CString str = _T("");

	int state = -1;

	// ----------------------------------------------------------------------------------------------------
	// Ready
	// m_pwRxdata 할당
	m_pwRxData = new DWORD[COLORMAPSIZE];
	for (i = 0; i < COLORMAPSIZE; i++)
		m_pwRxData[i] = 0;

	// ----------------------------------------------------------------------------------------------------
	// Read
	int iCnt = 0;
	int iiCnt = 0;
	int iReadCnt = 0; // m_pwRxData;
	DWORD dwAddr = 0;
	DWORD dwData = 0;

	BYTE* temp = NULL;
	BYTE* flag = NULL;

	// 할당
	if (m_dwCommColormap == NULL)
		delete[] m_dwCommColormap;
	m_dwCommColormap = new DWORD[COLORMAPSIZE];
	
	// ----------------------------------------------------------------------------------------------------
	// Colormap Table (AWBL_CM)
#if JTAG_UART
	while (iReadCnt < COLORMAPSIZE)
	{
		iCnt = 0;
		iiCnt = 0;
		RxCheck_flag = TRUE;

		dwAddr = m_iAddrMin + iReadCnt;
		state = ReadISP(dwAddr);
		if (state < 0)
		{
			str.Format(_T("Fail Read Value - Colormap Table(Addr : 0x%x)"), dwAddr);
			goto END;
		}

		// Wait
		do{
			Sleep(10);
			state = getDataFromRemote(ConnectSocket, tx_addr, 4, WBCOM, &flag);
			if (state < 0 | iCnt > RETRY)
			{
				RxCheck_flag = FALSE;
				str.Format(_T("Fail Read Value - Colormap Table(Addr : 0x%x)"), dwAddr);
				goto END;
			}
			if ((((UINT32)flag & 0X0000ffff) == 0xd002) | iiCnt == RETRY)
			{
				iiCnt = 0;
				iCnt++;
				state = ReadISP(dwAddr);
			}
			iiCnt++;
		} while (((UINT32)flag & 0X0000ffff) != 0x2002);
		state = getDataFromRemote(ConnectSocket, tx_addr + (1 << 2), 4, WBCOM, &temp);
		
		if (state < 0)
		{
			str.Format(_T("Fail Read Value - Colormap Table(Addr : 0x%x)"), dwAddr);
			goto END;
		}

		// 저장
		m_pwRxData[iReadCnt] = ntohl((UINT32)temp);
		m_dwCommColormap[iReadCnt] = m_pwRxData[iReadCnt];

		iReadCnt++;
		Sleep(1);
	}
#else
	// Set ProgressCtrl
	m_Progress_Loading.ShowWindow(SW_SHOW);
	m_Progress_Loading.SetRange(0, COLORMAPSIZE);
	m_Progress_Loading.SetPos(0);
	while (iReadCnt < COLORMAPSIZE)
	{
		ProcessWindowMessage();
		RxCheck_flag = TRUE;
		dwAddr = m_iAddrMin + iReadCnt;
		state = getDataFromRemote(ConnectSocket, m_dwEN673BaseAdr + (dwAddr << 2), 4, WB0, &temp);
		if (state < 0)
		{
			RxCheck_flag = FALSE;
			str.Format(_T("Fail Read Value - Colormap Table(Addr : 0x%x)"), dwAddr);
			goto END;
		}

		// 저장
		m_pwRxData[iReadCnt] = ntohl((UINT32)temp);
		m_dwCommColormap[iReadCnt] = m_pwRxData[iReadCnt];

		iReadCnt++;
		m_Progress_Loading.SetPos(m_Progress_Loading.GetPos() + 1);
		//Sleep(1);
		Wait(1);
	}
#endif

	// ----------------------------------------------------------------------------------------------------
	// AWB Window
	// Horizontal
	/*
	EN673 : 0x80 HSP[27:16],HW[11:0]
	EN673 : 0x57 HSP[27:16],HW[11:0]
	*/
	dwAddr = 0x80;

#if JTAG_UART
	state = ReadISP(dwAddr);
	if (state < 0)
	{
		str.Format(_T("Fail Read Value - AWB Window Horizontal(Addr : 0x%x)"), dwAddr);
		goto END;
	}

	// Wait
	iCnt = 0;
	iiCnt = 0;
	do{
		Sleep(10);
		state = getDataFromRemote(ConnectSocket, tx_addr, 4, WBCOM, &flag);
		if (state < 0 | iCnt > RETRY)
		{
			RxCheck_flag = FALSE;
			str.Format(_T("Fail Read Value - AWB Window Horizontal(Addr : 0x%x)"), dwAddr);
			goto END;
		}
		if ((((UINT32)flag & 0X0000ffff) == 0xd002) | iiCnt == RETRY)
		{
			iiCnt = 0;
			iCnt++;
			state = ReadISP(dwAddr);
		}
		iiCnt++;
	} while (((UINT32)flag & 0X0000ffff) != 0x2002);
	state = getDataFromRemote(ConnectSocket, tx_addr + (1 << 2), 4, WBCOM, &temp);

	if (state < 0)
	{
		str.Format(_T("Fail Read Value - AWB Window Horizontal(Addr : 0x%x)"), dwAddr);
		goto END;
	}
#else
	state = getDataFromRemote(ConnectSocket, m_dwEN673BaseAdr + (dwAddr << 2), 4, WB0, &temp);
	if (state < 0)
	{
		RxCheck_flag = FALSE;
		str.Format(_T("Fail Read Value - AWB Window Horizontal(Addr : 0x%x)"), dwAddr);
		goto END;
	}
#endif

	// Data
	m_dwRxData = ntohl((UINT32)temp);
	dwData = m_dwRxData;

	uiAwbWinHsp = ValSft_R16(dwData)&(BitMask_12);
	uiAwbWinHw = ValSft_R00(dwData)&(BitMask_12);

	// Vertical
	/*
	EN673 : VSP[27:16],VW[11:0]
	EN771 : VSP[27:16],VW[11:0]
	*/
	dwAddr++;

#if JTAG_UART
	state = ReadISP(dwAddr);
	if (state < 0)
	{
		str.Format(_T("Fail Read Value - AWB Window Vertical(Addr : 0x%x)"), dwAddr);
		goto END;
	}

	// Wait
	iCnt = 0;
	iiCnt = 0;
	do{
		Sleep(10);
		state = getDataFromRemote(ConnectSocket, tx_addr, 4, WBCOM, &flag);
		if (state < 0 | iCnt > RETRY)
		{
			RxCheck_flag = FALSE;
			str.Format(_T("Fail Read Value - AWB Window Vertical(Addr : 0x%x)"), dwAddr);
			goto END;
		}
		if ((((UINT32)flag & 0X0000ffff) == 0xd002) | iiCnt == RETRY)
		{
			iiCnt = 0;
			iCnt++;
			state = ReadISP(dwAddr);
		}
		iiCnt++;
	} while (((UINT32)flag & 0X0000ffff) != 0x2002);
	state = getDataFromRemote(ConnectSocket, tx_addr + (1 << 2), 4, WBCOM, &temp);

	if (state < 0)
	{
		str.Format(_T("Fail Read Value - AWB Window Vertical(Addr : 0x%x)"), dwAddr);
		goto END;
	}
#else
	state = getDataFromRemote(ConnectSocket, m_dwEN673BaseAdr + (dwAddr << 2), 4, WB0, &temp);
	if (state < 0)
	{
		RxCheck_flag = FALSE;
		str.Format(_T("Fail Read Value - AWB Window Vertical(Addr : 0x%x)"), dwAddr);
		goto END;
	}
#endif

	// Data
	m_dwRxData = ntohl((UINT32)temp);
	dwData = m_dwRxData;

	uiAwbWinVsp = ValSft_R16(dwData)&(BitMask_12);
	uiAwbWinVw = ValSft_R00(dwData)&(BitMask_12);

	// Spot
	i = uiAwbWinHw / 22;
	uiAwbWinHspSpot = i * 10;
	uiAwbWinHwSpot = i * 3;
	i = uiAwbWinVw / 12;
	uiAwbWinVspSpot = i * 4;
	uiAwbWinVwSpot = i * 2;

	// Check
	/* 멤버변수 아이들은 Full 기준 */

	if ((0 == m_uiAwbWinHsp) &&			/* 극초기 초기화 */
		(0 == m_uiAwbWinHw) &&
		(0 == m_uiAwbWinVsp) &&
		(0 == m_uiAwbWinVw))
	{
		m_uiAwbWinHsp = uiAwbWinHsp;
		m_uiAwbWinHw = uiAwbWinHw;
		m_uiAwbWinVsp = uiAwbWinVsp;
		m_uiAwbWinVw = uiAwbWinVw;

		m_uiAwbWinHspSpot = uiAwbWinHspSpot;
		m_uiAwbWinHwSpot = uiAwbWinHwSpot;
		m_uiAwbWinVspSpot = uiAwbWinVspSpot;
		m_uiAwbWinVwSpot = uiAwbWinVwSpot;

		m_bAwbWinMode = TRUE;
	}
	else
	{
		if ((m_uiAwbWinHsp == uiAwbWinHsp) && /* 기존 Full이랑 같으면 Full */
			(m_uiAwbWinHw == uiAwbWinHw) &&
			(m_uiAwbWinVsp == uiAwbWinVsp) &&
			(m_uiAwbWinVw == uiAwbWinVw))
		{
			m_bAwbWinMode = TRUE;
		}
		else if ((m_uiAwbWinHspSpot == uiAwbWinHsp) && /* 기존 Spot이랑 같으면 Spot */
			(m_uiAwbWinHwSpot == uiAwbWinHw) &&
			(m_uiAwbWinVspSpot == uiAwbWinVsp) &&
			(m_uiAwbWinVwSpot == uiAwbWinVw))
		{
			m_bAwbWinMode = FALSE;
		}
		else
		{
			if (AfxMessageBox(_T("Do you want to initialize at the new value?"), MB_YESNO) == IDYES)
			{
				m_uiAwbWinHsp = uiAwbWinHsp;
				m_uiAwbWinHw = uiAwbWinHw;
				m_uiAwbWinVsp = uiAwbWinVsp;
				m_uiAwbWinVw = uiAwbWinVw;

				m_uiAwbWinHspSpot = uiAwbWinHspSpot;
				m_uiAwbWinHwSpot = uiAwbWinHwSpot;
				m_uiAwbWinVspSpot = uiAwbWinVspSpot;
				m_uiAwbWinVwSpot = uiAwbWinVwSpot;

				m_bAwbWinMode = TRUE;
			}
			else
			{
				m_bAwbWinMode = TRUE;
			}
		}
	}

	// ----------------------------------------------------------------------------------------------------
	// Bypass [29]
	dwAddr = 0x84;

#if JTAG_UART
	state = ReadISP(dwAddr);
	if (state < 0)
	{
		str.Format(_T("Fail Read Value - Bypass(Addr : 0x%x)"), dwAddr);
		goto END;
	}

	// Wait
	iCnt = 0;
	iiCnt = 0;
	do{
		Sleep(10);
		state = getDataFromRemote(ConnectSocket, tx_addr, 4, WBCOM, &flag);
		if (state < 0 | iCnt > RETRY)
		{
			RxCheck_flag = FALSE;
			str.Format(_T("Fail Read Value - Bypass(Addr : 0x%x)"), dwAddr);
			goto END;
		}
		if ((((UINT32)flag & 0X0000ffff) == 0xd002) | iiCnt == RETRY)
		{
			iiCnt = 0;
			iCnt++;
			state = ReadISP(dwAddr);
		}
		iiCnt++;
	} while (((UINT32)flag & 0X0000ffff) != 0x2002);
	state = getDataFromRemote(ConnectSocket, tx_addr + (1 << 2), 4, WBCOM, &temp);

	if (state < 0)
	{
		str.Format(_T("Fail Read Value - Bypass(Addr : 0x%x)"), dwAddr);
		goto END;
	}
#else
	state = getDataFromRemote(ConnectSocket, m_dwEN673BaseAdr + (dwAddr << 2), 4, WB0, &temp);
	if (state < 0)
	{
		RxCheck_flag = FALSE;
		str.Format(_T("Fail Read Value - Bypass(Addr : 0x%x)"), dwAddr);
		goto END;
	}
#endif

	// Data
	m_dwRxData = ntohl((UINT32)temp);
	dwData = m_dwRxData;

	m_bBypass = ValSft_R29(dwData)&(BitMask_01);

	// ----------------------------------------------------------------------------------------------------
	// Threshold
	// Y Clip [25:16], Y Slice[9:0]
	dwAddr = 0x86;

#if JTAG_UART
	state = ReadISP(dwAddr);
	if (state < 0)
	{
		str.Format(_T("Fail Read Value - Y Clip(Addr : 0x%x)"), dwAddr);
		goto END;
	}

	// Wait
	iCnt = 0;
	iiCnt = 0;
	do{
		Sleep(10);
		state = getDataFromRemote(ConnectSocket, tx_addr, 4, WBCOM, &flag);
		if (state < 0 | iCnt > RETRY)
		{
			RxCheck_flag = FALSE;
			str.Format(_T("Fail Read Value - Y Clip(Addr : 0x%x)"), dwAddr);
			goto END;
		}
		if ((((UINT32)flag & 0X0000ffff) == 0xd002) | iiCnt == RETRY)
		{
			iiCnt = 0;
			iCnt++;
			state = ReadISP(dwAddr);
		}
		iiCnt++;
		Sleep(1);
	} while (((UINT32)flag & 0X0000ffff) != 0x2002);
	state = getDataFromRemote(ConnectSocket, tx_addr + (1 << 2), 4, WBCOM, &temp);

	if (state < 0)
	{
		str.Format(_T("Fail Read Value - Y Clip(Addr : 0x%x)"), dwAddr);
		goto END;
	}
#else
	state = getDataFromRemote(ConnectSocket, m_dwEN673BaseAdr + (dwAddr << 2), 4, WB0, &temp);
	if (state < 0)
	{
		RxCheck_flag = FALSE;
		str.Format(_T("Fail Read Value - Y Clip(Addr : 0x%x)"), dwAddr);
		goto END;
	}
#endif

	// Data
	m_dwRxData = ntohl((UINT32)temp);
	dwData = m_dwRxData;

	m_uiYClip = ValSft_R16(dwData)&(BitMask_10);
	m_uiYSlice = ValSft_R00(dwData)&(BitMask_10);

	// ----------------------------------------------------------------------------------------------------
	// End
	bReturn = TRUE;

END:
	if (!bReturn)
		AfxMessageBox(str);

#if 1
	if (!RxCheck_flag)
	{
		NetClo(ConnectSocket);
		ConnectSocket = NULL;

		Wait(10);

		NetClo(StateSocket);
		StateSocket = NULL;
		m_Btn_Connect.SetIcon(IDI_DISCONNECT, NULL);
	}
#endif

	if (m_pwRxData != NULL)
		delete[] m_pwRxData;
	m_pwRxData = NULL;

	return bReturn;
}


void CColormapDlg::OnEnChangeEditColormapyclip()
{
	if (m_bSetYClip) return;

	int iYClip = 0;
	CString str = _T("");

	m_Edit_YClip.GetWindowText(str);
	iYClip = HexToDec(str);

	SetYClip(iYClip);
}


// ====================================================================================================
// CColormapDlg::SetYClip
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CColormapDlg::SetYClip(int iYClip)
{
	m_bSetYClip = TRUE;

	// ----------------------------------------------------------------------------------------------------
	CString str = _T("");

	// Check Value
	if (iYClip > COLORMAP_AWBTHRESHOLDMAX)
	{
		str.Format(_T("YClip Value is too big. (Max : %x)"), COLORMAP_AWBTHRESHOLDMAX);
		AfxMessageBox(str);
	}
	else
	{
		m_uiYClip = iYClip;
	}

	// 적용
	str.Format(_T("%x"), m_uiYClip);
	m_Edit_YClip.SetWindowTextW(str);

	DWORD dwLeng = m_Edit_YClip.GetWindowTextLength();
	m_Edit_YClip.SetSel(dwLeng, -1, TRUE);

	// ----------------------------------------------------------------------------------------------------
	m_bSetYClip = FALSE;
}


void CColormapDlg::OnEnChangeEditColormapyslice()
{
	if (m_bSetYSlice) return;

	int iYSlice = 0;
	CString str = _T("");

	m_Edit_YSlice.GetWindowTextW(str);
	iYSlice = HexToDec(str);

	SetYSlice(iYSlice);
}


// ====================================================================================================
// CColormapDlg::SetYSlice
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CColormapDlg::SetYSlice(int iYSlice)
{
	m_bSetYSlice = TRUE;

	// ----------------------------------------------------------------------------------------------------
	CString str = _T("");

	// Check Value
	if (iYSlice > COLORMAP_AWBTHRESHOLDMAX)
	{
		str.Format(_T("YSlice Value is too big. (Max : %x)"), COLORMAP_AWBTHRESHOLDMAX);
		AfxMessageBox(str);
	}
	else
	{
		m_uiYSlice = iYSlice;
	}

	// 적용
	str.Format(_T("%x"), m_uiYSlice);
	m_Edit_YSlice.SetWindowTextW(str);

	DWORD dwLength = m_Edit_YSlice.GetWindowTextLength();
	m_Edit_YSlice.SetSel(dwLength, -1, TRUE);

	// ----------------------------------------------------------------------------------------------------
	m_bSetYSlice = FALSE;
}


void CColormapDlg::OnBnClickedButtonColormapapply()
{
	if (!ConnectSocket) return;

	StartColormapApplyThread();
}

// ====================================================================================================
// CColormapDlg::StartColormapApplyThread()
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CColormapDlg::StartColormapApplyThread()
{
	// ----------------------------------------------------------------------------------------------------
	// Run Loading Thread
	AfxBeginThread(LoadingThreadColormap, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);

	// ----------------------------------------------------------------------------------------------------
	// Run Colormap Write Thread
	AfxBeginThread(ColormapApplyThread, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
}


// ====================================================================================================
// ColormapApplyThread
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
UINT ColormapApplyThread(LPVOID pParam)
{
	// ----------------------------------------------------------------------------------------------------
	// Colormap Flag On
	pColormapDlg->m_bColormapISP = TRUE;

	// ----------------------------------------------------------------------------------------------------
	pColormapDlg->ApplyColormap_EN673();
	
	// ----------------------------------------------------------------------------------------------------
	// Colormap Flag Off
	pColormapDlg->m_bColormapISP = FALSE;

	// ----------------------------------------------------------------------------------------------------
	// End Loading
	pColormapDlg->m_bLoading = FALSE;

	return 0L;
}

// ====================================================================================================
// CColormapDlg::ApplyColormap_EN673
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CColormapDlg::ApplyColormap_EN673()
{
	int i = 0;
	BOOL bReturn = FALSE;
	CString str = _T("");

	BYTE* temp = NULL;
	BYTE* flag = NULL;

	int state = -1;

	// ----------------------------------------------------------------------------------------------------
	// Write
	int iCnt = 0;
	int iiCnt = 0;
	DWORD dwAddr = 0;
	DWORD dwData = 0;

	// ----------------------------------------------------------------------------------------------------
	// Read
	dwAddr = 0x86;
	RxCheck_flag = TRUE;

	// ----------------------------------------------------------------------------------------------------
	// Y Clip, Y Slice
	// Data
	dwData = ValSft_L16(m_uiYClip) +
		ValSft_L00(m_uiYSlice);
#if JTAG_UART
	state = WriteISP(dwAddr, dwData);
	if (state < 0)
	{
		str.Format(_T("Fail Write Value - Y Clip(Addr : 0x%x)"), dwAddr);
		goto END;
	}

	// Wait
	do{
		Sleep(10);
		state = getDataFromRemote(ConnectSocket, tx_addr, 4, WBCOM, &flag);
		if (state < 0 | iCnt > RETRY)
		{
			RxCheck_flag = FALSE;
			str.Format(_T("Fail Write Value - Y Clip(Addr : 0x%x)"), dwAddr);
			goto END;
		}
		if ((((UINT32)flag & 0X0000ffff) == 0xd002) | iiCnt == RETRY)
		{
			iiCnt = 0;
			iCnt++;
			state = WriteISP(dwAddr, dwData);
		}
		iiCnt++;
	} while (((UINT32)flag & 0X0000ffff) != 0x2002);
#else
	dwData = ntohl(dwData);
	state = setDataFromRemote(ConnectSocket, m_dwEN673BaseAdr + (dwAddr << 2), 4, WB0, &dwData);
	if (state < 0)
	{
		str.Format(_T("Fail Write Value - Y Clip(Addr : 0x%x)"), dwAddr);
		goto END;
	}
#endif
	bReturn = TRUE;

END:
	if (!bReturn)
		AfxMessageBox(str);
}


void CColormapDlg::OnBnClickedButtonColormapwrite()
{
	if (!ConnectSocket) return;

	StartColormapWriteThread();
}


// ====================================================================================================
// CColormapDlg::StartColormapWriteThread
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CColormapDlg::StartColormapWriteThread()
{
	// ----------------------------------------------------------------------------------------------------
	// Run Loading Thread
	AfxBeginThread(LoadingThreadColormap, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);

	// ----------------------------------------------------------------------------------------------------
	// Run Colormap Write Thread
	AfxBeginThread(ColormapWriteThread, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
}

// ====================================================================================================
// ColormapWriteThread
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
UINT ColormapWriteThread(LPVOID pParam)
{
	// ----------------------------------------------------------------------------------------------------
	// Colormap Flag On
	pColormapDlg->m_bColormapISP = TRUE;

	// ----------------------------------------------------------------------------------------------------
	pColormapDlg->WriteColormap_EN673();

	// ----------------------------------------------------------------------------------------------------
	// Colormap Flag Off
	pColormapDlg->m_bColormapISP = FALSE;

	// ----------------------------------------------------------------------------------------------------
	// End Loading
	pColormapDlg->m_bLoading = FALSE;

	return 0L;
}

// ====================================================================================================
// CColormapDlg::WriteColormapTable_EN673
// ----------------------------------------------------------------------------------------------------
// EN673, EN771
// ====================================================================================================
void CColormapDlg::WriteColormap_EN673()
{
	int i = 0;
	int iCnt = 0;
	int iiCnt = 0;
	DWORD dwAddr = 0;
	DWORD dwData = 0;
	BOOL bReturn = FALSE;
	CString str = _T("");

	BYTE* temp = NULL;
	BYTE* flag = NULL;

	int state = -1;
	RxCheck_flag = TRUE;

	// ----------------------------------------------------------------------------------------------------
	// Write
	if (m_dwCommColormap != NULL)
		delete[] m_dwCommColormap;
	m_dwCommColormap = new DWORD[COLORMAPSIZE];
	for (i = 0; i < COLORMAPSIZE; i++)
		m_dwCommColormap[i] = 0;

	ConvertToRegTable(m_dwCommColormap, m_bColormap);

	// Colormap Table
	int iWriteCnt = 0;
	while (iWriteCnt < COLORMAPSIZE)
	{
		ProcessWindowMessage();
		iCnt = 0;

		dwAddr = m_iAddrMin + iWriteCnt;
		dwData = m_dwCommColormap[iWriteCnt];
#if JTAG_UART
		state = WriteISP(dwAddr, dwData);
		if (state < 0)
		{
			str.Format(_T("Fail Write Value. (Address : 0x%x)"), m_iAddrMin + iWriteCnt);
			goto END;
		}

		// Wait
		do{
			Sleep(10);
			state = getDataFromRemote(ConnectSocket, tx_addr, 4, WBCOM, &flag);
			if (state < 0 | iCnt > RETRY)
			{
				RxCheck_flag = FALSE;
				str.Format(_T("Fail Write Value. (Address : 0x%x)"), m_iAddrMin + iWriteCnt);
				goto END;
			}
			if ((((UINT32)flag & 0X0000ffff) == 0xd002) | iiCnt == RETRY)
			{
				iiCnt = 0;
				iCnt++;
				state = WriteISP(dwAddr, dwData);
			}
			iiCnt++;
		} while (((UINT32)flag & 0X0000ffff) != 0x2002);
#else
		dwData = ntohl(dwData);
		state = setDataFromRemote(ConnectSocket, m_dwEN673BaseAdr + (dwAddr << 2), 4, WB0, &dwData);
		if (state < 0)
		{
			str.Format(_T("Fail Write Value. (Address : 0x%x)"), m_iAddrMin + iWriteCnt);
			goto END;
		}
#endif
		iWriteCnt++;
		//Sleep(1);
		Wait(1);
	}

	bReturn = TRUE;

END:
	if (!bReturn)
		AfxMessageBox(str);

#if 0
	if (!RxCheck_flag)
	{
		ConnectSocket = NULL;
		m_Btn_Connect.SetIcon(IDI_DISCONNECT, NULL);
	}
#endif
	if (m_dwCommColormap != NULL)
		delete[] m_dwCommColormap;
	m_dwCommColormap = NULL;
}


void CColormapDlg::OnBnClickedButtonColormapreset()
{
	ResetColormapData();

	DrawColormap();
}


// ====================================================================================================
// CColormapDlg::SetColormapReset
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CColormapDlg::SetColormapReset()
{
	memcpy(m_bColormapReset, m_bColormap, sizeof(BOOL)*(COLORMAPSIZE*COLORMAPSIZE));
	m_uiAwbWinHspReset = m_uiAwbWinHsp;
	m_uiAwbWinHwReset = m_uiAwbWinHw;
	m_uiAwbWinVspReset = m_uiAwbWinVsp;
	m_uiAwbWinVwReset = m_uiAwbWinVw;
	m_bBypassReset = m_bBypass;
	m_uiYClipReset = m_uiYClip;
	m_uiYSliceReset = m_uiYSlice;
}

// ====================================================================================================
// CColormapDlg::ResetColormapData
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CColormapDlg::ResetColormapData()
{
	memcpy(m_bColormap, m_bColormapReset, sizeof(BOOL)*(COLORMAPSIZE*COLORMAPSIZE));
	m_uiAwbWinHsp = m_uiAwbWinHspReset;
	m_uiAwbWinHw = m_uiAwbWinHwReset;
	m_uiAwbWinVsp = m_uiAwbWinVspReset;
	m_uiAwbWinVw = m_uiAwbWinVwReset;
	m_bBypass = m_bBypassReset;
	m_uiYClip = m_uiYClipReset;
	m_uiYSlice = m_uiYSliceReset;

	//SetAwbWindowMode(TRUE);
	//SetBypass(m_bBypass);
	//SetYClip(m_uiYClip);
	//SetYSlice(m_uiYSlice);
}

void CColormapDlg::OnBnClickedButtonColormapsave()
{
	CString strTxtFile = _T("");
	CString strDefExt = _T("txt");
	CString strFilter = _T("Text Document(*txt)|*.txt||");

	// Save Dialog
	if (!ShowSaveFileDlg(&strTxtFile, strDefExt, strFilter, this))
		return;

	// Save
	SaveColormap(strTxtFile);

	AfxMessageBox(_T("Save Complete!"));
}


void CColormapDlg::SaveColormap(CString strPath)
{
	int i = 0;
	CString str = _T("");

	CStdioFile txtFile;
	txtFile.Open(strPath, CFile::modeCreate | CFile::modeWrite);

	str.Format(_T("YCLIP : 0x%x\n"), m_uiYClip);
	txtFile.WriteString(str);
	str.Format(_T("YSLICE : 0x%x\n"), m_uiYSlice);
	txtFile.WriteString(str);

	txtFile.WriteString(_T("\n"));

	int iColormapRegNum = 0;
	//int iPlatformSel = pECMDlg->GetPlatformSel();
	
	iColormapRegNum = COLORMAPSIZE;

	m_dwCommColormap = new DWORD[iColormapRegNum];
	for (i = 0; i < iColormapRegNum; i++)
		m_dwCommColormap[i] = 0;

	ConvertToRegTable(m_dwCommColormap, m_bColormap);

	for (i = 0; i < iColormapRegNum; i++)
	{
		if (i == iColormapRegNum - 1)	str.Format(_T("0x%08x"), m_dwCommColormap[i]);
		else						str.Format(_T("0x%08x,\n"), m_dwCommColormap[i]);
		txtFile.WriteString(str);
	}

	// Delete
	if (m_dwCommColormap != NULL)
		delete[] m_dwCommColormap;
	m_dwCommColormap = NULL;

	txtFile.Close();
}


void CColormapDlg::OnBnClickedRadioColormapspot()
{
	if (m_bSetAwbWin) return;

	SetAwbWindowMode(FALSE);

	if (ConnectSocket)
		StartAwbWindowWriteThread();
}


void CColormapDlg::OnBnClickedRadioColormapfull()
{
	if (m_bSetAwbWin) return;

	SetAwbWindowMode(TRUE);

	if (ConnectSocket)
		StartAwbWindowWriteThread();
}


// ====================================================================================================
// CColormapDlg::SetAwbWindowMode
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CColormapDlg::SetAwbWindowMode(BOOL bFlag)
{
	m_bSetAwbWin = TRUE;
	// ----------------------------------------------------------------------------------------------------
	m_bAwbWindow = bFlag;

	if (bFlag)
	{
		m_Radio_Full.SetCheck(TRUE);
		m_Radio_Spot.SetCheck(FALSE);
	}
	else
	{
		m_Radio_Spot.SetCheck(TRUE);
		m_Radio_Full.SetCheck(FALSE);
	}
	// ----------------------------------------------------------------------------------------------------
	m_bSetAwbWin = FALSE;
}


// ====================================================================================================
// CColormapDlg::StartAwbWindowWriteThread
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CColormapDlg::StartAwbWindowWriteThread()
{
	// ----------------------------------------------------------------------------------------------------
	// Run Loading Thread
	AfxBeginThread(LoadingThreadColormap, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);

	// ----------------------------------------------------------------------------------------------------
	// Run AwbWindonWriteThread
	AfxBeginThread(AwbWindowWriteThread, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
}

// ====================================================================================================
// AwbWindowWriteThread
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
UINT AwbWindowWriteThread(LPVOID pParam)
{
	// ----------------------------------------------------------------------------------------------------
	// Colormap Flag On
	pColormapDlg->m_bColormapISP = TRUE;

	// ----------------------------------------------------------------------------------------------------
	pColormapDlg->WriteAwbWindow_EN673();

	// ----------------------------------------------------------------------------------------------------
	// Colormap Flag Off
	pColormapDlg->m_bColormapISP = FALSE;

	// ----------------------------------------------------------------------------------------------------
	// End Loading
	pColormapDlg->m_bLoading = FALSE;

	return 0L;
}


// ====================================================================================================
// CColormapDlg::WriteAwbWindow_EN673
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CColormapDlg::WriteAwbWindow_EN673()
{
	int i = 0;
	int iCnt = 0;
	int iiCnt = 0;
	BOOL bReturn = FALSE;
	DWORD dwAddr = 0;
	DWORD dwData = 0;
	CString str = _T("");

	BYTE* temp = NULL;
	BYTE* flag = NULL;

	int state = -1;
	RxCheck_flag = TRUE;

	// Flag On
	m_bColormapISP = TRUE;

	// ----------------------------------------------------------------------------------------------------
	// Set Platform
	dwAddr = 0x80;

	// ----------------------------------------------------------------------------------------------------
	// AWB Window
	// Horizontal
	if (m_bAwbWindow)	dwData = ValSft_L16(m_uiAwbWinHsp) + m_uiAwbWinHw;		// Full
	else				dwData = ValSft_L16(m_uiAwbWinHspSpot) + m_uiAwbWinHwSpot;	// Spot

#if JTAG_UART
	state = WriteISP(dwAddr, dwData);
	if (state < 0)
	{
		str.Format(_T("Fail Write Value - Colormap Table(Addr : 0x%x)"), dwAddr);
		goto END;
	}

	// Wait
	do{
		Sleep(10);
		state = getDataFromRemote(ConnectSocket, tx_addr, 4, WBCOM, &flag);
		if (state < 0 | iCnt > RETRY)
		{
			RxCheck_flag = FALSE;
			str.Format(_T("Fail Write Value - Colormap Table(Addr : 0x%x)"), dwAddr);
			goto END;
		}
		if ((((UINT32)flag & 0X0000ffff) == 0xd002) | iiCnt == RETRY)
		{
			iiCnt = 0;
			iCnt++;
			state = WriteISP(dwAddr, dwData);
		}
		iiCnt++;
	} while (((UINT32)flag & 0X0000ffff) != 0x2002);
#else
	dwData = ntohl(dwData);
	state = setDataFromRemote(ConnectSocket, m_dwEN673BaseAdr + (dwAddr << 2), 4, WB0, &dwData);
	if (state < 0)
	{
		RxCheck_flag = FALSE;
		str.Format(_T("Fail Write Value - Colormap Table(Addr : 0x%x)"), dwAddr);
		goto END;
	}
#endif
	// ----------------------------------------------------------------------------------------------------
	// Vertical
	dwAddr++;

	if (m_bAwbWindow)	dwData = ValSft_L16(m_uiAwbWinVsp) + m_uiAwbWinVw;			// Full
	else				dwData = ValSft_L16(m_uiAwbWinVspSpot) + m_uiAwbWinVwSpot;	// Spot

#if JTAG_UART
	state = WriteISP(dwAddr, dwData);
	if (state < 0)
	{
		str.Format(_T("Fail Write Value - Colormap Table(Addr : 0x%x)"), dwAddr);
		goto END;
	}

	// Wait
	iCnt = 0;
	iiCnt = 0;
	do{
		Sleep(10);
		state = getDataFromRemote(ConnectSocket, tx_addr, 4, WBCOM, &flag);
		if (state < 0 | iCnt > RETRY)
		{
			RxCheck_flag = FALSE;
			str.Format(_T("Fail Write Value - Colormap Table(Addr : 0x%x)"), dwAddr);
			goto END;
		}
		if ((((UINT32)flag & 0X0000ffff) == 0xd002) | iiCnt == RETRY)
		{
			iiCnt = 0;
			iCnt++;
			state = WriteISP(dwAddr, dwData);
		}
		iiCnt++;
	} while (((UINT32)flag & 0X0000ffff) != 0x2002);
#else
	dwData = ntohl(dwData);
	state = setDataFromRemote(ConnectSocket, m_dwEN673BaseAdr + (dwAddr << 2), 4, WB0, &dwData);
	if (state < 0)
	{
		RxCheck_flag = FALSE;
		str.Format(_T("Fail Write Value - Colormap Table(Addr : 0x%x)"), dwAddr);
		goto END;
	}
#endif

	bReturn = TRUE;

END:
	if (!bReturn)
		AfxMessageBox(str);
}


void CColormapDlg::OnBnClickedCheckColormapbypass()
{
	// AWBLNOR_SEL

	if (m_bSetBypass) return;

	SetBypass(m_Check_Bypass.GetCheck());

	if (ConnectSocket)
		StartAwbBypassWriteThread();
}


// ====================================================================================================
// CColormapDlg::SetBypass
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CColormapDlg::SetBypass(BOOL bBypass)
{
	m_bSetBypass = TRUE;
	// ----------------------------------------------------------------------------------------------------
	m_bBypass = bBypass;
	m_Check_Bypass.SetCheck(m_bBypass);
	// ----------------------------------------------------------------------------------------------------
	m_bSetBypass = FALSE;
}

// ====================================================================================================
// CColormapDlg::StartAwbBypassWriteThread
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CColormapDlg::StartAwbBypassWriteThread()
{
	// ----------------------------------------------------------------------------------------------------
	// Run Loading Thread
	AfxBeginThread(LoadingThreadColormap, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);

	// ----------------------------------------------------------------------------------------------------
	// Run Awb Bypass Write Thread
	AfxBeginThread(AwbBypassWriteThread, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
}

// ====================================================================================================
// AwbBypassWriteThread
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
UINT AwbBypassWriteThread(LPVOID pParam)
{
	// ----------------------------------------------------------------------------------------------------
	// Colormap Flag On
	pColormapDlg->m_bColormapISP = TRUE;

	// ----------------------------------------------------------------------------------------------------
	pColormapDlg->WriteAwbBypass_EN673();

	// ----------------------------------------------------------------------------------------------------
	// Colormap Flag Off
	pColormapDlg->m_bColormapISP = FALSE;

	// ----------------------------------------------------------------------------------------------------
	// End Loading
	pColormapDlg->m_bLoading = FALSE;

	return 0L;
}

// ====================================================================================================
// CColormapDlg::WriteAwbBypass_EN673
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CColormapDlg::WriteAwbBypass_EN673()
{
	int iCnt = 0;
	int iiCnt = 0;
	BOOL bReturn = FALSE;
	DWORD dwAddr = 0;
	DWORD dwData = 0;
	CString str = _T("");

	BYTE* temp = NULL;
	BYTE* flag = NULL;

	int state = -1;
	RxCheck_flag = TRUE;

	// ----------------------------------------------------------------------------------------------------
	// Set Platform
	dwAddr = 0x84;

	// ----------------------------------------------------------------------------------------------------
	// Bypass
	// Read
	state = ReadISP(dwAddr);
	if (state < 0)
	{
		str.Format(_T("Fail Write Value - Bypass(Addr : 0x%x)"), dwAddr);
		goto END;
	}

	// Wait
	do{
		//Sleep(10);
		ProcessWindowMessage();
		Wait(10);
		state = getDataFromRemote(ConnectSocket, tx_addr, 4, WBCOM, &flag);;
		if (state < 0 | iCnt > RETRY)
		{
			str.Format(_T("Fail Write Value - Bypass(Addr : 0x%x)"), dwAddr);
			goto END;
		}
		if ((((UINT32)flag & 0X0000ffff) == 0xd002) | iiCnt == RETRY)
		{
			iiCnt = 0;
			iCnt++;
			state = ReadISP(dwAddr);
		}
		iiCnt++;
	} while (((UINT32)flag & 0X0000ffff) != 0x2002);
	state = getDataFromRemote(ConnectSocket, tx_addr + (1 << 2), 4, WBCOM, &temp);

	// Data
	m_dwRxData = ntohl((UINT32)temp);
	dwData = m_dwRxData;
	dwData |= ValSft_L29(BitMask_01);
	dwData ^= ValSft_L29(BitMask_01);
	dwData += ValSft_L29(m_bBypass);

	state = WriteISP(dwAddr, dwData);
	if (state < 0)
	{
		str.Format(_T("Fail Write Value - Bypass(Addr : 0x%x)"), dwAddr);
		goto END;
	}

	// Wait
	iCnt = 0;
	iiCnt = 0;
	do{
		//Sleep(10);
		ProcessWindowMessage();
		Wait(10);
		state = getDataFromRemote(ConnectSocket, tx_addr, 4, WBCOM, &flag);
		if (state < 0 | iCnt > RETRY)
		{
			RxCheck_flag = FALSE;
			str.Format(_T("Fail Write Value - Bypass(Addr : 0x%x)"), dwAddr);
			goto END;
		}
		if ((((UINT32)flag & 0X0000ffff) == 0xd002) | iiCnt == RETRY)
		{
			iiCnt = 0;
			iCnt++;
			state = WriteISP(dwAddr, dwData);
		}
		iiCnt++;
	} while (((UINT32)flag & 0X0000ffff) != 0x2002);

	bReturn = TRUE;

END:

	if (!bReturn)
		AfxMessageBox(str);
}


// ====================================================================================================
// CColormapDlg::ConvertToRegTable
// ----------------------------------------------------------------------------------------------------
/*
Write/Save를 위해 Draw Table을 Reg Table로 변환
*/
// ====================================================================================================
void CColormapDlg::ConvertToRegTable(DWORD *des, BOOL *src)
{
	int iStep = 0;

	int iHSP = 0;
	int iHEP = 0;
	int iCnt = 0;

	int iMaxHSP = 0;
	int iMaxHEP = 0;
	int iMaxCnt = 0;

	for (int i = 0; i < COLORMAPSIZE; i++)
	{
		iStep = 0;
		iHSP = 0;
		iHEP = 0;
		iCnt = 0;
		iMaxHSP = 0;
		iMaxHEP = 0;
		iMaxCnt = 0;

		for (int j = 0; j < COLORMAPSIZE; j++)
		{
			switch (iStep)
			{
			case 0:
				if (src[(i*COLORMAPSIZE) + j]) {
					iHSP = j; iHEP = j; iCnt++; iStep = 1;
					if (iMaxCnt <= iCnt) {
						iMaxHSP = iHSP; iMaxHEP = iHEP; iMaxCnt = iCnt;
					}
				}
				break;

			case 1:
				if (src[(i*COLORMAPSIZE) + j])
				{
					iHEP = j; iCnt++;
					if (iMaxCnt < iCnt) { iMaxHSP = iHSP; iMaxHEP = iHEP; iMaxCnt = iCnt; }
				}
				else
				{
					iStep = 0; iHSP = 0; iHEP = 0; iCnt = 0;
				}
				break;
			}
		}

		if (iMaxCnt == 0) {
			des[COLORMAPSIZE - i - 1] = 0x3f00;
		}
		else {
			iHSP = iMaxHSP; iHEP = iMaxHEP;
			des[COLORMAPSIZE - i - 1] = ((iHSP&BitMask_06) << 8) + (iHEP&BitMask_06);
		}
	}

}

// ====================================================================================================
// CColormapDlg::ConvertToDrawTable
// ----------------------------------------------------------------------------------------------------
/*
Read 후 Draw를 위해 Reg Table을 Draw Table로 변환
*/
// ====================================================================================================
void CColormapDlg::ConvertToDrawTable(BOOL *des, DWORD *src)
{
	if (m_dwCommColormap == NULL) return;

	int iHSP = 0;
	int iHEP = 0;

	for (int y = 0; y < COLORMAPSIZE; y++)
	{
		iHSP = ValSft_R08(src[y])&(BitMask_06);
		iHEP = ValSft_R00(src[y])&(BitMask_06);

		if ((iHSP == 0x3F00 || iHEP == 0x3F00) || // 둘중에 하나라도 값이 3F00 이거나
			(iHSP >= COLORMAPSIZE || iHEP >= COLORMAPSIZE) || // 둘중에 하나라도 COLORMAPSIZE를 넘었거나
			(iHSP > iHEP) // HSP가 더 크거나
			)
		{
			for (int x = 0; x < COLORMAPSIZE; x++)
				des[((COLORMAPSIZE - y - 1)*COLORMAPSIZE) + x] = 0;
		}
		else
		{
			for (int x = iHSP; x <= iHEP; x++)
			{
				des[((COLORMAPSIZE - y - 1)*COLORMAPSIZE) + x] = 1;
			}
		}
	}

	// Delete
	if (m_dwCommColormap != NULL)
		delete[] m_dwCommColormap;
	m_dwCommColormap = NULL;
}

#define COLORMAPWIDTHMAX	(2-1)	// Max = 2, DrawColormap이랑 SetColormapTable에서 쓰임
// ====================================================================================================
// CColormapDlg::DrawColormap
// ----------------------------------------------------------------------------------------------------
/*
가로세로 가이드라인은 8칸 간격
*/
// ====================================================================================================
void CColormapDlg::DrawColormap()
{
	int i = 0;
	int x = 0;
	int y = 0;

	// ----------------------------------------------------------------------------------------------------
	// Ready
	// DC
	CDC* pDC = m_Colormap.GetWindowDC();
	CDC dc;
	dc.CreateCompatibleDC(pDC);

	// Bitmap
	CBitmap bmpBuffer;
	bmpBuffer.CreateCompatibleBitmap(pDC, COLORMAPWIDTH, COLORMAPHEIGHT);
	CBitmap* pOldBitmap = (CBitmap*)dc.SelectObject(&bmpBuffer);

	// ----------------------------------------------------------------------------------------------------
	// Draw
	// BackGround Color
	dc.FillSolidRect(0, 0, COLORMAPWIDTH, COLORMAPHEIGHT, RGB(255, 255, 255));

	// Guide Line
	CPen penGuide;
	CPen* pOldPenGuide;
	penGuide.CreatePen(PS_SOLID, 1, RGB(200, 200, 200));
	pOldPenGuide = (CPen*)dc.SelectObject(&penGuide);

	for (i = 1; i < 8; i++)
	{
		// Width
		dc.MoveTo(0, i*(COLORMAPWIDTH / 8));
		dc.LineTo(COLORMAPWIDTH, i*(COLORMAPWIDTH / 8));

		// Height
		dc.MoveTo(i*(COLORMAPHEIGHT / 8), 0);
		dc.LineTo(i*(COLORMAPHEIGHT / 8), COLORMAPHEIGHT);
	}
	dc.SelectObject(pOldPenGuide);

	// Colormap
	//BOOL bOn = 0;
	BYTE byBit = 0;

	CPen penNothing;
	CPen* pOldPenColormap;
	penNothing.CreatePen(PS_SOLID, 0, RGB(170, 170, 170));

	CBrush brushColormap;
	CBrush* pOldBrushColormap;
	brushColormap.CreateSolidBrush(RGB(170, 170, 170));

	pOldPenColormap = (CPen*)dc.SelectObject(&penNothing);
	pOldBrushColormap = (CBrush*)dc.SelectObject(&brushColormap);

	for (y = 0; y < COLORMAPSIZE; y++)
	{
		for (x = 0; x < COLORMAPSIZE; x++)
		{
			if (m_bColormap[(y*COLORMAPSIZE) + x])
				dc.Rectangle(x*COLORMAPSPACE, y*COLORMAPSPACE, ((x + 1)*COLORMAPSPACE), ((y + 1)*COLORMAPSPACE));

		}
	}
	dc.SelectObject(pOldBrushColormap);

	// ----------------------------------------------------------------------------------------------------
	// Copy, Paint
	CDC dcColormap;
	dcColormap.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmapColormap = (CBitmap*)dcColormap.SelectObject(&m_bmpColormap);

	dcColormap.BitBlt(0, 0, COLORMAPWIDTH, COLORMAPHEIGHT, &dc, 0, 0, SRCCOPY);
	pDC->BitBlt(1, 1, COLORMAPWIDTH - 2, COLORMAPHEIGHT - 2, &dc, 1, 1, SRCCOPY);
	dcColormap.SelectObject(pOldBitmapColormap);

	// ----------------------------------------------------------------------------------------------------
	// Return Resource
	dc.SelectObject(pOldBitmap);
	m_Colormap.ReleaseDC(pDC);
}


// ====================================================================================================
// CColormapDlg::EnableCtrl
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CColormapDlg::EnableCtrl(BOOL bEnable)
{
	m_Colormap.EnableWindow(bEnable);

	// ISP Register
	if (bEnable)
	{
		if (!ConnectSocket)
		{
			m_Btn_Read.EnableWindow(FALSE);
			m_Radio_Spot.EnableWindow(FALSE);
			m_Radio_Full.EnableWindow(FALSE);
			m_Check_Bypass.EnableWindow(FALSE);
			m_Edit_YClip.EnableWindow(FALSE);
			m_Edit_YSlice.EnableWindow(FALSE);
			m_Btn_Apply.EnableWindow(FALSE);
			m_Btn_Write.EnableWindow(FALSE);
			m_Btn_Reset.EnableWindow(FALSE);
		}
		else
		{
			m_Btn_Read.EnableWindow(TRUE);
			m_Radio_Spot.EnableWindow(m_bAwbInitial);
			m_Radio_Full.EnableWindow(m_bAwbInitial);
			m_Check_Bypass.EnableWindow(m_bAwbInitial);
			m_Edit_YClip.EnableWindow(m_bAwbInitial);
			m_Edit_YSlice.EnableWindow(m_bAwbInitial);
			m_Btn_Apply.EnableWindow(m_bAwbInitial);
			m_Btn_Write.EnableWindow(TRUE);
			m_Btn_Reset.EnableWindow(TRUE);
		}
	}
	else {
		m_Btn_Read.EnableWindow(FALSE);
		m_Radio_Spot.EnableWindow(FALSE);
		m_Radio_Full.EnableWindow(FALSE);
		m_Check_Bypass.EnableWindow(FALSE);
		m_Edit_YClip.EnableWindow(FALSE);
		m_Edit_YSlice.EnableWindow(FALSE);
		m_Btn_Apply.EnableWindow(FALSE);
		m_Btn_Write.EnableWindow(FALSE);
		m_Btn_Reset.EnableWindow(FALSE);
	}
}


void CColormapDlg::OnBnClickedButtonConnect()
{
#if 0
	UINT32 read = 0;
	int state = -1;

	if (StateSocket)
	{
		state = sendMsg(StateSocket, "rem_check ");
		//state = getDataFromRemote(StateSocket, 0x06fff004, 4, WBCOM, &read);
	}
	if ((state < 0) || (StateSocket == NULL))
	{
		StateSocket = NetCon(ch_ip, ch_port);
		if (StateSocket <= 0)
		{
			StateSocket = NULL;
			ConnectSocket = NULL;
		}
		else
			ConnectSocket = NetCon(ch_ip, ch_port);
	}

	if (StateSocket && ConnectSocket)
	{
		EnableCtrl(TRUE);
		m_Btn_Connect.SetIcon(IDI_CONNECT, NULL);
	}
	else 
	{
		EnableCtrl(FALSE);
		m_Btn_Connect.SetIcon(IDI_DISCONNECT, NULL);
	}
#endif
}


void CColormapDlg::OnTimer(UINT_PTR nIDEvent)
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


void CColormapDlg::Check_Timer_On()
{
	m_CheckTimerID = SetTimer(ID_CHECK_TIMER, Check_Time, NULL);
}

void CColormapDlg::Check_Timer_Off()
{
	if (m_CheckTimerID)
	{
		if (this->GetSafeHwnd())
			KillTimer(m_CheckTimerID);
		m_CheckTimerID = 0;
	}
}

void CColormapDlg::Connect_Timer_On()
{
	m_ConnectTimerID = SetTimer(ID_CONNECT_TIMER, Connect_Time, NULL);
}

void CColormapDlg::Connect_Timer_Off()
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

	char server_state_flag;
	if (state != -1)
		state = recv(StateSocket, &server_state_flag, sizeof(server_state_flag), 0);
	else
		goto DISCONNECT;

	if ((state != -1))
	{
		if (server_state_flag == '0')
		{
			if (!Invalidate_flsg)
			{
				pColormapDlg->EnableCtrl(TRUE);
				pColormapDlg->m_Btn_Connect.SetIcon(IDI_CONNECT, NULL);

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
	pColormapDlg->EnableCtrl(FALSE);
	pColormapDlg->m_Btn_Connect.SetIcon(IDI_DISCONNECT, NULL);

	NetClo(ConnectSocket);
	ConnectSocket = NULL;

	Wait(1);

	NetClo(StateSocket);
	StateSocket = NULL;

	pColormapDlg->Check_Timer_Off();
	pColormapDlg->Connect_Timer_On();

	Invalidate_flsg = FALSE;

	return 0;
}


UINT Connect_Check_Thread(LPVOID pParam)
{
	ConnectSocket = NetCon(pColormapDlg->ch_ip, pColormapDlg->ch_port);
	//Sleep(1);
	Wait(1);
	StateSocket = NetCon(pColormapDlg->ch_ip, pColormapDlg->ch_port);

	if (ConnectSocket <= 0 || StateSocket <= 0)
	{
		NetClo(ConnectSocket);
		ConnectSocket = NULL;

		Wait(1);

		NetClo(StateSocket);
		StateSocket = NULL;
	}
	else
	{
		pColormapDlg->Connect_Timer_Off();
		pColormapDlg->Check_Timer_On();

		Invalidate_flsg = FALSE;
	}
	return 0;
}