
// ViewerDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "Viewer.h"
#include "ViewerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BYTE	rxData[1024];

// Thread
UINT				DrawViewerThread(LPVOID pParam);

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CViewerDlg ��ȭ ����



CViewerDlg::CViewerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CViewerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ECM);
}


void CViewerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_VIEWERCLOSE, m_Btn_Close);
	DDX_Control(pDX, IDC_BUTTON_MINIMIZE, m_Btn_Minimize);
	DDX_Control(pDX, IDC_BUTTON_VIEWER_START, m_Btn_StartViewer);
	DDX_Control(pDX, IDC_BUTTON_VIEWERSTART, m_Btn_Start);
	DDX_Control(pDX, IDC_BUTTON_SHOWSET, m_Btn_ShowSet);
	DDX_Control(pDX, IDC_VIEWER_GRAPH, m_Graph);
	DDX_Control(pDX, IDC_BUTTON_SHOWSNAP, m_Btn_ShowSnap);
	DDX_Control(pDX, IDC_BUTTON_SHOWCAPTURE, m_Btn_ShowCapture);
}

BEGIN_MESSAGE_MAP(CViewerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_VIEWERCLOSE, &CViewerDlg::OnBnClickedButtonViewerclose)
	ON_BN_CLICKED(IDC_BUTTON_MINIMIZE, &CViewerDlg::OnBnClickedButtonMinimize)
	ON_BN_CLICKED(IDC_BUTTON_VIEWERSTART, &CViewerDlg::OnBnClickedButtonViewerstart)
	ON_BN_CLICKED(IDC_BUTTON_SHOWSET, &CViewerDlg::OnBnClickedButtonShowset)
	ON_BN_CLICKED(IDC_BUTTON_SHOWSNAP, &CViewerDlg::OnBnClickedButtonShowsnap)
	ON_BN_CLICKED(IDC_BUTTON_SHOWCAPTURE, &CViewerDlg::OnBnClickedButtonShowcapture)
	ON_WM_MOVE()
	ON_BN_CLICKED(IDC_BUTTON_VIEWER_START, &CViewerDlg::OnBnClickedButtonViewerStart)
END_MESSAGE_MAP()


// CViewerDlg �޽��� ó����

BOOL CViewerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	SetWindowText(DLG_VIEWER);

	int x = ReadIni(SEC_WININFO, KEY_VIEWDLGLEFT, DEF_VIEWDLGLEFT);
	int y = ReadIni(SEC_WININFO, KEY_VIEWDLGTOP, DEF_VIEWDLGTOP);
	SetWindowPos(NULL, x, y, 552, 600, NULL);
	//this->SetWindowPos(NULL, 0, 0, 520, 600, NULL);

// ----------------------------------------------------------------------------------------------------
// Control
	// Close
	pViewerDlg = this;
	m_Btn_Close.DrawBorder(FALSE);
	m_Btn_Close.SetColor(CButtonST::BTNST_COLOR_BK_OUT, DIALOGCOLOR);
	m_Btn_Close.SetColor(CButtonST::BTNST_COLOR_BK_IN, DIALOGSUBCOLOR);

	// Minimize
	m_Btn_Minimize.DrawBorder(FALSE);
	m_Btn_Minimize.SetColor(CButtonST::BTNST_COLOR_BK_OUT, DIALOGCOLOR);
	m_Btn_Minimize.SetColor(CButtonST::BTNST_COLOR_BK_IN, DIALOGSUBCOLOR);

// ----------------------------------------------------------------------------------------------------
// Create Sub Dialog
	CRect rect;
	this->GetWindowRect(&rect);

	m_pDlg_vSet = new CViewerSet();
	m_pDlg_vSnap = new CViewerSnap();
	m_pDlg_vCapture = new CViewerCapture();

	m_pDlg_vSet->Create(IDD_VIEWER_SET, this);
	m_pDlg_vSnap->Create(IDD_VIEWER_SNAP, this);
	m_pDlg_vCapture->Create(IDD_VIEWER_CAPTURE, this);

	m_pDlg_vSet->SetWindowPos(NULL, rect.right, rect.top, 350, 280, SWP_SHOWWINDOW | SWP_NOZORDER);
	m_pDlg_vSnap->SetWindowPos(NULL, rect.left, rect.bottom, 552, 155, SWP_SHOWWINDOW | SWP_NOZORDER);

	m_pDlg_vSet->GetWindowRect(&rect);
	m_pDlg_vCapture->SetWindowPos(NULL, rect.left, rect.bottom + 1, 350, 290, SWP_SHOWWINDOW | SWP_NOZORDER);

	m_pDlg_vSet->ShowWindow(SW_HIDE);
	m_pDlg_vSnap->ShowWindow(SW_HIDE);
	m_pDlg_vCapture->ShowWindow(SW_HIDE);

	m_bShowSetDlg = FALSE;
	m_bShowSnapDlg = FALSE;
	m_bShowCaptureDlg = FALSE;

// ----------------------------------------------------------------------------------------------------
// Variable
	int i = 0;
	int j = 0;
	m_bStartGraph = TRUE;		// Stop Draw Graph or not
	m_bGraphClick = FALSE;

	m_buffIndex = 0;		// Buffer of Draw
	m_iBarH = 200;		// ����Bar �ʱⰪ.

	for (i = 0; i < CHANNELTOTAL; i++)
	{
		m_oBarV[i].m_int = 0;
		for (j = 0; j < DRAWWIDTH; j++)
		{
			m_Channel[i][j].m_int = 0;
		}
	}

// ----------------------------------------------------------------------------------------------------
// Control
	// Viewer Control
	m_Graph.SetWindowPos(NULL, VIEW_HSP, VIEW_VSP, DRAWWIDTH, DRAWHEIGHT, SWP_SHOWWINDOW | SWP_NOZORDER);

	// Button
	//m_Btn_Start.SetBitmaps(IDB_STOP, RGB(255,0,255));
	m_Btn_Start.SetWindowTextW(_T("��"));

// ----------------------------------------------------------------------------------------------------
// ETC
	// CreatePen
	penGrid.CreatePen(PS_DOT, 1, RGB(80, 80, 80));
	penVBar.CreatePen(PS_SOLID, 1, RGB(255, 255, 255));

// ----------------------------------------------------------------------------------------------------
// Initialize DrawViewer
	CDC* pDC = m_Graph.GetWindowDC();

	// Create Bitmap
	m_bmpGraphBg.CreateCompatibleBitmap(pDC, DRAWWIDTH, DRAWHEIGHT);
	m_bmpGraph.CreateCompatibleBitmap(pDC, DRAWWIDTH, DRAWHEIGHT);
	m_bmpImage.CreateCompatibleBitmap(pDC, DRAWWIDTH, DRAWHEIGHT);

	CDC dcImage;
	dcImage.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap = (CBitmap*)dcImage.SelectObject(&m_bmpImage);

	dcImage.FillSolidRect(0, 0, DRAWWIDTH, DRAWHEIGHT, ::GetSysColor(COLOR_3DFACE));
	//dcImage.BitBlt(0, 0, DRAWWIDTH, DRAWHEIGHT, pDC , 0, 0, SRCCOPY);

	dcImage.SelectObject(pOldBitmap);
	m_Graph.ReleaseDC(pDC);

	//Flag
	m_bUpdateGraph = TRUE; // ó�� ������ �� �ʱ�ȭ�� ���� TRUE�� ����
	m_bUpdateCapture = TRUE;

	// ----------------------------------------------------------------------------------------------------
	// Init Start
	int check = 0;
	check = ReadIni(SEC_SETTING, KEY_VIEWERSTART, DEF_VIEWERSTART);
	if (check == 1)
		OnBnClickedButtonViewerStart();

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CViewerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

BOOL CViewerDlg::PreTranslateMessage(MSG* pMsg)
{
	// Default Window Message
	if (DefaultWindowMessage(pMsg))	return TRUE;
	else							return CDialog::PreTranslateMessage(pMsg);
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CViewerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		// �ƿ� ����
		// Top
		CPaintDC dc(this);
		CRect rect;
		CWnd* pWnd = this;
		pWnd->GetWindowRect(rect);
		int iWidth = rect.Width();
		int iHeight = rect.Height();
		dc.FillSolidRect(0, 0, iWidth, 25, DIALOGCOLOR);

		// OutLine
		CPen NewPen(PS_SOLID, 2, DIALOGCOLOR);
		//CPen NewPen(PS_SOLID, 2, DIALOGOUTLINE);
		CPen* pOldPen = dc.SelectObject(&NewPen);
		/*
		dcBg.MoveTo(0,0);
		dcBg.LineTo(iWidth-1,0);
		dcBg.LineTo(iWidth-1,iHeight-1);
		dcBg.LineTo(0,iHeight-1);
		dcBg.LineTo(0,0);
		*/
		dc.MoveTo(1, 1);
		dc.LineTo(iWidth - 1, 1);
		dc.LineTo(iWidth - 1, iHeight - 1);
		dc.LineTo(1, iHeight - 1);
		dc.LineTo(1, 1);

		CPen NewPen2(PS_SOLID, 1, DIALOGOUTLINE);
		dc.SelectObject(NewPen2);

		dc.MoveTo(0, 0);
		dc.LineTo(iWidth - 1, 0);
		dc.LineTo(iWidth - 1, iHeight - 1);
		dc.LineTo(0, iHeight - 1);
		dc.LineTo(0, 0);

		dc.SelectObject(pOldPen);

		// Font
		LOGFONT lf;
		::ZeroMemory(&lf, sizeof(lf));
		lf.lfHeight = 15;
		lf.lfWeight = 700;
		wsprintf(lf.lfFaceName, _T("%s"), _T("Arial"));
		CFont NewFont;
		NewFont.CreateFontIndirectW(&lf);
		CFont* pOldFont = dc.SelectObject(&NewFont);

		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(TITLECOLOR);

		dc.TextOutW(10, 6, DLG_VIEWER);

		dc.SelectObject(pOldFont);
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CViewerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CViewerDlg::OnCancel()
{
	pViewerSet->SaveValue();

	NetClo(ConnectSocket);
	ConnectSocket = NULL;

	m_pDlg_vSet->DestroyWindow();
	delete m_pDlg_vSet;

	m_pDlg_vSnap->DestroyWindow();
	delete m_pDlg_vSnap;

	m_pDlg_vCapture->DestroyWindow();
	delete m_pDlg_vCapture;

	CDialogEx::OnCancel();
}


void CViewerDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	BOOL bX = INMIDDLE(point.x, VIEW_HSP + 1, VIEW_HSP + DRAWWIDTH - 2);
	BOOL bY = INMIDDLE(point.y, VIEW_VSP + 1, VIEW_VSP + DRAWHEIGHT - 2);

	if (bX && bY)
	{
		if (ConnectSocket)
		{
			SetCapture();
			m_iBarH = point.x - VIEW_HSP;
			m_bGraphClick = TRUE;
		}
		else
		{
			m_bGraphClick = FALSE;
		}
	}

	SetCapture();
	m_Point = point;

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CViewerDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	BOOL bX = INMIDDLE(point.x, VIEW_HSP + 1, VIEW_HSP + DRAWWIDTH - 2);
	BOOL bY = INMIDDLE(point.y, VIEW_VSP + 1, VIEW_VSP + DRAWHEIGHT - 2);

	if (m_bGraphClick)
	{
		if (bX && bY)
		{
			m_iBarH = point.x - VIEW_HSP;
		}
		else
		{
			m_bGraphClick = FALSE;
			ReleaseCapture();
		}
		return;
	}

	if (this == GetCapture())
	{
		CRect rcDialog;
		GetWindowRect(&rcDialog);

		int x = rcDialog.left + point.x - m_Point.x;
		int y = rcDialog.top + point.y - m_Point.y;

		SetWindowPos(NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		WriteIni(SEC_WININFO, KEY_VIEWDLGLEFT, x);
		WriteIni(SEC_WININFO, KEY_VIEWDLGTOP, y);

// ----------------------------------------------------------------------------------------------------
// Set Sub Dialog
		CRect rectSet;
		CRect rectSnap;
		CRect rectCapture;

		pViewerSet->GetWindowRect(&rectSet);
		pViewerSet->MoveWindow(rcDialog.right, rcDialog.top,
			rectSet.Width(), rectSet.Height(), TRUE);

		pViewerSnap->GetWindowRect(&rectSnap);
		pViewerSnap->MoveWindow(rcDialog.left, rcDialog.bottom,
			rectSnap.Width(), rectSnap.Height(), TRUE);

		pViewerCapture->GetWindowRect(&rectCapture);
		pViewerCapture->MoveWindow(rcDialog.right, rcDialog.top + rectSet.Height() + 1,
			rectCapture.Width(), rectCapture.Height(), TRUE);
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void CViewerDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_bGraphClick)
	{
		m_bGraphClick = FALSE;
	}

	ReleaseCapture();

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CViewerDlg::OnBnClickedButtonViewerclose()
{
	CViewerDlg::OnCancel();
}


void CViewerDlg::OnBnClickedButtonMinimize()
{
	ShowWindow(SW_MINIMIZE);
}


void CViewerDlg::StartDrawViewerThread()
{
	// DrawViewerThread
	g_pDrawViewerThread = AfxBeginThread(DrawViewerThread, GetSafeHwnd());
}

// ====================================================================================================
// DrawViewerThread
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
UINT DrawViewerThread(LPVOID pParam)
{
	bGraphFlag = FALSE;

	while (ConnectSocket)
	{
		bGraphFlag = TRUE;
		if (bGraphFlag)	pViewerDlg->DrawViewer();
		//if (bGraphFlag | pViewerDlg->m_bStartGraph)	pViewerDlg->DrawViewer();
		Sleep(1);
	}

	return 0L;
}

// ====================================================================================================
// CViewerDlg::DrawViewer
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CViewerDlg::DrawViewer()
{
/*
	if (!m_ShowDlg)
	{
		bGraphFlag = FALSE;
		return;
	}
*/
	// ----------------------------------------------------------------------------------------------------
	// 1. �غ�
	int	i = 0;
	int	j = 0;
	CStatic* pGraph = &m_Graph;

	// Load rxData
	BYTE byData[1024] = { 0, };
	BYTE* flag;

	if (m_bStartGraph)
	{
		do{
			getDataFromRemote(ConnectSocket, tx_addr, 4, WBCOM, &flag);
			Sleep(10);
		} while (((UINT32)flag & 0X0000ffff) != 0xc002);
		getDataFromRemote(ConnectSocket, tx_addr, 36, WBCOM, &rxData);
	}

	// 5Channel
	if (pViewerSet->m_bChMode)
	{
		for (i = 0; i<(4 * 5 + 1); i++)	{ byData[i] = rxData[i + 1]; }
	}
	// 8Channel
	else
	{
		for (i = 0; i<(4 * 8 + 1); i++)	{ byData[i] = rxData[i + 1]; }
	}
	bGraphFlag = FALSE; // �ʿ��� ������ �� �ް�, ���� ������ �ޱ� ���� FALSE


	// DC
	CDC* pDC = m_Graph.GetWindowDC();
	CDC dc;
	dc.CreateCompatibleDC(pDC);

	// Bitmap
	CBitmap bmpBuffer;
	bmpBuffer.CreateCompatibleBitmap(pDC, DRAWWIDTH, DRAWHEIGHT);
	CBitmap* pOldBitmap = (CBitmap*)dc.SelectObject(&bmpBuffer);

	// ----------------------------------------------------------------------------------------------------
	// 2. �׸���
	CRect rect;
	pGraph->GetClientRect(&rect);

	// Capture
	if (m_bUpdateCapture)
		UpdateGraphBg();

	// Paint BackGround
	CDC dcGraphBg;
	dcGraphBg.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmapGraphBg = (CBitmap*)dcGraphBg.SelectObject(&m_bmpGraphBg);

	dc.BitBlt(0, 0, DRAWWIDTH, DRAWHEIGHT, &dcGraphBg, 0, 0, SRCCOPY);
	dcGraphBg.SelectObject(pOldBitmapGraphBg);

	// Graph
	// ���� ����
	int	buffCnt = 0;
	int	buffPtr = 0;
	int	buffSP = 0;

	if (m_buffIndex >= DRAWWIDTH)
		m_buffIndex = 0;

	if (m_buffIndex >= DRAWWIDTH)
		buffSP = 0;
	else
		buffSP = m_buffIndex + 1;

	BYTE tByte0 = 0;
	BYTE tByte1 = 0;
	BYTE tByte2 = 0;
	BYTE tByte3 = 0;

	//int	rxCnt = -1;
	int	rxCnt = 0;
	for (i = 0; i < CHANNELTOTAL; i++)
	{
		tByte0 = byData[++rxCnt];
		tByte1 = byData[++rxCnt];
		tByte2 = byData[++rxCnt];
		tByte3 = byData[++rxCnt];
		m_Channel[i][m_buffIndex].m_int = (tByte0 << 24) |
			(tByte1 << 16) |
			(tByte2 << 8) |
			(tByte3);
	}

	// Graph Bitmap ������.
	CDC dcGraph;
	dcGraph.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmapGraph = (CBitmap*)dcGraph.SelectObject(&m_bmpGraph);

	long yPos0[CHANNELTOTAL] = { 0, };
	long yPos1[CHANNELTOTAL] = { 0, };
	// Graph�� Update ���� ���(����, Scale, Offset ����) �׷����� �ٽ� �׸�
	if (m_bStartGraph && (!m_bUpdateGraph))
	{
		dcGraph.BitBlt(-1, 0, DRAWWIDTH, DRAWWIDTH, &dcGraph, 0, 0, SRCCOPY);
		dcGraph.FillSolidRect(DRAWWIDTH - 1, 0, 2, DRAWHEIGHT, RGB(0, 0, 0));

		if (0 == m_buffIndex)
			GetPosData(DRAWWIDTH - 1, 0, yPos0, yPos1);
		else
			GetPosData(m_buffIndex - 1, m_buffIndex, yPos0, yPos1);

		for (j = 0; j < CHANNELTOTAL; j++)
		{
			pOldPen[j] = (CPen *)dcGraph.SelectObject(&pen[j]);
			if (pViewerSet->m_Ch[j].bCh)
			{
				dcGraph.MoveTo(543, yPos0[j]);
				dcGraph.LineTo(544, yPos1[j]);
			}
			dcGraph.SelectObject(pOldPen[j]);
		}
	}
	else if (m_bUpdateGraph)
	{
		dcGraph.FillSolidRect(0, 0, DRAWWIDTH, DRAWHEIGHT, RGB(0, 0, 0));

		for (i = buffSP; buffCnt < DRAWWIDTH - 1; i++, buffCnt++)
		{
			if (i == DRAWWIDTH - 1) {
				buffPtr = 0;
			}
			else if (i > DRAWWIDTH - 1) {
				i = 0;
				buffPtr = i + 1;
			}
			else {
				buffPtr = i + 1;
			}

			GetPosData(i, buffPtr, yPos0, yPos1);

			for (j = 0; j < CHANNELTOTAL; j++)
			{
				pOldPen[j] = (CPen *)dcGraph.SelectObject(&pen[j]);
				if (pViewerSet->m_Ch[j].bCh)
				{
					dcGraph.MoveTo(buffCnt, yPos0[j]);
					dcGraph.LineTo(buffCnt + 1, yPos1[j]);
				}
				dcGraph.SelectObject(pOldPen[j]);
			}
		}
		m_bUpdateGraph = FALSE;
	}

	dc.TransparentBlt(0, 0, DRAWWIDTH, DRAWHEIGHT, &dcGraph, 0, 0, DRAWWIDTH, DRAWHEIGHT, RGB(0, 0, 0));
	dcGraph.SelectObject(pOldBitmapGraph);

	// ���� ����
	pOldPenVBar = (CPen*)dc.SelectObject(&penVBar);

	dc.MoveTo(m_iBarH, 0);
	dc.LineTo(m_iBarH, DRAWHEIGHT);

	dc.SetTextColor(RGB(255, 255, 255));
	dc.SetBkColor(RGB(0, 0, 0));
	CString str = _T("");
	str.Format(_T("%d"), m_iBarH);

	rect.top = 5;
	rect.left = m_iBarH - 30;

	dc.DrawText(str, rect, DT_LEFT);				// Display Mnem. (String)

	dc.SelectObject(pOldPenVBar);

	// ������ �� ����
	int iBarH = m_iBarH + m_buffIndex;
	iBarH = iBarH < DRAWWIDTH ? iBarH : iBarH - DRAWWIDTH;

	CString	strMnem = _T("");
	CString strYPos = _T("");

	// Graph
	for (i = 0; i < CHANNELTOTAL; i++)
	{
		strMnem = pViewerSet->m_Ch[i].strMnem;

		if (pViewerSet->m_Ch[i].strType == CBO_TYPE[1])
		{
			m_oBarV[i].m_float = m_Channel[i][iBarH].m_float;
			strYPos.Format(_T("%f"), m_oBarV[i].m_float);
		}
		else if (pViewerSet->m_Ch[i].strType == CBO_TYPE[0])
		{
			m_oBarV[i].m_int = m_Channel[i][iBarH].m_int;
			strYPos.Format(_T("%d"), m_oBarV[i].m_int);
		}
		else if (pViewerSet->m_Ch[i].strType == CBO_TYPE[2])
		{
			m_oBarV[i].m_int = m_Channel[i][iBarH].m_int;
			strYPos.Format(_T("%02x"), m_oBarV[i].m_int & 0xff);
			strYPos = HexToBin(strYPos);
		}

		if (pViewerSet->m_Ch[i].bCh){
			rect.top = 30 + i * 15;
			rect.left = 340;

			dc.SetTextColor(pViewerSet->m_Ch[i].crColor);
			dc.DrawText(strMnem, rect, DT_LEFT);
			rect.right = 540;
			dc.DrawText(strYPos, rect, DT_RIGHT);
		}
		strMnem.Empty();
		strYPos.Empty();
	}

	// Capture
	iBarH = m_iBarH;

	if (pViewerCapture->m_bCaptureCh)
	{
		for (i = 0; i < CHANNELTOTAL; i++)
		{
			strMnem = pViewerCapture->m_ChCap[i].strMnem;

			if (pViewerCapture->m_ChCap[i].strType == CBO_TYPE[1])
			{
				m_oBarVCap[i].m_float = pViewerCapture->m_ChannelCap[i][iBarH].m_float;
				strYPos.Format(_T("%f"), m_oBarVCap[i].m_float);
			}
			else if (pViewerCapture->m_ChCap[i].strType == CBO_TYPE[0])
			{
				m_oBarVCap[i].m_int = pViewerCapture->m_ChannelCap[i][iBarH].m_int;
				strYPos.Format(_T("%d"), m_oBarVCap[i].m_int);
			}
			else if (pViewerCapture->m_ChCap[i].strType == CBO_TYPE[2])
			{
				m_oBarVCap[i].m_int = pViewerCapture->m_ChannelCap[i][iBarH].m_int;
				strYPos.Format(_T("%02x"), m_oBarVCap[i].m_int & 0xff);
				strYPos = HexToBin(strYPos);
			}

			if (pViewerCapture->m_ChCap[i].bCh) {
				rect.top = 30 + (i + 9) * 15;
				rect.left = 340;

				dc.SetTextColor(pViewerCapture->m_ChCap[i].crColor);
				// dc.SetBkMode(TRANSPARENT);
				dc.DrawText(strMnem, rect, DT_LEFT);
				rect.right = 540;
				dc.DrawText(strYPos, rect, DT_RIGHT);
			}
		}
	}

	// �׷��� ī��Ʈ
	if (m_bStartGraph)
		m_buffIndex++;

	// �׷��� ���
	pDC->BitBlt(1, 1, DRAWWIDTH - 2, DRAWHEIGHT - 2, &dc, 1, 1, SRCCOPY);

	// �׷��� �̹��� ����
	CDC dcImage;
	dcImage.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmapImage = (CBitmap*)dcImage.SelectObject(&m_bmpImage);

	dcImage.BitBlt(0, 0, DRAWWIDTH, DRAWHEIGHT, &dc, 0, 0, SRCCOPY);
	dcImage.SelectObject(pOldBitmapImage);

	// �ڿ� ��ȯ
	dc.SelectObject(pOldBitmap);
	m_Graph.ReleaseDC(pDC);
}


void CViewerDlg::UpdateGraphBg()
{
	int i = 0;
	int j = 0;
	CDC* pDC = m_Graph.GetWindowDC();

	CDC dcGraphBg;
	dcGraphBg.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmapGraphBg = (CBitmap*)dcGraphBg.SelectObject(&m_bmpGraphBg);

	// ���
	dcGraphBg.FillSolidRect(0, 0, DRAWWIDTH, DRAWHEIGHT, RGB(0, 0, 0));

	// ����
	CPen* pOldPen = (CPen*)dcGraphBg.SelectObject(&penGrid);
	for (i = 7; i < DRAWHEIGHT; i += 50)
	{
		dcGraphBg.MoveTo(0, i);
		dcGraphBg.LineTo(DRAWWIDTH, i);
	}
	dcGraphBg.SelectObject(pOldPen);

	if (pViewerCapture->m_bCaptureCh)
	{
		int iValue = 0;
		int iValue0 = 0;	 // ������
		int iScale = 0;
		int iOffset = 0;

		CPen	Pen[CHANNELTOTAL];
		CPen*	pOldPen;

		Pen[0].CreatePen(PS_DOT, 1, pViewerCapture->m_ChCap[0].crColor);
		pOldPen = (CPen*)dcGraphBg.SelectObject(&Pen[0]);

		for (i = 0; i < CHANNELTOTAL; i++)
		{
			if (!pViewerCapture->m_ChCap[i].bCh) continue;

			if (i>0) Pen[i].CreatePen(PS_DOT, 1, pViewerCapture->m_ChCap[i].crColor);

			dcGraphBg.SelectObject(&Pen[i]);

			for (j = 0; j < DRAWWIDTH; j++)
			{
				iScale = _ttoi(pViewerCapture->m_ChCap[i].strScale);
				iOffset = _ttoi(pViewerCapture->m_ChCap[i].strOffset);

				if (pViewerCapture->m_ChCap[i].strType == CBO_TYPE[1])	iValue = pViewerCapture->m_ChannelCap[i][j].m_float;
				else													iValue = pViewerCapture->m_ChannelCap[i][j].m_int;

				if (iScale < 0)	iValue = DRAWHEIGHT - iOffset - 5 - (iValue / (iScale * -1));
				else			iValue = DRAWHEIGHT - iOffset - 5 - (iValue * iScale);

				dcGraphBg.MoveTo(j - 1, iValue0);
				dcGraphBg.LineTo(j, iValue);

				iValue0 = iValue;

				if (pViewerDlg->m_iBarH == j)
					pViewerDlg->m_oBarVCap[i] = pViewerCapture->m_ChannelCap[i][j];
			}
		}

		dcGraphBg.SelectObject(pOldPen);
	}

	dcGraphBg.SelectObject(pOldBitmapGraphBg);
	m_bUpdateCapture = FALSE;
}


void CViewerDlg::GetPosData(unsigned long ptr0, unsigned long ptr1, long yPos0[], long yPos1[])
{
	// ----------------------------------------------------------------------------------------------------
	// Calculate y axis Position
	int i = 0;
	int	iScale = 0;
	int iOffset = 0;
	uDOUBLE pos0, pos1;

	for (i = 0; i < CHANNELTOTAL; i++)
	{
		iScale = m_GrpScale[i];
		iOffset = m_GrpOffset[i];

		// float
		if (pViewerSet->m_Ch[i].strType == CBO_TYPE[1])
		{
			if (iScale < 0)
			{
				pos0.m_float = m_Channel[i][ptr0].m_float / (iScale * -1);
				pos1.m_float = m_Channel[i][ptr1].m_float / (iScale * -1);
			}
			else
			{
				pos0.m_float = m_Channel[i][ptr0].m_float * iScale;
				pos1.m_float = m_Channel[i][ptr1].m_float * iScale;
			}
			yPos0[i] = DRAWHEIGHT - iOffset - 5 - pos0.m_float;
			yPos1[i] = DRAWHEIGHT - iOffset - 5 - pos1.m_float;
		}
		// UINT
		else
		{
			if (iScale < 0)
			{
				pos0.m_int = m_Channel[i][ptr0].m_int / (iScale * -1);
				pos1.m_int = m_Channel[i][ptr1].m_int / (iScale * -1);
			}
			else
			{
				pos0.m_int = m_Channel[i][ptr0].m_int * iScale;
				pos1.m_int = m_Channel[i][ptr1].m_int * iScale;
			}
			yPos0[i] = DRAWHEIGHT - iOffset - 5 - pos0.m_int;
			yPos1[i] = DRAWHEIGHT - iOffset - 5 - pos1.m_int;
		}
	}
}


void CViewerDlg::OnBnClickedButtonViewerStart()
{
	BYTE byData[1024] = { 0, };
	if (!ConnectSocket)
	{
		setDataFromRemote(ConnectSocket, tx_addr, 36, WBCOM, &byData);
		m_Btn_StartViewer.EnableWindow(FALSE);
		// ----------------------------------------------------------------------------------------------------
		// Server ����
		CString strCmd = theApp.m_lpCmdLine;
		CString strAddr;
		CString strPort;

		AfxExtractSubString(strAddr, strCmd, 0, ' ');
		AfxExtractSubString(strPort, strCmd, 1, ' ');

#ifdef _DEBUG
		strAddr.Format(_T("192.168.0.199"));
		strPort = DEFAULT_PORT;
#endif
		if (strPort == _T(""))	strPort = DEFAULT_PORT;

		CStringA addr;
		CStringA port;
		char ch_ip[64];
		char ch_port[64];
		addr = strAddr;
		port = strPort;
		strcpy(ch_ip, addr.GetBuffer(addr.GetLength()));
		strcpy(ch_port, port.GetBuffer(port.GetLength()));

		ConnectSocket = NetCon(ch_ip, ch_port);
		if (ConnectSocket <= 0)
		{
			m_Btn_StartViewer.SetWindowTextW(_T("Start"));
			m_Btn_StartViewer.EnableWindow(TRUE);
			AfxMessageBox(_T("Not Connect"));
			return;
		}
		m_Btn_StartViewer.EnableWindow(TRUE);
		m_Btn_StartViewer.SetWindowTextW(_T("Stop"));
		StartDrawViewerThread();
	}
	else
	{
		setDataFromRemote(ConnectSocket, tx_addr, 36, WBCOM, &byData);
		m_Btn_StartViewer.EnableWindow(FALSE);
		if (WaitForSingleObject(g_pDrawViewerThread->m_hThread, 2000) == WAIT_TIMEOUT)
		{
			// Ÿ�Ӿƿ����� ������� ������ ��������
			g_pDrawViewerThread->SuspendThread();
			g_pDrawViewerThread->ExitInstance();
			delete g_pDrawViewerThread;
		}

		if (ConnectSocket != NULL)
		{
			NetClo(ConnectSocket);
			ConnectSocket = NULL;
		}
		m_Btn_StartViewer.EnableWindow(TRUE);
		m_Btn_StartViewer.SetWindowTextW(_T("Start"));
	}
}


void CViewerDlg::OnBnClickedButtonViewerstart()
{
	if (!m_bStartGraph)
	{
		// Start Graph
		m_bStartGraph = TRUE;
		m_Btn_Start.SetWindowTextW(_T("��"));
	}
	else
	{
		// Stop Graph
		m_bStartGraph = FALSE;
		m_Btn_Start.SetWindowTextW(_T("��"));
	}
}


void CViewerDlg::OnBnClickedButtonShowset()
{
	if (pViewerSet == NULL) return;

	if (m_bShowSetDlg)
	{
		pViewerSet->ShowWindow(SW_HIDE);
		m_bShowSetDlg = FALSE;
	}
	else
	{
		CRect rectThis;
		CRect rectSet;

		this->GetWindowRect(&rectThis);
		pViewerSet->GetWindowRect(&rectSet);

		pViewerSet->MoveWindow(rectThis.right, rectThis.top,
			rectSet.Width(), rectSet.Height(), TRUE);

		pViewerSet->ShowWindow(SW_SHOW);
		m_bShowSetDlg = TRUE;
	}
}


void CViewerDlg::OnBnClickedButtonShowsnap()
{
	if (pViewerSnap == NULL) return;

	if (m_bShowSnapDlg)
	{
		pViewerSnap->ShowWindow(SW_HIDE);
		m_bShowSnapDlg = FALSE;
	}
	else
	{
		CRect rectThis;
		CRect rectSnap;

		this->GetWindowRect(&rectThis);
		pViewerSnap->GetWindowRect(&rectSnap);

		pViewerSnap->MoveWindow(rectThis.left, rectThis.bottom,
			rectSnap.Width(), rectSnap.Height(), TRUE);

		pViewerSnap->ShowWindow(SW_SHOW);
		m_bShowSnapDlg = TRUE;
	}
}


void CViewerDlg::OnBnClickedButtonShowcapture()
{
	if (pViewerCapture == NULL) return;

	if (m_bShowCaptureDlg)
	{
		pViewerCapture->ShowWindow(SW_HIDE);
		m_bShowCaptureDlg = FALSE;
	}
	else
	{
		CRect rectThis;
		CRect rectSet;
		CRect rectCapture;

		this->GetWindowRect(&rectThis);
		pViewerSet->GetWindowRect(&rectSet);
		pViewerCapture->GetWindowRect(&rectCapture);

		pViewerCapture->MoveWindow(rectThis.right, rectThis.top + rectSet.Height() + 1,
			rectCapture.Width(), rectCapture.Height(),
			TRUE);

		pViewerCapture->ShowWindow(SW_SHOW);
		m_bShowCaptureDlg = TRUE;
	}
}
