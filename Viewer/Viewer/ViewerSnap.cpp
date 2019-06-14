// ViewerSnap.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Viewer.h"
#include "ViewerSnap.h"
#include "afxdialogex.h"


// CViewerSnap 대화 상자입니다.

IMPLEMENT_DYNAMIC(CViewerSnap, CDialogEx)

CViewerSnap::CViewerSnap(CWnd* pParent /*=NULL*/)
	: CDialogEx(CViewerSnap::IDD, pParent)
{

}

CViewerSnap::~CViewerSnap()
{
}

void CViewerSnap::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SNAP, m_List_Snap);
	DDX_Control(pDX, IDC_EDIT_SNAP, m_Edit_SnapTime);
	DDX_Control(pDX, IDC_BUTTON_SNAP, m_Btn_Snap);
	DDX_Control(pDX, IDC_CHECK_AUTO, m_Chk_AutoSnap);
	DDX_Control(pDX, IDC_BUTTON_SAVESNAP, m_Btn_SaveSnap);
	DDX_Control(pDX, IDC_BUTTON_SNAPCLEAR, m_Btn_SnapClear);
}


BEGIN_MESSAGE_MAP(CViewerSnap, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SNAP, &CViewerSnap::OnBnClickedButtonSnap)
	ON_BN_CLICKED(IDC_CHECK_AUTO, &CViewerSnap::OnBnClickedCheckAuto)
	ON_BN_CLICKED(IDC_BUTTON_SAVESNAP, &CViewerSnap::OnBnClickedButtonSavesnap)
	ON_BN_CLICKED(IDC_BUTTON_SNAPCLEAR, &CViewerSnap::OnBnClickedButtonSnapclear)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CViewerSnap 메시지 처리기입니다.


BOOL CViewerSnap::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	pViewerSnap = this;

	int iWidth = 50;

	m_List_Snap.InsertColumn(0, _T("Time"), LVCFMT_LEFT, 110);
	m_List_Snap.InsertColumn(1, pViewerSet->m_Ch[0].strMnem, LVCFMT_LEFT, iWidth);
	m_List_Snap.InsertColumn(2, pViewerSet->m_Ch[1].strMnem, LVCFMT_LEFT, iWidth);
	m_List_Snap.InsertColumn(3, pViewerSet->m_Ch[2].strMnem, LVCFMT_LEFT, iWidth);
	m_List_Snap.InsertColumn(4, pViewerSet->m_Ch[3].strMnem, LVCFMT_LEFT, iWidth);
	m_List_Snap.InsertColumn(5, pViewerSet->m_Ch[4].strMnem, LVCFMT_LEFT, iWidth);
	m_List_Snap.InsertColumn(6, pViewerSet->m_Ch[5].strMnem, LVCFMT_LEFT, iWidth);
	m_List_Snap.InsertColumn(7, pViewerSet->m_Ch[6].strMnem, LVCFMT_LEFT, iWidth);
	m_List_Snap.InsertColumn(8, pViewerSet->m_Ch[7].strMnem, LVCFMT_LEFT, iWidth);
	EnableCtrl(TRUE);

	m_Edit_SnapTime.EnableWindow(FALSE);
	m_OnAutoSnap = FALSE;

	m_Btn_SaveSnap.SetBitmaps(IDB_SAVE, RGB(255, 0, 255));

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL CViewerSnap::PreTranslateMessage(MSG* pMsg)
{
	CWnd* wndFocus = GetFocus();

	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_DELETE:
			if (wndFocus == NULL) return FALSE;
			if (wndFocus == (CWnd*)&m_List_Snap)
			{
				int iSelItem;

				for (iSelItem = m_List_Snap.GetNextItem(-1, LVNI_SELECTED);
					iSelItem != -1;
					iSelItem = m_List_Snap.GetNextItem(iSelItem, LVNI_SELECTED))
				{
					m_List_Snap.DeleteItem(iSelItem);
					iSelItem--;
				}
				return TRUE;
			}
			break;
		}
	}

	// Default Window Message
	if (DefaultWindowMessage(pMsg))	return TRUE;
	else							return CDialogEx::PreTranslateMessage(pMsg);
}


void CViewerSnap::OnBnClickedButtonSnap()
{
	CString strSnapTime = _T("");
	m_Edit_SnapTime.GetWindowTextW(strSnapTime);

	// 연결 확인
	if (!ConnectSocket) return;

	// Snap Mode
	if (!m_Chk_AutoSnap.GetCheck())
		LineCapture();
	// Auto Snap Mode
	else
	{
		if (strSnapTime == _T("0")) return;
		if (!CheckDec(strSnapTime)) return;

		// Start
		if (!m_OnAutoSnap)
		{
			int iTime = (int)(_ttoi(strSnapTime) * 1000);
			SetTimer(IDT_AUTOSNAP, iTime, NULL);

			m_OnAutoSnap = TRUE;

			m_Edit_SnapTime.EnableWindow(FALSE);
			m_Chk_AutoSnap.EnableWindow(FALSE);
			m_Btn_Snap.SetWindowTextW(_T("Stop"));
		}
		// Stop
		else
		{
			KillTimer(IDT_AUTOSNAP);

			m_OnAutoSnap = FALSE;

			m_Edit_SnapTime.EnableWindow(TRUE);
			m_Chk_AutoSnap.EnableWindow(TRUE);
			m_Btn_Snap.SetWindowTextW(_T("Snap"));
		}
	}
}

// ====================================================================================================
// CViewerSnap::LineCapture
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CViewerSnap::LineCapture()
{
	int i = 0;
	int j = 0;
	CString strTime = _T("");
	SYSTEMTIME st;
	GetLocalTime(&st);

	strTime.Format(_T("%d-%d-%d %d:%d:%d"), st.wYear, st.wMonth, st.wDay,
		st.wHour, st.wMinute, st.wSecond);
	CString strBar = _T("");

	j = m_List_Snap.InsertItem(m_List_Snap.GetItemCount(), strTime);

	for (i = 0; i < CHANNELTOTAL; i++)
	{
		if (pViewerSet->m_Ch[i].strType == CBO_TYPE[1])
			strBar.Format(_T("%f"), pViewerDlg->m_oBarV[i].m_float);
		else if (pViewerSet->m_Ch[i].strType == CBO_TYPE[0])
			strBar.Format(_T("%d"), pViewerDlg->m_oBarV[i].m_int);
		else if (pViewerSet->m_Ch[i].strType == CBO_TYPE[2]) {
			strBar.Format(_T("%02x"), pViewerDlg->m_oBarV[i].m_int & 0xff);
			strBar = HexToBin(strBar);
		}

		m_List_Snap.SetItemText(j, i + 1, strBar);
	}

	GetDlgItem(IDC_LIST_SNAP)->SendMessage(WM_VSCROLL, SB_BOTTOM);

	if (m_List_Snap.GetItemCount() > 2000)
	{
		m_List_Snap.DeleteItem(0);
	}
}

// ====================================================================================================
// CViewerSnap::LineCapture
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CViewerSnap::EnableCtrl(BOOL b)
{
	m_Btn_SaveSnap.EnableWindow(b);
	if (ConnectSocket)
		m_Edit_SnapTime.EnableWindow(m_Chk_AutoSnap.GetCheck());
	else
		m_Edit_SnapTime.EnableWindow(b);

	m_Btn_Snap.EnableWindow(b);
	m_Chk_AutoSnap.EnableWindow(b);
	m_Btn_SnapClear.EnableWindow(b);
}


void CViewerSnap::OnBnClickedCheckAuto()
{
	if (m_Chk_AutoSnap.GetCheck())	m_Edit_SnapTime.EnableWindow(TRUE);
	else							m_Edit_SnapTime.EnableWindow(FALSE);
}


void CViewerSnap::OnBnClickedButtonSavesnap()
{
	CString strTxtPath = _T("");
	CString strDefExt = _T("txt");
	CString strFilter = _T("Text File(*.txt)|*.txt||");

	// Save Dialog
	if (!ShowSaveFileDlg(&strTxtPath, strDefExt, strFilter, this))
		return;

	// Save
	int i = 0;
	int j = 0;
	CString	strLine = _T("");

	CStdioFile file;
	if (!file.Open(strTxtPath, CFile::modeCreate | CFile::modeReadWrite)) return;

	strLine.Format(_T("[TIME]				%s	%s	%s	%s	%s	%s	%s	%s\n"),
		pViewerSet->m_Ch[0].strMnem, pViewerSet->m_Ch[1].strMnem,
		pViewerSet->m_Ch[2].strMnem, pViewerSet->m_Ch[3].strMnem,
		pViewerSet->m_Ch[4].strMnem, pViewerSet->m_Ch[5].strMnem,
		pViewerSet->m_Ch[6].strMnem, pViewerSet->m_Ch[7].strMnem);

	file.WriteString(strLine);

	CString strSubLine[10];
	for (i = 0; i < m_List_Snap.GetItemCount(); i++)
	{
		for (j = 0; j < 10; j++)
		{
			strSubLine[j] = m_List_Snap.GetItemText(i, j);
		}

		strLine.Format(_T("[%s]	%s	%s	%s	%s	%s	%s	%s	%s\n"),
			strSubLine[0], strSubLine[1], strSubLine[2],
			strSubLine[3], strSubLine[4], strSubLine[5],
			strSubLine[6], strSubLine[7], strSubLine[8]
			);

		file.WriteString(strLine);
	}

	//if(AfxMessageBox(_T("저장한 파일을 여시겠습니까?"), MB_OKCANCEL )==IDOK)
	//{
	//	::ShellExecute(NULL, _T("open"), FilePath, NULL, NULL, SW_SHOWNORMAL);
	//}

	file.Close();
}


void CViewerSnap::OnBnClickedButtonSnapclear()
{
	m_List_Snap.DeleteAllItems();
}


void CViewerSnap::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case IDT_AUTOSNAP:
		if (!pViewerDlg->m_bStartGraph) return;
		if (!m_OnAutoSnap) return;

		LineCapture();

		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}
