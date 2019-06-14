
// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이 
// 들어 있는 포함 파일입니다.

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 일부 CString 생성자는 명시적으로 선언됩니다.

// MFC의 공통 부분과 무시 가능한 경고 메시지에 대한 숨기기를 해제합니다.
#define _AFX_ALL_WARNINGS
#ifdef _DEBUG
#include "vld.h"
#endif
#include <afxwin.h>         // MFC 핵심 및 표준 구성 요소입니다.
#include <afxext.h>         // MFC 확장입니다.


#include <afxdisp.h>        // MFC 자동화 클래스입니다.


#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Internet Explorer 4 공용 컨트롤에 대한 MFC 지원입니다.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // Windows 공용 컨트롤에 대한 MFC 지원입니다.
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC의 리본 및 컨트롤 막대 지원

#include "jtag_flash.h"
#include "jtag_def.h"
#include "lib\CLI.h"
#include "Define.h"
#include "Define_Config.h"
#include "DownloaderDlg.h"
#include "DownCompileOption673.h"
#include "DownDownOption673.h"
#include "DownSectionWrite673.h"
#include "DownOutput.h"
#include "EN673_Configuration_GeneratorDlg.h"
#include "SPIDlg.h"
#include "PeripheralDlg.h"

#define _CRTDBG_MAP_ALLOC

extern int							ConnectSocket;
extern int							StateSocket;
extern int							iPlatformSel;

extern		CDownloaderDlg*			pDownloaderDlg;
extern		CDownCompileOption673*	pDownCompileOption673;
extern		CDownDownOption673*		pDownDownOption673;
extern		CDownSectionWrite673*	pDownSectionWrite673;
extern		CDownOutput*			pDownOutput;
extern		CEN673_Configuration_GeneratorDlg*	pCEN673_Configuration_GeneratorDlg;
extern		CSPIDlg*				pCSPIDlg;
extern		CPeripheralDlg*			pCPeripheralDlg;

// Downloader
extern BOOL							bRunDownFunc1Thread;
extern BOOL							bRunDownFunc2Thread;
extern BOOL							bRunDownFunc3Thread;
extern BOOL							bRunDownFunc4Thread;
extern BOOL							bRunDownFunc5Thread;
extern BOOL							bRunDownloadHexThread;
extern BOOL							bRunJTAGFlashReadThread;
extern BOOL							bRunSPIFlashReadThread;
extern BOOL							bRunJTAGFlashEraseThread;
extern BOOL							bRunSPIFlashEraseThread;
extern BOOL							bRunJTAGFlashTestThread;
extern BOOL							bRunSPIFlashTestThread;
extern BOOL							bRunUserAreaReadThread;
extern BOOL							bRunUserAreaEraseThread;
extern BOOL							bRunUserAreaWriteThread;

extern CWinThread*					g_pDownFunc1Thread;
extern CWinThread*					g_pDownFunc2Thread;
extern CWinThread*					g_pDownFunc3Thread;
extern CWinThread*					g_pDownFunc4Thread;
extern CWinThread*					g_pDownFunc5Thread;
extern CWinThread*					g_pDownloadHexThread;
extern CWinThread*					g_pJTAGFlashReadThread;
extern CWinThread*					g_pJTAGFlashEraseThread;
extern CWinThread*					g_pJTAGFlashTestThread;
extern CWinThread*					g_pUserAreaReadThread;
extern CWinThread*					g_pUserAreaEraseThread;
extern CWinThread*					g_pUserAreaWriteThread;


#define THREAD_ON					bRunDownFunc1Thread ||		/* DownFunc1 : Dongle Download */ \
									bRunDownFunc2Thread ||		/* DownFunc2 : Uart Download */ \
									bRunDownFunc3Thread ||		/* DownFunc3 : Build */ \
									bRunDownFunc4Thread ||		/* DownFunc4 : Rebuild */ \
									bRunDownFunc5Thread ||		/* DownFunc5 : Jtag Flash Test / Jtag Flash Read */ \
									bRunDownloadHexThread ||		/* Download Hex */ \
									bRunJTAGFlashReadThread || \
									bRunJTAGFlashEraseThread || \
									bRunJTAGFlashTestThread || \
									bRunUserAreaReadThread || \
									bRunUserAreaEraseThread || \
									bRunUserAreaWriteThread



#ifdef _DEBUG
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


