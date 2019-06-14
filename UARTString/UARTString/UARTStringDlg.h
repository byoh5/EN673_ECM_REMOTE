
// UARTStringDlg.h : 헤더 파일
//
#include "BtnST.h"

#pragma once
#include "UARTStringCmdLogDlg.h"
#include "CommThread.h"
#include "resource.h"
#include "afxwin.h"

// CUARTStringDlg 대화 상자
class CUARTStringDlg : public CDialogEx
{
// 생성입니다.
public:
	CUARTStringDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_STRING };

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
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnCancel();



	CButtonST m_Btn_Close;
	afx_msg void OnBnClickedButtonStringclose();

	CButtonST m_Btn_Minimize;
	afx_msg void OnBnClickedButtonMinimize();

	CButton m_Btn_Clear;
	afx_msg void OnBnClickedButtonStringclear();

	CButton m_Btn_Stop;
	afx_msg void OnBnClickedButtonStringstop();

	CButtonST m_Btn_Save;
	afx_msg void OnBnClickedButtonStringsave();

	int m_iMaxLine;
	BOOL m_bOnChangeEditMaxLine;
	CEdit m_Edit_MaxLine;
	CButton m_Chk_Infinite;
	afx_msg void OnBnClickedCheckStringinfinite();
	afx_msg void OnEnUpdateEditStringmaxline();
	afx_msg void OnEnKillfocusEditStringmaxline();


	// String
	BOOL m_bRunString;	// Run Show String or not
	int m_iStringCnt;
	BYTE rxData[1024];
	CString m_strDispString;
	BOOL m_bOnDispString;
	BOOL m_bOnUpdateString;
	CEdit m_Edit_String;
	CEdit m_Edit_SendString;
	CWinThread*	g_pDispStringThread;
	void StartDispStringThread();
	void RxStr();
	void DispString();
	void SendString();
	int CommandShow(int sign);
	afx_msg void OnEnUpdateEditSendstring();


	// Serial Port
	CCommThread			m_ComPort;
	CString				m_strPort;
	CString				m_strBps;
	CString				m_strDataBit;
	CString				m_strParityBit;
	CString				m_strStopBit;
	CString				m_strFlowControl;
	CComboBox m_Cbo_Port;
	CComboBox m_Cbo_Bps;
	CButton m_Btn_PortOpen;
	afx_msg void OnBnClickedButtonPortopen();
	afx_msg void OnCbnSelchangeComboMainport();
	afx_msg void OnCbnSelchangeComboMainbps();
	afx_msg void OnCbnDropdownComboMainport();
	BOOL PortOpen();
	void PortClose();

	// Command Log
	CUARTStringCmdLogDlg* m_pDlg_CmdLogShow;
	BOOL m_ShowDlg_CmdLog;
	CButton m_Btn_CmdLogShow;
	afx_msg void OnBnClickedButtonCmdlogshow();

	// Etc..
	CPoint m_Point;
	int m_iPlatformSel;

	void SaveValue();
	void EnableCtrl(BOOL bEnable);
};
