// PeripheralDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Downloader.h"
#include "PeripheralDlg.h"
#include "afxdialogex.h"


// CPeripheralDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CPeripheralDlg, CDialogEx)

CPeripheralDlg::CPeripheralDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPeripheralDlg::IDD, pParent)
{

}

CPeripheralDlg::~CPeripheralDlg()
{
}

void CPeripheralDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SENSOERESET, m_Cbo_SensorReset);
	DDX_Control(pDX, IDC_COMBO_ISPIRQLED, m_Cbo_IspIrqLed);
	DDX_Control(pDX, IDC_COMBO_ENCLED, m_Cbo_EncLed);
	DDX_Control(pDX, IDC_COMBO_ICRP0, m_Cbo_IcrP0);
	DDX_Control(pDX, IDC_COMBO_ICRP2, m_Cbo_IcrP1);
	DDX_Control(pDX, IDC_COMBO_FOCUSAP, m_Cbo_FocusAp);
	DDX_Control(pDX, IDC_COMBO_FOCUSAM, m_Cbo_FocusAm);
	DDX_Control(pDX, IDC_COMBO_FOCUSBP, m_Cbo_FocusBp);
	DDX_Control(pDX, IDC_COMBO_FOCUSBM, m_Cbo_FocusBm);
	DDX_Control(pDX, IDC_COMBO_ZOOMAP, m_Cbo_ZoomAp);
	DDX_Control(pDX, IDC_COMBO_ZOOMAM, m_Cbo_ZoomAm);
	DDX_Control(pDX, IDC_COMBO_IRLED, m_Cbo_IrLed);
	DDX_Control(pDX, IDC_COMBO_ZOOMBP, m_Cbo_ZoomBp);
	DDX_Control(pDX, IDC_COMBO_IRISPWM, m_Cbo_IrisPwm);
	DDX_Control(pDX, IDC_COMBO_ETHIRQ, m_Cbo_EthIrq);
	DDX_Control(pDX, IDC_COMBO_MOCTION, m_Cbo_Motion);
	DDX_Control(pDX, IDC_COMBO_UARTRX1, m_Cbo_UartRx1);
	DDX_Control(pDX, IDC_COMBO_UARTTX1, m_Cbo_UartTx1);
	DDX_Control(pDX, IDC_COMBO_I2C2SDA, m_Cbo_I2C2Sda);
	DDX_Control(pDX, IDC_COMBO_II2C2SCL, m_Cbo_I2C2Scl);
	DDX_Control(pDX, IDC_COMBO_ZOOMBM, m_Cbo_ZoomBm);
	DDX_Control(pDX, IDC_COMBO_SDIO1RESET, m_Cbo_Sdio1Reset);
	DDX_Control(pDX, IDC_COMBO_ETHRESET, m_Cbo_EthReset);
	DDX_Control(pDX, IDC_COMBO_AUDIORESET, m_Cbo_AudioReset);
	DDX_Control(pDX, IDC_COMBO_ADKEY, m_Cbo_AdKey);
	DDX_Control(pDX, IDC_COMBO_CDSIN, m_Cbo_CdsIn);
	DDX_Control(pDX, IDC_COMBO_KEYUP, m_Cbo_KeyUp);
	DDX_Control(pDX, IDC_COMBO_DOWN, m_Cbo_KeyDown);
	DDX_Control(pDX, IDC_COMBO_KEYRIGHT, m_Cbo_KeyRight);
	DDX_Control(pDX, IDC_COMBO_KEYLEFT, m_Cbo_KeyLeft);
	DDX_Control(pDX, IDC_COMBO_CENTER, m_Cbo_KeyCenter);
}


BEGIN_MESSAGE_MAP(CPeripheralDlg, CDialogEx)
	ON_CBN_CLOSEUP(IDC_COMBO_SENSOERESET, &CPeripheralDlg::OnCbnCloseupComboSensoereset)
	ON_CBN_CLOSEUP(IDC_COMBO_ISPIRQLED, &CPeripheralDlg::OnCbnCloseupComboIspirqled)
	ON_CBN_CLOSEUP(IDC_COMBO_ENCLED, &CPeripheralDlg::OnCbnCloseupComboEncled)
	ON_CBN_CLOSEUP(IDC_COMBO_ICRP0, &CPeripheralDlg::OnCbnCloseupComboIcrp0)
	ON_CBN_CLOSEUP(IDC_COMBO_ICRP2, &CPeripheralDlg::OnCbnCloseupComboIcrp2)
	ON_CBN_CLOSEUP(IDC_COMBO_FOCUSAP, &CPeripheralDlg::OnCbnCloseupComboFocusap)
	ON_CBN_CLOSEUP(IDC_COMBO_FOCUSAM, &CPeripheralDlg::OnCbnCloseupComboFocusam)
	ON_CBN_CLOSEUP(IDC_COMBO_FOCUSBP, &CPeripheralDlg::OnCbnCloseupComboFocusbp)
	ON_CBN_CLOSEUP(IDC_COMBO_FOCUSBM, &CPeripheralDlg::OnCbnCloseupComboFocusbm)
	ON_CBN_CLOSEUP(IDC_COMBO_ZOOMAP, &CPeripheralDlg::OnCbnCloseupComboZoomap)
	ON_CBN_CLOSEUP(IDC_COMBO_ZOOMAM, &CPeripheralDlg::OnCbnCloseupComboZoomam)
	ON_CBN_CLOSEUP(IDC_COMBO_IRLED, &CPeripheralDlg::OnCbnCloseupComboIrled)
	ON_CBN_CLOSEUP(IDC_COMBO_ZOOMBP, &CPeripheralDlg::OnCbnCloseupComboZoombp)
	ON_CBN_CLOSEUP(IDC_COMBO_IRISPWM, &CPeripheralDlg::OnCbnCloseupComboIrispwm)
	ON_CBN_CLOSEUP(IDC_COMBO_ETHIRQ, &CPeripheralDlg::OnCbnCloseupComboEthirq)
	ON_CBN_CLOSEUP(IDC_COMBO_MOCTION, &CPeripheralDlg::OnCbnCloseupComboMoction)
	ON_CBN_CLOSEUP(IDC_COMBO_UARTRX1, &CPeripheralDlg::OnCbnCloseupComboUartrx1)
	ON_CBN_CLOSEUP(IDC_COMBO_UARTTX1, &CPeripheralDlg::OnCbnCloseupComboUarttx1)
	ON_CBN_CLOSEUP(IDC_COMBO_I2C2SDA, &CPeripheralDlg::OnCbnCloseupComboI2c2sda)
	ON_CBN_CLOSEUP(IDC_COMBO_II2C2SCL, &CPeripheralDlg::OnCbnCloseupComboIi2c2scl)
	ON_CBN_CLOSEUP(IDC_COMBO_ZOOMBM, &CPeripheralDlg::OnCbnCloseupComboZoombm)
	ON_CBN_CLOSEUP(IDC_COMBO_SDIO1RESET, &CPeripheralDlg::OnCbnCloseupComboSdio1reset)
	ON_CBN_CLOSEUP(IDC_COMBO_ETHRESET, &CPeripheralDlg::OnCbnCloseupComboEthreset)
	ON_CBN_CLOSEUP(IDC_COMBO_AUDIORESET, &CPeripheralDlg::OnCbnCloseupComboAudioreset)
	ON_CBN_CLOSEUP(IDC_COMBO_ADKEY, &CPeripheralDlg::OnCbnCloseupComboAdkey)
	ON_CBN_CLOSEUP(IDC_COMBO_CDSIN, &CPeripheralDlg::OnCbnCloseupComboCdsin)
	ON_CBN_CLOSEUP(IDC_COMBO_CENTER, &CPeripheralDlg::OnCbnCloseupComboCenter)
	ON_CBN_CLOSEUP(IDC_COMBO_KEYUP, &CPeripheralDlg::OnCbnCloseupComboKeyup)
	ON_CBN_CLOSEUP(IDC_COMBO_DOWN, &CPeripheralDlg::OnCbnCloseupComboDown)
	ON_CBN_CLOSEUP(IDC_COMBO_KEYLEFT, &CPeripheralDlg::OnCbnCloseupComboKeyleft)
	ON_CBN_CLOSEUP(IDC_COMBO_KEYRIGHT, &CPeripheralDlg::OnCbnCloseupComboKeyright)
END_MESSAGE_MAP()


// CPeripheralDlg 메시지 처리기입니다.


BOOL CPeripheralDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	pCPeripheralDlg = this;

	InitCombo_AddString();
	InitCombo_Setting();

	EnableCtrl(TRUE);
	EnableCheckCtrl();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL CPeripheralDlg::PreTranslateMessage(MSG* pMsg)
{
	// Default Window Message
	if (DefaultWindowMessage(pMsg))	return TRUE;
	else							return CDialogEx::PreTranslateMessage(pMsg);
}

void CPeripheralDlg::InitCombo_AddString()
{
	int i;

	for (i = 0; i < NUM_GPTO; i++)
	{
		m_Cbo_SensorReset.AddString(CBO_GPIO[i]);
		m_Cbo_IspIrqLed.AddString(CBO_GPIO[i]);
		m_Cbo_EncLed.AddString(CBO_GPIO[i]);
		m_Cbo_IcrP0.AddString(CBO_GPIO[i]);
		m_Cbo_IcrP1.AddString(CBO_GPIO[i]);
		m_Cbo_FocusAp.AddString(CBO_GPIO[i]);
		m_Cbo_FocusAm.AddString(CBO_GPIO[i]);
		m_Cbo_FocusBp.AddString(CBO_GPIO[i]);
		m_Cbo_FocusBm.AddString(CBO_GPIO[i]);
		m_Cbo_ZoomAp.AddString(CBO_GPIO[i]);
		m_Cbo_ZoomAm.AddString(CBO_GPIO[i]);

		m_Cbo_ZoomBp.AddString(CBO_GPIO[i]);
		m_Cbo_EthIrq.AddString(CBO_GPIO[i]);
		m_Cbo_Motion.AddString(CBO_GPIO[i]);

		m_Cbo_ZoomBm.AddString(CBO_GPIO[i]);
		m_Cbo_Sdio1Reset.AddString(CBO_GPIO[i]);
		m_Cbo_EthReset.AddString(CBO_GPIO[i]);
		m_Cbo_AudioReset.AddString(CBO_GPIO[i]);

		m_Cbo_KeyUp.AddString(CBO_GPIO[i]);
		m_Cbo_KeyDown.AddString(CBO_GPIO[i]);
		m_Cbo_KeyRight.AddString(CBO_GPIO[i]);
		m_Cbo_KeyLeft.AddString(CBO_GPIO[i]);
		m_Cbo_KeyCenter.AddString(CBO_GPIO[i]);
	}

	for (i = 8; i < 14; i++)				m_Cbo_IrisPwm.AddString(CBO_GPIO[i]);

	m_Cbo_UartRx1.AddString(CBO_GPIO[16]);
	m_Cbo_UartTx1.AddString(CBO_GPIO[17]);
	m_Cbo_I2C2Sda.AddString(CBO_GPIO[18]);
	m_Cbo_I2C2Scl.AddString(CBO_GPIO[19]);


	for (i = 0; i < NUM_ADC; i++)			m_Cbo_AdKey.AddString(CBO_ADC[i]);


	if (pCSPIDlg->m_Cbo_Led.GetCurSel() == 1)
	{
		for (i = 0; i < NUM_GPTO; i++)		m_Cbo_IrLed.AddString(CBO_GPIO[i]);
	}
	else
	{
		for (i = 8; i < 14; i++)			m_Cbo_IrLed.AddString(CBO_GPIO[i]);
	}


	if (pCSPIDlg->m_Cbo_Cds.GetCurSel() == 1)
	{
		for (i = 0; i < NUM_GPTO; i++)		m_Cbo_CdsIn.AddString(CBO_GPIO[i]);
	}
	else
	{
		for (i = 0; i < NUM_ADC; i++)		m_Cbo_CdsIn.AddString(CBO_ADC[i]);
	}
}


void CPeripheralDlg::InitCombo_Setting()
{
	m_Cbo_SensorReset.SetCurSel(0);
	m_Cbo_IspIrqLed.SetCurSel(1);
	m_Cbo_EncLed.SetCurSel(2);
	m_Cbo_IcrP0.SetCurSel(3);
	m_Cbo_IcrP1.SetCurSel(4);
	m_Cbo_FocusAp.SetCurSel(5);
	m_Cbo_FocusAm.SetCurSel(6);
	m_Cbo_FocusBp.SetCurSel(7);
	m_Cbo_FocusBm.SetCurSel(8);
	m_Cbo_ZoomAp.SetCurSel(9);
	m_Cbo_ZoomAm.SetCurSel(10);
	m_Cbo_IrLed.SetCurSel(11);
	m_Cbo_ZoomBp.SetCurSel(12);
	m_Cbo_IrisPwm.SetCurSel(13 - 8);
	m_Cbo_EthIrq.SetCurSel(14);
	m_Cbo_Motion.SetCurSel(15);
	m_Cbo_UartRx1.SetCurSel(0);
	m_Cbo_UartTx1.SetCurSel(0);
	m_Cbo_I2C2Sda.SetCurSel(0);
	m_Cbo_I2C2Scl.SetCurSel(0);
	m_Cbo_ZoomBm.SetCurSel(20);
	m_Cbo_Sdio1Reset.SetCurSel(21);
	m_Cbo_EthReset.SetCurSel(22);
	m_Cbo_AudioReset.SetCurSel(23);

	m_Cbo_AdKey.SetCurSel(0);
	m_Cbo_CdsIn.SetCurSel(1);

	m_Cbo_KeyUp.SetCurSel(16);
	m_Cbo_KeyDown.SetCurSel(16);
	m_Cbo_KeyRight.SetCurSel(16);
	m_Cbo_KeyLeft.SetCurSel(16);
	m_Cbo_KeyCenter.SetCurSel(16);
}


void CPeripheralDlg::EnableCtrl(BOOL bEnable)
{
	m_Cbo_SensorReset.EnableWindow(bEnable);
	m_Cbo_IspIrqLed.EnableWindow(bEnable);
	m_Cbo_EncLed.EnableWindow(bEnable);
	m_Cbo_IcrP0.EnableWindow(bEnable);
	m_Cbo_IcrP1.EnableWindow(bEnable);
	m_Cbo_FocusAp.EnableWindow(bEnable);
	m_Cbo_FocusAm.EnableWindow(bEnable);
	m_Cbo_FocusBp.EnableWindow(bEnable);
	m_Cbo_FocusBm.EnableWindow(bEnable);
	m_Cbo_ZoomAp.EnableWindow(bEnable);
	m_Cbo_ZoomAm.EnableWindow(bEnable);
	m_Cbo_IrLed.EnableWindow(bEnable);
	m_Cbo_IrisPwm.EnableWindow(bEnable);
	m_Cbo_ZoomBp.EnableWindow(bEnable);
	m_Cbo_EthIrq.EnableWindow(bEnable);
	m_Cbo_Motion.EnableWindow(bEnable);
	m_Cbo_UartRx1.EnableWindow(bEnable);
	m_Cbo_UartTx1.EnableWindow(bEnable);
	m_Cbo_I2C2Sda.EnableWindow(bEnable);
	m_Cbo_I2C2Scl.EnableWindow(bEnable);
	m_Cbo_ZoomBm.EnableWindow(bEnable);
	m_Cbo_Sdio1Reset.EnableWindow(bEnable);
	m_Cbo_EthReset.EnableWindow(bEnable);
	m_Cbo_AudioReset.EnableWindow(bEnable);

	m_Cbo_AdKey.EnableWindow(bEnable);
	m_Cbo_CdsIn.EnableWindow(bEnable);

	m_Cbo_KeyUp.EnableWindow(bEnable);
	m_Cbo_KeyDown.EnableWindow(bEnable);
	m_Cbo_KeyRight.EnableWindow(bEnable);
	m_Cbo_KeyLeft.EnableWindow(bEnable);
	m_Cbo_KeyCenter.EnableWindow(bEnable);
}


void CPeripheralDlg::EnableCheckCtrl()
{
	if (pCSPIDlg->m_Cbo_Tdn.GetCurSel() == 2)
		m_Cbo_IcrP1.EnableWindow(TRUE);
	else
		m_Cbo_IcrP1.EnableWindow(FALSE);


	if (pCSPIDlg->m_Cbo_Lens.GetCurSel() == 1)
	{
		m_Cbo_FocusAp.EnableWindow(TRUE);
		m_Cbo_FocusAm.EnableWindow(TRUE);
		m_Cbo_FocusBp.EnableWindow(TRUE);
		m_Cbo_FocusBm.EnableWindow(TRUE);
		m_Cbo_ZoomAp.EnableWindow(TRUE);
		m_Cbo_ZoomAm.EnableWindow(TRUE);
		m_Cbo_ZoomBp.EnableWindow(TRUE);
		m_Cbo_ZoomBm.EnableWindow(TRUE);
	}
	else
	{
		m_Cbo_FocusAp.EnableWindow(FALSE);
		m_Cbo_FocusAm.EnableWindow(FALSE);
		m_Cbo_FocusBp.EnableWindow(FALSE);
		m_Cbo_FocusBm.EnableWindow(FALSE);
		m_Cbo_ZoomAp.EnableWindow(FALSE);
		m_Cbo_ZoomAm.EnableWindow(FALSE);
		m_Cbo_ZoomBp.EnableWindow(FALSE);
		m_Cbo_ZoomBm.EnableWindow(FALSE);
	}


	if (pCSPIDlg->m_Cbo_Iris.GetCurSel() != 0)
		m_Cbo_IrisPwm.EnableWindow(TRUE);
	else
		m_Cbo_IrisPwm.EnableWindow(FALSE);


	if (pCSPIDlg->m_Cbo_Motion.GetCurSel() == 1)
		m_Cbo_Motion.EnableWindow(TRUE);
	else
		m_Cbo_Motion.EnableWindow(FALSE);


	if (pCSPIDlg->m_Cbo_Key.GetCurSel() == 0)
	{
		m_Cbo_AdKey.EnableWindow(TRUE);

		m_Cbo_KeyUp.EnableWindow(FALSE);
		m_Cbo_KeyDown.EnableWindow(FALSE);
		m_Cbo_KeyRight.EnableWindow(FALSE);
		m_Cbo_KeyLeft.EnableWindow(FALSE);
		m_Cbo_KeyCenter.EnableWindow(FALSE);
	}
	else if (pCSPIDlg->m_Cbo_Key.GetCurSel() == 1)
	{
		m_Cbo_AdKey.EnableWindow(FALSE);

		m_Cbo_KeyUp.EnableWindow(TRUE);
		m_Cbo_KeyDown.EnableWindow(TRUE);
		m_Cbo_KeyRight.EnableWindow(TRUE);
		m_Cbo_KeyLeft.EnableWindow(TRUE);
		m_Cbo_KeyCenter.EnableWindow(TRUE);
	}
	else
	{
		m_Cbo_AdKey.EnableWindow(FALSE);

		m_Cbo_KeyUp.EnableWindow(FALSE);
		m_Cbo_KeyDown.EnableWindow(FALSE);
		m_Cbo_KeyRight.EnableWindow(FALSE);
		m_Cbo_KeyLeft.EnableWindow(FALSE);
		m_Cbo_KeyCenter.EnableWindow(FALSE);
	}

	int i;
	int temp_sel;
	temp_sel = m_Cbo_IrLed.GetCurSel();
	m_Cbo_IrLed.ResetContent();
	if (pCSPIDlg->m_Cbo_Led.GetCurSel() == 1)
	{
		for (i = 0; i < NUM_GPTO; i++)
			m_Cbo_IrLed.AddString(CBO_GPIO[i]);
		m_Cbo_IrLed.SetCurSel(temp_sel);
	}
	else
	{
		for (i = 8; i < 14; i++)
			m_Cbo_IrLed.AddString(CBO_GPIO[i]);
		m_Cbo_IrLed.SetCurSel(temp_sel);
	}

	temp_sel = m_Cbo_CdsIn.GetCurSel();
	m_Cbo_CdsIn.ResetContent();
	if (pCSPIDlg->m_Cbo_Cds.GetCurSel() == 1)
	{
		for (i = 0; i < NUM_GPTO; i++)
			m_Cbo_CdsIn.AddString(CBO_GPIO[i]);
		m_Cbo_CdsIn.SetCurSel(temp_sel);
	}
	else
	{
		for (i = 0; i < NUM_ADC; i++)
			m_Cbo_CdsIn.AddString(CBO_ADC[i]);
		m_Cbo_CdsIn.SetCurSel(temp_sel);
	}
}

void CPeripheralDlg::OnCbnCloseupComboSensoereset()		{ pCEN673_Configuration_GeneratorDlg->ChangeConfig(); }
void CPeripheralDlg::OnCbnCloseupComboIspirqled()		{ pCEN673_Configuration_GeneratorDlg->ChangeConfig(); }
void CPeripheralDlg::OnCbnCloseupComboEncled()			{ pCEN673_Configuration_GeneratorDlg->ChangeConfig(); }
void CPeripheralDlg::OnCbnCloseupComboIcrp0()			{ pCEN673_Configuration_GeneratorDlg->ChangeConfig(); }
void CPeripheralDlg::OnCbnCloseupComboIcrp2()			{ pCEN673_Configuration_GeneratorDlg->ChangeConfig(); }
void CPeripheralDlg::OnCbnCloseupComboFocusap()			{ pCEN673_Configuration_GeneratorDlg->ChangeConfig(); }
void CPeripheralDlg::OnCbnCloseupComboFocusam()			{ pCEN673_Configuration_GeneratorDlg->ChangeConfig(); }
void CPeripheralDlg::OnCbnCloseupComboFocusbp()			{ pCEN673_Configuration_GeneratorDlg->ChangeConfig(); }
void CPeripheralDlg::OnCbnCloseupComboFocusbm()			{ pCEN673_Configuration_GeneratorDlg->ChangeConfig(); }
void CPeripheralDlg::OnCbnCloseupComboZoomap()			{ pCEN673_Configuration_GeneratorDlg->ChangeConfig(); }
void CPeripheralDlg::OnCbnCloseupComboZoomam()			{ pCEN673_Configuration_GeneratorDlg->ChangeConfig(); }
void CPeripheralDlg::OnCbnCloseupComboIrled()			{ pCEN673_Configuration_GeneratorDlg->ChangeConfig(); }
void CPeripheralDlg::OnCbnCloseupComboZoombp()			{ pCEN673_Configuration_GeneratorDlg->ChangeConfig(); }
void CPeripheralDlg::OnCbnCloseupComboIrispwm()			{ pCEN673_Configuration_GeneratorDlg->ChangeConfig(); }
void CPeripheralDlg::OnCbnCloseupComboEthirq()			{ pCEN673_Configuration_GeneratorDlg->ChangeConfig(); }
void CPeripheralDlg::OnCbnCloseupComboMoction()			{ pCEN673_Configuration_GeneratorDlg->ChangeConfig(); }
void CPeripheralDlg::OnCbnCloseupComboUartrx1()			{ pCEN673_Configuration_GeneratorDlg->ChangeConfig(); }
void CPeripheralDlg::OnCbnCloseupComboUarttx1()			{ pCEN673_Configuration_GeneratorDlg->ChangeConfig(); }
void CPeripheralDlg::OnCbnCloseupComboI2c2sda()			{ pCEN673_Configuration_GeneratorDlg->ChangeConfig(); }
void CPeripheralDlg::OnCbnCloseupComboIi2c2scl()		{ pCEN673_Configuration_GeneratorDlg->ChangeConfig(); }
void CPeripheralDlg::OnCbnCloseupComboZoombm()			{ pCEN673_Configuration_GeneratorDlg->ChangeConfig(); }
void CPeripheralDlg::OnCbnCloseupComboSdio1reset()		{ pCEN673_Configuration_GeneratorDlg->ChangeConfig(); }
void CPeripheralDlg::OnCbnCloseupComboEthreset()		{ pCEN673_Configuration_GeneratorDlg->ChangeConfig(); }
void CPeripheralDlg::OnCbnCloseupComboAudioreset()		{ pCEN673_Configuration_GeneratorDlg->ChangeConfig(); }
void CPeripheralDlg::OnCbnCloseupComboAdkey()			{ pCEN673_Configuration_GeneratorDlg->ChangeConfig(); }
void CPeripheralDlg::OnCbnCloseupComboCdsin()			{ pCEN673_Configuration_GeneratorDlg->ChangeConfig(); }
void CPeripheralDlg::OnCbnCloseupComboCenter()			{ pCEN673_Configuration_GeneratorDlg->ChangeConfig(); }
void CPeripheralDlg::OnCbnCloseupComboKeyup()			{ pCEN673_Configuration_GeneratorDlg->ChangeConfig(); }
void CPeripheralDlg::OnCbnCloseupComboDown()			{ pCEN673_Configuration_GeneratorDlg->ChangeConfig(); }
void CPeripheralDlg::OnCbnCloseupComboKeyleft()			{ pCEN673_Configuration_GeneratorDlg->ChangeConfig(); }
void CPeripheralDlg::OnCbnCloseupComboKeyright()		{ pCEN673_Configuration_GeneratorDlg->ChangeConfig(); }