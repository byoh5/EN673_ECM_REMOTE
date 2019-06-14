
// HTBDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "lib\CLI.h"
#include "afxcmn.h"

// CHTBDlg 대화 상자
class CHTBDlg : public CDialogEx
{
// 생성입니다.
public:
	CHTBDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_HTB_DIALOG };

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
	afx_msg void OnClose();

	CEdit m_Edit_Port;
	CIPAddressCtrl m_ctrlIPAddr;
	CButton m_Btn_OpenDis;
	CButton m_Btn_OpenTbp;
	CButton m_Btn_ProfileGen;
	int m_CPU;

	afx_msg void OnBnClickedButtonOpendis();
	afx_msg void OnBnClickedButtonOpentbp();
	BOOL ShowOpenFileDlg(CString* strPath, CString strDefExt, CString strFilter, CWnd* pWnd, CString strStartPath = _T(""));
	CString CHTBDlg::GetSelectFolderPath();

	CString tbp_path_str;
	CString	dis_path_str;
	CString prf_path_str;
	afx_msg void OnBnClickedRadioJtagselectcpuCpu0();
	afx_msg void OnBnClickedRadioJtagselectcpuCpu1();
	int m_gcpu;

	afx_msg void OnBnClickedButtonGeneration();
	int	ConnectSocket;
	int batrun();

	void EnableCtrl(BOOL bEnable);
};
