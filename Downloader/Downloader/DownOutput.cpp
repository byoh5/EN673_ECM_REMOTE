// DownOutput.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Downloader.h"
#include "DownOutput.h"
#include "afxdialogex.h"


// CDownOutput 대화 상자입니다.

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


// CDownOutput 메시지 처리기입니다.


BOOL CDownOutput::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	pDownOutput = this;
	
	m_Edit_Output.SetLimitText(65536);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
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
str : 출력할 문자.
bClear
- 0 (default) : 그냥 추가 출력
- 1           : 해당 라인 지우고 출력
- 2           : 모두 지우고 출력
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
	//if(str.Find('\n')>=0) // 이거 했더니 제대로 인식이 안되는지 커서가 안감ㅠㅠ
	{
		int iLength = m_Edit_Output.GetWindowTextLengthW();
		m_Edit_Output.SetSel(iLength, -1);
	}

}