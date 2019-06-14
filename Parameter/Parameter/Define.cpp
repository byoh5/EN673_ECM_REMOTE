#include "stdafx.h"

BOOL RxCheck_flag = TRUE;

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


// ====================================================================================================
// copyClipboard
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void copyClipboard(const CString& str)
{

	int iSize = (str.GetLength() + 1) * sizeof(TCHAR);
	HGLOBAL	hGlobal = GlobalAlloc(GHND, iSize);
	if (!hGlobal) return;

	TCHAR* lptext = static_cast<TCHAR*>(GlobalLock(hGlobal));
	memcpy(lptext, str, iSize);
	GlobalUnlock(hGlobal);

	// 클립보드 핸들을 연다.
	if (::OpenClipboard(AfxGetMainWnd()->GetSafeHwnd()))
	{
		/*
		BYTE* hData = (BYTE*)::GlobalAlloc( GMEM_FIXED, str.GetLength() * 2 );

		for (int i = 0; i <= str.GetLength(); i++)
		{
		*( hData + i ) = str.GetAt(i);
		}
		*/
		// 클립보드의 포맷, TEXT 포맷이 유효한지 판단
		if (::IsClipboardFormatAvailable(CF_UNICODETEXT))
		{
			// 클립보드의 내용을 가져온다  
			HANDLE hd = ::GetClipboardData(CF_UNICODETEXT);

			// 비었는지 확인한후 처리한다  
			if (hd != NULL)
			{
				// 비운다  
				::EmptyClipboard();
			}
		}
		else
		{
			// 클립보드를 비운다  
			::EmptyClipboard();
		}

		/*
		// 클립보드에 데이터를 쓴다
		if ( !SetClipboardData( CF_UNICODETEXT, hData ))
		{
		AfxMessageBox(_T("Unable to write Clipboard Data"));
		}
		*/

#ifdef UNICODE
		SetClipboardData(CF_UNICODETEXT, hGlobal);
#else
		SetClipboardData(CF_TEXT, hGlobal);
#endif
		::CloseClipboard();
		//::GlobalUnlock( hData );
	}
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

UINT32 jtag_htonl(UINT32 n)
{
	return ((n & 0xff) << 24) |
		((n & 0xff00) << 8) |
		((n & 0xff0000UL) >> 8) |
		((n & 0xff000000UL) >> 24);
}


int ReadParameter(DWORD dwAddr, int iByte)
{
	BYTE SendData[5] = { 0, };

	int state;

	BYTE* flag = NULL;
	BYTE* data = NULL;
	DWORD dwData = 0;

	SendData[0] = PC_STX;
	SendData[1] = PC_CMD_PARR;

	SendData[4] = PC_ETX;

	for (int i = 0; i < iByte; i++)
	{
		DWORD dwTempData = 0;

		// Addr
		SendData[2] = (BYTE)(((dwAddr + i) & 0xff00) >> 8);
		SendData[3] = (BYTE)((dwAddr + i) & 0x00ff);

		state = WriteComm(SendData, 5);

		int iCnt = 0;
		int iiCnt = 0;
		RxCheck_flag = TRUE;

		do{
			if (pParameterDlg->m_bStopAll) return 0; // Stop Read All
			//Sleep(10);
			//ProcessWindowMessage();
			Wait(10);
			state = getDataFromRemote(ConnectSocket, tx_addr, 4, WBCOM, &flag);
			if (state < 0 | iCnt > RETRY)
			{
				RxCheck_flag = FALSE;
				return -1;
			}
			if ((((UINT32)flag & 0X0000ffff) == 0xd002) | iiCnt == RETRY)
			{
				iiCnt = 0;
				iCnt++;
				state = WriteComm(SendData, 5);
			}
			iiCnt++;
		} while ((ntohl((UINT32)flag) & 0x000ffff) != (dwAddr + i));

		state = getDataFromRemote(ConnectSocket, tx_addr + (1 << 2), 4, WBCOM, &data);

		if (state < 0)	return -1;

		dwData = (UINT32)data & 0x000000ff;
		
		g_iRxAddress = dwAddr + i;

		// Display Rx
		pParameterDlg->DispRxPar(dwAddr + i, dwData);

		// Check Feedback
		if (pParameterDlg->m_Chk_FeedBackRead.GetCheck())
			pParameterDlg->DispTxPar(dwAddr + i, dwData);
	}

	return 0;
}


int WriteParameter(DWORD dwAddr, int iByte, DWORD dwData)
{
	BYTE SendData[6] = { 0, };

	BYTE * flag = NULL;

	int state;

	SendData[0] = PC_STX;
	SendData[1] = PC_CMD_PARW;

	SendData[5] = PC_ETX;

	for (int i = 0; i < iByte; i++)
	{
		SendData[2] = (BYTE)(((dwAddr + i) & 0xff00) >> 8);
		SendData[3] = (BYTE)((dwAddr + i) & 0x00ff);
		SendData[4] = (BYTE)((dwData >> (i * 8)) & 0x00ff);

		state = WriteComm(SendData, 6);

		Sleep(1000);
		//g_iRxAddress = dwAddr + i;

		int iCnt = 0;
		int iiCnt = 0;
		RxCheck_flag = TRUE;
		do{
			if (pParameterDlg->m_bStopAll) return 0;		// Stop
			//Sleep(10);
			//ProcessWindowMessage();
			Wait(10);
			state = getDataFromRemote(ConnectSocket, tx_addr, 4, WBCOM, &flag);
			if (state < 0 | iCnt > RETRY)
			{
				RxCheck_flag = FALSE;
				return -1;
			}
			if (((UINT32)flag & 0X0000ffff) == 0xd002)
			{
				iiCnt = 0;
				iCnt++;
				state = WriteComm(SendData, 6);
			}
			iiCnt++;
		} while ((ntohl((UINT32)flag) & 0x000ffff) != (dwAddr + i));


		g_iRxAddress = dwAddr;

		// Check Feedback
		if (pParameterDlg->m_Chk_FeedBackWrite.GetCheck())
			pParameterDlg->DispRxPar(dwAddr, dwData);
	}
	return 0;
}

BOOL TxParameterKey()
{
	pParameterDlg->m_bParameterKey = -1;

	// Send
#if 1
	DWORD dwKey = HexToDec(pParameterDlg->m_strKey);
#else
	DWORD dwKey = HexToDec(ReadIni(SEC_SETTING, KEY_PARAMETERKEY, DEF_PARAMETERKEY));
#endif

	BYTE SendData[7] = { 0, };

	int state;

	SendData[0] = PC_STX;
	SendData[1] = PC_CMD_PARK;
	SendData[2] = (BYTE)(dwKey >> 24);
	SendData[3] = (BYTE)(dwKey >> 16);
	SendData[4] = (BYTE)(dwKey >> 8);
	SendData[5] = (BYTE)(dwKey);
	SendData[6] = PC_ETX;

	state = WriteComm(SendData, 7);
	if (state < 0)	return FALSE;

	// Check
	int iCnt = 0;
	int iiCnt = 0;
	BYTE* flag;
	do{
		//ProcessWindowMessage();
		state = getDataFromRemote(ConnectSocket, tx_addr, 4, WBCOM, &flag);
		if (state == -1)
		{
			pParameterDlg->m_Btn_Connect.SetIcon(IDI_DISCONNECT, NULL);
			pParameterDlg->m_bParameterKey = 0;
			return FALSE;
		}
		if (iCnt > RETRY)
		{
			pParameterDlg->m_bParameterKey = 0;
			return FALSE;
		}
		if ((((UINT32)flag & 0X0000ffff) == 0xd002) | iiCnt == RETRY)
		{
			iiCnt = 0;
			iCnt++;
			state = WriteComm(SendData, 7);
		}
		iiCnt++;
	} while (jtag_htonl((UINT32)flag) != 0x02680103);

	pParameterDlg->m_bParameterKey = 1;
	return TRUE;

}

int	JtagUartAck()
{
	BYTE * temp;

	int state;

	temp = (BYTE *)(ntohl(JTAG_UART_NOTIFY));
	state = setDataFromRemote(ConnectSocket, JTAG_SHELL_NOTIFY_ADDR, 4, WBCOM, &temp);
	if (state < 0)	return -1;

	temp = (BYTE *)(ntohl(JTAG_CPU_IRQ0));
	state = setDataFromRemote(ConnectSocket, JTAG_CPU_IRQ_ADDR, 4, WBCOM, &temp);
	if (state < 0)	return -1;

	return 0;
}

int WriteComm(BYTE *pBuff, int nToWrite)
{
	BYTE SendData[12] = { 0, };
	UINT32 n_temp[3] = { 0, };

	int i = 0;
	int j = 0;
	int state;

	// Type
	SendData[0] = tx_typr;

	// Size
	SendData[1] = (BYTE)(nToWrite + 1);

	for (i = 0; i < nToWrite; i++)
	{
		SendData[i + 2] = *(pBuff + i);
	}

	for (i = 0; i < (nToWrite + 2) / 4 + 1; i++)
	{
		//ProcessWindowMessage();
		if (((nToWrite + 1) - (i * 4)) > 0)
		{
			for (j = 0; j < 4; j++)
			{
				n_temp[i] = n_temp[i] | (SendData[i * 4 + j] & 0xff) << (24 - (j * 8));
			}
		}
		else
		{
			for (j = 0; j < (nToWrite + 2) % 4; j++)
				n_temp[i] = n_temp[i] | (SendData[i * 4 + j] & 0xff) << (24 - (j * 8));
		}

		n_temp[i] = ntohl(n_temp[i]) & 0xffffffff;
	}

	//write32(addr, (UINT32*)n_temp, 3, WBCOM);
	state = setDataFromRemote(ConnectSocket, JTAG_UART_ADDR, nToWrite + 2, WBCOM, &n_temp);
	if (state < 0)	return -1;

	state = JtagUartAck();
	if (state < 0)	return -1;

	return 0;
}


// ====================================================================================================
// CUartProtocol::ReadEEPROMAll
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void ReadEEPROMAll()
{
	UINT i = 0;
	int j = 0;
	int iCnt = 0;
	int iByte = 0;
	int	iListCnt = pParameterDlg->m_List_Parameter.GetCount();
	DWORD dwAddr = 0;
	CString str = _T("");
	CString strAddr = _T("");
	CString strByte = _T("");
	HTREEITEM hItem = pParameterDlg->m_List_Parameter.GetFirstItem();
	HTREEITEM hLastItem = hItem;

	g_iRxAddress = -1;

	// Set ProgressCtrl
	pParameterDlg->m_Progress_Loading.ShowWindow(SW_SHOW);
	pParameterDlg->m_Progress_Loading.SetRange(0, 5 + iListCnt);
	pParameterDlg->m_Progress_Loading.SetPos(0);

	// 1. EEPROM Read
	ReadEEP();

	//Sleep(10);
	Wait(10);

	pParameterDlg->m_bSuccessEEPRead = TRUE;


	/*
	iCnt = 0;
	pParameterDlg->m_bSuccessEEPRead = FALSE;

	while (!pParameterDlg->m_bSuccessEEPRead) // 5초 대기
	{
		Sleep(100);
		pParameterDlg->m_bSuccessEEPRead = TRUE;
		if (pParameterDlg->m_bSuccessEEPRead)
			break;
		else
			if (iCnt == 50) { // 5초
				AfxMessageBox(_T("Fail EEPROM Read"));
				goto END;
			}
		iCnt++;

		if ((iCnt % 10) == 0)
		{
			pParameterDlg->m_Progress_Loading.SetStep(1);
			pParameterDlg->m_Progress_Loading.StepIt();
		}
	}
	*/

	pParameterDlg->m_Progress_Loading.SetPos(5);
	pParameterDlg->m_Progress_Loading.StepIt();

	// 2. Parameter Read All
	for (i = 0; i < pParameterDlg->m_List_Parameter.GetCount(); i++)
	{
		//ProcessWindowMessage();
		if (pParameterDlg->m_bStopAll) return;			 // Stop ROM Read All
		pParameterDlg->m_Progress_Loading.SetStep(1);
		pParameterDlg->m_Progress_Loading.StepIt();

		if (hItem == NULL)
		{
			pParameterDlg->m_List_Parameter.SelectItem(hLastItem);
			pParameterDlg->m_List_Parameter.EnsureVisible(hLastItem);
			goto END;
		}

		hLastItem = hItem;

		pParameterDlg->m_List_Parameter.SelectItem(hItem);
		strAddr = pParameterDlg->m_List_Parameter.GetItemText(hItem, TC_PAR_ADDR);
		strByte = pParameterDlg->m_List_Parameter.GetItemText(hItem, TC_PAR_BYTE);

		// 검사
		if (!CheckHex(strAddr) || !CheckDec(strByte))
		{
			hItem = pParameterDlg->m_List_Parameter.GetNextItem(hItem);
			continue;
		}
		iByte = _ttoi(strByte);
		if (!INMIDDLE(iByte, 1, 4))
		{
			hItem = pParameterDlg->m_List_Parameter.GetNextItem(hItem);
			continue;
		}
		dwAddr = HexToDec(strAddr);

		pParameterDlg->m_List_Parameter.EnsureVisible(hItem);

		ReadParameter(dwAddr, iByte);

		hItem = pParameterDlg->m_List_Parameter.GetNextItem(hItem);
	}

	// 3. Select Item
	pParameterDlg->m_List_Parameter.SelectItem(hLastItem);
	pParameterDlg->m_List_Parameter.EnsureVisible(hLastItem);

END:
	pParameterDlg->m_Progress_Loading.ShowWindow(SW_HIDE);
}

// ====================================================================================================
// void CUartProtocol::WriteEEPROMAll()
// ----------------------------------------------------------------------------------------------------
/*
- Parameter Control의 모든 값을 PARW command를 이용해서 한 번에 전송
(단, Write 중 실패하면 동작 종료)
- EEPW command 전송 후 약 5초동안 대기
- EEPR command가 오면 PARR command로 확인 후
- 값이 다른 경우 실패했음 -> 붉은색 글씨로 표시
- EEPW command를 보내면, F/W에서는 EEPR command를 통해서 ACK를 보내줌.

- 이 모든 과정을 Process Bar로 표현.
*/
// ====================================================================================================
void WriteEEPROMAll()
{
	int i = 0;
	int j = 0;
	int iCnt = 0;
	int	iByte = 0;
	int iMaxAddr = 0;
	DWORD dwAddr = 0;
	DWORD dwData = 0;
	int iListCnt = pParameterDlg->m_List_Parameter.GetCount();
	CString str = _T("");
	CString	strAddr = _T("");
	CString	strByte = _T("");
	CString	strTx = _T("");
	HTREEITEM hItem = pParameterDlg->m_List_Parameter.GetFirstItem();
	HTREEITEM hLastItem = NULL;

	g_iRxAddress = -1;

	pParameterDlg->m_bRunCmd = FALSE;

	pParameterDlg->m_Progress_Loading.ShowWindow(SW_SHOW);
	pParameterDlg->m_Progress_Loading.SetRange(0, (iListCnt * 3) + 3 + 10);
	pParameterDlg->m_Progress_Loading.SetPos(0);

	// 1. Parameter Write All
	for (i = 0; i < iListCnt; i++)
	{
		//ProcessWindowMessage();
		if (pParameterDlg->m_bStopAll) goto END;			// Stop ROM Write All
		pParameterDlg->m_Progress_Loading.SetStep(1);
		pParameterDlg->m_Progress_Loading.StepIt();

		if (hItem == NULL)
		{
			pParameterDlg->m_List_Parameter.SelectItem(hLastItem);
			pParameterDlg->m_List_Parameter.EnsureVisible(hLastItem);
			goto END;
		}

		hLastItem = hItem;
		pParameterDlg->m_List_Parameter.EnsureVisible(hItem);

		pParameterDlg->m_List_Parameter.SelectItem(hItem);
		strAddr = pParameterDlg->m_List_Parameter.GetItemText(hItem, TC_PAR_ADDR);
		strByte = pParameterDlg->m_List_Parameter.GetItemText(hItem, TC_PAR_BYTE);
		strTx = pParameterDlg->m_List_Parameter.GetItemText(hItem, TC_PAR_TX);

		// 검사
		if (!CheckHex(strAddr) || !CheckDec(strByte) || !CheckHex(strTx))
		{
			hItem = pParameterDlg->m_List_Parameter.GetNextItem(hItem);
			continue;
		}
		iByte = _ttoi(strByte);
		if (!INMIDDLE(iByte, 1, 4))
		{
			hItem = pParameterDlg->m_List_Parameter.GetNextItem(hItem);
			continue;
		}

		dwAddr = HexToDec(strAddr);
		dwData = HexToDec(strTx);

#if 0
		//for(j = 0; j < iByte; j++)
		for (j = iByte - 1; j >= 0; j--)
		{
			//pUART->WriteParameter(dwAddr + j, (BYTE)((dwData >> (j * 8)) & 0x00ff));

			iCnt = 0;
			while ((int)(dwAddr + j) > g_iRxAddress)
			{
				if (iCnt == 1000)
				{
					str.Format(_T("Fail Write Value (Address : %x)"), dwAddr + j);
					AfxMessageBox(str);
					pParameterDlg->m_List_Parameter.SelectItem(hItem);
					goto END;
				}
				Sleep(1);
				iCnt++;
			}
		}
#endif

		WriteParameter(dwAddr, iByte, dwData);

		hItem = pParameterDlg->m_List_Parameter.GetNextItem(hItem);
	}

	// 2. EEP Write (Read까지 해야되기 때문에... 약 10초 대기)
	WriteEEP();

	iCnt = 0;
	while (!pParameterDlg->m_bSuccessEEPWrite)
	{
		//Sleep(10);
		//ProcessWindowMessage();
		Wait(10);
		if (pParameterDlg->m_bSuccessEEPWrite)
			break;
		else {
			if (iCnt == 100) { // 10초
				AfxMessageBox(_T("Fail EEPROM Write"));
				goto END;
			}
		}
		iCnt++;

		if ((iCnt % 10) == 0)
		{
			pParameterDlg->m_Progress_Loading.SetStep(1);
			pParameterDlg->m_Progress_Loading.StepIt();
		}
	}

	pParameterDlg->m_Progress_Loading.SetPos(iListCnt + 10);
	pParameterDlg->m_Progress_Loading.StepIt();

	// 2.5 Get Max Addr
	hItem = pParameterDlg->m_List_Parameter.GetFirstItem();
	for (i = 0; i < pParameterDlg->m_List_Parameter.GetCount(); i++)
	{
		//ProcessWindowMessage();
		strAddr = pParameterDlg->m_List_Parameter.GetItemText(hItem, TC_PAR_ADDR);
		strByte = pParameterDlg->m_List_Parameter.GetItemText(hItem, TC_PAR_BYTE);

		if (!CheckHex(strAddr) || !CheckDec(strByte))
		{
			hItem = pParameterDlg->m_List_Parameter.GetNextSiblingItem(hItem);
			continue;
		}

		dwAddr = HexToDec(strAddr);
		iByte = _ttoi(strByte);

		if ((int)(dwAddr + iByte - 1) > iMaxAddr)
			iMaxAddr = dwAddr + iByte;

		hItem = pParameterDlg->m_List_Parameter.GetNextSiblingItem(hItem);
	}

	// 3. Parameter Read All
	// 값이 다른 것만 글씨 색상 변경하고 FeedBack Write일 경우 Rx에 값 작성(은 알아서)

	ReadEEP();

	byEEPValue = new BYTE[iMaxAddr + 1];
	for (i = 0; i < iMaxAddr + 1; i++)
		byEEPValue[i] = -1;

	hItem = pParameterDlg->m_List_Parameter.GetFirstItem();
	hLastItem = hItem;

	for (i = 0; i < pParameterDlg->m_List_Parameter.GetCount(); i++)
	{
		//ProcessWindowMessage();
		pParameterDlg->m_Progress_Loading.SetStep(1);
		pParameterDlg->m_Progress_Loading.StepIt();

		if (hItem == NULL)
		{
			pParameterDlg->m_List_Parameter.SelectItem(hLastItem);
			pParameterDlg->m_List_Parameter.EnsureVisible(hLastItem);
			goto END;
		}

		hLastItem = hItem;
		pParameterDlg->m_List_Parameter.EnsureVisible(hItem);

		strAddr = pParameterDlg->m_List_Parameter.GetItemText(hItem, TC_PAR_ADDR);
		strByte = pParameterDlg->m_List_Parameter.GetItemText(hItem, TC_PAR_BYTE);

		// 검사
		if (!CheckHex(strAddr) || !CheckDec(strByte))
		{
			hItem = pParameterDlg->m_List_Parameter.GetNextItem(hItem);
			continue;
		}
		iByte = _ttoi(strByte);
		if (!INMIDDLE(iByte, 1, 4))
		{
			hItem = pParameterDlg->m_List_Parameter.GetNextItem(hItem);
			continue;
		}

		dwAddr = HexToDec(strAddr);

#if 0
		for (j = 0; j < iByte; j++)
		{
			//pUART->ReadParameter(dwAddr + j);

			iCnt = 0;
			while ((int)(dwAddr + j) > g_iRxAddress)
			{
				if (iCnt == 1000) 	continue;
				iCnt++;
			}
			Sleep(1);
		}
#endif
		ReadParameter(dwAddr, iByte);

		hItem = pParameterDlg->m_List_Parameter.GetNextItem(hItem);
	}

	// 4. Select Item
	pParameterDlg->m_List_Parameter.SelectItem(hLastItem);
	pParameterDlg->m_List_Parameter.EnsureVisible(hLastItem);

	// 5. Change Text Color
	BOOL bFlag = FALSE;
	DWORD dwTx = 0;
	hItem = pParameterDlg->m_List_Parameter.GetFirstItem();
	for (i = 0; i < pParameterDlg->m_List_Parameter.GetCount(); i++)
	{
		pParameterDlg->m_Progress_Loading.SetStep(1);
		pParameterDlg->m_Progress_Loading.StepIt();

		if (hItem == NULL)
			goto END;

		strAddr = pParameterDlg->m_List_Parameter.GetItemText(hItem, TC_PAR_ADDR);
		strByte = pParameterDlg->m_List_Parameter.GetItemText(hItem, TC_PAR_BYTE);
		strTx = pParameterDlg->m_List_Parameter.GetItemText(hItem, TC_PAR_TX);

		if (!CheckHex(strAddr) || !CheckDec(strByte) || !CheckHex(strTx))
		{
			hItem = pParameterDlg->m_List_Parameter.GetNextItem(hItem);
			continue;
		}
		iByte = _ttoi(strByte);

		if (!INMIDDLE(iByte, 1, 4)){
			hItem = pParameterDlg->m_List_Parameter.GetNextItem(hItem);
			continue;
		}
		dwAddr = HexToDec(strAddr);
		dwData = HexToDec(strTx);

		for (j = 0; j < iByte; j++)
		{
			if (byEEPValue[dwAddr + j] == -1)
			{
				bFlag = TRUE;
				break;
			}

			dwTx += byEEPValue[dwAddr + j] << (j * 8);
		}

		if (dwData != dwTx)
			bFlag = TRUE;

		if (bFlag)
			pParameterDlg->SetItemText(hItem, RGB(255, 0, 0));

		bFlag = FALSE;
		dwTx = 0;

		hItem = pParameterDlg->m_List_Parameter.GetNextItem(hItem);
	}

END:
	if (byEEPValue != NULL)
		delete[] byEEPValue;

	byEEPValue = NULL;


	pParameterDlg->m_Progress_Loading.ShowWindow(SW_HIDE);
}

void ReadEEP()
{
	g_iRxAddress = -1;

	BYTE SendData[3] = { 0, };

	// EEPROM Read Command
	SendData[0] = PC_STX;
	SendData[1] = PC_CMD_EEPR;
	SendData[2] = PC_ETX;
	//pComPort->WriteComm(SendData, 3); // Send Command
	WriteComm(SendData, 3);
}

void WriteEEP()
{
	pParameterDlg->m_bSuccessEEPWrite = FALSE;

	BYTE SendData[3] = { 0, };

	SendData[0] = PC_STX;
	SendData[1] = PC_CMD_EEPW;
	SendData[2] = PC_ETX;
	//pComPort->WriteComm(SendData, 3);
	WriteComm(SendData, 3);

	pParameterDlg->m_bSuccessEEPWrite = TRUE;
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

// ====================================================================================================
// DrawWinBg
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void DrawWinBg(CWnd* pWnd, CBitmap* bmpBg, const CString& strTitle, BOOL bLogoOn) // Bitmap은 아예 비어있는 걸로.
{
	// 1. 준비
	// Rect
	CRect rect;
	pWnd->GetWindowRect(rect);
	int iWidth = rect.Width();
	int iHeight = rect.Height();

	// Create DC
	CDC* pDC = pWnd->GetWindowDC();
	CDC dcBg;
	dcBg.CreateCompatibleDC(pDC);

	// Create Bitmap
	bmpBg->CreateCompatibleBitmap(pDC, iWidth, iHeight);

	// Select Object
	CBitmap* pOldBmpBg = (CBitmap*)dcBg.SelectObject(bmpBg);

	// 2. Draw
	// BackGround
	dcBg.FillSolidRect(0, 0, iWidth, iHeight, GetSysColor(COLOR_BTNFACE));

	// Top
	dcBg.FillSolidRect(0, 0, iWidth, 25, DIALOGCOLOR);

	CPen NewPen(PS_SOLID, 2, DIALOGCOLOR);
	//CPen NewPen(PS_SOLID, 2, DIALOGOUTLINE);
	CPen* pOldPen = dcBg.SelectObject(&NewPen);
	/*
	dcBg.MoveTo(0,0);
	dcBg.LineTo(iWidth-1,0);
	dcBg.LineTo(iWidth-1,iHeight-1);
	dcBg.LineTo(0,iHeight-1);
	dcBg.LineTo(0,0);
	*/
	dcBg.MoveTo(1, 1);
	dcBg.LineTo(iWidth - 1, 1);
	dcBg.LineTo(iWidth - 1, iHeight - 1);
	dcBg.LineTo(1, iHeight - 1);
	dcBg.LineTo(1, 1);

	CPen NewPen2(PS_SOLID, 1, DIALOGOUTLINE);
	dcBg.SelectObject(NewPen2);

	dcBg.MoveTo(0, 0);
	dcBg.LineTo(iWidth - 1, 0);
	dcBg.LineTo(iWidth - 1, iHeight - 1);
	dcBg.LineTo(0, iHeight - 1);
	dcBg.LineTo(0, 0);

	dcBg.SelectObject(pOldPen);

	// font
	LOGFONT lf;
	::ZeroMemory(&lf, sizeof(lf));
	lf.lfHeight = 15;
	lf.lfWeight = 700;
	wsprintf(lf.lfFaceName, _T("%s"), _T("Arial"));
	CFont NewFont;
	NewFont.CreateFontIndirectW(&lf);
	CFont* pOldFont = dcBg.SelectObject(&NewFont);

	dcBg.SetBkMode(TRANSPARENT);
	dcBg.SetTextColor(TITLECOLOR);

	dcBg.TextOutW(10, 6, strTitle);

	dcBg.SelectObject(pOldFont);

	pWnd->ReleaseDC(pDC);
}