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

	if (bLogoOn)
		dcBg.TextOutW(30, 6, strTitle);
	else
		dcBg.TextOutW(10, 6, strTitle);

	dcBg.SelectObject(pOldFont);

	pWnd->ReleaseDC(pDC);
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


int ReadISP(DWORD dwAddr)
{
	BYTE SendData[5] = { 0, };

	int state;

	SendData[0] = PC_STX;
	SendData[1] = PC_CMD_REG;
	// Addr
	SendData[2] = (BYTE)((dwAddr & 0xff00) >> 8);
	SendData[3] = (BYTE)(dwAddr & 0x00ff);

	SendData[4] = PC_ETX;

	state = WriteComm(SendData, 5);
	if (state < 0)	return -1;

	return 0;
}

// ====================================================================================================
// JtagUartWrite
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
int WriteISP(DWORD dwAddr, DWORD dwData)
{	
	BYTE SendData[9] = { 0, };
	int state;

	SendData[0] = PC_STX;
	SendData[1] = PC_CMD_REGW;
	// Addr
	SendData[2] = (BYTE)((dwAddr & 0xff00) >> 8);
	SendData[3] = (BYTE)(dwAddr & 0x00ff);
	// Data 
	SendData[4] = (BYTE)(dwData >> 24);
	SendData[5] = (BYTE)(dwData >> 16);
	SendData[6] = (BYTE)(dwData >> 8);
	SendData[7] = (BYTE)(dwData);

	SendData[8] = PC_ETX;

	state = WriteComm(SendData, 9);
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

		n_temp[i] = ntohl(n_temp[i]);
	}

	//write32(addr, (UINT32*)n_temp, 3, WBCOM);
	state = setDataFromRemote(ConnectSocket, JTAG_UART_ADDR, nToWrite + 2, WBCOM, &n_temp);
	if (state < 0)	return -1;

	state = JtagUartAck();
	if (state < 0)	return -1;

	return 0;
}

int	JtagUartAck()
{
	UINT32 shell_noty = 0;
	UINT32 irq = 0;

	BYTE * temp;

	int state;

	shell_noty = JTAG_UART_NOTIFY;
	temp = (BYTE *)(ntohl(shell_noty));
	//pJTAG->write32(JTAG_SHELL_NOTIFY_ADDR, &shell_noty, 1, WBCOM);
	state = setDataFromRemote(ConnectSocket, JTAG_SHELL_NOTIFY_ADDR, 4, WBCOM, &temp);
	if (state < 0)	return -1;

	state = getDataFromRemote(ConnectSocket, JTAG_CPU_IRQ_ADDR, 4, WBCOM, &temp);
	irq = ntohl((UINT32)temp);
	irq = irq | JTAG_CPU_IRQ0;
	temp = (BYTE *)(ntohl(irq));
	//pJTAG->write32(JTAG_CPU_IRQ_ADDR, &irq, 1, WBCOM);
	state = setDataFromRemote(ConnectSocket, JTAG_CPU_IRQ_ADDR, 4, WBCOM, &temp);
	if (state < 0)	return -1;

	Sleep(20);

	return 0;
}