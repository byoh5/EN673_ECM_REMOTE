// SettingDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ECM_remote.h"
#include "SettingDlg.h"
#include "afxdialogex.h"


// CSettingDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSettingDlg, CDialogEx)

CSettingDlg::CSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSettingDlg::IDD, pParent)
{

}

CSettingDlg::~CSettingDlg()
{
}

void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_EXROCDVIEW, m_Chk_EXROCDView);
	DDX_Control(pDX, IDC_EDIT_PARAMETERKEY, m_Edit_Key);
	DDX_Control(pDX, IDC_CHECK_KEYSHOW, m_Chk_ShowKey);
	DDX_Control(pDX, IDC_CHECK_VIEWERSTART, m_Chk_ViewerStart);
	DDX_Control(pDX, IDC_CHECK_PRINTSTART, m_Chk_PrintStart);
	DDX_Control(pDX, IDC_EDIT_PRINTSAVEPATH, m_Edit_PrintSavePath);
	DDX_Control(pDX, IDC_EDIT_ANALYZESAVEPATH, m_Edit_AnalyzeSavePath);
	DDX_Control(pDX, IDC_BUTTON_OPENPRINTPATH, m_Btn_OpenPrintPath);
	DDX_Control(pDX, IDC_BUTTON_OPENANALYZEPATH, m_Btn_OpenAnalyzePath);
	DDX_Control(pDX, IDC_CHECK_AUTOSAVE, m_Chk_AutoSave);
	DDX_Control(pDX, IDC_CHECK_VECTORSCOPE, m_Chk_Vectorscope);
	DDX_Control(pDX, IDC_CHECK_WAVEFORMR, m_Chk_WaveformR);
	DDX_Control(pDX, IDC_CHECK_WAVEFORMG, m_Chk_WaveformG);
	DDX_Control(pDX, IDC_CHECK_WAVEFORMB, m_Chk_WaveformB);
	DDX_Control(pDX, IDC_CHECK_WAVEFORMY, m_Chk_WaveformY);
	DDX_Control(pDX, IDC_COMBO_MAINPLATFORM, m_Cbo_Platform);
	DDX_Control(pDX, IDC_COMBO_JTAGCLKDIV, m_Cbo_JTAGClkdiv);
}


BEGIN_MESSAGE_MAP(CSettingDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSettingDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_OPENPRINTPATH, &CSettingDlg::OnBnClickedButtonOpenprintpath)
	ON_BN_CLICKED(IDC_BUTTON_OPENANALYZEPATH, &CSettingDlg::OnBnClickedButtonOpenanalyzepath)
	ON_BN_CLICKED(IDC_CHECK_AUTOSAVE, &CSettingDlg::OnBnClickedCheckAutosave)
	ON_BN_CLICKED(IDC_CHECK_KEYSHOW, &CSettingDlg::OnBnClickedCheckKeyshow)
	ON_BN_CLICKED(IDCANCEL, &CSettingDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CSettingDlg 메시지 처리기입니다.


BOOL CSettingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	m_Btn_OpenPrintPath.SetBitmaps(IDB_OPEN, RGB(255, 0, 255));
	m_Btn_OpenAnalyzePath.SetBitmaps(IDB_OPEN, RGB(255, 0, 255));

	CString strPrintPath = _T("");
	CString strAnalyzePath = _T("");

	int i = 0;
	CString str = _T("");

	// Get 'My Document'
	TCHAR szPath[MAX_PATH];
	SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, 0, szPath);

	CString strDirectory = _T("");
	strDirectory.Format(_T("%s\\ecm_retome"), szPath);

	strPrintPath.Format(_T("%s\\ecm_retome\\jtagprint"), szPath);
	strAnalyzePath.Format(_T("%s\\ecm_retome\\analyze"), szPath);

	// Platform
	for (i = 0; i < NUM_PLATFORM; i++)
		m_Cbo_Platform.AddString(CBO_PLATFORM[i]);
	i = ReadIni(SEC_SETTING, KEY_PLATFORM, DEF_PLATFORM);
	m_Cbo_Platform.SetCurSel(i);

	// JTAGClkdiv
	for (i = 0; i < NUM_JTAGCLKDIV; i++)
		m_Cbo_JTAGClkdiv.AddString(CBO_JTAGCLKDIV[i]);
	i = ReadIni(SEC_SETTING, KEY_JTAGCLKDIV, DEF_JTAGCLKDIV);
	m_Cbo_JTAGClkdiv.SetCurSel(i);

	// EXROCD Window View
	i = ReadIni(SEC_SETTING, KEY_EXROCD, DEF_EXROCD);
	m_Chk_EXROCDView.SetCheck(i);

	// Parameter Key
	m_Edit_Key.SetLimitText(8);
	m_Edit_Key.SetPasswordChar('*');
#if 0
	str = ReadIni(SEC_SETTING, KEY_PARAMETERKEY, DEF_PARAMETERKEY);
	if (str != DEF_PARAMETERKEY)
		str = OpenKey(str);
	m_Edit_Key.SetWindowTextW(str);
#else
	m_strKey = _T("");
	m_strKeyPw = _T("");
	OpenKeyFile();
	m_Edit_Key.SetWindowTextW(m_strKey);
#endif

	// Parameter Key Show
	i = ReadIni(SEC_SETTING, KEY_PARAMETERKEYSHOW, DEF_PARAMETERKEYSHOW);
	m_Chk_ShowKey.SetCheck(i);
	OnBnClickedCheckKeyshow();
	
	// Viewer Start Check
	i = ReadIni(SEC_SETTING, KEY_VIEWERSTART, DEF_VIEWERSTART);
	m_Chk_ViewerStart.SetCheck(i);
	
	// Print Start Check
	i = ReadIni(SEC_SETTING, KEY_PRINTSTART, DEF_PRINTSTART);
	m_Chk_PrintStart.SetCheck(i);

	// Auto Save ON Check
	i = ReadIni(SEC_SETTING, KEY_PRINTAUTOSAVE, DEF_PRINTAUTOSAVE);
	m_Chk_AutoSave.SetCheck(i);

	// Print Auto Save Path
	str = ReadIni(SEC_SETTING, KEY_PRINTSAVEPATH, strPrintPath);
	m_Edit_PrintSavePath.SetWindowTextW(str);

	if (!m_Chk_AutoSave.GetCheck())
	{
		m_Edit_PrintSavePath.EnableWindow(FALSE);
		m_Btn_OpenPrintPath.EnableWindow(FALSE);
	}

	// Vectorscope
	i = ReadIni(SEC_ANALYZE, KEY_VECTORSCOPE, DEF_VECTORSCOPE);
	m_Chk_Vectorscope.SetCheck(i);
	// WaveformR
	i = ReadIni(SEC_ANALYZE, KEY_WAVEFORM_R, DEF_WAVEFORM_R);
	m_Chk_WaveformR.SetCheck(i);
	// WaveformG
	i = ReadIni(SEC_ANALYZE, KEY_WAVEFORM_G, DEF_WAVEFORM_G);
	m_Chk_WaveformG.SetCheck(i);
	// WaveformB
	i = ReadIni(SEC_ANALYZE, KEY_WAVEFORM_B, DEF_WAVEFORM_B);
	m_Chk_WaveformB.SetCheck(i);
	// WaveformY
	i = ReadIni(SEC_ANALYZE, KEY_WAVEFORM_Y, DEF_WAVEFORM_Y);
	m_Chk_WaveformY.SetCheck(i);

	// Analyze Image Save Path
	str = ReadIni(SEC_SETTING, KEY_ANALYZESAVEPATH, strAnalyzePath);
	m_Edit_AnalyzeSavePath.SetWindowTextW(str);


	// 형태만 만들어 둠. 동작은 아직 미활성화
	m_Cbo_Platform.EnableWindow(FALSE);
	//m_Cbo_JTAGClkdiv.EnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL CSettingDlg::PreTranslateMessage(MSG* pMsg)
{
	switch (pMsg->wParam)
	{
	case VK_ESCAPE:
	case VK_RETURN:
		return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CSettingDlg::OnBnClickedOk()
{
	int i = 0;
	CString str = _T("");

	// Platform
	i = m_Cbo_Platform.GetCurSel();
	WriteIni(SEC_SETTING, KEY_PLATFORM, i);

	// JTAGClkdiv
	i = m_Cbo_JTAGClkdiv.GetCurSel();
	WriteIni(SEC_SETTING, KEY_JTAGCLKDIV, i);

	// EXR OCD Window View
	i = m_Chk_EXROCDView.GetCheck();
	WriteIni(SEC_SETTING, KEY_EXROCD, i);

	// Parameter Key
#if 0
	m_Edit_Key.GetWindowTextW(str);
	str = SaveKey(str);
	WriteIni(SEC_SETTING, KEY_PARAMETERKEY, str);
#else
	// ----------------------------------------------------------------------------------------------------
	// Parameter Key
	m_Edit_Key.GetWindowTextW(str);
	m_strKey = str;
	SaveKeyFile();
#endif
	// Parameter Key Show
	i = m_Chk_ShowKey.GetCheck();
	WriteIni(SEC_SETTING, KEY_PARAMETERKEYSHOW, i);

	// Viewer Start Check
	i = m_Chk_ViewerStart.GetCheck();
	WriteIni(SEC_SETTING, KEY_VIEWERSTART, i);

	// Print Start Check
	i = m_Chk_PrintStart.GetCheck();
	WriteIni(SEC_SETTING, KEY_PRINTSTART, i);

	// Auto Save ON Check
	i = m_Chk_AutoSave.GetCheck();
	WriteIni(SEC_SETTING, KEY_PRINTAUTOSAVE, i);

	// Print Auto Save Path
	m_Edit_PrintSavePath.GetWindowTextW(str);
	WriteIni(SEC_SETTING, KEY_PRINTSAVEPATH, str);
	
	// Vectorscope
	WriteIni(SEC_ANALYZE, KEY_VECTORSCOPE, m_Chk_Vectorscope.GetCheck());

	// WaveformR
	WriteIni(SEC_ANALYZE, KEY_WAVEFORM_R, m_Chk_WaveformR.GetCheck());

	// WaveformG
	WriteIni(SEC_ANALYZE, KEY_WAVEFORM_G, m_Chk_WaveformG.GetCheck());

	// WaveformB
	WriteIni(SEC_ANALYZE, KEY_WAVEFORM_B, m_Chk_WaveformB.GetCheck());

	// WaveformY
	WriteIni(SEC_ANALYZE, KEY_WAVEFORM_Y, m_Chk_WaveformY.GetCheck());

	// Analyze Image Save Path
	m_Edit_AnalyzeSavePath.GetWindowTextW(str);
	WriteIni(SEC_SETTING, KEY_ANALYZESAVEPATH, str);

	CDialogEx::OnOK();
}


// m_Edit_Key 암호화 
#define PASS_KEY 0x06730673
CString CSettingDlg::OpenKey(CString strKeyPw)
{
	CString strKey = _T("");
	//strKey = strKeyPw;

	int intKey = _ttoi(strKeyPw);
	int temp = 0;
	temp = intKey ^ PASS_KEY;

	strKey.Format(_T("%d"), temp);

	return strKey;
}


CString CSettingDlg::SaveKey(CString strKey)
{
	CString strKeyPw = _T("");
	//strKeyPw = strKey;

	int intKey = _ttoi(strKey);
	int temp = 0;
	temp = intKey ^ PASS_KEY;
	
	strKeyPw.Format(_T("%d"), temp);

	return strKeyPw;
}


void CSettingDlg::OnBnClickedCheckKeyshow()
{
	const static TCHAR cPasswordChar = m_Edit_Key.GetPasswordChar();

	if (m_Chk_ShowKey.GetCheck())
		m_Edit_Key.SetPasswordChar(NULL);			// 입력 문자 표시
	else
		m_Edit_Key.SetPasswordChar(cPasswordChar);	// 입력 문자 숨김

	m_Edit_Key.RedrawWindow();						// m_Edit_Key 컨트롤 갱신
}


void CSettingDlg::OnBnClickedButtonOpenprintpath()
{
	CString strFolderPath;

	strFolderPath = GetSelectFolderPath();

	m_Edit_PrintSavePath.SetWindowTextW(strFolderPath);
}


void CSettingDlg::OnBnClickedButtonOpenanalyzepath()
{
	CString strFolderPath;

	strFolderPath = GetSelectFolderPath();

	m_Edit_AnalyzeSavePath.SetWindowTextW(strFolderPath);
}


CString CSettingDlg::GetSelectFolderPath()
{
	CString strFolderPath;

	ITEMIDLIST *pidlBrowse;
	TCHAR       pszPathname[MAX_PATH];
	BROWSEINFO  BrInfo;

	BrInfo.hwndOwner = GetSafeHwnd();
	BrInfo.pidlRoot = NULL; //# Null이면 최초 위치는 "바탕화면"입니다.

	memset(&BrInfo, 0, sizeof(BrInfo));
	BrInfo.pszDisplayName = pszPathname;
	BrInfo.lpszTitle = _T("Select Directory");
	BrInfo.ulFlags = BIF_RETURNONLYFSDIRS;
	pidlBrowse = ::SHBrowseForFolder(&BrInfo);
	if (pidlBrowse != NULL)
	{
		SHGetPathFromIDList(pidlBrowse, pszPathname);
	}

	strFolderPath.Format(_T("%s"), pszPathname);

	return strFolderPath;
}

void CSettingDlg::OnBnClickedCheckAutosave()
{
	UpdateData(TRUE);
	m_Edit_PrintSavePath.EnableWindow(m_Chk_AutoSave.GetCheck());
	m_Btn_OpenPrintPath.EnableWindow(m_Chk_AutoSave.GetCheck());
	UpdateData(FALSE);
}


void CSettingDlg::OnBnClickedCancel()
{
	if (IDYES == AfxMessageBox(_T("Exit after saving settings?"), MB_YESNO))
		OnBnClickedOk();
	else
		CDialogEx::OnCancel();

	CDialogEx::OnCancel();
}

BOOL CheckHex(const CString& str);
DWORD HexToDec(const CString& sHex);
void CSettingDlg::OpenKeyFile()
{
	DWORD64 dwKeyPw = 0;
	CString strKeyFile = ReadIni(SEC_SETTING, KEY_PARAMETERKEY, DEF_PARAMETERKEY);
	CString strPath = _T("");
	CString str = _T("");
	CString strKeyPw = _T("");
	CString strKey = _T("");

	if (strKeyFile != _T("NULL"))
	{
		// 랜덤 Key값
		dwKeyPw = _ttoi(strKeyFile);

		// 파일 오픈
		TCHAR cDir[256];
		::GetWindowsDirectory(cDir, 256);
		strPath.Format(_T("%s\\Temp\\TFP%x.tmp"), cDir, dwKeyPw);

		CStdioFile strFile;
		if (!strFile.Open(strPath, CFile::modeRead))
			goto ERRORKEY;

		// 변환
		strFile.ReadString(str);
		strFile.Close();

		// 떼서붙임
		str = str.Right(4) + str.Left(str.GetLength() - 4);

		// 16진수 확인
		if (!CheckHex(str))
			goto ERRORKEY;

		// 16진수 -> 10진수
		DWORD64 dwKey = HexToDec(str);

		// KeyPassword 추출
		strKeyPw = str.Mid(0, 1) + str.Mid(5, 1) + str.Mid(10, 1);

		strKey = str.Mid(1, 4) + str.Mid(6, 4);
		if (!CheckHex(strKey))
			goto ERRORKEY;

		if (dwKeyPw == _ttoi(strKeyPw))
		{
			m_strKey = strKey;
			m_strKeyPw = strKeyPw;
			return;
		}
		else
			goto ERRORKEY;
	}

ERRORKEY:
	// strKeyPw
	srand((unsigned int)time(NULL));
	m_strKeyPw.Format(_T("%d"), rand() % 999 + 100); // 랜덤적용

	// default
	m_strKey = _T("12345678");
}

// ====================================================================================================
// CParameterDlg::SaveKeyFile
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CSettingDlg::SaveKeyFile()
{
	CString str = _T("");

	TCHAR cDir[256];
	::GetWindowsDirectory(cDir, 256);
	CString strPath = _T("");

	// ----------------------------------------------------------------------------------------------------
	// 변환
	// 1. KeyPw 추가
	// Key(Hex) : @
	// KeyPw(Dec) : *
	// *@@@@*@@@@*
	CString strKey = m_strKeyPw.Mid(0, 1) + m_strKey.Left(4) + m_strKeyPw.Mid(1, 1) + m_strKey.Right(4) + m_strKeyPw.Mid(2, 1);

	// 2. 떼서붙임
	str = strKey.Right(strKey.GetLength() - 4) + strKey.Left(4);

	// ----------------------------------------------------------------------------------------------------
	// 저장
	// 파일
	DWORD dwKeyPw = _ttoi(m_strKeyPw);
	strPath.Format(_T("%s\\Temp\\TFP%x.tmp"), cDir, dwKeyPw);
	CStdioFile strFile;

	if (strFile.Open(strPath, CFile::modeReadWrite | CFile::modeCreate))
	{
		strFile.WriteString(str);

		strFile.Close();
	}

	// ecm.ini
	WriteIni(SEC_SETTING, KEY_PARAMETERKEY, m_strKeyPw);
}

BOOL CheckHex(const CString& str)
{
	int i = 0;
	int iLen = str.GetLength();
	WCHAR ch = 0;
	CString strCh = 0;

	if (iLen == 0) return FALSE;

	for (i = 0; i < iLen; i++)
	{
		strCh = str.Mid(i, 1);
		ch = str.GetAt(i);
		if (!(ch >= '0' && ch <= '9' ||
			ch >= 'A' && ch <= 'F' ||
			ch >= 'a' && ch <= 'f'))
		{
			return FALSE;
		}
	}

	return TRUE;
}

DWORD HexToDec(const CString& sHex)
{
	int i = 0;
	int n = 1;
	char *string, *stopstring;
	DWORD dec = 0;
	CString str = _T("");

	for (i = sHex.GetLength(); i > 0; i--)
	{
		str = sHex.Mid(i - 1, 1);
		string = (char*)(LPCTSTR)str;
		strtod(string, &stopstring);

		dec += ((int)strtoul(string, &stopstring, 16)) * n;
		n = n * 16;
	}

	return dec;
}
