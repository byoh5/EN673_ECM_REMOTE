
// stdafx.cpp : 표준 포함 파일만 들어 있는 소스 파일입니다.
// ECM_remote.pch는 미리 컴파일된 헤더가 됩니다.
// stdafx.obj에는 미리 컴파일된 형식 정보가 포함됩니다.

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