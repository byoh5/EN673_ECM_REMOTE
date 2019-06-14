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


BOOL IsFileWritable(const WCHAR* pszFilePath)
{
	HANDLE      hFile = INVALID_HANDLE_VALUE;

	hFile = CreateFile(pszFilePath, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	CloseHandle(hFile);

	return TRUE;
}


UINT32 jtag_htonl(UINT32 n)
{
	return ((n & 0xff) << 24) |
		((n & 0xff00) << 8) |
		((n & 0xff0000UL) >> 8) |
		((n & 0xff000000UL) >> 24);
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

void Trace(char* szFormat, ...)
{
	char szTempBuf[2048];
	va_list vlMarker;

	va_start(vlMarker, szFormat);
	vsprintf(szTempBuf, szFormat, vlMarker);
	va_end(vlMarker);

	OutputDebugString((LPCWSTR)szTempBuf);
}