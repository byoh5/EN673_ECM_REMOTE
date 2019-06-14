
// DownloaderDlg.h : 헤더 파일
//

#pragma once

#include "resource.h"
#include "ShadeButtonST.h"
#include "BtnST.h"
#include "afxcmn.h"
#include "jtag_flash.h"
#include "DownCompileOption673.h"
#include "DownDownOption673.h"
#include "DownSectionWrite673.h"
#include "DownOutput.h"
#include "EN673_Configuration_GeneratorDlg.h"
#include "afxwin.h"


// CDownloaderDlg 대화 상자
class CDownloaderDlg : public CDialogEx
{
// 생성입니다.
public:
	CDownloaderDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.
	virtual ~CDownloaderDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DOWNLOADER };

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
	virtual void OnCancel();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTcnSelchangeTabList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonDownclose();
	afx_msg void OnBnClickedButtonMinimize();
// ----------------------------------------------------------------------------------------------------
// Variable
	CPoint			m_Point;
	CBitmap			m_bmpBg;

	CButtonST m_Btn_Close;
	CButtonST m_Btn_Minimize;
	CButtonST m_Btn_Connect;
	CShadeButtonST m_Btn_DownFunc1;
	CShadeButtonST m_Btn_DownFunc2;
	CShadeButtonST m_Btn_DownFunc3;
	CShadeButtonST m_Btn_DownFunc4;
	CShadeButtonST m_Btn_DownFunc5;

	BINFILE				m_BinFile[BINNUM];
	CButton				m_Chk_BinUse[BINNUM];
	CEdit				m_Edit_BinPath[BINNUM];
	CEdit				m_Edit_SectorBgn[BINNUM];
	CEdit				m_Edit_SectorEnd[BINNUM];
	CEdit				m_Edit_StartAddr[BINNUM];
	CButtonST			m_Btn_OpenBin[BINNUM];


	CDownCompileOption673*	m_pDlg_CompileOption673;
	CDownDownOption673*		m_pDlg_DownOption673;
	CDownSectionWrite673*	m_pDlg_DownSectionWrite673;
	CDownOutput*			m_pDlg_Output;
	CTabCtrl				m_Tab_List;

	CEN673_Configuration_GeneratorDlg*	m_pCEN673_Configuration_GeneratorDlg;

	BOOL m_bStopDownload;
	BOOL m_bBuildOption;	// 0 : build, 1 : rebuild

// ----------------------------------------------------------------------------------------------------
// Function	
	// File List
	void				InitBinFileInfo(int iNum);		// BinFile 정보.
	void				InitFileList(int iNum);
	void				SaveValue();
	BOOL				ChkBins(int isUart);

	afx_msg void OnBnClickedCheckBinuse1();
	afx_msg void OnBnClickedCheckBinuse2();
	afx_msg void OnBnClickedCheckBinuse3();
	afx_msg void OnBnClickedCheckBinuse4();
	void		 OnBnClickedCheckBinuse(int iNum);
	void		 m_Edit_EnableWindow(int iNum, BOOL bEnable);
	void		 m_Chk_Option(int iNum);
	afx_msg void OnEnChangeEditBinpath1();
	afx_msg void OnEnChangeEditBinpath2();
	afx_msg void OnEnChangeEditBinpath3();
	afx_msg void OnEnChangeEditBinpath4();
	void		 OnEnChangeEditBinpath(int iNum);
	afx_msg void OnEnChangeEditSectorBgn1();
	afx_msg void OnEnChangeEditSectorBgn2();
	afx_msg void OnEnChangeEditSectorBgn3();
	afx_msg void OnEnChangeEditSectorBgn4();
	void		 OnEnChangeEditSectorBgn(int iNum);
	afx_msg void OnBnClickedButtonOpenbinpath1();
	afx_msg void OnBnClickedButtonOpenbinpath2();
	afx_msg void OnBnClickedButtonOpenbinpath3();
	afx_msg void OnBnClickedButtonOpenbinpath4();
	void		 OnBnClickedButtonOpenbinpath(int iNum);

	afx_msg void OnBnClickedButtonDownfunc1();
	void				StartDownFunc1Thread();
	void				JTAGDownload673();

	afx_msg void OnBnClickedButtonDownfunc2();
	BOOL				m_ShowDlg_ConfigGen;

	afx_msg void OnBnClickedButtonDownfunc3();
	void				StartDownFunc3Thread();
	void				BuildExRISC();
	BOOL				RunBuildExRISC(int iNum);

	afx_msg void OnBnClickedButtonDownfunc4();
	void				StartDownFunc4Thread();
	void				JTAGReset();

	afx_msg void OnBnClickedButtonDownfunc5();
	void				StartDownFunc5Thread();
	void				JTAGFlashTest672();
	BOOL				CheckSectionWrite();
	void				SectionWrite(int iNum);
	BOOL				RunSectionWrite(int iNum, UINT32* uiData, UINT32* uiiData, CString& strMsg);

	BOOL				JTAGErase(UINT32 uiStartAddress, UINT32 uiSize, CString& strMsg); // EN672
	BOOL				JTAGWrite(UINT32 uiStartAddress, UINT32 uiSize, UINT32* uiData, CString& strMsg); // EN672
	BOOL				JTAGVerify(UINT32 uiStartAddress, UINT32 uiSize, UINT8* uiData, CString& strMsg); // EN672

	// Set
	void		 SetBinPath(int iNum, CString strPath);
	void		 SetSectorBgn(int iNum, UINT uiSectorBgn);
	void		 SetSectorEnd(int iNum, UINT uiSectorEnd);

	void EnableCtrl(BOOL bEnable);

	int GetDeviceSize_JTAG();

	// Server IP, Port
	char ch_ip[64];
	char ch_port[64];

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void Check_Timer_On();
	void Check_Timer_Off();
	void Connect_Timer_On();
	void Connect_Timer_Off();
	UINT m_CheckTimerID;
	UINT m_ConnectTimerID;
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
};
