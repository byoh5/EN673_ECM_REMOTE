
// JTAGDebugger.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CJTAGDebuggerApp:
// �� Ŭ������ ������ ���ؼ��� JTAGDebugger.cpp�� �����Ͻʽÿ�.
//

class CJTAGDebuggerApp : public CWinApp
{
public:
	CJTAGDebuggerApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CJTAGDebuggerApp theApp;