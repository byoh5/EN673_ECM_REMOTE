// JTAGPrintCmdLogDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "JTAGPrintCPU1.h"
#include "JTAGPrintCmdLogDlg.h"
#include "afxdialogex.h"


// CJTAGPrintCmdLogDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CJTAGPrintCmdLogDlg, CDialogEx)

CJTAGPrintCmdLogDlg::CJTAGPrintCmdLogDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CJTAGPrintCmdLogDlg::IDD, pParent)
{

}

CJTAGPrintCmdLogDlg::~CJTAGPrintCmdLogDlg()
{
}

void CJTAGPrintCmdLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CMDLOG, m_List_CmdLog);
	DDX_Control(pDX, IDC_BUTTON_JTAGPRINTCMDLOG_CLOSE, m_Btn_Close);
}


BEGIN_MESSAGE_MAP(CJTAGPrintCmdLogDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_JTAGPRINTCMDLOG_CLOSE, &CJTAGPrintCmdLogDlg::OnBnClickedButtonJtagprintcmdlogClose)
	ON_LBN_DBLCLK(IDC_LIST_CMDLOG, &CJTAGPrintCmdLogDlg::OnLbnDblclkListCmdlog)
END_MESSAGE_MAP()


// CJTAGPrintCmdLogDlg 메시지 처리기입니다.


BOOL CJTAGPrintCmdLogDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	pJTAGPrintCmdLogDlg = this;


	// CLOSE 버튼
	m_Btn_Close.DrawBorder(FALSE);
	m_Btn_Close.SetColor(CButtonST::BTNST_COLOR_BK_OUT, DIALOGCOLOR);
	m_Btn_Close.SetColor(CButtonST::BTNST_COLOR_BK_IN, DIALOGSUBCOLOR);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CJTAGPrintCmdLogDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	// Top
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

	dc.TextOutW(10, 6, DLG_JTAGPRINTCMDLOG);
}


BOOL CJTAGPrintCmdLogDlg::PreTranslateMessage(MSG* pMsg)
{
	if (DefaultWindowMessage(pMsg))	return TRUE;
	else							return CDialogEx::PreTranslateMessage(pMsg);
}

void CJTAGPrintCmdLogDlg::OnBnClickedButtonJtagprintcmdlogClose()
{
	ShowWindow(SW_HIDE);
	pJTAGPrintCPU1Dlg->m_ShowDlg_CmdLog = FALSE;
}


void CJTAGPrintCmdLogDlg::OnLbnDblclkListCmdlog()
{
	CString str;
	int nList = 0;

	nList = m_List_CmdLog.GetCurSel();		//인자 얻기
	m_List_CmdLog.GetText(nList, str);		//텍스트 얻기

	pJTAGPrintCPU1Dlg->m_Edit_RxShellCommand.SetWindowTextW(str);
}
