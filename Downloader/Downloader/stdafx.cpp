
// stdafx.cpp : 표준 포함 파일만 들어 있는 소스 파일입니다.
// Downloader.pch는 미리 컴파일된 헤더가 됩니다.
// stdafx.obj에는 미리 컴파일된 형식 정보가 포함됩니다.

#include "stdafx.h"

int					ConnectSocket;
int					StateSocket;
int					iPlatformSel;
CDownloaderDlg*				pDownloaderDlg;
CDownCompileOption673*		pDownCompileOption673;
CDownDownOption673*			pDownDownOption673;
CDownSectionWrite673*		pDownSectionWrite673;
CDownOutput*				pDownOutput;
CEN673_Configuration_GeneratorDlg*	pCEN673_Configuration_GeneratorDlg;
CSPIDlg*					pCSPIDlg;
CPeripheralDlg*				pCPeripheralDlg;


// Downloader
BOOL				bRunDownFunc1Thread;	// Dongle Download
BOOL				bRunDownFunc2Thread;	// Uart/Flash Download
BOOL				bRunDownFunc3Thread;	// Build
BOOL				bRunDownFunc4Thread;	// Rebuild All / Jtag Reset ...
BOOL				bRunDownFunc5Thread;	// Flash Read / Flash Test
BOOL				bRunDownloadHexThread;
BOOL				bRunJTAGFlashReadThread;
BOOL				bRunJTAGFlashEraseThread;
BOOL				bRunJTAGFlashTestThread;
BOOL				bRunUserAreaReadThread;
BOOL				bRunUserAreaEraseThread;
BOOL				bRunUserAreaWriteThread;

CWinThread*			g_pDownFunc1Thread;
CWinThread*			g_pDownFunc2Thread;
CWinThread*			g_pDownFunc3Thread;
CWinThread*			g_pDownFunc4Thread;
CWinThread*			g_pDownFunc5Thread;
CWinThread*			g_pDownloadHexThread;
CWinThread*			g_pJTAGFlashReadThread;
CWinThread*			g_pSPIFlashReadThread;
CWinThread*			g_pJTAGFlashEraseThread;
CWinThread*			g_pSPIFlashEraseThread;
CWinThread*			g_pJTAGFlashTestThread;
CWinThread*			g_pSPIFlashTestThread;
CWinThread*			g_pUserAreaReadThread;
CWinThread*			g_pUserAreaEraseThread;
CWinThread*			g_pUserAreaWriteThread;