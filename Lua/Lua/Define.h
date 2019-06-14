#pragma once

#include <windows.h>

#define DEFAULT_PORT "5556"

#define DLG_LUA					_T("Lua")

// >> Base Color
// ----------------------------------------------------------------------------------------------------
#define TITLECOLOR				RGB(255, 255, 255)
#if 0
#define DIALOGCOLOR				RGB(73, 85, 118) /*��ä���Ķ�*/
//#define DIALOGCOLOR				RGB(125, 138, 147) /*�Ķ��� ������ ȸ��*/
#define	DIALOGSUBCOLOR			RGB(110, 135, 170)
#define DIALOGOUTLINE			RGB(27, 39, 67)
#else
#define DIALOGCOLOR				RGB(117, 94, 72)
#define	DIALOGSUBCOLOR			RGB(170, 140, 110)
#define DIALOGOUTLINE			RGB(66, 46, 26)
#endif

// TreeList
//#define ROOTCOLOR				RGB(241, 245, 251) // Root
#define ROOTCOLOR				RGB(245, 245, 245) // Root
#define ERRORCOLOR				RGB(228, 203, 221) // Root


// Window Message Default Processing
BOOL DefaultWindowMessage(MSG* pMsg);

// Get
CString	GetNowPath();	// �������α׷� ��ġ ���丮

// ��ȯ
CString	RelativeToAbsolute(CString strRePath, CString strNowPath); // �����->������
CString	AbsoluteToRelative(CString strAbPath, CString strNowPath); // ������->�����

DWORD	HexToDec(const CString& sHex); // 16���� -> 10����
CString	HexToBin(const CString& sHex); // 16���� -> 2����
int		BinToDec(const CString& sBin); // 2���� -> 10����
CString	HexStringOut(unsigned int i);

// �˻�
BOOL	CheckHex(const CString& str);
BOOL	CheckDec(const CString& str);

// ����
BOOL	ShowOpenFileDlg(CString* strPath, CString strDefExt, CString strFilter, CWnd* pWnd);
BOOL	ShowSaveFileDlg(CString *strPath, CString strDefExt, CString strFilter, CWnd* pWnd);

void	DrawWinBg(CWnd* pWnd, CBitmap* bmpBg, const CString& strTitle, BOOL bLogoOn = FALSE);// Draw Window BackGround

// ====================================================================================================
// Initial (Default Value)
// ====================================================================================================
#define INIFILE					_T(".\\ecm.ini")

#define SEC_WININFO				_T("WinInfo")

#define	KEY_LUADLGLEFT			_T("LuaDlgLeft")
#define KEY_LUADLGTOP			_T("LuaDlgTop")

#define DEF_LUADLGLEFT			210
#define DEF_LUADLGTOP			390

// Ini File
// Read
int ReadIni(CString strSector, CString strKey, int iDefault);
CString ReadIni(CString strSector, CString strKey, CString strDefault);
//Write
void WriteIni(CString strSector, CString strKey, CString strData);
void WriteIni(CString strSector, CString strKey, int iData);

UINT32 jtag_htonl(UINT32 n);

//JTAG UART
int ReadISP(DWORD dwAddr);
int WriteISP(DWORD dwAddr, DWORD dwData);
int WriteComm(BYTE *pBuff, int nToWrite);
int	JtagUartAck();

void Wait(DWORD deMillisecond);