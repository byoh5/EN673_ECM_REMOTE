#pragma once
#include "afxwin.h"


#define DOWNOUTPUT_NONE			0
#define DOWNOUTPUT_CLEARLINE	1
#define	DOWNOUTPUT_CLEARALL		2

// CDownOutput ��ȭ �����Դϴ�.

class CDownOutput : public CDialogEx
{
	DECLARE_DYNAMIC(CDownOutput)

public:
	CDownOutput(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDownOutput();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DOWN_OUTPUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_Edit_Output;
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	void	AddOutBox(CString str, BOOL bClear = 0);
};
