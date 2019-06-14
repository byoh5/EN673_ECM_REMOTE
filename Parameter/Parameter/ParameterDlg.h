
// ParameterDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "resource.h"
#include "BtnST.h"
#include "ShadeButtonST.h"
#include "PictureEx.h"
#include "TreeListCtrl.h"

#define WM_PAR_ENDLABELEDIT		(WM_USER+8)
// CParameterDlg 대화 상자
class CParameterDlg : public CDialogEx
{
// 생성입니다.
public:
	CParameterDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_PARAMETER };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// Event & Window Message
	virtual void OnCancel();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	// Control Message
	afx_msg void OnBnClickedButtonParameterclose();
	afx_msg void OnBnClickedButtonMinimize();
	afx_msg void OnBnClickedButtonOpenpar();
	afx_msg void OnBnClickedButtonSavepar();
	afx_msg void OnBnClickedButtonParameterkeyset();
	afx_msg void OnDeltaposSpinParvalue(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonParread();
	afx_msg void OnDeltaposSpinReadpar(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonParreadall();
	afx_msg void OnBnClickedButtonEepreadPar();
	afx_msg void OnBnClickedButtonParwrite();
	afx_msg void OnDeltaposSpinWritepar(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonParwriteall();
	afx_msg void OnBnClickedButtonEepwritePar();
	afx_msg void OnBnClickedButtonParclearrx();
	afx_msg void OnBnClickedButtonSavehex();
	afx_msg void OnCbnSelchangeComboParmovename();
	afx_msg void OnEnChangeEditPardescription();
	afx_msg void OnBeginLabelEditTreelist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelChangedTreelist(NMHDR *pNmHdr, LRESULT *pResult);
	afx_msg void OnEndLabelEditTreelist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg LRESULT	OnParEndLabelEdit(WPARAM wParam, LPARAM lParam);

	CButtonST		m_Btn_Close;
	CButtonST		m_Btn_Minimize;
	CEdit			m_Edit_ParFile;
	CButtonST		m_Btn_OpenPar;
	CButtonST		m_Btn_SavePar;
	CButton			m_Btn_ParKeyEnable;
	CEdit			m_Edit_Description;
	CComboBox		m_Cbo_Movename;
	CStatic			m_Static_TxValue;
	CSpinButtonCtrl m_Spin_TxValue;
	CButton			m_Btn_Read;
	CSpinButtonCtrl m_Spin_ReadPar;
	CComboBox		m_Cbo_ReadStart;
	CComboBox		m_Cbo_ReadEnd;
	CButton			m_Btn_ReadAll;
	CButton			m_Btn_EepRead;
	CButton			m_Btn_Write;
	CSpinButtonCtrl m_Spin_WritePar;
	CComboBox		m_Cbo_WriteStart;
	CComboBox		m_Cbo_WriteEnd;
	CButton			m_Btn_WriteAll;
	CButton			m_Btn_EepWrite;
	CButton			m_Chk_FeedBackRead;
	CButton			m_Chk_FeedBackWrite;
	CButton			m_Btn_ClearRx;
	CButton			m_Btn_SaveHex;
	CProgressCtrl	m_Progress_Loading;
	CPictureEx		m_PicLoading;

	//Tree
	CTreeListCtrl	m_List_Parameter;

	CPoint			m_Point;
	CBitmap			m_bmpBg;		// Background
// ====================================================================================================
// Parameter
	// Data
	CString*		m_Des;			// Description Data

	int				m_iAddr;		// Max Address

	BOOL			m_bUpdatePar;	// Parameter가 변경된 후 파일을 저장하지 않은 채 다른 파일을 열거나
	// 프로그램을 종료하는 등의 경우 파일 저장 여부를 물어보는
	// 메세지 박스를 띄우기 위한 플래그.
	// 값이 변경되지 않도록 조정.
	// HTREEITEM
	HTREEITEM*		m_hItem;		// Root Tree Item
	HTREEITEM		m_hSelItem;		// 현재 선택한 셀 HTREEITEM
	HTREEITEM		m_hOldItem;		// 이전에 선택한 셀 HTREEITEM (Bold 설정시 사용)

	int				m_iSelCol;		// 현재 선택한 Column

	CString			m_strSelTx;		// 현재 선택한 아이템의 Column

	CString			m_strBeforeTx;

	BOOL			m_bRunCmd;		// Read - TRUE, Write - FALSE.
	// 펌웨어에서 커맨드가 왔을 때 이 전에 뭐였는지 확인하고 적절한 대처를 하기 위함.
	// Parameter만 해당하며,
	// EEP Read는 플래그 확인 없이,
	// Write는 ...

	// Description

	// Flag & etc
	BOOL			m_bESC; 		// ESC를 누른 후 OnEndLabelEditTreeList으로 갔을 때
	BOOL			m_bEnter;		// Enter
	BOOL			m_bEdit;		// Edit로 수정중
	int				m_iEditAddr;
	BOOL			m_bLabelEdit;
	BOOL			m_bPressedCtrl;

	BOOL			m_bSuccessEEPRead;
	BOOL			m_bSuccessEEPWrite;

	// Loading
	BOOL			m_bLoading;

	BOOL			m_bStopAll;				// Read All, Write All 동작 하던거 중지

// ====================================================================================================
// Function
	// File Open, Save
	BOOL			OpenPar(CString strPath);
	BOOL			SavePar(CString strPath);
	void			SaveHex(CString strPath);

	// Disp Tx, Rx
	void			DispTxPar(DWORD dwAddr, DWORD dwData);
	BOOL			DispFullTxPar(int iAddr, DWORD64 dwData);
	BOOL			DispFullTxPar(HTREEITEM hItem, DWORD64 dwData);
	void			DispRxPar(DWORD dwAddr, DWORD dwData);

	// Control
	void			EnableCtrl(BOOL bEnable); // 컨트롤 활성화/비활성화
	void			InitComboBox();	// 콤보박스 초기화(나중에 빼야함ㅎㅎ;)

	// Start Thread
	void			StartReadAllThread();
	void			StartWriteAllThread();
	void			StartEEPReadThread();
	void			StartEEPWriteThread();
	void			StartSaveHexThread();

	// etc
	void			SaveValue(); // Ini File 저장
	void			OnCtrlZ();

	void			SetItemText(HTREEITEM hItem, COLORREF uColor);
	BOOL			GetItemToAddress(DWORD dwAddr, HTREEITEM* phItem);

	// SetSpinRange
	void			SetSpinRange();

	// Description
	void			DispDes();

	void			SetBoldItem(HTREEITEM hItem, int iCol, BOOL bFlag);

	CString			m_strKey;
	CString			m_strKeyPw;
	SHORT			m_bParameterKey;	// -1 : 연결확인 안됨
									//  0 : 연결실패
									//  1 : 연결

	void			OpenKeyFile();
	void			SaveKeyFile();


	void			EnableParameter(BOOL bEnable);


	BOOL			m_bSaveHex;
	DWORD			m_dwCommAddr;
	DWORD			m_dwCommData;


	// Server IP, Port
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
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
