
// JTAGPrintCPU1Dlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "resource.h"
#include "ShadeButtonST.h"
#include "BtnST.h"
#include "JTAGPrintCmdLogDlg.h"

// CJTAGPrintCPU1Dlg ��ȭ ����
class CJTAGPrintCPU1Dlg : public CDialogEx
{
// �����Դϴ�.
public:
	CJTAGPrintCPU1Dlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_JTAGPRINTCPU1 };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnCancel();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBnClickedButtonJtagprintcpu1close();
	afx_msg void OnBnClickedButtonMinimize();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButtonJtagprintcpu1Start();
	afx_msg void OnBnClickedButtonJtagprintcpu1Stringsave();
	afx_msg void OnBnClickedButtonJtagprintcpu1Stringstop();
	afx_msg void OnBnClickedButtonJtagprintcpu1Stringclear();
	afx_msg void OnBnClickedButtonAutosavepath();

	CButtonST	m_Btn_Close;
	CButtonST m_Btn_Minimize;
	CButton		m_Btn_StartJTAGPrint;
	CButtonST	m_Btn_Save;
	CButton		m_Btn_Stop;
	CButton		m_Btn_Clear;
	CEdit		m_Edit_String;
	CEdit		m_Edit_RxShellCommand;
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

	// RxShellCommand
	BOOL		m_bCommand;

	// AutoSave flag
	BOOL		m_bAutoSave;

	void		JTAGPrint();
	void		DispString(UINT8 *pBuf);
	void		EnableCtrl(BOOL bEnable);
	void		RxShellCommand();
	void		SaveValue();						// �۾����� inifile�� ����
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	
	CJTAGPrintCmdLogDlg* m_pDlg_CmdLogShow;
	BOOL m_ShowDlg_CmdLog;
	CButton m_Btn_CmdLogShow;
	afx_msg void OnBnClickedButtonCmdlogshow();
	int CommandShow(int sign);

	CString up;

};
