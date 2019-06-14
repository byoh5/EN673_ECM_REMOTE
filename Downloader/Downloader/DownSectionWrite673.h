#pragma once
#include "afxwin.h"


// CDownSectionWrite673 대화 상자입니다.

class CDownSectionWrite673 : public CDialogEx
{
	DECLARE_DYNAMIC(CDownSectionWrite673)

public:
	CDownSectionWrite673(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDownSectionWrite673();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DOWN_SECTIONWRITE_673 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CButton m_Check_IncludeBoot;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
