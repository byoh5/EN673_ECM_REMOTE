
// stdafx.cpp : ǥ�� ���� ���ϸ� ��� �ִ� �ҽ� �����Դϴ�.
// JTAGPrintCPU1.pch�� �̸� �����ϵ� ����� �˴ϴ�.
// stdafx.obj���� �̸� �����ϵ� ���� ������ ���Ե˴ϴ�.

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