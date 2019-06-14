#pragma once
#include "afxwin.h"


// CViewerCapture 대화 상자입니다.

class CViewerCapture : public CDialogEx
{
	DECLARE_DYNAMIC(CViewerCapture)

public:
	CViewerCapture(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CViewerCapture();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_VIEWER_CAPTURE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	CButton m_Btn_LoadCap;
	CButton m_Btn_Capture;
	
	afx_msg void OnBnClickedButtonLoadcap();
	afx_msg void OnBnClickedButtonCapture();

	BOOL			OpenCap(CString strPath);

	CH				m_ChCap[CHANNELTOTAL];					// 채널 정보
	BOOL			m_bCaptureCh;							// 파일, 채널 정보 존재 여부.
	uDOUBLE			m_ChannelCap[CHANNELTOTAL][DRAWWIDTH];	// 값

	CButton			m_Chk_Ch[CHANNELTOTAL];
	CEdit			m_Edit_Mnem[CHANNELTOTAL];
	CComboBox		m_Cbo_Scale[CHANNELTOTAL];
	CSpinButtonCtrl	m_Spin_Scale[CHANNELTOTAL];
	CComboBox		m_Cbo_Offset[CHANNELTOTAL];
	CSpinButtonCtrl m_Spin_Offset[CHANNELTOTAL];
	CComboBox		m_Cbo_Type[CHANNELTOTAL];

	int				iSpinMin;
	int				iSpinMax;

	afx_msg void OnBnClickedCheckCapch0();
	afx_msg void OnBnClickedCheckCapch1();
	afx_msg void OnBnClickedCheckCapch2();
	afx_msg void OnBnClickedCheckCapch3();
	afx_msg void OnBnClickedCheckCapch4();
	afx_msg void OnBnClickedCheckCapch5();
	afx_msg void OnBnClickedCheckCapch6();
	afx_msg void OnBnClickedCheckCapch7();
	void OnBnClickedCheckCapch(int iNum);
	void EnableChannel(int iNum, BOOL b);

	afx_msg void OnEnChangeEditCapmnem0();
	afx_msg void OnEnChangeEditCapmnem1();
	afx_msg void OnEnChangeEditCapmnem2();
	afx_msg void OnEnChangeEditCapmnem3();
	afx_msg void OnEnChangeEditCapmnem4();
	afx_msg void OnEnChangeEditCapmnem5();
	afx_msg void OnEnChangeEditCapmnem6();
	afx_msg void OnEnChangeEditCapmnem7();
	void OnEnChangeEditCapmnem(int iNum);

	afx_msg void OnCbnEditchangeComboCapscale0();
	afx_msg void OnCbnEditchangeComboCapscale1();
	afx_msg void OnCbnEditchangeComboCapscale2();
	afx_msg void OnCbnEditchangeComboCapscale3();
	afx_msg void OnCbnEditchangeComboCapscale4();
	afx_msg void OnCbnEditchangeComboCapscale5();
	afx_msg void OnCbnEditchangeComboCapscale6();
	afx_msg void OnCbnEditchangeComboCapscale7();
	void OnCbnEditchangeComboCapscale(int iNum);

	afx_msg void OnDeltaposSpinCapscale0(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinCapscale1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinCapscale2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinCapscale3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinCapscale4(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinCapscale5(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinCapscale6(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinCapscale7(NMHDR *pNMHDR, LRESULT *pResult);
	void OnDeltaposSpinCapscale(NMHDR *pNMHDR, LRESULT *pResult, int iNum);

	afx_msg void OnCbnEditchangeComboCapoffset0();
	afx_msg void OnCbnEditchangeComboCapoffset1();
	afx_msg void OnCbnEditchangeComboCapoffset2();
	afx_msg void OnCbnEditchangeComboCapoffset3();
	afx_msg void OnCbnEditchangeComboCapoffset4();
	afx_msg void OnCbnEditchangeComboCapoffset5();
	afx_msg void OnCbnEditchangeComboCapoffset6();
	afx_msg void OnCbnEditchangeComboCapoffset7();
	void OnCbnEditchangeComboCapoffset(int iNum);

	afx_msg void OnDeltaposSpinCapoffset0(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinCapoffset1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinCapoffset2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinCapoffset3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinCapoffset4(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinCapoffset5(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinCapoffset6(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinCapoffset7(NMHDR *pNMHDR, LRESULT *pResult);
	void OnDeltaposSpinCapoffset(NMHDR *pNMHDR, LRESULT *pResult, int iNum);

	afx_msg void OnCbnSelchangeComboCaptype0();
	afx_msg void OnCbnSelchangeComboCaptype1();
	afx_msg void OnCbnSelchangeComboCaptype2();
	afx_msg void OnCbnSelchangeComboCaptype3();
	afx_msg void OnCbnSelchangeComboCaptype4();
	afx_msg void OnCbnSelchangeComboCaptype5();
	afx_msg void OnCbnSelchangeComboCaptype6();
	afx_msg void OnCbnSelchangeComboCaptype7();
	void OnCbnSelchangeComboCaptype(int iNum);
};
