
// stdafx.cpp : ǥ�� ���� ���ϸ� ��� �ִ� �ҽ� �����Դϴ�.
// JTAGPrintCPU0.pch�� �̸� �����ϵ� ����� �˴ϴ�.
// stdafx.obj���� �̸� �����ϵ� ���� ������ ���Ե˴ϴ�.

#include "stdafx.h"


int						ConnectSocket;

CJTAGPrintCPU0Dlg*		pJTAGPrintCPU0Dlg;

// JTAG Print
BOOL					bRunStartJTAGPrintCPU0Thread;
BOOL					bRunEndJTAGPrintCPU0Thread;

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

CString autosave_filename;