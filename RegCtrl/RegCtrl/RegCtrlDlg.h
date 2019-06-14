
// RegCtrlDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "resource.h"
#include "ShadeButtonST.h"
#include "PictureEx.h"
#include "TreeListCtrl.h"

#include "Define.h"
#include "BtnST.h"

#define WM_REG_ENDLABELEDIT		(WM_USER+9)

// CRegCtrlDlg 대화 상자
class CRegCtrlDlg : public CDialogEx
{
// 생성입니다.
public:
	CRegCtrlDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_REG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnCancel();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButtonRegclose();
	afx_msg void OnBnClickedButtonMinimize();
	afx_msg void OnBnClickedButtonOpenhas();
	afx_msg void OnBnClickedButtonOpenmne();
	afx_msg void OnBnClickedButtonSavehas();
	afx_msg void OnBnClickedButtonSavemne();
	afx_msg void OnCbnEditchangeComboSearch();
	afx_msg void OnCbnSelchangeComboSearch();
	afx_msg void OnCbnSelchangeComboSearchoption();
	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnBnClickedButtonBit(int iNum);
	afx_msg void OnBnClickedButtonBit31();
	afx_msg void OnBnClickedButtonBit30();
	afx_msg void OnBnClickedButtonBit29();
	afx_msg void OnBnClickedButtonBit28();
	afx_msg void OnBnClickedButtonBit27();
	afx_msg void OnBnClickedButtonBit26();
	afx_msg void OnBnClickedButtonBit25();
	afx_msg void OnBnClickedButtonBit24();
	afx_msg void OnBnClickedButtonBit23();
	afx_msg void OnBnClickedButtonBit22();
	afx_msg void OnBnClickedButtonBit21();
	afx_msg void OnBnClickedButtonBit20();
	afx_msg void OnBnClickedButtonBit19();
	afx_msg void OnBnClickedButtonBit18();
	afx_msg void OnBnClickedButtonBit17();
	afx_msg void OnBnClickedButtonBit16();
	afx_msg void OnBnClickedButtonBit15();
	afx_msg void OnBnClickedButtonBit14();
	afx_msg void OnBnClickedButtonBit13();
	afx_msg void OnBnClickedButtonBit12();
	afx_msg void OnBnClickedButtonBit11();
	afx_msg void OnBnClickedButtonBit10();
	afx_msg void OnBnClickedButtonBit9();
	afx_msg void OnBnClickedButtonBit8();
	afx_msg void OnBnClickedButtonBit7();
	afx_msg void OnBnClickedButtonBit6();
	afx_msg void OnBnClickedButtonBit5();
	afx_msg void OnBnClickedButtonBit4();
	afx_msg void OnBnClickedButtonBit3();
	afx_msg void OnBnClickedButtonBit2();
	afx_msg void OnBnClickedButtonBit1();
	afx_msg void OnBnClickedButtonBit0();
	afx_msg void OnBnClickedButtonRegread();
	afx_msg void OnDeltaposSpinRead(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonRegreadall();
	afx_msg void OnBnClickedButtonRegwrite();
	afx_msg void OnDeltaposSpinWrite(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonRegwriteall();
	afx_msg void OnBnClickedButtonClearrx();
	afx_msg void OnBnClickedButtonNewdes();
	afx_msg void OnBnClickedButtonOpendes();
	afx_msg void OnBnClickedButtonSavedes();
	afx_msg void OnEnChangeEditDescription();
	afx_msg void OnDeltaposSpinValue(NMHDR *pNMHDR, LRESULT *pResult);

// ----------------------------------------------------------------------------------------------------
// TreeList
// ----------------------------------------------------------------------------------------------------
	afx_msg void	OnSelChangedTreelist(NMHDR *pNmHdr, LRESULT *pResult);
	afx_msg void	OnBeginLabelEditTreelist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void	OnEndLabelEditTreelist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg LRESULT	OnRegEndLabelEdit(WPARAM wParam, LPARAM lParam);
	CPoint			m_Point;
	CBitmap			m_bmpBg;		// Background

// ----------------------------------------------------------------------------------------------------
// Variable
// Control
	CButtonST		m_Btn_Close;
	CButtonST		m_Btn_Minimize;

	// Tree
	CTreeListCtrl	m_List_Reg;
	// Has
	CButtonST		m_Btn_OpenHas;
	CButtonST		m_Btn_SaveHas;
	CEdit			m_Edit_HasFile;
	// Mne
	CButtonST		m_Btn_OpenMne;
	CButtonST		m_Btn_SaveMne;
	CEdit			m_Edit_MneFile;
	// Des
	CButtonST		m_Btn_NewDes;
	CButtonST		m_Btn_OpenDes;
	CButtonST		m_Btn_SaveDes;
	CEdit			m_Edit_DesFile;
	CEdit			m_Edit_Description;
	// Search
	CComboBox		m_Cbo_Search;
	CComboBox		m_Cbo_SearchOption;
	CButtonST		m_Btn_Search;
	// Bit Button
	CButtonST		m_Btn_Bit[32];
	// Read
	CButton			m_Btn_RegRead;
	CSpinButtonCtrl	m_Spin_Read;
	CComboBox		m_Cbo_ReadStart;
	CComboBox		m_Cbo_ReadEnd;
	CButton			m_Btn_RegReadAll;
	// Write
	CButton			m_Btn_RegWrite;
	CSpinButtonCtrl	m_Spin_Write;
	CComboBox		m_Cbo_WriteStart;
	CComboBox		m_Cbo_WriteEnd;
	CButton			m_Btn_RegWriteAll;
	// Feedback
	CButton			m_Chk_FeedBackRead;
	CButton			m_Chk_FeedBackWrite;

	CStatic			m_Static_Name;

	CSpinButtonCtrl m_Spin_Value;
	CButton			m_Btn_ClearRx;


// ====================================================================================================
// Has, Mne File 관련
// Data
	HAS*			strValuem_Has;			// Has Data
	HAS*			m_Has;					// Mne Data
	MNE*			m_Mne;					// Mne Data
	CString**		m_Des;					// Des Data

	int				m_iAddr;				// 트리에서 마지막으로 표시하는 주소(mne가 없으면 has, mne가 있으면 mne에 맞춤)
											// ㄴ그리고 m_Des 할당 크기
	int				m_iHasNum;				// Has Data Num (파일 크기와 동일)
	int				m_iMneNum;				// Mne Data Num (파일 크기와 동일)
	int				m_iDesNum;				// Des Data Num

	BOOL			m_bOpenHas;				// Has File 열음 (DispRegInfo 함수 동작 후 FALSE)
	BOOL			m_bOpenMne;				// Mne File 열음 (DispRegInfo 함수 동작 후 FALSE)
	BOOL			m_bOpenDes;				// Des File 열음 (DispRegInfo 함수 동작 후 FALSE)
	BOOL			m_bInitTree;			// 트리 초기화 했음...

	BOOL			m_bUpdateHas;			// Has File을 연 후 Has 정보를 변경
	BOOL			m_bUpdateMne;			// Mne File을 연 후 Mne 정보를 변경
	BOOL			m_bUpdateDes;			// Des File을 연 후 Des 정보를 변경

	// HTREEITEM
	HTREEITEM*		m_hItem;				// Root Tree Item
	HTREEITEM		m_hSelItem;				// 현재 선택한 셀 HTREEITEM
	HTREEITEM		m_hOldItem;				// 이전에 선택한 셀 HTREEITEM (Bold 설정시 사용)

	int				m_iSelAddr;				// 현재 선택한 아이템 주소
	int				m_iSelCol;				// 현재 선택한 아이템의 Column

	// strSelTx, strBeforeTx 둘 다 UINT형으로 변경하려고 했었는데
	// _T("") 검사하는 게 있어서... 걍 안바꾸는게 나은것같음.
	CString			m_strSelTx;				// 현재 선택한 셀의 Tx (OnEndLabelEditTreelist에서 검사후 사용)
	CString			m_strBeforeTx;			// Ctrl+Z 할 때 사용. 예전 Tx(FULL TX)

	// R/W Option
	//BOOL			m_bFeedBackRead;
	//BOOL			m_bFeedBackWrite;
	BOOL			m_bRunCmd;				// Read - TRUE, Write - FALSE

	// Search
	int				m_iSearchIdx;
	int				m_iSearchAddrNum;		// m_strSearchAddr 배열 개수 저장
	int				m_iSearchNameNum;		// m_strSearchName 배열 개수 저장
	CString			m_strSearchAddr[10];	// Search 정보 저장
	CString			m_strSearchName[10];	// Search 정보 저장
	void			SearchReg();

	// Loading
	CPictureEx		m_PicLoading;
	BOOL			m_bLoading;

	// Flag & etc
	BOOL			m_bESC;					// EditControl에 Focus가 있을 때 ESC를 누를 경우 TRUE,
	// OnEndLabelEditTreeList에 들어가서 수정 안하고 나옴.

	BOOL			m_bEnter;				// EditControl에 Focus가 있을 때 Enter를 누를 경우 TRUE,
	// OnEndLabelEditTreeList에 들어가서, 값이 바뀌든 안바뀌든 무조건 수정처리.

	BOOL			m_bLabelEdit;			// m_List_Reg의 Edit를 이용해 값을 변경했다는 것을 알려준다.
	// DispTxReg에서 m_strBeforeTx값에 넣을 값이 필요한데
	// EndLabelEdit 함수에서는 어쩔수없이 미리 바뀌기 때문에
	// m_strBeforeTx를 설정해줄 때 함수 내에서 미리 설정해줌

	// 근데 -
	// 지금 생각해 보니... EditLabel 함수가 호출된 후
	// 변경될 값 혹은 변경되지 않을 값을 CString형의 어떤 멤버함수에 담아놓고
	// 변경 할거냐 안할거냐 하는 플래그를 둔 다음,
	// CTreelistWnd에서 처리 후에 다시 돌아와서 DispRxReg를 해도 될것같다...;;

	BOOL			m_bPressedCtrl;			// TxValue 할 때 Ctrl+상,하로 조작한 경우 포커스를 트리컨트롤로 다시 돌려줌

	BOOL			m_bEdit;				// List의 Edit Ctrl이 떠있을 때 Spin을 통한 SelectItem을 막는 플래그.

	int				m_iEditAddr;			// OnEndLabelEditTreelist에서 수정한 주소
	// 하다보니 SelChanged 거치고 OnRegEndLabelEdit를 가기 때문...ㅠㅠ

	BOOL			m_bStopAll;				// Read All, Write All 동작 하던거 중지


// ----------------------------------------------------------------------------------------------------
// Function
// 초기화
	void			InitTreeCtrl(int iNum);

	// 표시
	BOOL			DispRegInfo();
	//void			DispTxReg(int iAddr, CString strTx = _T(""));
	void			DispTxReg(int iAddr);
	void			DispTxReg(int iAddr, CString strTxValue);
	void			DispTxReg(int iAddr, DWORD dwTxValue);
	void			DispRxReg(int iAddr, DWORD dwTxValue);
	void			DispRxReg(int iAddr, CString strRxValue = _T(""));
	void			DispHas();
	void			DispMne();
	void			DispDes();
	void			SetBitButton(); // m_hSelItem 기준으로 Bit Button을 설정함.
	void			SetTooltip(CString str, int iNum); //m_Btn_Bit[i]

	// 파일 Open, Save
	BOOL			OpenHas(CString strPath);	// Set m_Has
	BOOL			OpenMne(CString strPath);	// Set m_Mne
	BOOL			OpenDes(CString strPath);	// Set m_Des
	BOOL			SaveHas(CString strPath);
	void			SaveMne(CString strPath);
	BOOL			SaveDes(CString strPath);

	// Enable Ctrl
	void			EnableBtnBit(int iIndex, BOOL bEnable);
	void			EnableCtrl(BOOL bEnable);
	void			EnableComboSearchCtrl(BOOL bEnable = TRUE);

	// etc
	int				SliceVal(CString strVal, int iStart, int iEnd = -1);
	int				SliceVal(DWORD dwVal, int iStart, int iEnd = -1);
	void			SaveValue();

	// Thread
	void			StartDispRegInfoThread();
	void			StartReadAllThread();
	void			StartWriteAllThread();

	void			OnCtrlZ();

	CStatic			m_Static_Txvalue;

	// TREE 관련
	int				GetChildItemNum(HTREEITEM hParentItem, HTREEITEM hItem);
	HTREEITEM		GetNumChildItem(HTREEITEM hParentItem, UINT iChildNum);
	void			SetBoldItem(HTREEITEM hItem, int iCol, BOOL bFlag);		// 해당되는 아이템 Bold/Unbold

	void			SetSpinRange();

	// Rx Check flag
	BOOL RxCheck_flag;

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
