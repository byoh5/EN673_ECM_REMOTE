// UARTStringCmdLogDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "UARTString.h"
#include "UARTStringCmdLogDlg.h"
#include "afxdialogex.h"


// CUARTStringCmdLogDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CUARTStringCmdLogDlg, CDialogEx)

CUARTStringCmdLogDlg::CUARTStringCmdLogDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUARTStringCmdLogDlg::IDD, pParent)
{

}

CUARTStringCmdLogDlg::~CUARTStringCmdLogDlg()
{
}

void CUARTStringCmdLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_CLOSE, m_Btn_Close);
	DDX_Control(pDX, IDC_LIST_CMDLOG, m_List_CmdLog);
}


BEGIN_MESSAGE_MAP(CUARTStringCmdLogDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_LBN_DBLCLK(IDC_LIST_CMDLOG, &CUARTStringCmdLogDlg::OnLbnDblclkListCmdlog)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CUARTStringCmdLogDlg::OnBnClickedButtonClose)
END_MESSAGE_MAP()


// CUARTStringCmdLogDlg 메시지 처리기입니다.


BOOL CUARTStringCmdLogDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	pUARTStringCmdLogDlg = this;


	// CLOSE 버튼
	m_Btn_Close.DrawBorder(FALSE);
	m_Btn_Close.SetColor(CButtonST::BTNST_COLOR_BK_OUT, DIALOGCOLOR);
	m_Btn_Close.SetColor(CButtonST::BTNST_COLOR_BK_IN, DIALOGSUBCOLOR);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CUARTStringCmdLogDlg::OnPaint()
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

	dc.TextOutW(10, 6, DLG_UARTSTRINGCMDLOG);
}


BOOL CUARTStringCmdLogDlg::PreTranslateMessage(MSG* pMsg)
{
	if (DefaultWindowMessage(pMsg))	return TRUE;
	else							return CDialogEx::PreTranslateMessage(pMsg);
}


void CUARTStringCmdLogDlg::OnBnClickedButtonClose()
{
	ShowWindow(SW_HIDE);
	pUARTStringDlg->m_ShowDlg_CmdLog = FALSE;
}


void CUARTStringCmdLogDlg::OnLbnDblclkListCmdlog()
{
	CString str;
	int nList = 0;

	nList = m_List_CmdLog.GetCurSel();		//인자 얻기
	m_List_CmdLog.GetText(nList, str);		//텍스트 얻기

	pUARTStringDlg->m_Edit_SendString.SetWindowTextW(str);
}