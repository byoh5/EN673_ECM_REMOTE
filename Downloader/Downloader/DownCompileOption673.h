#pragma once
#include "afxwin.h"
#include "EN673_Configuration_GeneratorDlg.h"

// CDownCompileOption673 대화 상자입니다.

class CDownCompileOption673 : public CDialogEx
{
	DECLARE_DYNAMIC(CDownCompileOption673)

public:
	CDownCompileOption673(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDownCompileOption673();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DOWN_COMPILEOPTION_673 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CComboBox m_Cbo_Compile;
	CComboBox m_Cbo_Mode;
	CButton m_Chk_Disassemble;
	CButton m_Chk_SectionWriteBoot;
	CButton m_Chk_Ethernet;
	CButton m_Chk_WiFi;
	CButton m_Chk_ActiveX;
	CButton m_Chk_Onvif;
	CEdit m_Edit_CompileOption;
	CEdit m_Edit_ApplicationOption;
	CEdit m_Edit_ConfigGen;
	CEdit m_Edit_CustomOption;

	void ChangeOption();
	afx_msg void OnCbnSelchangeCombo673OptionCompile();
	afx_msg void OnCbnSelchangeCombo673OptionMode();
	afx_msg void OnBnClickedCheck673OptionEthernet();
	afx_msg void OnBnClickedCheck673OptionWifi();
	afx_msg void OnBnClickedCheck673OptionActivex();
	afx_msg void OnBnClickedCheck673OptionOnvif();
	afx_msg void OnBnClickedCheck673OptionDis();
	afx_msg void OnBnClickedCheck673OptionSectionwriteboot();

	
	CRect	m_rcOriginalRect;
	// actual scroll position
	int		m_nScrollPos;
	// actual dialog height
	int		m_nCurHeight;
	// dragging
	BOOL	m_bDragging;
	CPoint	m_ptDragPoint;
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

	// Config Generator
	CEN673_Configuration_GeneratorDlg*	m_pCEN673_Configuration_GeneratorDlg;
	BOOL m_ShowDlg_ConfigGen;
	CButton m_Btn_ConfigGen;
	afx_msg void OnBnClickedButtonConfiggen();
	afx_msg void OnDestroy();
};
