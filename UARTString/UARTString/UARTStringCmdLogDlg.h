#pragma once
#include "BtnST.h"
#include "afxwin.h"
#include "resource.h"

// CUARTStringCmdLogDlg ��ȭ �����Դϴ�.

class CUARTStringCmdLogDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CUARTStringCmdLogDlg)

public:
	CUARTStringCmdLogDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CUARTStringCmdLogDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_UARTSTRINGCMDLOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
