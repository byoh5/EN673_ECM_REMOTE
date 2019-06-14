#include "stdafx.h"

// ====================================================================================================
// DefaultWindowMessage
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
BOOL DefaultWindowMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_ESCAPE:
		case VK_RETURN:
			return TRUE;
		}
	}
	return FALSE;
}


// ====================================================================================================
// GetNowPath
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
CString GetNowPath()
{
	TCHAR szNowPath[MAX_PATH];
	CString strNowPath = _T("");
	GetModuleFileName(NULL, szNowPath, MAX_PATH);
	PathRemoveFileSpec(szNowPath);

	strNowPath = CString(szNowPath);
	return strNowPath;
}

// ====================================================================================================
// RelativeToAbsolute
// ----------------------------------------------------------------------------------------------------
// 상대경로 -> 절대경로
// ====================================================================================================
CString	RelativeToAbsolute(CString strRePath, CString strNowPath)
{
	// strRePath - 상대 & 절대경로 (앞에있는 \만 제외시킨 경로)
	if (strRePath.Left(1) == _T("\\")) strRePath.Right(strRePath.GetLength() - 1);
	// strNowPath - 현재 디렉토리 (뒤에있는 \만 제외시킨 경로)
	if (strNowPath.Right(1) == _T("\\")) strNowPath.Left(strRePath.GetLength() - 1);

	int n = 0;
	CString str = _T("");

	// 상위 폴더
	n = strRePath.Find(_T("../"));
	if (n == -1) n = strRePath.Find(_T("..\\"));

	if (n != -1)
	{
		while (n != -1)
		{
			strRePath = strRePath.Right(strRePath.GetLength() - 3); // ..\\ 뺌
			strNowPath = strNowPath.Left(strNowPath.ReverseFind('\\'));
			if (strRePath == _T("") && strNowPath == _T("")) return _T("");

			n = strRePath.Find(_T("../"));
			if (n == -1) n = strRePath.Find(_T("..\\"));
		}

		strRePath.Replace('/', '\\');

		str = strNowPath + _T("\\") + strRePath;
		return str;
	}

	// 현재 폴더
	n = strRePath.Find(_T("./"));
	if (n == -1) n = strRePath.Find(_T(".\\"));

	if (n != -1)
	{
		strRePath = strRePath.Right(strRePath.GetLength() - 2);
		str = strNowPath + _T("\\") + strRePath;
		return str;
	}

	// 최상위 폴더
	n = strRePath.Find(_T("/"));
	CString strRoot = strNowPath.Left(strNowPath.Find(_T("\\")) - 1);
	if (n == 1)
	{
		str = strRoot + _T("\\") + strRePath;
		return str;
	}
	else // 아무것도 아님
	{
		str = strNowPath + _T("\\") + strRePath;
		return str;
	}
}

// ====================================================================================================
// AbsoluteToRelative
// ----------------------------------------------------------------------------------------------------
// 절대경로 -> 상대경로
// ====================================================================================================
CString	AbsoluteToRelative(CString strAbPath, CString strNowPath)
{
	int i = 0;
	int j = 0;
	int nCnt = 0;
	CString str = _T("");

	strAbPath.Replace('\\', '/');

	if (strAbPath.Left(1) != strNowPath.Left(1))
	{
		return strAbPath;
	}

	i = 0;
	while (1)
	{
		i = strNowPath.Find('\\', i);
		if (i == -1)	break;
		i++;
		nCnt++;
	}

	CString Ab = _T("");
	CString Now = _T("");
	int nAb = 0;
	int nNow = 0;

	for (i = 0; i <= nCnt; i++)
	{
		nAb = strAbPath.Find('/');
		nNow = strNowPath.Find('\\');

		Ab = strAbPath.Mid(0, nAb);
		if (nNow == -1) Now = strNowPath;
		else		 Now = strNowPath.Mid(0, nNow);

		if (Ab != Now)
		{
			nCnt = (nCnt + 1) - i;
			for (j = 0; j < nCnt; j++) str += _T("../");
			str = str + strAbPath;
			return str;
		}

		strAbPath = strAbPath.Right(strAbPath.GetLength() - strAbPath.Find('/') - 1);
		if (nNow == -1)	strNowPath = _T("");
		else			strNowPath = strNowPath.Right(strNowPath.GetLength() - strNowPath.Find('\\') - 1);
	}

	str = _T("./") + strAbPath;
	return str;
}

// ====================================================================================================
// HexToDec
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
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

// ====================================================================================================
// HexToBin
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
CString HexToBin(const CString& sHex)
{
	// 글자 수를 맞추려면 하기 전에 추가
	// int iLen =  strTx.GetLength();
	// if (iLen < 8) {
	// 	for (i = 0 ; i < 8 - iLen ; i++)
	// 	{
	//	 	strTx = _T("0") + strTx;
	//	}
	//} 
	int i = 0;
	int j = 0;
	int iLen = sHex.GetLength();
	CString	sBin = _T("");

	for (i = 0; i < iLen; i++)
	{
		j = HexToDec(sHex.Mid(i, 1));

		switch (j) // 나중에 정리...;;;
		{
		case 0:		sBin = sBin + _T("0000"); break;
		case 1:		sBin = sBin + _T("0001"); break;
		case 2:		sBin = sBin + _T("0010"); break;
		case 3:		sBin = sBin + _T("0011"); break;
		case 4:		sBin = sBin + _T("0100"); break;
		case 5:		sBin = sBin + _T("0101"); break;
		case 6:		sBin = sBin + _T("0110"); break;
		case 7:		sBin = sBin + _T("0111"); break;
		case 8:		sBin = sBin + _T("1000"); break;
		case 9:		sBin = sBin + _T("1001"); break;
		case 10:	sBin = sBin + _T("1010"); break;
		case 11:	sBin = sBin + _T("1011"); break;
		case 12:	sBin = sBin + _T("1100"); break;
		case 13:	sBin = sBin + _T("1101"); break;
		case 14:	sBin = sBin + _T("1110"); break;
		case 15:	sBin = sBin + _T("1111"); break;
		}
	}

	return sBin;
}

// ====================================================================================================
// BinToDec
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
int BinToDec(const CString& sBin)
{
	int	i = 0;
	int	j = 1;
	int	iDec = 0;

	for (i = sBin.GetLength() - 1; i >= 0; i--)
	{
		iDec += j * _ttoi(sBin.Mid(i, 1));
		j = j * 2;
	}

	return iDec;
}

// ====================================================================================================
// HexStringOut
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
CString HexStringOut(unsigned int i)
{
	char cBuff[40];

	_itoa_s(i, cBuff, 16);
	return (CString)cBuff;
}

// ====================================================================================================
// CheckHex
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
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

// ====================================================================================================
// CheckDec
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
BOOL CheckDec(const CString& str)
{
	int i = 0;
	int iLen = str.GetLength();
	char ch = 0;

	if (iLen == 0) return FALSE;

	for (i = 0; i < iLen; i++)
	{
		ch = (char)str.GetAt(i);
		if (!(ch >= '0' && ch <= '9'))
		{
			if (i == 0 && ch == '-') continue;
			return FALSE;
		}
	}

	return TRUE;
}


// ====================================================================================================
// ShowOpenFileDlg
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
BOOL ShowOpenFileDlg(CString* strPath, CString strDefExt, CString strFilter, CWnd* pWnd)
{
	int iDlgReturn = 0;
	_TCHAR szNowPath[MAX_PATH];

	// ----------------------------------------------------------------------------------------------------
	// 다이얼로그
	// 현재 작업 경로 얻기
	::GetCurrentDirectory(MAX_PATH, szNowPath);

	// 파일 다이얼로그 경로 설정
	CFileFind ffind;
	if (ffind.FindFile(*strPath))
		ffind.Close();
	else
		*strPath = _T("");

	// Open 다이얼로그
	CFileDialog FileDlg(TRUE, strDefExt, *strPath, OFN_HIDEREADONLY, strFilter, pWnd);
	iDlgReturn = FileDlg.DoModal();

	// 현재 작업 경로 재설정
	::SetCurrentDirectory(szNowPath);

	// ----------------------------------------------------------------------------------------------------
	// Return
	if (iDlgReturn != IDOK)
	{
		*strPath = _T("");
		return FALSE;
	}
	else
	{
		*strPath = FileDlg.GetPathName();
		return TRUE;
	}
}


// ====================================================================================================
// ShowSaveFileDlg
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
BOOL ShowSaveFileDlg(CString *strPath, CString strDefExt, CString strFilter, CWnd* pWnd)
{
	int iDlgReturn = 0;
	_TCHAR szNowPath[MAX_PATH];

	// ----------------------------------------------------------------------------------------------------
	// 다이얼로그
	// 현재 작업 경로 얻기
	::GetCurrentDirectory(MAX_PATH, szNowPath);

	// 파일 다이얼로그 경로 설정
	CFileFind ffind;
	if (ffind.FindFile(*strPath))
		ffind.Close();
	else
		*strPath = _T("");

	// Save 다이얼로그
	CFileDialog FileDlg(FALSE, strDefExt, *strPath, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strFilter, pWnd);
	iDlgReturn = FileDlg.DoModal();

	// 현재 작업 경로 재설정
	::SetCurrentDirectory(szNowPath);

	// ----------------------------------------------------------------------------------------------------
	// Return
	if (iDlgReturn != IDOK)
	{
		*strPath = _T("");
		return FALSE;
	}
	else
	{
		*strPath = FileDlg.GetPathName();
		return TRUE;
	}
}


UINT32 jtag_htonl(UINT32 n)
{
	return ((n & 0xff) << 24) |
		((n & 0xff00) << 8) |
		((n & 0xff0000UL) >> 8) |
		((n & 0xff000000UL) >> 24);
}


void resetpos(UINT32 cpu) {
	if (cpu == 4) {
		now_pos_CPU0 = jtag_print_base_CPU0;
		last_pos_CPU0 = jtag_print_base_CPU0;
	}
	if (cpu == 5) {
		now_pos_CPU1 = jtag_print_base_CPU1;
		last_pos_CPU1 = jtag_print_base_CPU1;
	}
}

// ====================================================================================================
// CJTAG::JTAGPrint
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
UINT32 JTAGPrint_define(UINT8* pbuf, UINT32 cpu){

	m_csJTAGPrint.Lock(); // Critical Section Lock

	UINT32 uiReturn = 0xFFFFFFFF;

	UINT fir_size = 0;
	UINT sec_size = 0;
	UINT32 size = 0;
	INT32 check = 0;
	UINT32 err = 0;

	UINT32* now_pos = NULL;
	UINT32* last_pos = NULL;
	UINT32* jtag_print_base = NULL;
	//UINT32* jtag_print_point = NULL;
	UINT32 jtag_print_point_addr = NULL;

	if (cpu == 4) {
		now_pos = &now_pos_CPU0;
		last_pos = &last_pos_CPU0;
		jtag_print_base = &jtag_print_base_CPU0;
		//jtag_print_point = &jtag_print_point_CPU0;
		jtag_print_point_addr = JTAG_PRINT0_POINT;
	}
	else if (cpu == 5) {
		now_pos = &now_pos_CPU1;
		last_pos = &last_pos_CPU1;
		jtag_print_base = &jtag_print_base_CPU1;
		//jtag_print_point = &jtag_print_point_CPU1;
		jtag_print_point_addr = JTAG_PRINT1_POINT;
	}
	else {
		goto END;
	}

	// get size of jtag_print
	//if (err |= pJTAG->read32(jtag_print_point_addr, now_pos, 1, JTAG_COMMON_MODULE_IDX))	goto END;
	//if (err |= getDataFromRemote(ConnectSocket, jtag_print_point_addr, 4, JTAG_COMMON_MODULE_IDX, now_pos))	goto END;
	if (-1 == getDataFromRemote(ConnectSocket, jtag_print_point_addr, 4, JTAG_COMMON_MODULE_IDX, now_pos))	goto END;
	*now_pos = jtag_htonl((UINT32)(*now_pos));
	if ((*jtag_print_base <= *now_pos) & (*now_pos < (*jtag_print_base + jtag_print_size))){

		if (*now_pos == *last_pos) { uiReturn = 0; goto END; }

		check = *now_pos - *last_pos;
		if (check > 0)
		{
			size = *now_pos - *last_pos;
			//if (err |= ReadJTAGPrintData(*last_pos, size, pbuf, cpu)) goto END;
			if (-1 == ReadJTAGPrintData(*last_pos, size, pbuf, cpu)) goto END;
			*last_pos += size;
		}
		else if (check < 0){
			fir_size = (*jtag_print_base + jtag_print_size) - *last_pos;
			//if (err |= ReadJTAGPrintData(*last_pos, fir_size, pbuf, cpu)) goto END;
			if (-1 == ReadJTAGPrintData(*last_pos, fir_size, pbuf, cpu)) goto END;

			sec_size = *now_pos - *jtag_print_base;
			//if (err |= ReadJTAGPrintData(*jtag_print_base, sec_size, pbuf + fir_size, cpu)) goto END;
			if (-1 == ReadJTAGPrintData(*jtag_print_base, sec_size, pbuf + fir_size, cpu)) goto END;
			*last_pos = *now_pos;
			size = fir_size + sec_size;
		}
		else {
			uiReturn = 0;
			goto END;
		}
	}

	uiReturn = size;

END:
	m_csJTAGPrint.Unlock(); // Critical Section Lock

	if (err != 0)
	{
		ConnectSocket = NULL;
		pJTAGPrintCPU0Dlg->m_bRunJTAGPrint = TRUE;
		pJTAGPrintCPU0Dlg->OnBnClickedButtonJtagprintcpu0Start();
	}

	return size;
}


// ====================================================================================================
// CJTAG::ReadJTAGPrintData
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
UINT32 ReadJTAGPrintData(UINT32 last_pos, UINT32 size, UINT8* pbuf, UINT32 cpu)
{
	UINT32 err = 0;
	UINT8 * memblock = NULL;
	UINT8 * memblock_t = NULL;
	UINT8 * memblock_new_pos = NULL;
	UINT32* memblock32 = NULL;
	UINT32* memblock32_t = NULL;
	UINT32 retry = 0, left = 0;
	UINT32 i = 0;
	UINT32 origsize = size;
	UINT32 offset = (last_pos & 0x03);

	UINT32 re_last_pos = (last_pos >> 2) << 2;

	size += (offset + 4);
	memblock = (UINT8*)malloc(size + 8);
	memblock_t = (UINT8*)malloc(size + 8);
	retry = (size) / (MR_READBUFFER);
	left = (size) % (MR_READBUFFER);

	for (i = 0; i < retry; i++){
		//if (err |= pJTAG->read32(last_pos + (MR_READBUFFER * i), (UINT32*)(memblock + (MR_READBUFFER * i)), (MR_READBUFFER / 4), JTAG_COMMON_MODULE_IDX)) {
		if ((err = getDataFromRemote(ConnectSocket, re_last_pos + (MR_READBUFFER * i), MR_READBUFFER, JTAG_COMMON_MODULE_IDX, (UINT32*)(memblock + (MR_READBUFFER * i)))) == -1) {
			goto END;
		}
	}
	if (left) {
		//if (err |= pJTAG->read32(last_pos + (MR_READBUFFER * i), (UINT32*)(memblock + (MR_READBUFFER * i)), (left / 4) + 1, JTAG_COMMON_MODULE_IDX)) {
		if ((err = getDataFromRemote(ConnectSocket, re_last_pos + (MR_READBUFFER * i), left + 1, JTAG_COMMON_MODULE_IDX, (UINT32*)(memblock + (MR_READBUFFER * i)))) == -1) {
			goto END;
		}
	}

	memblock32 = (UINT32*)memblock;
	memblock32_t = (UINT32*)memblock_t;
	for (i = 0; i < (size / 4) + 1; i++){
		*(memblock32_t + i) = *(memblock32 + i);
	}
	memblock_t = (UINT8*)memblock32_t;
	memblock_new_pos = memblock_t + offset;
	memblock_new_pos[origsize] = 0;

	if ((pJTAGPrintCPU0Dlg->m_bRunJTAGPrint) && (cpu == 4)) {
		pJTAGPrintCPU0Dlg->DispString(memblock_new_pos);
	}

	/*
	if ((pJTAGPrintCPU1Dlg->m_bRunJTAGPrint) && (cpu == 5)) {
		pJTAGPrintCPU1Dlg->DispString(memblock_new_pos);
	}
	*/

END:
	if (memblock) free(memblock);
	if (memblock_t) free(memblock_t);

	return err;
}


void AutoSave()
{
	CString data = _T("");
	CString strPath = _T("");
	strPath = ReadIni(SEC_SETTING, KEY_PRINTSAVEPATH, DEF_PRINTSAVEPATH);

	// Ini 파일에 Path가 없는경우
	if (strPath == _T(""))
	{
		// Get 'My Document'
		TCHAR szPath[MAX_PATH];
		SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, 0, szPath);

		// Create ecm folder
		CString strDirectory = _T("");
		strDirectory.Format(_T("%s\\ecm_retome"), szPath);
		CreateDirectory(strDirectory, NULL);

		// Create Analyze folder
		strDirectory.Format(_T("%s\\ecm_retome\\jtagprint"), szPath);
		CreateDirectory(strDirectory, NULL);

		strPath = strDirectory;
	}

	// 디렉토리 유무 확인
	if (GetFileAttributes(strPath) == -1)
	{
		CreateDirectory(strPath, NULL);
	}

	strPath.Format(_T("%s\\%s"), strPath, autosave_filename);

	// Save
	// Create File
	CStdioFile fileTxt;
	if (fileTxt.Open(strPath, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite))
	{
		fileTxt.SeekToEnd();
		pJTAGPrintCPU0Dlg->m_Edit_String.GetWindowTextW(data);
		for (int i = 0; i < pJTAGPrintCPU0Dlg->m_iMaxLine*REMOVE_RATE; i++) {
			data.Delete(data.GetLength() - 1, 1);
			int size = data.GetLength();
			int n_flag = data.ReverseFind('\n');
			data.Delete(n_flag + 1, size - n_flag - 1);
		}
		fileTxt.WriteString(data);
	}
	fileTxt.Close();
}


void AutoSave_Re()
{
	CString data = _T("");
	CString strPath = _T("");
	strPath = ReadIni(SEC_SETTING, KEY_PRINTSAVEPATH, DEF_PRINTSAVEPATH);

	// Ini 파일에 Path가 없는경우
	if (strPath == _T(""))
	{
		// Get 'My Document'
		TCHAR szPath[MAX_PATH];
		SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, 0, szPath);

		// Create ecm folder
		CString strDirectory = _T("");
		strDirectory.Format(_T("%s\\ecm_retome"), szPath);
		CreateDirectory(strDirectory, NULL);

		// Create Analyze folder
		strDirectory.Format(_T("%s\\ecm_retome\\jtagprint"), szPath);
		CreateDirectory(strDirectory, NULL);

		strPath = strDirectory;
	}

	// 디렉토리 유무 확인
	if (GetFileAttributes(strPath) == -1)
	{
		CreateDirectory(strPath, NULL);
	}

	strPath.Format(_T("%s\\%s"), strPath, autosave_filename);

	// Save
	// Create File
	CStdioFile fileTxt;
	if (fileTxt.Open(strPath, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite))
	{
		fileTxt.SeekToEnd();
		pJTAGPrintCPU0Dlg->m_Edit_String.GetWindowTextW(data);
		fileTxt.WriteString(data);
	}
	fileTxt.Close();
}



// ====================================================================================================
// ReadIni
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
int ReadIni(CString strSector, CString strKey, int iDefault)
{
	return ::GetPrivateProfileIntW(strSector, strKey, iDefault, INIFILE);
}

CString ReadIni(CString strSector, CString strKey, CString strDefault)
{
	TCHAR tCh[MAX_PATH];
	CString strResult = _T("");

	::GetPrivateProfileStringW(strSector, strKey, strDefault, tCh, MAX_PATH, INIFILE);

	strResult = (CString)tCh;

	return strResult;
}

// ====================================================================================================
// WriteIni
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void WriteIni(CString strSector, CString strKey, CString strData)
{
	::WritePrivateProfileStringW(strSector, strKey, strData, INIFILE);
}

void WriteIni(CString strSector, CString strKey, int iData)
{
	CString strData = _T("");
	strData.Format(_T("%d"), iData);

	::WritePrivateProfileStringW(strSector, strKey, strData, INIFILE);
}

void Wait(DWORD deMillisecond)
{
	MSG msg;
	DWORD dwStart;
	dwStart = GetTickCount();

	while (GetTickCount() - dwStart < deMillisecond)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

void ProcessWindowMessage()
{
	MSG msg;

	while (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
	{
		SendMessage(msg.hwnd, msg.message, msg.wParam, msg.lParam);
	}
}