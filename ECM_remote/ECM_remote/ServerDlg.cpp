// ServerDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ECM_remote.h"
#include "ServerDlg.h"
#include "afxdialogex.h"


// CServerDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CServerDlg, CDialogEx)

CServerDlg::CServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CServerDlg::IDD, pParent)
{

}

CServerDlg::~CServerDlg()
{
}

void CServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDCANCEL, m_Btn_Close);
	DDX_Control(pDX, IDC_EDIT_SERVERCOMMAND, m_Edit_ServerCommand);
	DDX_Control(pDX, IDC_SERVERRUN, m_Btn_ServerRun);
	DDX_Control(pDX, IDC_RADIO_CHA, m_Radio_ChA);
	DDX_Control(pDX, IDC_RADIO_CHB, m_Radio_ChB);
}


BEGIN_MESSAGE_MAP(CServerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDCANCEL, &CServerDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_SERVERRUN, &CServerDlg::OnBnClickedServerrun)
END_MESSAGE_MAP()


// CServerDlg 메시지 처리기입니다.


BOOL CServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	pCServerDlg = this;

	// Close
	m_Btn_Close.DrawBorder(FALSE);
	m_Btn_Close.SetColor(CButtonST::BTNST_COLOR_BK_OUT, DIALOGCOLOR);
	m_Btn_Close.SetColor(CButtonST::BTNST_COLOR_BK_IN, DIALOGSUBCOLOR);

	// Command
	//m_Edit_ExrocdCommand.SetWindowTextW(_T("ft2232"));
	m_Edit_ServerCommand.SetWindowTextW(ReadIni(SEC_ECMREMOTE, KEY_COMMAND, DEF_COMMAND));

	CString str = _T("");
	str = ReadIni(SEC_ECMREMOTE, KEY_CHANEL, DEF_CHANEL);

	if (str == _T("A"))
	{
		m_Radio_ChA.SetCheck(1);
		m_Radio_ChB.SetCheck(0);
	}
	if (str == _T("B"))
	{
		m_Radio_ChA.SetCheck(0);
		m_Radio_ChB.SetCheck(1);
	}

	m_CServerDlg = FALSE;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL CServerDlg::PreTranslateMessage(MSG* pMsg)
{
	CWnd* wndFocus = GetFocus();

	switch (pMsg->wParam)
	{
	case VK_ESCAPE:
		return TRUE;
	case VK_RETURN:
		if (wndFocus == (CWnd*)&m_Edit_ServerCommand) {
			OnBnClickedServerrun();
			return TRUE;
		}
		else
			return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CServerDlg::OnPaint()
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

	dc.TextOutW(10, 6, DLG_EXROCD);
}


void CServerDlg::OnBnClickedCancel()
{
	m_Edit_ServerCommand.GetWindowTextW(pRemoteDlg->Command);
	WriteIni(SEC_ECMREMOTE, KEY_COMMAND, pRemoteDlg->Command);

	if (m_Radio_ChA.GetCheck())
		WriteIni(SEC_ECMREMOTE, KEY_CHANEL, _T("A"));
	if (m_Radio_ChB.GetCheck())
		WriteIni(SEC_ECMREMOTE, KEY_CHANEL, _T("B"));

	pRemoteDlg->m_ShowDlg_Server = FALSE;
	ShowWindow(SW_HIDE);
}


void CServerDlg::OnBnClickedServerrun()
{
	int err;
	if (!m_CServerDlg)
	{
		//pRemoteDlg->Check_Timer_Off();

		// SERVER 실행
		err = pRemoteDlg->ExeFunc(Server, SERVER);
		pRemoteDlg->ActiveCtrl(Server, TRUE);
		if (err < 0)
		{
			AfxMessageBox(_T("JtagControl.exe Fail"));
			//pRemoteDlg->Check_Timer_On();
			return;
		}

		pCServerDlg->m_Btn_ServerRun.SetWindowTextW(_T("Stop"));
		m_CServerDlg = TRUE;

		// EXR OCD 동작 확인
		//pRemoteDlg->m_Bt_EXROCDState.SetColor(CButtonST::BTNST_COLOR_BK_OUT, RGB(0x00, 0xFF, 0x00));
		//pRemoteDlg->m_Bt_EXROCDState.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(0x00, 0xFF, 0x00));

		// PORT & Server IP 비활성화
		//pRemoteDlg->m_Edit_Port.EnableWindow(FALSE);
		//pRemoteDlg->m_ctrlIPAddr.EnableWindow(FALSE);
		//pRemoteDlg->Check_Timer_On();
	}
	else
	{
		DWORD exitcode = 0;
		GetExitCodeProcess(pRemoteDlg->m_sInfo[Server].hProcess, &exitcode);
		if (exitcode == STILL_ACTIVE)
		{
			TerminateProcess(pRemoteDlg->m_sInfo[Server].hProcess, 0);
			ZeroMemory(&pRemoteDlg->m_sInfo[Server], sizeof(SHELLEXECUTEINFO));
			CloseHandle(pRemoteDlg->m_sInfo[Server].hProcess);
		}

		pCServerDlg->m_Btn_ServerRun.SetWindowTextW(_T("Run"));
		m_CServerDlg = FALSE;

		// SERVER 동작 확인
		pRemoteDlg->m_Bt_ServerState.SetColor(CButtonST::BTNST_COLOR_BK_OUT, RGB(0xFF, 0x00, 0x00));
		pRemoteDlg->m_Bt_ServerState.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(0xFF, 0x00, 0x00));

		// PORT & Server IP 비활성화
		//pRemoteDlg->m_Edit_Port.EnableWindow(TRUE);
		//pRemoteDlg->m_ctrlIPAddr.EnableWindow(TRUE);
		pRemoteDlg->ActiveCtrl(Server, FALSE);
	}

#if 0
	CString strNowPath = GetNowPath();
	CString strUsbdosPath = SERVER;
	strUsbdosPath = RelativeToAbsolute(strUsbdosPath, strNowPath); // 상대경로 -> 절대경로

	CWnd* hWndDlg = NULL;
	hWndDlg = FindWindow(NULL, strUsbdosPath);
	::ShowWindow(hWndDlg->m_hWnd, SW_HIDE);
	::ShowWindow(hWndDlg->m_hWnd, SW_SHOW);
#endif
}
