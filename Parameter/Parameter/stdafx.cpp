
// stdafx.cpp : ǥ�� ���� ���ϸ� ��� �ִ� �ҽ� �����Դϴ�.
// Parameter.pch�� �̸� �����ϵ� ����� �˴ϴ�.
// stdafx.obj���� �̸� �����ϵ� ���� ������ ���Ե˴ϴ�.

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