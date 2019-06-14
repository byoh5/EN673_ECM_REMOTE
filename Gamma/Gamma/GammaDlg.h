
// GammaDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "resource.h"
#include "BtnST.h"
#include "ShadeButtonST.h"
#include "afxcmn.h"


// Source Code Define
#define CHANGEGAMMA		1
#define USEGAMMAREAD	0

//#define Gamma(X, GAMMA, TARGET, TLEVEL, TOFF) (((X+TOFF)>=Target) ? 1023 : (pow(((X+TOFF)/TARGET),GAMMA))*1024)*TLEVEL/1024
//#define GAMMA(X, GAMMA, TARGET) (1024*(pow((((float)(X)/(TARGET)),(GAMMA)))))
#define GAMMA(X, GAMMA, TARGET) ( ((X) >= TARGET) ? 1023 : ((pow(((float)(X)/(TARGET)),(GAMMA)))*1024) )

// ====================================================================================================
// define
// ----------------------------------------------------------------------------------------------------
#define	NUM_PLATFORM			11	// Platform 개수
#define EN572_GAMMAREGNUM		8
#define EN573_GAMMAREGNUM		8
#define EN673_GAMMAREGNUM		9
#if INSERT_EN674
#define EN674_GAMMAREGNUM		-1
#endif
#define EN771_GAMMAREGNUM		9
#define EN773_GAMMAREGNUM		7
#define EN773A_GAMMAREGNUM		7
#define EN777_GAMMAREGNUM		9
#define EN778_GAMMAREGNUM		9
#define EN779_GAMMAREGNUM		9
#define EN970_GAMMAREGNUM		-1

const int GAMMAREGNUM[NUM_PLATFORM] = {
	EN572_GAMMAREGNUM,
	EN573_GAMMAREGNUM,
	EN673_GAMMAREGNUM,
#if INSERT_EN674
	EN674_GAMMAREGNUM,
#endif
	EN771_GAMMAREGNUM,
	EN773_GAMMAREGNUM,
	EN773A_GAMMAREGNUM,
	EN777_GAMMAREGNUM,
	EN778_GAMMAREGNUM,
	EN779_GAMMAREGNUM,
	EN970_GAMMAREGNUM
};

// ====================================================================================================
// X Step
// ----------------------------------------------------------------------------------------------------
// X값
// EN673	: [17] 0 2 4 8 16 32 64 128 192 256 320 384 512 640 768 896 1023

// ====================================================================================================
// <Register>
// ----------------------------------------------------------------------------------------------------
// EN673
// 0x0106	YGMA_ON[31],CGMA_ON[30],YGMY_00[25:16],YGMY_01[9:0]
// 0x0107	YGMY_02[25:16],YGMY_03[9:0]
// 0x0108	YGMY_04[25:16],YGMY_05[9:0]
// 0x0109	YGMY_06[25:16],YGMY_07[9:0]
// 0x010A	YGMY_08[25:16],YGMY_09[9:0]
// 0x010B	YGMY_10[25:16],YGMY_11[9:0]
// 0x010C	YGMY_12[25:16],YGMY_13[9:0]
// 0x010D	YGMY_14[25:16],YGMY_15[9:0]
// 0x010E	YGMY_16[25:16]

// 0x0110	CGMY_00[25:16],CGMY_01[9:0]
// 0x0111	CGMY_02[25:16],CGMY_03[9:0]
// 0x0112	CGMY_04[25:16],CGMY_05[9:0]
// 0x0113	CGMY_06[25:16],CGMY_07[9:0]
// 0x0114	CGMY_08[25:16],CGMY_09[9:0]
// 0x0115	CGMY_10[25:16],CGMY_11[9:0]
// 0x0116	CGMY_12[25:16],CGMY_13[9:0]
// 0x0117	CGMY_14[25:16],CGMY_15[9:0]
// 0x0118	CGMY_16[25:16]

// ====================================================================================================
// CGammaGraph
class CGammaGraph
{
public:
	CGammaGraph();
	~CGammaGraph();

	// Function
	void UpdateGraph(); // 모든 동작이 끝나고 외부에서 호출..

	// Set
	void SetPictureCtrl(CStatic* pGraph);
	void SetGammaStep(UINT uiXStep, UINT* iXPoint);

	void SetGammaVal(float fGamma, float fTarget = -1);	// Gamma Value를 조정하며
	void SetGammaY(UINT uiXStep, int iYValue = -1); // 2번째 인자를 넣지 않으면 x값에 따라 default value 적용
	void SetGammaZoomRate(int iZoomRate);

	// Get
	float GetGammaVal();
	UINT GetGammaY(UINT uiXStep);
	int GetGammaZoomRate();

	BOOL ClickPoint(int iX, int iY);
	BOOL ClickPoint(CPoint point);
	void MovePoint(int iX, int iY);
	void MoveGraph(int iFirstX, int iFirstY, int iX, int iY);

	// Variable
	CStatic*	m_pGraph; // Picture Control

	CPoint*		m_pGrpPoint;
	float		m_fGammaVal;
	float		m_fGammaTarget;
	UINT		m_uiXStep;

	int			m_iZoomRate;	// Default : 100
	int			m_uiPointSel;	// FALSE : -1
	CPoint		m_ptMove;		// Move Graph(default : 0, 0)
	CPoint		m_ptMoveStart;	// Move Graph Start
};


// CGammaDlg 대화 상자
class CGammaDlg : public CDialogEx
{
// 생성입니다.
public:
	CGammaDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_GAMMA };

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
	CButtonST m_Btn_Close;
	CButtonST m_Btn_Minimize;
	CStatic m_Pic_GammaGraph;
	CEdit m_Edit_GammaValue;
	CEdit m_Edit_GammaTarget;
	CButton m_Btn_GammaApply;
	CComboBox m_Cbo_GammaTable;
	CButton m_Btn_GammaWrite;
	CButtonST m_Btn_GammaLoad;
	CButtonST m_Btn_GammaSave;
	CComboBox m_Cbo_GammaZoom;

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnCancel();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnBnClickedButtonGammaclose();
	afx_msg void OnBnClickedButtonMinimize();
	afx_msg void OnBnClickedButtonGammaapply();
	afx_msg void OnCbnSelchangeComboGammatable();
	afx_msg void OnBnClickedButtonGammawrite();
	afx_msg void OnBnClickedButtonGammaload();
	afx_msg void OnBnClickedButtonGammasave();
	afx_msg void OnCbnSelchangeComboGammazoom();
	void OnChangeGammazoom(); // OnCbnEditchangeComboGammazoom 대신임.

	CPoint		m_Point;

// ----------------------------------------------------------------------------------------------------
// Variable
	// Gamma
	CGammaGraph	m_Gamma;

	// Mouse Event
	BOOL		m_bPointMoveOn;
	BOOL		m_bGraphMoveOn;
	CPoint		m_ptLDownPoint;

	// ISP Read, Write 관련
	BOOL		m_bGammaISP;

	DWORD*		m_pwRxData;

	int			m_iAddrMin;
	int			m_iAddrMax;

	// 실행취소(Undo:Ctrl+Z/Redo:Ctrl+Y)
#define UNDOMAX		10
	typedef struct tagGAMMAUNDO
	{
		int iStep;
		int iValue;
	} GAMMAUNDO;
	GAMMAUNDO*	m_iUndo;
	int			m_iUndoNum; // Undo Max
	int			m_iUndoCnt;

	void	InitUndo();
	void	SetUndo(int iStep, int iValue); // 작업내역 저장
	void	OnUndo(); // 예전값 복구
	void	OnRedo();

	// Rx Check flag
	BOOL RxCheck_flag;

// ----------------------------------------------------------------------------------------------------
	// Function
	void SetPlatform();
	void SetGammaTable(UINT uiPlatform);

	void StartLoadingThreadGamma();
	BOOL m_bLoading;

	// Gamma Write
	void StartGammaWriteThread();
	void GammaWrite_EN673();
	//void GammaWrite_EN771();

	// Gamma Load, Save
	BOOL LoadGamma(CString strPath);
	BOOL SaveGamma(CString strPath);

	// Save Value
	void SaveValue();

	void EnableCtrl(BOOL bEnable);

	char ch_ip[64];
	char ch_port[64];
	CButtonST m_Btn_Connect;
	afx_msg void OnBnClickedButtonConnect();

	DWORD m_dwEN673BaseAdr;		// EN673 Dongle Base Address

	CString		m_strKey;
	CString		m_strKeyPw;
	void OpenKeyFile();
	void SaveKeyFile();

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void Check_Timer_On();
	void Check_Timer_Off();
	void Connect_Timer_On();
	void Connect_Timer_Off();
	UINT m_CheckTimerID;
	UINT m_ConnectTimerID;
	CProgressCtrl m_Progress_Loading;
};
