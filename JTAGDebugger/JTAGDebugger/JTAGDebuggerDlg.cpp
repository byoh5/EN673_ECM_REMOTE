
// JTAGDebuggerDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "JTAGDebugger.h"
#include "JTAGDebuggerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

UINT	MemoryReadThread(LPVOID pParam);
UINT	MemoryWriteThread(LPVOID pParam);
UINT	RegisterReadThread(LPVOID pParam);
UINT	RegisterWriteThread(LPVOID pParam);
UINT	StallCPUThread(LPVOID pParam);
UINT	UnstallCPUThread(LPVOID pParam);
UINT	SinglestepRunThread(LPVOID pParam);
UINT	SinglestepContinueThread(LPVOID pParam);
UINT	DisplayCPURegisterThread(LPVOID pParam);

UINT32 jtag_stall_cpu(UINT8 cpu);
UINT32 jtag_unstall_cpu(UINT8 cpu);
UINT32 jtag_single_step(UINT8 cpu);
UINT32 jtag_continue(UINT8 cpu);
UINT32 jtag_read_cpu_status(UINT8 cpu, UINT8* buffer);
UINT32 jtag_wb_read32(UINT32 adr, UINT32 *data, UINT32 cpu);

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


// CJTAGDebuggerDlg 대화 상자



CJTAGDebuggerDlg::CJTAGDebuggerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CJTAGDebuggerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ECM);
}

void CJTAGDebuggerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_JTAGDEBUGGERCLOSE, m_Btn_Close);
	DDX_Control(pDX, IDC_BUTTON_MINIMIZE, m_Btn_Minimize);
	DDX_Control(pDX, IDC_EDIT_MEMORYRWADDR, m_Edit_MemoryAddr);
	DDX_Control(pDX, IDC_EDIT_MEMORYRWSIZE, m_Edit_MemorySize);
	DDX_Control(pDX, IDC_COMBO_MEMORYRWMODULE, m_Cbo_MemoryModule);
	DDX_Control(pDX, IDC_BUTTON_MEMORYRWREAD, m_Btn_MemoryRead);
	DDX_Control(pDX, IDC_BUTTON_MEMORYRWWRITE, m_Btn_MemoryWrite);
	DDX_Control(pDX, IDC_EDIT_REGISTERRWADDR, m_Edit_RegisterAddr);
	DDX_Control(pDX, IDC_EDIT_REGISTERRWSIZE, m_Edit_RegisterSize);
	DDX_Control(pDX, IDC_EDIT_REGISTERRWDATA, m_Edit_RegisterData);
	DDX_Control(pDX, IDC_COMBO_REGISTERRWMODULE, m_Cbo_RegisterModule);
	DDX_Control(pDX, IDC_BUTTON_REGISTERRWREAD, m_Btn_RegisterRead);
	DDX_Control(pDX, IDC_BUTTON_REGISTERRWWRITE, m_Btn_RegisterWrite);
	DDX_Control(pDX, IDC_RADIO_JTAGSELECTCPU_CPU0, m_Radio_CPU_Cpu0);
	DDX_Control(pDX, IDC_RADIO_JTAGSELECTCPU_CPU1, m_Radio_CPU_Cpu1);
	DDX_Control(pDX, IDC_BUTTON_JTAGSTALLCPU, m_Btn_StallCPU);
	DDX_Control(pDX, IDC_BUTTON_JTAGUNSTALLCPU, m_Btn_UnstallCPU);
	DDX_Control(pDX, IDC_EDIT_JTAGSINGLESTEPNUM, m_Edit_SinglestepNum);
	DDX_Control(pDX, IDC_BUTTON_JTAGSINGLESTEPRUN, m_Btn_SinglestepRun);
	DDX_Control(pDX, IDC_BUTTON_JTAGSINGLESTEPCONTINUE, m_Btn_Continue);
	DDX_Control(pDX, IDC_BUTTON_JTAGDCR, m_Btn_Dcr);
	DDX_Control(pDX, IDC_EDIT_JTAGLOG, m_Edit_JTAGLog);
	DDX_Control(pDX, IDC_BUTTON_CONNECT, m_Btn_Connect);
}

BEGIN_MESSAGE_MAP(CJTAGDebuggerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_JTAGDEBUGGERCLOSE, &CJTAGDebuggerDlg::OnBnClickedButtonJtagdebuggerclose)
	ON_BN_CLICKED(IDC_BUTTON_MINIMIZE, &CJTAGDebuggerDlg::OnBnClickedButtonMinimize)
	ON_BN_CLICKED(IDC_BUTTON_MEMORYRWREAD, &CJTAGDebuggerDlg::OnBnClickedButtonMemoryrwread)
	ON_BN_CLICKED(IDC_BUTTON_MEMORYRWWRITE, &CJTAGDebuggerDlg::OnBnClickedButtonMemoryrwwrite)
	ON_BN_CLICKED(IDC_BUTTON_REGISTERRWREAD, &CJTAGDebuggerDlg::OnBnClickedButtonRegisterrwread)
	ON_BN_CLICKED(IDC_BUTTON_REGISTERRWWRITE, &CJTAGDebuggerDlg::OnBnClickedButtonRegisterrwwrite)
	ON_BN_CLICKED(IDC_BUTTON_JTAGSTALLCPU, &CJTAGDebuggerDlg::OnBnClickedButtonJtagstallcpu)
	ON_BN_CLICKED(IDC_BUTTON_JTAGUNSTALLCPU, &CJTAGDebuggerDlg::OnBnClickedButtonJtagunstallcpu)
	ON_BN_CLICKED(IDC_BUTTON_JTAGSINGLESTEPRUN, &CJTAGDebuggerDlg::OnBnClickedButtonJtagsinglesteprun)
	ON_BN_CLICKED(IDC_BUTTON_JTAGSINGLESTEPCONTINUE, &CJTAGDebuggerDlg::OnBnClickedButtonJtagsinglestepcontinue)
	ON_BN_CLICKED(IDC_BUTTON_JTAGDCR, &CJTAGDebuggerDlg::OnBnClickedButtonJtagdcr)
	ON_BN_CLICKED(IDC_BUTTON_JTAGDEBUGGER_SAVELOG, &CJTAGDebuggerDlg::OnBnClickedButtonJtagdebuggerSavelog)
	ON_BN_CLICKED(IDC_BUTTON_JTAGDEBUGGER_CLEARLOG, &CJTAGDebuggerDlg::OnBnClickedButtonJtagdebuggerClearlog)
	ON_BN_CLICKED(IDC_RADIO_JTAGSELECTCPU_CPU0, &CJTAGDebuggerDlg::OnBnClickedRadioJtagselectcpuCpu0)
	ON_BN_CLICKED(IDC_RADIO_JTAGSELECTCPU_CPU1, &CJTAGDebuggerDlg::OnBnClickedRadioJtagselectcpuCpu1)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CJTAGDebuggerDlg::OnBnClickedButtonConnect)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CJTAGDebuggerDlg 메시지 처리기

BOOL CJTAGDebuggerDlg::OnInitDialog()
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
	SetWindowText(DLG_JTAGDEBUGGER);
// ----------------------------------------------------------------------------------------------------
// Server 연결
	CString strCmd = theApp.m_lpCmdLine;
	CString strAddr;
	CString strPort;

	AfxExtractSubString(strAddr, strCmd, 0, ' ');
	AfxExtractSubString(strPort, strCmd, 1, ' ');

#ifdef _DEBUG
	strAddr.Format(_T("127.0.0.1"));
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

	int x = ReadIni(SEC_WININFO, KEY_JTAGDEBUGGERDLGLEFT, DEF_JTAGDEBUGGERDLGLEFT);
	int y = ReadIni(SEC_WININFO, KEY_JTAGDEBUGGERDLGTOP, DEF_JTAGDEBUGGERDLGTOP);
	SetWindowPos(NULL, x, y, 520, 785, NULL);
	//this->SetWindowPos(NULL, 0, 0, 520, 600, NULL);

	// ----------------------------------------------------------------------------------------------------
	// Control
	// Close
	pJTAGDebuggerDlg = this;
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

	// Memory
	m_Cbo_MemoryModule.AddString(_T("wbcpu0"));
	m_Cbo_MemoryModule.AddString(_T("wbcpu1"));
	m_Cbo_MemoryModule.AddString(_T("wbcom"));
	m_Cbo_MemoryModule.SetCurSel(2);

	// Register
	m_Cbo_RegisterModule.AddString(_T("wbcpu0"));
	m_Cbo_RegisterModule.AddString(_T("wbcpu1"));
	m_Cbo_RegisterModule.AddString(_T("wbcom"));
	m_Cbo_RegisterModule.SetCurSel(2);

	// Select CPU
	m_Radio_CPU_Cpu0.SetCheck(TRUE);
	m_gcpu = 4;

	// Single Step
	m_Edit_SinglestepNum.SetWindowTextW(_T(""));

	// Log
	m_Edit_JTAGLog.SetLimitText(0xffffffff);

// Variable
	// Thread
	bRunMemoryReadThread = FALSE;
	bRunMemoryWriteThread = FALSE;
	bRunRegisterReadThread = FALSE;
	bRunRegisterWriteThread = FALSE;
	bRunStallCPUThread = FALSE;
	bRunUnstallCPUThread = FALSE;
	bRunSinglestepRunThread = FALSE;
	bRunSinglestepContinueThread = FALSE;
	bRunDisplayCPURegisterThread = FALSE;

	WDT_flag = FALSE;

	m_bStop = FALSE;

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CJTAGDebuggerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CJTAGDebuggerDlg::OnPaint()
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

		dc.TextOutW(10, 6, DLG_JTAGDEBUGGER);

		dc.SelectObject(pOldFont);
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CJTAGDebuggerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CJTAGDebuggerDlg::PreTranslateMessage(MSG* pMsg)
{
	// Default Window Message
	if (DefaultWindowMessage(pMsg))	return TRUE;
	else							return CDialogEx::PreTranslateMessage(pMsg);
}


void CJTAGDebuggerDlg::OnCancel()
{
	NetClo(ConnectSocket);
	ConnectSocket = NULL;

	NetClo(StateSocket);
	StateSocket = NULL;

	CDialogEx::OnCancel();
}


void CJTAGDebuggerDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetCapture();
	m_Point = point;

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CJTAGDebuggerDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (this == GetCapture())
	{
		CRect rcDialog;
		GetWindowRect(&rcDialog);

		int x = rcDialog.left + point.x - m_Point.x;
		int y = rcDialog.top + point.y - m_Point.y;

		SetWindowPos(NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		WriteIni(SEC_WININFO, KEY_JTAGDEBUGGERDLGLEFT, x);
		WriteIni(SEC_WININFO, KEY_JTAGDEBUGGERDLGTOP, y);
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void CJTAGDebuggerDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	ReleaseCapture();

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CJTAGDebuggerDlg::OnBnClickedButtonJtagdebuggerclose()
{
	CJTAGDebuggerDlg::OnCancel();
}

void CJTAGDebuggerDlg::OnBnClickedButtonMinimize()
{
	ShowWindow(SW_MINIMIZE);
}


void CJTAGDebuggerDlg::OnBnClickedButtonMemoryrwread()
{
	if (!ConnectSocket)	return;
	AfxBeginThread(MemoryReadThread, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
}


// ====================================================================================================
// CJTAGDebuggerDlg::MemoryReadThread
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
UINT MemoryReadThread(LPVOID pParam)
{
	bRunMemoryReadThread = TRUE;

	// ----------------------------------------------------------------------------------------------------
	// 컨트롤 비활성화
	pJTAGDebuggerDlg->EnableCtrl(FALSE);
	pJTAGDebuggerDlg->m_Btn_Close.EnableWindow(FALSE);

	// ----------------------------------------------------------------------------------------------------
	// Run
	pJTAGDebuggerDlg->MemoryRead();

	// ----------------------------------------------------------------------------------------------------
	// 컨트롤 활성화
	pJTAGDebuggerDlg->EnableCtrl(TRUE);
	pJTAGDebuggerDlg->m_Btn_Close.EnableWindow(TRUE);

	// ----------------------------------------------------------------------------------------------------
	bRunMemoryReadThread = FALSE;

	return 0;
}


// ====================================================================================================
// CJTAGDebuggerDlg::MemoryRead
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CJTAGDebuggerDlg::MemoryRead()
{
	BOOL bReturn = FALSE;
	CString str = _T("");
	CString strMsg = _T("");
	CFile pFile;
	UINT32 err = 0;
	UINT32 addr = 0;
	UINT32 size = 0;
	UINT32 size_adj = 0;
	UINT8* memblock = NULL;
	UINT8* memblock_t = NULL;

	// Save Path
	CString strTxtFile = _T("");
	CString strDefExt = _T("txt");
	CString strFilter = _T("Text Document(*txt)|*.txt||");

	if (!ShowSaveFileDlg(&strTxtFile, strDefExt, strFilter, this))
		return;

#if 0
	if (!IsFileWritable((const WCHAR *)strTxtFile))
		return;
#endif

	// Title
	AddOutBox(_T("\r\n"));
	AddOutBox(_T(" > Memory Read\r\n"));

	// Get Address
	m_Edit_MemoryAddr.GetWindowTextW(str);
	if (!CheckHex(str)) {
		strMsg.Format(_T("Address가 Hex Value가 아닙니다.")); // ★
		goto END;
	}
	addr = HexToDec(str);
	strMsg.Format(_T(" - Address : 0x%x\r\n"), addr);
	AddOutBox(strMsg);

	// Get Size
	m_Edit_MemorySize.GetWindowTextW(str);
	if (!CheckDec(str)) {
		strMsg.Format(_T("Size가 숫자가 아닙니다.")); // ★
		goto END;
	}
	size = _ttoi(str);
	size_adj = ((size + 4) >> 2) << 2;
	strMsg.Format(_T(" - Size : %dByte\r\n"), size);
	AddOutBox(strMsg);

	// Get Module
	UINT32 module = m_Cbo_MemoryModule.GetCurSel();
	switch (module)
	{
	case 0: // wbcpu0
		module = 0;
		break;
	case 1: // wbcpu1
		module = 1;
		break;
	case 2: // wbcom
		module = 3;
		break;
	}

#if 0
	// Initial JTAG
	strMsg.Format(_T("Init JTAG...... "));
	AddOutBox(strMsg);

	//if (!pJTAG->JTAGInitial(strMsg)) goto END;

	strMsg.Format(_T("End\r\n"));
	AddOutBox(strMsg);
#endif

	// Get Memory Data
	memblock = (UINT8*)malloc(size_adj + 4);
	memblock_t = (UINT8*)malloc(size_adj + 4);
	UINT32 retry = (size_adj) / (MR_READBUFFER);
	UINT32 left = (size_adj) % (MR_READBUFFER);

	int i = 0;
	for (i = 0; i < retry; i++) {
		//if (err |= pJTAG->read32(addr + (MR_READBUFFER * i), (UINT32*)(memblock + (MR_READBUFFER * i)), (MR_READBUFFER / 4), module)) {
		if (err |= getDataFromRemote(ConnectSocket, addr + (MR_READBUFFER * i), MR_READBUFFER, module, (UINT32*)(memblock + (MR_READBUFFER * i)))) {
			strMsg.Format(_T("Fail : Read (Error : 0x%08x)"), err);
			goto END;
		}
		ProcessWindowMessage();
	}
	if (left) {
		//if (err |= pJTAG->read32(addr + (MR_READBUFFER * i), (UINT32*)(memblock + (MR_READBUFFER * i)), (left / 4) + 1, module)) {
		if (err |= getDataFromRemote(ConnectSocket, addr + (MR_READBUFFER * i), left, module, (UINT32*)(memblock + (MR_READBUFFER * i)))) {
			strMsg.Format(_T("Fail : Read (Error : 0x%08x)"), err);
			goto END;
		}
	}

	UINT32* memblock32 = (UINT32*)memblock;
	UINT32* memblock32_t = (UINT32*)memblock_t;
	for (i = 0; i < (size_adj / 4) + 1; i++){
		*(memblock32_t + i) = (UINT32)*(memblock32 + i);
		ProcessWindowMessage();
	}
	memblock_t = (UINT8*)memblock32_t;

	// Save memory Data
	pFile.Open(strTxtFile, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
	pFile.Write(memblock_t, size);
	pFile.Close();

	strMsg.Format(_T(" - Path : %s\r\nSave Complete!\r\n"), strTxtFile);
	AddOutBox(strMsg);

	bReturn = TRUE;

	// End
END:
	if (bReturn) {
	}
	else {
		if (strMsg != _T("")) {
			AddOutBox(strMsg + _T("\r\n"));
			AfxMessageBox(strMsg);
			//pJTAG->JTAGClose();
		}
	}

	// Release
	if (memblock) free(memblock);
	if (memblock_t) free(memblock_t);
}


void CJTAGDebuggerDlg::OnBnClickedButtonMemoryrwwrite()
{
	if (!ConnectSocket)	return;
	AfxBeginThread(MemoryWriteThread, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
}


// ====================================================================================================
// MemoryWriteThread
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
UINT MemoryWriteThread(LPVOID pParam)
{
	bRunMemoryWriteThread = TRUE;

	// ----------------------------------------------------------------------------------------------------
	// 컨트롤 비활성화
	pJTAGDebuggerDlg->EnableCtrl(FALSE);
	pJTAGDebuggerDlg->m_Btn_Close.EnableWindow(FALSE);
	// ----------------------------------------------------------------------------------------------------
	// Run
	pJTAGDebuggerDlg->MemoryWrite();

	// ----------------------------------------------------------------------------------------------------
	// 컨트롤 활성화
	pJTAGDebuggerDlg->EnableCtrl(TRUE);
	pJTAGDebuggerDlg->m_Btn_Close.EnableWindow(TRUE);

	// ----------------------------------------------------------------------------------------------------
	bRunMemoryWriteThread = FALSE;

	return 0;
}

#define MW_MAX_RETRY_NUM 100
#define MEM_WRITE_BUFFER_SIZE 1024*8
// ====================================================================================================
// CJTAGDebuggerDlg::MemoryWrite
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CJTAGDebuggerDlg::MemoryWrite()
{
	UINT i = 0;
	UINT32 err = 0;
	BOOL bReturn = FALSE;
	CFile pFile;
	CString str = _T("");
	CString strMsg = _T("");
	char * veribuf = NULL;
	char * memblock = NULL;
	char * Nmemblock = NULL;
	UINT32* memblock32 = NULL;
	UINT32* Nmemblock32 = NULL;

	// Open Path
	CString strTxtFile = _T("");
	CString strDefExt = _T("txt");
	CString strFilter = _T("Text File(*.txt)|*.txt||"); // 확장자 상관없이 가져올 수 있도록 함

	if (!ShowOpenFileDlg(&strTxtFile, strDefExt, strFilter, this))
		return;

	pFile.Open(strTxtFile, CFile::modeRead);

	// Title
	AddOutBox(_T("\r\n"));
	AddOutBox(_T(" > Memory Write\r\n"));

	// Get Address
	UINT32 addr = 0;
	m_Edit_MemoryAddr.GetWindowTextW(str);
	if (!CheckHex(str)) {
		strMsg.Format(_T("Address가 Hex Value가 아닙니다.")); // ★
		goto END;
	}
	addr = HexToDec(str);
	str.Format(_T(" - Address : 0x%x\r\n"), addr);
	AddOutBox(str);

	// Get Size
	UINT32 size = pFile.GetLength();
	UINT32 size_adj = ((size + 4) >> 2) << 2;
	strMsg.Format(_T(" - Size : %dByte\r\n"), size);
	AddOutBox(strMsg);

#if 0
	// Initial JTAG
	strMsg.Format(_T("Init JTAG...... "));
	AddOutBox(strMsg);

	//if (!pJTAG->JTAGInitial(strMsg)) goto END;

	strMsg.Format(_T("End\r\n"));
	AddOutBox(strMsg);
#endif

	// Stall CPU
	sendMsg(ConnectSocket, "rem_st ");
	/*
	UINT8 stalled = 0;
	for (UINT8 ncpu = 4; ncpu < 6; ncpu++){
		try {
			if (err = jtag_stall_cpu(ncpu)) throw err;
			if (err = pJTAG->checkstalledcpu(ncpu, &stalled)) throw err;
			if (!stalled) throw 0xffffffff;
		}
		catch (UINT32 err) {
			strMsg.Format(_T("Fail : unstalled. (Error : 0x%08x)"), err);
			goto END;
		}
	}
	*/

#if !CHANGE_EN674
	// Watchdog
	if (err |= reset_sys_wdt()) {    // Add for Reset Watchdog!!!! Flash write will fail when watchdog enabled!
		strMsg.Format(_T("Watchdog enable fail! (Error : 0x%08x)"), err);
		goto END;
	}
	// Protect Disable All
	if (err |= Sfls_writeProtect_Disable_all()) {
		strMsg.Format(_T("Protect disable fail! (Error : 0x%08x)"), err);
		goto END;
	}
#endif

	// Read File
	memblock = new char[size_adj];
	Nmemblock = new char[size_adj];

	pFile.Read(memblock, size);
	pFile.Close();

	memblock32 = (UINT32*)memblock;
	Nmemblock32 = (UINT32*)Nmemblock;
	for (i = 0; i < (size_adj / 4) + 1; i++){
		*(Nmemblock32 + i) = (UINT32)*(memblock32 + i);
	}

	// Write
	UINT32 remaining_len;
	UINT32 pos = 0;

	for (remaining_len = size_adj; remaining_len >= MEM_WRITE_BUFFER_SIZE; remaining_len -= MEM_WRITE_BUFFER_SIZE){
		//if (err |= pJTAG->write32(addr + pos, (UINT32*)(Nmemblock + pos), MEM_WRITE_BUFFER_SIZE / 4, JTAG_COMMON_MODULE_IDX)) {
		if (err |= setDataFromRemote(ConnectSocket, addr + pos, MEM_WRITE_BUFFER_SIZE, JTAG_COMMON_MODULE_IDX, (UINT32*)(Nmemblock + pos))) {
			strMsg.Format(_T("Fail : Read (Error : 0x%08x)"), err);
			goto END;
		}
		ProcessWindowMessage();
		pos += MEM_WRITE_BUFFER_SIZE;
	}

	if (remaining_len){
		//pJTAG->write32(addr + pos, (UINT32*)(Nmemblock + pos), (remaining_len / 4) + 1, JTAG_COMMON_MODULE_IDX);
		setDataFromRemote(ConnectSocket, addr + pos, remaining_len, JTAG_COMMON_MODULE_IDX, (UINT32*)(Nmemblock + pos));
		ProcessWindowMessage();
	}

	// Verify
#ifdef DATA_VERIFY // for Verify
	// Verify
	// Compare 4kbytes 
	// If different write again
	UINT32 remainlen = 0;
	char retry = 0;
	veribuf = new char[MEM_WRITE_BUFFER_SIZE];
	i = 0;
	for (remainlen = (UINT32)size; remainlen > MEM_WRITE_BUFFER_SIZE; remainlen -= (UINT32)(MEM_WRITE_BUFFER_SIZE)){
		retry = 0;
		//pJTAG->read32(addr + i, (UINT32*)veribuf, MEM_WRITE_BUFFER_SIZE / 4, JTAG_COMMON_MODULE_IDX);
		getDataFromRemote(ConnectSocket, addr + i, MEM_WRITE_BUFFER_SIZE, JTAG_COMMON_MODULE_IDX, (UINT32*)veribuf);
		printf("v");
		while (memcmp(veribuf, Nmemblock + i, MEM_WRITE_BUFFER_SIZE)){
			ProcessWindowMessage();
			// Erase 4K 
			//pJTAG->write32(addr + i, (UINT32*)(Nmemblock + i), MEM_WRITE_BUFFER_SIZE / 4, JTAG_COMMON_MODULE_IDX);
			setDataFromRemote(ConnectSocket, addr + i, MEM_WRITE_BUFFER_SIZE, JTAG_COMMON_MODULE_IDX, (UINT32*)(Nmemblock + i));
			retry++;
			if (retry>MW_MAX_RETRY_NUM){
				printf("Over Max Retry for write!");
				break;
			}
			//pJTAG->read32(addr + i, (UINT32*)veribuf, MEM_WRITE_BUFFER_SIZE / 4, JTAG_COMMON_MODULE_IDX);
			getDataFromRemote(ConnectSocket, addr + i, MEM_WRITE_BUFFER_SIZE, JTAG_COMMON_MODULE_IDX, (UINT32*)veribuf);
		}
		ProcessWindowMessage();
		i += MEM_WRITE_BUFFER_SIZE;
	}

	if (remainlen){
		retry = 0;
		//pJTAG->read32(addr + i, (UINT32*)veribuf, (remainlen / 4), JTAG_COMMON_MODULE_IDX);
		getDataFromRemote(ConnectSocket, addr + i, remainlen, JTAG_COMMON_MODULE_IDX, (UINT32*)veribuf);
		while (memcmp(veribuf, Nmemblock + i, remainlen)){
			ProcessWindowMessage();
			//pJTAG->write32(addr + i, (UINT32*)(Nmemblock + i), MEM_WRITE_BUFFER_SIZE / 4, JTAG_COMMON_MODULE_IDX);
			setDataFromRemote(ConnectSocket, addr + i, MEM_WRITE_BUFFER_SIZE, JTAG_COMMON_MODULE_IDX, (UINT32*)(Nmemblock + i));
			retry++;
			if (retry>MW_MAX_RETRY_NUM){
				printf("Over Max Retry for write flash!");
				break;
			}
			//pJTAG->read32(addr + i, (UINT32*)veribuf, (remainlen / 4), JTAG_COMMON_MODULE_IDX);
			getDataFromRemote(ConnectSocket, addr + i, remainlen, JTAG_COMMON_MODULE_IDX, (UINT32*)veribuf);
		}
	}

#endif

	strMsg.Format(_T("Write Complete!\r\n"), strTxtFile);
	AddOutBox(strMsg);

	bReturn = TRUE;

END:
	sendMsg(ConnectSocket, "rem_ust ");
	/*
	// Unstall CPU
	for (i = 4; i <= 5; i++) {
		jtag_unstall_cpu(i);
	}
	*/

	// Error message
	if (bReturn) {
	}
	else {
		if (strMsg != _T("")) {
			AddOutBox(strMsg + _T("\r\n"));
			AfxMessageBox(strMsg);
			//pJTAG->JTAGClose();
		}
	}

	// Release
	if (veribuf != NULL) delete[] veribuf;
	if (memblock != NULL) delete[] memblock;
	if (Nmemblock != NULL) delete[] Nmemblock;
}

void CJTAGDebuggerDlg::OnBnClickedButtonRegisterrwread()
{
	if (!ConnectSocket)	return;
	AfxBeginThread(RegisterReadThread, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
}


// ====================================================================================================
// RegisterReadThread
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
UINT RegisterReadThread(LPVOID pParam)
{
	bRunRegisterReadThread = TRUE;

	// ----------------------------------------------------------------------------------------------------
	// 컨트롤 비활성화
	pJTAGDebuggerDlg->EnableCtrl(FALSE);
	pJTAGDebuggerDlg->m_Btn_Close.EnableWindow(FALSE);
	// ----------------------------------------------------------------------------------------------------
	// Run
	pJTAGDebuggerDlg->RegisterRead();

	// ----------------------------------------------------------------------------------------------------
	// 컨트롤 활성화
	pJTAGDebuggerDlg->EnableCtrl(TRUE);
	pJTAGDebuggerDlg->m_Btn_Close.EnableWindow(TRUE);

	// ----------------------------------------------------------------------------------------------------
	bRunRegisterReadThread = FALSE;

	return 0;
}

// ====================================================================================================
// CJTAGDebuggerDlg::RegisterRead
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CJTAGDebuggerDlg::RegisterRead()
{
	BOOL bReturn = FALSE;
	CString str = _T("");
	CString strMsg = _T("");
	CString temp_strMsg = _T("");
	UINT32 err = 0;
	char* memblock = NULL;
	UINT8 stalled = 0;
	int state = -1;

	// Title
	AddOutBox(_T("\r\n"));
	AddOutBox(_T(" > Register Read\r\n"));

	// Get Address
	UINT32 addr = 0;
	m_Edit_RegisterAddr.GetWindowTextW(str);
	if (!CheckHex(str)) {
		strMsg.Format(_T("Address가 Hex Value가 아닙니다.")); // ★
		goto END;
	}
	addr = HexToDec(str);
	str.Format(_T(" - Address : 0x%x\r\n"), addr);
	AddOutBox(str);

	// Get Size
	UINT32 size = 0;
	UINT32 size_adj = 0;
	m_Edit_RegisterSize.GetWindowTextW(str);
	if (!CheckDec(str)) {
		strMsg.Format(_T("Size가 숫자가 아닙니다.")); // ★
		goto END;
	}
	size = _ttoi(str);
	size_adj = ((size + 4) >> 2) << 2;
	str.Format(_T(" - Size : %dByte\r\n"), size);
	AddOutBox(str);

	// Get Module
	UINT32 module = m_Cbo_RegisterModule.GetCurSel();
	switch (module)
	{
	case 0: // wbcpu0
		module = 0;
		break;
	case 1: // wbcpu1
		module = 1;
		break;
	case 2: // wbcom
		module = 3;
		break;
	}

#if 0
	// Initial JTAG
	strMsg.Format(_T("Init JTAG...... "));
	AddOutBox(strMsg);

	//if (!pJTAG->JTAGInitial(strMsg)) goto END;

	strMsg.Format(_T("End\r\n"));
	AddOutBox(strMsg);
#endif

	// Get Register Data
#define MAX_TXT_BUFFER	(1024*1024)
	int i = 0;
	int j = 0;
	UINT32 reg = 0;
	memblock = (char*)malloc(MAX_TXT_BUFFER);
	addr = ((addr >> 2) << 2);			// 4의 배수 단위로 Addr 맞춤 

	for (i = 0; i < size; i++){
		//reg = example_read_register(module, addr + (i * 4));
		state = getDataFromRemote(ConnectSocket, addr + (i * 4), 4, module, &reg);
		
		if (state < 0)
			goto END;

		strMsg.Format(_T("0x%.8x :   reg = %.8x \r\n"), addr + (i * 4), htonl(reg));
		AddOutBox(strMsg);
		ProcessWindowMessage();
		Wait(10);
	}

	strMsg.Format(_T(" - Read Complete!\r\n"));
	AddOutBox(strMsg);

	bReturn = TRUE;

	// End
END:
	if (bReturn) {
	}
	else {
		if (strMsg != _T("")) {
			AddOutBox(strMsg + _T("\r\n"));
			AfxMessageBox(strMsg);
			//pJTAG->JTAGClose();
		}
	}

	// Release
	if (memblock) free(memblock);
}


void CJTAGDebuggerDlg::OnBnClickedButtonRegisterrwwrite()
{
	if (!ConnectSocket)	return;
	AfxBeginThread(RegisterWriteThread, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
}


// ====================================================================================================
// RegisterWriteThread
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
UINT RegisterWriteThread(LPVOID pParam)
{
	bRunRegisterWriteThread = TRUE;

	// ----------------------------------------------------------------------------------------------------
	// 컨트롤 비활성화
	pJTAGDebuggerDlg->EnableCtrl(FALSE);
	pJTAGDebuggerDlg->m_Btn_Close.EnableWindow(FALSE);
	// ----------------------------------------------------------------------------------------------------
	// Run
	pJTAGDebuggerDlg->RegisterWrite();

	// ----------------------------------------------------------------------------------------------------
	// 컨트롤 활성화
	pJTAGDebuggerDlg->EnableCtrl(TRUE);
	pJTAGDebuggerDlg->m_Btn_Close.EnableWindow(TRUE);

	// ----------------------------------------------------------------------------------------------------
	bRunRegisterWriteThread = FALSE;

	return 0;
}

// ====================================================================================================
// CJTAGDebuggerDlg::RegisterWrite
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CJTAGDebuggerDlg::RegisterWrite()
{
	BOOL bReturn = FALSE;
	CString str = _T("");
	CString strMsg = _T("");
	UINT32 err = 0;
	CFile pFile;

	// Title
	AddOutBox(_T("\r\n"));
	AddOutBox(_T(" > Register Write\r\n"));

	// Get Address
	UINT32 addr = 0;
	m_Edit_RegisterAddr.GetWindowTextW(str);
	if (!CheckHex(str)) {
		strMsg.Format(_T("Address가 Hex Value가 아닙니다.")); // ★
		goto END;
	}
	addr = HexToDec(str);
	strMsg.Format(_T(" - Address : 0x%x\r\n"), addr);
	AddOutBox(strMsg);

	// Get Size
	m_Edit_RegisterSize.GetWindowTextW(str);
	if (!CheckDec(str)) {
		strMsg.Format(_T("Size가 Value가 아닙니다.")); // ★
		goto END;
	}
	UINT32 size = _ttoi(str);
	UINT32 size_adj = ((size + 4) >> 2) << 2;
	strMsg.Format(_T(" - Size : %d\r\n"), size);
	AddOutBox(strMsg);

	// Get Data
	UINT32 data = 0;
	m_Edit_RegisterData.GetWindowTextW(str);
	if (!CheckHex(str)) {
		strMsg.Format(_T("Data가 Hex Value가 아닙니다.")); // ★
		goto END;
	}
	data = HexToDec(str);
	strMsg.Format(_T(" - Data : 0x%x\r\n"), data);
	AddOutBox(strMsg);

	// Get Module
	UINT32 module = m_Cbo_RegisterModule.GetCurSel();
	switch (module)
	{
	case 0: // wbcpu0
		module = 0;
		break;
	case 1: // wbcpu1
		module = 1;
		break;
	case 2: // wbcom
		module = 3;
		break;
	}

#if 0
	// Initial JTAG
	strMsg.Format(_T("Init JTAG...... "));
	AddOutBox(strMsg);

	//if (!pJTAG->JTAGInitial(strMsg)) goto END;

	strMsg.Format(_T("End\r\n"));
	AddOutBox(strMsg);
#endif

	// Get Register Data
#if CHANGE_EN674
#define FLASH_BASE 0x2F000000 // EN674
#else
#if INSERT_EN674
#define FLASH_BASE_EN673 0x06000000 // EN673
#define FLASH_BASE_EN674 0x2F000000 // EN674
#else
#define FLASH_BASE 0x06000000 // EN673
#endif
#endif

#if INSERT_EN674
	UINT32 iPlatformSel = pECMDlg->GetPlatformSel();
	UINT32 FLASH_BASE = 0;
	if (iPlatformSel == EN673) FLASH_BASE = FLASH_BASE_EN673;
	else if (iPlatformSel == EN674) FLASH_BASE = FLASH_BASE_EN674;
#endif
	data = htonl(data);
	UINT32 reg = 0;
	for (int i = 0; i < size; i++){
		ProcessWindowMessage();
		if ((addr >> 24) == 0x06){
			strMsg.Format(_T("Flash Write\r\n"), i, reg);
			AddOutBox(strMsg);
			if (err = Sfls_init_quad())											{ strMsg.Format(_T("Fail Write (Error : 0x%08x)"), err); goto END; }
			if (err = Sfls_point_write32(data, (addr - FLASH_BASE) + (i * 4)))	{ strMsg.Format(_T("Fail Write (Error : 0x%08x)"), err); goto END; }
			//Sleep(20);
			Wait(20);
		}
		else {
			//if (err = jtag_write32(addr + (i * 4), data, module))				{ strMsg.Format(_T("Fail Write (Error : 0x%08x)"), err); goto END; }
			err = setDataFromRemote(ConnectSocket, addr + (i * 4), 4, module, &data);
			if (err)															{ strMsg.Format(_T("Fail Write (Error : 0x%08x)"), err); goto END; }
		}

		
		//if (err = jtag_read32(addr + (i * 4), &reg, module)) { strMsg.Format(_T("Fail Read (Error : 0x%08x)"), err); goto END; }
		if (err = getDataFromRemote(ConnectSocket, addr + (i * 4), 4, module, &reg)) { strMsg.Format(_T("Fail Read (Error : 0x%08x)"), err); goto END; }
		strMsg.Format(_T("[%03d] read: 0x%x\r\n"), i, htonl(reg));
		AddOutBox(strMsg);

		if (data != reg) {
			strMsg.Format(_T("[%d] write fail\r\n"), i);
			AddOutBox(strMsg);
		}
	}

	strMsg.Format(_T(" - Write Complete!\r\n"));
	AddOutBox(strMsg);

	bReturn = TRUE;

	// End
END:
	//tap_reset_global();

	if (bReturn) {
	}
	else {
		if (strMsg != _T("")) {
			AddOutBox(strMsg + _T("\r\n"));
			AfxMessageBox(strMsg);
			//pJTAG->JTAGClose();
		}
	}

	// Release
}


void CJTAGDebuggerDlg::OnBnClickedRadioJtagselectcpuCpu0()
{
	m_gcpu = 4;
}


void CJTAGDebuggerDlg::OnBnClickedRadioJtagselectcpuCpu1()
{
	m_gcpu = 5;
}


void CJTAGDebuggerDlg::OnBnClickedButtonJtagstallcpu()
{
	if (!ConnectSocket)	return;
	AfxBeginThread(StallCPUThread, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
}


// ====================================================================================================
// StallCPUThread
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
UINT StallCPUThread(LPVOID pParam)
{
	bRunStallCPUThread = TRUE;

	// ----------------------------------------------------------------------------------------------------
	// 컨트롤 비활성화
	pJTAGDebuggerDlg->EnableCtrl(FALSE);
	pJTAGDebuggerDlg->m_Btn_Close.EnableWindow(FALSE);
	// ----------------------------------------------------------------------------------------------------
	// Run
	pJTAGDebuggerDlg->StallCPU();

	// ----------------------------------------------------------------------------------------------------
	// 컨트롤 활성화
	pJTAGDebuggerDlg->EnableCtrl(TRUE);
	pJTAGDebuggerDlg->m_Btn_Close.EnableWindow(TRUE);

	// ----------------------------------------------------------------------------------------------------
	bRunStallCPUThread = FALSE;

	return 0;
}

// ====================================================================================================
// CJTAGDebuggerDlg::StallCPU
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CJTAGDebuggerDlg::StallCPU()
{
	CString strMsg = _T("");
	UINT32 err = 0;
	BOOL bReturn = FALSE;
	int state = -1;

	// Title
	AddOutBox(_T("\r\n"));
	AddOutBox(_T(" > Stall CPU\r\n"));

#if 0
	// Init JTAG
	strMsg.Format(_T("Init JTAG...... "));
	AddOutBox(strMsg);

	//if (!pJTAG->JTAGInitial(strMsg)) goto END;

	strMsg.Format(_T("End\r\n"));
	AddOutBox(strMsg);
#endif

	// Stall
	UINT8 stalled = 0;
	UINT8 cpu = 0;

	if (m_Radio_CPU_Cpu0.GetCheck())	cpu = 4;
	else								cpu = 5;

	/*
	if (err = jtag_stall_cpu(cpu))						{ strMsg.Format(_T("Fail Stalled!")); goto END; }
	if (err = pJTAG->checkstalledcpu(cpu, &stalled))	{ strMsg.Format(_T("Fail Stalled!")); goto END; }
	if (!stalled)										{ strMsg.Format(_T("Fail Stalled!")); goto END; }
	*/

	//sendMsg(ConnectSocket, "rem_st ");
	if (cpu == 4)	state = sendMsg(ConnectSocket, "rem_st cpu0 ");
	if (cpu == 5)	state = sendMsg(ConnectSocket, "rem_st cpu1 ");

	if (state < 0)
	{
		strMsg.Format(_T("Stall Fail"));
		goto END;
	}

#if STALL
	// Stall check 부분 필요
	// jtag_check_stalled_cpu 필요
	if (cpu == 4)	state = sendMsg(ConnectSocket, "rem_cst cpu0 ");
	if (cpu == 5)	state = sendMsg(ConnectSocket, "rem_cst cpu1 ");
	if (state < 0)
	{
		strMsg.Format(_T("UnStall Fail"));
		goto END;
	}

	char stall_flag;
	state = recv(ConnectSocket, &stall_flag, sizeof(stall_flag), 0);
	if (stall_flag == '0')
	{
		strMsg.Format(_T("Stall Fail"));
		goto END;
	}
#endif

#if WDT
	// WDT off
	UINT32 data = 0;
	state = getDataFromRemote(ConnectSocket, 0xf9500028, 4, JTAG_COMMON_MODULE_IDX, &data);
	if (htonl(data) == 1)
	{
		WDT_flag = TRUE;
		data = 0;
		state = setDataFromRemote(ConnectSocket, 0xf9500028, 4, JTAG_COMMON_MODULE_IDX, &data);
	}

	if (state < 0)
	{
		strMsg.Format(_T("Stall Fail"));
		goto END;
	}
#endif

	strMsg.Format(_T("Success stall CPU!\r\n"));
	AddOutBox(strMsg);

	bReturn = TRUE;

END:
	if (bReturn) {
	}
	else {
		if (strMsg != _T("")) {
			AddOutBox(strMsg + _T("\r\n"));
			AfxMessageBox(strMsg);
			//pJTAG->JTAGClose();
		}
	}
}


void CJTAGDebuggerDlg::OnBnClickedButtonJtagunstallcpu()
{
	if (!ConnectSocket)	return;
	AfxBeginThread(UnstallCPUThread, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
}

// ====================================================================================================
// UnstallCPUThread
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
UINT UnstallCPUThread(LPVOID pParam)
{
	bRunUnstallCPUThread = TRUE;

	// ----------------------------------------------------------------------------------------------------
	// 컨트롤 비활성화
	pJTAGDebuggerDlg->EnableCtrl(FALSE);
	pJTAGDebuggerDlg->m_Btn_Close.EnableWindow(FALSE);
	// ----------------------------------------------------------------------------------------------------
	// Run
	pJTAGDebuggerDlg->UnstallCPU();

	// ----------------------------------------------------------------------------------------------------
	// 컨트롤 활성화
	pJTAGDebuggerDlg->EnableCtrl(TRUE);
	pJTAGDebuggerDlg->m_Btn_Close.EnableWindow(TRUE);

	// ----------------------------------------------------------------------------------------------------
	bRunUnstallCPUThread = FALSE;

	return 0;
}

// ====================================================================================================
// CJTAGDebuggerDlg::UnstallCPU
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CJTAGDebuggerDlg::UnstallCPU()
{
	CString strMsg = _T("");
	UINT32 err = 0;
	BOOL bReturn = FALSE;
	int state = -1;

	// Title
	AddOutBox(_T("\r\n"));
	AddOutBox(_T(" > Unstall CPU\r\n"));

#if 0
	// Init JTAG
	strMsg.Format(_T("Init JTAG...... "));
	AddOutBox(strMsg);

	//if (!pJTAG->JTAGInitial(strMsg)) goto END;

	strMsg.Format(_T("End\r\n"));
	AddOutBox(strMsg);
#endif

#if WDT
	// WDT on
	UINT32 data = 0;
	if (WDT_flag)
	{
		data = htonl(0x1);
		state = setDataFromRemote(ConnectSocket, 0xf9500028, 4, JTAG_COMMON_MODULE_IDX, &data);
		WDT_flag = FALSE;

		if (state < 0)
		{
			strMsg.Format(_T("UnStall Fail"));
			goto END;
		}
	}
#endif

	// UnStall
	UINT8 stalled = 0;
	UINT8 cpu = 0;

	if (m_Radio_CPU_Cpu0.GetCheck())	cpu = 4;
	else								cpu = 5;
	
	//if (err = jtag_unstall_cpu(cpu))					{ strMsg.Format(_T("Fail UnStalled!")); goto END; }
	//if (err = pJTAG->checkstalledcpu(cpu, &stalled))	{ strMsg.Format(_T("Fail UnStalled!")); goto END; }
	//if (stalled)										{ strMsg.Format(_T("Fail UnStalled!")); goto END; }
	
	//sendMsg(ConnectSocket, "rem_ust ");
	if (cpu == 4)	state = sendMsg(ConnectSocket, "rem_ust cpu0 ");
	if (cpu == 5)	state = sendMsg(ConnectSocket, "rem_ust cpu1 ");

	if (state < 0)
	{
		strMsg.Format(_T("UnStall Fail"));
		goto END;
	}

#if 0
	// UnStall check 부분 필요
	// jtag_check_stalled_cpu필요
	if (cpu == 4)	state = sendMsg(ConnectSocket, "rem_cst cpu0 ");
	if (cpu == 5)	state = sendMsg(ConnectSocket, "rem_cst cpu1 ");
	if (state < 0)
	{
		strMsg.Format(_T("UnStall Fail"));
		goto END;
	}

	char stall_flag;
	state = recv(ConnectSocket, &stall_flag, sizeof(stall_flag), 0);
	if (stall_flag == '1')
	{
		strMsg.Format(_T("UnStall Fail"));
		goto END;
	}
#endif


	strMsg.Format(_T("Success UnStall CPU!\r\n"));
	AddOutBox(strMsg);

	bReturn = TRUE;

END:
	if (bReturn) {
	}
	else {
		if (strMsg != _T("")) {
			AddOutBox(strMsg + _T("\r\n"));
			AfxMessageBox(strMsg);
			//pJTAG->JTAGClose();
		}
	}
}


void CJTAGDebuggerDlg::OnBnClickedButtonJtagsinglesteprun()
{
	if (!ConnectSocket)	return;
	if (m_bStop)
		m_bStop = FALSE;
	else
	{
		m_bStop = TRUE;
		AfxBeginThread(SinglestepRunThread, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
	}
}


// ====================================================================================================
// SinglestepRunThread
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
UINT SinglestepRunThread(LPVOID pParam)
{
	bRunSinglestepRunThread = TRUE;

	// ----------------------------------------------------------------------------------------------------
	// 컨트롤 비활성화
	pJTAGDebuggerDlg->EnableCtrl(FALSE);
	pJTAGDebuggerDlg->m_Btn_Close.EnableWindow(FALSE);

	pJTAGDebuggerDlg->m_Btn_SinglestepRun.SetWindowTextW(_T("Stop"));
	pJTAGDebuggerDlg->m_Btn_SinglestepRun.EnableWindow(TRUE);

	// ----------------------------------------------------------------------------------------------------
	// Run
	pJTAGDebuggerDlg->SinglestepRun();

	// ----------------------------------------------------------------------------------------------------
	// 컨트롤 활성화
	pJTAGDebuggerDlg->EnableCtrl(TRUE);
	pJTAGDebuggerDlg->m_Btn_Close.EnableWindow(TRUE);

	pJTAGDebuggerDlg->m_Btn_SinglestepRun.SetWindowTextW(_T("Run"));

	// ----------------------------------------------------------------------------------------------------
	bRunSinglestepRunThread = FALSE;

	return 0;
}

// ====================================================================================================
// CJTAGDebuggerDlg::SinglestepRun
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CJTAGDebuggerDlg::SinglestepRun()
{
	int iCnt = 0;
	UINT32 num = 0;
	CString str = _T("");
	CString strMsg = _T("");
	UINT32 err = 0;
	BOOL bReturn = FALSE;
	int state = -1;

	// Clear JTAG Log
	//AddOutBox(_T(" > Single Step\r\n"), DOWNOUTPUT_CLEARALL);

	// Check Singlestep Num
	m_Edit_SinglestepNum.GetWindowTextW(str);
	if (!CheckDec(str)) {
		strMsg.Format(_T("숫자가 아닙니다."));
		goto END;
	}
	num = _ttoi(str);

	int i = 0;
	int j = 0;
	UINT8 stalled = 0;
	char buf[128] = { 0, 0 };

	for (i = 0; i < num; i++){
		if (!m_bStop) break;
		Wait(10);
		if (m_Radio_CPU_Cpu0.GetCheck())	m_gcpu = 4;
		else								m_gcpu = 5;

		if (m_gcpu == 4)	state = sendMsg(ConnectSocket, "rem_si cpu0 ");
		if (m_gcpu == 5)	state = sendMsg(ConnectSocket, "rem_si cpu1 ");

		if (state < 0)
		{
			strMsg.Format(_T("Sigle step Fail"));
			goto END;
		}

		state = recv(ConnectSocket, (char*)buf, sizeof(buf), 0);
		if (state < 0)
		{
			strMsg.Format(_T("Sigle step Fail"));
			goto END;
		}

		strMsg.Format(_T("%s\r\n"), (CString)buf);
		AddOutBox(strMsg);
	}

	//strMsg.Format(_T("Success Single Step!\r\n"));
	//AddOutBox(strMsg);

	bReturn = TRUE;

END:
	if (bReturn) {
	}
	else {
		if (strMsg != _T("")) {
			AddOutBox(strMsg + _T("\r\n"));
			AfxMessageBox(strMsg);
			//pJTAG->JTAGClose();
		}
	}
}

void CJTAGDebuggerDlg::OnBnClickedButtonJtagsinglestepcontinue()
{
	if (!ConnectSocket)	return;
	AfxBeginThread(SinglestepContinueThread, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
}


// ====================================================================================================
// SinglestepContinueThread
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
UINT SinglestepContinueThread(LPVOID pParam)
{
	bRunSinglestepContinueThread = TRUE;

	// ----------------------------------------------------------------------------------------------------
	// 컨트롤 비활성화
	pJTAGDebuggerDlg->EnableCtrl(FALSE);
	pJTAGDebuggerDlg->m_Btn_Close.EnableWindow(FALSE);

	// ----------------------------------------------------------------------------------------------------
	// Run
	pJTAGDebuggerDlg->SinglestepContinue();

	// ----------------------------------------------------------------------------------------------------
	// 컨트롤 활성화
	pJTAGDebuggerDlg->EnableCtrl(TRUE);
	pJTAGDebuggerDlg->m_Btn_Close.EnableWindow(TRUE);

	// ----------------------------------------------------------------------------------------------------
	bRunSinglestepContinueThread = FALSE;

	return 0;
}

// ====================================================================================================
// CJTAGDebuggerDlg::SinglestepContinue
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CJTAGDebuggerDlg::SinglestepContinue()
{
	CString strMsg = _T("");
	UINT32 err = 0;
	BOOL bReturn = FALSE;

	// Title
	AddOutBox(_T("\r\n"));
	AddOutBox(_T(" > Continue\r\n"));

#if 0
	// Init JTAG
	strMsg.Format(_T("Init JTAG...... "));
	AddOutBox(strMsg);

	//if (!pJTAG->JTAGInitial(strMsg)) goto END;

	strMsg.Format(_T("End\r\n"));
	AddOutBox(strMsg);
#endif

	// Single Step
	if ((err |= jtag_continue(m_gcpu)) <0) { strMsg.Format(_T("Fail : Continue (Error : 0x%08x)"), err); goto END; }

	strMsg.Format(_T("Success Continue!\r\n"));
	AddOutBox(strMsg);

	bReturn = TRUE;

END:
	if (bReturn) {
	}
	else {
		if (strMsg != _T("")) {
			AddOutBox(strMsg + _T("\r\n"));
			AfxMessageBox(strMsg);
		}
	}
}

void CJTAGDebuggerDlg::OnBnClickedButtonJtagdcr()
{
	if (!ConnectSocket)	return;
	AfxBeginThread(DisplayCPURegisterThread, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
}


// ====================================================================================================
// DisplayCPURegisterThread
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
UINT DisplayCPURegisterThread(LPVOID pParam)
{
	bRunDisplayCPURegisterThread = TRUE;

	// ----------------------------------------------------------------------------------------------------
	// 컨트롤 비활성화
	pJTAGDebuggerDlg->EnableCtrl(FALSE);
	pJTAGDebuggerDlg->m_Btn_Close.EnableWindow(FALSE);

	// ----------------------------------------------------------------------------------------------------
	// Run
	pJTAGDebuggerDlg->DisplayCPURegister();

	// ----------------------------------------------------------------------------------------------------
	// 컨트롤 활성화
	pJTAGDebuggerDlg->EnableCtrl(TRUE);
	pJTAGDebuggerDlg->m_Btn_Close.EnableWindow(TRUE);

	// ----------------------------------------------------------------------------------------------------
	bRunDisplayCPURegisterThread = FALSE;

	return 0;
}

#define SPR_BIT (1<<18)
#define DRF_BIT (2<<18)
#define DTB_BIT (4<<18)
#define  IC_BIT (8<<18)

//Group ID
#define SYS_GID		(0<<13)
#define DMMU_GID	(1<<13)
#define IMMU_GID	(2<<13)
#define DC_GID		(3<<13)
#define IC_GID		(4<<13)
#define MAC_GID		(5<<13)
#define DU_GID		(6<<13)
#define PERF_GID	(7<<13)
#define PM_GID		(8<<13)
#define PIC_GID		(9<<13)
#define TT_GID		(10<<13)
#define FPU_GID		(11<<13)
#define IWB_GID		(12<<13)
#define DWB_GID		(13<<13)
#define TB_GID		(14<<13)
// ====================================================================================================
// CJTAGDebuggerDlg::DisplayCPURegister
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CJTAGDebuggerDlg::DisplayCPURegister()
{
	BOOL bReturn = FALSE;
	CString strMsg = _T("");
	CString temp_strMsg = _T("");

	UINT32 err = 0;
	UINT32 npc, ppc, sr, esr, EPCR, EEAR, DMR1, DSR, DRR, i;
	UINT32 IWMR, IWSR, IWDTR, IWAR;
	UINT32 DWMR, DWSR, DWDTR, DWAR;
	UINT32 tbcr;
	UINT32 r[32];

	// Title
	AddOutBox(_T("\r\n"));
	AddOutBox(_T(" > Display CPU Register\r\n"));

#if 0
	// Initial JTAG
	strMsg.Format(_T("Init JTAG...... "));
	AddOutBox(strMsg);

	//if (!pJTAG->JTAGInitial(strMsg)) goto END;

	strMsg.Format(_T("End\r\n"));
	AddOutBox(strMsg);
#endif

	// Stall CPU
	int state = -1;
	if (m_Radio_CPU_Cpu0.GetCheck())	state = sendMsg(ConnectSocket, "rem_st cpu0 ");
	else								state = sendMsg(ConnectSocket, "rem_st cpu1 ");


	if (state < 0)
	{
		strMsg.Format(_T("Stall Fail"));
		goto END;
	}

#if STALL
	// Stall check 부분 필요
	// jtag_check_stalled_cpu필요
	if (m_gcpu == 4)	state = sendMsg(ConnectSocket, "rem_cst cpu0 ");
	if (m_gcpu == 5)	state = sendMsg(ConnectSocket, "rem_cst cpu1 ");
	if (state < 0)
	{
		strMsg.Format(_T("Stall Fail"));
		goto END;
}

	char stall_flag;
	state = recv(ConnectSocket, &stall_flag, sizeof(stall_flag), 0);
	if (stall_flag == '0')
	{
		strMsg.Format(_T("Stall Fail"));
		goto END;
	}
#endif

	// WDT off
	UINT32 data = 0;
	state = getDataFromRemote(ConnectSocket, 0xf9500028, 4, JTAG_COMMON_MODULE_IDX, &data);
	if (htonl(data) == 1)
	{
		WDT_flag = TRUE;
		data = 0;
		state = setDataFromRemote(ConnectSocket, 0xf9500028, 4, JTAG_COMMON_MODULE_IDX, &data);
	}

	if (state < 0)
	{
		strMsg.Format(_T("Stall Fail"));
		goto END;
	}

	//Sleep(1);
	Wait(10);
	//if (err |= jtag_stall_cpu(m_gcpu)) { strMsg.Format(_T("Fail : Stall CPU (Error : 0x%08x)"), err); goto END; }

	// Get CPU Register
#if 0
	err |= jtag_read32(SPR_BIT + SYS_GID + (16 << 2), &npc, m_gcpu);  /* Read NPC */
	err |= jtag_read32(SPR_BIT + SYS_GID + (17 << 2), &sr, m_gcpu);  /* Read SR  */
	err |= jtag_read32(SPR_BIT + SYS_GID + (18 << 2), &ppc, m_gcpu);  /* Read PPC */

	err |= jtag_read32(SPR_BIT + SYS_GID + (32 << 2), &EPCR, m_gcpu);  /* Read EPCR */
	err |= jtag_read32(SPR_BIT + SYS_GID + (64 << 2), &esr, m_gcpu);  /* Read ESR */
	err |= jtag_read32(SPR_BIT + SYS_GID + (48 << 2), &EEAR, m_gcpu);  /* Read EEAR */

	err |= jtag_read32(SPR_BIT + DU_GID + (16 << 2), &DMR1, m_gcpu);  /* Read DMR1 */
	err |= jtag_read32(SPR_BIT + DU_GID + (20 << 2), &DSR, m_gcpu);  /* Read DSR */
	err |= jtag_read32(SPR_BIT + DU_GID + (21 << 2), &DRR, m_gcpu);  /* Read DRR */

	err |= jtag_read32(SPR_BIT + IWB_GID + (16 << 2), &IWMR, m_gcpu);  /* Read IWMR */
	err |= jtag_read32(SPR_BIT + IWB_GID + (17 << 2), &IWSR, m_gcpu);  /* Read IWSR */
	err |= jtag_read32(SPR_BIT + IWB_GID + (18 << 2), &IWDTR, m_gcpu);  /* Read IWDTR */
	err |= jtag_read32(SPR_BIT + IWB_GID + (19 << 2), &IWAR, m_gcpu);  /* Read IWAR */

	err |= jtag_read32(SPR_BIT + DWB_GID + (16 << 2), &DWMR, m_gcpu);  /* Read DWMR */
	err |= jtag_read32(SPR_BIT + DWB_GID + (17 << 2), &DWSR, m_gcpu);  /* Read DWSR */
	err |= jtag_read32(SPR_BIT + DWB_GID + (18 << 2), &DWDTR, m_gcpu);  /* Read DWDTR */
	err |= jtag_read32(SPR_BIT + DWB_GID + (19 << 2), &DWAR, m_gcpu);  /* Read DWAR */

	err |= jtag_read32(SPR_BIT + TB_GID + TBCR, &tbcr, m_gcpu);  /* Read TBCR */
#endif
	///////
	err |= getDataFromRemote(ConnectSocket, SPR_BIT + SYS_GID + (16 << 2), 4, m_gcpu, &npc);	/* Read NPC */
	Wait(1);
	err |= getDataFromRemote(ConnectSocket, SPR_BIT + SYS_GID + (17 << 2), 4, m_gcpu, &sr);		/* Read SR  */
	Wait(1);
	err |= getDataFromRemote(ConnectSocket, SPR_BIT + SYS_GID + (18 << 2), 4, m_gcpu, &ppc);	/* Read PPC */
	Wait(1);

	err |= getDataFromRemote(ConnectSocket, SPR_BIT + SYS_GID + (32 << 2), 4, m_gcpu, &EPCR);	/* Read EPCR */
	Wait(1);
	err |= getDataFromRemote(ConnectSocket, SPR_BIT + SYS_GID + (64 << 2), 4, m_gcpu, &esr);	/* Read ESR */
	Wait(1);
	err |= getDataFromRemote(ConnectSocket, SPR_BIT + SYS_GID + (48 << 2), 4, m_gcpu, &EEAR);	/* Read EEAR */
	Wait(1);

	err |= getDataFromRemote(ConnectSocket, SPR_BIT + DU_GID + (16 << 2), 4, m_gcpu, &DMR1);	/* Read DMR1 */
	Wait(1);
	err |= getDataFromRemote(ConnectSocket, SPR_BIT + DU_GID + (20 << 2), 4, m_gcpu, &DSR);		/* Read DSR */
	Wait(1);
	err |= getDataFromRemote(ConnectSocket, SPR_BIT + DU_GID + (21 << 2), 4, m_gcpu, &DRR);		/* Read DRR */
	Wait(1);


	err |= getDataFromRemote(ConnectSocket, SPR_BIT + IWB_GID + (16 << 2), 4, m_gcpu, &IWMR);	/* Read IWMR */
	Wait(1);
	
	err |= getDataFromRemote(ConnectSocket, SPR_BIT + IWB_GID + (17 << 2), 4, m_gcpu, &IWSR);	/* Read IWSR */
	Wait(1);
	err |= getDataFromRemote(ConnectSocket, SPR_BIT + IWB_GID + (18 << 2), 4, m_gcpu, &IWDTR);	/* Read IWDTR */
	Wait(1);
	err |= getDataFromRemote(ConnectSocket, SPR_BIT + IWB_GID + (19 << 2), 4, m_gcpu, &IWAR);	/* Read IWAR */
	Wait(1);

	err |= getDataFromRemote(ConnectSocket, SPR_BIT + DWB_GID + (16 << 2), 4, m_gcpu, &DWMR);	/* Read DWMR */
	Wait(1);
	err |= getDataFromRemote(ConnectSocket, SPR_BIT + DWB_GID + (17 << 2), 4, m_gcpu, &DWSR);	/* Read DWSR */
	Wait(1);
	err |= getDataFromRemote(ConnectSocket, SPR_BIT + DWB_GID + (18 << 2), 4, m_gcpu, &DWDTR);	/* Read DWDTR */
	Wait(1);
	err |= getDataFromRemote(ConnectSocket, SPR_BIT + DWB_GID + (19 << 2), 4, m_gcpu, &DWAR);	/* Read DWAR */
	Wait(1);

	err |= getDataFromRemote(ConnectSocket, SPR_BIT + TB_GID + TBCR, 4, m_gcpu, &tbcr);			/* Read TBCR */
	Wait(1);


	if (err < 0) {
		strMsg.Format(_T("Fail : Read register (Error : 0x%08x)"), err);
		goto END;
	}
	
	// Display CPU Register
	temp_strMsg.Format(_T("Status:     NPC  = %.8x  SR   = %.8x PPC   = %.8x\r\n"), htonl(npc) & 0xfffffffc, htonl(sr), htonl(ppc) & 0xfffffffc);		strMsg = strMsg + temp_strMsg;//AddOutBox(strMsg);
	temp_strMsg.Format(_T("Exception:  EPCR = %.8x  ESR  = %.8x EEAR  = %.8x\r\n"), htonl(EPCR) & 0xfffffffc, htonl(esr), htonl(EEAR));					strMsg = strMsg + temp_strMsg;//AddOutBox(strMsg);
	temp_strMsg.Format(_T("Debug:      DMR1 = %.8x  DSR  = %.8x DRR   = %.8x\r\n"), htonl(DMR1), htonl(DSR), htonl(DRR));								strMsg = strMsg + temp_strMsg;//AddOutBox(strMsg);
	temp_strMsg.Format(_T("IHWP:       IWMR = %.8x  IWSR = %.8x IWDTR = %.8x IWAR = %.8x\r\n"), htonl(IWMR), htonl(IWSR), htonl(IWDTR), htonl(IWAR));	strMsg = strMsg + temp_strMsg;//AddOutBox(strMsg);
	temp_strMsg.Format(_T("DHWP:       DWMR = %.8x  DWSR = %.8x DWDTR = %.8x DWAR = %.8x\r\n"), htonl(DWMR), htonl(DWSR), htonl(DWDTR), htonl(DWAR));	strMsg = strMsg + temp_strMsg;//AddOutBox(strMsg);
	temp_strMsg.Format(_T("TB:         TBCR = %.8x\r\n"), htonl(tbcr));																					strMsg = strMsg + temp_strMsg;//AddOutBox(strMsg);
	temp_strMsg.Format(_T("GPR:\r\n"));																													strMsg = strMsg + temp_strMsg;//AddOutBox(strMsg);

	for (i = 0; i < 32; i++){
		//if (err |= jtag_read32(DRF_BIT + (0x400 << 2) + (i << 2), &r[i], m_gcpu)) {
		if (0 > getDataFromRemote(ConnectSocket, DRF_BIT + (0x400 << 2) + (i << 2), 4, m_gcpu, &r[i])) {
			strMsg.Format(_T("Fail : Read register (Error : 0x%08x)"), err);
			Wait(10);
			goto END;
		}
		temp_strMsg.Format(_T("\t r%.2d = %.8x \r\n"), i, htonl(r[i]));	
		strMsg = strMsg + temp_strMsg; //AddOutBox(strMsg);
	}

	AddOutBox(strMsg);
	bReturn = TRUE;
END:
	if (bReturn) {
	}
	else {
		if (strMsg != _T("")) {
			AddOutBox(strMsg + _T("\r\n"));
			AfxMessageBox(strMsg);
			//pJTAG->JTAGClose();
		}
	}
}


void CJTAGDebuggerDlg::OnBnClickedButtonJtagdebuggerSavelog()
{
	if (m_Edit_JTAGLog.GetWindowTextLengthW() <= 0) {
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
	m_Edit_JTAGLog.GetWindowTextW(str);
	file.WriteString(str);

	file.Close();

	AfxMessageBox(_T("Save Complete!"));
}


void CJTAGDebuggerDlg::OnBnClickedButtonJtagdebuggerClearlog()
{
	AddOutBox(_T(""), DOWNOUTPUT_CLEARALL);
}


// ====================================================================================================
// CJTAGDebuggerDlg::AddOutBox
// ----------------------------------------------------------------------------------------------------
/*
str : 출력할 문자.
bClear
- 0 (default) : 그냥 추가 출력
- 1           : 해당 라인 지우고 출력
- 2           : 모두 지우고 출력
*/
// ====================================================================================================
void CJTAGDebuggerDlg::AddOutBox(CString str, BOOL bClear)
{
	int iLen = 0;
	int iIndex = 0;
	int iLineCount = 0;
	CString strOutput = _T("");

	m_Edit_JTAGLog.SetRedraw(FALSE);

	switch (bClear)
	{
	case DOWNOUTPUT_NONE:
		// Add String
		m_Edit_JTAGLog.GetWindowTextW(strOutput);
		m_Edit_JTAGLog.SetWindowTextW(strOutput + str);
		break;

	case DOWNOUTPUT_CLEARLINE: // Clear Line
		iLineCount = m_Edit_JTAGLog.GetLineCount() - 1;
		iIndex = m_Edit_JTAGLog.LineIndex(iLineCount);
		iLen = m_Edit_JTAGLog.GetWindowTextLengthW() - iIndex;
		m_Edit_JTAGLog.SetSel(iIndex, iIndex + iLen);
		m_Edit_JTAGLog.ReplaceSel(str);
		break;

	case DOWNOUTPUT_CLEARALL: // Clear All
		m_Edit_JTAGLog.SetWindowTextW(str);

		break;
	}

	m_Edit_JTAGLog.SetRedraw(TRUE);
	//m_Edit_JTAGLog.Invalidate();
	// Set Cursor
	//if(str.Find('\n')>=0) // 이거 했더니 제대로 인식이 안되는지 커서가 안감ㅠㅠ
	{
		int iLength = m_Edit_JTAGLog.GetWindowTextLengthW();
		m_Edit_JTAGLog.SetSel(iLength, -1);
	}
}

// ====================================================================================================
// CJTAGDebuggerDlg::EnableCtrl
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CJTAGDebuggerDlg::EnableCtrl(BOOL bEnable)
{
	m_Edit_MemoryAddr.EnableWindow(bEnable);
	m_Edit_MemorySize.EnableWindow(bEnable);
	m_Cbo_MemoryModule.EnableWindow(bEnable);
	m_Btn_MemoryRead.EnableWindow(bEnable);
	m_Btn_MemoryWrite.EnableWindow(bEnable);
	m_Edit_RegisterAddr.EnableWindow(bEnable);
	m_Edit_RegisterSize.EnableWindow(bEnable);
	m_Edit_RegisterData.EnableWindow(bEnable);
	m_Cbo_RegisterModule.EnableWindow(bEnable);
	m_Btn_RegisterRead.EnableWindow(bEnable);
	m_Btn_RegisterWrite.EnableWindow(bEnable);
	m_Radio_CPU_Cpu0.EnableWindow(bEnable);
	m_Radio_CPU_Cpu1.EnableWindow(bEnable);
	m_Btn_StallCPU.EnableWindow(bEnable);
	m_Btn_UnstallCPU.EnableWindow(bEnable);
	m_Edit_SinglestepNum.EnableWindow(bEnable);
	m_Btn_SinglestepRun.EnableWindow(bEnable);
	m_Btn_Continue.EnableWindow(bEnable);
	m_Btn_Dcr.EnableWindow(bEnable);
	m_Edit_JTAGLog.EnableWindow(bEnable);
}

UINT32 jtag_stall_cpu(UINT8 cpu){
	int err;
	if (cpu == 4)	err = sendMsg(ConnectSocket, "rem_st cpu0 ");
	if (cpu == 5)	err = sendMsg(ConnectSocket, "rem_st cpu1 ");
	//sendMsg(ConnectSocket, "rem_st ");
	return err;
}


UINT32 jtag_unstall_cpu(UINT8 cpu){
	int err;
	if (cpu == 4)	err = sendMsg(ConnectSocket, "rem_ust cpu0 ");
	if (cpu == 5)	err = sendMsg(ConnectSocket, "rem_ust cpu1 ");
	//sendMsg(ConnectSocket, "rem_ust ");

	return err;
}


UINT32 jtag_single_step(UINT8 cpu){
	UINT32 err = 0;
#if 0
	err |= jtag_stall_cpu(cpu);
	err |= jtag_write32(SPR_BIT + DU_GID + (16 << 2), (1 << 22) | (1 << 26), cpu);  /* Set step bit and NOP enable */
#endif
	UINT32 data = htonl((1 << 22) | (1 << 26));
	err |= jtag_stall_cpu(cpu);
	Wait(10);
	err |= setDataFromRemote(ConnectSocket, SPR_BIT + DU_GID + (16 << 2), 4, cpu, &data);   /* Set step bit and NOP enable */

	return err;
}

UINT32 jtag_continue(UINT8 cpu){
	UINT32 err = 0;
	UINT32 data = 0;
#if 0
	err |= jtag_stall_cpu(cpu);
	err |= jtag_write32(SPR_BIT + DU_GID + (16 << 2), 0, cpu);  /* Reset step bit */
	err |= jtag_unstall_cpu(cpu);
#endif
	err |= jtag_stall_cpu(cpu);
	Wait(10);
	err |= setDataFromRemote(ConnectSocket, SPR_BIT + DU_GID + (16 << 2), 4, cpu, &data);  /* Reset step bit */
	Wait(10);
	err |= jtag_unstall_cpu(cpu);

	return err;
}


UINT32 jtag_read_cpu_status(UINT8 cpu, UINT8* buffer)
{
	UINT32 err = 0;
	UINT32 npc, ppc;
	UINT32 expc, wbpc;
	UINT32 insn, module;
	UINT32 ex_pd_flag, ex_pd_taken;
	UINT32 ex_nop, ex_flush;
	UINT32 ex_insn;

	UINT32 ex_op, ex_ra, ex_rb, ex_rd_a, ex_rd_b;

	UINT32 ex_branch_op;

	UINT32 ex_fwdat_a, ex_fwdat_b;
	UINT8	ex_fwdat_aS[10] = { 0, 0 };
	UINT8	ex_fwdat_bS[10] = { 0, 0 };

	//err |= jtag_stall_cpu(cpu);

	//err |= jtag_read32(SPR_BIT + SYS_GID + (16 << 2), &npc, cpu);  /* Read NPC */
	//err |= jtag_read32(SPR_BIT + SYS_GID + (18 << 2), &ppc, cpu);  /* Read PPC */
	err |= getDataFromRemote(ConnectSocket, SPR_BIT + SYS_GID + (16 << 2), 4, cpu, &npc);		/* Read NPC */
	Wait(10);
	err |= getDataFromRemote(ConnectSocket, SPR_BIT + SYS_GID + (18 << 2), 4, cpu, &ppc);		/* Read PPC */
	npc = htonl(npc);
	ppc = htonl(ppc);

	expc = npc & 0xfffffffc;
	ex_pd_flag = (npc & 0x00000002) >> 1;
	ex_pd_taken = npc & 0x00000001;

	wbpc = ppc & 0xfffffffc;
	ex_nop = (ppc & 0x00000002) >> 1;
	ex_flush = ppc & 0x00000001;




	if ((expc & 0xff000000) == SDRAM_BASE){
		module = CPU0;
	}
	else
	{
		module = WBCOM;
	}

	err |= jtag_wb_read32(expc, &insn, module);

	if (ex_nop) ex_insn = INOP;
	else        ex_insn = htonl(insn);


	ex_op = (ex_insn & 0xfc000000) >> 26;
	ex_ra = (ex_insn & 0x001f0000) >> 16;
	ex_rb = (ex_insn & 0x0000f800) >> 11;
	ex_rd_a = (ex_insn & 0x80000000) >> 31;
	ex_rd_b = (ex_insn & 0x40000000) >> 30;

	switch (ex_op)
	{
	case EXR1K_OP_J:
	case EXR1K_OP_JAL:
	case EXR1K_OP_JR:
	case EXR1K_OP_JALR:
	case EXR1K_OP_BNF:
	case EXR1K_OP_BF:
	case EXR1K_OP_RFE:
		ex_branch_op = 1;
		break;
	default:
		ex_branch_op = 0;
		break;
	}

	ex_ra &= 0xfffffffc;
	ex_rb &= 0xfffffffc;
	
	if (ex_rd_a) {
		//err |= jtag_read32(DRF_BIT + EXR1K_SYS_RF0 + ex_ra, &ex_fwdat_a, cpu);
		err |= getDataFromRemote(ConnectSocket, DRF_BIT + EXR1K_SYS_RF0 + ex_ra, 4, (int)cpu, &ex_fwdat_a);
		//Wait(10);
		ex_fwdat_a = htonl(ex_fwdat_a);
		sprintf_s((char*)ex_fwdat_aS, 10, "%.8x", ex_fwdat_a);
	}
	else{
		sprintf_s((char*)ex_fwdat_aS, 10, "%s", "xxxxxxxx");
	}

	if (ex_rd_b) {
		//err |= jtag_read32(DRF_BIT + EXR1K_SYS_RF0 + ex_rb, &ex_fwdat_b, cpu);
		err |= getDataFromRemote(ConnectSocket, DRF_BIT + EXR1K_SYS_RF0 + ex_rb, 4, cpu, &ex_fwdat_b);
		//Wait(10);
		ex_fwdat_b = htonl(ex_fwdat_b);
		sprintf_s((char*)ex_fwdat_bS, 10, "%.8x", ex_fwdat_b);
	}
	else{
		sprintf_s((char*)ex_fwdat_bS, 10, "%s", "xxxxxxxx");
	}

	if (ex_flush){
		sprintf_s((char*)buffer, 100, "@%.8x: %.8x x\n", expc, INOP);
	}
	else{
		sprintf_s((char*)buffer, 100, "@%.8x: %.8x %1x: %s %s\n", expc, ex_insn, ex_branch_op, ex_fwdat_aS, ex_fwdat_bS);

	}

	return err;
}

UINT32 jtag_wb_read32(UINT32 adr, UINT32 *data, UINT32 cpu)
{
	UINT32 err = 0;
	UINT32 wb = cpu - 4;
	if (cpu == WBCOM) wb = cpu;
	//err |= jtag_read32(adr, data, wb);
	err |= getDataFromRemote(ConnectSocket, adr, 4, wb, data);
	//data = (UINT32*)jtag_htonl((UINT32)data);
	return err;
}

void CJTAGDebuggerDlg::OnBnClickedButtonConnect()
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
		m_Btn_Connect.SetIcon(IDI_CONNECT, NULL);
	}
	else {
		m_Btn_Connect.SetIcon(IDI_DISCONNECT, NULL);
	}
#endif
}


void CJTAGDebuggerDlg::OnTimer(UINT_PTR nIDEvent)
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


void CJTAGDebuggerDlg::Check_Timer_On()
{
	m_CheckTimerID = SetTimer(ID_CHECK_TIMER, Check_Time, NULL);
}

void CJTAGDebuggerDlg::Check_Timer_Off()
{
	if (m_CheckTimerID)
	{
		if (this->GetSafeHwnd())
			KillTimer(m_CheckTimerID);
		m_CheckTimerID = 0;
	}
}

void CJTAGDebuggerDlg::Connect_Timer_On()
{
	m_ConnectTimerID = SetTimer(ID_CONNECT_TIMER, Connect_Time, NULL);
}

void CJTAGDebuggerDlg::Connect_Timer_Off()
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
				pJTAGDebuggerDlg->EnableCtrl(TRUE);
				pJTAGDebuggerDlg->m_Btn_Connect.SetIcon(IDI_CONNECT, NULL);

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
	pJTAGDebuggerDlg->EnableCtrl(FALSE);
	pJTAGDebuggerDlg->m_Btn_Connect.SetIcon(IDI_DISCONNECT, NULL);

	NetClo(ConnectSocket);
	ConnectSocket = NULL;

	Wait(1);

	NetClo(StateSocket);
	StateSocket = NULL;

	pJTAGDebuggerDlg->Check_Timer_Off();
	pJTAGDebuggerDlg->Connect_Timer_On();

	Invalidate_flsg = FALSE;

	return 0;
}

UINT Connect_Check_Thread(LPVOID pParam)
{
	ConnectSocket = NetCon(pJTAGDebuggerDlg->ch_ip, pJTAGDebuggerDlg->ch_port);
	//Sleep(1);
	Wait(1);
	StateSocket = NetCon(pJTAGDebuggerDlg->ch_ip, pJTAGDebuggerDlg->ch_port);

	if (ConnectSocket <= 0 || StateSocket <= 0)
	{
		NetClo(ConnectSocket);
		ConnectSocket = NULL;

		NetClo(StateSocket);
		StateSocket = NULL;
	}
	else
	{
		pJTAGDebuggerDlg->Connect_Timer_Off();
		pJTAGDebuggerDlg->Check_Timer_On();

		Invalidate_flsg = FALSE;
	}
	return 0;
}