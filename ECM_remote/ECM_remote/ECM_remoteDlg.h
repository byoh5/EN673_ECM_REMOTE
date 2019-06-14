
// ECM_remoteDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "btnst.h"
#include "ShadeButtonST.h"
#include "resource.h"
#include "ServerDlg.h"
#include "ECMSearchDlg.h"
#include "Define.h"


// CECM_remoteDlg 대화 상자

class CECM_remoteDlg : public CDialogEx
{
// 생성입니다.
public:
	CECM_remoteDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ECM_REMOTE_DIALOG };

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
	CButtonST		m_Btn_Close;
	CButtonST		m_Btn_Minimize;
	CIPAddressCtrl	m_ctrlIPAddr;
	CEdit			m_Edit_Port;
	CShadeButtonST	m_Btn_Reset;
	CShadeButtonST	m_Btn_Stall;
	CButtonST		m_Btn_Setting;
	CShadeButtonST	m_Bt_Server;
	CButtonST		m_Bt_ServerState;
	CShadeButtonST	m_Bt_ECMSearch;
	CShadeButtonST	m_Bt_Downloader;
	CShadeButtonST	m_Bt_Parameter;
	CShadeButtonST	m_Bt_Viewer;
	CShadeButtonST	m_Bt_JTAGPrint0;
	CShadeButtonST	m_Bt_JTAGPrint1;
	CShadeButtonST	m_Bt_JTAGPrint;
	CShadeButtonST	m_Bt_JTAGDebugger;
	CShadeButtonST	m_Bt_Analyzer;
	CShadeButtonST	m_Bt_ISP;
	CShadeButtonST	m_Bt_Gamma;
	CShadeButtonST	m_Bt_ColorMap;
	CShadeButtonST	m_Bt_Key;
	CShadeButtonST	m_Bt_UartString;
	CShadeButtonST	m_Bt_Lua;
	CShadeButtonST	m_Bt_IPCamSearch;
	CButtonST		m_Btn_Special;

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonMinimize();
	afx_msg void OnBnClickedButtonReset();
	afx_msg void OnBnClickedButtonStall();
	afx_msg void OnBnClickedButtonSetting();
	afx_msg void OnBnClickedButtonServer();
	afx_msg void OnBnClickedButtonServerstate();
	afx_msg void OnBnClickedButtonEcmsearch();
	afx_msg void OnBnClickedButtonDownloader();
	afx_msg void OnBnClickedButtonParameter();
	afx_msg void OnBnClickedButtonViewer();
	afx_msg void OnBnClickedButtonJtagprint0();
	afx_msg void OnBnClickedButtonJtagprint1();
	afx_msg void OnBnClickedButtonJtagprint();
	afx_msg void OnBnClickedButtonDebugger();
	afx_msg void OnBnClickedButtonAnalyzer();
	afx_msg void OnBnClickedButtonIsp();
	afx_msg void OnBnClickedButtonGamma();
	afx_msg void OnBnClickedButtonColormap();
	afx_msg void OnBnClickedButtonKey();
	afx_msg void OnBnClickedButtonUartstring();
	afx_msg void OnBnClickedButtonLua();
	afx_msg void OnBnClickedButtonIpcamsearch();
	afx_msg void OnBnClickedButtonShspecial();


	CPoint			m_Point;
	CRect			initRect;
	int				initRect_Width;
	int				initRect_Height;

	// Connect Button
	BOOL			flag_close;

	// IP, Port
	SHELLEXECUTEINFO m_sInfo[MAUE_NUM];
	BYTE			IP[4];
	CString			Addr;
	CString			Port;

	CString GetMyIPAddress();
	int GetIP();
	int GetPort();

	// exe 실행
	CString			Command;
	int ExeFunc(int func, const CString& strTitle);

	// 종료 확인 thread
	CWinThread*		g_pExeState;

	// 종료, 최소화 동작
	void EXEControl(CString dlgname, CString buttonname = NULL);
	void EXEControl(int dlgnum, CString buttonname = NULL);

	// 버튼 활성화
	void InitEnableCtrl();
	void EnableCtrl(int i, BOOL state);
	void ActiveCtrl(int i, BOOL state);

	void ShowSpecial(BOOL bFlag);


	CServerDlg*		m_pDlg_Server;
	CECMSearchDlg*	m_pDlg_ECMSearch;
	BOOL			m_ShowDlg_Server;
	BOOL			m_ShowDlg_ECMSearch;
	BOOL			m_ShowDlg_Downloader;
	BOOL			m_ShowDlg_Parameter;
	BOOL			m_ShowDlg_Viewer;
	BOOL			m_ShowDlg_JTAGPrint0;
	BOOL			m_ShowDlg_JTAGPrint1;
	BOOL			m_ShowDlg_JTAGPrint;
	BOOL			m_ShowDlg_JTAGDebugger;
	BOOL			m_ShowDlg_Analyzer;
	BOOL			m_ShowDlg_ISP;
	BOOL			m_ShowDlg_Gamma;
	BOOL			m_ShowDlg_ColorMap;
	BOOL			m_ShowDlg_Key;
	BOOL			m_ShowDlg_UartString;
	BOOL			m_ShowDlg_Lua;
	BOOL			m_ShowDlg_IPCamSearch;

	BOOL			m_ShowSpecial_flag;

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void Check_Timer_On();
	void Check_Timer_Off();
	UINT m_CheckTimerID;
	void Connect_Timer_On();
	void Connect_Timer_Off();
	UINT m_ConnectTimerID;


	char ch_ip[64];
	char ch_port[64];

	char server_flag;
	char preserver_flag;

	afx_msg void OnEnKillfocusEdit1();
	afx_msg void OnEnSetfocusEdit1();
	CString FocusOnPort;
	CString FocusOffPort;

	WSADATA wsaData;
	WORD wVersionRequested;
};