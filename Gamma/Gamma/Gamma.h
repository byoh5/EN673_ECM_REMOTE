
// Gamma.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CGammaApp:
// �� Ŭ������ ������ ���ؼ��� Gamma.cpp�� �����Ͻʽÿ�.
//

class CGammaApp : public CWinApp
{
public:
	CGammaApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CGammaApp theApp;