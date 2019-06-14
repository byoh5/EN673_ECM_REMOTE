#pragma once
#include "afxwin.h"
#include "BtnST.h"


// CJTAGPrintCmdLogDlg 대화 상자입니다.

class CJTAGPrintCmdLogDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CJTAGPrintCmdLogDlg)

public:
	CJTAGPrintCmdLogDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CJTAGPrintCmdLogDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_JTAGPRINTCMDLOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonJtagprintcmdlogClose();
	CListBox m_List_CmdLog;
	CButtonST m_Btn_Close;
	afx_msg void OnLbnDblclkListCmdlog();
};
