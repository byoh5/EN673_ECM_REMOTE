
// Colormap.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CColormapApp:
// �� Ŭ������ ������ ���ؼ��� Colormap.cpp�� �����Ͻʽÿ�.
//

class CColormapApp : public CWinApp
{
public:
	CColormapApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CColormapApp theApp;