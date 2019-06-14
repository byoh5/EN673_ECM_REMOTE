
// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������ 
// ��� �ִ� ���� �����Դϴ�.

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // �Ϻ� CString �����ڴ� ��������� ����˴ϴ�.

// MFC�� ���� �κа� ���� ������ ��� �޽����� ���� ����⸦ �����մϴ�.
#define _AFX_ALL_WARNINGS
#ifdef _DEBUG
#include "vld.h"
#endif
#include <afxwin.h>         // MFC �ٽ� �� ǥ�� ���� ����Դϴ�.
#include <afxext.h>         // MFC Ȯ���Դϴ�.


#include <afxdisp.h>        // MFC �ڵ�ȭ Ŭ�����Դϴ�.



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Internet Explorer 4 ���� ��Ʈ�ѿ� ���� MFC �����Դϴ�.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // Windows ���� ��Ʈ�ѿ� ���� MFC �����Դϴ�.
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC�� ���� �� ��Ʈ�� ���� ����


#include "lib\CLI.h"
#include "Define.h"
#include "JTAGPrintCPU1Dlg.h"
#include "JTAGPrintCmdLogDlg.h"

extern int							ConnectSocket;
extern int							StateSocket;

extern CJTAGPrintCPU1Dlg*			pJTAGPrintCPU1Dlg;
extern CJTAGPrintCmdLogDlg*			pJTAGPrintCmdLogDlg;

// JTAG Print
extern BOOL							bRunStartJTAGPrintCPU1Thread;
extern BOOL							bRunEndJTAGPrintCPU1Thread;

extern UINT32 now_pos_CPU0;
extern UINT32 now_pos_CPU1;
extern UINT32 last_pos_CPU0;
extern UINT32 last_pos_CPU1;
extern UINT32 jtag_print_base_CPU0;
extern UINT32 jtag_print_base_CPU1;
extern UINT32 jtag_print_point_CPU0;
extern UINT32 jtag_print_point_CPU1;
extern UINT32 jtag_print_size;
extern CCriticalSection m_csJTAGPrint;
extern CCriticalSection m_csJTAGDis;

extern CSingleLock m_csJTAG;

extern CString autosave_filename;

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


