// EN673_Configuration_GeneratorDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Downloader.h"
#include "EN673_Configuration_GeneratorDlg.h"
#include "afxdialogex.h"


UINT	ConfigFileLoadThread(LPVOID pParam);
UINT	ConfigFileSaveThread(LPVOID pParam);
// CEN673_Configuration_GeneratorDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CEN673_Configuration_GeneratorDlg, CDialogEx)

CEN673_Configuration_GeneratorDlg::CEN673_Configuration_GeneratorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEN673_Configuration_GeneratorDlg::IDD, pParent)
{

}

CEN673_Configuration_GeneratorDlg::~CEN673_Configuration_GeneratorDlg()
{
}

void CEN673_Configuration_GeneratorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_CLOSE, m_Btn_Close);
	DDX_Control(pDX, IDC_TAB_LIST, m_Tab_List);
	DDX_Control(pDX, IDC_BUTTON_LOAD, m_Btn_Load);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_Btn_Save);
	DDX_Control(pDX, IDC_EDIT_PATH, m_Edit_Path);
	DDX_Control(pDX, IDC_CHECK_IMAGEPATH, m_Chk_ImagePath);
	DDX_Control(pDX, IDC_CHECK_ISP, m_Chk_ISP);
	DDX_Control(pDX, IDC_CHECK_PERIPHERAL, m_Chk_Peripheral);
	DDX_Control(pDX, IDC_EDIT_DESCRIPTION, m_Edit_Description);
}


BEGIN_MESSAGE_MAP(CEN673_Configuration_GeneratorDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CEN673_Configuration_GeneratorDlg::OnBnClickedButtonClose)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CEN673_Configuration_GeneratorDlg::OnBnClickedButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CEN673_Configuration_GeneratorDlg::OnBnClickedButtonSave)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_LIST, &CEN673_Configuration_GeneratorDlg::OnTcnSelchangeTabList)
	ON_BN_CLICKED(IDC_CHECK_IMAGEPATH, &CEN673_Configuration_GeneratorDlg::OnBnClickedCheckImagepath)
	ON_BN_CLICKED(IDC_CHECK_ISP, &CEN673_Configuration_GeneratorDlg::OnBnClickedCheckIsp)
	ON_BN_CLICKED(IDC_CHECK_PERIPHERAL, &CEN673_Configuration_GeneratorDlg::OnBnClickedCheckPeripheral)
END_MESSAGE_MAP()


// CEN673_Configuration_GeneratorDlg 메시지 처리기입니다.


BOOL CEN673_Configuration_GeneratorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	pCEN673_Configuration_GeneratorDlg = this;

// ----------------------------------------------------------------------------------------------------
// Control
	// CLOSE 버튼
	m_Btn_Close.DrawBorder(FALSE);
	m_Btn_Close.SetColor(CButtonST::BTNST_COLOR_BK_OUT, DIALOGCOLOR);
	m_Btn_Close.SetColor(CButtonST::BTNST_COLOR_BK_IN, DIALOGSUBCOLOR);

	// Check Box
	m_Chk_ImagePath.SetCheck(1);
	m_Chk_ISP.SetCheck(1);
	m_Chk_Peripheral.SetCheck(1);

// ----------------------------------------------------------------------------------------------------
// Create Sub Dialog
	CRect rect;
	m_Tab_List.GetWindowRect(&rect);

	int x = 2;
	int y = 23;
	int cx = rect.Width() - 6;
	int cy = rect.Height() - 26;
	UINT nFlags = SWP_SHOWWINDOW | SWP_NOZORDER;

	m_pDlg_SPI = new CSPIDlg();
	m_pDlg_SPI->Create(IDD_SPI, &m_Tab_List);
	m_pDlg_SPI->SetWindowPos(NULL, x, y, cx, cy, nFlags);

	m_pDlg_Peripheral = new CPeripheralDlg();
	m_pDlg_Peripheral->Create(IDD_PERIPHERAL, &m_Tab_List);
	m_pDlg_Peripheral->SetWindowPos(NULL, x, y, cx, cy, SWP_NOZORDER);


	m_Tab_List.InsertItem(0, _T("ISP"), 0);
	m_Tab_List.InsertItem(1, _T("Peripheral"), 1);

	m_Tab_List.SetCurSel(0);
	m_Tab_List.RedrawWindow();


	ChangeConfig();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CEN673_Configuration_GeneratorDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	// Top
	CRect rect;
	CWnd* pWnd = this;
	pWnd->GetWindowRect(rect);
	int iWidth = rect.Width();
	int iHeight = rect.Height();
	dc.FillSolidRect(0, 0, iWidth, 25, DIALOGCOLOR);

	// OutLine
	CPen NewPen(PS_SOLID, 2, DIALOGCOLOR);
	//CPen NewPen(PS_SOLID, 2, DIALOGOUTLINE);
	CPen* pOldPen = dc.SelectObject(&NewPen);
	/*
	dcBg.MoveTo(0,0);
	dcBg.LineTo(iWidth-1,0);
	dcBg.LineTo(iWidth-1,iHeight-1);
	dcBg.LineTo(0,iHeight-1);
	dcBg.LineTo(0,0);
	*/
	dc.MoveTo(1, 1);
	dc.LineTo(iWidth - 1, 1);
	dc.LineTo(iWidth - 1, iHeight - 1);
	dc.LineTo(1, iHeight - 1);
	dc.LineTo(1, 1);

	CPen NewPen2(PS_SOLID, 1, DIALOGOUTLINE);
	dc.SelectObject(NewPen2);

	dc.MoveTo(0, 0);
	dc.LineTo(iWidth - 1, 0);
	dc.LineTo(iWidth - 1, iHeight - 1);
	dc.LineTo(0, iHeight - 1);
	dc.LineTo(0, 0);

	dc.SelectObject(pOldPen);

	// Font
	LOGFONT lf;
	::ZeroMemory(&lf, sizeof(lf));
	lf.lfHeight = 15;
	lf.lfWeight = 700;
	wsprintf(lf.lfFaceName, _T("%s"), _T("Arial"));
	CFont NewFont;
	NewFont.CreateFontIndirectW(&lf);
	CFont* pOldFont = dc.SelectObject(&NewFont);

	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(TITLECOLOR);

	dc.TextOutW(10, 6, DLG_EN673_CONFIG);
}


BOOL CEN673_Configuration_GeneratorDlg::PreTranslateMessage(MSG* pMsg)
{
	// Default Window Message
	if (DefaultWindowMessage(pMsg))	return TRUE;
	else							return CDialogEx::PreTranslateMessage(pMsg);
}


void CEN673_Configuration_GeneratorDlg::OnBnClickedButtonClose()
{
	pDownloaderDlg->m_ShowDlg_ConfigGen = FALSE;
	ShowWindow(SW_HIDE);
}


void CEN673_Configuration_GeneratorDlg::OnBnClickedButtonLoad()
{
	AfxBeginThread(ConfigFileLoadThread, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
}


UINT ConfigFileLoadThread(LPVOID pParam)
{
	// 컨트롤 비활성화
	pCEN673_Configuration_GeneratorDlg->EnableCtrl(FALSE);
	pCEN673_Configuration_GeneratorDlg->m_Btn_Close.EnableWindow(FALSE);

	pCPeripheralDlg->EnableCheckCtrl();

	// Config Load
	pCEN673_Configuration_GeneratorDlg->LoadCombo();
	pDownCompileOption673->ChangeOption();

	// 컨트롤 활성화
	pCEN673_Configuration_GeneratorDlg->EnableCtrl(TRUE);
	pCEN673_Configuration_GeneratorDlg->m_Btn_Close.EnableWindow(TRUE);

	return 0;
}


void CEN673_Configuration_GeneratorDlg::OnBnClickedButtonSave()
{
	AfxBeginThread(ConfigFileSaveThread, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
}


UINT ConfigFileSaveThread(LPVOID pParam)
{
	// 컨트롤 비활성화
	pCEN673_Configuration_GeneratorDlg->EnableCtrl(FALSE);
	pCEN673_Configuration_GeneratorDlg->m_Btn_Close.EnableWindow(FALSE);

	//pCPeripheralDlg->EnableCheckCtrl();
	// Config Save
	pCEN673_Configuration_GeneratorDlg->SaveCombo();

	// 컨트롤 활성화
	pCEN673_Configuration_GeneratorDlg->EnableCtrl(TRUE);
	pCEN673_Configuration_GeneratorDlg->m_Btn_Close.EnableWindow(TRUE);

	pCPeripheralDlg->EnableCheckCtrl();

	return 0;
}


void CEN673_Configuration_GeneratorDlg::LoadCombo()
{
	// 파일 다이얼로그
	int iMsgBoxReturn = 0;
	CString strMkFile = _T("");
	CString strDefExt = _T("mk");
	CString strFilter = _T("mk File(*.mk)|*.mk||");

	CString strStartPath = _T("");
	int i = 0;
	// BinFile
	for (i = 0; i < BINNUM; i++)
	{
		// Bin Use
		if (!pDownloaderDlg->m_Chk_BinUse[i].GetCheck()) continue;

		pDownloaderDlg->m_Edit_BinPath[i].GetWindowTextW(strStartPath);
		if (0 < strStartPath.ReverseFind('\\')) {
			strStartPath = strStartPath.Left(strStartPath.ReverseFind('\\'));
			strStartPath = strStartPath.Left(strStartPath.ReverseFind('\\'));
		}
	}

	// Open Dialog
	if (!ShowOpenFileDlg(&strMkFile, strDefExt, strFilter, this, strStartPath))
		return;


	m_Edit_Path.SetWindowTextW(strMkFile);

	// Config File Load
	CStdioFile mkFile;
	CString strLine = _T("");
	CString strVari = _T("");
	int intVari = 0;
	if (!mkFile.Open(strMkFile, CFile::modeRead))
		return;

	while (mkFile.ReadString(strLine))
	{
		if (strLine.Find(ETHSUPPORT_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 1, '=');
			if (strVari.Find(_T("y")) != -1)
				pDownCompileOption673->m_Chk_Ethernet.SetCheck(1);
			else
				pDownCompileOption673->m_Chk_Ethernet.SetCheck(0);
		}
		else if (strLine.Find(WIFISUPPORT_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 1, '=');
			if (strVari.Find(_T("y")) != -1)
				pDownCompileOption673->m_Chk_WiFi.SetCheck(1);
			else
				pDownCompileOption673->m_Chk_WiFi.SetCheck(0);
		}
		else if (strLine.Find(ONVIFSUPPORT_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 1, '=');
			if (strVari.Find(_T("y")) != -1)
				pDownCompileOption673->m_Chk_Onvif.SetCheck(1);
			else
				pDownCompileOption673->m_Chk_Onvif.SetCheck(0);
		}
		else if (strLine.Find(ACTIVEXSUPPORT_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 1, '=');
			if (strVari.Find(_T("y")) != -1)
				pDownCompileOption673->m_Chk_ActiveX.SetCheck(1);
			else
				pDownCompileOption673->m_Chk_ActiveX.SetCheck(0);
		}
		else if (strLine.Find(INPUTMODE_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 2, '=');
			intVari = _ttoi(strVari);
			switch (intVari)
			{
			case 1:		intVari = 0;	break;
			case 2:		intVari = 1;	break;
			case 3:		intVari = 2;	break;
			}
			pCSPIDlg->m_Cbo_Mode.SetCurSel(intVari);
		}
		else if (strLine.Find(DIGITAL_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 2, '=');
			intVari = _ttoi(strVari);
			pCSPIDlg->m_Cbo_Device.SetCurSel(intVari);
		}
		else if (strLine.Find(FRAMERATE_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 2, '=');
			intVari = _ttoi(strVari);
			pCSPIDlg->m_Cbo_FrameRate.SetCurSel(intVari);
		}
		else if (strLine.Find(REEOLUTION_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 2, '=');
			intVari = _ttoi(strVari);
			pCSPIDlg->m_Cbo_Resolution.SetCurSel(intVari);
		}
		else if (strLine.Find(SENSOR_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 2, '=');
			intVari = _ttoi(strVari);
			switch (intVari)
			{
			case 1:		intVari = 0;	break;
			case 4:		intVari = 1;	break;
			case 11:	intVari = 2;	break;
			case 12:	intVari = 3;	break;
			case 13:	intVari = 4;	break;
			case 14:	intVari = 5;	break;
			case 15:	intVari = 6;	break;
			case 18:	intVari = 7;	break;
			case 21:	intVari = 8;	break;
			case 22:	intVari = 9;	break;
			case 24:	intVari = 10;	break;
			}
			pCSPIDlg->m_Cbo_Model.SetCurSel(intVari);
		}
		else if (strLine.Find(CONTROL_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 2, '=');
			intVari = _ttoi(strVari);
			pCSPIDlg->m_Cbo_Control.SetCurSel(intVari);
		}
		else if (strLine.Find(KEY_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 2, '=');
			intVari = _ttoi(strVari);
			pCSPIDlg->m_Cbo_Key.SetCurSel(intVari);
		}
		else if (strLine.Find(LENS_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 2, '=');
			intVari = _ttoi(strVari);
			pCSPIDlg->m_Cbo_Lens.SetCurSel(intVari);
		}
		else if (strLine.Find(MORORIZED_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 2, '=');
			intVari = _ttoi(strVari);
			pCSPIDlg->m_Cbo_MotorizedModel.SetCurSel(intVari);
		}
		else if (strLine.Find(IRIS_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 2, '=');
			intVari = _ttoi(strVari);
			pCSPIDlg->m_Cbo_Iris.SetCurSel(intVari);
		}
		else if (strLine.Find(TDN_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 2, '=');
			intVari = _ttoi(strVari);
			pCSPIDlg->m_Cbo_Tdn.SetCurSel(intVari);
		}
		else if (strLine.Find(CDS_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 2, '=');
			intVari = _ttoi(strVari);
			pCSPIDlg->m_Cbo_Cds.SetCurSel(intVari);
		}
		else if (strLine.Find(LED_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 2, '=');
			intVari = _ttoi(strVari);
			pCSPIDlg->m_Cbo_Led.SetCurSel(intVari);
		}
		else if (strLine.Find(MOTION_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 2, '=');
			intVari = _ttoi(strVari);
			pCSPIDlg->m_Cbo_Motion.SetCurSel(intVari);
		}
		else if (strLine.Find(SHADE_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 2, '=');
			intVari = _ttoi(strVari);
			pCSPIDlg->m_Cbo_Shade.SetCurSel(intVari);
		}
		else if (strLine.Find(SAVE_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 2, '=');
			intVari = _ttoi(strVari);
			pCSPIDlg->m_Cbo_Save.SetCurSel(intVari);
		}
		else if (strLine.Find(PARUSE_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 2, '=');
			intVari = _ttoi(strVari);
			pCSPIDlg->m_Cbo_ParUse.SetCurSel(intVari);
		}
		else if (strLine.Find(PARSAVE_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 2, '=');
			intVari = _ttoi(strVari);
			pCSPIDlg->m_Cbo_ParSave.SetCurSel(intVari);
		}
		else if (strLine.Find(OPTIONFLAGNUM_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 1, '=');
			pCSPIDlg->m_Edit_Extend.SetWindowTextW(strVari);
		}
		else if (strLine.Find(PERIPHERAL_COMMANT_STRING) != -1)
		{
			pCPeripheralDlg->EnableCheckCtrl();
		}
		else if (strLine.Find(SENSOERESET_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 2, '=');
			intVari = CStringtoIntGPIO(strVari);
			pCPeripheralDlg->m_Cbo_SensorReset.SetCurSel(intVari);
		}
		else if (strLine.Find(ISPIRQLED_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 2, '=');
			intVari = CStringtoIntGPIO(strVari);
			pCPeripheralDlg->m_Cbo_IspIrqLed.SetCurSel(intVari);
		}
		else if (strLine.Find(ENCLED_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 2, '=');
			intVari = CStringtoIntGPIO(strVari);
			pCPeripheralDlg->m_Cbo_EncLed.SetCurSel(intVari);
		}
		else if (strLine.Find(ICRP0_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 2, '=');
			intVari = CStringtoIntGPIO(strVari);
			pCPeripheralDlg->m_Cbo_IcrP0.SetCurSel(intVari);
		}
		else if (strLine.Find(ICRP1_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 2, '=');
			intVari = CStringtoIntGPIO(strVari);
			pCPeripheralDlg->m_Cbo_IcrP1.SetCurSel(intVari);
		}
		else if (strLine.Find(FOCUSAP_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 2, '=');
			intVari = CStringtoIntGPIO(strVari);
			pCPeripheralDlg->m_Cbo_FocusAp.SetCurSel(intVari);
		}
		else if (strLine.Find(FOCUSAM_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 2, '=');
			intVari = CStringtoIntGPIO(strVari);
			pCPeripheralDlg->m_Cbo_FocusAm.SetCurSel(intVari);
		}
		else if (strLine.Find(FOCUSBP_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 2, '=');
			intVari = CStringtoIntGPIO(strVari);
			pCPeripheralDlg->m_Cbo_FocusBp.SetCurSel(intVari);
		}
		else if (strLine.Find(FOCUSBM_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 2, '=');
			intVari = CStringtoIntGPIO(strVari);
			pCPeripheralDlg->m_Cbo_FocusBm.SetCurSel(intVari);
		}

		else if (strLine.Find(ZOOMAP_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 2, '=');
			intVari = CStringtoIntGPIO(strVari);
			pCPeripheralDlg->m_Cbo_ZoomAp.SetCurSel(intVari);
		}
		else if (strLine.Find(ZOOMAM_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 2, '=');
			intVari = CStringtoIntGPIO(strVari);
			pCPeripheralDlg->m_Cbo_ZoomAm.SetCurSel(intVari);
		}
		else if (strLine.Find(IRLED_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 2, '=');
			if (pCSPIDlg->m_Cbo_Led.GetCurSel() == 1)
				intVari = CStringtoIntGPIO(strVari);
			else
				intVari = CStringtoIntGPIO(strVari) - 8;
			pCPeripheralDlg->m_Cbo_IrLed.SetCurSel(intVari);
		}
		else if (strLine.Find(ZOOMBP_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 2, '=');
			intVari = CStringtoIntGPIO(strVari);
			pCPeripheralDlg->m_Cbo_ZoomBp.SetCurSel(intVari);
		}
		else if (strLine.Find(IRISPWM_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 2, '=');
			intVari = CStringtoIntGPIO(strVari) - 8;
			pCPeripheralDlg->m_Cbo_IrisPwm.SetCurSel(intVari);
		}
		else if (strLine.Find(ETHIRQ_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 2, '=');
			intVari = CStringtoIntGPIO(strVari);
			pCPeripheralDlg->m_Cbo_EthIrq.SetCurSel(intVari);
		}
		else if (strLine.Find(PERMOTION_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 2, '=');
			intVari = CStringtoIntGPIO(strVari);
			pCPeripheralDlg->m_Cbo_Motion.SetCurSel(intVari);
		}
#if 0
		else if (strLine.Find(UARTRX1_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 2, '=');
			intVari = CStringtoIntGPIO(strVari);
			pCPeripheralDlg->m_Cbo_UartRx1.SetCurSel(intVari);
		}
		else if (strLine.Find(UARTTX1_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 2, '=');
			intVari = CStringtoIntGPIO(strVari);
			pCPeripheralDlg->m_Cbo_UartTx1.SetCurSel(intVari);
		}
		else if (strLine.Find(I2C2SDA_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 2, '=');
			intVari = CStringtoIntGPIO(strVari);
			pCPeripheralDlg->m_Cbo_I2C2Sda.SetCurSel(intVari);
		}
		else if (strLine.Find(I2C2SCL_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 2, '=');
			intVari = CStringtoIntGPIO(strVari);
			pCPeripheralDlg->m_Cbo_I2C2Scl.SetCurSel(intVari);
		}
#endif
		else if (strLine.Find(ZOOMBM_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 2, '=');
			intVari = CStringtoIntGPIO(strVari);
			pCPeripheralDlg->m_Cbo_ZoomBm.SetCurSel(intVari);
		}
		else if (strLine.Find(SDIO1RESET_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 2, '=');
			intVari = CStringtoIntGPIO(strVari);
			pCPeripheralDlg->m_Cbo_Sdio1Reset.SetCurSel(intVari);
		}
		else if (strLine.Find(ETHRESET_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 2, '=');
			intVari = CStringtoIntGPIO(strVari);
			pCPeripheralDlg->m_Cbo_EthReset.SetCurSel(intVari);
		}
		else if (strLine.Find(AUDIORESET_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 2, '=');
			intVari = CStringtoIntGPIO(strVari);
			pCPeripheralDlg->m_Cbo_AudioReset.SetCurSel(intVari);
		}
		else if (strLine.Find(ADKEY_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 2, '=');
			intVari = CStringtoIntADC(strVari);
			pCPeripheralDlg->m_Cbo_AdKey.SetCurSel(intVari);
		}
		else if (strLine.Find(CDSINADC_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 2, '=');
			intVari = CStringtoIntADC(strVari);
			pCPeripheralDlg->m_Cbo_CdsIn.SetCurSel(intVari);
		}
		else if (strLine.Find(CDSINGPIO_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 2, '=');
			intVari = CStringtoIntGPIO(strVari);
			pCPeripheralDlg->m_Cbo_CdsIn.SetCurSel(intVari);
		}
		else if (strLine.Find(KEY_C_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 2, '=');
			intVari = CStringtoIntGPIO(strVari);
			pCPeripheralDlg->m_Cbo_KeyCenter.SetCurSel(intVari);
		}
		else if (strLine.Find(KEY_U_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 2, '=');
			intVari = CStringtoIntGPIO(strVari);
			pCPeripheralDlg->m_Cbo_KeyUp.SetCurSel(intVari);
		}
		else if (strLine.Find(KEY_D_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 2, '=');
			intVari = CStringtoIntGPIO(strVari);
			pCPeripheralDlg->m_Cbo_KeyDown.SetCurSel(intVari);
		}
		else if (strLine.Find(KEY_L_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 2, '=');
			intVari = CStringtoIntGPIO(strVari);
			pCPeripheralDlg->m_Cbo_KeyRight.SetCurSel(intVari);
		}
		else if (strLine.Find(KEY_R_STRING) != -1)
		{
			AfxExtractSubString(strVari, strLine, 2, '=');
			intVari = CStringtoIntGPIO(strVari);
			pCPeripheralDlg->m_Cbo_KeyLeft.SetCurSel(intVari);
		}
		else if (strLine.Find(USING_CONFIG_IMGPATH_SCRIPT_STRING) != -1)
		{
			if (strLine.Find(_T("#")) != -1)	m_Chk_ImagePath.SetCheck(0);
			else								m_Chk_ImagePath.SetCheck(1);
		}
		else if (strLine.Find(USING_CONFIG_ISP_SCRIPT_STRING) != -1)
		{
			if (strLine.Find(_T("#")) != -1)	m_Chk_ISP.SetCheck(0);
			else								m_Chk_ISP.SetCheck(1);
		}
		else if (strLine.Find(USING_CONFIG_GPIO_SCRIPT_STRING) != -1)
		{
			if (strLine.Find(_T("#")) != -1)	m_Chk_Peripheral.SetCheck(0);
			else								m_Chk_Peripheral.SetCheck(1);
		}
		else
		{
			continue;
		}
	}

	mkFile.Close();
}


void CEN673_Configuration_GeneratorDlg::SaveCombo()
{
	// 파일 다이얼로그
	int iMsgBoxReturn = 0;
	CString strMkFile = _T("");
	CString strDefExt = _T("mk");
	CString strFilter = _T("mk File(*.mk)|*.mk||");

	CString strStartPath = _T("");
	int i = 0;
	// BinFile
	for (i = 0; i < BINNUM; i++)
	{
		// Bin Use
		if (!pDownloaderDlg->m_BinFile[i].bBinUse) continue;
		
		pDownloaderDlg->m_Edit_BinPath[i].GetWindowTextW(strStartPath);
		if (0 < strStartPath.ReverseFind('\\')) {
			strStartPath = strStartPath.Left(strStartPath.ReverseFind('\\'));
			strStartPath = strStartPath.Left(strStartPath.ReverseFind('\\'));
		}
	}

	// Open Dialog
	if (!ShowSaveFileDlg(&strMkFile, strDefExt, strFilter, this, strStartPath))
		return;

	m_Edit_Path.SetWindowTextW(strMkFile);

	// Config File Save
	CStdioFile mkFile;
	CString strLine = _T("");
	CString strBase = BASE_CONFIG_STRING;
	CString strDef = _T("");
	CString strVari = _T("");

	CString strBulid = _T("");
	CString strWifi	= _T("");
	CString strCconfig = _T("");
	CString strCTdn = _T("");
	CString strCLen = _T("");
	CString strCIris = _T("");
	CString strCMotion = _T("");
	CString strCKey0 = _T("");
	CString strCKey1 = _T("");
	if (!mkFile.Open(strMkFile, CFile::modeWrite | CFile::modeCreate))
		return;

	// Config
	strLine = _T("##################################################\n");
	mkFile.WriteString(strLine);
	strLine = _T("# EN673 Configuration Script\n");
	mkFile.WriteString(strLine);
	strLine = _T("##################################################\n\n");
	mkFile.WriteString(strLine);
#if 0
	// Build Option
	strDef = BUILD_COMMANT_STRING;
	strLine = strDef + _T("\n");
	mkFile.WriteString(strLine);

	if (pDownCompileOption673->m_Chk_Ethernet.GetCheck())	strBulid = _T("y");
	else													strBulid = _T("n");
	strDef = ETHSUPPORT_STRING;
	strLine = strDef + _T(" = ") + strBulid + _T("\n");
	mkFile.WriteString(strLine);

	if (pDownCompileOption673->m_Chk_WiFi.GetCheck())		strBulid = _T("y");
	else													strBulid = _T("n");
	strDef = WIFISUPPORT_STRING;
	strLine = strDef + _T(" = ") + strBulid + _T("\n");
	mkFile.WriteString(strLine);

	if (pDownCompileOption673->m_Chk_Onvif.GetCheck())		strBulid = _T("y");
	else													strBulid = _T("n");
	strDef = ONVIFSUPPORT_STRING;
	strLine = strDef + _T(" = ") + strBulid + _T("\n");
	mkFile.WriteString(strLine);

	if (pDownCompileOption673->m_Chk_ActiveX.GetCheck())	strBulid = _T("y");
	else													strBulid = _T("n");
	strDef = ACTIVEXSUPPORT_STRING;
	strLine = strDef + _T(" = ") + strBulid + _T("\n");
	mkFile.WriteString(strLine);

	for (int i = 0; i < NUM_WIFIMODEL; i++)
	{
		if (i == 1)		strWifi = _T("");
		else			strWifi = _T("#");
		strDef = WIFIMODULE_STRING;
		strLine = strWifi + strDef + _T(" = ") + CBO_WIFIMODEL[i] + _T("\n");
		mkFile.WriteString(strLine);
	}
	mkFile.WriteString(_T("\n"));
#endif
	// Image Input Mode
	strDef = IMAGEPATH_COMMANT_STRING;
	strLine = strDef + _T("\n");
	mkFile.WriteString(strLine);

	if (m_Chk_ImagePath.GetCheck())		strCconfig = _T("");
	else								strCconfig = _T("#");
	strDef = USING_CONFIG_IMGPATH_SCRIPT_STRING;
	strLine = strCconfig + strBase + _T(" := ") + strDef + _T("\n");
	mkFile.WriteString(strLine);

	strDef = INPUTMODE_STRING;
	switch (pCSPIDlg->m_Cbo_Mode.GetCurSel())
	{
	case 0:		strVari.Format(_T("%d"), 0);	break;
	case 1:		strVari.Format(_T("%d"), 2);	break;
	case 2:		strVari.Format(_T("%d"), 3);	break;
	}
	strLine = strCconfig + strBase + _T(" += ") + strDef + _T("=") + strVari + _T("\n");
	mkFile.WriteString(strLine);

	strDef = DIGITAL_STRING;
	strVari.Format(_T("%d"), pCSPIDlg->m_Cbo_Device.GetCurSel());
	strLine = strCconfig + strBase + _T(" += ") + strDef + _T("=") + strVari + _T("\n");
	mkFile.WriteString(strLine);

	strDef = FRAMERATE_STRING;
	strVari.Format(_T("%d"), pCSPIDlg->m_Cbo_FrameRate.GetCurSel());
	strLine = strCconfig + strBase + _T(" += ") + strDef + _T("=") + strVari + _T("\n");
	mkFile.WriteString(strLine);

	strDef = REEOLUTION_STRING;
	strVari.Format(_T("%d"), pCSPIDlg->m_Cbo_Resolution.GetCurSel());
	strLine = strCconfig + strBase + _T(" += ") + strDef + _T("=") + strVari + _T("\n\n");
	mkFile.WriteString(strLine);


	// ISP
	strDef = ISP_COMMANT_STRING;
	strLine = strDef + _T("\n");
	mkFile.WriteString(strLine);

	if (m_Chk_ISP.GetCheck())			strCconfig = _T("");
	else								strCconfig = _T("#");
	strDef = USING_CONFIG_ISP_SCRIPT_STRING;
	strLine = strCconfig + strBase + _T(" += ") + strDef + _T("\n");
	mkFile.WriteString(strLine);

	strDef = SENSOR_STRING;
	switch (pCSPIDlg->m_Cbo_Model.GetCurSel())
	{
	case 0:		strVari.Format(_T("%d"), 1);	break;
	case 1:		strVari.Format(_T("%d"), 4);	break;
	case 2:		strVari.Format(_T("%d"), 11);	break;
	case 3:		strVari.Format(_T("%d"), 12);	break;
	case 4:		strVari.Format(_T("%d"), 13);	break;
	case 5:		strVari.Format(_T("%d"), 14);	break;
	case 6:		strVari.Format(_T("%d"), 15);	break;
	case 7:		strVari.Format(_T("%d"), 18);	break;
	case 8:		strVari.Format(_T("%d"), 21);	break;
	case 9:		strVari.Format(_T("%d"), 22);	break;
	case 10:	strVari.Format(_T("%d"), 24);	break;
	}
	strLine = strCconfig + strBase + _T(" += ") + strDef + _T("=") + strVari + _T("\n");
	mkFile.WriteString(strLine);

	strDef = CONTROL_STRING;
	strVari.Format(_T("%d"), pCSPIDlg->m_Cbo_Control.GetCurSel());
	strLine = strCconfig + strBase + _T(" += ") + strDef + _T("=") + strVari + _T("\n");
	mkFile.WriteString(strLine);

	// Options
	strDef = KEY_STRING;
	strVari.Format(_T("%d"), pCSPIDlg->m_Cbo_Key.GetCurSel());
	strLine = strCconfig + strBase + _T(" += ") + strDef + _T("=") + strVari + _T("\n");
	mkFile.WriteString(strLine);
	if (pCSPIDlg->m_Cbo_Key.GetCurSel() != 0)	strCKey0 = _T("#");
	if (pCSPIDlg->m_Cbo_Key.GetCurSel() != 1)	strCKey1 = _T("#");

	strDef = LENS_STRING;
	strVari.Format(_T("%d"), pCSPIDlg->m_Cbo_Lens.GetCurSel());
	strLine = strCconfig + strBase + _T(" += ") + strDef + _T("=") + strVari + _T("\n");
	mkFile.WriteString(strLine);
	if (pCSPIDlg->m_Cbo_Lens.GetCurSel() != 1)	strCLen = _T("#");

	strDef = MORORIZED_STRING;
	strVari.Format(_T("%d"), pCSPIDlg->m_Cbo_MotorizedModel.GetCurSel());
	strLine = strCconfig + strBase + _T(" += ") + strDef + _T("=") + strVari + _T("\n");
	mkFile.WriteString(strLine);

	strDef = IRIS_STRING;
	strVari.Format(_T("%d"), pCSPIDlg->m_Cbo_Iris.GetCurSel());
	strLine = strCconfig + strBase + _T(" += ") + strDef + _T("=") + strVari + _T("\n");
	mkFile.WriteString(strLine);
	if (pCSPIDlg->m_Cbo_Iris.GetCurSel() == 0)	strCIris = _T("#");

	strDef = TDN_STRING;
	strVari.Format(_T("%d"), pCSPIDlg->m_Cbo_Tdn.GetCurSel());
	strLine = strCconfig + strBase + _T(" += ") + strDef + _T("=") + strVari + _T("\n");
	mkFile.WriteString(strLine);
	if (pCSPIDlg->m_Cbo_Tdn.GetCurSel() != 2)	strCTdn = _T("#");

	strDef = CDS_STRING;
	strVari.Format(_T("%d"), pCSPIDlg->m_Cbo_Cds.GetCurSel());
	strLine = strCconfig + strBase + _T(" += ") + strDef + _T("=") + strVari + _T("\n");
	mkFile.WriteString(strLine);

	strDef = LED_STRING;
	strVari.Format(_T("%d"), pCSPIDlg->m_Cbo_Led.GetCurSel());
	strLine = strCconfig + strBase + _T(" += ") + strDef + _T("=") + strVari + _T("\n");
	mkFile.WriteString(strLine);

	strDef = MOTION_STRING;
	strVari.Format(_T("%d"), pCSPIDlg->m_Cbo_Motion.GetCurSel());
	strLine = strCconfig + strBase + _T(" += ") + strDef + _T("=") + strVari + _T("\n");
	mkFile.WriteString(strLine);
	if (pCSPIDlg->m_Cbo_Motion.GetCurSel() != 1)	strCMotion = _T("#");

	// ETC
	strDef = SHADE_STRING;
	strVari.Format(_T("%d"), pCSPIDlg->m_Cbo_Shade.GetCurSel());
	strLine = strCconfig + strBase + _T(" += ") + strDef + _T("=") + strVari + _T("\n");
	mkFile.WriteString(strLine);

	strDef = SAVE_STRING;
	strVari.Format(_T("%d"), pCSPIDlg->m_Cbo_Save.GetCurSel());
	strLine = strCconfig + strBase + _T(" += ") + strDef + _T("=") + strVari + _T("\n");
	mkFile.WriteString(strLine);

	strDef = PARUSE_STRING;
	strVari.Format(_T("%d"), pCSPIDlg->m_Cbo_ParUse.GetCurSel());
	strLine = strCconfig + strBase + _T(" += ") + strDef + _T("=") + strVari + _T("\n");
	mkFile.WriteString(strLine);

	strDef = PARSAVE_STRING;
	strVari.Format(_T("%d"), pCSPIDlg->m_Cbo_ParSave.GetCurSel());
	strLine = strCconfig + strBase + _T(" += ") + strDef + _T("=") + strVari + _T("\n\n");
	mkFile.WriteString(strLine);

	strDef = OPTIONFLAGNUM_STRING;
	pCSPIDlg->m_Edit_Extend.GetWindowTextW(strVari);
	int option_count = 0;
	option_count = _ttoi(strVari);
	strLine = _T("#") + strDef + _T("=") + strVari + _T("\n");
	mkFile.WriteString(strLine);

	if (option_count)
	{
		for (int i = 0; i < option_count; i++)
		{
			strDef = OPTIONFLAG_STRING;
			strVari.Format(_T("%d"), i);
			strLine = strBase + _T(" += ") + strDef + strVari + _T("\n");
			mkFile.WriteString(strLine);
		}
	}

	strLine = _T("\n");
	mkFile.WriteString(strLine);

	// Peripheral
	strDef = PERIPHERAL_COMMANT_STRING;
	strLine = strDef + _T("\n");
	mkFile.WriteString(strLine);

	if (m_Chk_Peripheral.GetCheck())	strCconfig = _T("");
	else								strCconfig = _T("#");
	strDef = USING_CONFIG_GPIO_SCRIPT_STRING;
	strLine = strCconfig + strBase + _T(" += ") + strDef + _T("\n");
	mkFile.WriteString(strLine);

	strDef = SENSOERESET_STRING;
	pCPeripheralDlg->m_Cbo_SensorReset.GetLBText(pCPeripheralDlg->m_Cbo_SensorReset.GetCurSel(), strVari);
	//strVari.Format(_T("%d"), pCPeripheralDlg->m_Cbo_SensorReset.GetCurSel());
	strLine = strCconfig + strBase + _T(" += ") + strDef + _T("=") + strVari + _T("\n");
	mkFile.WriteString(strLine);

	strDef = ISPIRQLED_STRING;
	pCPeripheralDlg->m_Cbo_IspIrqLed.GetLBText(pCPeripheralDlg->m_Cbo_IspIrqLed.GetCurSel(), strVari);
	//strVari.Format(_T("%d"), pCPeripheralDlg->m_Cbo_IspIrqLed.GetCurSel());
	strLine = strCconfig + strBase + _T(" += ") + strDef + _T("=") + strVari + _T("\n");
	mkFile.WriteString(strLine);

	strDef = ENCLED_STRING;
	pCPeripheralDlg->m_Cbo_EncLed.GetLBText(pCPeripheralDlg->m_Cbo_EncLed.GetCurSel(), strVari);
	//strVari.Format(_T("%d"), pCPeripheralDlg->m_Cbo_EncLed.GetCurSel());
	strLine = strCconfig + strBase + _T(" += ") + strDef + _T("=") + strVari + _T("\n");
	mkFile.WriteString(strLine);

	strDef = ICRP0_STRING;
	pCPeripheralDlg->m_Cbo_IcrP0.GetLBText(pCPeripheralDlg->m_Cbo_IcrP0.GetCurSel(), strVari);
	//strVari.Format(_T("%d"), pCPeripheralDlg->m_Cbo_IcrP0.GetCurSel());
	strLine = strCconfig + strBase + _T(" += ") + strDef + _T("=") + strVari + _T("\n");
	mkFile.WriteString(strLine);

	strDef = ICRP1_STRING;
	pCPeripheralDlg->m_Cbo_IcrP1.GetLBText(pCPeripheralDlg->m_Cbo_IcrP1.GetCurSel(), strVari);
	//strVari.Format(_T("%d"), pCPeripheralDlg->m_Cbo_IcrP1.GetCurSel());
	strLine = strCconfig + strCTdn + strBase + _T(" += ") + strDef + _T("=") + strVari + _T("\n");
	strLine.Replace(_T("##"), _T("#"));
	mkFile.WriteString(strLine);

	strDef = FOCUSAP_STRING;
	pCPeripheralDlg->m_Cbo_FocusAp.GetLBText(pCPeripheralDlg->m_Cbo_FocusAp.GetCurSel(), strVari);
	//strVari.Format(_T("%d"), pCPeripheralDlg->m_Cbo_FocusAp.GetCurSel());
	strLine = strCconfig + strCLen + strBase + _T(" += ") + strDef + _T("=") + strVari + _T("\n");
	strLine.Replace(_T("##"), _T("#"));
	mkFile.WriteString(strLine);

	strDef = FOCUSAM_STRING;
	pCPeripheralDlg->m_Cbo_FocusAm.GetLBText(pCPeripheralDlg->m_Cbo_FocusAm.GetCurSel(), strVari);
	//strVari.Format(_T("%d"), pCPeripheralDlg->m_Cbo_FocusAm.GetCurSel());
	strLine = strCconfig + strCLen + strBase + _T(" += ") + strDef + _T("=") + strVari + _T("\n");
	strLine.Replace(_T("##"), _T("#"));
	mkFile.WriteString(strLine);

	strDef = FOCUSBP_STRING;
	pCPeripheralDlg->m_Cbo_FocusBp.GetLBText(pCPeripheralDlg->m_Cbo_FocusBp.GetCurSel(), strVari);
	//strVari.Format(_T("%d"), pCPeripheralDlg->m_Cbo_FocusBp.GetCurSel());
	strLine = strCconfig + strCLen + strBase + _T(" += ") + strDef + _T("=") + strVari + _T("\n");
	strLine.Replace(_T("##"), _T("#"));
	mkFile.WriteString(strLine);

	strDef = FOCUSBM_STRING;
	pCPeripheralDlg->m_Cbo_FocusBm.GetLBText(pCPeripheralDlg->m_Cbo_FocusBm.GetCurSel(), strVari);
	//strVari.Format(_T("%d"), pCPeripheralDlg->m_Cbo_FocusBm.GetCurSel());
	strLine = strCconfig + strCLen + strBase + _T(" += ") + strDef + _T("=") + strVari + _T("\n");
	strLine.Replace(_T("##"), _T("#"));
	mkFile.WriteString(strLine);

	strDef = ZOOMAP_STRING;
	pCPeripheralDlg->m_Cbo_ZoomAp.GetLBText(pCPeripheralDlg->m_Cbo_ZoomAp.GetCurSel(), strVari);
	//strVari.Format(_T("%d"), pCPeripheralDlg->m_Cbo_ZoomAp.GetCurSel());
	strLine = strCconfig + strCLen + strBase + _T(" += ") + strDef + _T("=") + strVari + _T("\n");
	strLine.Replace(_T("##"), _T("#"));
	mkFile.WriteString(strLine);

	strDef = ZOOMAM_STRING;
	pCPeripheralDlg->m_Cbo_ZoomAm.GetLBText(pCPeripheralDlg->m_Cbo_ZoomAm.GetCurSel(), strVari);
	//strVari.Format(_T("%d"), pCPeripheralDlg->m_Cbo_ZoomAm.GetCurSel());
	strLine = strCconfig + strCLen + strBase + _T(" += ") + strDef + _T("=") + strVari + _T("\n");
	strLine.Replace(_T("##"), _T("#"));
	mkFile.WriteString(strLine);

	strDef = IRLED_STRING;
	pCPeripheralDlg->m_Cbo_IrLed.GetLBText(pCPeripheralDlg->m_Cbo_IrLed.GetCurSel(), strVari);
	//strVari.Format(_T("%d"), pCPeripheralDlg->m_Cbo_IrLed.GetCurSel());
	strLine = strCconfig + strBase + _T(" += ") + strDef + _T("=") + strVari + _T("\n");
	mkFile.WriteString(strLine);

	strDef = ZOOMBP_STRING;
	pCPeripheralDlg->m_Cbo_ZoomBp.GetLBText(pCPeripheralDlg->m_Cbo_ZoomBp.GetCurSel(), strVari);
	//strVari.Format(_T("%d"), pCPeripheralDlg->m_Cbo_ZoomBp.GetCurSel());
	strLine = strCconfig + strCLen + strBase + _T(" += ") + strDef + _T("=") + strVari + _T("\n");
	strLine.Replace(_T("##"), _T("#"));
	mkFile.WriteString(strLine);

	strDef = IRISPWM_STRING;
	pCPeripheralDlg->m_Cbo_IrisPwm.GetLBText(pCPeripheralDlg->m_Cbo_IrisPwm.GetCurSel(), strVari);
	//strVari.Format(_T("%d"), pCPeripheralDlg->m_Cbo_IrisPwm.GetCurSel());
	strLine = strCconfig + strCIris + strBase + _T(" += ") + strDef + _T("=") + strVari + _T("\n");
	strLine.Replace(_T("##"), _T("#"));
	mkFile.WriteString(strLine);

	strDef = ETHIRQ_STRING;
	pCPeripheralDlg->m_Cbo_EthIrq.GetLBText(pCPeripheralDlg->m_Cbo_EthIrq.GetCurSel(), strVari);
	//strVari.Format(_T("%d"), pCPeripheralDlg->m_Cbo_EthIrq.GetCurSel());
	strLine = strCconfig + strBase + _T(" += ") + strDef + _T("=") + strVari + _T("\n");
	mkFile.WriteString(strLine);

	strDef = PERMOTION_STRING;
	pCPeripheralDlg->m_Cbo_Motion.GetLBText(pCPeripheralDlg->m_Cbo_Motion.GetCurSel(), strVari);
	//strVari.Format(_T("%d"), pCPeripheralDlg->m_Cbo_Motion.GetCurSel());
	strLine = strCconfig + strCMotion + strBase + _T(" += ") + strDef + _T("=") + strVari + _T("\n");
	mkFile.WriteString(strLine);

#if 0
	strDef = UARTRX1_STRING;
	pCPeripheralDlg->m_Cbo_UartRx1.GetLBText(pCPeripheralDlg->m_Cbo_UartRx1.GetCurSel(), strVari);
	//strVari.Format(_T("%d"), pCPeripheralDlg->m_Cbo_UartRx1.GetCurSel());
	strLine = strBase + _T(" += ") + strDef + _T("=") + strVari + _T("\n");
	mkFile.WriteString(strLine);

	strDef = UARTTX1_STRING;
	pCPeripheralDlg->m_Cbo_UartTx1.GetLBText(pCPeripheralDlg->m_Cbo_UartTx1.GetCurSel(), strVari);
	//strVari.Format(_T("%d"), pCPeripheralDlg->m_Cbo_UartTx1.GetCurSel());
	strLine = strBase + _T(" += ") + strDef + _T("=") + strVari + _T("\n");
	mkFile.WriteString(strLine);

	strDef = I2C2SDA_STRING;
	pCPeripheralDlg->m_Cbo_I2C2Sda.GetLBText(pCPeripheralDlg->m_Cbo_I2C2Sda.GetCurSel(), strVari);
	//strVari.Format(_T("%d"), pCPeripheralDlg->m_Cbo_I2C2Sda.GetCurSel());
	strLine = strBase + _T(" += ") + strDef + _T("=") + strVari + _T("\n");
	mkFile.WriteString(strLine);

	strDef = I2C2SCL_STRING;
	pCPeripheralDlg->m_Cbo_I2C2Scl.GetLBText(pCPeripheralDlg->m_Cbo_I2C2Scl.GetCurSel(), strVari);
	//strVari.Format(_T("%d"), pCPeripheralDlg->m_Cbo_I2C2Scl.GetCurSel());
	strLine = strBase + _T(" += ") + strDef + _T("=") + strVari + _T("\n");
	mkFile.WriteString(strLine);
#endif

	strDef = ZOOMBM_STRING;
	pCPeripheralDlg->m_Cbo_ZoomBm.GetLBText(pCPeripheralDlg->m_Cbo_ZoomBm.GetCurSel(), strVari);
	//strVari.Format(_T("%d"), pCPeripheralDlg->m_Cbo_ZoomBm.GetCurSel());
	strLine = strCconfig + strCLen + strBase + _T(" += ") + strDef + _T("=") + strVari + _T("\n");
	strLine.Replace(_T("##"), _T("#"));
	mkFile.WriteString(strLine);

	strDef = SDIO1RESET_STRING;
	pCPeripheralDlg->m_Cbo_Sdio1Reset.GetLBText(pCPeripheralDlg->m_Cbo_Sdio1Reset.GetCurSel(), strVari);
	//strVari.Format(_T("%d"), pCPeripheralDlg->m_Cbo_Sdio1Reset.GetCurSel());
	strLine = strCconfig + strBase + _T(" += ") + strDef + _T("=") + strVari + _T("\n");
	mkFile.WriteString(strLine);

	strDef = ETHRESET_STRING;
	pCPeripheralDlg->m_Cbo_EthReset.GetLBText(pCPeripheralDlg->m_Cbo_EthReset.GetCurSel(), strVari);
	//strVari.Format(_T("%d"), pCPeripheralDlg->m_Cbo_EthReset.GetCurSel());
	strLine = strCconfig + strBase + _T(" += ") + strDef + _T("=") + strVari + _T("\n");
	mkFile.WriteString(strLine);

	strDef = AUDIORESET_STRING;
	pCPeripheralDlg->m_Cbo_AudioReset.GetLBText(pCPeripheralDlg->m_Cbo_AudioReset.GetCurSel(), strVari);
	//strVari.Format(_T("%d"), pCPeripheralDlg->m_Cbo_AudioReset.GetCurSel());
	strLine = strCconfig + strBase + _T(" += ") + strDef + _T("=") + strVari + _T("\n");
	mkFile.WriteString(strLine);

	strDef = ADKEY_STRING;
	strVari = TR_CBO_ADC[pCPeripheralDlg->m_Cbo_AdKey.GetCurSel()];
	//strVari.Format(_T("%d"), pCPeripheralDlg->m_Cbo_AdKey.GetCurSel());
	strLine = strCconfig + strCKey0 + strBase + _T(" += ") + strDef + _T("=") + strVari + _T("\n");
	strLine.Replace(_T("##"), _T("#"));
	mkFile.WriteString(strLine);

	if (pCSPIDlg->m_Cbo_Cds.GetCurSel() == 0)
	{
		strDef = CDSINADC_STRING;
		strVari = TR_CBO_ADC[pCPeripheralDlg->m_Cbo_CdsIn.GetCurSel()];
		//strVari.Format(_T("%d"), pCPeripheralDlg->m_Cbo_CdsIn.GetCurSel());
		strLine = strCconfig + strBase + _T(" += ") + strDef + _T("=") + strVari + _T("\n");
		mkFile.WriteString(strLine);
	}
	else
	{
		strDef = CDSINGPIO_STRING;
		pCPeripheralDlg->m_Cbo_CdsIn.GetLBText(pCPeripheralDlg->m_Cbo_CdsIn.GetCurSel(), strVari);
		strLine = strCconfig + strBase + _T(" += ") + strDef + _T("=") + strVari + _T("\n");
		mkFile.WriteString(strLine);
	}

	strDef = KEY_C_STRING;
	pCPeripheralDlg->m_Cbo_KeyCenter.GetLBText(pCPeripheralDlg->m_Cbo_KeyCenter.GetCurSel(), strVari);
	strLine = strCconfig + strCKey1 + strBase + _T(" += ") + strDef + _T("=") + strVari + _T("\n");
	strLine.Replace(_T("##"), _T("#"));
	mkFile.WriteString(strLine);

	strDef = KEY_U_STRING;
	pCPeripheralDlg->m_Cbo_KeyUp.GetLBText(pCPeripheralDlg->m_Cbo_KeyUp.GetCurSel(), strVari);
	strLine = strCconfig + strCKey1 + strBase + _T(" += ") + strDef + _T("=") + strVari + _T("\n");
	strLine.Replace(_T("##"), _T("#"));
	mkFile.WriteString(strLine);

	strDef = KEY_D_STRING;
	pCPeripheralDlg->m_Cbo_KeyDown.GetLBText(pCPeripheralDlg->m_Cbo_KeyDown.GetCurSel(), strVari);
	strLine = strCconfig + strCKey1 + strBase + _T(" += ") + strDef + _T("=") + strVari + _T("\n");
	strLine.Replace(_T("##"), _T("#"));
	mkFile.WriteString(strLine);

	strDef = KEY_L_STRING;
	pCPeripheralDlg->m_Cbo_KeyRight.GetLBText(pCPeripheralDlg->m_Cbo_KeyRight.GetCurSel(), strVari);
	strLine = strCconfig + strCKey1 + strBase + _T(" += ") + strDef + _T("=") + strVari + _T("\n");
	strLine.Replace(_T("##"), _T("#"));
	mkFile.WriteString(strLine);

	strDef = KEY_R_STRING;
	pCPeripheralDlg->m_Cbo_KeyLeft.GetLBText(pCPeripheralDlg->m_Cbo_KeyLeft.GetCurSel(), strVari);
	strLine = strCconfig + strCKey1 + strBase + _T(" += ") + strDef + _T("=") + strVari;	// +_T("\n\n");
	strLine.Replace(_T("##"), _T("#"));
	mkFile.WriteString(strLine);

	mkFile.Close();
}


int CEN673_Configuration_GeneratorDlg::CStringtoIntGPIO(CString strGPIO)
{
	for (int i = 0; i < NUM_GPTO; i++)
	{
		if (strGPIO == CBO_GPIO[i])
			return i;
	}

	return -1;
}


int CEN673_Configuration_GeneratorDlg::CStringtoIntADC(CString strADC)
{
	for (int i = 0; i < NUM_ADC; i++)
	{
		if (strADC == TR_CBO_ADC[i])
			return i;
	}

	return -1;
}


void CEN673_Configuration_GeneratorDlg::OnTcnSelchangeTabList(NMHDR *pNMHDR, LRESULT *pResult)
{
	int iTabSel = m_Tab_List.GetCurSel();
	InitFileList(iTabSel);

	*pResult = 0;
}


void CEN673_Configuration_GeneratorDlg::InitFileList(int iNum) // FileList 초기화
{
	if (iNum == 0)
	{
		m_pDlg_SPI->ShowWindow(SW_SHOW);
		m_pDlg_Peripheral->ShowWindow(SW_HIDE);
	}
	else if (iNum == 1)
	{
		m_pDlg_SPI->ShowWindow(SW_HIDE);
		m_pDlg_Peripheral->ShowWindow(SW_SHOW);
		m_pDlg_Peripheral->EnableCheckCtrl();
	}

	RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
	return;
}


void CEN673_Configuration_GeneratorDlg::EnableCtrl(BOOL bEnable)
{
	m_Btn_Load.EnableWindow(bEnable);
	m_Btn_Save.EnableWindow(bEnable);

	m_Edit_Description.EnableWindow(bEnable);
	m_Edit_Path.EnableWindow(bEnable);

	m_pDlg_SPI->EnableCtrl(bEnable);
	m_pDlg_Peripheral->EnableCtrl(bEnable);
}



void CEN673_Configuration_GeneratorDlg::OnBnClickedCheckImagepath()		{ ChangeConfig(); }
void CEN673_Configuration_GeneratorDlg::OnBnClickedCheckIsp()			{ ChangeConfig(); }
void CEN673_Configuration_GeneratorDlg::OnBnClickedCheckPeripheral()	{ ChangeConfig(); }
void CEN673_Configuration_GeneratorDlg::ChangeConfig()
{
	CString strCommand = _T("");

	CString strLine = _T("");
	CString strDef = _T("");
	CString strVari = _T("");

	int intCconfig = 0;
	int strCTdn = 0;
	int strCLen = 0;
	int strCIris = 0;
	int strCMotion = 0;
	int strCKey0 = 0;
	int strCKey1 = 0;

	// Image Input Mode
	if (m_Chk_ImagePath.GetCheck())		intCconfig = 1;
	else								intCconfig = 0;

	if (intCconfig)
	{
		strDef = INPUTMODE_STRING;
		switch (pCSPIDlg->m_Cbo_Mode.GetCurSel())
		{
		case 0:		strVari.Format(_T("%d"), 0);	break;
		case 1:		strVari.Format(_T("%d"), 2);	break;
		case 2:		strVari.Format(_T("%d"), 3);	break;
		}
		strLine = strDef + _T("=") + strVari + _T("\n");
		strCommand = strCommand + strLine + _T("\n ");

		strDef = DIGITAL_STRING;
		strVari.Format(_T("%d"), pCSPIDlg->m_Cbo_Device.GetCurSel());
		strLine = strDef + _T("=") + strVari + _T("\n");
		strCommand = strCommand + strLine + _T("\n ");

		strDef = FRAMERATE_STRING;
		strVari.Format(_T("%d"), pCSPIDlg->m_Cbo_FrameRate.GetCurSel());
		strLine = strDef + _T("=") + strVari + _T("\n");
		strCommand = strCommand + strLine + _T("\n ");

		strDef = REEOLUTION_STRING;
		strVari.Format(_T("%d"), pCSPIDlg->m_Cbo_Resolution.GetCurSel());
		strLine = strDef + _T("=") + strVari + _T("\n");
		strCommand = strCommand + strLine + _T("\n ");
	}

	// ISP
	if (m_Chk_ISP.GetCheck())			intCconfig = 1;
	else								intCconfig = 0;

	if (intCconfig)
	{
		strDef = SENSOR_STRING;
		switch (pCSPIDlg->m_Cbo_Model.GetCurSel())
		{
		case 0:		strVari.Format(_T("%d"), 1);	break;
		case 1:		strVari.Format(_T("%d"), 4);	break;
		case 2:		strVari.Format(_T("%d"), 11);	break;
		case 3:		strVari.Format(_T("%d"), 12);	break;
		case 4:		strVari.Format(_T("%d"), 13);	break;
		case 5:		strVari.Format(_T("%d"), 14);	break;
		case 6:		strVari.Format(_T("%d"), 15);	break;
		case 7:		strVari.Format(_T("%d"), 18);	break;
		case 8:		strVari.Format(_T("%d"), 21);	break;
		case 9:		strVari.Format(_T("%d"), 22);	break;
		case 10:	strVari.Format(_T("%d"), 24);	break;
		}
		strLine = strDef + _T("=") + strVari + _T("\n");
		strCommand = strCommand + strLine + _T("\n ");

		strDef = CONTROL_STRING;
		strVari.Format(_T("%d"), pCSPIDlg->m_Cbo_Control.GetCurSel());
		strLine = strDef + _T("=") + strVari + _T("\n");
		strCommand = strCommand + strLine + _T("\n ");

		// Options
		strDef = KEY_STRING;
		strVari.Format(_T("%d"), pCSPIDlg->m_Cbo_Key.GetCurSel());
		strLine = strDef + _T("=") + strVari + _T("\n");
		strCommand = strCommand + strLine + _T("\n ");
		if (pCSPIDlg->m_Cbo_Key.GetCurSel() != 0)	strCKey0 = 0;
		else										strCKey0 = 1;
		if (pCSPIDlg->m_Cbo_Key.GetCurSel() != 1)	strCKey1 = 0;
		else										strCKey1 = 1;

		strDef = LENS_STRING;
		strVari.Format(_T("%d"), pCSPIDlg->m_Cbo_Lens.GetCurSel());
		strLine = strDef + _T("=") + strVari + _T("\n");
		strCommand = strCommand + strLine + _T("\n ");
		if (pCSPIDlg->m_Cbo_Lens.GetCurSel() != 1)	strCLen = 0;
		else										strCLen = 1;

		strDef = MORORIZED_STRING;
		strVari.Format(_T("%d"), pCSPIDlg->m_Cbo_MotorizedModel.GetCurSel());
		strLine = strDef + _T("=") + strVari + _T("\n");
		strCommand = strCommand + strLine + _T("\n ");

		strDef = IRIS_STRING;
		strVari.Format(_T("%d"), pCSPIDlg->m_Cbo_Iris.GetCurSel());
		strLine = strDef + _T("=") + strVari + _T("\n");
		strCommand = strCommand + strLine + _T("\n ");
		if (pCSPIDlg->m_Cbo_Iris.GetCurSel() == 0)	strCIris = 0;
		else										strCIris = 1;

		strDef = TDN_STRING;
		strVari.Format(_T("%d"), pCSPIDlg->m_Cbo_Tdn.GetCurSel());
		strLine = strDef + _T("=") + strVari + _T("\n");
		strCommand = strCommand + strLine + _T("\n ");
		if (pCSPIDlg->m_Cbo_Tdn.GetCurSel() != 2)	strCTdn = 0;
		else										strCTdn = 1;

		strDef = CDS_STRING;
		strVari.Format(_T("%d"), pCSPIDlg->m_Cbo_Cds.GetCurSel());
		strLine = strDef + _T("=") + strVari + _T("\n");
		strCommand = strCommand + strLine + _T("\n ");

		strDef = LED_STRING;
		strVari.Format(_T("%d"), pCSPIDlg->m_Cbo_Led.GetCurSel());
		strLine = strDef + _T("=") + strVari + _T("\n");
		strCommand = strCommand + strLine + _T("\n ");

		strDef = MOTION_STRING;
		strVari.Format(_T("%d"), pCSPIDlg->m_Cbo_Motion.GetCurSel());
		strLine = strDef + _T("=") + strVari + _T("\n");
		strCommand = strCommand + strLine + _T("\n ");
		if (pCSPIDlg->m_Cbo_Motion.GetCurSel() != 1)	strCMotion = 0;
		else											strCMotion = 1;

		// ETC
		strDef = SHADE_STRING;
		strVari.Format(_T("%d"), pCSPIDlg->m_Cbo_Shade.GetCurSel());
		strLine = strDef + _T("=") + strVari + _T("\n");
		strCommand = strCommand + strLine + _T("\n ");

		strDef = SAVE_STRING;
		strVari.Format(_T("%d"), pCSPIDlg->m_Cbo_Save.GetCurSel());
		strLine = strDef + _T("=") + strVari + _T("\n");
		strCommand = strCommand + strLine + _T("\n ");

		strDef = PARUSE_STRING;
		strVari.Format(_T("%d"), pCSPIDlg->m_Cbo_ParUse.GetCurSel());
		strLine = strDef + _T("=") + strVari + _T("\n");
		strCommand = strCommand + strLine + _T("\n ");

		strDef = PARSAVE_STRING;
		strVari.Format(_T("%d"), pCSPIDlg->m_Cbo_ParSave.GetCurSel());
		strLine = strDef + _T("=") + strVari + _T("\n");
		strCommand = strCommand + strLine + _T("\n ");
	}

	// Peripheral
	if (m_Chk_Peripheral.GetCheck())	intCconfig = 1;
	else								intCconfig = 0;

	if (intCconfig)
	{
		strDef = SENSOERESET_STRING;
		pCPeripheralDlg->m_Cbo_SensorReset.GetLBText(pCPeripheralDlg->m_Cbo_SensorReset.GetCurSel(), strVari);
		//strVari.Format(_T("%d"), pCPeripheralDlg->m_Cbo_SensorReset.GetCurSel());
		strLine = strDef + _T("=") + strVari + _T("\n");
		strCommand = strCommand + strLine + _T("\n ");

		strDef = ISPIRQLED_STRING;
		pCPeripheralDlg->m_Cbo_IspIrqLed.GetLBText(pCPeripheralDlg->m_Cbo_IspIrqLed.GetCurSel(), strVari);
		//strVari.Format(_T("%d"), pCPeripheralDlg->m_Cbo_IspIrqLed.GetCurSel());
		strLine = strDef + _T("=") + strVari + _T("\n");
		strCommand = strCommand + strLine + _T("\n ");

		strDef = ENCLED_STRING;
		pCPeripheralDlg->m_Cbo_EncLed.GetLBText(pCPeripheralDlg->m_Cbo_EncLed.GetCurSel(), strVari);
		//strVari.Format(_T("%d"), pCPeripheralDlg->m_Cbo_EncLed.GetCurSel());
		strLine = strDef + _T("=") + strVari + _T("\n");
		strCommand = strCommand + strLine + _T("\n ");

		strDef = ICRP0_STRING;
		pCPeripheralDlg->m_Cbo_IcrP0.GetLBText(pCPeripheralDlg->m_Cbo_IcrP0.GetCurSel(), strVari);
		//strVari.Format(_T("%d"), pCPeripheralDlg->m_Cbo_IcrP0.GetCurSel());
		strLine = strDef + _T("=") + strVari + _T("\n");
		strCommand = strCommand + strLine + _T("\n ");

		if (strCTdn)
		{
			strDef = ICRP1_STRING;
			pCPeripheralDlg->m_Cbo_IcrP1.GetLBText(pCPeripheralDlg->m_Cbo_IcrP1.GetCurSel(), strVari);
			//strVari.Format(_T("%d"), pCPeripheralDlg->m_Cbo_IcrP1.GetCurSel());
			strLine = strDef + _T("=") + strVari + _T("\n");
			strCommand = strCommand + strLine + _T("\n ");
		}

		if (strCLen)
		{
			strDef = FOCUSAP_STRING;
			pCPeripheralDlg->m_Cbo_FocusAp.GetLBText(pCPeripheralDlg->m_Cbo_FocusAp.GetCurSel(), strVari);
			//strVari.Format(_T("%d"), pCPeripheralDlg->m_Cbo_FocusAp.GetCurSel());
			strLine = strDef + _T("=") + strVari + _T("\n");
			strCommand = strCommand + strLine + _T("\n ");

			strDef = FOCUSAM_STRING;
			pCPeripheralDlg->m_Cbo_FocusAm.GetLBText(pCPeripheralDlg->m_Cbo_FocusAm.GetCurSel(), strVari);
			//strVari.Format(_T("%d"), pCPeripheralDlg->m_Cbo_FocusAm.GetCurSel());
			strLine = strDef + _T("=") + strVari + _T("\n");
			strCommand = strCommand + strLine + _T("\n ");

			strDef = FOCUSBP_STRING;
			pCPeripheralDlg->m_Cbo_FocusBp.GetLBText(pCPeripheralDlg->m_Cbo_FocusBp.GetCurSel(), strVari);
			//strVari.Format(_T("%d"), pCPeripheralDlg->m_Cbo_FocusBp.GetCurSel());
			strLine = strDef + _T("=") + strVari + _T("\n");
			strCommand = strCommand + strLine + _T("\n ");

			strDef = FOCUSBM_STRING;
			pCPeripheralDlg->m_Cbo_FocusBm.GetLBText(pCPeripheralDlg->m_Cbo_FocusBm.GetCurSel(), strVari);
			//strVari.Format(_T("%d"), pCPeripheralDlg->m_Cbo_FocusBm.GetCurSel());
			strLine = strDef + _T("=") + strVari + _T("\n");
			strCommand = strCommand + strLine + _T("\n ");

			strDef = ZOOMAP_STRING;
			pCPeripheralDlg->m_Cbo_ZoomAp.GetLBText(pCPeripheralDlg->m_Cbo_ZoomAp.GetCurSel(), strVari);
			//strVari.Format(_T("%d"), pCPeripheralDlg->m_Cbo_ZoomAp.GetCurSel());
			strLine = strDef + _T("=") + strVari + _T("\n");
			strCommand = strCommand + strLine + _T("\n ");

			strDef = ZOOMAM_STRING;
			pCPeripheralDlg->m_Cbo_ZoomAm.GetLBText(pCPeripheralDlg->m_Cbo_ZoomAm.GetCurSel(), strVari);
			//strVari.Format(_T("%d"), pCPeripheralDlg->m_Cbo_ZoomAm.GetCurSel());
			strLine = strDef + _T("=") + strVari + _T("\n");
			strCommand = strCommand + strLine + _T("\n ");
		}

		strDef = IRLED_STRING;
		pCPeripheralDlg->m_Cbo_IrLed.GetLBText(pCPeripheralDlg->m_Cbo_IrLed.GetCurSel(), strVari);
		//strVari.Format(_T("%d"), pCPeripheralDlg->m_Cbo_IrLed.GetCurSel());
		strLine = strDef + _T("=") + strVari + _T("\n");
		strCommand = strCommand + strLine + _T("\n ");

		if (strCLen)
		{
			strDef = ZOOMBP_STRING;
			pCPeripheralDlg->m_Cbo_ZoomBp.GetLBText(pCPeripheralDlg->m_Cbo_ZoomBp.GetCurSel(), strVari);
			//strVari.Format(_T("%d"), pCPeripheralDlg->m_Cbo_ZoomBp.GetCurSel());
			strLine = strDef + _T("=") + strVari + _T("\n");
			strCommand = strCommand + strLine + _T("\n ");
		}

		if (strCIris)
		{
			strDef = IRISPWM_STRING;
			pCPeripheralDlg->m_Cbo_IrisPwm.GetLBText(pCPeripheralDlg->m_Cbo_IrisPwm.GetCurSel(), strVari);
			//strVari.Format(_T("%d"), pCPeripheralDlg->m_Cbo_IrisPwm.GetCurSel());
			strLine = strDef + _T("=") + strVari + _T("\n");
			strCommand = strCommand + strLine + _T("\n ");
		}

		strDef = ETHIRQ_STRING;
		pCPeripheralDlg->m_Cbo_EthIrq.GetLBText(pCPeripheralDlg->m_Cbo_EthIrq.GetCurSel(), strVari);
		//strVari.Format(_T("%d"), pCPeripheralDlg->m_Cbo_EthIrq.GetCurSel());
		strLine = strDef + _T("=") + strVari + _T("\n");
		strCommand = strCommand + strLine + _T("\n ");

		if (strCMotion)
		{
			strDef = PERMOTION_STRING;
			pCPeripheralDlg->m_Cbo_Motion.GetLBText(pCPeripheralDlg->m_Cbo_Motion.GetCurSel(), strVari);
			//strVari.Format(_T("%d"), pCPeripheralDlg->m_Cbo_Motion.GetCurSel());
			strLine = strDef + _T("=") + strVari + _T("\n");
			strCommand = strCommand + strLine + _T("\n ");
		}
#if 0
		strDef = UARTRX1_STRING;
		pCPeripheralDlg->m_Cbo_UartRx1.GetLBText(pCPeripheralDlg->m_Cbo_UartRx1.GetCurSel(), strVari);
		//strVari.Format(_T("%d"), pCPeripheralDlg->m_Cbo_UartRx1.GetCurSel());
		strLine = strDef + _T("=") + strVari + _T("\n");
		strCommand = strCommand + strLine + _T("\n ");

		strDef = UARTTX1_STRING;
		pCPeripheralDlg->m_Cbo_UartTx1.GetLBText(pCPeripheralDlg->m_Cbo_UartTx1.GetCurSel(), strVari);
		//strVari.Format(_T("%d"), pCPeripheralDlg->m_Cbo_UartTx1.GetCurSel());
		strLine = strDef + _T("=") + strVari + _T("\n");
		strCommand = strCommand + strLine + _T("\n ");

		strDef = I2C2SDA_STRING;
		pCPeripheralDlg->m_Cbo_I2C2Sda.GetLBText(pCPeripheralDlg->m_Cbo_I2C2Sda.GetCurSel(), strVari);
		//strVari.Format(_T("%d"), pCPeripheralDlg->m_Cbo_I2C2Sda.GetCurSel());
		strLine = strDef + _T("=") + strVari + _T("\n");
		strCommand = strCommand + strLine + _T("\n ");

		strDef = I2C2SCL_STRING;
		pCPeripheralDlg->m_Cbo_I2C2Scl.GetLBText(pCPeripheralDlg->m_Cbo_I2C2Scl.GetCurSel(), strVari);
		//strVari.Format(_T("%d"), pCPeripheralDlg->m_Cbo_I2C2Scl.GetCurSel());
		strLine = strDef + _T("=") + strVari + _T("\n");
		strCommand = strCommand + strLine + _T("\n ");
#endif

		if (strCLen)
		{
			strDef = ZOOMBM_STRING;
			pCPeripheralDlg->m_Cbo_ZoomBm.GetLBText(pCPeripheralDlg->m_Cbo_ZoomBm.GetCurSel(), strVari);
			//strVari.Format(_T("%d"), pCPeripheralDlg->m_Cbo_ZoomBm.GetCurSel());
			strLine = strDef + _T("=") + strVari + _T("\n");
			strCommand = strCommand + strLine + +_T("\n ");
		}

		strDef = SDIO1RESET_STRING;
		pCPeripheralDlg->m_Cbo_Sdio1Reset.GetLBText(pCPeripheralDlg->m_Cbo_Sdio1Reset.GetCurSel(), strVari);
		//strVari.Format(_T("%d"), pCPeripheralDlg->m_Cbo_Sdio1Reset.GetCurSel());
		strLine = strDef + _T("=") + strVari + _T("\n");
		strCommand = strCommand + strLine + _T("\n ");

		strDef = ETHRESET_STRING;
		pCPeripheralDlg->m_Cbo_EthReset.GetLBText(pCPeripheralDlg->m_Cbo_EthReset.GetCurSel(), strVari);
		//strVari.Format(_T("%d"), pCPeripheralDlg->m_Cbo_EthReset.GetCurSel());
		strLine = strDef + _T("=") + strVari + _T("\n");
		strCommand = strCommand + strLine + _T("\n ");

		strDef = AUDIORESET_STRING;
		pCPeripheralDlg->m_Cbo_AudioReset.GetLBText(pCPeripheralDlg->m_Cbo_AudioReset.GetCurSel(), strVari);
		//strVari.Format(_T("%d"), pCPeripheralDlg->m_Cbo_AudioReset.GetCurSel());
		strLine = strDef + _T("=") + strVari + _T("\n");
		strCommand = strCommand + strLine + _T("\n ");

		if (strCKey0)
		{
			strDef = ADKEY_STRING;
			strVari = TR_CBO_ADC[pCPeripheralDlg->m_Cbo_AdKey.GetCurSel()];
			//strVari.Format(_T("%d"), pCPeripheralDlg->m_Cbo_AdKey.GetCurSel());
			strLine = strDef + _T("=") + strVari + _T("\n");
			strCommand = strCommand + strLine + _T("\n ");
		}

		if (pCSPIDlg->m_Cbo_Cds.GetCurSel() == 0)
		{
			strDef = CDSINADC_STRING;
			strVari = TR_CBO_ADC[pCPeripheralDlg->m_Cbo_CdsIn.GetCurSel()];
			//strVari.Format(_T("%d"), pCPeripheralDlg->m_Cbo_CdsIn.GetCurSel());
			strLine = strDef + _T("=") + strVari + _T("\n");
			strCommand = strCommand + strLine + _T("\n ");
		}
		else
		{
			strDef = CDSINGPIO_STRING;
			pCPeripheralDlg->m_Cbo_CdsIn.GetLBText(pCPeripheralDlg->m_Cbo_CdsIn.GetCurSel(), strVari);
			strLine = strDef + _T("=") + strVari + _T("\n");
			strCommand = strCommand + strLine + _T("\n ");
		}

		if (strCKey1)
		{
			strDef = KEY_C_STRING;
			pCPeripheralDlg->m_Cbo_KeyCenter.GetLBText(pCPeripheralDlg->m_Cbo_KeyCenter.GetCurSel(), strVari);
			strLine = strDef + _T("=") + strVari + _T("\n");
			strCommand = strCommand + strLine + _T("\n ");

			strDef = KEY_U_STRING;
			pCPeripheralDlg->m_Cbo_KeyUp.GetLBText(pCPeripheralDlg->m_Cbo_KeyUp.GetCurSel(), strVari);
			strLine = strDef + _T("=") + strVari + _T("\n");
			strCommand = strCommand + strLine + _T("\n ");

			strDef = KEY_D_STRING;
			pCPeripheralDlg->m_Cbo_KeyDown.GetLBText(pCPeripheralDlg->m_Cbo_KeyDown.GetCurSel(), strVari);
			strLine = strDef + _T("=") + strVari + _T("\n");
			strCommand = strCommand + strLine + _T("\n ");

			strDef = KEY_L_STRING;
			pCPeripheralDlg->m_Cbo_KeyRight.GetLBText(pCPeripheralDlg->m_Cbo_KeyRight.GetCurSel(), strVari);
			strLine = strDef + _T("=") + strVari + _T("\n");
			strCommand = strCommand + strLine + _T(" ");

			strDef = KEY_R_STRING;
			pCPeripheralDlg->m_Cbo_KeyLeft.GetLBText(pCPeripheralDlg->m_Cbo_KeyLeft.GetCurSel(), strVari);
			strLine = strDef + _T("=") + strVari + _T("\n");
			strCommand = strCommand + strLine + _T("\n ");
		}
	}

	pDownCompileOption673->m_Edit_ConfigGen.SetWindowTextW(strCommand);
}