// DownCompileOption673.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Downloader.h"
#include "DownCompileOption673.h"
#include "afxdialogex.h"


// CDownCompileOption673 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDownCompileOption673, CDialogEx)

CDownCompileOption673::CDownCompileOption673(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDownCompileOption673::IDD, pParent)
{

}

CDownCompileOption673::~CDownCompileOption673()
{
}

void CDownCompileOption673::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_673_OPTION_COMPILE, m_Cbo_Compile);
	DDX_Control(pDX, IDC_COMBO_673_OPTION_MODE, m_Cbo_Mode);
	DDX_Control(pDX, IDC_CHECK_673_OPTION_DIS, m_Chk_Disassemble);
	DDX_Control(pDX, IDC_CHECK_673_OPTION_SECTIONWRITEBOOT, m_Chk_SectionWriteBoot);
	DDX_Control(pDX, IDC_CHECK_673_OPTION_ETHERNET, m_Chk_Ethernet);
	DDX_Control(pDX, IDC_CHECK_673_OPTION_WIFI, m_Chk_WiFi);
	DDX_Control(pDX, IDC_CHECK_673_OPTION_ACTIVEX, m_Chk_ActiveX);
	DDX_Control(pDX, IDC_CHECK_673_OPTION_ONVIF, m_Chk_Onvif);
	DDX_Control(pDX, IDC_EDIT_COMPILEOPTION, m_Edit_CompileOption);
	DDX_Control(pDX, IDC_EDIT_APPLICATIONOPTION, m_Edit_ApplicationOption);
	DDX_Control(pDX, IDC_EDIT_CONFIGGEN, m_Edit_ConfigGen);
	DDX_Control(pDX, IDC_EDIT_CUSTOMOPTION, m_Edit_CustomOption);
	DDX_Control(pDX, IDC_BUTTON_CONFIGGEN, m_Btn_ConfigGen);
}


BEGIN_MESSAGE_MAP(CDownCompileOption673, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_673_OPTION_COMPILE, &CDownCompileOption673::OnCbnSelchangeCombo673OptionCompile)
	ON_CBN_SELCHANGE(IDC_COMBO_673_OPTION_MODE, &CDownCompileOption673::OnCbnSelchangeCombo673OptionMode)
	ON_BN_CLICKED(IDC_CHECK_673_OPTION_ETHERNET, &CDownCompileOption673::OnBnClickedCheck673OptionEthernet)
	ON_BN_CLICKED(IDC_CHECK_673_OPTION_WIFI, &CDownCompileOption673::OnBnClickedCheck673OptionWifi)
	ON_BN_CLICKED(IDC_CHECK_673_OPTION_ACTIVEX, &CDownCompileOption673::OnBnClickedCheck673OptionActivex)
	ON_BN_CLICKED(IDC_CHECK_673_OPTION_ONVIF, &CDownCompileOption673::OnBnClickedCheck673OptionOnvif)
	ON_BN_CLICKED(IDC_CHECK_673_OPTION_DIS, &CDownCompileOption673::OnBnClickedCheck673OptionDis)
	ON_BN_CLICKED(IDC_CHECK_673_OPTION_SECTIONWRITEBOOT, &CDownCompileOption673::OnBnClickedCheck673OptionSectionwriteboot)
	ON_WM_VSCROLL()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_CONFIGGEN, &CDownCompileOption673::OnBnClickedButtonConfiggen)
	ON_WM_MOUSEWHEEL()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CDownCompileOption673 메시지 처리기입니다.


BOOL CDownCompileOption673::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	pDownCompileOption673 = this;

	int i = 0;
	int j = 0;
	int iCnt = 0;

	// Initial Control
	// Compile
	// Insert String
	for (i = 0; i < NUM_673BUILDOPTION_COMPILE; i++)	m_Cbo_Compile.InsertString(i, CBO_673BUILDOPTION_COMPILE[i]);
	// Select
	i = ReadIni(SEC_DOWN, KEY_673BUILDOPTION_COMPILE, DEF_673BUILDOPTION_COMPILE);
	if (i >= NUM_673BUILDOPTION_COMPILE) i = NUM_673BUILDOPTION_COMPILE;
	m_Cbo_Compile.SetCurSel(i);

	// Mode
	// Insert String
	for (i = 0; i < NUM_673BUILDOPTION_MODE; i++)	m_Cbo_Mode.InsertString(i, CBO_673BUILDOPTION_MODE[i]);
	// Select
	i = ReadIni(SEC_DOWN, KEY_673BUILDOPTION_MODE, DEF_673BUILDOPTION_MODE);
	if (i >= NUM_673BUILDOPTION_MODE) i = NUM_673BUILDOPTION_MODE;
	m_Cbo_Mode.SetCurSel(i);

	// Disassemble
	i = ReadIni(SEC_DOWN, KEY_673BUILDOPTION_DISASSEMBLE, DEF_673BUILDOPTION_DISASSEMBLE);
	m_Chk_Disassemble.SetCheck(i);
	// Section
	i = ReadIni(SEC_DOWN, KEY_673BUILDOPTION_SECTION, DEF_673BUILDOPTION_SECTION);
	m_Chk_SectionWriteBoot.SetCheck(i);
	// Ethernet
	i = ReadIni(SEC_DOWN, KEY_673BUILDOPTION_ETHERNET, DEF_673BUILDOPTION_ETHERNET);
	m_Chk_Ethernet.SetCheck(i);
	// Wi-Fi
	i = ReadIni(SEC_DOWN, KEY_673BUILDOPTION_WIFI, DEF_673BUILDOPTION_WIFI);
	m_Chk_WiFi.SetCheck(i);
	// ONVIF
	i = ReadIni(SEC_DOWN, KEY_673BUILDOPTION_ONVIF, DEF_673BUILDOPTION_ONVIF);
	m_Chk_Onvif.SetCheck(i);
	// ActiveX
	i = ReadIni(SEC_DOWN, KEY_673BUILDOPTION_ACTIVEX, DEF_673BUILDOPTION_ACTIVEX);
	m_Chk_ActiveX.SetCheck(i);

	ChangeOption();

	GetWindowRect(m_rcOriginalRect);

	// initial scroll position
	m_nScrollPos = 0;

// ----------------------------------------------------------------------------------------------------
// Create Sub Dialog
	m_pCEN673_Configuration_GeneratorDlg = new CEN673_Configuration_GeneratorDlg();
	m_pCEN673_Configuration_GeneratorDlg->Create(IDD_EN673_CONFIGURATION_GENERATOR_DIALOG, this);
	m_pCEN673_Configuration_GeneratorDlg->SetWindowPos(NULL, m_rcOriginalRect.right, m_rcOriginalRect.top, 0, 0, SWP_SHOWWINDOW | SWP_NOZORDER | SWP_NOSIZE);

	m_pCEN673_Configuration_GeneratorDlg->ShowWindow(SW_HIDE);
	m_ShowDlg_ConfigGen = FALSE;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL CDownCompileOption673::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

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
				if (wndFocus == NULL) return FALSE;
				if (wndFocus == (CWnd*)&m_Edit_CompileOption) {
					m_Edit_CompileOption.SetSel(0, m_Edit_CompileOption.GetWindowTextLengthW());
					return TRUE;
				}
				break;
			}
		}
	}

	// Default Window Message
	if (DefaultWindowMessage(pMsg))	return TRUE;
	else							return CDialog::PreTranslateMessage(pMsg);
}


void CDownCompileOption673::OnCbnSelchangeCombo673OptionCompile()		{ ChangeOption(); }
void CDownCompileOption673::OnCbnSelchangeCombo673OptionMode()			{ ChangeOption(); }
void CDownCompileOption673::OnBnClickedCheck673OptionEthernet()			{ ChangeOption(); }
void CDownCompileOption673::OnBnClickedCheck673OptionWifi()				{ ChangeOption(); }
void CDownCompileOption673::OnBnClickedCheck673OptionActivex()			{ ChangeOption(); }
void CDownCompileOption673::OnBnClickedCheck673OptionOnvif()			{ ChangeOption(); }
void CDownCompileOption673::OnBnClickedCheck673OptionDis()				{ ChangeOption(); }
void CDownCompileOption673::OnBnClickedCheck673OptionSectionwriteboot()	{ ChangeOption(); }


// ====================================================================================================
// CDownCompileOption673::ChangeOption
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CDownCompileOption673::ChangeOption()
{
	int i = 0;
	CString strCommand = _T("");
	CString strAppCommand = _T("");

	// Make
	i = m_Cbo_Compile.GetCurSel();
	if (i == 0) { strCommand = _T("make"); }
	else if (i == 1) { strCommand = _T("make boot"); }
	else if (i == 2) { strCommand = _T("make cpu0"); }
	else if (i == 3) { strCommand = _T("make cpu1"); }
	else if (i == 4) { strCommand = _T("make install PLATFORM=windows"); goto ENDCHANGEOPTION; }
	else if (i == 5) { strCommand = _T("make clean PLATFORM=windows"); goto ENDCHANGEOPTION; }
	else            { goto ENDCHANGEOPTION; } // None

	// Platform
	strCommand = strCommand + _T(" PLATFORM=windows");

	// Mode
	i = m_Cbo_Mode.GetCurSel();
	if (i == 1) { strCommand = strCommand + _T(" MODE=debug"); }
	else if (i == 2) { strCommand = strCommand + _T(" MODE=trace"); }
	else            { strCommand = strCommand + _T(" MODE=release"); }

	// Application Option
	if (m_Chk_Ethernet.GetCheck()) strAppCommand = strAppCommand + _T(" CONFIG_ETH_SUPPORT=y");
	if (m_Chk_WiFi.GetCheck())     strAppCommand = strAppCommand + _T(" CONFIG_WIFI_SUPPORT=y");
	if (m_Chk_Onvif.GetCheck())    strAppCommand = strAppCommand + _T(" CONFIG_ONVIF_SUPPORT=y");
	if (m_Chk_ActiveX.GetCheck())  strAppCommand = strAppCommand + _T(" CONFIG_ACTIVEX_SUPPORT=y");

	// Compile Option
	if (m_Chk_Disassemble.GetCheck())		strCommand = strCommand + _T(" COMPILE_DIS=y");
	if (m_Chk_SectionWriteBoot.GetCheck())	strCommand = strCommand + _T(" SECTION=y");

ENDCHANGEOPTION:
	m_Edit_CompileOption.SetWindowTextW(strCommand);
	m_Edit_ApplicationOption.SetWindowTextW(strAppCommand);
}


void CDownCompileOption673::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int nDelta;
	int nMaxPos = m_rcOriginalRect.Height() - m_nCurHeight;

	switch (nSBCode)
	{
	case SB_LINEDOWN:
		if (m_nScrollPos >= nMaxPos)
			return;

		nDelta = min(max(nMaxPos / 20, 5), nMaxPos - m_nScrollPos);
		break;

	case SB_LINEUP:
		if (m_nScrollPos <= 0)
			return;
		nDelta = -min(max(nMaxPos / 20, 5), m_nScrollPos);
		break;
	case SB_PAGEDOWN:
		if (m_nScrollPos >= nMaxPos)
			return;
		nDelta = min(max(nMaxPos / 10, 5), nMaxPos - m_nScrollPos);
		break;
	case SB_THUMBTRACK:
	case SB_THUMBPOSITION:
		nDelta = (int)nPos - m_nScrollPos;
		break;

	case SB_PAGEUP:
		if (m_nScrollPos <= 0)
			return;
		nDelta = -min(max(nMaxPos / 10, 5), m_nScrollPos);
		break;

	default:
		return;
	}
	m_nScrollPos += nDelta;
	SetScrollPos(SB_VERT, m_nScrollPos, TRUE);
	ScrollWindow(0, -nDelta);

	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}


void CDownCompileOption673::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	m_nCurHeight = cy;

	SCROLLINFO si;
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_ALL;
	si.nMin = 0;
	si.nMax = m_rcOriginalRect.Height();
	si.nPage = cy;
	si.nPos = 0;
	SetScrollInfo(SB_VERT, &si, TRUE);
}


void CDownCompileOption673::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_bDragging = TRUE;
	SetCapture();
	m_ptDragPoint = point;

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CDownCompileOption673::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_bDragging)
	{
		int nDelta = m_ptDragPoint.y - point.y;
		m_ptDragPoint = point;

		int nNewPos = m_nScrollPos + nDelta;

		if (nNewPos<0)
			nNewPos = 0;
		else if (nNewPos>m_rcOriginalRect.Height() - m_nCurHeight)
			nNewPos = m_rcOriginalRect.Height() - m_nCurHeight;

		nDelta = nNewPos - m_nScrollPos;
		m_nScrollPos = nNewPos;

		SetScrollPos(SB_VERT, m_nScrollPos, TRUE);
		ScrollWindow(0, -nDelta);
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


BOOL CDownCompileOption673::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	int nMaxPos = m_rcOriginalRect.Height() - m_nCurHeight;

	if (zDelta<0)
	{
		if (m_nScrollPos < nMaxPos)
		{
			zDelta = min(max(nMaxPos / 20, 5), nMaxPos - m_nScrollPos);

			m_nScrollPos += zDelta;
			SetScrollPos(SB_VERT, m_nScrollPos, TRUE);
			ScrollWindow(0, -zDelta);
		}
	}
	else
	{
		if (m_nScrollPos > 0)
		{
			zDelta = -min(max(nMaxPos / 20, 5), m_nScrollPos);

			m_nScrollPos += zDelta;
			SetScrollPos(SB_VERT, m_nScrollPos, TRUE);
			ScrollWindow(0, -zDelta);
		}
	}

	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}


void CDownCompileOption673::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_bDragging = FALSE;
	ReleaseCapture();

	CDialogEx::OnLButtonUp(nFlags, point);
}

void CDownCompileOption673::OnBnClickedButtonConfiggen()
{
	if (!m_ShowDlg_ConfigGen)
	{
		CRect rectThis;
		CRect rectSet;

		pDownloaderDlg->GetWindowRect(&rectThis);
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

void CDownCompileOption673::OnDestroy()
{
	CDialogEx::OnDestroy();

	if (m_pCEN673_Configuration_GeneratorDlg->m_pDlg_SPI != NULL)
		delete m_pCEN673_Configuration_GeneratorDlg->m_pDlg_SPI;
	if (m_pCEN673_Configuration_GeneratorDlg->m_pDlg_Peripheral != NULL)
		delete m_pCEN673_Configuration_GeneratorDlg->m_pDlg_Peripheral;
	if (m_pCEN673_Configuration_GeneratorDlg->m_pDlg_Peripheral != NULL)
		delete m_pCEN673_Configuration_GeneratorDlg;

}
