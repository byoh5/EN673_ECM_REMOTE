#pragma once
#include "BtnST.h"
#include "ShadeButtonST.h"
#include "afxwin.h"


// CServerDlg 대화 상자입니다.

class CServerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CServerDlg)

public:
	CServerDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CServerDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SERVER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnPaint();

	CButtonST m_Btn_Close;
	CEdit m_Edit_ServerCommand;
	CButton m_Btn_ServerRun;
	CButton m_Radio_ChA;
	CButton m_Radio_ChB;

	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedServerrun();
};
