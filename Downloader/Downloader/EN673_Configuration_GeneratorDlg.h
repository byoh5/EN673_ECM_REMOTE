#pragma once
#include "BtnST.h"
#include "ShadeButtonST.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "SPIDlg.h"
#include "PeripheralDlg.h"

// CEN673_Configuration_GeneratorDlg 대화 상자입니다.

class CEN673_Configuration_GeneratorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEN673_Configuration_GeneratorDlg)

public:
	CEN673_Configuration_GeneratorDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CEN673_Configuration_GeneratorDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_EN673_CONFIGURATION_GENERATOR_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	// Close Button
	CButtonST m_Btn_Close;
	afx_msg void OnBnClickedButtonClose();

	// Congif File Load
	CEdit m_Edit_Path;
	CButton m_Btn_Load;
	afx_msg void OnBnClickedButtonLoad();

	// Config File Save
	CButton m_Btn_Save;
	afx_msg void OnBnClickedButtonSave();

	// Check
	CButton m_Chk_ImagePath;
	CButton m_Chk_ISP;
	CButton m_Chk_Peripheral;

	void LoadCombo();
	void SaveCombo();
	int CStringtoIntGPIO(CString strGPIO);
	int CStringtoIntADC(CString strADC);

	// Description
	CEdit m_Edit_Description;

	//  Tab
	CSPIDlg* m_pDlg_SPI;
	CPeripheralDlg* m_pDlg_Peripheral;
	CTabCtrl m_Tab_List;
	afx_msg void OnTcnSelchangeTabList(NMHDR *pNMHDR, LRESULT *pResult);
	void InitFileList(int iNum);		//  Tab List 초기화

	void EnableCtrl(BOOL bEnable);

	afx_msg void OnBnClickedCheckImagepath();
	afx_msg void OnBnClickedCheckIsp();
	afx_msg void OnBnClickedCheckPeripheral();
	void ChangeConfig();
};
