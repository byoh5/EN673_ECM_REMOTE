#pragma once
#include "afxwin.h"


// CPeripheralDlg 대화 상자입니다.

class CPeripheralDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPeripheralDlg)

public:
	CPeripheralDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CPeripheralDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_PERIPHERAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CComboBox m_Cbo_SensorReset;
	CComboBox m_Cbo_IspIrqLed;
	CComboBox m_Cbo_EncLed;
	CComboBox m_Cbo_IcrP0;
	CComboBox m_Cbo_IcrP1;
	CComboBox m_Cbo_FocusAp;
	CComboBox m_Cbo_FocusAm;
	CComboBox m_Cbo_FocusBp;
	CComboBox m_Cbo_FocusBm;
	CComboBox m_Cbo_ZoomAp;
	CComboBox m_Cbo_ZoomAm;
	CComboBox m_Cbo_IrLed;
	CComboBox m_Cbo_ZoomBp;
	CComboBox m_Cbo_IrisPwm;
	CComboBox m_Cbo_EthIrq;
	CComboBox m_Cbo_Motion;
	CComboBox m_Cbo_UartRx1;
	CComboBox m_Cbo_UartTx1;
	CComboBox m_Cbo_I2C2Sda;
	CComboBox m_Cbo_I2C2Scl;
	CComboBox m_Cbo_ZoomBm;
	CComboBox m_Cbo_Sdio1Reset;
	CComboBox m_Cbo_EthReset;
	CComboBox m_Cbo_AudioReset;
	CComboBox m_Cbo_AdKey;
	CComboBox m_Cbo_CdsIn;
	CComboBox m_Cbo_KeyUp;
	CComboBox m_Cbo_KeyDown;
	CComboBox m_Cbo_KeyRight;
	CComboBox m_Cbo_KeyLeft;
	CComboBox m_Cbo_KeyCenter;

	void InitCombo_AddString();
	void InitCombo_Setting();
	void EnableCtrl(BOOL bEnable);
	void EnableCheckCtrl();
	afx_msg void OnCbnCloseupComboSensoereset();
	afx_msg void OnCbnCloseupComboIspirqled();
	afx_msg void OnCbnCloseupComboEncled();
	afx_msg void OnCbnCloseupComboIcrp0();
	afx_msg void OnCbnCloseupComboIcrp2();
	afx_msg void OnCbnCloseupComboFocusap();
	afx_msg void OnCbnCloseupComboFocusam();
	afx_msg void OnCbnCloseupComboFocusbp();
	afx_msg void OnCbnCloseupComboFocusbm();
	afx_msg void OnCbnCloseupComboZoomap();
	afx_msg void OnCbnCloseupComboZoomam();
	afx_msg void OnCbnCloseupComboIrled();
	afx_msg void OnCbnCloseupComboZoombp();
	afx_msg void OnCbnCloseupComboIrispwm();
	afx_msg void OnCbnCloseupComboEthirq();
	afx_msg void OnCbnCloseupComboMoction();
	afx_msg void OnCbnCloseupComboUartrx1();
	afx_msg void OnCbnCloseupComboUarttx1();
	afx_msg void OnCbnCloseupComboI2c2sda();
	afx_msg void OnCbnCloseupComboIi2c2scl();
	afx_msg void OnCbnCloseupComboZoombm();
	afx_msg void OnCbnCloseupComboSdio1reset();
	afx_msg void OnCbnCloseupComboEthreset();
	afx_msg void OnCbnCloseupComboAudioreset();
	afx_msg void OnCbnCloseupComboAdkey();
	afx_msg void OnCbnCloseupComboCdsin();
	afx_msg void OnCbnCloseupComboCenter();
	afx_msg void OnCbnCloseupComboKeyup();
	afx_msg void OnCbnCloseupComboDown();
	afx_msg void OnCbnCloseupComboKeyleft();
	afx_msg void OnCbnCloseupComboKeyright();
};
