#pragma once
#include "afxwin.h"
#include "resource.h"
#include "BtnST.h"


// CAnalyzeSourceimage 대화 상자입니다.

class CAnalyzeSourceimage : public CDialogEx
{
	DECLARE_DYNAMIC(CAnalyzeSourceimage)

public:
	CAnalyzeSourceimage(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CAnalyzeSourceimage();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ANALYZE_SOURCEIMAGE };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CButton m_Btn_Play;
	CButton m_Btn_CaptureOne;
	CButton m_Btn_CaptureCon;
	CButton m_Btn_OriginalSize;
	CStatic m_Pic_Sourceimage;
	
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	afx_msg void OnEnterSizeMove();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnClose();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButtonAnalyzePlay();
	afx_msg void OnBnClickedButtonAnalyzeCaptureone();
	afx_msg void OnBnClickedButtonAnalyzeCapturecon();
	afx_msg void OnBnClickedButtonAnalyzeOriginalsize();

	void SaveSourceimage();

	CBitmap* m_bmpImage;
	UINT8* m_uiImagedata;

	int m_iImageWidth;
	int m_iImageHeight;
	int m_iImagedataSize;

	BOOL m_bCapture;
	BOOL m_bCaptureOne;
	CButton m_Chk_Capture;
	CStatic m_Static_CapturePath;

	CButtonST m_Btn_OpenPath;
	afx_msg void OnBnClickedButtonOpenpath();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
