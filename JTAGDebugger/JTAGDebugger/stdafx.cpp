
// stdafx.cpp : 표준 포함 파일만 들어 있는 소스 파일입니다.
// JTAGDebugger.pch는 미리 컴파일된 헤더가 됩니다.
// stdafx.obj에는 미리 컴파일된 형식 정보가 포함됩니다.

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