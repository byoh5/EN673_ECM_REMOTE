
// Key.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CKeyApp:
// �� Ŭ������ ������ ���ؼ��� Key.cpp�� �����Ͻʽÿ�.
//

class CKeyApp : public CWinApp
{
public:
	CKeyApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CKeyApp theApp;