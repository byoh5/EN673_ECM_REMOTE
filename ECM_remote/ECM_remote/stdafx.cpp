
// stdafx.cpp : ǥ�� ���� ���ϸ� ��� �ִ� �ҽ� �����Դϴ�.
// ECM_remote.pch�� �̸� �����ϵ� ����� �˴ϴ�.
// stdafx.obj���� �̸� �����ϵ� ���� ������ ���Ե˴ϴ�.

#include "stdafx.h"

//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

// ETC
// Hover
int						g_iHover;

CECM_remoteDlg*			pRemoteDlg;
CServerDlg*				pCServerDlg;
CSettingDlg*			pCSettingDlg;
CECMSearchDlg*			pCECMSearchDlg;

BOOL					m_CServerDlg;
BOOL					m_CECMSearchDlg;

int				ConnectSocket;