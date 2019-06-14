
// KeyDlg.h : 헤더 파일
//

#pragma once

#include "resource.h"
#include "BtnST.h"
#include "ShadeButtonST.h"
#define		WM_COMM_KEY						(WM_USER+2)

// CKeyDlg 대화 상자
class CKeyDlg : public CDialogEx
{
// 생성입니다.
public:
	CKeyDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_KEY };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnCancel();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButtonKeyclose();
	afx_msg void OnBnClickedButtonMinimize();
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonKeyup();
	afx_msg void OnBnClickedButtonKeyleft();
	afx_msg void OnBnClickedButtonKeyenter();
	afx_msg void OnBnClickedButtonKeyright();
	afx_msg void OnBnClickedButtonKeydown();
	afx_msg void OnBnClickedButtonExit();
	afx_msg LRESULT OnCtrlCamKey(WPARAM wParam, LPARAM lParam);

	CButtonST m_Btn_Close;
	CButtonST m_Btn_Minimize;
	CButtonST m_Btn_Connect;
	CButtonST m_Btn_Up;
	CButtonST m_Btn_Down;
	CButtonST m_Btn_Left;
	CButtonST m_Btn_Right;
	CButtonST m_Btn_Enter;
	CButtonST m_Btn_Exit;

	CPoint			m_Point;

	char ch_ip[64];
	char ch_port[64];

	void EnableCtrl(BOOL bEnable);

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void Check_Timer_On();
	void Check_Timer_Off();
	void Connect_Timer_On();
	void Connect_Timer_Off();
	UINT m_CheckTimerID;
	UINT m_ConnectTimerID;
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
};
