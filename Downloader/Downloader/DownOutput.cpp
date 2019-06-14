// DownOutput.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Downloader.h"
#include "DownOutput.h"
#include "afxdialogex.h"


// CDownOutput ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CDownOutput, CDialogEx)

CDownOutput::CDownOutput(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDownOutput::IDD, pParent)
{

}

CDownOutput::~CDownOutput()
{
}

void CDownOutput::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_OUTPUT, m_Edit_Output);
}


BEGIN_MESSAGE_MAP(CDownOutput, CDialogEx)
END_MESSAGE_MAP()


// CDownOutput �޽��� ó�����Դϴ�.


BOOL CDownOutput::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	pDownOutput = this;
	
	m_Edit_Output.SetLimitText(65536);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


BOOL CDownOutput::PreTranslateMessage(MSG* pMsg)
{
	CWnd* wndFocus = GetFocus();
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_RETURN:
			if (wndFocus == NULL) return FALSE;
			if (wndFocus == (CWnd*)&m_Edit_Output)
				return CDialog::PreTranslateMessage(pMsg);
		}
	}

	// Default Window Message
	if (DefaultWindowMessage(pMsg))	return TRUE;
	else							return CDialog::PreTranslateMessage(pMsg);
}


// ====================================================================================================
// CDownOutput :: AddOutBox
// ----------------------------------------------------------------------------------------------------
/*
str : ����� ����.
bClear
- 0 (default) : �׳� �߰� ���
- 1           : �ش� ���� ����� ���
- 2           : ��� ����� ���
*/
// ====================================================================================================
void CDownOutput::AddOutBox(CString str, BOOL bClear)
{
	int iLen = 0;
	int iIndex = 0;
	int iLineCount = 0;
	CString strOutput = _T("");

	m_Edit_Output.SetRedraw(FALSE);

	switch (bClear)
	{
	case DOWNOUTPUT_NONE:
		// Add String
		m_Edit_Output.GetWindowTextW(strOutput);
		m_Edit_Output.SetWindowTextW(strOutput + str);
		break;

	case DOWNOUTPUT_CLEARLINE: // Clear Line
#if 0
		m_Edit_Output.GetWindowTextW(strOutput);

		iIndex = strOutput.ReverseFind('\n');
		if (iIndex == -1) {
			strOutput = _T("");
		}
		else {
			strOutput = strOutput.Left(strOutput.ReverseFind('\n') + 1);
		}
		m_Edit_Output.SetWindowTextW(strOutput + str);
#else
		iLineCount = m_Edit_Output.GetLineCount() - 1;
		iIndex = m_Edit_Output.LineIndex(iLineCount);
		iLen = m_Edit_Output.GetWindowTextLengthW() - iIndex;
		m_Edit_Output.SetSel(iIndex, iIndex + iLen);
		m_Edit_Output.ReplaceSel(str);
#endif
		break;

	case DOWNOUTPUT_CLEARALL: // Clear All
		m_Edit_Output.SetWindowTextW(str);

		break;
	}

	m_Edit_Output.SetRedraw(TRUE);

	// Set Cursor
	//if(str.Find('\n')>=0) // �̰� �ߴ��� ����� �ν��� �ȵǴ��� Ŀ���� �Ȱ��Ф�
	{
		int iLength = m_Edit_Output.GetWindowTextLengthW();
		m_Edit_Output.SetSel(iLength, -1);
	}

}