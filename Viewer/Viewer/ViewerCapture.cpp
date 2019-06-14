// ViewerCapture.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Viewer.h"
#include "ViewerCapture.h"
#include "afxdialogex.h"


// CViewerCapture 대화 상자입니다.

IMPLEMENT_DYNAMIC(CViewerCapture, CDialogEx)

CViewerCapture::CViewerCapture(CWnd* pParent /*=NULL*/)
	: CDialogEx(CViewerCapture::IDD, pParent)
{

}

CViewerCapture::~CViewerCapture()
{
}

void CViewerCapture::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_LOADCAP, m_Btn_LoadCap);
	DDX_Control(pDX, IDC_BUTTON_CAPTURE, m_Btn_Capture);
	DDX_Control(pDX, IDC_CHECK_CAPCH0, m_Chk_Ch[0]);
	DDX_Control(pDX, IDC_CHECK_CAPCH1, m_Chk_Ch[1]);
	DDX_Control(pDX, IDC_CHECK_CAPCH2, m_Chk_Ch[2]);
	DDX_Control(pDX, IDC_CHECK_CAPCH3, m_Chk_Ch[3]);
	DDX_Control(pDX, IDC_CHECK_CAPCH4, m_Chk_Ch[4]);
	DDX_Control(pDX, IDC_CHECK_CAPCH5, m_Chk_Ch[5]);
	DDX_Control(pDX, IDC_CHECK_CAPCH6, m_Chk_Ch[6]);
	DDX_Control(pDX, IDC_CHECK_CAPCH7, m_Chk_Ch[7]);
	DDX_Control(pDX, IDC_EDIT_CAPMNEM0, m_Edit_Mnem[0]);
	DDX_Control(pDX, IDC_EDIT_CAPMNEM1, m_Edit_Mnem[1]);
	DDX_Control(pDX, IDC_EDIT_CAPMNEM2, m_Edit_Mnem[2]);
	DDX_Control(pDX, IDC_EDIT_CAPMNEM3, m_Edit_Mnem[3]);
	DDX_Control(pDX, IDC_EDIT_CAPMNEM4, m_Edit_Mnem[4]);
	DDX_Control(pDX, IDC_EDIT_CAPMNEM5, m_Edit_Mnem[5]);
	DDX_Control(pDX, IDC_EDIT_CAPMNEM6, m_Edit_Mnem[6]);
	DDX_Control(pDX, IDC_EDIT_CAPMNEM7, m_Edit_Mnem[7]);
	DDX_Control(pDX, IDC_COMBO_CAPSCALE0, m_Cbo_Scale[0]);
	DDX_Control(pDX, IDC_COMBO_CAPSCALE1, m_Cbo_Scale[1]);
	DDX_Control(pDX, IDC_COMBO_CAPSCALE2, m_Cbo_Scale[2]);
	DDX_Control(pDX, IDC_COMBO_CAPSCALE3, m_Cbo_Scale[3]);
	DDX_Control(pDX, IDC_COMBO_CAPSCALE4, m_Cbo_Scale[4]);
	DDX_Control(pDX, IDC_COMBO_CAPSCALE5, m_Cbo_Scale[5]);
	DDX_Control(pDX, IDC_COMBO_CAPSCALE6, m_Cbo_Scale[6]);
	DDX_Control(pDX, IDC_COMBO_CAPSCALE7, m_Cbo_Scale[7]);
	DDX_Control(pDX, IDC_SPIN_CAPSCALE0, m_Spin_Scale[0]);
	DDX_Control(pDX, IDC_SPIN_CAPSCALE1, m_Spin_Scale[1]);
	DDX_Control(pDX, IDC_SPIN_CAPSCALE2, m_Spin_Scale[2]);
	DDX_Control(pDX, IDC_SPIN_CAPSCALE3, m_Spin_Scale[3]);
	DDX_Control(pDX, IDC_SPIN_CAPSCALE4, m_Spin_Scale[4]);
	DDX_Control(pDX, IDC_SPIN_CAPSCALE5, m_Spin_Scale[5]);
	DDX_Control(pDX, IDC_SPIN_CAPSCALE6, m_Spin_Scale[6]);
	DDX_Control(pDX, IDC_SPIN_CAPSCALE7, m_Spin_Scale[7]);
	DDX_Control(pDX, IDC_COMBO_CAPOFFSET0, m_Cbo_Offset[0]);
	DDX_Control(pDX, IDC_COMBO_CAPOFFSET1, m_Cbo_Offset[1]);
	DDX_Control(pDX, IDC_COMBO_CAPOFFSET2, m_Cbo_Offset[2]);
	DDX_Control(pDX, IDC_COMBO_CAPOFFSET3, m_Cbo_Offset[3]);
	DDX_Control(pDX, IDC_COMBO_CAPOFFSET4, m_Cbo_Offset[4]);
	DDX_Control(pDX, IDC_COMBO_CAPOFFSET5, m_Cbo_Offset[5]);
	DDX_Control(pDX, IDC_COMBO_CAPOFFSET6, m_Cbo_Offset[6]);
	DDX_Control(pDX, IDC_COMBO_CAPOFFSET7, m_Cbo_Offset[7]);
	DDX_Control(pDX, IDC_SPIN_CAPOFFSET0, m_Spin_Offset[0]);
	DDX_Control(pDX, IDC_SPIN_CAPOFFSET1, m_Spin_Offset[1]);
	DDX_Control(pDX, IDC_SPIN_CAPOFFSET2, m_Spin_Offset[2]);
	DDX_Control(pDX, IDC_SPIN_CAPOFFSET3, m_Spin_Offset[3]);
	DDX_Control(pDX, IDC_SPIN_CAPOFFSET4, m_Spin_Offset[4]);
	DDX_Control(pDX, IDC_SPIN_CAPOFFSET5, m_Spin_Offset[5]);
	DDX_Control(pDX, IDC_SPIN_CAPOFFSET6, m_Spin_Offset[6]);
	DDX_Control(pDX, IDC_SPIN_CAPOFFSET7, m_Spin_Offset[7]);
	DDX_Control(pDX, IDC_COMBO_CAPTYPE0, m_Cbo_Type[0]);
	DDX_Control(pDX, IDC_COMBO_CAPTYPE1, m_Cbo_Type[1]);
	DDX_Control(pDX, IDC_COMBO_CAPTYPE2, m_Cbo_Type[2]);
	DDX_Control(pDX, IDC_COMBO_CAPTYPE3, m_Cbo_Type[3]);
	DDX_Control(pDX, IDC_COMBO_CAPTYPE4, m_Cbo_Type[4]);
	DDX_Control(pDX, IDC_COMBO_CAPTYPE5, m_Cbo_Type[5]);
	DDX_Control(pDX, IDC_COMBO_CAPTYPE6, m_Cbo_Type[6]);
	DDX_Control(pDX, IDC_COMBO_CAPTYPE7, m_Cbo_Type[7]);
}


BEGIN_MESSAGE_MAP(CViewerCapture, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_LOADCAP, &CViewerCapture::OnBnClickedButtonLoadcap)
	ON_BN_CLICKED(IDC_BUTTON_CAPTURE, &CViewerCapture::OnBnClickedButtonCapture)
	ON_BN_CLICKED(IDC_CHECK_CAPCH0, &CViewerCapture::OnBnClickedCheckCapch0)
	ON_BN_CLICKED(IDC_CHECK_CAPCH1, &CViewerCapture::OnBnClickedCheckCapch1)
	ON_BN_CLICKED(IDC_CHECK_CAPCH2, &CViewerCapture::OnBnClickedCheckCapch2)
	ON_BN_CLICKED(IDC_CHECK_CAPCH3, &CViewerCapture::OnBnClickedCheckCapch3)
	ON_BN_CLICKED(IDC_CHECK_CAPCH4, &CViewerCapture::OnBnClickedCheckCapch4)
	ON_BN_CLICKED(IDC_CHECK_CAPCH5, &CViewerCapture::OnBnClickedCheckCapch5)
	ON_BN_CLICKED(IDC_CHECK_CAPCH6, &CViewerCapture::OnBnClickedCheckCapch6)
	ON_BN_CLICKED(IDC_CHECK_CAPCH7, &CViewerCapture::OnBnClickedCheckCapch7)
	ON_EN_CHANGE(IDC_EDIT_CAPMNEM0, &CViewerCapture::OnEnChangeEditCapmnem0)
	ON_EN_CHANGE(IDC_EDIT_CAPMNEM1, &CViewerCapture::OnEnChangeEditCapmnem1)
	ON_EN_CHANGE(IDC_EDIT_CAPMNEM2, &CViewerCapture::OnEnChangeEditCapmnem2)
	ON_EN_CHANGE(IDC_EDIT_CAPMNEM3, &CViewerCapture::OnEnChangeEditCapmnem3)
	ON_EN_CHANGE(IDC_EDIT_CAPMNEM4, &CViewerCapture::OnEnChangeEditCapmnem4)
	ON_EN_CHANGE(IDC_EDIT_CAPMNEM5, &CViewerCapture::OnEnChangeEditCapmnem5)
	ON_EN_CHANGE(IDC_EDIT_CAPMNEM6, &CViewerCapture::OnEnChangeEditCapmnem6)
	ON_EN_CHANGE(IDC_EDIT_CAPMNEM7, &CViewerCapture::OnEnChangeEditCapmnem7)
	ON_CBN_EDITCHANGE(IDC_COMBO_CAPSCALE0, &CViewerCapture::OnCbnEditchangeComboCapscale0)
	ON_CBN_EDITCHANGE(IDC_COMBO_CAPSCALE1, &CViewerCapture::OnCbnEditchangeComboCapscale1)
	ON_CBN_EDITCHANGE(IDC_COMBO_CAPSCALE2, &CViewerCapture::OnCbnEditchangeComboCapscale2)
	ON_CBN_EDITCHANGE(IDC_COMBO_CAPSCALE3, &CViewerCapture::OnCbnEditchangeComboCapscale3)
	ON_CBN_EDITCHANGE(IDC_COMBO_CAPSCALE4, &CViewerCapture::OnCbnEditchangeComboCapscale4)
	ON_CBN_EDITCHANGE(IDC_COMBO_CAPSCALE5, &CViewerCapture::OnCbnEditchangeComboCapscale5)
	ON_CBN_EDITCHANGE(IDC_COMBO_CAPSCALE6, &CViewerCapture::OnCbnEditchangeComboCapscale6)
	ON_CBN_EDITCHANGE(IDC_COMBO_CAPSCALE7, &CViewerCapture::OnCbnEditchangeComboCapscale7)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_CAPSCALE0, &CViewerCapture::OnDeltaposSpinCapscale0)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_CAPSCALE1, &CViewerCapture::OnDeltaposSpinCapscale1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_CAPSCALE2, &CViewerCapture::OnDeltaposSpinCapscale2)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_CAPSCALE3, &CViewerCapture::OnDeltaposSpinCapscale3)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_CAPSCALE4, &CViewerCapture::OnDeltaposSpinCapscale4)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_CAPSCALE5, &CViewerCapture::OnDeltaposSpinCapscale5)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_CAPSCALE6, &CViewerCapture::OnDeltaposSpinCapscale6)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_CAPSCALE7, &CViewerCapture::OnDeltaposSpinCapscale7)
	ON_CBN_EDITCHANGE(IDC_COMBO_CAPOFFSET0, &CViewerCapture::OnCbnEditchangeComboCapoffset0)
	ON_CBN_EDITCHANGE(IDC_COMBO_CAPOFFSET1, &CViewerCapture::OnCbnEditchangeComboCapoffset1)
	ON_CBN_EDITCHANGE(IDC_COMBO_CAPOFFSET2, &CViewerCapture::OnCbnEditchangeComboCapoffset2)
	ON_CBN_EDITCHANGE(IDC_COMBO_CAPOFFSET3, &CViewerCapture::OnCbnEditchangeComboCapoffset3)
	ON_CBN_EDITCHANGE(IDC_COMBO_CAPOFFSET4, &CViewerCapture::OnCbnEditchangeComboCapoffset4)
	ON_CBN_EDITCHANGE(IDC_COMBO_CAPOFFSET5, &CViewerCapture::OnCbnEditchangeComboCapoffset5)
	ON_CBN_EDITCHANGE(IDC_COMBO_CAPOFFSET6, &CViewerCapture::OnCbnEditchangeComboCapoffset6)
	ON_CBN_EDITCHANGE(IDC_COMBO_CAPOFFSET7, &CViewerCapture::OnCbnEditchangeComboCapoffset7)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_CAPOFFSET0, &CViewerCapture::OnDeltaposSpinCapoffset0)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_CAPOFFSET1, &CViewerCapture::OnDeltaposSpinCapoffset1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_CAPOFFSET2, &CViewerCapture::OnDeltaposSpinCapoffset2)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_CAPOFFSET3, &CViewerCapture::OnDeltaposSpinCapoffset3)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_CAPOFFSET4, &CViewerCapture::OnDeltaposSpinCapoffset4)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_CAPOFFSET5, &CViewerCapture::OnDeltaposSpinCapoffset5)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_CAPOFFSET6, &CViewerCapture::OnDeltaposSpinCapoffset6)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_CAPOFFSET7, &CViewerCapture::OnDeltaposSpinCapoffset7)
	ON_CBN_SELCHANGE(IDC_COMBO_CAPTYPE0, &CViewerCapture::OnCbnSelchangeComboCaptype0)
	ON_CBN_SELCHANGE(IDC_COMBO_CAPTYPE1, &CViewerCapture::OnCbnSelchangeComboCaptype1)
	ON_CBN_SELCHANGE(IDC_COMBO_CAPTYPE2, &CViewerCapture::OnCbnSelchangeComboCaptype2)
	ON_CBN_SELCHANGE(IDC_COMBO_CAPTYPE3, &CViewerCapture::OnCbnSelchangeComboCaptype3)
	ON_CBN_SELCHANGE(IDC_COMBO_CAPTYPE4, &CViewerCapture::OnCbnSelchangeComboCaptype4)
	ON_CBN_SELCHANGE(IDC_COMBO_CAPTYPE5, &CViewerCapture::OnCbnSelchangeComboCaptype5)
	ON_CBN_SELCHANGE(IDC_COMBO_CAPTYPE6, &CViewerCapture::OnCbnSelchangeComboCaptype6)
	ON_CBN_SELCHANGE(IDC_COMBO_CAPTYPE7, &CViewerCapture::OnCbnSelchangeComboCaptype7)
END_MESSAGE_MAP()


// CViewerCapture 메시지 처리기입니다.


BOOL CViewerCapture::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	pViewerCapture = this;

	iSpinMin = -99999999;
	iSpinMax = 999999999;

	int	i = 0;
	CString str = _T("");

	for (i = 0; i < CHANNELTOTAL; i++)
	{
		str.Format(_T("Mnem%d"), i);
		m_Edit_Mnem[i].SetWindowTextW(str);
		m_Cbo_Scale[i].SetWindowTextW(_T("0"));
		m_Cbo_Offset[i].SetWindowTextW(_T("0"));
		m_ChCap[i].strMnem = _T("");
		m_ChCap[i].strScale = _T("0");
		m_ChCap[i].strOffset = _T("0");

		m_Spin_Scale[i].SetRange((short)iSpinMax, (short)iSpinMin);
		m_Spin_Scale[i].SetPos(0);

		m_Spin_Offset[i].SetRange((short)iSpinMax, (short)iSpinMin);
		m_Spin_Offset[i].SetPos(0);

		m_Cbo_Type[i].InsertString(0, CBO_TYPE[0]);
		m_Cbo_Type[i].InsertString(1, CBO_TYPE[1]);
		m_Cbo_Type[i].SetCurSel(DEF_TYPE);

		EnableChannel(i, FALSE);
	}

	m_bCaptureCh = FALSE;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL CViewerCapture::PreTranslateMessage(MSG* pMsg)
{
	if (DefaultWindowMessage(pMsg))	return TRUE;
	else							return CDialogEx::PreTranslateMessage(pMsg);
}


void CViewerCapture::OnBnClickedButtonLoadcap()
{
	CString strCapFile = _T("");
	CString strDefExt = _T("cap");
	CString strFilter = _T("Capture file(*.cap)|*.cap||");

	// Open Dialog
	if (!ShowOpenFileDlg(&strCapFile, strDefExt, strFilter, this))
		return;

	// Open
	m_bCaptureCh = OpenCap(strCapFile);

	for (int i = 0; i < CHANNELTOTAL; i++)
		EnableChannel(i, m_ChCap[i].bCh);

	pViewerDlg->m_bUpdateCapture = TRUE;

	RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}


BOOL CViewerCapture::OpenCap(CString strPath)
{
	CStdioFile strFile;
	strFile.Open(strPath, CFile::modeRead);

	int i = 0;
	int j = 0;
	int iR = 0;
	int iG = 0;
	int iB = 0;
	int iS = 0;
	int iNum = 0;
	int iStg = 0;
	int iStgCnt = 0;
	CString str = _T("");
	CString	strLine[4];

	// 초기화
	for (i = 0; i < CHANNELTOTAL; i++)
	{
		// Use Channel
		m_Chk_Ch[i].SetCheck(FALSE);

		// Mnem
		str.Format(_T("Mnem%d"), i);
		m_Edit_Mnem[i].SetWindowTextW(str);
		m_ChCap[i].strMnem = str;

		// Color
		iR = GetRValue(pViewerSet->m_Ch[i].crColor);
		iG = GetGValue(pViewerSet->m_Ch[i].crColor);
		iB = GetBValue(pViewerSet->m_Ch[i].crColor);

		iR -= iR / 2;
		iG -= iG / 2;
		iB -= iB / 2;

		if (iR < 0) { iR = 0; }
		else if (iR > 255) { iR = 255; }
		if (iG < 0) { iG = 0; }
		else if (iG > 255) { iG = 255; }
		if (iB < 0) { iB = 0; }
		else if (iB > 255) { iB = 255; }

		m_ChCap[i].crColor = RGB(iR, iG, iB);

		// Scale
		m_Cbo_Scale[i].SetWindowTextW(_T("1"));
		m_ChCap[i].strScale = _T("1");

		// Offset
		m_Cbo_Offset[i].SetWindowTextW(_T("0"));
		m_ChCap[i].strOffset = _T("0");

		// Data Value
		for (j = 0; j < DRAWWIDTH; j++)
			m_ChannelCap[i][j].m_int = 0;
	}

	iStgCnt = 0;
	while (strFile.ReadString(str))
	{
		if (str == _T("")) continue;

		switch (iStg)
		{
			// Find <Set>
			// Pre Flag
		case 0:
			if (str.Find(_T("<Set>")) >= 0)
			{
				iStg = 1;
				break;
			}
			break;

			// <Set>
			// Option
		case 1:
			if ((str.Find(_T("</Set>")) >= 0) || iStgCnt == 8)
			{
				iStg = 2;
				break;
			}

			// strLine 초기화
			for (i = 0; i < 4; i++) strLine[i] = _T("");

			// Mnem, Scale, Offset, Type 설정
			for (i = 0; i < 4; i++)
			{
				str = str.TrimLeft();
				iS = str.FindOneOf(_T("\t "));

				if (iS == -1)
				{
					if (!str.GetLength()) break;
					else strLine[i] = str;
				}
				else
				{
					strLine[i] = str.Left(iS);
					str = str.Right(str.GetLength() - iS);
				}
			}

			if (strLine[0] == _T("") || strLine[0] == _T("_")) strLine[0].Format(_T("Mnem%d"), iStgCnt);

			// Use Channel
			EnableChannel(iStgCnt, TRUE);

			// Mnem
			m_Edit_Mnem[iStgCnt].SetWindowTextW(strLine[0]);
			m_ChCap[iStgCnt].strMnem = strLine[0];

			// Scale
			m_Cbo_Scale[iStgCnt].SetWindowTextW(strLine[1]);
			m_ChCap[iStgCnt].strScale = strLine[1];

			// Offset
			m_Cbo_Offset[iStgCnt].SetWindowTextW(strLine[2]);
			m_ChCap[iStgCnt].strOffset = strLine[2];

			// Type 
			for (i = 0; i < NUM_TYPE; i++) {
				if (strLine[3] == CBO_TYPE[i]) {
					m_Cbo_Type[iStgCnt].SetWindowTextW(CBO_TYPE[i]);
					m_ChCap[iStgCnt].strType = CBO_TYPE[i];
					break;
				}
			}
			if (i == NUM_TYPE) {
				m_Cbo_Type[iStgCnt].SetWindowTextW(CBO_TYPE[DEF_TYPE]);
				m_ChCap[iStgCnt].strType = CBO_TYPE[DEF_TYPE];
			}

			iStgCnt++;

			break;

		case 2:
			if ((str.Find(_T("<Data>")) >= 0))
			{
				iStg = 3;
				iS = 0;
				break;
			}

			break;

		case 3:
			if ((str.Find(_T("</Data>")) >= 0) || iStgCnt == DRAWWIDTH)
			{
				//iStg = 6;
				break;
			}

			str = str.TrimLeft();
			iS = str.FindOneOf(_T("\t "));

			if (iS == -1)
			{
				if (str.GetLength()) break;
				else iNum = _ttoi(str);
			}
			else
			{
				iNum = _ttoi(str.Left(iS));
				str = str.Right(str.GetLength() - iS);
			}

			for (i = 0; i < CHANNELTOTAL; i++)
			{
				str = str.TrimLeft();
				iS = str.FindOneOf(_T("\t "));

				if (iS == -1)
				{
					if (str.GetLength()) break;
					else{
						if (m_ChCap[i].strType == CBO_TYPE[1])	m_ChannelCap[i][iNum].m_float = _ttof(str);
						else									m_ChannelCap[i][iNum].m_int = _ttoi(str);
					}
				}
				else
				{
					if (m_ChCap[i].strType == CBO_TYPE[1])	m_ChannelCap[i][iNum].m_float = _ttof(str.Left(iS));
					else									m_ChannelCap[i][iNum].m_int = _ttoi(str.Left(iS));

					str = str.Right(str.GetLength() - iS);
				}
			}

			break;
		default:
			return FALSE;
		}
	}

	return TRUE;
}


void CViewerCapture::OnBnClickedButtonCapture()
{
	if (!ConnectSocket)
	{
		AfxMessageBox(_T("Check Server connection!"));
		return;
	}

	BOOL bGraph = FALSE;
	if (pViewerDlg->m_bStartGraph)
	{
		pViewerDlg->OnBnClickedButtonViewerstart();
		bGraph = TRUE;
	}

	CString strCapFile = _T("");
	CString strDefExt = _T("cap");
	CString strFilter = _T("Capture File(*.cap)|*.cap||");

	// Save Dialog
	if (!ShowSaveFileDlg(&strCapFile, strDefExt, strFilter, this))
	{
		if (bGraph)
			pViewerDlg->OnBnClickedButtonViewerstart();
		return;
	}

	// Save
	CStdioFile strFile;
	if (!strFile.Open(strCapFile, CFile::modeReadWrite | CFile::modeCreate))
	{
		if (bGraph)
			pViewerDlg->OnBnClickedButtonViewerstart();
		return;
	}

	int i = 0;
	int j = 0;
	int cnt = 0;
	CString str = _T("");
	CString	strLine = _T("");

	CString strMnem = _T("");
	CString strScale = _T("");
	CString strOffset = _T("");
	CString strType = _T("");

	// Set
	strFile.WriteString(_T("<Set>\n"));
	for (i = 0; i < CHANNELTOTAL; i++)
	{
		if (pViewerSet->m_Ch[i].bCh)
		{
			m_Edit_Mnem[i].GetWindowTextW(strMnem);
			m_Cbo_Scale[i].GetWindowTextW(strScale);
			m_Cbo_Offset[i].GetWindowTextW(strOffset);
			m_Cbo_Type[i].GetWindowTextW(strType);

			str.Format(_T("%s\t%s\t%s\t%s\n"), strMnem, strScale, strOffset, strType);

			strFile.WriteString(str);
		}
	}
	strFile.WriteString(_T("</Set>\n"));

	// Data
	strFile.WriteString(_T("<Data>\n"));

	for (i = pViewerDlg->m_buffIndex + 1; cnt < DRAWWIDTH; cnt++, i++)
	{
		if (i > DRAWWIDTH - 1) i = 0;

		strLine.Format(_T("%d"), cnt);
		for (j = 0; j < CHANNELTOTAL; j++)
		{
			if (pViewerSet->m_Ch[j].strType == CBO_TYPE[1]) // Float
			{
				str.Format(_T("\t%10f"), pViewerDlg->m_Channel[j][i].m_float);
				strLine = strLine + str;
			}
			else
			{
				str.Format(_T("\t%10d"), pViewerDlg->m_Channel[j][i].m_int);
				strLine = strLine + str;
			}
		}
		strFile.WriteString(strLine + _T("\n"));
	}

	strFile.WriteString(_T("</Data>\n"));
	strFile.Close();

	pViewerCapture->RedrawWindow();

	if (bGraph) { pViewerDlg->OnBnClickedButtonViewerstart(); }
}



void CViewerCapture::OnBnClickedCheckCapch0()	{ OnBnClickedCheckCapch(0); }
void CViewerCapture::OnBnClickedCheckCapch1()	{ OnBnClickedCheckCapch(1); }
void CViewerCapture::OnBnClickedCheckCapch2()	{ OnBnClickedCheckCapch(2); }
void CViewerCapture::OnBnClickedCheckCapch3()	{ OnBnClickedCheckCapch(3); }
void CViewerCapture::OnBnClickedCheckCapch4()	{ OnBnClickedCheckCapch(4); }
void CViewerCapture::OnBnClickedCheckCapch5()	{ OnBnClickedCheckCapch(5); }
void CViewerCapture::OnBnClickedCheckCapch6()	{ OnBnClickedCheckCapch(6); }
void CViewerCapture::OnBnClickedCheckCapch7()	{ OnBnClickedCheckCapch(7); }
void CViewerCapture::OnBnClickedCheckCapch(int iNum)
{
	m_ChCap[iNum].bCh = m_Chk_Ch[iNum].GetCheck();

	EnableChannel(iNum, m_ChCap[iNum].bCh);

	pViewerDlg->m_bUpdateCapture = TRUE;

	RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}


void CViewerCapture::EnableChannel(int iNum, BOOL b)
{
	m_Chk_Ch[iNum].SetCheck(b);

	m_Edit_Mnem[iNum].EnableWindow(b);
	m_Cbo_Scale[iNum].EnableWindow(b);
	m_Spin_Scale[iNum].EnableWindow(b);
	m_Cbo_Offset[iNum].EnableWindow(b);
	m_Spin_Offset[iNum].EnableWindow(b);
	m_Cbo_Type[iNum].EnableWindow(b);
}


void CViewerCapture::OnEnChangeEditCapmnem0()	{ OnEnChangeEditCapmnem(0); }
void CViewerCapture::OnEnChangeEditCapmnem1()	{ OnEnChangeEditCapmnem(1); }
void CViewerCapture::OnEnChangeEditCapmnem2()	{ OnEnChangeEditCapmnem(2); }
void CViewerCapture::OnEnChangeEditCapmnem3()	{ OnEnChangeEditCapmnem(3); }
void CViewerCapture::OnEnChangeEditCapmnem4()	{ OnEnChangeEditCapmnem(4); }
void CViewerCapture::OnEnChangeEditCapmnem5()	{ OnEnChangeEditCapmnem(5); }
void CViewerCapture::OnEnChangeEditCapmnem6()	{ OnEnChangeEditCapmnem(6); }
void CViewerCapture::OnEnChangeEditCapmnem7()	{ OnEnChangeEditCapmnem(7); }
void CViewerCapture::OnEnChangeEditCapmnem(int iNum)
{
	CString str = _T("");

	// 저장
	m_Edit_Mnem[iNum].GetWindowTextW(str);
	m_ChCap[iNum].strMnem = str;

	// Drawviewer Update Flag
	pViewerDlg->m_bUpdateCapture = TRUE;
}


void CViewerCapture::OnCbnEditchangeComboCapscale0()	{ OnCbnEditchangeComboCapscale(0); }
void CViewerCapture::OnCbnEditchangeComboCapscale1()	{ OnCbnEditchangeComboCapscale(1); }
void CViewerCapture::OnCbnEditchangeComboCapscale2()	{ OnCbnEditchangeComboCapscale(2); }
void CViewerCapture::OnCbnEditchangeComboCapscale3()	{ OnCbnEditchangeComboCapscale(3); }
void CViewerCapture::OnCbnEditchangeComboCapscale4()	{ OnCbnEditchangeComboCapscale(4); }
void CViewerCapture::OnCbnEditchangeComboCapscale5()	{ OnCbnEditchangeComboCapscale(5); }
void CViewerCapture::OnCbnEditchangeComboCapscale6()	{ OnCbnEditchangeComboCapscale(6); }
void CViewerCapture::OnCbnEditchangeComboCapscale7()	{ OnCbnEditchangeComboCapscale(7); }
void CViewerCapture::OnCbnEditchangeComboCapscale(int iNum)
{
	CString str = _T("");

	// 저장
	m_Cbo_Scale[iNum].GetWindowTextW(str);
	m_ChCap[iNum].strScale = str;

	// DrawViewer Update Flag
	pViewerDlg->m_bUpdateCapture = TRUE;
}


void CViewerCapture::OnDeltaposSpinCapscale0(NMHDR *pNMHDR, LRESULT *pResult)
{ OnDeltaposSpinCapscale(pNMHDR, pResult, 0); *pResult = 0; }
void CViewerCapture::OnDeltaposSpinCapscale1(NMHDR *pNMHDR, LRESULT *pResult)
{ OnDeltaposSpinCapscale(pNMHDR, pResult, 1); *pResult = 0; }
void CViewerCapture::OnDeltaposSpinCapscale2(NMHDR *pNMHDR, LRESULT *pResult)
{ OnDeltaposSpinCapscale(pNMHDR, pResult, 2); *pResult = 0; }
void CViewerCapture::OnDeltaposSpinCapscale3(NMHDR *pNMHDR, LRESULT *pResult)
{ OnDeltaposSpinCapscale(pNMHDR, pResult, 3); *pResult = 0; }
void CViewerCapture::OnDeltaposSpinCapscale4(NMHDR *pNMHDR, LRESULT *pResult)
{ OnDeltaposSpinCapscale(pNMHDR, pResult, 4); *pResult = 0; }
void CViewerCapture::OnDeltaposSpinCapscale5(NMHDR *pNMHDR, LRESULT *pResult)
{ OnDeltaposSpinCapscale(pNMHDR, pResult, 5); *pResult = 0; }
void CViewerCapture::OnDeltaposSpinCapscale6(NMHDR *pNMHDR, LRESULT *pResult)
{ OnDeltaposSpinCapscale(pNMHDR, pResult, 6); *pResult = 0; }
void CViewerCapture::OnDeltaposSpinCapscale7(NMHDR *pNMHDR, LRESULT *pResult)
{ OnDeltaposSpinCapscale(pNMHDR, pResult, 7); *pResult = 0; }
void CViewerCapture::OnDeltaposSpinCapscale(NMHDR *pNMHDR, LRESULT *pResult, int iNum)
{
	LPNMUPDOWN	pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	int iScale = _ttoi(m_ChCap[iNum].strScale);
	int iDelta = pNMUpDown->iDelta;
	CString	str = _T("");

	if (iDelta)
	{
		if (iScale <= pViewerSet->m_iSpinMax - iDelta &&
			iScale >= pViewerSet->m_iSpinMin + iDelta)
		{
			iScale += iDelta;
			str.Format(_T("%d"), iScale);
		}
	}

	m_Cbo_Scale[iNum].SetWindowTextW(str);
	m_ChCap[iNum].strScale = str;

	OnCbnEditchangeComboCapscale(iNum);
}

void CViewerCapture::OnCbnEditchangeComboCapoffset0()	{ OnCbnEditchangeComboCapoffset(0); }
void CViewerCapture::OnCbnEditchangeComboCapoffset1()	{ OnCbnEditchangeComboCapoffset(1); }
void CViewerCapture::OnCbnEditchangeComboCapoffset2()	{ OnCbnEditchangeComboCapoffset(2); }
void CViewerCapture::OnCbnEditchangeComboCapoffset3()	{ OnCbnEditchangeComboCapoffset(3); }
void CViewerCapture::OnCbnEditchangeComboCapoffset4()	{ OnCbnEditchangeComboCapoffset(4); }
void CViewerCapture::OnCbnEditchangeComboCapoffset5()	{ OnCbnEditchangeComboCapoffset(5); }
void CViewerCapture::OnCbnEditchangeComboCapoffset6()	{ OnCbnEditchangeComboCapoffset(6); }
void CViewerCapture::OnCbnEditchangeComboCapoffset7()	{ OnCbnEditchangeComboCapoffset(7); }
void CViewerCapture::OnCbnEditchangeComboCapoffset(int iNum)
{
	CString str = _T("");

	// 저장
	m_Cbo_Offset[iNum].GetWindowTextW(str);
	m_ChCap[iNum].strOffset = str;

	// DrawViewer Update Flag
	pViewerDlg->m_bUpdateCapture = TRUE;
}


void CViewerCapture::OnDeltaposSpinCapoffset0(NMHDR *pNMHDR, LRESULT *pResult)
{	OnDeltaposSpinCapoffset(pNMHDR, pResult, 0);  *pResult = 0;	}
void CViewerCapture::OnDeltaposSpinCapoffset1(NMHDR *pNMHDR, LRESULT *pResult)
{	OnDeltaposSpinCapoffset(pNMHDR, pResult, 1);  *pResult = 0; }
void CViewerCapture::OnDeltaposSpinCapoffset2(NMHDR *pNMHDR, LRESULT *pResult)
{	OnDeltaposSpinCapoffset(pNMHDR, pResult, 2);  *pResult = 0; }
void CViewerCapture::OnDeltaposSpinCapoffset3(NMHDR *pNMHDR, LRESULT *pResult)
{	OnDeltaposSpinCapoffset(pNMHDR, pResult, 3);  *pResult = 0; }
void CViewerCapture::OnDeltaposSpinCapoffset4(NMHDR *pNMHDR, LRESULT *pResult)
{	OnDeltaposSpinCapoffset(pNMHDR, pResult, 4);  *pResult = 0; }
void CViewerCapture::OnDeltaposSpinCapoffset5(NMHDR *pNMHDR, LRESULT *pResult)
{	OnDeltaposSpinCapoffset(pNMHDR, pResult, 5);  *pResult = 0; }
void CViewerCapture::OnDeltaposSpinCapoffset6(NMHDR *pNMHDR, LRESULT *pResult)
{	OnDeltaposSpinCapoffset(pNMHDR, pResult, 6);  *pResult = 0; }
void CViewerCapture::OnDeltaposSpinCapoffset7(NMHDR *pNMHDR, LRESULT *pResult)
{	OnDeltaposSpinCapoffset(pNMHDR, pResult, 7);  *pResult = 0; }
void CViewerCapture::OnDeltaposSpinCapoffset(NMHDR *pNMHDR, LRESULT *pResult, int iNum)
{
	LPNMUPDOWN	pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	int	iOffset = _ttoi(m_ChCap[iNum].strOffset);
	int	iDelta = pNMUpDown->iDelta;
	CString	str = _T("");

	if (iDelta)
	{
		if (iOffset <= pViewerSet->m_iSpinMax - iDelta &&
			iOffset >= pViewerSet->m_iSpinMin + iDelta)
		{
			iOffset += iDelta;
			str.Format(_T("%d"), iOffset);
		}
	}

	m_Cbo_Offset[iNum].SetWindowTextW(str);
	m_ChCap[iNum].strOffset = str;

	OnCbnEditchangeComboCapoffset(iNum);
}


void CViewerCapture::OnCbnSelchangeComboCaptype0()	{ OnCbnSelchangeComboCaptype(0); }
void CViewerCapture::OnCbnSelchangeComboCaptype1()	{ OnCbnSelchangeComboCaptype(1); }
void CViewerCapture::OnCbnSelchangeComboCaptype2()	{ OnCbnSelchangeComboCaptype(2); }
void CViewerCapture::OnCbnSelchangeComboCaptype3()	{ OnCbnSelchangeComboCaptype(3); }
void CViewerCapture::OnCbnSelchangeComboCaptype4()	{ OnCbnSelchangeComboCaptype(4); }
void CViewerCapture::OnCbnSelchangeComboCaptype5()	{ OnCbnSelchangeComboCaptype(5); }
void CViewerCapture::OnCbnSelchangeComboCaptype6()	{ OnCbnSelchangeComboCaptype(6); }
void CViewerCapture::OnCbnSelchangeComboCaptype7()	{ OnCbnSelchangeComboCaptype(7); }
void CViewerCapture::OnCbnSelchangeComboCaptype(int iNum)
{
	m_ChCap[iNum].strType = CBO_TYPE[m_Cbo_Type[iNum].GetCurSel()];

	pViewerDlg->m_bUpdateCapture = TRUE;
}