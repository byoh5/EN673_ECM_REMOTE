
// Parameter.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CParameterApp:
// �� Ŭ������ ������ ���ؼ��� Parameter.cpp�� �����Ͻʽÿ�.
//

class CParameterApp : public CWinApp
{
public:
	CParameterApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CParameterApp theApp;