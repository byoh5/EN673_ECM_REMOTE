#include "stdafx.h"

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