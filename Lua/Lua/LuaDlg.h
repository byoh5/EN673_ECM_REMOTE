
// LuaDlg.h : 헤더 파일
//

#pragma once
#include "resource.h"
#include "BtnST.h"
#include "ShadeButtonST.h"
#include "afxwin.h"

// CLuaDlg 대화 상자
class CLuaDlg : public CDialogEx
{
// 생성입니다.
public:
	CLuaDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_LUA };

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
	virtual void OnCancel();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	CPoint m_Point;

	char ch_ip[64];
	char ch_port[64];

	CButtonST m_Btn_Close;
	CButtonST m_Btn_Minimize;
	CButtonST m_Btn_Connect;
	CEdit m_Edit_LuaFile;
	CButtonST m_Btn_OpenLua;
	CButton m_Btn_LuaRun;


	afx_msg void OnBnClickedButtonLuaclose();
	afx_msg void OnBnClickedButtonMinimize();
	afx_msg void OnBnClickedButtonOpenlua();
	
	
	afx_msg void OnBnClickedButtonLuarun();
	void StartLuaRunThread();
	BOOL m_bLua;
	BOOL m_bLuaThread;

	void EnableCtrl(BOOL bEnable);

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void Check_Timer_On();
	void Check_Timer_Off();
	void Connect_Timer_On();
	void Connect_Timer_Off();
	UINT m_CheckTimerID;
	UINT m_ConnectTimerID;
};
