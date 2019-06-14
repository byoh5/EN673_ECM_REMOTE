// DownDownOption673.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Downloader.h"
#include "DownDownOption673.h"
#include "afxdialogex.h"


UINT	JTAGFlashReadThread(LPVOID pParam);
UINT	JTAGFlashEraseThread(LPVOID pParam);
UINT	JTAGFlashTestThread(LPVOID pParam);
UINT	UserAreaReadThread(LPVOID pParam);
UINT	UserAreaEraseThread(LPVOID pParam);
UINT	UserAreaWriteThread(LPVOID pParam);


// CDownDownOption673 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDownDownOption673, CDialogEx)

CDownDownOption673::CDownDownOption673(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDownDownOption673::IDD, pParent)
{
	m_bOnChangeEditMacaddress = FALSE;
}

CDownDownOption673::~CDownDownOption673()
{
}

void CDownDownOption673::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_MACADDRESS1, m_Edit_MacAddress[0]);
	DDX_Control(pDX, IDC_EDIT_MACADDRESS2, m_Edit_MacAddress[1]);
	DDX_Control(pDX, IDC_EDIT_MACADDRESS3, m_Edit_MacAddress[2]);
	DDX_Control(pDX, IDC_EDIT_MACADDRESS4, m_Edit_MacAddress[3]);
	DDX_Control(pDX, IDC_EDIT_MACADDRESS5, m_Edit_MacAddress[4]);
	DDX_Control(pDX, IDC_EDIT_MACADDRESS6, m_Edit_MacAddress[5]);
	DDX_Control(pDX, IDC_EDIT_USERAREA_FLASHSIZE, m_Edit_FlashSize);
	DDX_Control(pDX, IDC_EDIT_USERADDRESS, m_Edit_UserAddress);
	DDX_Control(pDX, IDC_EDIT_BOOTADDRESS, m_Edit_BootAddress);
	DDX_Control(pDX, IDC_RADIO_DOWNOPTION_JTAG, m_Radio_JTAG);
	DDX_Control(pDX, IDC_RADIO_DOWNOPTION_SPI, m_Radio_SPI);
}


BEGIN_MESSAGE_MAP(CDownDownOption673, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_EN673FLASHREAD, &CDownDownOption673::OnBnClickedButtonEn673flashread)
	ON_BN_CLICKED(IDC_BUTTON_EN673FLASHERASE, &CDownDownOption673::OnBnClickedButtonEn673flasherase)
	ON_BN_CLICKED(IDC_BUTTON_EN673FLASHTEST, &CDownDownOption673::OnBnClickedButtonEn673flashtest)
	ON_BN_CLICKED(IDC_BUTTON_USERAREAREAD, &CDownDownOption673::OnBnClickedButtonUserarearead)
	ON_BN_CLICKED(IDC_BUTTON_USERAREAERASE, &CDownDownOption673::OnBnClickedButtonUserareaerase)
	ON_BN_CLICKED(IDC_BUTTON_USERAREAWRITE, &CDownDownOption673::OnBnClickedButtonUserareawrite)
	ON_EN_UPDATE(IDC_EDIT_BOOTADDRESS, &CDownDownOption673::OnEnUpdateEditBootaddress)
	ON_EN_UPDATE(IDC_EDIT_MACADDRESS1, &CDownDownOption673::OnEnUpdateEditMacaddress1)
	ON_EN_UPDATE(IDC_EDIT_MACADDRESS2, &CDownDownOption673::OnEnUpdateEditMacaddress2)
	ON_EN_UPDATE(IDC_EDIT_MACADDRESS3, &CDownDownOption673::OnEnUpdateEditMacaddress3)
	ON_EN_UPDATE(IDC_EDIT_MACADDRESS4, &CDownDownOption673::OnEnUpdateEditMacaddress4)
	ON_EN_UPDATE(IDC_EDIT_MACADDRESS5, &CDownDownOption673::OnEnUpdateEditMacaddress5)
	ON_EN_UPDATE(IDC_EDIT_MACADDRESS6, &CDownDownOption673::OnEnUpdateEditMacaddress6)
	ON_EN_CHANGE(IDC_EDIT_MACADDRESS1, &CDownDownOption673::OnEnChangeEditMacaddress1)
	ON_EN_CHANGE(IDC_EDIT_MACADDRESS2, &CDownDownOption673::OnEnChangeEditMacaddress2)
	ON_EN_CHANGE(IDC_EDIT_MACADDRESS3, &CDownDownOption673::OnEnChangeEditMacaddress3)
	ON_EN_CHANGE(IDC_EDIT_MACADDRESS4, &CDownDownOption673::OnEnChangeEditMacaddress4)
	ON_EN_CHANGE(IDC_EDIT_MACADDRESS5, &CDownDownOption673::OnEnChangeEditMacaddress5)
	ON_EN_CHANGE(IDC_EDIT_MACADDRESS6, &CDownDownOption673::OnEnChangeEditMacaddress6)
END_MESSAGE_MAP()


// CDownDownOption673 메시지 처리기입니다.


BOOL CDownDownOption673::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	pDownDownOption673 = this;

	int i = 0;
	CString str = _T("");
	/*
	// Communication
	i = ReadIni(SEC_DOWN, KEY_673DOWNOPTION_COM, DEF_673DOWNOPTION_COM);
	if (i >= NUM_673DOWNOPTION_COM) i = DEF_673DOWNOPTION_COM;
	if (i == 0)	m_Radio_JTAG.SetCheck(1);
	else		m_Radio_SPI.SetCheck(1);
	*/
	m_Radio_JTAG.SetCheck(1);
	m_Radio_SPI.SetCheck(0);
	//m_Radio_JTAG.SetCheck(TRUE);
	m_Radio_SPI.EnableWindow(FALSE);
	m_Radio_SPI.ShowWindow(FALSE);

	// ini 파일 초기화 불러오는 코드 필요.

	// Size, User Address
	BYTE byDeviceSize = 0;

	i = ReadIni(SEC_DOWN, KEY_673DOWNOPTION_SIZE, 0);

	//byDeviceSize = pDownloaderDlg->GetDeviceSize_JTAG();
	// SPI는 검사하지 않는걸로!! 무조건 재부팅됨

	if ((i == 16) || (i == 8) || (i == 4)) { // ini에 저장된 것을 읽은 값이 정상
		if ((byDeviceSize == 16) || (byDeviceSize == 8) || (byDeviceSize == 4)) { // Device에서 읽어온 값이 정상

			m_byDeviceSize = byDeviceSize;

			if (i == byDeviceSize) { // ini 값과 device에서 가져온 값이 같음
				str = ReadIni(SEC_DOWN, KEY_673DOWNOPTION_USERADDR, _T(""));
				str = str.Trim(_T("\t "));
				if (str.Find(_T("0x")) == 0) str = str.Right(str.GetLength() - 2);

				if (!CheckHex(str))						m_uiUserAddress = (m_byDeviceSize * 1024 * 1024) - 4096; // Device size - 4KB
				else if (HexToDec(str) > m_byDeviceSize)	m_uiUserAddress = (m_byDeviceSize * 1024 * 1024) - 4096; // Device size - 4KB
				else									m_uiUserAddress = HexToDec(str);
			}
			else { // ini 값과 device에서 가져온 값이 다름
				m_uiUserAddress = (byDeviceSize * 1024 * 1024) - 4096; // Device - 4KB
			}
		}
		else { // Device에서 읽어온 값이 비정상
			m_byDeviceSize = i;

			str = ReadIni(SEC_DOWN, KEY_673DOWNOPTION_USERADDR, _T(""));
			str = str.Trim(_T("\t "));
			if (str.Find(_T("0x")) == 0) str = str.Right(str.GetLength() - 2);

			if (!CheckHex(str))						m_uiUserAddress = (m_byDeviceSize * 1024 * 1024) - 4096; // Device size - 4KB
			else if (HexToDec(str) > m_byDeviceSize)	m_uiUserAddress = (m_byDeviceSize * 1024 * 1024) - 4096; // Device size - 4KB
			else									m_uiUserAddress = HexToDec(str);
		}
	}
	else { // ini에 저장된 것을 읽은 값이 비정상
		if ((byDeviceSize == 16) || (byDeviceSize == 8) || (byDeviceSize == 4)) { // Device에서 읽어온 값이 정상
			m_byDeviceSize = byDeviceSize;
		}
		else { // Device에서 읽어온 값이 정상
			m_byDeviceSize = DEF_673DOWNOPTION_SIZE;
		}
		m_uiUserAddress = (m_byDeviceSize * 1024 * 1024) - 4096; // Device size - 4KB
	}

	SetDeviceSize(m_byDeviceSize);

	str.Format(_T("0x%X"), m_uiUserAddress);
	m_Edit_UserAddress.SetWindowTextW(str);

	// Boot Address : User Address + 0
	str = ReadIni(SEC_DOWN, KEY_673DOWNOPTION_BOOTADDR, _T(""));
	//str = str.Trim(_T("\t "));
	//if (str.Find(_T("0x")) == 0) str = str.Right(str.GetLength() - 2);
	m_uiBootAddress = HexToDec(str);
	if (!CheckHex(str))	m_uiBootAddress = 0x10000;

	str.Format(_T("0x%X"), m_uiBootAddress);
	m_Edit_BootAddress.SetWindowTextW(str);

	// Mac Address : User Address + 16
	int iMACnt = 0;
	str = ReadIni(SEC_DOWN, KEY_673DOWNOPTION_MACADDR, _T(""));
	CString temp;

	while (iMACnt < 6) {
		AfxExtractSubString(temp, str, iMACnt, ':');
		m_byMacAddress[iMACnt] = HexToDec(temp);
		iMACnt++;
	}

	/*
	while (iMACnt < 6) {
		str = str.Trim(_T("\t "));

		if (iMACnt <= 4) {
			i = str.Find(_T(":"));
			if ((i > 2) || (i == -1)) break;
			if (!CheckHex(str.Left(i))) break;
			m_byMacAddress[iMACnt] = HexToDec(str.Left(i));
			str.Right(str.GetLength() - (i + 1));
		}
		else if (iMACnt == 5) {
			if (str.GetLength() > 2) break;
			if (!CheckHex(str)) break;
			m_byMacAddress[iMACnt] = HexToDec(str);
			str = _T("");
		}

		iMACnt++;
	}
	*/

	for (i = 0; i < 6; i++) {
		m_Edit_MacAddress[i].SetLimitText(2);

		if (iMACnt < 6) m_byMacAddress[i] = 0;

		str.Format(_T("%02X"), m_byMacAddress[i]);
		m_Edit_MacAddress[i].SetWindowTextW(str);
	}

	bRunJTAGFlashReadThread = FALSE;
	bRunJTAGFlashEraseThread = FALSE;
	bRunJTAGFlashTestThread = FALSE;
	bRunUserAreaReadThread = FALSE;
	bRunUserAreaWriteThread = FALSE;

	g_pJTAGFlashReadThread = FALSE;
	g_pJTAGFlashEraseThread = FALSE;
	g_pJTAGFlashTestThread = FALSE;
	g_pUserAreaReadThread = FALSE;
	g_pUserAreaWriteThread = FALSE;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL CDownDownOption673::PreTranslateMessage(MSG* pMsg)
{
	// Default Window Message
	if (DefaultWindowMessage(pMsg))	return TRUE;
	else							return CDialogEx::PreTranslateMessage(pMsg);
}


void CDownDownOption673::OnBnClickedButtonEn673flashread()
{
	// ----------------------------------------------------------------------------------------------------
	// Run Thread
	if (m_Radio_JTAG.GetCheck())	g_pJTAGFlashReadThread = AfxBeginThread(JTAGFlashReadThread, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
}

// ====================================================================================================
// JTAGFlashReadThread
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
UINT JTAGFlashReadThread(LPVOID pParam)
{
	bRunJTAGFlashReadThread = TRUE;

	// ----------------------------------------------------------------------------------------------------
	// 컨트롤 비활성화
	pDownloaderDlg->m_Btn_Close.EnableWindow(FALSE);
	pDownloaderDlg->EnableCtrl(FALSE);
	pDownloaderDlg->Check_Timer_Off();
	pDownloaderDlg->Connect_Timer_Off();

	// ----------------------------------------------------------------------------------------------------
	// 실행
	pDownDownOption673->JTAGFlashRead();

	// ----------------------------------------------------------------------------------------------------
	// 컨트롤 활성화
	pDownloaderDlg->m_Btn_Close.EnableWindow(TRUE);
	pDownloaderDlg->EnableCtrl(TRUE);

	// ----------------------------------------------------------------------------------------------------
	// Flash Window
	Sleep(500);

	pDownloaderDlg->SendMessage(WM_USER + 2/*WM_CHECK_ACTIVE*/, 0, 0);

	bRunJTAGFlashReadThread = FALSE;
	sendMsg(ConnectSocket, "rem_release ");
	pDownloaderDlg->Check_Timer_On();
	
	return TRUE;
}

#define READBUFFER	(1024*8)
// ====================================================================================================
// JTAGFlashRead
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CDownDownOption673::JTAGFlashRead()
{
	int i = 0;
	int iAddress = 0;
	int iCnt = 0;
	UINT32 err = 0;
	CString strMsg = _T("");
	BOOL bReturn = FALSE;
	CFile *pBinFile = NULL;

	UINT32 ret = 0;
	UINT8* memblock = NULL;
	UINT8* memcompblock = NULL;
	UINT8* Nmemblock = NULL;
	UINT32* memblock32 = NULL;
	UINT32* Nmemblock32 = NULL;
	UINT32 retry = 0;

	// 저장 공간 지정
	CString strBinFile = _T("");
	CString strDefExt = _T("bin");
	CString strFilter = _T("Binary Files(*.bin)|*.bin|");

	int state = -1;

	// Save Dialog
	if (!ShowSaveFileDlg(&strBinFile, strDefExt, strFilter, this))
		return;

	// Clear Output Box
	pDownOutput->AddOutBox(_T(" > JTAG Flash Read \r\n"), DOWNOUTPUT_CLEARALL);

	// Change Tab
	int iTabCount = pDownloaderDlg->m_Tab_List.GetItemCount();
	pDownloaderDlg->m_Tab_List.SetCurSel(iTabCount - 1);
	pDownloaderDlg->InitFileList(iTabCount - 1);
	Sleep(100);

	// Get Platform Information
	//int iPlatformSel = pMainDlg->GetPlatformSel();

	// ----------------------------------------------------------------------------------------------------
	// Init JTAG
	strMsg.Format(_T("Init JTAG...... "));
	pDownOutput->AddOutBox(strMsg);

#if 1
	if (ConnectSocket != NULL)
		state = sendMsg(ConnectSocket, "rem_check ");

	if (state < 0)
	{
		strMsg.Format(_T("Fail : Can't initialize JTAG"));
		goto END;
	}

	char ocd_flag;
	state = recv(ConnectSocket, &ocd_flag, sizeof(ocd_flag), 0);

	if (state > 0)
	{
		if (ocd_flag != '0')
		{
			strMsg.Format(_T("Fail : Can't initialize JTAG"));
			goto END;
		}
	}
	else
	{
		strMsg.Format(_T("Fail : Can't initialize JTAG"));
		goto END;
	}
#endif

	sendMsg(ConnectSocket, "rem_hold ");

	/*
	pJTAG->JTAGClose();
	pMainDlg->InitSPI();

	iCnt = 0;
	while (TRUE) {
		if ((err = EN673_JTAG_INIT(pMainDlg->m_Platform[iPlatformSel].GetJTAGClkdiv())) == 0) break;
		if (iCnt>10) {
			strMsg.Format(_T("Fail : Can't initialize JTAG. (Error : 0x%08x)"), err);
			goto END;
		}
		iCnt++;
		Sleep(0);
	}
	*/

	// Reset CPU
	// 리셋을 안하면 flash id가 읽어지지 않음
	//if (err |= pJTAG->rc()) { strMsg.Format(_T("Fail : rc (Error : 0x%08x)"), err); goto END; }

	strMsg.Format(_T("End\r\n"));
	pDownOutput->AddOutBox(strMsg);

	// ----------------------------------------------------------------------------------------------------
	// Start Read
	// Time
	ULONGLONG dwTimeStart = 0;
	ULONGLONG dwTimeEnd = 0;
	ULONGLONG dwTime = 0;

	// Enter
	strMsg.Format(_T("\r\n"));
	pDownOutput->AddOutBox(strMsg);

	// Get Size
	UINT32 uiSize = 0;
	if (err = Get_device_SIZE(&uiSize)) {
		strMsg.Format(_T("Getting flash id failed."));
		goto END;
	}
	uiSize = uiSize / 8 * 1024 * 1024; // Megabit -> Byte

	// Read
	strMsg.Format(_T("Read... %.2f%% "), ((float)(iAddress * 4) / (float)uiSize) * 100);
	pDownOutput->AddOutBox(strMsg, 1);

	dwTimeStart = GetTickCount();

	iCnt = 0;
	memblock = (UINT8*)malloc(uiSize + 4);
	memcompblock = (UINT8*)malloc(uiSize + 4);
	//Nmemblock = (UINT8*)malloc(uiSize + 4);
	retry = (uiSize) / (READBUFFER);
	for (i = 0; i < retry; i++){
#if 0
		do{
			jtag_read_block32(FLASH_BASE + (READBUFFER * i), (UINT32*)(memblock + (READBUFFER * i)), (READBUFFER / 4), JTAG_COMMON_MODULE_IDX);
			jtag_read_block32(FLASH_BASE + (READBUFFER * i), (UINT32*)(memcompblock + (READBUFFER * i)), (READBUFFER / 4), JTAG_COMMON_MODULE_IDX);
		} while (ret = memcmp((memblock + (READBUFFER * i)), (memcompblock + (READBUFFER * i)), READBUFFER));
#else
		//jtag_read_block32(FLASH_BASE + (READBUFFER * i), (UINT32*)(memblock + (READBUFFER * i)), (READBUFFER / 4), JTAG_COMMON_MODULE_IDX);
		state = getDataFromRemote(ConnectSocket, FLASH_BASE + (READBUFFER * i), READBUFFER, JTAG_COMMON_MODULE_IDX, (UINT32*)(memblock + (READBUFFER * i)));
		if (state)
		{
			strMsg.Format(_T("Read Fail"));
			pDownOutput->AddOutBox(strMsg);
			goto END;
		}

#endif
		iCnt++;
		if (iCnt % 100 == 0){
			double p = ((float)(i) / (float)retry) * 100;
			strMsg.Format(_T("Read... %.2f%%"), p);
			pDownOutput->AddOutBox(strMsg, 1);
		}

		Sleep(0);
	}

	// change endian fr
	memblock32 = (UINT32*)memblock;
	
	/*
	Nmemblock32 = (UINT32*)Nmemblock;
	for (i = 0; i < (uiSize / 4) + 1; i++){
		*(Nmemblock32 + i) = pJTAG->jtag_htonl((UINT32)*(memblock32 + i));
	}
	*/

	dwTimeEnd = GetTickCount();
	dwTime = dwTimeEnd - dwTimeStart;

	if (dwTime == 0)		strMsg.Format(_T("Read... %.2f%%, Time : %.2fs (%.2fKByte/s)\r\n"), 100.0, ((float)dwTime) / 1000, 0);
	else				strMsg.Format(_T("Read... %.2f%%, Time : %.2fs (%.2fKByte/s)\r\n"), 100.0, ((float)dwTime) / 1000, (uiSize / 1024) / (((float)dwTime) / 1000));
	pDownOutput->AddOutBox(strMsg, 1);

	// Create file
	strMsg.Format(_T("Save Data : %s \r\n"), strBinFile);
	pDownOutput->AddOutBox(strMsg);

	pBinFile = new CFile;
	if (!pBinFile->Open(strBinFile, CFile::typeBinary | CFile::modeWrite | CFile::modeCreate)) {
		strMsg.Format(_T("Can't create file."));
		goto END;
	}
	pBinFile->Write(memblock, uiSize);
	pBinFile->Close();
	delete pBinFile;
	pBinFile = NULL;

	strMsg.Format(_T("Read Complete!\r\n"));
	pDownOutput->AddOutBox(strMsg);

	bReturn = TRUE;

END:
	//tap_reset_global0();
	//pJTAG->JTAGClose();

	sendMsg(ConnectSocket, "rem_rst ");

	if (bReturn) {
	}
	else {
		if (strMsg != _T("")) {
			NetClo(ConnectSocket);
			ConnectSocket = NULL;
			Wait(10);
			NetClo(StateSocket);
			ConnectSocket = NULL;

			pDownOutput->AddOutBox(strMsg + _T("\r\n"));
			AfxMessageBox(strMsg, MB_ICONWARNING);
		}
	}

	if (pBinFile != NULL) delete pBinFile;
	if (memblock) free(memblock);
	if (memcompblock) free(memcompblock);
	//if (Nmemblock) free(Nmemblock);
}

void CDownDownOption673::OnBnClickedButtonEn673flasherase()
{
	// ----------------------------------------------------------------------------------------------------
	// Run Thread
	if (m_Radio_JTAG.GetCheck())	g_pJTAGFlashEraseThread = AfxBeginThread(JTAGFlashEraseThread, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
}

UINT JTAGFlashEraseThread(LPVOID pParam)
{
	bRunJTAGFlashEraseThread = TRUE;

	// ----------------------------------------------------------------------------------------------------
	// 컨트롤 비활성화
	pDownloaderDlg->m_Btn_Close.EnableWindow(FALSE);
	pDownloaderDlg->EnableCtrl(FALSE);

	// ----------------------------------------------------------------------------------------------------
	// JTAG Thread Hold
	sendMsg(ConnectSocket, "rem_hold ");
	pDownloaderDlg->Check_Timer_Off();
	pDownloaderDlg->Connect_Timer_Off();


	// ----------------------------------------------------------------------------------------------------
	// 실행
	pDownDownOption673->JTAGFlashErase();

	// ----------------------------------------------------------------------------------------------------
	// 컨트롤 활성화
	pDownloaderDlg->m_Btn_Close.EnableWindow(TRUE);
	pDownloaderDlg->EnableCtrl(TRUE);

	// ----------------------------------------------------------------------------------------------------
	// Flash Window
	Sleep(500);
	pDownloaderDlg->SendMessage(WM_USER + 2/*WM_CHECK_ACTIVE*/, 0, 0);

	bRunJTAGFlashEraseThread = FALSE;
	sendMsg(ConnectSocket, "rem_release ");
	pDownloaderDlg->Check_Timer_On();

	return TRUE;
}


// ====================================================================================================
// CDownDownOption673::JTAGFlashErase
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CDownDownOption673::JTAGFlashErase()
{
	int i = 0;
	int iCnt = 0;
	BOOL bReturn = FALSE;
	UINT32 err = 0;
	CString strMsg = _T("");

	// Clear Output Box
	pDownOutput->AddOutBox(_T(" > JTAG Flash Erase \r\n"), DOWNOUTPUT_CLEARALL);

	// Change Tab
	int iTabCount = pDownloaderDlg->m_Tab_List.GetItemCount();
	pDownloaderDlg->m_Tab_List.SetCurSel(iTabCount - 1);
	pDownloaderDlg->InitFileList(iTabCount - 1);
	Sleep(100);

	// Get Platform Information
	//int iPlatformSel = pMainDlg->GetPlatformSel();

	// ----------------------------------------------------------------------------------------------------
	// Init JTAG
	strMsg.Format(_T("Init JTAG...... "));
	pDownOutput->AddOutBox(strMsg);

	/*
	pJTAG->JTAGClose();
	pMainDlg->InitSPI();

	iCnt = 0;
	while (TRUE) {
		if ((err = EN673_JTAG_INIT(pMainDlg->m_Platform[iPlatformSel].GetJTAGClkdiv())) == 0) break;
		if (iCnt>5) {
			strMsg.Format(_T("Fail : Can't initialize JTAG. (Error : 0x%08x)"), err);
			goto END;
		}
		iCnt++;
		Sleep(0);
	}
	
	// Reset CPU
	// 리셋을 안하면 flash id가 읽어지지 않음
	if (err |= pJTAG->rc()) { strMsg.Format(_T("Fail : rc (Error : 0x%08x)"), err); goto END; }
	*/
#if 1
	int state = 0;

	if (ConnectSocket != NULL)
		state = sendMsg(ConnectSocket, "rem_check ");

	if (state < 0)
	{
		strMsg.Format(_T("Fail : Can't initialize JTAG"));
		goto END;
	}

	char ocd_flag;
	state = recv(ConnectSocket, &ocd_flag, sizeof(ocd_flag), 0);

	if (state > 0)
	{
		if (ocd_flag != '0')
		{
			strMsg.Format(_T("Fail : Can't initialize JTAG"));
			goto END;
		}
	}
	else
	{
		strMsg.Format(_T("Fail : Can't initialize JTAG"));
		goto END;
	}
#endif
	strMsg.Format(_T("End\r\n"));
	pDownOutput->AddOutBox(strMsg);

	// Stall CPU
	strMsg.Format(_T("Stall..... "));
	pDownOutput->AddOutBox(strMsg);

	if(sendMsg(ConnectSocket, "rem_st ") < 0)
	{
		strMsg.Format(_T("Fail : now unstalled. (Error : 0x%08x)"), err);
		goto END;
	}

	/*
	UINT8 stalled = 0;
	for (UINT8 ncpu = 4; ncpu < 6; ncpu++) {
		try {
			if (err = jtag_stall_cpu(ncpu)) throw err;
			if (err = jtag_check_stalled_cpu(ncpu, &stalled)) throw err;
			if (!stalled) throw 0xffffffff;
		}
		catch (UINT32 err) {
			strMsg.Format(_T("Fail : now unstalled. (Error : 0x%08x)"), err);
			goto END;
		}
	}
	*/

	strMsg.Format(_T("Success : now stalled\r\n"));
	pDownOutput->AddOutBox(strMsg);

#if !CHANGE_EN674
	// Watchdog
	if (err |= reset_sys_wdt()) {    // Add for Reset Watchdog!!!! Flash write will fail when watchdog enabled!
		strMsg.Format(_T("Watchdog enable fail! (Error : 0x%08x)"), err);
		goto END;
	}
#endif

	// Init Flash
	strMsg.Format(_T("Init Flash...... "));
	pDownOutput->AddOutBox(strMsg);

	iCnt = 0;
	while (TRUE) {
		if ((err = Sfls_init_quad()) == 0) break;
		if (iCnt>5) {
			strMsg.Format(_T("Fail : Can't init flash memory. (Error : 0x%08x)"), err);
			goto END;
		}
		iCnt++;
		Sleep(0);
	}

	strMsg.Format(_T("End\r\n"));
	pDownOutput->AddOutBox(strMsg);

	// ----------------------------------------------------------------------------------------------------
	// Start Erase
	// Erase
	strMsg.Format(_T("Erase all...(It takes more than one minute!) "));
	pDownOutput->AddOutBox(strMsg);

#if 0
	if (err = Sfls_erase_all()) {
		strMsg.Format(_T("Failed erase. (Error : 0x%08x)"), err);
		goto ENDJTAGFLASHERASE;
	}
#else
	UINT32 read = 0;
	UINT32 rd_com;

	if (err = sfls_write_en()) {
		strMsg.Format(_T("sfls_write_en (Error : 0x%08x)"), err);
		goto END;
	}

	//if (err = jtag_read32(SFLS_REG_BASE + _SFLS_WBCONT, &read, JTAG_COMMON_MODULE_IDX)) {
	if (err < getDataFromRemote(ConnectSocket, SFLS_REG_BASE + _SFLS_WBCONT, 4, JTAG_COMMON_MODULE_IDX, &read)) {
		strMsg.Format(_T("jtag_read32_1 (Error : 0x%08x)"), err);
		goto END;
	}
	read = ntohl(read);
	read = (read & 0x00ffffff) | (CMD_CE << REG_CMD);
	read = ntohl(read);
	//if (err = jtag_write32(SFLS_REG_BASE + _SFLS_WBCONT, read | (CMD_CE << REG_CMD), JTAG_COMMON_MODULE_IDX)) {
	if (err < setDataFromRemote(ConnectSocket, SFLS_REG_BASE + _SFLS_WBCONT, 4, JTAG_COMMON_MODULE_IDX, &read)) {
		strMsg.Format(_T("jtag_write32_1 (Error : 0x%08x)"), err);
		goto END;
	}

	//if(err = jtag_read32(SFLS_REG_BASE + _SFLS_WBCONT, &read, JTAG_COMMON_MODULE_IDX)) {
	if (err < getDataFromRemote(ConnectSocket, SFLS_REG_BASE + _SFLS_WBCONT, 4, JTAG_COMMON_MODULE_IDX, &read)) {
		strMsg.Format(_T("jtag_read32_2 (Error : 0x%08x)"), err);
		goto END;
	}

	read = ntohl(read);
	rd_com = (read & 0x00030000) >> WB_RDCMD_IOM;
	read = 0x00020800 | (rd_com << REG_CMD_IOM);
	read = ntohl(read);
	//if (err = jtag_write32(SFLS_REG_BASE + _SFLS_CMD, 0x00020800 | (rd_com << REG_CMD_IOM), JTAG_COMMON_MODULE_IDX)) {
	if (err < setDataFromRemote(ConnectSocket, SFLS_REG_BASE + _SFLS_CMD, 4, JTAG_COMMON_MODULE_IDX, &read)) {
		strMsg.Format(_T("jtag_write32_2 (Error : 0x%08x)"), err);
		goto END;
	}
#if 0
	/*
	if(err = sfls_wait_for_reg_request()) {
	strMsg.Format(_T("sfls_wait_for_reg_request (Error : 0x%08x)"), err);
	goto ENDJTAGFLASHERASE;
	}
	*/
#else
	clock_t start;
	start = clock();
	do{
		//err |= jtag_read32(SFLS_REG_BASE + _SFLS_CMD, &read, JTAG_COMMON_MODULE_IDX);
		err |= getDataFromRemote(ConnectSocket, SFLS_REG_BASE + _SFLS_CMD, 4, JTAG_COMMON_MODULE_IDX, &read);
		read = ntohl(read);
		if (err) {
			strMsg.Format(_T("sfls_wait_for_reg_request (Error : 0x%08x)"), err);
			goto END;
		}
		Sleep(0);
	} while (read & (1 << REG_REQ));
#endif
#endif

	strMsg.Format(_T("End (%.2fs)\r\n"), ((float)(clock() - start)) / 1000);
	pDownOutput->AddOutBox(strMsg);

	strMsg.Format(_T("Erase Complete!\r\n"));
	pDownOutput->AddOutBox(strMsg);

	bReturn = TRUE;

	// ----------------------------------------------------------------------------------------------------
END:
	//tap_reset_global0();
	//pJTAG->JTAGClose();
	
	sendMsg(ConnectSocket, "rem_rst ");
	
	if (bReturn) {
	}
	else {
		if (strMsg != _T("")) {
			NetClo(ConnectSocket);
			ConnectSocket = NULL;
			Wait(10);
			NetClo(StateSocket);
			ConnectSocket = NULL;

			pDownOutput->AddOutBox(strMsg + _T("\r\n"));
			AfxMessageBox(strMsg, MB_ICONWARNING);
		}
	}
}


void CDownDownOption673::OnBnClickedButtonEn673flashtest()
{
// ----------------------------------------------------------------------------------------------------
// Run Thread
	if (m_Radio_JTAG.GetCheck())	g_pJTAGFlashTestThread = AfxBeginThread(JTAGFlashTestThread, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
}

// ====================================================================================================
// JTAGFlashTestThread
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
UINT JTAGFlashTestThread(LPVOID pParam)
{
	bRunJTAGFlashTestThread = TRUE;

	// ----------------------------------------------------------------------------------------------------
	// 컨트롤 비활성화
	pDownloaderDlg->m_Btn_Close.EnableWindow(FALSE);
	pDownloaderDlg->EnableCtrl(FALSE);

	// ----------------------------------------------------------------------------------------------------
	// JTAG Thread Hold
	sendMsg(ConnectSocket, "rem_hold ");

	// ----------------------------------------------------------------------------------------------------
	// 실행
	pDownloaderDlg->JTAGFlashTest672();

	// ----------------------------------------------------------------------------------------------------
	// 컨트롤 활성화
	pDownloaderDlg->m_Btn_Close.EnableWindow(TRUE);
	pDownloaderDlg->EnableCtrl(TRUE);

	// ----------------------------------------------------------------------------------------------------
	// Flash Window
	Sleep(500);
	pDownloaderDlg->SendMessage(WM_USER + 2/*WM_CHECK_ACTIVE*/, 0, 0);

	bRunJTAGFlashTestThread = FALSE;
	sendMsg(ConnectSocket, "rem_release ");

	return TRUE;
}


void CDownDownOption673::OnBnClickedButtonUserarearead()
{
	g_pUserAreaReadThread = AfxBeginThread(UserAreaReadThread, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
}

// ====================================================================================================
// UserAreaReadThread
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
UINT UserAreaReadThread(LPVOID pParam)
{
	bRunUserAreaReadThread = TRUE;

	// ----------------------------------------------------------------------------------------------------
	// 컨트롤 비활성화
	pDownloaderDlg->EnableCtrl(FALSE);

	// ----------------------------------------------------------------------------------------------------
	// 실행
	if (pDownDownOption673->m_Radio_JTAG.GetCheck()) pDownDownOption673->JTAGUserAreaRead();

	// ----------------------------------------------------------------------------------------------------
	// + Down Option 탭으로 돌아가기
	pDownloaderDlg->m_Tab_List.SetCurSel(1);
	pDownloaderDlg->InitFileList(1);

	// ----------------------------------------------------------------------------------------------------
	// 컨트롤 활성화
	pDownloaderDlg->EnableCtrl(TRUE);

	// ----------------------------------------------------------------------------------------------------
	// Flash Window
	Sleep(500);
	pDownloaderDlg->SendMessage(WM_USER + 2/*WM_CHECK_ACTIVE*/, 0, 0);

	bRunUserAreaReadThread = FALSE;

	return TRUE;
}

// ====================================================================================================
// CDownDownOption673::JTAGUserAreaRead
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CDownDownOption673::JTAGUserAreaRead()
{
	int i = 0;
	int iCnt = 0;
	UINT32 err = 0;
	BOOL bReturn = FALSE;
	CString strMsg = _T("");

	// Clear Output Box
	pDownOutput->AddOutBox(_T(" > JTAG User Data Read \r\n"), DOWNOUTPUT_CLEARALL);

	// Change Tab
	int iTabCount = pDownloaderDlg->m_Tab_List.GetItemCount();
	pDownloaderDlg->m_Tab_List.SetCurSel(iTabCount - 1);
	pDownloaderDlg->InitFileList(iTabCount - 1);
	Sleep(100);

	// Get Platform Information
	//int iPlatformSel = pDownloaderDlg->GetPlatformSel();

	// ----------------------------------------------------------------------------------------------------
	// Init JTAG
	strMsg.Format(_T("Init JTAG...... "));
	pDownOutput->AddOutBox(strMsg);

	/*
	pJTAG->JTAGClose();
	pMainDlg->InitSPI();

	iCnt = 0;
	while (TRUE) {
		if ((err = EN673_JTAG_INIT(pMainDlg->m_Platform[iPlatformSel].GetJTAGClkdiv())) == 0) break;
		if (iCnt>10) {
			strMsg.Format(_T("Fail : Can't initialize JTAG. (Error : 0x%08x)"), err);
			goto ENDJTAGUSERAREAREAD;
		}
		iCnt++;
		Sleep(0);
	}
	*/
#if 1
	int state = 0;

	if (ConnectSocket != NULL)
		state = sendMsg(ConnectSocket, "rem_check ");

	if (state < 0)
	{
		strMsg.Format(_T("Fail : Can't initialize JTAG"));
		goto ENDJTAGUSERAREAREAD;
	}

	char ocd_flag;
	state = recv(ConnectSocket, &ocd_flag, sizeof(ocd_flag), 0);

	if (state > 0)
	{
		if (ocd_flag != '0')
		{
			strMsg.Format(_T("Fail : Can't initialize JTAG"));
			goto ENDJTAGUSERAREAREAD;
		}
	}
	else
	{
		strMsg.Format(_T("Fail : Can't initialize JTAG"));
		goto ENDJTAGUSERAREAREAD;
	}
#endif


	strMsg.Format(_T("End\r\n"));
	pDownOutput->AddOutBox(strMsg);

// ----------------------------------------------------------------------------------------------------
// Start Read
	// Read
	strMsg.Format(_T("Read... "));
	pDownOutput->AddOutBox(strMsg);

	UINT8 rdata[5000];
	UINT8 Nrdata[5000];
	UINT32* rdata32;
	UINT32* Nrdata32;

	//if (err = jtag_read_block32(FLASH_BASE + m_uiUserAddress, (UINT32*)rdata, 4096 / 4, JTAG_COMMON_MODULE_IDX)) {
	if (err < getDataFromRemote(ConnectSocket, FLASH_BASE + m_uiUserAddress, 4096, JTAG_COMMON_MODULE_IDX, (UINT32*)rdata)) {
		strMsg.Format(_T("Failed verify! (Error : 0x%08x)"), err);
		goto ENDJTAGUSERAREAREAD;
	}

	strMsg.Format(_T("End\r\n"));
	pDownOutput->AddOutBox(strMsg);

	// change endian
	rdata32 = (UINT32*)rdata;
	/*
	Nrdata32 = (UINT32*)Nrdata;
	for (i = 0; i < (4096 / 4) + 1; i++) {
		*(Nrdata32 + i) = pJTAG->jtag_htonl((UINT32)*(rdata32 + i));
	}
	*/

	SetBootAddress((rdata[0] << 24) + (rdata[1] << 16) + (rdata[2] << 8) + rdata[3]);
	strMsg.Format(_T("Boot Address : 0x%x\r\n"), (rdata[0] << 24) + (rdata[1] << 16) + (rdata[2] << 8) + rdata[3]);
	pDownOutput->AddOutBox(strMsg);

	SetMacAddress(rdata[16], rdata[17], rdata[18], rdata[19], rdata[20], rdata[21]);
	strMsg.Format(_T("Mac Address : %02X:%02X:%02X:%02X:%02X:%02X\r\n"), rdata[16], rdata[17], rdata[18], rdata[19], rdata[20], rdata[21]);
	pDownOutput->AddOutBox(strMsg);

	strMsg.Format(_T("Read Complete!\r\n"));
	pDownOutput->AddOutBox(strMsg);

	bReturn = TRUE;

ENDJTAGUSERAREAREAD:
	//tap_reset_global0();
	//sendMsg(ConnectSocket, "rem_rst ");

	/*
	jtag_continue(4);
	jtag_continue(5);
	pJTAG->JTAGClose();
	*/

	if (bReturn) {
	}
	else {
		if (strMsg != _T("")) {
			NetClo(ConnectSocket);
			ConnectSocket = NULL;
			Wait(10);
			NetClo(StateSocket);
			ConnectSocket = NULL;

			pDownOutput->AddOutBox(strMsg + _T("\r\n"));
			AfxMessageBox(strMsg, MB_ICONWARNING);
		}
	}
}

void CDownDownOption673::OnBnClickedButtonUserareaerase()
{
	g_pUserAreaEraseThread = AfxBeginThread(UserAreaEraseThread, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
}

// ====================================================================================================
// UserAreaEraseThread
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
UINT UserAreaEraseThread(LPVOID pParam)
{
	bRunUserAreaEraseThread = TRUE;

	// ----------------------------------------------------------------------------------------------------
	// 컨트롤 비활성화
	pDownloaderDlg->m_Btn_Close.EnableWindow(FALSE);

	// ----------------------------------------------------------------------------------------------------
	// JTAG Thread Hold
	sendMsg(ConnectSocket, "rem_hold ");
	pDownloaderDlg->Check_Timer_Off();
	pDownloaderDlg->Connect_Timer_Off();

	// ----------------------------------------------------------------------------------------------------
	// Check Size
	CString strMsg = _T("");

	UINT32 uiDeviceSize = 0;

	// Check JTAG/SPI, Get Device Size
	if (pDownDownOption673->m_Radio_JTAG.GetCheck()) uiDeviceSize = pDownloaderDlg->GetDeviceSize_JTAG();
	else {
		AfxMessageBox(_T("JTAG, SPI 중 하나를 선택해주세요."));
		return FALSE;
	}

	if (uiDeviceSize == 0) {
		AfxMessageBox(_T("Device Size를 읽을 수 없습니다."));
		return FALSE;
	}

	if (pDownDownOption673->m_byDeviceSize == uiDeviceSize) {
		if ((pDownDownOption673->m_byDeviceSize * 1024 * 1024) <= pDownDownOption673->m_uiUserAddress) {
			strMsg.Format(_T("User Address가 Flash Size보다 큽니다."));
			AfxMessageBox(strMsg);
			return FALSE;
		}
		if ((pDownDownOption673->m_uiUserAddress % SECTOR_SIZE) != 0) {
			strMsg.Format(_T("User Address는 Sector 단위(4KB)여야 합니다."));
			AfxMessageBox(strMsg);
			return FALSE;
		}
	}
	else {
		strMsg.Format(_T("저장되어있는 Flash size와 읽어온 Flash Size가 다릅니다.\r\n\
						 						읽어온 Flash Size의 값으로 초기화한 후에 진행하시겠습니까?\r\n\
																		(Flash Size : %dMB, User Address : 0x%X)"), uiDeviceSize, (uiDeviceSize * 1024 * 1024) - SECTOR_SIZE);
		if (AfxMessageBox(strMsg, MB_YESNO) == IDYES) {
			pDownDownOption673->SetDeviceSize(uiDeviceSize);
			pDownDownOption673->SetUserAddress((uiDeviceSize * 1024 * 1024) - SECTOR_SIZE);
		}
		else return FALSE;
	}

	// ----------------------------------------------------------------------------------------------------
	// 실행
	if (pDownDownOption673->m_Radio_JTAG.GetCheck()) pDownDownOption673->JTAGUserAreaErase();

	// ----------------------------------------------------------------------------------------------------
	// + Down Option 탭으로 돌아가기
	pDownloaderDlg->m_Tab_List.SetCurSel(1);
	pDownloaderDlg->InitFileList(1);

	// ----------------------------------------------------------------------------------------------------
	// 컨트롤 활성화
	pDownloaderDlg->m_Btn_Close.EnableWindow(TRUE);

	// ----------------------------------------------------------------------------------------------------
	// Flash Window
	Sleep(500);
	pDownloaderDlg->SendMessage(WM_USER + 2/*WM_CHECK_ACTIVE*/, 0, 0);

	bRunUserAreaEraseThread = FALSE;
	sendMsg(ConnectSocket, "rem_release ");
	pDownloaderDlg->Check_Timer_On();

	return TRUE;
}

// ====================================================================================================
// CDownDownOption673::JTAGUserAreaErase
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CDownDownOption673::JTAGUserAreaErase()
{
	UINT32 err = 0;
	BOOL bReturn = FALSE;
	CString strMsg = _T("");

	// Clear Output Box
	pDownOutput->AddOutBox(_T(" > JTAG User Data Erase \r\n"), DOWNOUTPUT_CLEARALL);

	// Change Tab
	int iTabCount = pDownloaderDlg->m_Tab_List.GetItemCount();
	pDownloaderDlg->m_Tab_List.SetCurSel(iTabCount - 1);
	pDownloaderDlg->InitFileList(iTabCount - 1);
	Sleep(100);

	// Get Platform Information
	//int iPlatformSel = pECMDlg->GetPlatformSel();

	// ----------------------------------------------------------------------------------------------------
	// Init JTAG
	strMsg.Format(_T("Init JTAG...... "));
	pDownOutput->AddOutBox(strMsg);

#if 1
	int state = 0;

	if (ConnectSocket != NULL)
		state = sendMsg(ConnectSocket, "rem_check ");

	if (state < 0)
	{
		strMsg.Format(_T("Fail : Can't initialize JTAG"));
		goto END;
	}

	char ocd_flag;
	state = recv(ConnectSocket, &ocd_flag, sizeof(ocd_flag), 0);

	if (state > 0)
	{
		if (ocd_flag != '0')
		{
			strMsg.Format(_T("Fail : Can't initialize JTAG"));
			goto END;
		}
	}
	else
	{
		strMsg.Format(_T("Fail : Can't initialize JTAG"));
		goto END;
	}
#endif
	//if (!pJTAG->JTAGInitial(strMsg)) goto END;

	strMsg.Format(_T("End\r\n"));
	pDownOutput->AddOutBox(strMsg);

	// ----------------------------------------------------------------------------------------------------
	// Start Erase
	strMsg.Format(_T("Erasing... "));
	pDownOutput->AddOutBox(strMsg);

	if (err = Sfls_erase_sect(m_uiUserAddress)) {
		strMsg.Format(_T("Fail : Can't erase flash memory. (Error : %x%08x)"), err);
		goto END;
	}

	strMsg.Format(_T("Erase Complete!\r\n"));
	pDownOutput->AddOutBox(strMsg);

	bReturn = TRUE;
END:
	//pJTAG->JTAGClose();

	if (bReturn) {
	}
	else {
		if (strMsg != _T("")) {
			NetClo(ConnectSocket);
			ConnectSocket = NULL;
			Wait(10);
			NetClo(StateSocket);
			ConnectSocket = NULL;

			pDownOutput->AddOutBox(strMsg + _T("\r\n"));
			AfxMessageBox(strMsg, MB_ICONWARNING);
		}
	}
}


void CDownDownOption673::OnBnClickedButtonUserareawrite()
{
	g_pUserAreaWriteThread = AfxBeginThread(UserAreaWriteThread, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
}

// ====================================================================================================
// UserAreaWriteThread
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
UINT UserAreaWriteThread(LPVOID pParam)
{
	bRunUserAreaWriteThread = TRUE;

	// ----------------------------------------------------------------------------------------------------
	// 컨트롤 비활성화
	pDownloaderDlg->m_Btn_Close.EnableWindow(FALSE);

	// ----------------------------------------------------------------------------------------------------
	// JTAG Thread Hold
	sendMsg(ConnectSocket, "rem_hold ");
	pDownloaderDlg->Check_Timer_Off();
	pDownloaderDlg->Connect_Timer_Off();


	// ----------------------------------------------------------------------------------------------------
	// Check Size
	CString strMsg = _T("");

	UINT32 uiDeviceSize = 0;

	// Check JTAG/SPI, Get Device Size
	if (pDownDownOption673->m_Radio_JTAG.GetCheck()) uiDeviceSize = pDownloaderDlg->GetDeviceSize_JTAG();
	else {
		AfxMessageBox(_T("JTAG, SPI 중 하나를 선택해주세요."));
		return FALSE;
	}

	if (uiDeviceSize == 0) {
		AfxMessageBox(_T("Device Size를 읽을 수 없습니다."));
		return FALSE;
	}

	if (pDownDownOption673->m_byDeviceSize == uiDeviceSize) {
		if ((pDownDownOption673->m_byDeviceSize * 1024 * 1024) <= pDownDownOption673->m_uiUserAddress) {
			strMsg.Format(_T("User Address가 Flash Size보다 큽니다."));
			AfxMessageBox(strMsg);
			return FALSE;
		}
		if ((pDownDownOption673->m_uiUserAddress % SECTOR_SIZE) != 0) {
			strMsg.Format(_T("User Address는 Sector 단위(4KB)여야 합니다."));
			AfxMessageBox(strMsg);
			return FALSE;
		}
	}
	else {
		strMsg.Format(_T("저장되어있는 Flash size와 읽어온 Flash Size가 다릅니다.\r\n\
						 						읽어온 Flash Size의 값으로 초기화한 후에 진행하시겠습니까?\r\n\
																		(Flash Size : %dMB, User Address : 0x%X)"), uiDeviceSize, (uiDeviceSize * 1024 * 1024) - SECTOR_SIZE);
		if (AfxMessageBox(strMsg, MB_YESNO) == IDYES) {
			pDownDownOption673->SetDeviceSize(uiDeviceSize);
			pDownDownOption673->SetUserAddress((uiDeviceSize * 1024 * 1024) - SECTOR_SIZE);
		}
		else return FALSE;
	}

	// ----------------------------------------------------------------------------------------------------
	// 실행
	if (pDownDownOption673->m_Radio_JTAG.GetCheck()) pDownDownOption673->JTAGUserAreaWrite();

	// ----------------------------------------------------------------------------------------------------
	// + Down Option 탭으로 돌아가기
	pDownloaderDlg->m_Tab_List.SetCurSel(1);
	pDownloaderDlg->InitFileList(1);

	// ----------------------------------------------------------------------------------------------------
	// 컨트롤 활성화
	pDownloaderDlg->m_Btn_Close.EnableWindow(TRUE);

	// ----------------------------------------------------------------------------------------------------
	// Flash Window
	Sleep(500);
	pDownloaderDlg->SendMessage(WM_USER + 2/*WM_CHECK_ACTIVE*/, 0, 0);

	bRunUserAreaWriteThread = FALSE;
	sendMsg(ConnectSocket, "rem_release ");
	pDownloaderDlg->Check_Timer_On();

	return TRUE;
}


// ====================================================================================================
// CDownDownOption673::JTAGUserAreaWrite
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CDownDownOption673::JTAGUserAreaWrite()
{
	int i = 0;
	int iCnt = 0;
	BOOL bReturn = FALSE;
	UINT32 err = 0;
	CString strMsg = _T("");

	// Read Buffer
	UCHAR *rdata = NULL;
	UCHAR *Nrdata = NULL;
	UINT32* rdata32 = NULL;
	UINT32* Nrdata32 = NULL;

	// Write Buffer
	UCHAR *wdata = NULL;
	UCHAR *Nwdata = NULL;
	UINT32* wdata32 = NULL;
	UINT32* Nwdata32 = NULL;
	//m_uiUserAddress = 0x00fff000;
#if JTAGUSERAREAWRITE_DEBUG
	// 저장 공간 지정
	CString strBinFile1 = _T("");
	CString strDefExt = _T("bin");
	CString strFilter = _T("Binary Files(*.bin)|*.bin|");

	// Save Dialog
	if(!ShowSaveFileDlg(&strBinFile1, strDefExt, strFilter, this))
		return;

	CString strBinFile2 = strBinFile1.Left(strBinFile1.GetLength()-4) + _T("2.bin");

	ULONGLONG dwTimeStart = 0;
	ULONGLONG dwTimeEnd = 0;
	ULONGLONG dwTime = 0;
	CFile pBinFile1;
	CFile pBinFile2;
#endif
	// Clear Output Box
	pDownOutput->AddOutBox(_T(" > JTAG User Data Write \r\n"), DOWNOUTPUT_CLEARALL);

	// Change Tab
	int iTabCount = pDownloaderDlg->m_Tab_List.GetItemCount();
	pDownloaderDlg->m_Tab_List.SetCurSel(iTabCount - 1);
	pDownloaderDlg->InitFileList(iTabCount - 1);
	Sleep(100);

	// Get Platform Information
	//int iPlatformSel = pDownloaderDlg->GetPlatformSel();

	// ----------------------------------------------------------------------------------------------------
	// Init JTAG
	strMsg.Format(_T("Init JTAG...... "));
	pDownOutput->AddOutBox(strMsg);

	/*
	pJTAG->JTAGClose();
	pMainDlg->InitSPI();

	iCnt = 0;
	while (TRUE) {
#if 0
		if ((err = EN673_JTAG_INIT(pDownloaderDlg->m_Platform[iPlatformSel].GetJTAGClkdiv())) == 0) break;
#else
		err |= MPSSE_init(pMainDlg->m_Platform[iPlatformSel].GetJTAGClkdiv());
		err |= tap_reset();
		err |= tap_set_ir_debug();
		if (!err) break;
#endif
		if (iCnt>5) {
			strMsg.Format(_T("Fail : Can't initialize JTAG. (Error : 0x%08x)"), err);
			goto END;
		}
		iCnt++;
		Sleep(0);
	}

	// Reset CPU
	// 리셋을 안하면 flash id가 읽어지지 않음
	if (err |= pJTAG->rc()) { strMsg.Format(_T("Fail : rc (Error : 0x%08x)"), err); goto END; }
	*/

#if 1
	int state = 0;

	if (ConnectSocket != NULL)
		state = sendMsg(ConnectSocket, "rem_check ");

	if (state < 0)
	{
		strMsg.Format(_T("Fail : Can't initialize JTAG"));
		goto END;
	}

	char ocd_flag;
	state = recv(ConnectSocket, &ocd_flag, sizeof(ocd_flag), 0);

	if (state > 0)
	{
		if (ocd_flag != '0')
		{
			strMsg.Format(_T("Fail : Can't initialize JTAG"));
			goto END;
		}
	}
	else
	{
		strMsg.Format(_T("Fail : Can't initialize JTAG"));
		goto END;
	}
#endif

	strMsg.Format(_T("End\r\n"));
	pDownOutput->AddOutBox(strMsg);

	// Stall CPU
	strMsg.Format(_T("Stall..... "));
	pDownOutput->AddOutBox(strMsg);

	if (sendMsg(ConnectSocket, "rem_st ") < 0)
	{
		strMsg.Format(_T("Fail : now unstalled. (Error : 0x%08x)"), err);
		goto END;
	}
	/*
	UINT8 stalled = 0;
	for (UINT8 ncpu = 4; ncpu < 6; ncpu++) {
		try {
			if (err = jtag_stall_cpu(ncpu)) throw err;
			if (err = jtag_check_stalled_cpu(ncpu, &stalled)) throw err;
			if (!stalled) throw 0xffffffff;
		}
		catch (UINT32 err) {
			strMsg.Format(_T("Fail : now unstalled. (Error : 0x%08x)"), err);
			goto END;
		}
	}
	*/

	strMsg.Format(_T("Success : now stalled\r\n"));
	pDownOutput->AddOutBox(strMsg);

#if !CHANGE_EN674
	// Watchdog
	if (err |= reset_sys_wdt()) {    // Add for Reset Watchdog!!!! Flash write will fail when watchdog enabled!
		strMsg.Format(_T("Watchdog enable fail! (Error : 0x%08x)"), err);
		goto END;
	}
#endif

	// Init Flash
	strMsg.Format(_T("Init Flash...... "));
	pDownOutput->AddOutBox(strMsg);

	iCnt = 0;
	while (TRUE) {
		if ((err = Sfls_init_quad()) == 0) break;
		if (iCnt>5) {
			strMsg.Format(_T("Fail : Can't init flash memory. (Error : 0x%08x)"), err);
			goto END;
		}
		iCnt++;
		Sleep(0);
	}

	strMsg.Format(_T("End\r\n"));
	pDownOutput->AddOutBox(strMsg);

// ----------------------------------------------------------------------------------------------------
	// Read
	strMsg.Format(_T("Reading... "));

	rdata = new UCHAR[SECTOR_SIZE];
	Nrdata = new UCHAR[SECTOR_SIZE];
	memset(rdata, 0, sizeof(UCHAR)*SECTOR_SIZE);
	memset(Nrdata, 0, sizeof(UCHAR)*SECTOR_SIZE);

	// Read
	//if (err = pJTAG->read32(FLASH_BASE + m_uiUserAddress, (UINT32*)rdata, SECTOR_SIZE / 4, JTAG_COMMON_MODULE_IDX)) {
	if (err = getDataFromRemote(ConnectSocket, FLASH_BASE + m_uiUserAddress, SECTOR_SIZE, JTAG_COMMON_MODULE_IDX, (UINT32*)rdata)) {
		strMsg.Format(_T("Failed read! (Error : 0x%08x)"), err);
		goto END;
	}

	// change endian
	rdata32 = (UINT32*)rdata;
	Nrdata32 = (UINT32*)Nrdata;
	/*
	for (i = 0; i < (SECTOR_SIZE / 4); i++) {
		*(Nrdata32 + i) = pJTAG->jtag_htonl((UINT32)*(rdata32 + i));
		Sleep(0);
	}
	*/

	strMsg.Format(_T("End\r\n"));
	pDownOutput->AddOutBox(strMsg);
	
	// Erase
	strMsg.Format(_T("Erasing... "));
	pDownOutput->AddOutBox(strMsg);

	if (err = Sfls_erase_sect(m_uiUserAddress)) {
		strMsg.Format(_T("Fail : Can't erase flash memory. (Error : %x%08x)"), err);
		goto END;
	}

	strMsg.Format(_T("End\r\n"));
	pDownOutput->AddOutBox(strMsg);

	// Write
	strMsg.Format(_T("Writing... "));
	pDownOutput->AddOutBox(strMsg);

	wdata = new UCHAR[4096];
	Nwdata = new UCHAR[4096];
	memset(wdata, 0, sizeof(UCHAR) * 4096);
	memset(Nwdata, 0, sizeof(UCHAR) * 4096);

	if (htonl(rdata32[1]) == 0x5555AAAA) {
		memcpy(wdata, rdata32, SECTOR_SIZE);
	}
	else {
		memcpy(wdata, Nrdata32, SECTOR_SIZE);
	}

	// Boot Address
	for (i = 0; i < 4; i++)
		wdata[(4 - 1) - i] = (m_uiBootAddress >> (i * 8)) & 0xff;
	// Mac Address
	for (i = 0; i < 6; i++)
		wdata[16 + i] = m_byMacAddress[i];

	// change endian
	wdata32 = (UINT32*)wdata;
	/*
	Nwdata32 = (UINT32*)Nwdata;
	for (i = 0; i < (4096 / 4); i++) {
		*(Nwdata32 + i) = pJTAG->jtag_htonl((UINT32)*(wdata32 + i));
		Sleep(0);
	}
	*/

	// Write
	//if (err = Sfls_write32((UINT32*)Nwdata, 4096 / 4, m_uiUserAddress)) {
	if (err = Sfls_write32((UINT32*)wdata32, 4096 / 4, m_uiUserAddress)) {
		strMsg.Format(_T("Fail : Can't write flash memory. (Error : 0x%08x)"), err);
		goto END;
	}

	strMsg.Format(_T("End\r\n"));
	pDownOutput->AddOutBox(strMsg);

	// Verify
	strMsg.Format(_T("Verifing... "));
	pDownOutput->AddOutBox(strMsg);

	// Read
	char veribuf[4096];
	//if (err = jtag_read_block32(FLASH_BASE + m_uiUserAddress, (UINT32*)veribuf, 4096 / 4, JTAG_COMMON_MODULE_IDX)) {
	if (err = getDataFromRemote(ConnectSocket, FLASH_BASE + m_uiUserAddress, 4096, JTAG_COMMON_MODULE_IDX, (UINT32*)veribuf)) {
		strMsg.Format(_T("Failed verify! (Error : 0x%08x)"), err);
		goto END;
	}

	// Verify
	if (memcmp(veribuf, wdata, 4096) != 0) {
		strMsg.Format(_T("Failed verify!"));
		goto END;
	}

	strMsg.Format(_T("End\r\n"));
	pDownOutput->AddOutBox(strMsg);

	strMsg.Format(_T("Write Complete!\r\n"));
	pDownOutput->AddOutBox(strMsg);

	bReturn = TRUE;

	// ----------------------------------------------------------------------------------------------------
END:
	//tap_reset_global0();
	//pJTAG->JTAGClose();

	sendMsg(ConnectSocket, "rem_rst ");

	if (bReturn) {
	}
	else {
		if (strMsg != _T("")) {
			NetClo(ConnectSocket);
			ConnectSocket = NULL;
			Wait(10);
			NetClo(StateSocket);
			ConnectSocket = NULL;

			pDownOutput->AddOutBox(strMsg + _T("\r\n"));
			AfxMessageBox(strMsg, MB_ICONWARNING);
		}
	}

	if (rdata != NULL) delete[] rdata;
	if (Nrdata != NULL) delete[] Nrdata;
	if (wdata != NULL) delete[] wdata;
	if (Nwdata != NULL) delete[] Nwdata;
}


void CDownDownOption673::OnEnUpdateEditMacaddress1() { OnEnUpdateEditMacaddress(0); }
void CDownDownOption673::OnEnUpdateEditMacaddress2() { OnEnUpdateEditMacaddress(1); }
void CDownDownOption673::OnEnUpdateEditMacaddress3() { OnEnUpdateEditMacaddress(2); }
void CDownDownOption673::OnEnUpdateEditMacaddress4() { OnEnUpdateEditMacaddress(3); }
void CDownDownOption673::OnEnUpdateEditMacaddress5() { OnEnUpdateEditMacaddress(4); }
void CDownDownOption673::OnEnUpdateEditMacaddress6() { OnEnUpdateEditMacaddress(5); }
void CDownDownOption673::OnEnUpdateEditMacaddress(int iNum)
{
	if (m_bOnChangeEditMacaddress) return;

	int nCur;
	BOOL bEdit = FALSE;

	CString str = _T("");
	CString strEdit = _T("");
	m_Edit_MacAddress[iNum].GetWindowText(str);
	m_Edit_MacAddress[iNum].GetSel(nCur, nCur);

	for (int i = 0; i < str.GetLength(); i++)
	{
		if ((str.GetAt(i) >= _T('0') && str.GetAt(i) <= _T('9')) |
			(str.GetAt(i) >= _T('A') && str.GetAt(i) <= _T('F'))) {
			strEdit = strEdit + str.GetAt(i);
		}
		else if (str.GetAt(i) >= _T('a') && str.GetAt(i) <= _T('f')) {
			strEdit = strEdit + ((CString)str.GetAt(i)).MakeUpper();
			m_Edit_MacAddress[iNum].SetModify(TRUE);
			bEdit = TRUE;
		}
		else
		{
			m_Edit_MacAddress[iNum].SetModify(TRUE);
			bEdit = TRUE;
			nCur--;
		}
	}

	if (bEdit) {
		if (m_Edit_MacAddress[iNum].GetModify())
		{
			m_bOnChangeEditMacaddress = TRUE;
			m_Edit_MacAddress[iNum].SetWindowText(strEdit);
			m_bOnChangeEditMacaddress = FALSE;
			m_Edit_MacAddress[iNum].SetModify(FALSE);
			m_Edit_MacAddress[iNum].SetSel(nCur, nCur);
			str = strEdit;
		}
	}
	
	if (str == _T("")) m_byMacAddress[iNum] = 0;
	else if (CheckHex(str))	m_byMacAddress[iNum] = HexToDec(str);
	else					m_byMacAddress[iNum] = 0;
}

void CDownDownOption673::OnEnUpdateEditBootaddress()
{
	CString str = _T("");
	m_Edit_BootAddress.GetWindowTextW(str);

	m_uiBootAddress = HexToDec(str);
}


void CDownDownOption673::OnEnChangeEditMacaddress1() { OnEnChangeEditMacaddress(0); }
void CDownDownOption673::OnEnChangeEditMacaddress2() { OnEnChangeEditMacaddress(1); }
void CDownDownOption673::OnEnChangeEditMacaddress3() { OnEnChangeEditMacaddress(2); }
void CDownDownOption673::OnEnChangeEditMacaddress4() { OnEnChangeEditMacaddress(3); }
void CDownDownOption673::OnEnChangeEditMacaddress5() { OnEnChangeEditMacaddress(4); }
void CDownDownOption673::OnEnChangeEditMacaddress6() { OnEnChangeEditMacaddress(5); }
void CDownDownOption673::OnEnChangeEditMacaddress(int iNum)
{
	if (m_bOnChangeEditMacaddress) return;

	CString str = _T("");
	m_Edit_MacAddress[iNum].GetWindowTextW(str);

	if (str.GetLength() >= 2) {
		if (iNum == 0) { m_Edit_MacAddress[1].SetFocus(); m_Edit_MacAddress[1].SetSel(0, -1, TRUE); }
		else if (iNum == 1) { m_Edit_MacAddress[2].SetFocus(); m_Edit_MacAddress[2].SetSel(0, -1, TRUE); }
		else if (iNum == 2) { m_Edit_MacAddress[3].SetFocus(); m_Edit_MacAddress[3].SetSel(0, -1, TRUE); }
		else if (iNum == 3) { m_Edit_MacAddress[4].SetFocus(); m_Edit_MacAddress[4].SetSel(0, -1, TRUE); }
		else if (iNum == 4) { m_Edit_MacAddress[5].SetFocus(); m_Edit_MacAddress[5].SetSel(0, -1, TRUE); }
	}
}

// ====================================================================================================
// CDownDownOption673::SetDeviceSize
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CDownDownOption673::SetDeviceSize(BYTE byDeviceSize)
{
	CString strDeviceSize = _T("");
	m_byDeviceSize = byDeviceSize;
	strDeviceSize.Format(_T("%d"), byDeviceSize);
	m_Edit_FlashSize.SetWindowTextW(strDeviceSize);
}

// ====================================================================================================
// CDownDownOption673::SetUserAddress
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CDownDownOption673::SetUserAddress(UINT32 uiUserAddress)
{
	CString strUserAddress = _T("");
	m_uiUserAddress = uiUserAddress;
	strUserAddress.Format(_T("0x%X"), uiUserAddress);
	m_Edit_UserAddress.SetWindowTextW(strUserAddress);
}

// ====================================================================================================
// CDownDownOption673::uiBootAddress
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CDownDownOption673::SetBootAddress(UINT32 uiBootAddress)
{
	CString strBootAddress = _T("");
	m_uiBootAddress = uiBootAddress;
	strBootAddress.Format(_T("0x%X"), uiBootAddress);
	m_Edit_BootAddress.SetWindowTextW(strBootAddress);
}

// ====================================================================================================
// CDownDownOption673::SetMacAddress
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CDownDownOption673::SetMacAddress(BYTE by1, BYTE by2, BYTE by3, BYTE by4, BYTE by5, BYTE by6)
{
	CString str = _T("");

	m_byMacAddress[0] = by1;
	m_byMacAddress[1] = by2;
	m_byMacAddress[2] = by3;
	m_byMacAddress[3] = by4;
	m_byMacAddress[4] = by5;
	m_byMacAddress[5] = by6;

	for (int i = 0; i < 6; i++) {
		str.Format(_T("%02X"), m_byMacAddress[i]);
		m_Edit_MacAddress[i].SetWindowTextW(str);
	}
}