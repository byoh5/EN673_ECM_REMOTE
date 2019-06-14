
// AnalyzeDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "AnalyzeSourceimage.h"
#include "btnst.h"
#include "ShadeButtonST.h"


#define READ_JTAG_SIZE        (1024*1024)

// >> Base Color
// ----------------------------------------------------------------------------------------------------
#if 0
#define DIALOGCOLOR				RGB(73, 85, 118) /*저채도파랑*/
//#define DIALOGCOLOR				RGB(125, 138, 147) /*파란빛 감도는 회색*/
#define	DIALOGSUBCOLOR			RGB(110, 135, 170)
#define DIALOGOUTLINE			RGB(27, 39, 67)
#else
#define DIALOGCOLOR				RGB(117, 94, 72)
#define	DIALOGSUBCOLOR			RGB(170, 140, 110)
#define DIALOGOUTLINE			RGB(66, 46, 26)
#endif
#define TITLECOLOR				RGB(255, 255, 255)

#define DLG_ANALYZE				_T("Analyze")


// CAnalyzeDlg 대화 상자
class CAnalyzeDlg : public CDialogEx
{
// 생성입니다.
public:
	CAnalyzeDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ANALYZE };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.
	virtual void OnCancel();

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
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBnClickedButtonAnalyzeclose();
	afx_msg void OnBnClickedButtonMinimize();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButtonPlayanalyze();

	CButtonST m_Btn_Close;
	CButtonST m_Btn_Minimize;
	CButton m_Btn_PlayAnalyze;
	CButton m_Chk_Vectorscope;
	CButton m_Chk_WaveformR;
	CButton m_Chk_WaveformG;
	CButton m_Chk_WaveformB;
	CButton m_Chk_WaveformY;

	CPoint	m_Point;
	CBitmap	m_bmpBg;

	BOOL	m_bRunAnalyze;
	BOOL	m_bStopAnalyze; // Run중에 일시정지

	CAnalyzeSourceimage* m_pAnalyzeSourceimage;
	CWinThread* m_pThreadEnd;


	void RunAnalyze();
	void StopAnalyze(BOOL bStop); // 일시정지/해제
	void RunEndAnalyzeThread();

	void SaveSubimage(CString strDirectory, CString strJpgTime);

	void SaveValue();

	afx_msg void OnBnClickedCheckVectorscope();
	afx_msg void OnBnClickedCheckWaveformr();
	afx_msg void OnBnClickedCheckWaveformg();
	afx_msg void OnBnClickedCheckWaveformb();
	afx_msg void OnBnClickedCheckWaveformy();
	afx_msg void OnClose();
};
