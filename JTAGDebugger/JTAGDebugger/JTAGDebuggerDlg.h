
// JTAGDebuggerDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "resource.h"
#include "BtnST.h"
#include "ShadeButtonST.h"
#include "jtag_flash.h"

#define DOWNOUTPUT_NONE			0
#define DOWNOUTPUT_CLEARLINE	1
#define	DOWNOUTPUT_CLEARALL		2

// CJTAGDebuggerDlg 대화 상자
class CJTAGDebuggerDlg : public CDialogEx
{
// 생성입니다.
public:
	CJTAGDebuggerDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_JTAGDEBUGGER };

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
	CButtonST m_Btn_Close;
	CButtonST m_Btn_Minimize;

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnCancel();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButtonJtagdebuggerclose();
	afx_msg void OnBnClickedButtonMinimize();

	CPoint			m_Point;

	// Memory
	afx_msg void OnBnClickedButtonMemoryrwread();
	afx_msg void OnBnClickedButtonMemoryrwwrite();
	CEdit m_Edit_MemoryAddr;
	CEdit m_Edit_MemorySize;
	CComboBox m_Cbo_MemoryModule;
	CButton m_Btn_MemoryRead;
	CButton m_Btn_MemoryWrite;
	void MemoryRead();
	void MemoryWrite();

	// Register
	afx_msg void OnBnClickedButtonRegisterrwread();
	afx_msg void OnBnClickedButtonRegisterrwwrite();
	CEdit m_Edit_RegisterAddr;
	CEdit m_Edit_RegisterSize;
	CEdit m_Edit_RegisterData;
	CComboBox m_Cbo_RegisterModule;
	CButton m_Btn_RegisterRead;
	CButton m_Btn_RegisterWrite;
	void RegisterRead();
	void RegisterWrite();

	// Select CPU
	afx_msg void OnBnClickedRadioJtagselectcpuCpu0();
	afx_msg void OnBnClickedRadioJtagselectcpuCpu1();
	CButton m_Radio_CPU_Cpu0;
	CButton m_Radio_CPU_Cpu1;
	UINT32 m_gcpu;

	// Stall CPU
	afx_msg void OnBnClickedButtonJtagstallcpu();
	afx_msg void OnBnClickedButtonJtagunstallcpu();
	CButton m_Btn_StallCPU;
	CButton m_Btn_UnstallCPU;
	void StallCPU();
	void UnstallCPU();

	// Single Step
	afx_msg void OnBnClickedButtonJtagsinglesteprun();
	afx_msg void OnBnClickedButtonJtagsinglestepcontinue();
	CEdit m_Edit_SinglestepNum;
	CButton m_Btn_SinglestepRun;
	CButton m_Btn_Continue;
	BOOL m_bStop;
	void SinglestepRun();
	void SinglestepContinue();

	// DCR
	afx_msg void OnBnClickedButtonJtagdcr();
	CButton m_Btn_Dcr;
	void DisplayCPURegister();

	// Log
	afx_msg void OnBnClickedButtonJtagdebuggerSavelog();
	afx_msg void OnBnClickedButtonJtagdebuggerClearlog();
	CEdit m_Edit_JTAGLog;
	void AddOutBox(CString str, BOOL bClear = 0);

	// Enable Control
	void EnableCtrl(BOOL bEnable);


	char ch_ip[64];
	char ch_port[64];

	CButtonST m_Btn_Connect;
	afx_msg void OnBnClickedButtonConnect();

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void Check_Timer_On();
	void Check_Timer_Off();
	void Connect_Timer_On();
	void Connect_Timer_Off();
	UINT m_CheckTimerID;
	UINT m_ConnectTimerID;

	BOOL WDT_flag;
};
