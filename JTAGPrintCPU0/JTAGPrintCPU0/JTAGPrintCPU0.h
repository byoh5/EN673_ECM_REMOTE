
// JTAGPrintCPU0.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CJTAGPrintCPU0App:
// �� Ŭ������ ������ ���ؼ��� JTAGPrintCPU0.cpp�� �����Ͻʽÿ�.
//

class CJTAGPrintCPU0App : public CWinApp
{
public:
	CJTAGPrintCPU0App();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CJTAGPrintCPU0App theApp;