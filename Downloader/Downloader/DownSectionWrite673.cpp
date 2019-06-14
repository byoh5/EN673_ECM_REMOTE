// DownSectionWrite673.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Downloader.h"
#include "DownSectionWrite673.h"
#include "afxdialogex.h"


// CDownSectionWrite673 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDownSectionWrite673, CDialogEx)

CDownSectionWrite673::CDownSectionWrite673(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDownSectionWrite673::IDD, pParent)
{

}

CDownSectionWrite673::~CDownSectionWrite673()
{
}

void CDownSectionWrite673::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_INCLUDEBOOT, m_Check_IncludeBoot);
}


BEGIN_MESSAGE_MAP(CDownSectionWrite673, CDialogEx)
END_MESSAGE_MAP()


// CDownSectionWrite673 메시지 처리기입니다.


BOOL CDownSectionWrite673::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	pDownSectionWrite673 = this;

	m_Check_IncludeBoot.SetCheck(1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL CDownSectionWrite673::PreTranslateMessage(MSG* pMsg)
{
	if (DefaultWindowMessage(pMsg))	return TRUE;
	else							return CDialog::PreTranslateMessage(pMsg);
}
