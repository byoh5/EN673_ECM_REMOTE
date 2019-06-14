
// JTAGPrintCPU0Dlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "resource.h"
#include "ShadeButtonST.h"
#include "BtnST.h"


// CJTAGPrintCPU0Dlg 대화 상자
class CJTAGPrintCPU0Dlg : public CDialogEx
{
// 생성입니다.
public:
	CJTAGPrintCPU0Dlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_JTAGPRINTCPU0 };

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
	afx_msg void OnBnClickedButtonJtagprintcpu0close();
	afx_msg void OnBnClickedButtonMinimize();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButtonJtagprintcpu0Stringclear();
	afx_msg void OnBnClickedButtonJtagprintcpu0Start();
	afx_msg void OnBnClickedButtonJtagprintcpu0Stringsave();
	afx_msg void OnBnClickedButtonJtagprintcpu0Stringstop();
	afx_msg void OnBnClickedButtonAutosavepath();

	CButtonST	m_Btn_Close;
	CButtonST	m_Btn_Minimize;
	CButton		m_Btn_StartJTAGPrint;
	CButtonST	m_Btn_Save;
	CButton		m_Btn_Stop;
	CButton		m_Btn_Clear;
	CEdit		m_Edit_String;
	CEdit		m_Edit_MaxLine;
	CStatic		m_Static_AutoSave;
	CButtonST	m_Btn_OpenPath;

	CPoint		m_Point;

	// String
	BOOL		m_bStopJTAGPrint;
	int			m_iStringCnt;
	int			m_iMaxLine;

	BOOL		m_bRunJTAGPrint;
	BOOL		m_bClear;
	BOOL		m_bWaitClearJTAGPrint;
	BOOL		m_bAutoSave;

	void		JTAGPrint();
	void		DispString(UINT8 *pBuf);
	void		EnableCtrl(BOOL bEnable);
	void		SaveValue();						// 작업정보 inifile에 저장
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
