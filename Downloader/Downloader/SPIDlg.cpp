// SPIDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Downloader.h"
#include "SPIDlg.h"
#include "afxdialogex.h"


// CSPIDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSPIDlg, CDialogEx)

CSPIDlg::CSPIDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSPIDlg::IDD, pParent)
{

}

CSPIDlg::~CSPIDlg()
{
}

void CSPIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_MODE, m_Cbo_Mode);
	DDX_Control(pDX, IDC_COMBO_DEVICE, m_Cbo_Device);
	DDX_Control(pDX, IDC_COMBO_FRAMERATE, m_Cbo_FrameRate);
	DDX_Control(pDX, IDC_COMBO_RESOLUTION, m_Cbo_Resolution);
	DDX_Control(pDX, IDC_COMBO_MODEL, m_Cbo_Model);
	DDX_Control(pDX, IDC_COMBO_CONTROL, m_Cbo_Control);
	DDX_Control(pDX, IDC_COMBO_KEY, m_Cbo_Key);
	DDX_Control(pDX, IDC_COMBO_LENS, m_Cbo_Lens);
	DDX_Control(pDX, IDC_COMBO_MOTORIZEDMODEL, m_Cbo_MotorizedModel);
	DDX_Control(pDX, IDC_COMBO_IRIS, m_Cbo_Iris);
	DDX_Control(pDX, IDC_COMBO_TDN, m_Cbo_Tdn);
	DDX_Control(pDX, IDC_COMBO_CDS, m_Cbo_Cds);
	DDX_Control(pDX, IDC_COMBO_LED, m_Cbo_Led);
	DDX_Control(pDX, IDC_COMBO_MOTION, m_Cbo_Motion);
	DDX_Control(pDX, IDC_COMBO_SHADE, m_Cbo_Shade);
	DDX_Control(pDX, IDC_COMBO_SAVE, m_Cbo_Save);
	DDX_Control(pDX, IDC_COMBO_PARUSE, m_Cbo_ParUse);
	DDX_Control(pDX, IDC_COMBO_PARSAVE, m_Cbo_ParSave);
	DDX_Control(pDX, IDC_EDIT_EXTEND, m_Edit_Extend);
}


BEGIN_MESSAGE_MAP(CSPIDlg, CDialogEx)
	ON_CBN_CLOSEUP(IDC_COMBO_MODE, &CSPIDlg::OnCbnCloseupComboMode)
	ON_CBN_CLOSEUP(IDC_COMBO_DEVICE, &CSPIDlg::OnCbnCloseupComboDevice)
	ON_CBN_CLOSEUP(IDC_COMBO_FRAMERATE, &CSPIDlg::OnCbnCloseupComboFramerate)
	ON_CBN_CLOSEUP(IDC_COMBO_RESOLUTION, &CSPIDlg::OnCbnCloseupComboResolution)
	ON_CBN_CLOSEUP(IDC_COMBO_MODEL, &CSPIDlg::OnCbnCloseupComboModel)
	ON_CBN_CLOSEUP(IDC_COMBO_CONTROL, &CSPIDlg::OnCbnCloseupComboControl)
	ON_CBN_CLOSEUP(IDC_COMBO_KEY, &CSPIDlg::OnCbnCloseupComboKey)
	ON_CBN_CLOSEUP(IDC_COMBO_LENS, &CSPIDlg::OnCbnCloseupComboLens)
	ON_CBN_CLOSEUP(IDC_COMBO_MOTORIZEDMODEL, &CSPIDlg::OnCbnCloseupComboMotorizedmodel)
	ON_CBN_CLOSEUP(IDC_COMBO_IRIS, &CSPIDlg::OnCbnCloseupComboIris)
	ON_CBN_CLOSEUP(IDC_COMBO_TDN, &CSPIDlg::OnCbnCloseupComboTdn)
	ON_CBN_CLOSEUP(IDC_COMBO_CDS, &CSPIDlg::OnCbnCloseupComboCds)
	ON_CBN_CLOSEUP(IDC_COMBO_LED, &CSPIDlg::OnCbnCloseupComboLed)
	ON_CBN_CLOSEUP(IDC_COMBO_MOTION, &CSPIDlg::OnCbnCloseupComboMotion)
	ON_CBN_CLOSEUP(IDC_COMBO_SHADE, &CSPIDlg::OnCbnCloseupComboShade)
	ON_CBN_CLOSEUP(IDC_COMBO_SAVE, &CSPIDlg::OnCbnCloseupComboSave)
	ON_CBN_CLOSEUP(IDC_COMBO_PARUSE, &CSPIDlg::OnCbnCloseupComboParuse)
	ON_CBN_CLOSEUP(IDC_COMBO_PARSAVE, &CSPIDlg::OnCbnCloseupComboParsave)
END_MESSAGE_MAP()


// CSPIDlg 메시지 처리기입니다.


BOOL CSPIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	pCSPIDlg = this;

	InitCombo_AddString();
	InitCombo_Setting();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL CSPIDlg::PreTranslateMessage(MSG* pMsg)
{
	// Default Window Message
	if (DefaultWindowMessage(pMsg))	return TRUE;
	else							return CDialogEx::PreTranslateMessage(pMsg);
}


void CSPIDlg::InitCombo_AddString()
{
	// ----------------------------------------------------------------------------------------------------
	// Combo Box List
	int i = 0;;

	// Image Mode 
	for (i = 0; i < NUM_MODE; i++)			m_Cbo_Mode.AddString(CBO_MODE[i]);
	// Image Digital
	for (i = 0; i < NUM_DEVICE; i++)		m_Cbo_Device.AddString(CBO_DEVICE[i]);
	// Image Frame Rate
	for (i = 0; i < NUM_FRAMERATE; i++)		m_Cbo_FrameRate.AddString(CBO_FRAMERATE[i]);
	// Image Resolution
	for (i = 0; i < NUM_RESOLUTION; i++)	m_Cbo_Resolution.AddString(CBO_RESOLUTION[i]);


	// Sensor Model
	for (i = 0; i < NUM_MODEL; i++)			m_Cbo_Model.AddString(CBO_MODEL[i]);
	// Sensor Control
	for (i = 0; i < NUM_CONTROL; i++)		m_Cbo_Control.AddString(CBO_CONTROL[i]);

	// Options Key
	for (i = 0; i < NUM_KEY; i++)			m_Cbo_Key.AddString(CBO_KEY[i]);
	// Options Lens
	for (i = 0; i < NUM_LENS; i++)			m_Cbo_Lens.AddString(CBO_LENS[i]);
	// Options Motorized Model
	for (i = 0; i < NUM_MORORIZED; i++)		m_Cbo_MotorizedModel.AddString(CBO_MORORIZED[i]);
	// Options Iris
	for (i = 0; i < NUM_IRIS; i++)			m_Cbo_Iris.AddString(CBO_IRIS[i]);
	// Options TDN
	for (i = 0; i < NUM_TDN; i++)			m_Cbo_Tdn.AddString(CBO_TDN[i]);
	// Options CDS
	for (i = 0; i < NUM_CDS; i++)			m_Cbo_Cds.AddString(CBO_CDS[i]);
	// Options LED
	for (i = 0; i < NUM_LED; i++)			m_Cbo_Led.AddString(CBO_LED[i]);
	// Options Motion
	for (i = 0; i < NUM_MOTION; i++)		m_Cbo_Motion.AddString(CBO_MOTION[i]);


	// Etc Save
	for (i = 0; i < NUM_SHADE; i++)			m_Cbo_Shade.AddString(CBO_SHADE[i]);
	// Etc Save
	for (i = 0; i < NUM_SAVE; i++)			m_Cbo_Save.AddString(CBO_SAVE[i]);
	// Etc Parameter Use
	for (i = 0; i < NUM_PARUSE; i++)		m_Cbo_ParUse.AddString(CBO_PARUSE[i]);
	// Etc Parameter Save
	for (i = 0; i < NUM_PARSAVE; i++)		m_Cbo_ParSave.AddString(CBO_PARSAVE[i]);
}


void CSPIDlg::InitCombo_Setting()
{
	m_Cbo_Mode.SetCurSel(0);
	m_Cbo_Device.SetCurSel(0);
	m_Cbo_FrameRate.SetCurSel(0);
	m_Cbo_Resolution.SetCurSel(0);

	m_Cbo_Model.SetCurSel(5);
	m_Cbo_Control.SetCurSel(1);

	m_Cbo_Key.SetCurSel(0);
	m_Cbo_Lens.SetCurSel(1);
	m_Cbo_MotorizedModel.SetCurSel(1);
	m_Cbo_Iris.SetCurSel(2);
	m_Cbo_Tdn.SetCurSel(2);
	m_Cbo_Cds.SetCurSel(0);
	m_Cbo_Led.SetCurSel(1);
	m_Cbo_Motion.SetCurSel(0);

	m_Cbo_Shade.SetCurSel(1);
	m_Cbo_Save.SetCurSel(1);
	m_Cbo_ParUse.SetCurSel(1);
	m_Cbo_ParSave.SetCurSel(0);

	m_Edit_Extend.SetWindowTextW(_T("0"));
}


void CSPIDlg::EnableCtrl(BOOL bEnable)
{
	m_Cbo_Mode.EnableWindow(bEnable);
	m_Cbo_Device.EnableWindow(bEnable);
	m_Cbo_FrameRate.EnableWindow(bEnable);
	m_Cbo_Resolution.EnableWindow(bEnable);

	m_Cbo_Model.EnableWindow(bEnable);
	m_Cbo_Control.EnableWindow(bEnable);

	m_Cbo_Key.EnableWindow(bEnable);
	m_Cbo_Lens.EnableWindow(bEnable);
	m_Cbo_MotorizedModel.EnableWindow(bEnable);
	m_Cbo_Iris.EnableWindow(bEnable);
	m_Cbo_Tdn.EnableWindow(bEnable);
	m_Cbo_Cds.EnableWindow(bEnable);
	m_Cbo_Led.EnableWindow(bEnable);
	m_Cbo_Motion.EnableWindow(bEnable);

	m_Cbo_Shade.EnableWindow(bEnable);
	m_Cbo_Save.EnableWindow(bEnable);
	m_Cbo_ParUse.EnableWindow(bEnable);
	m_Cbo_ParSave.EnableWindow(bEnable);

	m_Edit_Extend.EnableWindow(bEnable);
}


void CSPIDlg::OnCbnCloseupComboMode()			{ pCEN673_Configuration_GeneratorDlg->ChangeConfig(); }
void CSPIDlg::OnCbnCloseupComboDevice()			{ pCEN673_Configuration_GeneratorDlg->ChangeConfig(); }
void CSPIDlg::OnCbnCloseupComboFramerate()		{ pCEN673_Configuration_GeneratorDlg->ChangeConfig(); }
void CSPIDlg::OnCbnCloseupComboResolution()		{ pCEN673_Configuration_GeneratorDlg->ChangeConfig(); }
void CSPIDlg::OnCbnCloseupComboModel()			{ pCEN673_Configuration_GeneratorDlg->ChangeConfig(); }
void CSPIDlg::OnCbnCloseupComboControl()		{ pCEN673_Configuration_GeneratorDlg->ChangeConfig(); }
void CSPIDlg::OnCbnCloseupComboKey()			{ pCEN673_Configuration_GeneratorDlg->ChangeConfig(); }
void CSPIDlg::OnCbnCloseupComboLens()			{ pCEN673_Configuration_GeneratorDlg->ChangeConfig(); }
void CSPIDlg::OnCbnCloseupComboMotorizedmodel()	{ pCEN673_Configuration_GeneratorDlg->ChangeConfig(); }
void CSPIDlg::OnCbnCloseupComboIris()			{ pCEN673_Configuration_GeneratorDlg->ChangeConfig(); }
void CSPIDlg::OnCbnCloseupComboTdn()			{ pCEN673_Configuration_GeneratorDlg->ChangeConfig(); }
void CSPIDlg::OnCbnCloseupComboCds()			{ pCEN673_Configuration_GeneratorDlg->ChangeConfig(); }
void CSPIDlg::OnCbnCloseupComboLed()			{ pCEN673_Configuration_GeneratorDlg->ChangeConfig(); }
void CSPIDlg::OnCbnCloseupComboMotion()			{ pCEN673_Configuration_GeneratorDlg->ChangeConfig(); }
void CSPIDlg::OnCbnCloseupComboShade()			{ pCEN673_Configuration_GeneratorDlg->ChangeConfig(); }
void CSPIDlg::OnCbnCloseupComboSave()			{ pCEN673_Configuration_GeneratorDlg->ChangeConfig(); }
void CSPIDlg::OnCbnCloseupComboParuse()			{ pCEN673_Configuration_GeneratorDlg->ChangeConfig(); }
void CSPIDlg::OnCbnCloseupComboParsave()		{ pCEN673_Configuration_GeneratorDlg->ChangeConfig(); }