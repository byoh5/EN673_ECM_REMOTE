
// ViewerDlg.h : ��� ����
//

#pragma once
#include "resource.h"
#include "BtnST.h"
#include "ShadeButtonST.h"
#include "afxwin.h"
#include "ViewerSet.h"
#include "ViewerSnap.h"
#include "ViewerCapture.h"

// CViewerDlg ��ȭ ����
class CViewerDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CViewerDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_VIEWER };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
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
	CBitmap			m_bmpGraphBg;	// ���� ���
	CBitmap			m_bmpGraph;		// �׷���(��� RGB(0,0,0), ����)
	CBitmap			m_bmpImage;		// ���+�׷��� ���� �̹���.

	uDOUBLE			m_Channel[CHANNELTOTAL][DRAWWIDTH];
	int				m_GrpScale[CHANNELTOTAL];		// Scale Values of Channel 0's Graph
	int				m_GrpOffset[CHANNELTOTAL];		// Offset Values of Channel 0's Graph
	int				m_buffIndex;	// Buff Start
	int				m_iBarH;
	uDOUBLE			m_oBarV[CHANNELTOTAL];
	uDOUBLE			m_oBarVCap[CHANNELTOTAL]; // Capture Graph��...

	// Pen
	CPen			pen[CHANNELTOTAL];
	CPen*			pOldPen[CHANNELTOTAL];
	CPen			penGrid;		// ��������
	CPen*			pOldPenGrid;
	CPen			penVBar;		// ���μ�
	CPen*			pOldPenVBar;

	// Flag
	BOOL			m_bStartGraph;			// Stop Draw Graph or not
	BOOL			m_bGraphClick;
	BOOL			m_bUpdateGraph;			// �׷��� ���� ����
	BOOL			m_bUpdateCapture;		// Capture ���� ����

	CPoint			m_Point;
};
