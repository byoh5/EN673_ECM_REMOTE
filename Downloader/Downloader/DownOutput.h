#pragma once
#include "afxwin.h"


#define DOWNOUTPUT_NONE			0
#define DOWNOUTPUT_CLEARLINE	1
#define	DOWNOUTPUT_CLEARALL		2

// CDownOutput 대화 상자입니다.

class CDownOutput : public CDialogEx
{
	DECLARE_DYNAMIC(CDownOutput)

public:
	CDownOutput(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDownOutput();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DOWN_OUTPUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_Edit_Output;
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	void	AddOutBox(CString str, BOOL bClear = 0);
};
