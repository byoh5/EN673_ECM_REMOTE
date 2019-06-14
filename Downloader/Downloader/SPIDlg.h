#pragma once
#include "afxwin.h"


// CSPIDlg 대화 상자입니다.

class CSPIDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSPIDlg)

public:
	CSPIDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSPIDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SPI };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CComboBox m_Cbo_Mode;
	CComboBox m_Cbo_Device;
	CComboBox m_Cbo_FrameRate;
	CComboBox m_Cbo_Resolution;
	CComboBox m_Cbo_Model;
	CComboBox m_Cbo_Control;
	CComboBox m_Cbo_Key;
	CComboBox m_Cbo_Lens;
	CComboBox m_Cbo_MotorizedModel;
	CComboBox m_Cbo_Iris;
	CComboBox m_Cbo_Tdn;
	CComboBox m_Cbo_Cds;
	CComboBox m_Cbo_Led;
	CComboBox m_Cbo_Motion;
	CComboBox m_Cbo_Shade;
	CComboBox m_Cbo_Save;
	CComboBox m_Cbo_ParUse;
	CComboBox m_Cbo_ParSave;
	CEdit m_Edit_Extend;

	void InitCombo_AddString();
	void InitCombo_Setting();
	void EnableCtrl(BOOL bEnable);


	afx_msg void OnCbnCloseupComboMode();
	afx_msg void OnCbnCloseupComboDevice();
	afx_msg void OnCbnCloseupComboFramerate();
	afx_msg void OnCbnCloseupComboResolution();
	afx_msg void OnCbnCloseupComboModel();
	afx_msg void OnCbnCloseupComboControl();
	afx_msg void OnCbnCloseupComboKey();
	afx_msg void OnCbnCloseupComboLens();
	afx_msg void OnCbnCloseupComboMotorizedmodel();
	afx_msg void OnCbnCloseupComboIris();
	afx_msg void OnCbnCloseupComboTdn();
	afx_msg void OnCbnCloseupComboCds();
	afx_msg void OnCbnCloseupComboLed();
	afx_msg void OnCbnCloseupComboMotion();
	afx_msg void OnCbnCloseupComboShade();
	afx_msg void OnCbnCloseupComboSave();
	afx_msg void OnCbnCloseupComboParuse();
	afx_msg void OnCbnCloseupComboParsave();
};
