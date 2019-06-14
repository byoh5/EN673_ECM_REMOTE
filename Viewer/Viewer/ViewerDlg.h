
// ViewerDlg.h : 헤더 파일
//

#pragma once
#include "resource.h"
#include "BtnST.h"
#include "ShadeButtonST.h"
#include "afxwin.h"
#include "ViewerSet.h"
#include "ViewerSnap.h"
#include "ViewerCapture.h"

// CViewerDlg 대화 상자
class CViewerDlg : public CDialogEx
{
// 생성입니다.
public:
	CViewerDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_VIEWER };

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
	CViewerSet*		m_pDlg_vSet;			// Viewer Setting
	CViewerSnap*	m_pDlg_vSnap;			// Graph Snap
	CViewerCapture*	m_pDlg_vCapture;		// Capture

	CButtonST		m_Btn_Close;
	CButtonST		m_Btn_Minimize;
	CButton			m_Btn_StartViewer;
	CButton			m_Btn_Start;
	CStatic			m_Graph;

	CButton			m_Btn_ShowSet;
	CButton			m_Btn_ShowSnap;
	CButton			m_Btn_ShowCapture;
	BOOL			m_bShowSetDlg;
	BOOL			m_bShowSnapDlg;
	BOOL			m_bShowCaptureDlg;


	virtual void OnCancel();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	afx_msg void OnBnClickedButtonViewerclose();
	afx_msg void OnBnClickedButtonMinimize();
	afx_msg void OnBnClickedButtonViewerStart();
	afx_msg void OnBnClickedButtonViewerstart();
	afx_msg void OnBnClickedButtonShowset();
	afx_msg void OnBnClickedButtonShowsnap();
	afx_msg void OnBnClickedButtonShowcapture();

// ==========================================================================
// DrawViewer
	// Function
	void			StartDrawViewerThread();
	void			DrawViewer();
	void			UpdateGraphBg();
	void			GetPosData(unsigned long ptr0, unsigned long ptr1, long yPos0[], long yPos1[]);		// Get Value of Offset, Scale Slider

	// Variable
	CBitmap			m_bmpGraphBg;	// 실제 배경
	CBitmap			m_bmpGraph;		// 그래프(배경 RGB(0,0,0), 투명)
	CBitmap			m_bmpImage;		// 배경+그래프 최종 이미지.

	uDOUBLE			m_Channel[CHANNELTOTAL][DRAWWIDTH];
	int				m_GrpScale[CHANNELTOTAL];		// Scale Values of Channel 0's Graph
	int				m_GrpOffset[CHANNELTOTAL];		// Offset Values of Channel 0's Graph
	int				m_buffIndex;	// Buff Start
	int				m_iBarH;
	uDOUBLE			m_oBarV[CHANNELTOTAL];
	uDOUBLE			m_oBarVCap[CHANNELTOTAL]; // Capture Graph용...

	// Pen
	CPen			pen[CHANNELTOTAL];
	CPen*			pOldPen[CHANNELTOTAL];
	CPen			penGrid;		// 가로점선
	CPen*			pOldPenGrid;
	CPen			penVBar;		// 세로선
	CPen*			pOldPenVBar;

	// Flag
	BOOL			m_bStartGraph;			// Stop Draw Graph or not
	BOOL			m_bGraphClick;
	BOOL			m_bUpdateGraph;			// 그래프 정보 변경
	BOOL			m_bUpdateCapture;		// Capture 정보 변경

	CPoint			m_Point;
};
