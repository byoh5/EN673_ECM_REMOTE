// DownSectionWrite673.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Downloader.h"
#include "DownSectionWrite673.h"
#include "afxdialogex.h"


// CDownSectionWrite673 ��ȭ �����Դϴ�.

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


// CDownSectionWrite673 �޽��� ó�����Դϴ�.


BOOL CDownSectionWrite673::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	pDownSectionWrite673 = this;

	m_Check_IncludeBoot.SetCheck(1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


BOOL CDownSectionWrite673::PreTranslateMessage(MSG* pMsg)
{
	if (DefaultWindowMessage(pMsg))	return TRUE;
	else							return CDialog::PreTranslateMessage(pMsg);
}
