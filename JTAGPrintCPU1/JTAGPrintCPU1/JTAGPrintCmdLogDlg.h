#pragma once
#include "afxwin.h"
#include "BtnST.h"


// CJTAGPrintCmdLogDlg ��ȭ �����Դϴ�.

class CJTAGPrintCmdLogDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CJTAGPrintCmdLogDlg)

public:
	CJTAGPrintCmdLogDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CJTAGPrintCmdLogDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_JTAGPRINTCMDLOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
