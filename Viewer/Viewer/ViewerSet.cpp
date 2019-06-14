// ViewerSet.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Viewer.h"
#include "ViewerSet.h"
#include "afxdialogex.h"


// CViewerSet 대화 상자입니다.

IMPLEMENT_DYNAMIC(CViewerSet, CDialogEx)

CViewerSet::CViewerSet(CWnd* pParent /*=NULL*/)
	: CDialogEx(CViewerSet::IDD, pParent)
{

}

CViewerSet::~CViewerSet()
{
}

void CViewerSet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CHECK_VIEWERCH0, m_Chk_Ch[0]);
	DDX_Control(pDX, IDC_CHECK_VIEWERCH1, m_Chk_Ch[1]);
	DDX_Control(pDX, IDC_CHECK_VIEWERCH2, m_Chk_Ch[2]);
	DDX_Control(pDX, IDC_CHECK_VIEWERCH3, m_Chk_Ch[3]);
	DDX_Control(pDX, IDC_CHECK_VIEWERCH4, m_Chk_Ch[4]);
	DDX_Control(pDX, IDC_CHECK_VIEWERCH5, m_Chk_Ch[5]);
	DDX_Control(pDX, IDC_CHECK_VIEWERCH6, m_Chk_Ch[6]);
	DDX_Control(pDX, IDC_CHECK_VIEWERCH7, m_Chk_Ch[7]);
	DDX_Control(pDX, IDC_COLOR0, m_Color[0]);
	DDX_Control(pDX, IDC_COLOR1, m_Color[1]);
	DDX_Control(pDX, IDC_COLOR2, m_Color[2]);
	DDX_Control(pDX, IDC_COLOR3, m_Color[3]);
	DDX_Control(pDX, IDC_COLOR4, m_Color[4]);
	DDX_Control(pDX, IDC_COLOR5, m_Color[5]);
	DDX_Control(pDX, IDC_COLOR6, m_Color[6]);
	DDX_Control(pDX, IDC_COLOR7, m_Color[7]);
	DDX_Control(pDX, IDC_EDIT_MNEM0, m_Edit_Mnem[0]);
	DDX_Control(pDX, IDC_EDIT_MNEM1, m_Edit_Mnem[1]);
	DDX_Control(pDX, IDC_EDIT_MNEM2, m_Edit_Mnem[2]);
	DDX_Control(pDX, IDC_EDIT_MNEM3, m_Edit_Mnem[3]);
	DDX_Control(pDX, IDC_EDIT_MNEM4, m_Edit_Mnem[4]);
	DDX_Control(pDX, IDC_EDIT_MNEM5, m_Edit_Mnem[5]);
	DDX_Control(pDX, IDC_EDIT_MNEM6, m_Edit_Mnem[6]);
	DDX_Control(pDX, IDC_EDIT_MNEM7, m_Edit_Mnem[7]);
	DDX_Control(pDX, IDC_CBO_SCALE0, m_Cbo_Scale[0]);
	DDX_Control(pDX, IDC_CBO_SCALE1, m_Cbo_Scale[1]);
	DDX_Control(pDX, IDC_CBO_SCALE2, m_Cbo_Scale[2]);
	DDX_Control(pDX, IDC_CBO_SCALE3, m_Cbo_Scale[3]);
	DDX_Control(pDX, IDC_CBO_SCALE4, m_Cbo_Scale[4]);
	DDX_Control(pDX, IDC_CBO_SCALE5, m_Cbo_Scale[5]);
	DDX_Control(pDX, IDC_CBO_SCALE6, m_Cbo_Scale[6]);
	DDX_Control(pDX, IDC_CBO_SCALE7, m_Cbo_Scale[7]);
	DDX_Control(pDX, IDC_SPIN_SCALE0, m_Spin_Scale[0]);
	DDX_Control(pDX, IDC_SPIN_SCALE1, m_Spin_Scale[1]);
	DDX_Control(pDX, IDC_SPIN_SCALE2, m_Spin_Scale[2]);
	DDX_Control(pDX, IDC_SPIN_SCALE3, m_Spin_Scale[3]);
	DDX_Control(pDX, IDC_SPIN_SCALE4, m_Spin_Scale[4]);
	DDX_Control(pDX, IDC_SPIN_SCALE5, m_Spin_Scale[5]);
	DDX_Control(pDX, IDC_SPIN_SCALE6, m_Spin_Scale[6]);
	DDX_Control(pDX, IDC_SPIN_SCALE7, m_Spin_Scale[7]);
	DDX_Control(pDX, IDC_CBO_OFFSET0, m_Cbo_Offset[0]);
	DDX_Control(pDX, IDC_CBO_OFFSET1, m_Cbo_Offset[1]);
	DDX_Control(pDX, IDC_CBO_OFFSET2, m_Cbo_Offset[2]);
	DDX_Control(pDX, IDC_CBO_OFFSET3, m_Cbo_Offset[3]);
	DDX_Control(pDX, IDC_CBO_OFFSET4, m_Cbo_Offset[4]);
	DDX_Control(pDX, IDC_CBO_OFFSET5, m_Cbo_Offset[5]);
	DDX_Control(pDX, IDC_CBO_OFFSET6, m_Cbo_Offset[6]);
	DDX_Control(pDX, IDC_CBO_OFFSET7, m_Cbo_Offset[7]);
	DDX_Control(pDX, IDC_SPIN_OFFSET0, m_Spin_Offset[0]);
	DDX_Control(pDX, IDC_SPIN_OFFSET1, m_Spin_Offset[1]);
	DDX_Control(pDX, IDC_SPIN_OFFSET2, m_Spin_Offset[2]);
	DDX_Control(pDX, IDC_SPIN_OFFSET3, m_Spin_Offset[3]);
	DDX_Control(pDX, IDC_SPIN_OFFSET4, m_Spin_Offset[4]);
	DDX_Control(pDX, IDC_SPIN_OFFSET5, m_Spin_Offset[5]);
	DDX_Control(pDX, IDC_SPIN_OFFSET6, m_Spin_Offset[6]);
	DDX_Control(pDX, IDC_SPIN_OFFSET7, m_Spin_Offset[7]);
	DDX_Control(pDX, IDC_COMBO_TYPE0, m_Cbo_Type[0]);
	DDX_Control(pDX, IDC_COMBO_TYPE1, m_Cbo_Type[1]);
	DDX_Control(pDX, IDC_COMBO_TYPE2, m_Cbo_Type[2]);
	DDX_Control(pDX, IDC_COMBO_TYPE3, m_Cbo_Type[3]);
	DDX_Control(pDX, IDC_COMBO_TYPE4, m_Cbo_Type[4]);
	DDX_Control(pDX, IDC_COMBO_TYPE5, m_Cbo_Type[5]);
	DDX_Control(pDX, IDC_COMBO_TYPE6, m_Cbo_Type[6]);
	DDX_Control(pDX, IDC_COMBO_TYPE7, m_Cbo_Type[7]);
	DDX_Control(pDX, IDC_BUTTON_VIEWERSETLOAD, m_Btn_VSetLoad);
	DDX_Control(pDX, IDC_BUTTON_VIEWERSETSAVE, m_Btn_VSetSave);
	DDX_Control(pDX, IDC_RADIO_5CH, m_Radio_5Ch);
	DDX_Control(pDX, IDC_RADIO_8CH, m_Radio_8Ch);
}


BEGIN_MESSAGE_MAP(CViewerSet, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK_VIEWERCH0, &CViewerSet::OnBnClickedCheckViewerch0)
	ON_BN_CLICKED(IDC_CHECK_VIEWERCH1, &CViewerSet::OnBnClickedCheckViewerch1)
	ON_BN_CLICKED(IDC_CHECK_VIEWERCH2, &CViewerSet::OnBnClickedCheckViewerch2)
	ON_BN_CLICKED(IDC_CHECK_VIEWERCH3, &CViewerSet::OnBnClickedCheckViewerch3)
	ON_BN_CLICKED(IDC_CHECK_VIEWERCH4, &CViewerSet::OnBnClickedCheckViewerch4)
	ON_BN_CLICKED(IDC_CHECK_VIEWERCH5, &CViewerSet::OnBnClickedCheckViewerch5)
	ON_BN_CLICKED(IDC_CHECK_VIEWERCH6, &CViewerSet::OnBnClickedCheckViewerch6)
	ON_BN_CLICKED(IDC_CHECK_VIEWERCH7, &CViewerSet::OnBnClickedCheckViewerch7)
	ON_EN_CHANGE(IDC_EDIT_MNEM0, &CViewerSet::OnEnChangeEditMnem0)
	ON_EN_CHANGE(IDC_EDIT_MNEM1, &CViewerSet::OnEnChangeEditMnem1)
	ON_EN_CHANGE(IDC_EDIT_MNEM2, &CViewerSet::OnEnChangeEditMnem2)
	ON_EN_CHANGE(IDC_EDIT_MNEM3, &CViewerSet::OnEnChangeEditMnem3)
	ON_EN_CHANGE(IDC_EDIT_MNEM4, &CViewerSet::OnEnChangeEditMnem4)
	ON_EN_CHANGE(IDC_EDIT_MNEM5, &CViewerSet::OnEnChangeEditMnem5)
	ON_EN_CHANGE(IDC_EDIT_MNEM6, &CViewerSet::OnEnChangeEditMnem6)
	ON_EN_CHANGE(IDC_EDIT_MNEM7, &CViewerSet::OnEnChangeEditMnem7)
	ON_CBN_EDITCHANGE(IDC_CBO_SCALE0, &CViewerSet::OnCbnEditchangeCboScale0)
	ON_CBN_EDITCHANGE(IDC_CBO_SCALE1, &CViewerSet::OnCbnEditchangeCboScale1)
	ON_CBN_EDITCHANGE(IDC_CBO_SCALE2, &CViewerSet::OnCbnEditchangeCboScale2)
	ON_CBN_EDITCHANGE(IDC_CBO_SCALE3, &CViewerSet::OnCbnEditchangeCboScale3)
	ON_CBN_EDITCHANGE(IDC_CBO_SCALE4, &CViewerSet::OnCbnEditchangeCboScale4)
	ON_CBN_EDITCHANGE(IDC_CBO_SCALE5, &CViewerSet::OnCbnEditchangeCboScale5)
	ON_CBN_EDITCHANGE(IDC_CBO_SCALE6, &CViewerSet::OnCbnEditchangeCboScale6)
	ON_CBN_EDITCHANGE(IDC_CBO_SCALE7, &CViewerSet::OnCbnEditchangeCboScale7)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SCALE0, &CViewerSet::OnDeltaposSpinScale0)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SCALE1, &CViewerSet::OnDeltaposSpinScale1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SCALE2, &CViewerSet::OnDeltaposSpinScale2)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SCALE3, &CViewerSet::OnDeltaposSpinScale3)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SCALE4, &CViewerSet::OnDeltaposSpinScale4)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SCALE5, &CViewerSet::OnDeltaposSpinScale5)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SCALE6, &CViewerSet::OnDeltaposSpinScale6)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SCALE7, &CViewerSet::OnDeltaposSpinScale7)
	ON_CBN_EDITCHANGE(IDC_CBO_OFFSET0, &CViewerSet::OnCbnEditchangeCboOffset0)
	ON_CBN_EDITCHANGE(IDC_CBO_OFFSET1, &CViewerSet::OnCbnEditchangeCboOffset1)
	ON_CBN_EDITCHANGE(IDC_CBO_OFFSET2, &CViewerSet::OnCbnEditchangeCboOffset2)
	ON_CBN_EDITCHANGE(IDC_CBO_OFFSET3, &CViewerSet::OnCbnEditchangeCboOffset3)
	ON_CBN_EDITCHANGE(IDC_CBO_OFFSET4, &CViewerSet::OnCbnEditchangeCboOffset4)
	ON_CBN_EDITCHANGE(IDC_CBO_OFFSET5, &CViewerSet::OnCbnEditchangeCboOffset5)
	ON_CBN_EDITCHANGE(IDC_CBO_OFFSET6, &CViewerSet::OnCbnEditchangeCboOffset6)
	ON_CBN_EDITCHANGE(IDC_CBO_OFFSET7, &CViewerSet::OnCbnEditchangeCboOffset7)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_OFFSET0, &CViewerSet::OnDeltaposSpinOffset0)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_OFFSET1, &CViewerSet::OnDeltaposSpinOffset1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_OFFSET2, &CViewerSet::OnDeltaposSpinOffset2)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_OFFSET3, &CViewerSet::OnDeltaposSpinOffset3)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_OFFSET4, &CViewerSet::OnDeltaposSpinOffset4)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_OFFSET5, &CViewerSet::OnDeltaposSpinOffset5)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_OFFSET6, &CViewerSet::OnDeltaposSpinOffset6)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_OFFSET7, &CViewerSet::OnDeltaposSpinOffset7)
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE0, &CViewerSet::OnCbnSelchangeComboType0)
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE1, &CViewerSet::OnCbnSelchangeComboType1)
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE2, &CViewerSet::OnCbnSelchangeComboType2)
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE3, &CViewerSet::OnCbnSelchangeComboType3)
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE4, &CViewerSet::OnCbnSelchangeComboType4)
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE5, &CViewerSet::OnCbnSelchangeComboType5)
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE6, &CViewerSet::OnCbnSelchangeComboType6)
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE7, &CViewerSet::OnCbnSelchangeComboType7)
	ON_BN_CLICKED(IDC_BUTTON_VIEWERSETLOAD, &CViewerSet::OnBnClickedButtonViewersetload)
	ON_BN_CLICKED(IDC_BUTTON_VIEWERSETSAVE, &CViewerSet::OnBnClickedButtonViewersetsave)
	ON_BN_CLICKED(IDC_RADIO_5CH, &CViewerSet::OnBnClickedRadio5ch)
	ON_BN_CLICKED(IDC_RADIO_8CH, &CViewerSet::OnBnClickedRadio8ch)
END_MESSAGE_MAP()


// CViewerSet 메시지 처리기입니다.


BOOL CViewerSet::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	pViewerSet = this;

	//----------------------------------------------------------------------------------------------------
	// Variable
	m_iSpinMin = -99999999;
	m_iSpinMax = 999999999;

	//----------------------------------------------------------------------------------------------------
	// Control
	int i = 0;
	int j = 0;
	int iSel = 0;
	int iChannelNum = 0;
	CString str = _T("");

	for (i = 0; i < CHANNELTOTAL; i++)
	{
		// Use Channel
		m_Ch[i].bCh = ReadIni(SEC_VIEW, KEY_CH[i], DEF_CH[i]);
		m_Chk_Ch[i].SetCheck(m_Ch[i].bCh);

		m_Edit_Mnem[i].EnableWindow(m_Ch[i].bCh);
		m_Color[i].EnableWindow(m_Ch[i].bCh);
		m_Cbo_Scale[i].EnableWindow(m_Ch[i].bCh);
		m_Spin_Scale[i].EnableWindow(m_Ch[i].bCh);
		m_Cbo_Offset[i].EnableWindow(m_Ch[i].bCh);
		m_Spin_Offset[i].EnableWindow(m_Ch[i].bCh);
		m_Cbo_Type[i].EnableWindow(m_Ch[i].bCh);

		// Mnem 
		SetMnem(i, ReadIni(SEC_VIEW, KEY_MNEM[i], DEF_MNEM[i]));

		// Scale
		SetScale(i, ReadIni(SEC_VIEW, KEY_SCALE[i], DEF_SCALE[i]));

		// Spin Control 설정
		m_Spin_Scale[i].SetRange((short)m_iSpinMax, (short)m_iSpinMin); // Spin Control 방향 설정

		// Offset
		SetOffset(i, ReadIni(SEC_VIEW, KEY_OFFSET[i], DEF_OFFSET[i]));

		// Spin Control 설정
		m_Spin_Offset[i].SetRange((short)m_iSpinMax, (short)m_iSpinMin); // Spin Control 방향 설정

		// Type
		m_Ch[i].strType = ReadIni(SEC_VIEW, KEY_TYPE[i], CBO_TYPE[DEF_TYPE]);

		iSel = -1;
		for (j = 0; j < NUM_TYPE; j++)
		{
			m_Cbo_Type[i].InsertString(j, CBO_TYPE[j]);
			if (m_Ch[i].strType == CBO_TYPE[j]){
				iSel = j;
			}
		}

		if (iSel == -1) {
			m_Cbo_Type[i].SetCurSel(DEF_TYPE);
			m_Ch[i].strType = CBO_TYPE[DEF_TYPE];
		}
		else {
			m_Cbo_Type[i].SetCurSel(iSel);
		}
	}

	// Color
	InitColorButton();

	iChannelNum = ReadIni(SEC_VIEW, KEY_CHANNELNUM, DEF_CHANNELNUM);
	SetChannelMode(iChannelNum ? 5 : 8);

	m_bUpdateSet = FALSE;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL CViewerSet::PreTranslateMessage(MSG* pMsg)
{
	CWnd* wndFocus = GetFocus();

	if (pMsg->message == WM_KEYDOWN) {
		switch (pMsg->wParam)
		{
			// KEYDOWN - UP
		case VK_UP:
			if (wndFocus == NULL) return FALSE;
			break;

			// KEYDOWN - DOWN
		case VK_DOWN:
			if (wndFocus == NULL) return FALSE;
			break;
		}
	}

	if (DefaultWindowMessage(pMsg))	return TRUE;
	else							return CDialogEx::PreTranslateMessage(pMsg);
}


void CViewerSet::SaveValue()
{
	int i = 0;
	CString strR = _T("0");
	CString strG = _T("0");
	CString strB = _T("0");
	CString	strColor = _T("");

	for (i = 0; i < 8; i++)
	{
		strR.Format(_T("%.2x"), GetRValue(m_Ch[i].crColor));
		strG.Format(_T("%.2x"), GetGValue(m_Ch[i].crColor));
		strB.Format(_T("%.2x"), GetBValue(m_Ch[i].crColor));
		strColor = strR + strG + strB;

		WriteIni(SEC_VIEW, KEY_CH[i], (int)m_Ch[i].bCh);
		WriteIni(SEC_VIEW, KEY_COLOR[i], strColor);
		WriteIni(SEC_VIEW, KEY_MNEM[i], m_Ch[i].strMnem);
		WriteIni(SEC_VIEW, KEY_SCALE[i], m_Ch[i].strScale);
		WriteIni(SEC_VIEW, KEY_OFFSET[i], m_Ch[i].strOffset);
		WriteIni(SEC_VIEW, KEY_TYPE[i], m_Ch[i].strType);
	}

	WriteIni(SEC_VIEW, KEY_CHANNELNUM, (int)m_bChMode);
}


void CViewerSet::OnBnClickedCheckViewerch0()	{ OnBnClickedCheckViewerch(0); }
void CViewerSet::OnBnClickedCheckViewerch1()	{ OnBnClickedCheckViewerch(1); }
void CViewerSet::OnBnClickedCheckViewerch2()	{ OnBnClickedCheckViewerch(2); }
void CViewerSet::OnBnClickedCheckViewerch3()	{ OnBnClickedCheckViewerch(3); }
void CViewerSet::OnBnClickedCheckViewerch4()	{ OnBnClickedCheckViewerch(4); }
void CViewerSet::OnBnClickedCheckViewerch5()	{ OnBnClickedCheckViewerch(5); }
void CViewerSet::OnBnClickedCheckViewerch6()	{ OnBnClickedCheckViewerch(6); }
void CViewerSet::OnBnClickedCheckViewerch7()	{ OnBnClickedCheckViewerch(7); }
void CViewerSet::OnBnClickedCheckViewerch(int i)
{
	SetUseCh(i, m_Chk_Ch[i].GetCheck());

	m_bUpdateSet = TRUE;
}


void CViewerSet::SetUseCh(int iNum, BOOL bUse)
{
	m_Chk_Ch[iNum].SetCheck(bUse);

	m_Ch[iNum].bCh = bUse;

	// SetRedraw(LOCK)
	m_Color[iNum].SetRedraw(FALSE);
	m_Edit_Mnem[iNum].SetRedraw(FALSE);
	m_Cbo_Scale[iNum].SetRedraw(FALSE);
	m_Spin_Scale[iNum].SetRedraw(FALSE);
	m_Cbo_Offset[iNum].SetRedraw(FALSE);
	m_Spin_Offset[iNum].SetRedraw(FALSE);
	m_Cbo_Type[iNum].SetRedraw(FALSE);

	// EnableWindow
	m_Color[iNum].EnableWindow(bUse);
	m_Edit_Mnem[iNum].EnableWindow(bUse);
	m_Cbo_Scale[iNum].EnableWindow(bUse);
	m_Spin_Scale[iNum].EnableWindow(bUse);
	m_Cbo_Offset[iNum].EnableWindow(bUse);
	m_Spin_Offset[iNum].EnableWindow(bUse);
	m_Cbo_Type[iNum].EnableWindow(bUse);

	// SetRedraw(UNLOCK)
	m_Color[iNum].SetRedraw(TRUE);
	m_Edit_Mnem[iNum].SetRedraw(TRUE);
	m_Cbo_Scale[iNum].SetRedraw(TRUE);
	m_Spin_Scale[iNum].SetRedraw(TRUE);
	m_Cbo_Offset[iNum].SetRedraw(TRUE);
	m_Spin_Offset[iNum].SetRedraw(TRUE);
	m_Cbo_Type[iNum].SetRedraw(TRUE);

	RedrawWindow(NULL, NULL, /*RDW_NOCHILDREN |*/ RDW_NOERASE | RDW_INVALIDATE);

	// DrawViewer Update Flag
	pViewerDlg->m_bUpdateGraph = TRUE;
}


void CViewerSet::OnEnChangeEditMnem0()	{ OnEnChangeEditMnem(0); }
void CViewerSet::OnEnChangeEditMnem1()	{ OnEnChangeEditMnem(1); }
void CViewerSet::OnEnChangeEditMnem2()	{ OnEnChangeEditMnem(2); }
void CViewerSet::OnEnChangeEditMnem3()	{ OnEnChangeEditMnem(3); }
void CViewerSet::OnEnChangeEditMnem4()	{ OnEnChangeEditMnem(4); }
void CViewerSet::OnEnChangeEditMnem5()	{ OnEnChangeEditMnem(5); }
void CViewerSet::OnEnChangeEditMnem6()	{ OnEnChangeEditMnem(6); }
void CViewerSet::OnEnChangeEditMnem7()	{ OnEnChangeEditMnem(7); }
void CViewerSet::OnEnChangeEditMnem(int i)
{
	CString strMnem = _T("");
	m_Edit_Mnem[i].GetWindowTextW(strMnem);

	m_Ch[i].strMnem = strMnem;

	// DrawViwer Update Flag
	pViewerDlg->m_bUpdateGraph = TRUE;

	// Viewer Snap
	if (pViewerSnap == NULL) return;
	LVCOLUMN lvColumn;
	::ZeroMemory(&lvColumn, sizeof(&lvColumn));

	lvColumn.mask = LVCF_TEXT;
	lvColumn.pszText = (LPWSTR)(LPCTSTR)strMnem;
	pViewerSnap->m_List_Snap.SetColumn(i + 1, &lvColumn);

	//SetMnem(i, strMnem);

	m_bUpdateSet = TRUE;
}


void CViewerSet::SetMnem(int iNum, CString strMnem)
{
	m_Edit_Mnem[iNum].SetWindowTextW(strMnem); //OnEnChangeEditMnem로 넘어감ㅡ.ㅡ;
}


void CViewerSet::OnCbnEditchangeCboScale0()	{ OnCbnEditchangeCboScale(0); }
void CViewerSet::OnCbnEditchangeCboScale1()	{ OnCbnEditchangeCboScale(1); }
void CViewerSet::OnCbnEditchangeCboScale2()	{ OnCbnEditchangeCboScale(2); }
void CViewerSet::OnCbnEditchangeCboScale3()	{ OnCbnEditchangeCboScale(3); }
void CViewerSet::OnCbnEditchangeCboScale4()	{ OnCbnEditchangeCboScale(4); }
void CViewerSet::OnCbnEditchangeCboScale5()	{ OnCbnEditchangeCboScale(5); }
void CViewerSet::OnCbnEditchangeCboScale6()	{ OnCbnEditchangeCboScale(6); }
void CViewerSet::OnCbnEditchangeCboScale7()	{ OnCbnEditchangeCboScale(7); }
void CViewerSet::OnCbnEditchangeCboScale(int i)
{
	CString strScale = _T("");
	m_Cbo_Scale[i].GetWindowTextW(strScale);

	// 글자 제한
	if (strScale.GetLength() > 9)
		strScale.Left(9);

	// Scale 설정
	SetScale(i, strScale);

	// Update Flag
	m_bUpdateSet = TRUE;
}


void CViewerSet::OnDeltaposSpinScale0(NMHDR *pNMHDR, LRESULT *pResult)
{	OnDeltaposSpinScale(pNMHDR, pResult, 0); *pResult = 0;	}
void CViewerSet::OnDeltaposSpinScale1(NMHDR *pNMHDR, LRESULT *pResult)
{	OnDeltaposSpinScale(pNMHDR, pResult, 1); *pResult = 0;	}
void CViewerSet::OnDeltaposSpinScale2(NMHDR *pNMHDR, LRESULT *pResult)
{	OnDeltaposSpinScale(pNMHDR, pResult, 2); *pResult = 0;	}
void CViewerSet::OnDeltaposSpinScale3(NMHDR *pNMHDR, LRESULT *pResult)
{	OnDeltaposSpinScale(pNMHDR, pResult, 3); *pResult = 0;	}
void CViewerSet::OnDeltaposSpinScale4(NMHDR *pNMHDR, LRESULT *pResult)
{	OnDeltaposSpinScale(pNMHDR, pResult, 4); *pResult = 0;	}
void CViewerSet::OnDeltaposSpinScale5(NMHDR *pNMHDR, LRESULT *pResult)
{	OnDeltaposSpinScale(pNMHDR, pResult, 5); *pResult = 0;	}
void CViewerSet::OnDeltaposSpinScale6(NMHDR *pNMHDR, LRESULT *pResult)
{	OnDeltaposSpinScale(pNMHDR, pResult, 6); *pResult = 0;	}
void CViewerSet::OnDeltaposSpinScale7(NMHDR *pNMHDR, LRESULT *pResult)
{	OnDeltaposSpinScale(pNMHDR, pResult, 7); *pResult = 0;	}
void CViewerSet::OnDeltaposSpinScale(NMHDR *pNMHDR, LRESULT *pResult, int i)
{
	LPNMUPDOWN	pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	int iScale = _ttoi(m_Ch[i].strScale);
	int iDelta = pNMUpDown->iDelta;
	CString	strScale = _T("");

	if (iDelta > 0) // 증가
	{
		if (INMIDDLE(iScale, m_iSpinMin, m_iSpinMax - iDelta))
		{
			iScale += iDelta;
		}
		else if (INMIDDLE(iScale, m_iSpinMax - iDelta + 1, m_iSpinMax - 1))
		{
			iScale = m_iSpinMax;
		}
	}
	else if (iDelta < 0) // 감소
	{
		if (INMIDDLE(iScale, m_iSpinMin - iDelta, m_iSpinMax))
		{
			iScale += iDelta;
		}
		else if (INMIDDLE(iScale, m_iSpinMin + 1, m_iSpinMin - iDelta - 1))
		{
			iScale = m_iSpinMin;
		}
	}
	strScale.Format(_T("%d"), iScale);

	SetScale(i, strScale);

	// Update Flag
	m_bUpdateSet = TRUE;
}


void CViewerSet::SetScale(int iNum, CString strScale)
{
	// 커서 저장
	DWORD dwSel = m_Cbo_Scale[iNum].GetEditSel();

	// 값 적용
	m_Cbo_Scale[iNum].SetWindowTextW(strScale);
	m_Ch[iNum].strScale = strScale;

	// 커서 설정
	m_Cbo_Scale[iNum].SetEditSel(dwSel, dwSel);

	// DrawViewer 관련 Value 설정
	if (CheckDec(strScale))	pViewerDlg->m_GrpScale[iNum] = _ttoi(strScale);
	else					pViewerDlg->m_GrpScale[iNum] = 1;
	pViewerDlg->m_bUpdateGraph = TRUE;
}


void CViewerSet::OnCbnEditchangeCboOffset0()	{ OnCbnEditchangeCboOffset(0); }
void CViewerSet::OnCbnEditchangeCboOffset1()	{ OnCbnEditchangeCboOffset(1); }
void CViewerSet::OnCbnEditchangeCboOffset2()	{ OnCbnEditchangeCboOffset(2); }
void CViewerSet::OnCbnEditchangeCboOffset3()	{ OnCbnEditchangeCboOffset(3); }
void CViewerSet::OnCbnEditchangeCboOffset4()	{ OnCbnEditchangeCboOffset(4); }
void CViewerSet::OnCbnEditchangeCboOffset5()	{ OnCbnEditchangeCboOffset(5); }
void CViewerSet::OnCbnEditchangeCboOffset6()	{ OnCbnEditchangeCboOffset(6); }
void CViewerSet::OnCbnEditchangeCboOffset7()	{ OnCbnEditchangeCboOffset(7); }
void CViewerSet::OnCbnEditchangeCboOffset(int i)
{
	CString strOffset = _T("");
	m_Cbo_Offset[i].GetWindowTextW(strOffset);

	// 글자 제한
	if (strOffset.GetLength() > 9)
		strOffset.Left(9);

	SetOffset(i, strOffset);

	// Update Flag
	m_bUpdateSet = TRUE;
}

void CViewerSet::OnDeltaposSpinOffset0(NMHDR *pNMHDR, LRESULT *pResult)
{	OnDeltaposSpinOffset(pNMHDR, pResult, 0); *pResult = 0;	}
void CViewerSet::OnDeltaposSpinOffset1(NMHDR *pNMHDR, LRESULT *pResult)
{	OnDeltaposSpinOffset(pNMHDR, pResult, 1); *pResult = 0;	}
void CViewerSet::OnDeltaposSpinOffset2(NMHDR *pNMHDR, LRESULT *pResult)
{	OnDeltaposSpinOffset(pNMHDR, pResult, 2); *pResult = 0;	}
void CViewerSet::OnDeltaposSpinOffset3(NMHDR *pNMHDR, LRESULT *pResult)
{	OnDeltaposSpinOffset(pNMHDR, pResult, 3); *pResult = 0;	}
void CViewerSet::OnDeltaposSpinOffset4(NMHDR *pNMHDR, LRESULT *pResult)
{	OnDeltaposSpinOffset(pNMHDR, pResult, 4); *pResult = 0;	}
void CViewerSet::OnDeltaposSpinOffset5(NMHDR *pNMHDR, LRESULT *pResult)
{	OnDeltaposSpinOffset(pNMHDR, pResult, 5); *pResult = 0;	}
void CViewerSet::OnDeltaposSpinOffset6(NMHDR *pNMHDR, LRESULT *pResult)
{	OnDeltaposSpinOffset(pNMHDR, pResult, 6); *pResult = 0;	}
void CViewerSet::OnDeltaposSpinOffset7(NMHDR *pNMHDR, LRESULT *pResult)
{	OnDeltaposSpinOffset(pNMHDR, pResult, 7); *pResult = 0;	}
void CViewerSet::OnDeltaposSpinOffset(NMHDR *pNMHDR, LRESULT *pResult, int i)
{
	LPNMUPDOWN	pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	int iOffset = _ttoi(m_Ch[i].strOffset);
	int iDelta = pNMUpDown->iDelta;
	CString strOffset = _T("");

	if (iDelta > 0) // 증가
	{
		if (INMIDDLE(iOffset, m_iSpinMin, m_iSpinMax - iDelta))
		{
			iOffset += iDelta;
		}
		else if (INMIDDLE(iOffset, m_iSpinMax - iDelta + 1, m_iSpinMax - 1))
		{
			iOffset = m_iSpinMax;
		}
	}
	else if (iDelta < 0) // 감소
	{
		if (INMIDDLE(iOffset, m_iSpinMin - iDelta, m_iSpinMax))
		{
			iOffset += iDelta;
		}
		else if (INMIDDLE(iOffset, m_iSpinMin + 1, m_iSpinMin - iDelta - 1))
		{
			iOffset = m_iSpinMin;
		}
	}
	strOffset.Format(_T("%d"), iOffset);

	SetOffset(i, strOffset);

	// Update Flag
	m_bUpdateSet = TRUE;
}


void CViewerSet::SetOffset(int iNum, CString strOffset)
{
	// 커서 저장
	DWORD dwSel = m_Cbo_Offset[iNum].GetEditSel();

	// 값 적용
	m_Cbo_Offset[iNum].SetWindowTextW(strOffset);
	m_Ch[iNum].strOffset = strOffset;

	// 커서 설정
	m_Cbo_Offset[iNum].SetEditSel(dwSel, dwSel);

	// DrawViewer 관련 Value 설정
	if (CheckDec(strOffset))	pViewerDlg->m_GrpOffset[iNum] = _ttoi(strOffset);
	else					pViewerDlg->m_GrpOffset[iNum] = 1;
	pViewerDlg->m_bUpdateGraph = TRUE;
}

//====================================================================================================
// CViewerSet::SetColorButton
//----------------------------------------------------------------------------------------------------
//====================================================================================================
void CViewerSet::InitColorButton()
{
	int i = 0;
	int iR = 0;
	int iG = 0;
	int iB = 0;
	CString strRGB = _T("");

	for (i = 0; i < CHANNELTOTAL; i++)
	{
		strRGB = ReadIni(SEC_VIEW, KEY_COLOR[i], _T(""));

		if (strRGB == _T(""))
		{
			iR = DEF_COLOR[i][0];
			iG = DEF_COLOR[i][1];
			iB = DEF_COLOR[i][2];
		}
		else
		{
			iR = HexToDec(strRGB.Mid(0, 2));
			iG = HexToDec(strRGB.Mid(2, 2));
			iB = HexToDec(strRGB.Mid(4, 2));

			if (!INMIDDLE(iR, 0, 255) || !INMIDDLE(iG, 0, 255) || !INMIDDLE(iB, 0, 255))
			{
				iR = DEF_COLOR[i][0];
				iG = DEF_COLOR[i][1];
				iB = DEF_COLOR[i][2];
			}
		}

		m_Ch[i].crColor = RGB(iR, iG, iB);
		m_Color[i].SetBkColor(m_Ch[i].crColor);

		// Create Graph Pen
		pViewerDlg->pen[i].CreatePen(PS_SOLID, 1, m_Ch[i].crColor);
	}
}
//====================================================================================================
// CViewerSet::SetColor
//----------------------------------------------------------------------------------------------------
/*
OnInitDialog에서 사용하지 말 것.
*/
//====================================================================================================
void CViewerSet::SetColor(int iNum, int iR, int iG, int iB)
{
	m_Ch[iNum].crColor = RGB(iR, iG, iB);
	m_Color[iNum].SetBkColor(m_Ch[iNum].crColor);

	pViewerDlg->pen[iNum].DeleteObject();
	pViewerDlg->pen[iNum].CreatePen(PS_SOLID, 1, m_Ch[iNum].crColor);

	// Viewer Capture 설정
	iR -= iR / 2;
	iG -= iG / 2;
	iB -= iB / 2;

	if (iR < 0) { iR = 0; }
	else if (iR > 255) { iR = 255; }
	if (iG < 0) { iG = 0; }
	else if (iG > 255) { iG = 255; }
	if (iB < 0) { iB = 0; }
	else if (iB > 255) { iB = 255; }

	pViewerCapture->m_ChCap[iNum].crColor = RGB(iR, iG, iB);

	// Update Flag
	pViewerDlg->m_bUpdateGraph = TRUE;
	pViewerDlg->m_bUpdateCapture = TRUE;
}

//====================================================================================================
// CViewerSet::OnSelChangeColor
//----------------------------------------------------------------------------------------------------
//====================================================================================================
LRESULT CViewerSet::OnSelChangeColor(WPARAM wParam, LPARAM lParam)
{
	int i = 0;
	int iR = 0;
	int iG = 0;
	int iB = 0;
	COLORREF cr;

	for (i = 0; i < CHANNELTOTAL; i++)
	{
		cr = m_Color[i].GetBkColor();

		SetColor(i, GetRValue(cr), GetGValue(cr), GetBValue(cr));
	}

	m_bUpdateSet = TRUE;

	return 0L;
}


void CViewerSet::OnCbnSelchangeComboType0()	{ OnCbnSelchangeComboType(0); }
void CViewerSet::OnCbnSelchangeComboType1()	{ OnCbnSelchangeComboType(1); }
void CViewerSet::OnCbnSelchangeComboType2()	{ OnCbnSelchangeComboType(2); }
void CViewerSet::OnCbnSelchangeComboType3()	{ OnCbnSelchangeComboType(3); }
void CViewerSet::OnCbnSelchangeComboType4()	{ OnCbnSelchangeComboType(4); }
void CViewerSet::OnCbnSelchangeComboType5()	{ OnCbnSelchangeComboType(5); }
void CViewerSet::OnCbnSelchangeComboType6()	{ OnCbnSelchangeComboType(6); }
void CViewerSet::OnCbnSelchangeComboType7()	{ OnCbnSelchangeComboType(7); }
void CViewerSet::OnCbnSelchangeComboType(int i)
{
	m_Ch[i].strType = CBO_TYPE[m_Cbo_Type[i].GetCurSel()];

	m_bUpdateSet = TRUE;
	pViewerDlg->m_bUpdateGraph = TRUE;
}


void CViewerSet::OnBnClickedButtonViewersetload()
{
	// m_bUpdateSet을 만들었음. 고로 파일 이름을 담을 Edit Box도 필요하단 소리-_-
	// 확장자도 새로 만들고싶은데 잘 모르겠고...
	// 예외처리 하고...-_-;
	int iMsgBoxReturn = 0;
	CString strIniFile = _T("");
	CString strDefExt = _T("ini");
	CString strFilter = _T("ViewerSet File(*.ini)|*.ini||");

	// Save Ini File
	if (m_bUpdateSet)
	{
		iMsgBoxReturn = AfxMessageBox(_T("Would you like to save the file?"), MB_YESNOCANCEL);
		if (iMsgBoxReturn == IDCANCEL)
		{
			return;
		}
		else if (iMsgBoxReturn == IDYES)
		{
			if (ShowSaveFileDlg(&strIniFile, strDefExt, strFilter, this))
				SaveSet(strIniFile);
		}
	}

	// Open Dialog
	if (!ShowOpenFileDlg(&strIniFile, strDefExt, strFilter, this))
		return;

	// Open
	if (!OpenSet(strIniFile))
		AfxMessageBox(_T("Fail file open."));

	m_bUpdateSet = FALSE;

	pViewerDlg->m_bUpdateGraph = TRUE;
	pViewerDlg->m_bUpdateCapture = TRUE;
}


BOOL CViewerSet::OpenSet(CString strPath)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int iR = 0;
	int iG = 0;
	int iB = 0;
	BOOL bReturn = FALSE;
	CString str = _T("");
	CString strLine = _T("");
	CString strData[CHANNELTOTAL][8]; // 8줄 [Ch, Mnem, Scale, Offset, R, G, B, TYPE]
	CStdioFile setFile;

	// ----------------------------------------------------------------------------------------------------
	// 1. Open File
	if (!setFile.Open(strPath, CFile::modeRead))
		goto ENDSET;

	// 파일 검사
	i = 0;
	while (setFile.ReadString(strLine))
	{
		strLine.Trim();

		if (i >= CHANNELTOTAL)
			goto ENDSET;

		for (j = 0; j < 8; j++)
		{
			k = strLine.FindOneOf(_T("\t "));
			if ((j != 7) && (k == -1))	goto ENDSET;

			if (j == 7)	str = strLine;
			else		str = strLine.Left(k);

			switch (j)
			{
				// Numbers
			case 0: // Channel
			case 2: // Scale
			case 3: // Offset
			case 4: // R
			case 5: // G
			case 6: // B
				if (!CheckDec(str))	goto ENDSET;

				strData[i][j] = str;
				break;

				// CString
			case 1: // Mnem
			case 7:
				strData[i][j] = str;
				break;
			}
			strLine = strLine.Right(strLine.GetLength() - k - 1);
			strLine.TrimLeft();
		}
		i++;
	}

	//----------------------------------------------------------------------------------------------------
	// 2. Set Data
	for (i = 0; i < CHANNELTOTAL; i++)
	{
		// Use Channel
		SetUseCh(i, _ttoi(strData[i][0]));

		// Mnem
		SetMnem(i, strData[i][1]);

		// Scale
		SetScale(i, strData[i][2]);

		// Offset
		SetOffset(i, strData[i][3]);

		// Color
		iR = _ttoi(strData[i][4]);
		iG = _ttoi(strData[i][5]);
		iB = _ttoi(strData[i][6]);

		if ((!INMIDDLE(iR, 0, 255)) || (!INMIDDLE(iG, 0, 255)) || (!INMIDDLE(iB, 0, 255)))
		{
			iR = DEF_COLOR[i][0];
			iG = DEF_COLOR[i][1];
			iB = DEF_COLOR[i][2];
		}

		SetColor(i, iR, iG, iB);

		/*
		m_Ch[i].crColor = RGB(iR, iG, iB);
		pViewerDlg->pen[i].DeleteObject();
		pViewerDlg->pen[i].CreatePen(PS_SOLID, 1, m_Ch[i].crColor);

		if (iR < 0) { iR = 0; } else if (iR > 255) { iR = 255; }
		if (iG < 0) { iG = 0; } else if (iG > 255) { iG = 255; }
		if (iB < 0) { iB = 0; } else if (iB > 255) { iB = 255; }
		pViewerCapture->m_ChCap[i].crColor = RGB(iR, iG, iB);
		*/

		// Type
		for (j = 0; j < NUM_TYPE; j++)
		{
			if (strData[i][7] == CBO_TYPE[j])
			{
				m_Cbo_Type[i].SetCurSel(j);
				m_Ch[i].strType = CBO_TYPE[j];
				break;
			}
		}
		if (j == NUM_TYPE)
		{
			m_Cbo_Type[i].SetCurSel(DEF_TYPE);
			m_Ch[i].strType = CBO_TYPE[DEF_TYPE];
		}
	}

	bReturn = TRUE;

	//----------------------------------------------------------------------------------------------------
	// 3. End Open ViewerSet
ENDSET:
	if (!bReturn)
	{
		// 초기화
		for (i = 0; i<CHANNELTOTAL; i++)
		{
			// Use Channel
			SetUseCh(i, DEF_CH[i]);

			// Mnem
			SetMnem(i, DEF_MNEM[i]);

			// Scale
			SetScale(i, DEF_SCALE[i]);

			// Offset
			SetOffset(i, DEF_OFFSET[i]);

			// Color
			iR = DEF_COLOR[i][0];
			iG = DEF_COLOR[i][1];
			iB = DEF_COLOR[i][2];

			SetColor(i, iR, iG, iB);

			/*
			m_Ch[i].crColor = RGB(iR, iG, iB);

			pViewerDlg->pen[i].DeleteObject();
			pViewerDlg->pen[i].CreatePen(PS_SOLID, 1, m_Ch[i].crColor);

			if (iR < 0) { iR = 0; } else if (iR > 255) { iR = 255; }
			if (iG < 0) { iG = 0; } else if (iG > 255) { iG = 255; }
			if (iB < 0) { iB = 0; } else if (iB > 255) { iB = 255; }
			pViewerCapture->m_ChCap[i].crColor = RGB(iR, iG, iB);
			*/

			// Type
			m_Cbo_Type[i].SetCurSel(DEF_TYPE);
		}
		return bReturn;
	}

	return bReturn;

}


void CViewerSet::SetChannelMode(int i)
{
	if ((i != 5) && (i != 8))
		i = 8;

	switch (i)
	{
	case 5:
		m_bChMode = TRUE;
		m_Radio_5Ch.SetCheck(BST_CHECKED);
		break;
	case 8:
		m_bChMode = FALSE;
		m_Radio_8Ch.SetCheck(BST_CHECKED);
		break;
	}
}


void CViewerSet::OnBnClickedButtonViewersetsave()
{
	CString strIniFile = _T("");
	CString strDefExt = _T("ini");
	CString strFilter = _T("ViewerSet File(*.ini)|*.ini||");

	// Save Dialog
	if (!ShowSaveFileDlg(&strIniFile, strDefExt, strFilter, this))
		return;

	// Save
	SaveSet(strIniFile);

	m_bUpdateSet = FALSE;
}


void CViewerSet::SaveSet(CString strPath)
{
	int i = 0;
	int iR = 0;
	int iG = 0;
	int iB = 0;
	BOOL bCh = 0;
	CString str = _T("");
	CString strMnem = _T("");
	CString	strScale = _T("");
	CString	strOffset = _T("");
	CString strType = _T("");

	CStdioFile setFile;

	if (!setFile.Open(strPath, CFile::modeWrite | CFile::modeCreate)) return;

	for (i = 0; i < CHANNELTOTAL; i++)
	{
		// Use Channel
		bCh = m_Ch[i].bCh;

		// Mnem
		strMnem = m_Ch[i].strMnem;
		if (strMnem == _T("")) strMnem = _T("_");
		strMnem.Replace(' ', '_');

		// Scale
		strScale = m_Ch[i].strScale;
		if (!CheckDec(strScale)) strScale = _T("1");

		// Offset
		strOffset = m_Ch[i].strOffset;
		if (!CheckDec(strOffset)) strOffset = _T("0");

		// Color
		iR = GetRValue(m_Ch[i].crColor);
		iG = GetGValue(m_Ch[i].crColor);
		iB = GetBValue(m_Ch[i].crColor);

		// Type
		strType = m_Ch[i].strType;

		str.Format(_T("%d\t%s\t%s\t%s\t%d\t%d\t%d\t%s\n"),
			bCh, strMnem, strScale, strOffset, iR, iG, iB, strType);
		setFile.WriteString(str);
	}

	setFile.Close();
}


void CViewerSet::OnBnClickedRadio5ch()
{
	m_bChMode = TRUE;
	m_Radio_5Ch.SetCheck(BST_CHECKED);
	m_Radio_8Ch.SetCheck(BST_UNCHECKED);
}


void CViewerSet::OnBnClickedRadio8ch()
{
	m_bChMode = FALSE;
	m_Radio_5Ch.SetCheck(BST_UNCHECKED);
	m_Radio_8Ch.SetCheck(BST_CHECKED);
}
