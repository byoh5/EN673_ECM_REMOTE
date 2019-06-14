
// stdafx.cpp : 표준 포함 파일만 들어 있는 소스 파일입니다.
// Parameter.pch는 미리 컴파일된 헤더가 됩니다.
// stdafx.obj에는 미리 컴파일된 형식 정보가 포함됩니다.

#include "stdafx.h"


int					ConnectSocket;
int					StateSocket;
CParameterDlg*		pParameterDlg;

// Parameter
BOOL				bRunParLoadingThread;
BOOL				bRunParReadAllThread;
BOOL				bRunParWriteAllThread;
BOOL				bRunEEPReadThread;
BOOL				bRunEEPWriteThread;
BOOL				bRunSaveHexThread;
BYTE*				byEEPValue;

CWinThread*			g_pParLoadingThread;
CWinThread*			g_pParReadAllThread;
CWinThread*			g_pParWriteAllThread;
CWinThread*			g_pEEPReadAllThread;
CWinThread*			g_pEEPWriteAllThread;

// Thread Flag =======================================
int					g_iRxAddress;