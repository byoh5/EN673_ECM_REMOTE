
// ColormapDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "resource.h"
#include "BtnST.h"
#include "ShadeButtonST.h"
#include "afxcmn.h"

// ====================================================================================================
// <Register>
// ----------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------
// EN673
/*
	0x0080	AWB_WIN1_HSP[27:16],AWB_WIN1_HW[11:0]	
			AWB_WIN1_HSP[27:16]	AWB window horizontal start position register
			AWB_WIN1_HW[11:0]	AWB window horizontal width register

	0x0081	AWB_WIN1_VSP[27:16],AWB_WIN1_VW[11:0]
			AWB_WIN1_VSP[27:16]	AWB window vertical start position register
			AWB_WIN1_VW[11:0]	AWB window vertical width register

	0x0084	AWBLCBCRO_SEL[30],AWBLNOR_SEL[29],AWB_LOCK_SEL[28],AWBL_HTAB_SEL[25:24],AWBLYEDGE_TH[9:0]
			AWBLNOR_SEL[29]		color map no operation select register
								"0" : color map operation on.
								"1" : color map operation off(all bypass).

	0x0086	AWBL_CYCLIP[25:16],AWBL_CYSLICE[9:0]
			AWBL_CYCLIP[25:16]	AWB CY Clip threshold register
			AWBL_CYSLICE[9:0]	AWB CY Slice threshold register

	0x0088	AWBL_CM00_HSP[13:8],AWBL_CM00_HEP[5:0]
						~~~~~~
	0x00C7	AWBL_CM63_HSP[13:8],AWBL_CM63_HEP[5:0]
			AWBL_CM00~AWB63 : AWB color map generation register
*/

// ----------------------------------------------------------------------------------------------------
// EN673
/*
	0x0097	AWB_WIN1_HSP[27:16],AWB_WIN1_HW[11:0]	
			AWB_WIN1_HSP[27:16]	AWB window horizontal start position register
			AWB_WIN1_HW[11:0]	AWB window horizontal width register

	0x0098	AWB_WIN1_VSP[27:16],AWB_WIN1_VW[11:0]
			AWB_WIN1_VSP[27:16]	AWB window vertical start position register
			AWB_WIN1_VW[11:0]	AWB window vertical width register

	0x009B	AWBLCBCRO_SEL[30],AWBLNOR_SEL[29],AWB_LOCK_SEL[28],AWBL_HTAB_SEL[25:24],AWBLYEDGE_TH[9:0]
			AWBLNOR_SEL[29]		color map no operation select register
								"0" : color map operation on.
								"1" : color map operation off(all bypass).

	0x009D	AWBL_CYCLIP[25:16],AWBL_CYSLICE[9:0]
			AWBL_CYCLIP[25:16]	AWB CY Clip threshold register
			AWBL_CYSLICE[9:0]	AWB CY Slice threshold register

	0x009F	AWBL_CM00_HSP[13:8],AWBL_CM00_HEP[5:0]
						~~~~~~
	0x00DE	AWBL_CM63_HSP[13:8],AWBL_CM63_HEP[5:0]
			AWBL_CM00~AWB63 : AWB color map generation register
*/

// ====================================================================================================
// <Define>
// ----------------------------------------------------------------------------------------------------

#define COLORMAPADDRNUM	128

// Picture Control Size
#define COLORMAPSIZE	64	// Width Address
#define COLORMAPSPACE	8	// 한 칸 크기
#define COLORMAPWIDTH	(COLORMAPSIZE*COLORMAPSPACE) // 64*8 = 512, Colormap Drawing (Width)
#define COLORMAPHEIGHT	(COLORMAPSIZE*COLORMAPSPACE) // 64*8 = 512, Colormap Drawing (Width)

#define COLORMAP_HSP	4
#define COLORMAP_VSP	35

// Start Address
#define COLORMAPTABLE_STARTADDR_EN673	0x88

#define COLORMAP_AWBWINDOWMAX		BitMask_11 // (0 ~ 2047)
#define	COLORMAP_AWBTHRESHOLDMAX	BitMask_10  // (0 ~ 1023)


// CColormapDlg 대화 상자
class CColormapDlg : public CDialogEx
{
// 생성입니다.
public:
	CColormapDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_COLORMAP };

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
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnCancel();

	afx_msg void OnBnClickedButtonColormapclose();
	afx_msg void OnBnClickedButtonMinimize();
	afx_msg void OnBnClickedButtonColormapread();
	afx_msg void OnBnClickedRadioColormapspot();
	afx_msg void OnBnClickedRadioColormapfull();
	afx_msg void OnBnClickedCheckColormapbypass();
	afx_msg void OnEnChangeEditColormapyclip();
	afx_msg void OnEnChangeEditColormapyslice();
	afx_msg void OnBnClickedButtonColormapapply();
	afx_msg void OnBnClickedButtonColormapwrite();
	afx_msg void OnBnClickedButtonColormapreset();
	afx_msg void OnBnClickedButtonColormapsave();


// ----------------------------------------------------------------------------------------------------
// Variable
	// Control
	// Close
	CButtonST	m_Btn_Close;
	// Minimize
	CButtonST m_Btn_Minimize;
	// Picture Control
	CStatic		m_Colormap;
	// Read
	CButton		m_Btn_Read;
	// AWB Window
	CButton		m_Radio_Spot;
	CButton		m_Radio_Full;
	CButton		m_Check_Bypass;
	BOOL		m_bAwbInitial;
	BOOL		m_bAwbWindow; // Spot or Full
	// Threshold
	CButton		m_Btn_Apply;
	CEdit		m_Edit_YClip;
	CEdit		m_Edit_YSlice;
	// Write
	CButton		m_Btn_Write;
	// Reset
	CButton		m_Btn_Reset;
	// Save
	CButtonST	m_Btn_Save;


	// ColorMap
	CBitmap		m_bmpColormap;		// Colormap Bitmap
	BOOL*		m_bColormap;		// Colormap Table
	DWORD*		m_dwColormap;		// Colormap Table
	BOOL		m_bAwbWinMode;		// Awb Window Mode (Read할때에만 쓰임)
	UINT		m_uiAwbWinHsp;		// Awb Window Horizontal Start Point (Full 기준)
	UINT		m_uiAwbWinHw;		// Awb Window Horizontal Width
	UINT		m_uiAwbWinVsp;		// Awb Window Vertical Start Point
	UINT		m_uiAwbWinVw;		// Awb Window Vertical Width
	UINT		m_uiAwbWinHspSpot;	// Awb Window Horizontal Start Point (Spot 기준)
	UINT		m_uiAwbWinHwSpot;	// Awb Window Horizontal Width
	UINT		m_uiAwbWinVspSpot;	// Awb Window Vertical Start Point
	UINT		m_uiAwbWinVwSpot;	// Awb Window Vertical Width
	BOOL		m_bBypass;			// Bypass
	UINT		m_uiYClip;			// Y Clip
	UINT		m_uiYSlice;			// Y Slice
	// Reset
	BOOL*		m_bColormapReset;	// Colormap Table
	DWORD*		m_dwColormapReset;	// Colormap Table
	UINT		m_uiAwbWinHspReset;	// Awb Window Horizontal Start Point
	UINT		m_uiAwbWinHwReset;	// Awb Window Horizontal Width
	UINT		m_uiAwbWinVspReset;	// Awb Window Vertical Start Point
	UINT		m_uiAwbWinVwReset;	// Awb Window Vertical Width
	BOOL		m_bBypassReset;		// Bypass
	UINT		m_uiYClipReset;		// Y Clip
	UINT		m_uiYSliceReset;	// Y Slice
	// Communication
	DWORD*		m_dwCommColormap; // Read/Write

	BOOL		m_bColormapClick;
	int			m_iOldPoint;

	// ISP Read/Write
	BOOL		m_bColormapISP;
	int			m_iAddrMin;
	int			m_iAddrMax;
	DWORD		m_dwRxData;
	DWORD*		m_pwRxData;

	BOOL		m_bLoading;

	// Etc
	CBitmap		m_bmpBg;
	CPoint		m_Point;

// ----------------------------------------------------------------------------------------------------
// Function
	void EnableCtrl(BOOL bEnable);

	// Colormap
	void ClickColormap(CPoint* point, BOOL b);
	void ClickColormap(int iX, int iY, BOOL b);

	void SetColormapTable(int iX, int iY, BOOL b);

	void ConvertToRegTable(DWORD *des, BOOL *src);
	void ConvertToDrawTable(BOOL *des, DWORD *src);
	void DrawColormap();

	// Read AWB ISP
	void StartColormapReadThread();
	BOOL ReadColormap_EN673();

	// Write AWB ISP
	void StartColormapWriteThread();
	void WriteColormap_EN673();

	// Write Awb Window
	void StartAwbWindowWriteThread();
	void WriteAwbWindow_EN673();

	// Write Bypass
	void StartAwbBypassWriteThread();
	void WriteAwbBypass_EN673();

	// Apply (Write Threshold)
	void StartColormapApplyThread();
	void ApplyColormap_EN673();

	// Colormap Reset
	void SetColormapReset();
	void ResetColormapData();

	// Colormap File
	void OpenColormap(CString strPath);
	void SaveColormap(CString strPath);

	// AWB Window Mode (Spot/Full)
	void SetAwbWindowMode(BOOL bFlag);
	BOOL m_bSetAwbWin;

	// Bypass
	void SetBypass(BOOL bBypass);
	BOOL m_bSetBypass;

	// Threshold
	void SetYClip(int iYClip);
	BOOL m_bSetYClip;
	void SetYSlice(int iYSlice);
	BOOL m_bSetYSlice;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	// Rx Check flag
	BOOL RxCheck_flag;

	char ch_ip[64];
	char ch_port[64];

	CButtonST m_Btn_Connect;
	afx_msg void OnBnClickedButtonConnect();

	DWORD m_dwEN673BaseAdr;		// EN673 Dongle Base Address


	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void Check_Timer_On();
	void Check_Timer_Off();
	void Connect_Timer_On();
	void Connect_Timer_Off();
	UINT m_CheckTimerID;
	UINT m_ConnectTimerID;

	CProgressCtrl m_Progress_Loading;
};
