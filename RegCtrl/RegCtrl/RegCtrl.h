
// RegCtrl.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CRegCtrlApp:
// �� Ŭ������ ������ ���ؼ��� RegCtrl.cpp�� �����Ͻʽÿ�.
//

class CRegCtrlApp : public CWinApp
{
public:
	CRegCtrlApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CRegCtrlApp theApp;