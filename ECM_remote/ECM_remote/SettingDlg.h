#pragma once
#include "afxwin.h"
#include "BtnST.h"
#include "resource.h"

// CSettingDlg 대화 상자입니다.

class CSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSettingDlg)

public:
	CSettingDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSettingDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedCheckKeyshow();
	afx_msg void OnBnClickedCheckAutosave();
	afx_msg void OnBnClickedButtonOpenprintpath();
	afx_msg void OnBnClickedButtonOpenanalyzepath();

	CComboBox m_Cbo_Platform;
	CComboBox m_Cbo_JTAGClkdiv;
	CButton m_Chk_EXROCDView;
	CEdit m_Edit_Key;
	CButton m_Chk_ShowKey;
	CButton m_Chk_ViewerStart;
	CButton m_Chk_PrintStart;
	CButton m_Chk_AutoSave;
	CEdit m_Edit_PrintSavePath;
	CButtonST m_Btn_OpenPrintPath;
	CEdit m_Edit_AnalyzeSavePath;
	CButtonST m_Btn_OpenAnalyzePath;
	CString GetSelectFolderPath();
	CString OpenKey(CString strKeyPw);
	CString SaveKey(CString strKey);
	CButton m_Chk_Vectorscope;
	CButton m_Chk_WaveformR;
	CButton m_Chk_WaveformG;
	CButton m_Chk_WaveformB;
	CButton m_Chk_WaveformY;

	CString		m_strKey;
	CString		m_strKeyPw;
	void OpenKeyFile();
	void SaveKeyFile();
};
