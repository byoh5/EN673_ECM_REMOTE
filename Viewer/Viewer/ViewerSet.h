#pragma once
#include "afxwin.h"


// CViewerSet 대화 상자입니다.

class CViewerSet : public CDialogEx
{
	DECLARE_DYNAMIC(CViewerSet)

public:
	CViewerSet(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CViewerSet();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_VIEWER_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	CH				m_Ch[CHANNELTOTAL];

	CButton			m_Chk_Ch[CHANNELTOTAL];
	CColorPicker	m_Color[CHANNELTOTAL];
	CEdit			m_Edit_Mnem[CHANNELTOTAL];
	CComboBox		m_Cbo_Scale[CHANNELTOTAL];
	CSpinButtonCtrl	m_Spin_Scale[CHANNELTOTAL];
	CComboBox		m_Cbo_Offset[CHANNELTOTAL];
	CSpinButtonCtrl	m_Spin_Offset[CHANNELTOTAL];
	CComboBox		m_Cbo_Type[CHANNELTOTAL];

	int				m_iSpinMax;
	int				m_iSpinMin;

	CButton m_Btn_VSetLoad;
	CButton m_Btn_VSetSave;

	CButton			m_Radio_5Ch;
	CButton			m_Radio_8Ch;
	BOOL			m_bChMode;	// 5channel == TRUE, 8Channel == FALSE;
	void			SetChannelMode(int i);

	void			SaveValue();

	afx_msg void OnBnClickedCheckViewerch0();
	afx_msg void OnBnClickedCheckViewerch1();
	afx_msg void OnBnClickedCheckViewerch2();
	afx_msg void OnBnClickedCheckViewerch3();
	afx_msg void OnBnClickedCheckViewerch4();
	afx_msg void OnBnClickedCheckViewerch5();
	afx_msg void OnBnClickedCheckViewerch6();
	afx_msg void OnBnClickedCheckViewerch7();
	void OnBnClickedCheckViewerch(int i);

	afx_msg void OnEnChangeEditMnem0();
	afx_msg void OnEnChangeEditMnem1();
	afx_msg void OnEnChangeEditMnem2();
	afx_msg void OnEnChangeEditMnem3();
	afx_msg void OnEnChangeEditMnem4();
	afx_msg void OnEnChangeEditMnem5();
	afx_msg void OnEnChangeEditMnem6();
	afx_msg void OnEnChangeEditMnem7();
	void OnEnChangeEditMnem(int i);

	afx_msg void OnCbnEditchangeCboScale0();
	afx_msg void OnCbnEditchangeCboScale1();
	afx_msg void OnCbnEditchangeCboScale2();
	afx_msg void OnCbnEditchangeCboScale3();
	afx_msg void OnCbnEditchangeCboScale4();
	afx_msg void OnCbnEditchangeCboScale5();
	afx_msg void OnCbnEditchangeCboScale6();
	afx_msg void OnCbnEditchangeCboScale7();
	void OnCbnEditchangeCboScale(int i);

	afx_msg void OnDeltaposSpinScale0(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinScale1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinScale2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinScale3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinScale4(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinScale5(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinScale6(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinScale7(NMHDR *pNMHDR, LRESULT *pResult);
	void OnDeltaposSpinScale(NMHDR *pNMHDR, LRESULT *pResult, int i);

	afx_msg void OnCbnEditchangeCboOffset0();
	afx_msg void OnCbnEditchangeCboOffset1();
	afx_msg void OnCbnEditchangeCboOffset2();
	afx_msg void OnCbnEditchangeCboOffset3();
	afx_msg void OnCbnEditchangeCboOffset4();
	afx_msg void OnCbnEditchangeCboOffset5();
	afx_msg void OnCbnEditchangeCboOffset6();
	afx_msg void OnCbnEditchangeCboOffset7();
	void OnCbnEditchangeCboOffset(int i);

	afx_msg void OnDeltaposSpinOffset0(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinOffset1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinOffset2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinOffset3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinOffset4(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinOffset5(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinOffset6(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinOffset7(NMHDR *pNMHDR, LRESULT *pResult);
	void OnDeltaposSpinOffset(NMHDR *pNMHDR, LRESULT *pResult, int i);
	
	afx_msg void OnCbnSelchangeComboType0();
	afx_msg void OnCbnSelchangeComboType1();
	afx_msg void OnCbnSelchangeComboType2();
	afx_msg void OnCbnSelchangeComboType3();
	afx_msg void OnCbnSelchangeComboType4();
	afx_msg void OnCbnSelchangeComboType5();
	afx_msg void OnCbnSelchangeComboType6();
	afx_msg void OnCbnSelchangeComboType7();
	void OnCbnSelchangeComboType(int i);

	LRESULT		OnSelChangeColor(WPARAM wParam, LPARAM lParam);	// Event Function of Color Picker

	void SetUseCh(int iNum, BOOL bUse);
	void SetColor(int iNum, int iR, int iG, int iB);
	void SetMnem(int iNum, CString strMnem);
	void SetScale(int iNum, CString strScale);
	void SetOffset(int iNum, CString strOffset);
	void SetType(int iNum, CString strType);

	void InitColorButton(); // ColorButton 초기화

	afx_msg void OnBnClickedButtonViewersetload();
	afx_msg void OnBnClickedButtonViewersetsave();
	afx_msg void OnBnClickedRadio5ch();
	afx_msg void OnBnClickedRadio8ch();

	virtual BOOL PreTranslateMessage(MSG* pMsg);

	BOOL OpenSet(CString strPath);
	void SaveSet(CString strPath);

	BOOL m_bUpdateSet;
};
