
// JTAGPrintCPU1.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CJTAGPrintCPU1App:
// �� Ŭ������ ������ ���ؼ��� JTAGPrintCPU1.cpp�� �����Ͻʽÿ�.
//

class CJTAGPrintCPU1App : public CWinApp
{
public:
	CJTAGPrintCPU1App();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CJTAGPrintCPU1App theApp;