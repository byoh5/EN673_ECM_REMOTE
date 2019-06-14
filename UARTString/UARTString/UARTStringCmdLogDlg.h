#pragma once
#include "BtnST.h"
#include "afxwin.h"
#include "resource.h"

// CUARTStringCmdLogDlg 대화 상자입니다.

class CUARTStringCmdLogDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CUARTStringCmdLogDlg)

public:
	CUARTStringCmdLogDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CUARTStringCmdLogDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_UARTSTRINGCMDLOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	CButtonST m_Btn_Close;
	afx_msg void OnBnClickedButtonClose();

	CListBox m_List_CmdLog;
	afx_msg void OnLbnDblclkListCmdlog();
};
