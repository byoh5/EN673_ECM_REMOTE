
// Analyze.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CAnalyzeApp:
// �� Ŭ������ ������ ���ؼ��� Analyze.cpp�� �����Ͻʽÿ�.
//

class CAnalyzeApp : public CWinApp
{
public:
	CAnalyzeApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CAnalyzeApp theApp;