
// stdafx.cpp : ǥ�� ���� ���ϸ� ��� �ִ� �ҽ� �����Դϴ�.
// RegCtrl.pch�� �̸� �����ϵ� ����� �˴ϴ�.
// stdafx.obj���� �̸� �����ϵ� ���� ������ ���Ե˴ϴ�.

#include "stdafx.h"

CRegCtrlDlg*		pRegDlg;

// Thread Flag =======================================
int				g_iRxAddress;

BOOL			bRunLoadingThread;
BOOL			bRunDispRegInfoThread;
BOOL			bRunReadAllThread;
BOOL			bRunWriteAllThread;

CWinThread*		g_pLoadingThread;
CWinThread*		g_pDispRegInfoThread;
CWinThread*		g_pRegReadAllThread;
CWinThread*		g_pRegWriteAllThread;

int				ConnectSocket;
int				StateSocket;