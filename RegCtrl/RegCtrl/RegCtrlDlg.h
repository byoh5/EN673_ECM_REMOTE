
// RegCtrlDlg.h : ��� ����
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

// CRegCtrlDlg ��ȭ ����
class CRegCtrlDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CRegCtrlDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_REG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
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
// Has, Mne File ����
// Data
	HAS*			strValuem_Has;			// Has Data
	HAS*			m_Has;					// Mne Data
	MNE*			m_Mne;					// Mne Data
	CString**		m_Des;					// Des Data

	int				m_iAddr;				// Ʈ������ ���������� ǥ���ϴ� �ּ�(mne�� ������ has, mne�� ������ mne�� ����)
											// ���׸��� m_Des �Ҵ� ũ��
	int				m_iHasNum;				// Has Data Num (���� ũ��� ����)
	int				m_iMneNum;				// Mne Data Num (���� ũ��� ����)
	int				m_iDesNum;				// Des Data Num

	BOOL			m_bOpenHas;				// Has File ���� (DispRegInfo �Լ� ���� �� FALSE)
	BOOL			m_bOpenMne;				// Mne File ���� (DispRegInfo �Լ� ���� �� FALSE)
	BOOL			m_bOpenDes;				// Des File ���� (DispRegInfo �Լ� ���� �� FALSE)
	BOOL			m_bInitTree;			// Ʈ�� �ʱ�ȭ ����...

	BOOL			m_bUpdateHas;			// Has File�� �� �� Has ������ ����
	BOOL			m_bUpdateMne;			// Mne File�� �� �� Mne ������ ����
	BOOL			m_bUpdateDes;			// Des File�� �� �� Des ������ ����

	// HTREEITEM
	HTREEITEM*		m_hItem;				// Root Tree Item
	HTREEITEM		m_hSelItem;				// ���� ������ �� HTREEITEM
	HTREEITEM		m_hOldItem;				// ������ ������ �� HTREEITEM (Bold ������ ���)

	int				m_iSelAddr;				// ���� ������ ������ �ּ�
	int				m_iSelCol;				// ���� ������ �������� Column

	// strSelTx, strBeforeTx �� �� UINT������ �����Ϸ��� �߾��µ�
	// _T("") �˻��ϴ� �� �־... �� �ȹٲٴ°� �����Ͱ���.
	CString			m_strSelTx;				// ���� ������ ���� Tx (OnEndLabelEditTreelist���� �˻��� ���)
	CString			m_strBeforeTx;			// Ctrl+Z �� �� ���. ���� Tx(FULL TX)

	// R/W Option
	//BOOL			m_bFeedBackRead;
	//BOOL			m_bFeedBackWrite;
	BOOL			m_bRunCmd;				// Read - TRUE, Write - FALSE

	// Search
	int				m_iSearchIdx;
	int				m_iSearchAddrNum;		// m_strSearchAddr �迭 ���� ����
	int				m_iSearchNameNum;		// m_strSearchName �迭 ���� ����
	CString			m_strSearchAddr[10];	// Search ���� ����
	CString			m_strSearchName[10];	// Search ���� ����
	void			SearchReg();

	// Loading
	CPictureEx		m_PicLoading;
	BOOL			m_bLoading;

	// Flag & etc
	BOOL			m_bESC;					// EditControl�� Focus�� ���� �� ESC�� ���� ��� TRUE,
	// OnEndLabelEditTreeList�� ���� ���� ���ϰ� ����.

	BOOL			m_bEnter;				// EditControl�� Focus�� ���� �� Enter�� ���� ��� TRUE,
	// OnEndLabelEditTreeList�� ����, ���� �ٲ�� �ȹٲ�� ������ ����ó��.

	BOOL			m_bLabelEdit;			// m_List_Reg�� Edit�� �̿��� ���� �����ߴٴ� ���� �˷��ش�.
	// DispTxReg���� m_strBeforeTx���� ���� ���� �ʿ��ѵ�
	// EndLabelEdit �Լ������� ��¿������ �̸� �ٲ�� ������
	// m_strBeforeTx�� �������� �� �Լ� ������ �̸� ��������

	// �ٵ� -
	// ���� ������ ����... EditLabel �Լ��� ȣ��� ��
	// ����� �� Ȥ�� ������� ���� ���� CString���� � ����Լ��� ��Ƴ���
	// ���� �Ұų� ���Ұų� �ϴ� �÷��׸� �� ����,
	// CTreelistWnd���� ó�� �Ŀ� �ٽ� ���ƿͼ� DispRxReg�� �ص� �ɰͰ���...;;

	BOOL			m_bPressedCtrl;			// TxValue �� �� Ctrl+��,�Ϸ� ������ ��� ��Ŀ���� Ʈ����Ʈ�ѷ� �ٽ� ������

	BOOL			m_bEdit;				// List�� Edit Ctrl�� ������ �� Spin�� ���� SelectItem�� ���� �÷���.

	int				m_iEditAddr;			// OnEndLabelEditTreelist���� ������ �ּ�
	// �ϴٺ��� SelChanged ��ġ�� OnRegEndLabelEdit�� ���� ����...�Ф�

	BOOL			m_bStopAll;				// Read All, Write All ���� �ϴ��� ����


// ----------------------------------------------------------------------------------------------------
// Function
// �ʱ�ȭ
	void			InitTreeCtrl(int iNum);

	// ǥ��
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
	void			SetBitButton(); // m_hSelItem �������� Bit Button�� ������.
	void			SetTooltip(CString str, int iNum); //m_Btn_Bit[i]

	// ���� Open, Save
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

	// TREE ����
	int				GetChildItemNum(HTREEITEM hParentItem, HTREEITEM hItem);
	HTREEITEM		GetNumChildItem(HTREEITEM hParentItem, UINT iChildNum);
	void			SetBoldItem(HTREEITEM hItem, int iCol, BOOL bFlag);		// �ش�Ǵ� ������ Bold/Unbold

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
