
// ECM_remote.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CECM_remoteApp:
// �� Ŭ������ ������ ���ؼ��� ECM_remote.cpp�� �����Ͻʽÿ�.
//

class CECM_remoteApp : public CWinApp
{
public:
	CECM_remoteApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CECM_remoteApp theApp;