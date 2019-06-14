#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "BtnST.h"


// CViewerSnap ��ȭ �����Դϴ�.

class CViewerSnap : public CDialogEx
{
	DECLARE_DYNAMIC(CViewerSnap)

public:
	CViewerSnap(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CViewerSnap();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_VIEWER_SNAP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_List_Snap;
	CEdit m_Edit_SnapTime;
	CButton m_Btn_Snap;
	CButton m_Chk_AutoSnap;
	CButtonST m_Btn_SaveSnap;
	CButton m_Btn_SnapClear;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonSnap();
	afx_msg void OnBnClickedCheckAuto();
	afx_msg void OnBnClickedButtonSavesnap();
	afx_msg void OnBnClickedButtonSnapclear();

	BOOL		m_OnAutoSnap;		// TRUE == Run AutoSnap

	void LineCapture();

	void EnableCtrl(BOOL b);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
