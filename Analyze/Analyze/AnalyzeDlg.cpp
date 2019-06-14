
// AnalyzeDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "Analyze.h"
#include "AnalyzeDlg.h"
#include "afxdialogex.h"

#include "resource.h"

#include "WaveformImgOperation.h"
#include "Net_command.h"

// opencv
#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include <opencv\cv.h>
#include <opencv\cv.hpp>
#include <opencv\highgui.h>
#include <opencv2\imgcodecs.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\core.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv2\calib3d.hpp>
#include <opencv2\imgcodecs.hpp>
#include <opencv2\videoio.hpp>
#include <opencv2\highgui.hpp>

using namespace cv;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma warning(disable:4996)

// Thread
UINT	AnalyzeThread(LPVOID pParam);
UINT	EndAnalyzeThread(LPVOID pParam);
UINT	ImageRecvThread(LPVOID pParam);

CAnalyzeDlg				*pAnalyzeDlg;
CAnalyzeSourceimage		*pAnalyzeSourceimage;

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


// CAnalyzeDlg 대화 상자



CAnalyzeDlg::CAnalyzeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAnalyzeDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ECM);
}

void CAnalyzeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_PLAYANALYZE, m_Btn_PlayAnalyze);
	DDX_Control(pDX, IDC_CHECK_VECTORSCOPE, m_Chk_Vectorscope);
	DDX_Control(pDX, IDC_CHECK_WAVEFORMR, m_Chk_WaveformR);
	DDX_Control(pDX, IDC_CHECK_WAVEFORMG, m_Chk_WaveformG);
	DDX_Control(pDX, IDC_CHECK_WAVEFORMB, m_Chk_WaveformB);
	DDX_Control(pDX, IDC_CHECK_WAVEFORMY, m_Chk_WaveformY);
	DDX_Control(pDX, IDC_BUTTON_ANALYZECLOSE, m_Btn_Close);
	DDX_Control(pDX, IDC_BUTTON_MINIMIZE, m_Btn_Minimize);
}

BEGIN_MESSAGE_MAP(CAnalyzeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_PLAYANALYZE, &CAnalyzeDlg::OnBnClickedButtonPlayanalyze)
	ON_BN_CLICKED(IDC_BUTTON_ANALYZECLOSE, &CAnalyzeDlg::OnBnClickedButtonAnalyzeclose)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BUTTON_MINIMIZE, &CAnalyzeDlg::OnBnClickedButtonMinimize)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_CHECK_VECTORSCOPE, &CAnalyzeDlg::OnBnClickedCheckVectorscope)
	ON_BN_CLICKED(IDC_CHECK_WAVEFORMR, &CAnalyzeDlg::OnBnClickedCheckWaveformr)
	ON_BN_CLICKED(IDC_CHECK_WAVEFORMG, &CAnalyzeDlg::OnBnClickedCheckWaveformg)
	ON_BN_CLICKED(IDC_CHECK_WAVEFORMB, &CAnalyzeDlg::OnBnClickedCheckWaveformb)
	ON_BN_CLICKED(IDC_CHECK_WAVEFORMY, &CAnalyzeDlg::OnBnClickedCheckWaveformy)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CAnalyzeDlg 메시지 처리기

BOOL CAnalyzeDlg::OnInitDialog()
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
	SetWindowText(DLG_ANALYZE);

	int x = ReadIni(SEC_WININFO, KEY_ANALYZEDLGLEFT, DEF_ANALYZEDLGLEFT);
	int y = ReadIni(SEC_WININFO, KEY_ANALYZEDLGTOP, DEF_ANALYZEDLGTOP);
	SetWindowPos(NULL, x, y, 0, 0, SWP_NOSIZE);

	pAnalyzeDlg = this;
// ----------------------------------------------------------------------------------------------------
// Create Sub Dialog
	m_pAnalyzeSourceimage = new CAnalyzeSourceimage();
	m_pAnalyzeSourceimage->Create(IDD_ANALYZE_SOURCEIMAGE, this);
	m_pAnalyzeSourceimage->ShowWindow(SW_HIDE);



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
	char ch_ip[64];
	char ch_port[64];
	addr = strAddr;
	port = strPort;
	strcpy(ch_ip, addr.GetBuffer(addr.GetLength()));
	strcpy(ch_port, port.GetBuffer(port.GetLength()));

#if 0
	ConnectSocket = NetCon(ch_ip, ch_port);
	if (ConnectSocket <= 0)
	{
		AfxMessageBox(_T("Not Connect"));
		//exit(0);
	}
#else
	ConnectSocket = NULL;
#endif
// ----------------------------------------------------------------------------------------------------
	// Variable
	m_bRunAnalyze = FALSE;
	m_bStopAnalyze = FALSE; // 일시정지

	bRunAnalyzeThread = FALSE;

// ----------------------------------------------------------------------------------------------------
	// Control
	m_Btn_Close.DrawBorder(FALSE);
	m_Btn_Close.SetColor(CButtonST::BTNST_COLOR_BK_OUT, DIALOGCOLOR);
	m_Btn_Close.SetColor(CButtonST::BTNST_COLOR_BK_IN, DIALOGSUBCOLOR);

	m_Btn_Minimize.DrawBorder(FALSE);
	m_Btn_Minimize.SetColor(CButtonST::BTNST_COLOR_BK_OUT, DIALOGCOLOR);
	m_Btn_Minimize.SetColor(CButtonST::BTNST_COLOR_BK_IN, DIALOGSUBCOLOR);

	int i = 0;

	// Vectorscope
	i = ReadIni(SEC_ANALYZE, KEY_VECTORSCOPE, DEF_VECTORSCOPE);
	m_Chk_Vectorscope.SetCheck(i);
	// WaveformR
	i = ReadIni(SEC_ANALYZE, KEY_WAVEFORM_R, DEF_WAVEFORM_R);
	m_Chk_WaveformR.SetCheck(i);
	// WaveformG
	i = ReadIni(SEC_ANALYZE, KEY_WAVEFORM_G, DEF_WAVEFORM_G);
	m_Chk_WaveformG.SetCheck(i);
	// WaveformB
	i = ReadIni(SEC_ANALYZE, KEY_WAVEFORM_B, DEF_WAVEFORM_B);
	m_Chk_WaveformB.SetCheck(i);
	// WaveformY
	i = ReadIni(SEC_ANALYZE, KEY_WAVEFORM_Y, DEF_WAVEFORM_Y);
	m_Chk_WaveformY.SetCheck(i);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CAnalyzeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

BOOL CAnalyzeDlg::PreTranslateMessage(MSG* pMsg)
{
	// Default Window Message
	if (DefaultWindowMessage(pMsg))	return TRUE;
	else							return CDialogEx::PreTranslateMessage(pMsg);
}

int CAnalyzeDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
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

void CAnalyzeDlg::OnPaint()
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

		dc.TextOutW(10, 6, DLG_ANALYZE);

		dc.SelectObject(pOldFont);
	}
}


void CAnalyzeDlg::OnClose()
{
	SaveValue();
	
	pAnalyzeDlg->RunEndAnalyzeThread();

	if (m_bRunAnalyze)
		ReadImageKill();

	destroyAllWindows();

	if (m_pAnalyzeSourceimage != nullptr)
	{
		delete m_pAnalyzeSourceimage;
		m_pAnalyzeSourceimage = NULL;
	}

	if (ConnectSocket != NULL)
	{
		NetClo(ConnectSocket);
		ConnectSocket = NULL;
	}

	CDialogEx::OnClose();
}


void CAnalyzeDlg::OnCancel()
{
	SaveValue();

	if (m_bRunAnalyze)
		ReadImageKill();

	destroyAllWindows();

	if (m_pAnalyzeSourceimage != nullptr)
	{
		delete m_pAnalyzeSourceimage;
		m_pAnalyzeSourceimage = NULL;
	}

	if (ConnectSocket != NULL)
	{
		NetClo(ConnectSocket);
		ConnectSocket = NULL;
	}

	CDialogEx::OnCancel();
}


void CAnalyzeDlg::OnBnClickedButtonMinimize()
{
	ShowWindow(SW_MINIMIZE);
	//pAnalyzeSourceimage->ShowWindow(SW_MINIMIZE);

	// opencv imshow 로 생성한 window 최소화 방법? 없는건가?
}


// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CAnalyzeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CAnalyzeDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetCapture();
	m_Point = point;

	CDialogEx::OnLButtonDown(nFlags, point);
}

void CAnalyzeDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (this == GetCapture())
	{
		CRect rcDialog;
		GetWindowRect(&rcDialog);

		int x = rcDialog.left + point.x - m_Point.x;
		int y = rcDialog.top + point.y - m_Point.y;

		SetWindowPos(NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		WriteIni(SEC_WININFO, KEY_ANALYZEDLGLEFT, x);
		WriteIni(SEC_WININFO, KEY_ANALYZEDLGTOP, y);
	}

	CDialogEx::OnMouseMove(nFlags, point);
}

void CAnalyzeDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	ReleaseCapture();
	CDialogEx::OnLButtonUp(nFlags, point);
}


void CAnalyzeDlg::OnBnClickedButtonPlayanalyze()
{
	// Net Check
	if (ConnectSocket == NULL)
	{
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
		char ch_ip[64];
		char ch_port[64];
		addr = strAddr;
		port = strPort;
		strcpy(ch_ip, addr.GetBuffer(addr.GetLength()));
		strcpy(ch_port, port.GetBuffer(port.GetLength()));

		ConnectSocket = NetCon(ch_ip, ch_port);
		if (ConnectSocket <= 0)
		{
			NetClo(ConnectSocket);
			ConnectSocket = NULL;
			AfxMessageBox(_T("Not Connect"));
			return;
		}
	}

	// Start
	if (!m_bRunAnalyze) {
		int iResult;
		char instr[MAX_IN_STRING] = { 0, 0 };

		iResult = ReadImageCheck();
		
		if (iResult == 1)
		{
			if (IDYES == AfxMessageBox(_T("Already Image sending to another client!!!\nDo you want to terminate the other client connection and send the Image here?"), MB_YESNO))
			{
				iResult = ReadImageFlag(0);
				Sleep(1000);
			}
			else
			{
				if (IDNO)
				{
					NetClo(ConnectSocket);
					ConnectSocket = NULL;
					return;
				}
			}
		}
		if (iResult == -1)
		{
			NetClo(ConnectSocket);
			ConnectSocket = NULL;
			AfxMessageBox(_T("Server Connect Check err!"));
			return;
		}

		Sleep(100);

		ReadImage();

		// Change Button
		m_Btn_PlayAnalyze.SetWindowTextW(_T("Stop"));

		// Run Vectorscope Thread
		AfxBeginThread(AnalyzeThread, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
		AfxBeginThread(ImageRecvThread, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
	}
	else {
		// End
		RunEndAnalyzeThread();
	}

}


void CAnalyzeDlg::OnBnClickedButtonAnalyzeclose()
{
	CAnalyzeDlg::OnCancel();
}


// ====================================================================================================
// AnalyzeThread
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
UINT AnalyzeThread(LPVOID pParam)
{
	// ----------------------------------------------------------------------------------------------------
	// Start
	bRunAnalyzeThread = TRUE;
	pAnalyzeDlg->m_bRunAnalyze = TRUE;


	// ----------------------------------------------------------------------------------------------------
	// Run
	pAnalyzeDlg->RunAnalyze();

	// ----------------------------------------------------------------------------------------------------
	// End
	//Change Button
	pAnalyzeDlg->m_bRunAnalyze = FALSE;
	bRunAnalyzeThread = FALSE;

	pAnalyzeDlg->m_Btn_PlayAnalyze.SetWindowTextW(_T("Play"));

	return 0;
}


UINT ImageRecvThread(LPVOID pParam)
{

	/*
		Image recv 하는거 이부분으로 분리해서 적용
		but, 이미지 받는거랑 뿌리는거랑 싱크가 맞을까?
	*/

	return 0;
}

#define ToRadian( degree )  ( (degree) * (PI / 180.0f) )
#define ToDegree( radian )  ( (radian) * (180.0f / PI) )
const string COLOR_NAME[VECTORSCOPE_COLOR_POINT] = { "Mg", "R", "Y", "G", "Cy", "B" };
// ====================================================================================================
// drawBackgroundVectorscope
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
Mat drawBackgroundVectorscope(Mat img, int width, int height){
	Scalar color(0, 128, 255); //RGB(255, 128, 0)
	Scalar color2(0x3a, 0x5f, 0xa6); //RGB(255, 128, 0)

	int w2 = width / 2;
	int h2 = height / 2;
	int thickness = 1;
	float c1 = ((float)20 / 256) * width; // Circle1
	float c2 = ((float)40 / 256) * width; // Circle2
	float c3 = ((float)60 / 256) * width; // Circle3
	float c4 = ((float)80 / 256) * width; // Circle4
	float c5 = ((float)100 / 256) * width; // Circle5

	//line(img, Point(w2 - 5, h2), Point(w2 + 5, h2), color, thickness);	// Horizontal
	//line(img, Point(w2, h2 - 5), Point(w2, h2 + 5), color, thickness);	// Vertical

	// Horizontal
	line(img, Point(VECTORSCOPE_INTERVAL, h2), Point(w2 - 15, h2), color, thickness);
	line(img, Point(w2 + 15, h2), Point(width - VECTORSCOPE_INTERVAL, h2), color, thickness);
	line(img, Point(w2 - 5, h2), Point(w2 + 5, h2), color, thickness);
	// Vertical
	line(img, Point(w2, VECTORSCOPE_INTERVAL), Point(w2, h2 - 15), color, thickness);
	line(img, Point(w2, h2 + 15), Point(w2, height - VECTORSCOPE_INTERVAL), color, thickness);
	line(img, Point(w2, h2 - 5), Point(w2, h2 + 5), color, thickness);

	// Circle
	circle(img, Point(w2, h2), (int)c1, color, thickness, CV_AA);
	circle(img, Point(w2, h2), (int)c2, color, thickness, CV_AA);
	circle(img, Point(w2, h2), (int)c3, color, thickness, CV_AA);
	circle(img, Point(w2, h2), (int)c4, color, thickness, CV_AA);
	circle(img, Point(w2, h2), (int)c5, color, thickness, CV_AA);

#if 0
	double cos30 = cos(ToRadian(30));
	double cos60 = cos(ToRadian(60));
	double sin30 = sin(ToRadian(30));
	double sin60 = sin(ToRadian(60));
	line(img, Point(w2 + (c1 * cos30), h2 - (c1 * sin30)), Point(w2 + (c5 * cos30), h2 - (c5 * sin30)), color2, thickness, CV_AA); // 우상단 아래쪽
	line(img, Point(w2 - (c1 * cos30), h2 - (c1 * sin30)), Point(w2 - (c5 * cos30), h2 - (c5 * sin30)), color2, thickness, CV_AA); // 좌상단 아래쪽
	line(img, Point(w2 + (c1 * cos60), h2 - (c1 * sin60)), Point(w2 + (c5 * cos60), h2 - (c5 * sin60)), color2, thickness, CV_AA); // 우상단 위쪽
	line(img, Point(w2 - (c1 * cos60), h2 - (c1 * sin60)), Point(w2 - (c5 * cos60), h2 - (c5 * sin60)), color2, thickness, CV_AA); // 좌상단 위쪽
	line(img, Point(w2 + (c1 * cos30), h2 + (c1 * sin30)), Point(w2 + (c5 * cos30), h2 + (c5 * sin30)), color2, thickness, CV_AA);
	line(img, Point(w2 - (c1 * cos30), h2 + (c1 * sin30)), Point(w2 - (c5 * cos30), h2 + (c5 * sin30)), color2, thickness, CV_AA);
	line(img, Point(w2 + (c1 * cos60), h2 + (c1 * sin60)), Point(w2 + (c5 * cos60), h2 + (c5 * sin60)), color2, thickness, CV_AA);
	line(img, Point(w2 - (c1 * cos60), h2 + (c1 * sin60)), Point(w2 - (c5 * cos60), h2 + (c5 * sin60)), color2, thickness, CV_AA);
#else
	double cos0 = cos(ToRadian(COLOR_DEGREE[0]));
	double sin0 = sin(ToRadian(COLOR_DEGREE[0]));
	double cos1 = cos(ToRadian(COLOR_DEGREE[1]));
	double sin1 = sin(ToRadian(COLOR_DEGREE[1]));
	double cos2 = cos(ToRadian(COLOR_DEGREE[2]));
	double sin2 = sin(ToRadian(COLOR_DEGREE[2]));
	double cos3 = cos(ToRadian(COLOR_DEGREE[3]));
	double sin3 = sin(ToRadian(COLOR_DEGREE[3]));
	double cos4 = cos(ToRadian(COLOR_DEGREE[4]));
	double sin4 = sin(ToRadian(COLOR_DEGREE[4]));
	double cos5 = cos(ToRadian(COLOR_DEGREE[5]));
	double sin5 = sin(ToRadian(COLOR_DEGREE[5]));
	line(img, Point(w2 + (c1 * cos0), h2 - (c1 * sin0)), Point(w2 + (c5 * cos0), h2 - (c5 * sin0)), color2, thickness, CV_AA); // Mg
	line(img, Point(w2 + (c1 * cos1), h2 - (c1 * sin1)), Point(w2 + (c5 * cos1), h2 - (c5 * sin1)), color2, thickness, CV_AA); // R
	line(img, Point(w2 + (c1 * cos2), h2 - (c1 * sin2)), Point(w2 + (c5 * cos2), h2 - (c5 * sin2)), color2, thickness, CV_AA); // Y
	line(img, Point(w2 + (c1 * cos3), h2 - (c1 * sin3)), Point(w2 + (c5 * cos3), h2 - (c5 * sin3)), color2, thickness, CV_AA); // G
	line(img, Point(w2 + (c1 * cos4), h2 - (c1 * sin4)), Point(w2 + (c5 * cos4), h2 - (c5 * sin4)), color2, thickness, CV_AA); // Cy
	line(img, Point(w2 + (c1 * cos5), h2 - (c1 * sin5)), Point(w2 + (c5 * cos5), h2 - (c5 * sin5)), color2, thickness, CV_AA); // B
#endif

	float dRadian;
	int x, y;
	for (int i = 0; i < VECTORSCOPE_COLOR_POINT; i++) {
		dRadian = ToRadian(-COLOR_DEGREE[i]);
		x = (int)(COLOR_SCALE[i] * w2 * cos(dRadian));
		y = (int)(COLOR_SCALE[i] * h2 * sin(dRadian));

		// 평행이동
		x += w2;
		y += h2;

		// 사각형
		Rect rc(x - 3, y - 3, 6, 6);
		rectangle(img, rc, color, thickness);

		if (cos(dRadian) < 0)	putText(img, COLOR_NAME[i], Point(x - 6, y - 6), FONT_HERSHEY_SIMPLEX, 0.4, color, thickness, CV_AA);
		else					putText(img, COLOR_NAME[i], Point(x + 6, y + 3), FONT_HERSHEY_SIMPLEX, 0.4, color, thickness, CV_AA);
	}

	return img;
}

const string WAVE_GRAD[WAVE_GRADATION_POINT] = { "225", "200", "175", "150", "125", "100", "75", "50", "25" };
#define L_DEPTH 25
// ====================================================================================================
// drawBackgroundWaveform
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
Mat drawBackgroundWaveform(Mat img){
	Scalar color(0, 128, 255, 100); //RGB(255, 128, 0)
	int thickness = 1;
	for (int i = 0; i<WAVE_GRADATION_POINT; i++){
		// line
		line(img, Point(WAVEFORM_INTERVAL_WIDTH, 30 + L_DEPTH * i), Point(WAVEFORM_BACKGROUND_WIDTH - WAVEFORM_INTERVAL_WIDTH, 30 + L_DEPTH * i), color, thickness);
		// Text
		if (i < 6)	putText(img, WAVE_GRAD[i], Point(1, 30 + L_DEPTH * i - 6), FONT_HERSHEY_SIMPLEX, 0.3, color, thickness);
		else		putText(img, WAVE_GRAD[i], Point(7, 30 + L_DEPTH * i - 6), FONT_HERSHEY_SIMPLEX, 0.3, color, thickness);
		putText(img, WAVE_GRAD[i], Point(WAVEFORM_BACKGROUND_WIDTH - WAVEFORM_INTERVAL_WIDTH + 1, 30 + L_DEPTH * i - 6), FONT_HERSHEY_SIMPLEX, 0.3, color, thickness);
	}
	return img;
}

// ====================================================================================================
// DisplayImageDlg
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void DisplayImageDlg(Mat src)
{
	IplImage* targetIplImage = new IplImage(src);

	if (targetIplImage != nullptr){
		CDC* pDC = pAnalyzeSourceimage->m_Pic_Sourceimage.GetWindowDC();
		CRect rcImageTraget;
		pAnalyzeSourceimage->m_Pic_Sourceimage.GetWindowRect(&rcImageTraget);

		BITMAPINFO bitmapInfo;
		memset(&bitmapInfo, 0, sizeof(bitmapInfo));
		bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bitmapInfo.bmiHeader.biPlanes = 1;
		bitmapInfo.bmiHeader.biCompression = BI_RGB;
		bitmapInfo.bmiHeader.biWidth = targetIplImage->width;
		bitmapInfo.bmiHeader.biHeight = -targetIplImage->height;

		IplImage *tempImage = nullptr;

		if (targetIplImage->nChannels == 1)
		{
			tempImage = cvCreateImage(cvSize(targetIplImage->width, targetIplImage->height), IPL_DEPTH_8U, 3);
			cvCvtColor(targetIplImage, tempImage, CV_GRAY2BGR);
		}
		else if (targetIplImage->nChannels == 3)
		{
			tempImage = cvCloneImage(targetIplImage);
		}

		bitmapInfo.bmiHeader.biBitCount = tempImage->depth * tempImage->nChannels;

		CDC dcImage;
		dcImage.CreateCompatibleDC(pDC);
		CBitmap* pOldBitmap = (CBitmap*)dcImage.SelectObject(pAnalyzeSourceimage->m_bmpImage);

		dcImage.SetStretchBltMode(COLORONCOLOR);
		StretchDIBits(dcImage.GetSafeHdc(), 0, 0, rcImageTraget.Width(), rcImageTraget.Height(),
			0, 0, tempImage->width, tempImage->height, tempImage->imageData, &bitmapInfo, DIB_RGB_COLORS, SRCCOPY);

		cvReleaseImage(&tempImage);
		dcImage.SelectObject(pOldBitmap);
		pAnalyzeSourceimage->m_Pic_Sourceimage.ReleaseDC(pDC);

		pAnalyzeSourceimage->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_NOERASE);
	}

	delete targetIplImage;
}

Mat dst;
Mat img_filp_r;
Mat img_filp_g;
Mat img_filp_b;
Mat img_flip_y;
// ====================================================================================================
// CAnalyzeDlg::RunAnalyze
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CAnalyzeDlg::RunAnalyze()
{
	CWaveformImgOperation vec;
	Mat matJpg2(1, READ_JTAG_SIZE, CV_8UC1);
	Mat src;
	Mat yuv;
	Mat calImg; // 계산용 이미지, 1280*720
	Mat ch_yuv[3];
	Mat ch_bgr[3];
	Mat img(BIT_FREQUENCY, BIT_FREQUENCY, CV_8UC3);
//	Mat dst;
	Mat img_filp;
//	Mat img_filp_r;
//	Mat img_filp_g;
//	Mat img_filp_b;
//	Mat img_flip_y;
	Mat wimg_r(WAVEFORM_HEIGHT, WAVEFORM_WIDTH, CV_8UC4);
	Mat wimg_g(WAVEFORM_HEIGHT, WAVEFORM_WIDTH, CV_8UC4);
	Mat wimg_b(WAVEFORM_HEIGHT, WAVEFORM_WIDTH, CV_8UC4);
	Mat wimg_y(WAVEFORM_HEIGHT, WAVEFORM_WIDTH, CV_8UC4);
	Mat cur;

	char recvbuf[DEFAULT_BUFLEN];
	int iResult;
	UINT32 size = 0;
	char* buf = NULL;

	// Initial Stop Analyze
	m_bStopAnalyze = FALSE;
	pAnalyzeSourceimage->m_Btn_Play.SetWindowTextW(_T("■"));

	// Show Dialog
	pAnalyzeSourceimage->ShowWindow(SW_SHOW);
	pAnalyzeSourceimage->RedrawWindow();

	while (1) {
		//Sleep(1);
		// Sleep 막으니까 Vectorsope, Wavefrom 이동시 멈추는 현상 해결

		//if (memblock != NULL) { free(memblock); memblock = NULL; }

		if (!m_bRunAnalyze) {
			break;
		}

#if 0
		if (m_bStopAnalyze) {
			cv::waitKey(1);
			DisplayImageDlg(cur);
			continue;
		}
#endif

		while (pAnalyzeSourceimage->m_bCaptureOne) { Sleep(1); }


		size = 0;
		iResult = recv(ConnectSocket, recvbuf, DEFAULT_BUFLEN, 0);
		//printf("iResult %d", iResult);
		if (iResult > 0)
		{
			if (iResult < DEFAULT_BUFLEN){
				recvbuf[iResult] = '\0';
				if ((recvbuf[0] == 's' && recvbuf[1] == 'i' && recvbuf[2] == 'z' && recvbuf[3] == 'e')){
					size = atoi((char*)recvbuf + 4);
					//	printf("%s", recvbuf);
				}
			}
		}
		else
		{
			AfxMessageBox(_T("Recv Error"));
			goto END;
		}

		if (size > 0){
			buf = (char*)malloc(size);
			UINT a;
			for (a = 0; a < size;){
				iResult = recv(ConnectSocket, buf + a, size - a, 0);
				if (iResult < 0){
					printf("Error\n");
					goto END;
				}
				a += iResult;
				//	printf("recv %d\n", a);

			}

			if (m_bStopAnalyze) {
				cv::waitKey(1);
				DisplayImageDlg(cur);
				continue;
			}

			//	addNode(buf, size);
			memcpy(matJpg2.data, buf, size);
			src = imdecode(matJpg2, 1);
			if (src.data == NULL) continue;

			pAnalyzeSourceimage->m_iImageWidth = src.cols;
			pAnalyzeSourceimage->m_iImageHeight = src.rows;
			pAnalyzeSourceimage->m_iImagedataSize = size + 4;

			if (pAnalyzeSourceimage->m_uiImagedata != NULL)
				delete[] pAnalyzeSourceimage->m_uiImagedata;
			pAnalyzeSourceimage->m_uiImagedata = new uchar[size + 4];
			memcpy(pAnalyzeSourceimage->m_uiImagedata, matJpg2.data, size + 4);

			//if (pAnalyzeSourceimage->m_bCapture) pAnalyzeSourceimage->SaveSourceimage();

			resize(src, calImg, Size(1280, 720));

			/////////////////////////////
			cvtColor(calImg, yuv, COLOR_BGR2YCrCb);
			split(yuv, ch_yuv);
			split(calImg, ch_bgr);

			if (m_Chk_Vectorscope.GetCheck())
			{
				vec.InitWaveformDraw(calImg.cols, calImg.rows);
				if (ch_yuv[2].data == NULL) continue;
				if (ch_yuv[1].data == NULL) continue;
				BYTE *pVectorImage = vec.GetVectorScope(ch_yuv[2].data, ch_yuv[1].data, calImg.cols, calImg.rows, 1);

				img.data = pVectorImage;

				flip(img, img_filp, 0);// vertical flip

				resize(img_filp, dst, Size(VECTORSCOPE_BACKGROUND_WIDTH * (1.5), VECTORSCOPE_BACKGROUND_HEIGHT * (1.5)));

				// Vectorscope
				drawBackgroundVectorscope(dst, VECTORSCOPE_BACKGROUND_WIDTH * (1.5), VECTORSCOPE_BACKGROUND_WIDTH * (1.5));
				imshow("Vectorscope", dst);
				//if (m_Chk_Vectorscope.GetCheck())	imshow("Vectorscope", dst);
			}
			else							destroyWindow("Vectorscope");

			// Waveform Red
			if (ch_bgr[2].data == NULL) continue;
			if (m_Chk_WaveformR.GetCheck())
			{
				BYTE *pWaveformImage_r = vec.GetWaveform(ch_bgr[2].data, calImg.cols, calImg.rows, 1, 2);
				wimg_r.data = pWaveformImage_r;
				flip(wimg_r, img_filp_r, 0);
				drawBackgroundWaveform(img_filp_r);
				imshow("Red", img_filp_r);
			}
			//if (m_Chk_WaveformR.GetCheck())	imshow("Red", img_filp_r);
			else							destroyWindow("Red");


			// Waveform Green
			if (ch_bgr[1].data == NULL) continue;
			if (m_Chk_WaveformG.GetCheck())
			{
				BYTE *pWaveformImage_g = vec.GetWaveform(ch_bgr[1].data, calImg.cols, calImg.rows, 1, 1);
				wimg_g.data = pWaveformImage_g;
				flip(wimg_g, img_filp_g, 0);
				drawBackgroundWaveform(img_filp_g);
				imshow("Green", img_filp_g);
			}
			//if (m_Chk_WaveformG.GetCheck())	imshow("Green", img_filp_g);
			else							destroyWindow("Green");

			// Waveform Blue
			if (ch_bgr[0].data == NULL) continue;
			if (m_Chk_WaveformB.GetCheck())
			{
				BYTE *pWaveformImage_b = vec.GetWaveform(ch_bgr[0].data, calImg.cols, calImg.rows, 1, 0);
				wimg_b.data = pWaveformImage_b;
				flip(wimg_b, img_filp_b, 0);
				drawBackgroundWaveform(img_filp_b);
				imshow("Blue", img_filp_b);
			}
			//if (m_Chk_WaveformB.GetCheck())	imshow("Blue", img_filp_b);
			else							destroyWindow("Blue");

			// Waveform Y
			if (ch_yuv[0].data == NULL) continue;
			if (m_Chk_WaveformY.GetCheck())
			{
				BYTE *pWaveformImage_y = vec.GetWaveform(ch_yuv[0].data, calImg.cols, calImg.rows, 1, 3);
				wimg_y.data = pWaveformImage_y;
				flip(wimg_y, img_flip_y, 0);
				drawBackgroundWaveform(img_flip_y);
				imshow("Y", img_flip_y);
			}
			//if (m_Chk_WaveformY.GetCheck())	imshow("Y", img_flip_y);
			else							destroyWindow("Y");

		
			Mat gray_image;
			cvtColor(src, gray_image, CV_BGR2GRAY);
			Mat athimage;
			adaptiveThreshold(gray_image, athimage, 255,ADAPTIVE_THRESH_MEAN_C,THRESH_BINARY, 11, 7);


			DisplayImageDlg(src);
			cur = src;
			cv::waitKey(1);
				
			// Capture 
			// Vectorscope, Waveform 저장을 위해서 저장하는 위치는 끝으로 이동시킴
			if (pAnalyzeSourceimage->m_bCapture) pAnalyzeSourceimage->SaveSourceimage();

			free(buf);
			Sleep(1);
		}
		else
		{
			printf("iResult %d", iResult);
		}
	}
END:
	// Destroy Window
	destroyAllWindows();
	pAnalyzeSourceimage->ShowWindow(SW_HIDE);

	ReadImageKill();
	Sleep(10);
	NetClo(ConnectSocket);
	ConnectSocket = NULL;
}


// ====================================================================================================
// CAnalyzeDlg::RunEndAnalyzeThread
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CAnalyzeDlg::RunEndAnalyzeThread()
{
	// Run Vectorscope Thread
	AfxBeginThread(EndAnalyzeThread, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);

	m_Btn_PlayAnalyze.EnableWindow(FALSE);

}


// ====================================================================================================
// EndAnalyzeThread
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
UINT EndAnalyzeThread(LPVOID pParam)
{
	pAnalyzeDlg->m_bRunAnalyze = FALSE;

	// Wait
	while (bRunAnalyzeThread) { Sleep(1); }

	ReadImageKill();
	NetClo(ConnectSocket);
	ConnectSocket = NULL;


	// Change Button
	pAnalyzeDlg->m_Btn_PlayAnalyze.SetWindowTextW(_T("Play"));
	pAnalyzeDlg->m_Btn_PlayAnalyze.EnableWindow(TRUE);

	return 0;
}


void CAnalyzeDlg::SaveSubimage(CString strDirectory, CString strJpgTime)
{
	// Vectorscope, Waveform Capture
	if (pAnalyzeSourceimage->m_Chk_Capture.GetCheck())
	{
		CString strSubJpgPath = _T("");
		// Vectorscope
		if (pAnalyzeDlg->m_Chk_Vectorscope.GetCheck())
		{
			strSubJpgPath.Format(_T("%s\\ecm_vectorscope_%s.jpg"), strDirectory, strJpgTime);
			CT2CA pszConvertedAnsiString(strSubJpgPath);
			std::string s(pszConvertedAnsiString);
			imwrite(s, dst);
		}
		// Waveform (Red)
		if (pAnalyzeDlg->m_Chk_WaveformR.GetCheck())
		{
			strSubJpgPath.Format(_T("%s\\ecm_waveform_red_%s.jpg"), strDirectory, strJpgTime);
			CT2CA pszConvertedAnsiString(strSubJpgPath);
			std::string s(pszConvertedAnsiString);
			imwrite(s, img_filp_r);
		}
		// Waveform (Green)
		if (pAnalyzeDlg->m_Chk_WaveformG.GetCheck())
		{
			strSubJpgPath.Format(_T("%s\\ecm_waveform_green_%s.jpg"), strDirectory, strJpgTime);
			CT2CA pszConvertedAnsiString(strSubJpgPath);
			std::string s(pszConvertedAnsiString);
			imwrite(s, img_filp_g);
		}
		// Waveform (Blue)
		if (pAnalyzeDlg->m_Chk_WaveformB.GetCheck())
		{
			strSubJpgPath.Format(_T("%s\\ecm_waveform_blue_%s.jpg"), strDirectory, strJpgTime);
			CT2CA pszConvertedAnsiString(strSubJpgPath);
			std::string s(pszConvertedAnsiString);
			imwrite(s, img_filp_b);
		}
		// Waveform (Y)
		if (pAnalyzeDlg->m_Chk_WaveformY.GetCheck())
		{
			strSubJpgPath.Format(_T("%s\\ecm_waveform_y_%s.jpg"), strDirectory, strJpgTime);
			CT2CA pszConvertedAnsiString(strSubJpgPath);
			std::string s(pszConvertedAnsiString);
			imwrite(s, img_flip_y);
		}
	}
}

void CAnalyzeDlg::SaveValue()
{
	// Vectorscope
	WriteIni(SEC_ANALYZE, KEY_VECTORSCOPE, m_Chk_Vectorscope.GetCheck());
	// WaveformR
	WriteIni(SEC_ANALYZE, KEY_WAVEFORM_R, m_Chk_WaveformR.GetCheck());
	// WaveformG
	WriteIni(SEC_ANALYZE, KEY_WAVEFORM_G, m_Chk_WaveformG.GetCheck());
	// WaveformB
	WriteIni(SEC_ANALYZE, KEY_WAVEFORM_B, m_Chk_WaveformB.GetCheck());
	// WaveformY
	WriteIni(SEC_ANALYZE, KEY_WAVEFORM_Y, m_Chk_WaveformY.GetCheck());
	// Capture
	WriteIni(SEC_ANALYZE, KEY_CAPTURE, pAnalyzeSourceimage->m_Chk_Capture.GetCheck());
}

void CAnalyzeDlg::OnBnClickedCheckVectorscope()
{
	// Vectorscope
	WriteIni(SEC_ANALYZE, KEY_VECTORSCOPE, m_Chk_Vectorscope.GetCheck());
}


void CAnalyzeDlg::OnBnClickedCheckWaveformr()
{
	// WaveformR
	WriteIni(SEC_ANALYZE, KEY_WAVEFORM_R, m_Chk_WaveformR.GetCheck());
}


void CAnalyzeDlg::OnBnClickedCheckWaveformg()
{
	// WaveformG
	WriteIni(SEC_ANALYZE, KEY_WAVEFORM_G, m_Chk_WaveformG.GetCheck());
}


void CAnalyzeDlg::OnBnClickedCheckWaveformb()
{
	// WaveformB
	WriteIni(SEC_ANALYZE, KEY_WAVEFORM_B, m_Chk_WaveformB.GetCheck());
}


void CAnalyzeDlg::OnBnClickedCheckWaveformy()
{
	// WaveformY
	WriteIni(SEC_ANALYZE, KEY_WAVEFORM_Y, m_Chk_WaveformY.GetCheck());
}

