
// stdafx.cpp : 표준 포함 파일만 들어 있는 소스 파일입니다.
// JTAGPrintCPU1.pch는 미리 컴파일된 헤더가 됩니다.
// stdafx.obj에는 미리 컴파일된 형식 정보가 포함됩니다.

#include "stdafx.h"


int						ConnectSocket;
int						StateSocket;

CJTAGPrintCPU1Dlg*		pJTAGPrintCPU1Dlg;
CJTAGPrintCmdLogDlg*	pJTAGPrintCmdLogDlg;

// JTAG Print
BOOL					bRunStartJTAGPrintCPU1Thread;
BOOL					bRunEndJTAGPrintCPU1Thread;

UINT32 now_pos_CPU0;
UINT32 now_pos_CPU1;
UINT32 last_pos_CPU0;
UINT32 last_pos_CPU1;
UINT32 jtag_print_base_CPU0;
UINT32 jtag_print_base_CPU1;
UINT32 jtag_print_point_CPU0;
UINT32 jtag_print_point_CPU1;
UINT32 jtag_print_size;
CCriticalSection m_csJTAGPrint;
CCriticalSection m_csJTAGDis;

CSingleLock m_csJTAG(&m_csJTAGDis);

CString autosave_filename;