// AnalyzeSourceimage.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Analyze.h"
#include "AnalyzeSourceimage.h"
#include "afxdialogex.h"

#include <opencv\cv.h>

#include "AnalyzeDlg.h"
#include "Net_command.h"

#pragma warning(disable:4996)

#define WINDOW_SPACE_TOP		29
#define WINDOW_SPACE			4
#define WINDOW_SPACE_WIDTH		24
#define WINDOW_SPACE_HEIGHT		70
#define ANALYZE_SIZE_WIDTH_MIN	320
#define ANALYZE_SIZE_HEIGHT_MIN	240
#define ANALYZE_SIZE_WIDTH_MAX	1920
#define ANALYZE_SIZE_HEIGHT_MAX	1080

UINT RunCapturePathThread(LPVOID pParam);

// CAnalyzeSourceimage 대화 상자입니다.

IMPLEMENT_DYNAMIC(CAnalyzeSourceimage, CDialogEx)

CAnalyzeSourceimage::CAnalyzeSourceimage(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAnalyzeSourceimage::IDD, pParent)
{
	m_bmpImage = NULL;
	m_uiImagedata = NULL;
	m_iImageWidth = 0;
	m_iImageHeight = 0;
	m_iImagedataSize = 0;
	m_bCapture = FALSE;
	m_bCaptureOne = FALSE;
}

CAnalyzeSourceimage::~CAnalyzeSourceimage()
{
	if (m_bmpImage != NULL) delete[] m_bmpImage;
	//if (m_uiImagedata != NULL) delete[] m_uiImagedata;
}

void CAnalyzeSourceimage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_ANALYZE_PLAY, m_Btn_Play);
	DDX_Control(pDX, IDC_BUTTON_ANALYZE_CAPTUREONE, m_Btn_CaptureOne);
	DDX_Control(pDX, IDC_BUTTON_ANALYZE_CAPTURECON, m_Btn_CaptureCon);
	DDX_Control(pDX, IDC_BUTTON_ANALYZE_ORIGINALSIZE, m_Btn_OriginalSize);
	DDX_Control(pDX, IDC_STATIC_SOURCEIMAGE, m_Pic_Sourceimage);
	DDX_Control(pDX, IDC_CHECK_SUBIMAGE, m_Chk_Capture);
	DDX_Control(pDX, IDC_STATIC_CAPTUREPATH, m_Static_CapturePath);
	DDX_Control(pDX, IDC_BUTTON_OPENPATH, m_Btn_OpenPath);
}


BEGIN_MESSAGE_MAP(CAnalyzeSourceimage, CDialogEx)
	ON_WM_WINDOWPOSCHANGED()
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_ENTERSIZEMOVE()
	ON_WM_ERASEBKGND()
	ON_WM_SIZING()
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_ANALYZE_PLAY, &CAnalyzeSourceimage::OnBnClickedButtonAnalyzePlay)
	ON_BN_CLICKED(IDC_BUTTON_ANALYZE_CAPTUREONE, &CAnalyzeSourceimage::OnBnClickedButtonAnalyzeCaptureone)
	ON_BN_CLICKED(IDC_BUTTON_ANALYZE_CAPTURECON, &CAnalyzeSourceimage::OnBnClickedButtonAnalyzeCapturecon)
	ON_BN_CLICKED(IDC_BUTTON_ANALYZE_ORIGINALSIZE, &CAnalyzeSourceimage::OnBnClickedButtonAnalyzeOriginalsize)
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BUTTON_OPENPATH, &CAnalyzeSourceimage::OnBnClickedButtonOpenpath)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CAnalyzeSourceimage 메시지 처리기입니다.


BOOL CAnalyzeSourceimage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	pAnalyzeSourceimage = this;
	

	// Path Open
	m_Btn_OpenPath.SetBitmaps(IDB_OPEN, RGB(255, 0, 255));

// ----------------------------------------------------------------------------------------------------
	// m_Pic_Sourceimage
	CRect rectWindow;
	this->GetWindowRect(rectWindow);
	m_Pic_Sourceimage.SetWindowPos(NULL, WINDOW_SPACE, WINDOW_SPACE_TOP, rectWindow.Width() - WINDOW_SPACE_WIDTH, rectWindow.Height() - WINDOW_SPACE_HEIGHT, NULL);

// ----------------------------------------------------------------------------------------------------
	// m_bmpImage
	// 1. Initial
	CRect rectImage;
	m_Pic_Sourceimage.GetWindowRect(rectImage);
	int iImageWidth = ANALYZE_SIZE_WIDTH_MAX;
	int iImageHeight = ANALYZE_SIZE_HEIGHT_MAX;

	// Create DC
	CDC* pDC = m_Pic_Sourceimage.GetWindowDC();

	// Create Bitmap
	m_bmpImage = new CBitmap;
	m_bmpImage->CreateCompatibleBitmap(pDC, iImageWidth, iImageHeight);

	CDC dcImage;
	dcImage.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap = (CBitmap*)dcImage.SelectObject(m_bmpImage);

	// 2. Draw
	dcImage.FillSolidRect(0, 0, iImageWidth, iImageHeight, RGB(0xFF, 0xFF, 0xFF));

	// 3. Release
	dcImage.SelectObject(pOldBitmap);
	m_Pic_Sourceimage.ReleaseDC(pDC);

// ----------------------------------------------------------------------------------------------------
	int i = 0;
	// Capture
	i = ReadIni(SEC_ANALYZE, KEY_CAPTURE, DEF_CAPTURE);
	m_Chk_Capture.SetCheck(i);

	m_Static_CapturePath.EnableWindow(FALSE);
	m_Static_CapturePath.ShowWindow(SW_HIDE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL CAnalyzeSourceimage::PreTranslateMessage(MSG* pMsg)
{
	// Default Window Message
	if (DefaultWindowMessage(pMsg))	return TRUE;
	else							return CDialogEx::PreTranslateMessage(pMsg);
}


void CAnalyzeSourceimage::OnMouseMove(UINT nFlags, CPoint point)
{
	CDialogEx::OnMouseMove(nFlags, point);
}


void CAnalyzeSourceimage::OnSizing(UINT fwSide, LPRECT pRect)
{
	// 최저사이즈 : 320x240
	if ((pRect->right - pRect->left) < ANALYZE_SIZE_WIDTH_MIN + WINDOW_SPACE_WIDTH)  pRect->right = pRect->left + ANALYZE_SIZE_WIDTH_MIN + WINDOW_SPACE_WIDTH;
	if ((pRect->bottom - pRect->top) < ANALYZE_SIZE_HEIGHT_MIN + WINDOW_SPACE_HEIGHT) pRect->bottom = pRect->top + ANALYZE_SIZE_HEIGHT_MIN + WINDOW_SPACE_HEIGHT;
	// 최고사이즈 : 1920x1080
	if ((pRect->right - pRect->left) > ANALYZE_SIZE_WIDTH_MAX + WINDOW_SPACE_WIDTH)  pRect->right = pRect->left + ANALYZE_SIZE_WIDTH_MAX + WINDOW_SPACE_WIDTH;
	if ((pRect->bottom - pRect->top) > ANALYZE_SIZE_HEIGHT_MAX + WINDOW_SPACE_HEIGHT) pRect->bottom = pRect->top + ANALYZE_SIZE_HEIGHT_MAX + WINDOW_SPACE_HEIGHT;

	CRect rectWindow;
	GetWindowRect(rectWindow);
	m_Pic_Sourceimage.SetWindowPos(NULL, WINDOW_SPACE, WINDOW_SPACE_TOP, pRect->right - pRect->left - WINDOW_SPACE_WIDTH, pRect->bottom - pRect->top - WINDOW_SPACE_HEIGHT, NULL);

	RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_NOERASE);

	CDialogEx::OnSizing(fwSide, pRect);
}


void CAnalyzeSourceimage::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
	CDialogEx::OnWindowPosChanged(lpwndpos);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void CAnalyzeSourceimage::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	CDialogEx::OnWindowPosChanging(lpwndpos);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void CAnalyzeSourceimage::OnEnterSizeMove()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnEnterSizeMove();
}


BOOL CAnalyzeSourceimage::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CDialogEx::OnEraseBkgnd(pDC);
}


void CAnalyzeSourceimage::OnClose()
{
	pAnalyzeDlg->RunEndAnalyzeThread();
	
	return;
	//CDialogEx::OnClose();
}


void CAnalyzeSourceimage::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	// Draw Source Image
	CDC* pDC = m_Pic_Sourceimage.GetWindowDC();

	CDC dcSourceimage;
	dcSourceimage.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap = (CBitmap*)dcSourceimage.SelectObject(m_bmpImage);

	CRect rcSourceimage;
	pAnalyzeSourceimage->m_Pic_Sourceimage.GetWindowRect(&rcSourceimage);

	CRect rectPicture;
	m_Pic_Sourceimage.GetWindowRect(rectPicture);

	pDC->SetStretchBltMode(COLORONCOLOR);
	pDC->BitBlt(0, 0, m_iImageWidth, m_iImageHeight, &dcSourceimage, 0, 0, SRCCOPY);

	dcSourceimage.SelectObject(pOldBitmap);
	m_Pic_Sourceimage.ReleaseDC(pDC);
}


void CAnalyzeSourceimage::OnBnClickedButtonAnalyzePlay()
{
	if (!pAnalyzeDlg->m_bStopAnalyze) {
		pAnalyzeDlg->m_bStopAnalyze = TRUE;
		m_Btn_Play.SetWindowTextW(_T("▶"));
	}
	else {
		pAnalyzeDlg->m_bStopAnalyze = FALSE;
		m_Btn_Play.SetWindowTextW(_T("■"));
	}
}


void CAnalyzeSourceimage::OnBnClickedButtonAnalyzeCaptureone()
{
	m_bCaptureOne = TRUE;
	SaveSourceimage();
	m_bCaptureOne = FALSE;
}


void CAnalyzeSourceimage::SaveSourceimage()
{
	CString strJpgPath = _T("");
	CString strJpgTime = _T("");
	CString strDirectory = _T("");

	strDirectory = ReadIni(SEC_SETTING, KEY_ANALYZESAVEPATH, DEF_ANALYZESAVEPATH);

	// Ini 파일에 Path가 없는경우
	if (strDirectory == _T(""))
	{
		// Get 'My Document'
		TCHAR szPath[MAX_PATH];
		SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, 0, szPath);

		// Create ecm folder
		strDirectory.Format(_T("%s\\ecm_retome"), szPath);
		CreateDirectory(strDirectory, NULL);

		// Create Analyze folder
		strDirectory.Format(_T("%s\\ecm_retome\\analyze"), szPath);
		CreateDirectory(strDirectory, NULL);

		strJpgPath = strDirectory;
	}

	// 디렉토리 유무 확인
	if (GetFileAttributes(strDirectory) == -1)
	{
		CreateDirectory(strDirectory, NULL);
	}

	// Get Time
	SYSTEMTIME time;
	GetLocalTime(&time);

	strJpgTime.Format(_T("%04d%02d%02d%02d%02d%02d%03d"), time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
	strJpgPath.Format(_T("%s\\ecm_sourceimage_%s.jpg"), strDirectory, strJpgTime);

	//strJpgPath.Format(_T("%s\\ecm_sourceimage_%04d%02d%02d%02d%02d%02d%03d.jpg"), strDirectory,
	//	time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);

	// Waveform Save
	if (m_Chk_Capture.GetCheck())	pAnalyzeDlg->SaveSubimage(strDirectory, strJpgTime);

	// Save
	// Create File
	CFile fileJpg;
	fileJpg.Open(strJpgPath, CFile::typeBinary | CFile::modeCreate | CFile::modeWrite);
	fileJpg.Write(m_uiImagedata, m_iImagedataSize);
	fileJpg.Close();

	AfxBeginThread(RunCapturePathThread, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
}


UINT RunCapturePathThread(LPVOID pParam)
{
	pAnalyzeSourceimage->m_Static_CapturePath.EnableWindow(TRUE);
	pAnalyzeSourceimage->m_Static_CapturePath.ShowWindow(SW_SHOW);

	CString str;

	str = _T("Capture Complete");

	pAnalyzeSourceimage->m_Static_CapturePath.SetWindowTextW(str);

	Sleep(5000);

	pAnalyzeSourceimage->m_Static_CapturePath.EnableWindow(FALSE);
	pAnalyzeSourceimage->m_Static_CapturePath.ShowWindow(SW_HIDE);

	return 0;
}


void CAnalyzeSourceimage::OnBnClickedButtonAnalyzeCapturecon()
{
	if (m_bCapture) {
		m_bCapture = FALSE;
		m_Btn_CaptureCon.SetWindowTextW(_T("Continuity Capture"));
	}
	else {
		m_bCapture = TRUE;
		m_Btn_CaptureCon.SetWindowTextW(_T("Stop Capture"));
	}
}


void CAnalyzeSourceimage::OnBnClickedButtonAnalyzeOriginalsize()
{
	// Window
	SetWindowPos(NULL, 0, 0, m_iImageWidth + WINDOW_SPACE_WIDTH, m_iImageHeight + WINDOW_SPACE_HEIGHT, SWP_NOMOVE);

	m_Pic_Sourceimage.SetWindowPos(NULL, WINDOW_SPACE, WINDOW_SPACE_TOP, m_iImageWidth, m_iImageHeight, NULL);
}


void CAnalyzeSourceimage::OnBnClickedButtonOpenpath()
{
	CString strPath;
	strPath = ReadIni(SEC_SETTING, KEY_ANALYZESAVEPATH, DEF_ANALYZESAVEPATH);

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
		strDirectory.Format(_T("%s\\ecm_retome\\analyze"), szPath);
		CreateDirectory(strDirectory, NULL);

		strPath = strDirectory;
	}

	strPath.Format(_T("%s\\"), strPath);

	ShellExecute(NULL, _T("open"), _T("explorer"), strPath, NULL, SW_SHOW);
}


HBRUSH CAnalyzeSourceimage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (pWnd->GetDlgCtrlID() == IDC_STATIC_CAPTUREPATH)
	{
		pDC->SetTextColor(RGB(255, 0, 0));
	}

	return hbr;
}
