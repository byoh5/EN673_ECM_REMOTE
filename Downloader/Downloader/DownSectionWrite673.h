#pragma once
#include "afxwin.h"


// CDownSectionWrite673 ��ȭ �����Դϴ�.

class CDownSectionWrite673 : public CDialogEx
{
	DECLARE_DYNAMIC(CDownSectionWrite673)

public:
	CDownSectionWrite673(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDownSectionWrite673();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DOWN_SECTIONWRITE_673 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CButton m_Check_IncludeBoot;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
