
// stdafx.cpp : ǥ�� ���� ���ϸ� ��� �ִ� �ҽ� �����Դϴ�.
// JTAGDebugger.pch�� �̸� �����ϵ� ����� �˴ϴ�.
// stdafx.obj���� �̸� �����ϵ� ���� ������ ���Ե˴ϴ�.

#include "stdafx.h"

int					ConnectSocket;
int					StateSocket;
CJTAGDebuggerDlg*	pJTAGDebuggerDlg;

BOOL	bRunMemoryReadThread;
BOOL	bRunMemoryWriteThread;
BOOL	bRunRegisterReadThread;
BOOL	bRunRegisterWriteThread;
BOOL	bRunStallCPUThread;
BOOL	bRunUnstallCPUThread;
BOOL	bRunSinglestepRunThread;
BOOL	bRunSinglestepContinueThread;
BOOL	bRunDisplayCPURegisterThread;