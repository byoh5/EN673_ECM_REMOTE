#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "BtnST.h"


// CViewerSnap 대화 상자입니다.

class CViewerSnap : public CDialogEx
{
	DECLARE_DYNAMIC(CViewerSnap)

public:
	CViewerSnap(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CViewerSnap();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_VIEWER_SNAP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
