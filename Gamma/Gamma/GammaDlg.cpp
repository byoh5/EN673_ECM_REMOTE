
// GammaDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "Gamma.h"
#include "GammaDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

UINT	GammaWriteThread(LPVOID pParam);
UINT	LoadingThreadGamma(LPVOID pParam);

const UINT  ID_CHECK_TIMER = 100;
const UINT  ID_CONNECT_TIMER = 200;
UINT	State_Check_Thread(LPVOID pParam);
UINT	Connect_Check_Thread(LPVOID pParam);

#define		Check_Time		1000
#define		Connect_Time	5000

// ====================================================================================================
//
// CGammaGraph
//
// ====================================================================================================
// ====================================================================================================
// CGammaGraph :: CGammaGraph
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
CGammaGraph::CGammaGraph()
{
	m_pGraph = NULL;
	m_pGrpPoint = NULL;
}

// ====================================================================================================
// CGammaGraph :: ~CGammaGraph
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
CGammaGraph::~CGammaGraph()
{
	if (m_pGrpPoint != NULL) delete[] m_pGrpPoint;
}

#define GRPMAX		((m_pGrpPoint == NULL) ? 0 : pGammaDlg->m_Gamma.m_pGrpPoint[pGammaDlg->m_Gamma.m_uiXStep-1].x) //1023
#define GRPSPACE	25 //���ʾƷ� ����

#define Y_C(Y)		iCtrlHeight-(Y) // iCtrlHeight ���� Y ������.
#define Y_G(Y)		iBufHeight-(Y) // iGrpHeight ���� Y ������

#define MAXZOOM		600 /*%*/
#define MINZOOM		100 /*%*/
#define ZOOM_X(X) (int)((X)*(((float)iOutWidth /(float)iGrpWidth) *((float)pGammaDlg->m_Gamma.m_iZoomRate/100)))
#define ZOOM_Y(Y) (int)((Y)*(((float)iOutHeight/(float)iGrpHeight)*((float)pGammaDlg->m_Gamma.m_iZoomRate/100)))

// ====================================================================================================
// CGammaGraph :: UpdateGraph
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CGammaGraph::UpdateGraph()
{
	if (m_pGraph == NULL) return;

	UINT i = 0;
	CString str = _T("");

	// ----------------------------------------------------------------------------------------------------
	// Graph Size
	CRect rect;
	m_pGraph->GetWindowRect(rect);
	int iCtrlWidth = rect.Width(); // ��Ʈ�� ũ��
	int iCtrlHeight = rect.Height();
	int iOutWidth = iCtrlWidth - GRPSPACE; // �������� �׷������� ũ��
	int iOutHeight = iCtrlHeight - GRPSPACE;
	int iGrpWidth = GRPMAX + 20; // 20�� ��������(?) �ʹ� �� �پ������� ���ڵ� �� �Ⱥ����װ�.
	int iGrpHeight = GRPMAX + 20;
	int iBufWidth = ZOOM_X(iGrpWidth);
	int iBufHeight = ZOOM_Y(iGrpHeight);

	// ----------------------------------------------------------------------------------------------------
	// Move
	int iMoveMaxX = iBufWidth - iOutWidth;
	int iMoveMaxY = iBufHeight - iOutHeight;

	if (m_ptMove.x < 0)	m_ptMove.x = 0;
	else if (m_ptMove.x > iMoveMaxX)	m_ptMove.x = iMoveMaxX;

	if (m_ptMove.y < 0) m_ptMove.y = 0;
	else if (m_ptMove.y > iMoveMaxY) m_ptMove.y = iMoveMaxY;

	// ----------------------------------------------------------------------------------------------------
	// DC
	CDC *pDC = m_pGraph->GetWindowDC(); // Picture Control���� ����ϴ� DC�� ����

	// Bitmap
	// Buffer (���� ����� Bitmap, ���� �����̶� ���ݵ��� ���⿡)
	CDC dcBuffer;
	dcBuffer.CreateCompatibleDC(pDC); // Picture Box���� ����ϴ� DC�� ����Ͽ� Memory DC�� ����

	CBitmap bmpBuffer; //���������� ����ϴ� Bitmap
	bmpBuffer.CreateCompatibleBitmap(pDC, iCtrlWidth, iCtrlHeight);
	CBitmap* pOldBitmapBuffer = (CBitmap*)dcBuffer.SelectObject(&bmpBuffer);

	// Graph (�׷��� �׸� ����)
	CDC dcGraph;
	dcGraph.CreateCompatibleDC(pDC); // Picture Box���� ����ϴ� DC�� ����Ͽ� Memory DC�� ����

	CBitmap bmpGraph;
	bmpGraph.CreateCompatibleBitmap(pDC, iBufWidth, iBufHeight);
	CBitmap* pOldBitmapGraph = (CBitmap*)dcGraph.SelectObject(&bmpGraph);

	// ----------------------------------------------------------------------------------------------------
	// Draw
	CPen* pOldPen = NULL;
	CBrush* pOldBrush = NULL;
	CFont* pOldFont = NULL;

	// Set Pen
	CPen penNone(PS_NULL, 0, RGB(0, 0, 0));
	CPen penDef(PS_SOLID, 1, RGB(0, 0, 0));
	CPen penStep(PS_DOT, 1, RGB(180, 180, 180));
	CPen penGraph(PS_SOLID, 1, RGB(255, 0, 0));

	// BackGround
	dcBuffer.FillSolidRect(0, 0, iCtrlWidth, iCtrlHeight, RGB(255, 255, 255)); // Buffer
	dcGraph.FillSolidRect(0, 0, iBufWidth, iBufHeight, RGB(255, 0, 255));

	// Font
	LOGFONT lf;
	::ZeroMemory(&lf, sizeof(lf));
	wsprintf(lf.lfFaceName, _T("%s"), _T("Arial")); // �۾�ü
	lf.lfHeight = 13;

	CFont Font;
	Font.CreateFontIndirect(&lf);

	// SPACE ���� ����
	pOldPen = dcBuffer.SelectObject(&penDef);
	pOldFont = dcBuffer.SelectObject(&Font);
	dcBuffer.SetBkMode(TRANSPARENT);
	dcBuffer.SetTextAlign(TA_CENTER);
	// X����
	for (i = 0; i < (int)m_uiXStep; i++)
	{
		// ���� ǥ��
		str.Format(_T("%d"), m_pGrpPoint[i].x);
		dcBuffer.TextOutW(ZOOM_X(m_pGrpPoint[i].x) + GRPSPACE - m_ptMove.x, iOutHeight + 2, str);
	}
	dcBuffer.SetTextAlign(TA_RIGHT);
	// Y����
	for (i = 0; i < /*iGrpHeight/((float)m_iZoomRate/100)*/iGrpHeight; i = i + 100)
	{
		// ���� ǥ��
		str.Format(_T("%d"), i);
		dcBuffer.TextOutW(GRPSPACE - 2, Y_C(ZOOM_Y(i) + GRPSPACE - m_ptMove.y), str);

		// ����
		dcBuffer.MoveTo(GRPSPACE - 10, Y_C(ZOOM_Y(i) + GRPSPACE - m_ptMove.y));
		dcBuffer.LineTo(GRPSPACE, Y_C(ZOOM_Y(i) + GRPSPACE - m_ptMove.y));
	}
	dcBuffer.SelectObject(pOldPen);
	dcBuffer.SelectObject(pOldFont);

	// Draw Step
	pOldPen = dcGraph.SelectObject(&penStep);

	// Y
	for (i = 0; i < iGrpHeight; i = i + 100)
	{
		dcGraph.MoveTo(0, Y_G(ZOOM_Y(i)));
		dcGraph.LineTo(iBufHeight, Y_G(ZOOM_Y(i)));
	}

	// X
	for (i = 0; i < m_uiXStep; i++)
	{
		dcGraph.MoveTo(ZOOM_X(m_pGrpPoint[i].x), 0);
		dcGraph.LineTo(ZOOM_X(m_pGrpPoint[i].x), iBufHeight);
	}

	dcGraph.SelectObject(pOldPen);

	// Draw Graph
	pOldPen = dcGraph.SelectObject(&penGraph);

	if (m_pGrpPoint != NULL)
	{
		dcGraph.MoveTo(m_pGrpPoint[0].x, Y_G(ZOOM_Y(m_pGrpPoint[0].y)));
		for (i = 1; i < m_uiXStep; i++)
		{
			dcGraph.LineTo(ZOOM_X(m_pGrpPoint[i].x), Y_G(ZOOM_Y(m_pGrpPoint[i].y)));
		}
	}
	dcGraph.SelectObject(pOldPen);

	// Draw Point
#define POINTSIZE 4

	// ���
	// ���ۿ� �׷��� ���
	dcBuffer.TransparentBlt(GRPSPACE, 0, iOutWidth, iOutHeight, &dcGraph, m_ptMove.x, Y_G(iOutHeight + m_ptMove.y), iOutWidth, iOutHeight, RGB(255, 0, 255));
	// ȣ���ڿ���µ���ǥx, ȣ���ڿ���µ���ǥy, ȣ���ڿ���µɻ�����width, ȣ���ڿ���µɻ�����Height, �����DC,
	// ������ǥx, ������ǥy, ����ũ��width, ����ũ��height

	// X, Y ��
	pOldPen = dcBuffer.SelectObject(&penDef);

	dcBuffer.MoveTo(0, Y_C(GRPSPACE));		// X�� ����
	dcBuffer.LineTo(iCtrlWidth, Y_C(GRPSPACE));		// X�� ��
	dcBuffer.MoveTo(GRPSPACE, Y_C(0));				// Y�� ����
	dcBuffer.LineTo(GRPSPACE, Y_C(iCtrlHeight));	// Y�� ��

	dcBuffer.SelectObject(&pOldPen);

	// X,Y ��, ����Ʈ ��ġ
	CBrush brushPoint(RGB(130, 130, 130));
	pOldBrush = dcBuffer.SelectObject(&brushPoint);
	dcBuffer.SetTextAlign(TA_CENTER);
	pOldFont = dcBuffer.SelectObject(&Font);

	for (i = 0; i < m_uiXStep; i++)
	{
		if ((ZOOM_X(m_pGrpPoint[i].x) - m_ptMove.x)<0) continue;
		if ((ZOOM_Y(m_pGrpPoint[i].y) - m_ptMove.y)<0) continue;


		// ��
		if (m_uiPointSel == i)	dcBuffer.SelectObject(&penDef);
		else					dcBuffer.SelectObject(&penNone);

		dcBuffer.Ellipse(ZOOM_X(m_pGrpPoint[i].x) + GRPSPACE - POINTSIZE - m_ptMove.x, Y_C(ZOOM_Y(m_pGrpPoint[i].y) + GRPSPACE + POINTSIZE - m_ptMove.y),
			ZOOM_X(m_pGrpPoint[i].x) + GRPSPACE + POINTSIZE - m_ptMove.x, Y_C(ZOOM_Y(m_pGrpPoint[i].y) + GRPSPACE - POINTSIZE - m_ptMove.y));

		str.Format(_T("%d"), m_pGrpPoint[i].y);
		dcBuffer.TextOutW(ZOOM_X(m_pGrpPoint[i].x) + GRPSPACE - m_ptMove.x, Y_C(ZOOM_Y(m_pGrpPoint[i].y) + GRPSPACE - m_ptMove.y) + POINTSIZE, str);

	}
	dcBuffer.SelectObject(pOldPen);
	dcBuffer.SelectObject(pOldFont);
	dcBuffer.SelectObject(pOldBrush);

	// �������
	pDC->BitBlt(1, 1, iCtrlWidth - 2, iCtrlHeight - 2, &dcBuffer, 0, 0, SRCCOPY);

	// DC ��ȯ
	Font.DeleteObject();
	dcBuffer.SelectObject(pOldBitmapBuffer);
	dcGraph.SelectObject(pOldBitmapGraph);

	m_pGraph->ReleaseDC(pDC);
}

// ====================================================================================================
// CGammaGraph :: SetPictureCtrl
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CGammaGraph::SetPictureCtrl(CStatic* pGraph)
{
	m_pGraph = pGraph;
}

// ====================================================================================================
// CGammaGraph :: SetGammaStep
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CGammaGraph::SetGammaStep(UINT uiXStep, UINT* iXPoint)
{
	UINT i = 0;
	m_uiXStep = uiXStep;

	// Init GrpPoint
	if (m_pGrpPoint != NULL) delete[] m_pGrpPoint;

	// �Ҵ�
	if (uiXStep > 0)
		m_pGrpPoint = new CPoint[uiXStep];
	else
		m_pGrpPoint = NULL;

	// �� ����, ����
	for (i = 0; i < uiXStep; i++)
		m_pGrpPoint[i].x = iXPoint[i];

	// Renewal Y Value
	for (i = 0; i < m_uiXStep; i++)
	{
		SetGammaY(i);
	}
}

// ====================================================================================================
// CGammaGraph :: SetGammaVal
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CGammaGraph::SetGammaVal(float fGammaVal, float fTarget)
{
	int i = 0;
	m_fGammaVal = fGammaVal;
	m_fGammaTarget = fTarget;

	// Renewal Y Value
	for (i = 0; i < (int)m_uiXStep; i++)
	{
		SetGammaY(i);
	}
}

// ====================================================================================================
// CGammaGraph :: SetGammaY
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CGammaGraph::SetGammaY(UINT uiXStep, int iYValue)
{
	/*Target�� �ϴ��� ������ 1024*/
	//m_pGrpPoint[uiXStep].y = uiYValue;
	//m_pGrpPoint[uiXStep].y = GAMMA(m_pGrpPoint[uiXStep].x, m_fGammaVal, m_pGrpPoint[m_uiXStep-1].x);

	if (iYValue == -1)
	{
		if (m_fGammaTarget == -1)
			m_pGrpPoint[uiXStep].y = (LONG)GAMMA(m_pGrpPoint[uiXStep].x, m_fGammaVal, m_pGrpPoint[m_uiXStep - 1].x);
		else
			m_pGrpPoint[uiXStep].y = (LONG)GAMMA(m_pGrpPoint[uiXStep].x, m_fGammaVal, m_fGammaTarget);
	}
	else
	{
		m_pGrpPoint[uiXStep].y = iYValue;
	}
}

// ====================================================================================================
// CGammaGraph :: SetGammaZoomRate
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CGammaGraph::SetGammaZoomRate(int iZoomRate)
{
	if (m_pGrpPoint == NULL) return;

	m_iZoomRate = iZoomRate;

	if (m_iZoomRate > MAXZOOM) { m_iZoomRate = MAXZOOM; }
	else if (m_iZoomRate < MINZOOM) { m_iZoomRate = MINZOOM; }

	if (m_iZoomRate == 100)
	{
		m_ptMove.x = 0;
		m_ptMove.y = 0;
	}
}

// ====================================================================================================
// CGammaGraph :: GetValue
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
float CGammaGraph::GetGammaVal() { return m_fGammaVal; }
UINT CGammaGraph::GetGammaY(UINT uiXStep) { return m_pGrpPoint[uiXStep].y; }
int CGammaGraph::GetGammaZoomRate() { return m_iZoomRate; }

// ====================================================================================================
// CGammaGraph :: ClickPoint
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
BOOL CGammaGraph::ClickPoint(int iX, int iY)
{
	// Ŭ���� X, Y���� �޾Ƽ� m_uiPointSel�� m_pGrpPoint[m_uiPointSel].y�� ��������

	// point�� m_pGraph ũ�⿡ ���� ȯ���� ���� ���޹���
	// iX�� ��������, X���� ���� ����� ���� ����
	// ����κ��� ó������ ����.

	CRect rect;
	m_pGraph->GetWindowRect(rect);
	int iCtrlWidth = rect.Width();
	int iCtrlHeight = rect.Height();
	int iGrpWidth = GRPMAX + 20;
	int iGrpHeight = GRPMAX + 20;
	int iOutWidth = iCtrlWidth - GRPSPACE;
	int iOutHeight = iCtrlHeight - GRPSPACE;

	UINT i = 0;
	CString str = _T("");

	for (i = 0; i < m_uiXStep; i++)
	{
		// ����
		if (INMIDDLE(iX, 0, GRPSPACE) || INMIDDLE(iY, iCtrlHeight - GRPSPACE, iCtrlHeight))
		{
			continue;
		}
		// Point Ŭ��
		if (INMIDDLE(iX - GRPSPACE, ZOOM_X(m_pGrpPoint[i].x) - POINTSIZE - m_ptMove.x, ZOOM_X(m_pGrpPoint[i].x) + POINTSIZE - m_ptMove.x) &&
			INMIDDLE(iCtrlHeight - iY - GRPSPACE, ZOOM_Y(m_pGrpPoint[i].y) - POINTSIZE - m_ptMove.y, ZOOM_Y(m_pGrpPoint[i].y) + POINTSIZE - m_ptMove.y))
		{
			m_uiPointSel = i;
			return TRUE;
		}
	}

	return FALSE;
}

// ====================================================================================================
// CGammaGraph :: ClickPoint
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
BOOL CGammaGraph::ClickPoint(CPoint point)
{	// point�� m_pGraph ũ�⿡ ���� ȯ���� ���� ���޹���
	// iX�� ��������, X���� ���� ����� ���� ����
	// ����κ��� ó������ ����.

	int iX = point.x;
	int iY = point.y;

	return ClickPoint(iX, iY);
}

// ====================================================================================================
// CGammaGraph :: MovePoint
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CGammaGraph::MovePoint(int iX, int iY)
{
	if (m_pGrpPoint == NULL) return;

	CRect rect;
	m_pGraph->GetWindowRect(rect);
	int iCtrlWidth = rect.Width();
	int iCtrlHeight = rect.Height();
	int iGrpWidth = GRPMAX + 20;
	int iGrpHeight = GRPMAX + 20;

	int iGrpArea = iCtrlHeight - GRPSPACE;
	int iMaxHeight = ((iGrpHeight / ((float)m_iZoomRate / 100))); // Max Height
	float fMousePointRate = ((float)(iGrpArea - iY + m_ptMove.y) / (float)(iGrpArea)); // ���콺�� Ŭ���� ���� ����??

	int iChgY = iMaxHeight * fMousePointRate;

	if (iChgY < 0)
		iChgY = 0;
	else if (iChgY > m_pGrpPoint[m_uiXStep - 1].x)
		iChgY = m_pGrpPoint[m_uiXStep - 1].x;

	m_pGrpPoint[m_uiPointSel].y = iChgY;
}

// ====================================================================================================
// CGammaGraph :: MoveGraph
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CGammaGraph::MoveGraph(int iFirstX, int iFirstY, int iX, int iY)
{
	// m_ptMove ������ �����̸� Dafault���� 0, 0��..
	// Ȯ������ ���� ũ�⿡ �°� ����
	CRect rect;
	m_pGraph->GetWindowRect(rect);
	int iCtrlWidth = rect.Width();
	int iCtrlHeight = rect.Height();
	int iOutWidth = iCtrlWidth - GRPSPACE;
	int iOutHeight = iCtrlHeight - GRPSPACE;
	int iGrpWidth = GRPMAX + 20; // 20�� ��������(?).. �ʹ� �� �پ������� ���ڵ� �� �Ⱥ����װ�.
	int iGrpHeight = GRPMAX + 20;
	int iBufWidth = ZOOM_X(iGrpWidth);
	int iBufHeight = ZOOM_Y(iGrpHeight);

	// ----------------------------------------------------------------------------------------------------
	int iMoveX = iFirstX - iX;
	int iMoveY = -(iFirstY - iY);

	int iMoveMaxX = iBufWidth - iOutWidth;
	int iMoveMaxY = iBufHeight - iOutHeight;

	m_ptMove.x = m_ptMoveStart.x + iMoveX;
	m_ptMove.y = m_ptMoveStart.y + iMoveY;

	if (m_ptMove.x < 0)	m_ptMove.x = 0;
	else if (m_ptMove.x > iMoveMaxX)	m_ptMove.x = iMoveMaxX;

	if (m_ptMove.y < 0) m_ptMove.y = 0;
	else if (m_ptMove.y > iMoveMaxY) m_ptMove.y = iMoveMaxY;
}


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


// CGammaDlg ��ȭ ����



CGammaDlg::CGammaDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGammaDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ECM);
}

void CGammaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_GAMMACLOSE, m_Btn_Close);
	DDX_Control(pDX, IDC_STATIC_GAMMAGRAPH, m_Pic_GammaGraph);
	DDX_Control(pDX, IDC_EDIT_GAMMAVALUE, m_Edit_GammaValue);
	DDX_Control(pDX, IDC_EDIT_GAMMATARGET, m_Edit_GammaTarget);
	DDX_Control(pDX, IDC_BUTTON_GAMMAAPPLY, m_Btn_GammaApply);
	DDX_Control(pDX, IDC_COMBO_GAMMATABLE, m_Cbo_GammaTable);
	DDX_Control(pDX, IDC_BUTTON_GAMMAWRITE, m_Btn_GammaWrite);
	DDX_Control(pDX, IDC_BUTTON_GAMMALOAD, m_Btn_GammaLoad);
	DDX_Control(pDX, IDC_BUTTON_GAMMASAVE, m_Btn_GammaSave);
	DDX_Control(pDX, IDC_COMBO_GAMMAZOOM, m_Cbo_GammaZoom);
	DDX_Control(pDX, IDC_BUTTON_MINIMIZE, m_Btn_Minimize);
	DDX_Control(pDX, IDC_BUTTON_CONNECT, m_Btn_Connect);
	DDX_Control(pDX, IDC_PROGRESS_LOADING, m_Progress_Loading);
}

BEGIN_MESSAGE_MAP(CGammaDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_GAMMACLOSE, &CGammaDlg::OnBnClickedButtonGammaclose)
	ON_BN_CLICKED(IDC_BUTTON_MINIMIZE, &CGammaDlg::OnBnClickedButtonMinimize)
	ON_BN_CLICKED(IDC_BUTTON_GAMMAAPPLY, &CGammaDlg::OnBnClickedButtonGammaapply)
	ON_CBN_SELCHANGE(IDC_COMBO_GAMMATABLE, &CGammaDlg::OnCbnSelchangeComboGammatable)
	ON_BN_CLICKED(IDC_BUTTON_GAMMAWRITE, &CGammaDlg::OnBnClickedButtonGammawrite)
	ON_BN_CLICKED(IDC_BUTTON_GAMMALOAD, &CGammaDlg::OnBnClickedButtonGammaload)
	ON_BN_CLICKED(IDC_BUTTON_GAMMASAVE, &CGammaDlg::OnBnClickedButtonGammasave)
	ON_CBN_SELCHANGE(IDC_COMBO_GAMMAZOOM, &CGammaDlg::OnCbnSelchangeComboGammazoom)
	ON_WM_MOUSEWHEEL()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CGammaDlg::OnBnClickedButtonConnect)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CGammaDlg �޽��� ó����

BOOL CGammaDlg::OnInitDialog()
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
	SetWindowText(DLG_GAMMA);
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
	addr = strAddr;
	port = strPort;
	strcpy(ch_ip, addr.GetBuffer(addr.GetLength()));
	strcpy(ch_port, port.GetBuffer(port.GetLength()));

	ConnectSocket = NetCon(ch_ip, ch_port);
	if (ConnectSocket <= 0)
	{
		AfxMessageBox(_T("Not Connect"));
		//exit(0);
	}

	//Sleep(1);
	Wait(1);

	StateSocket = NetCon(ch_ip, ch_port);

	// Connect Check Timer Set
	Check_Timer_On();

// ----------------------------------------------------------------------------------------------------
// Gamma Dialog Setting
	int x = ReadIni(SEC_WININFO, KEY_GAMMADLGLEFT, DEF_GAMMADLGLEFT);
	int y = ReadIni(SEC_WININFO, KEY_GAMMADLGTOP, DEF_GAMMADLGTOP);
	SetWindowPos(NULL, x, y, 520, 620, NULL);

	pGammaDlg = this;

// ----------------------------------------------------------------------------------------------------
// Control
	// Close
	m_Btn_Close.DrawBorder(FALSE);
	m_Btn_Close.SetColor(CButtonST::BTNST_COLOR_BK_OUT, DIALOGCOLOR);
	m_Btn_Close.SetColor(CButtonST::BTNST_COLOR_BK_IN, DIALOGSUBCOLOR);
	
	// Minimize
	m_Btn_Minimize.DrawBorder(FALSE);
	m_Btn_Minimize.SetColor(CButtonST::BTNST_COLOR_BK_OUT, DIALOGCOLOR);
	m_Btn_Minimize.SetColor(CButtonST::BTNST_COLOR_BK_IN, DIALOGSUBCOLOR);

	// Connect
	m_Btn_Connect.SetIcon(IDI_CONNECT, NULL);
	m_Btn_Connect.DrawTransparent(TRUE);

	// Button
	m_Btn_GammaSave.SetWindowTextW(_T(""));
	m_Btn_GammaSave.SetBitmaps(IDB_SAVE, RGB(255, 0, 255));
	m_Btn_GammaLoad.SetBitmaps(IDB_OPEN, RGB(255, 0, 255));

	// Progress Bar
	m_Progress_Loading.ShowWindow(SW_HIDE);

	// Read, Write
	m_iUndo = NULL;
	SetPlatform();
	
	// Table
	CString strGmaTbl1[2] = { _T("YGMY"), _T("CGMY") };
	CString strGmaTbl2[4] = { _T("YGMY1"), _T("YGMY2"), _T("CGMY1"), _T("CGMY2") };
	
	int i = 0;
	
	for (i = 0; i < 2; i++)
		m_Cbo_GammaTable.AddString(strGmaTbl1[i]);

	m_Cbo_GammaTable.SetCurSel(0);

	// Zoom
	CString strZoom[4] = { _T("100"), _T("200"), _T("400"), _T("600") };
	for (i = 0; i < 4; i++)
		m_Cbo_GammaZoom.AddString(strZoom[i]);

	m_Cbo_GammaZoom.SetCurSel(0);

// ----------------------------------------------------------------------------------------------------
// Gamma Graph
	// Picture Control
	CRect rect;
	m_Pic_GammaGraph.GetWindowRect(rect);
	m_Pic_GammaGraph.SetWindowPos(NULL, 10, 35, 500, 500, NULL);

	// Gamma Value, Target
	m_Edit_GammaValue.SetWindowTextW(_T("0.45"));
	m_Edit_GammaTarget.SetWindowTextW(_T(""));

	m_Gamma.SetGammaVal((float)0.45);

	// Option 
	m_Gamma.m_iZoomRate = 100;
	m_Gamma.m_uiPointSel = -1;
	m_Gamma.m_ptMove.x = 0;
	m_Gamma.m_ptMove.y = 0;
	m_Gamma.m_ptMoveStart = 0;

	//m_bPointMoveOn = FALSE;
	//m_bGraphMoveOn = FALSE;

	// Picture Control
	m_Gamma.SetPictureCtrl(&m_Pic_GammaGraph);

// ----------------------------------------------------------------------------------------------------
// etc
	// Flag
	m_pwRxData = NULL;
	m_bGammaISP = FALSE;
	m_bLoading = FALSE;

	RxCheck_flag = TRUE;

	m_dwEN673BaseAdr = 0xf1100000;		// EN673 Dongle Base Address

// ----------------------------------------------------------------------------------------------------
// Key
	m_strKey = _T("");
	m_strKeyPw = _T("");
	OpenKeyFile();
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CGammaDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CGammaDlg::OnPaint()
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

		dc.TextOutW(10, 6, DLG_GAMMA);

		dc.SelectObject(pOldFont);
	}
	m_Gamma.UpdateGraph();
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CGammaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CGammaDlg::PreTranslateMessage(MSG* pMsg)
{
	CWnd* wndFocus = GetFocus();

	if (pMsg->message == WM_KEYDOWN)
	{
		if ((GetKeyState(VK_RCONTROL) & 0x8000) ||
			(GetKeyState(VK_LCONTROL) & 0x8000))
		{
			switch (pMsg->wParam)
			{
				// Ctrl+Z
			case VK_Z:
				OnUndo();
				m_bPointMoveOn = FALSE;
				return TRUE;
			}
		}
		else
		{
			switch (pMsg->wParam)
			{
			case VK_ESCAPE:
				if (m_Gamma.m_uiPointSel != -1)
				{
					m_Gamma.m_uiPointSel = -1;
					m_Gamma.UpdateGraph();
				}
				return TRUE;

			case VK_RETURN:
				if (wndFocus == NULL) return FALSE;
				if (wndFocus == m_Cbo_GammaZoom.GetNextDlgTabItem(GetDlgItem(IDC_COMBO_GAMMAZOOM)))
					OnChangeGammazoom();

				return TRUE;

			case VK_UP:
				if (m_Gamma.m_pGrpPoint == NULL) return TRUE;
				if (m_Gamma.m_uiPointSel != -1)
				{
					// Set Undo
					SetUndo(m_Gamma.m_uiPointSel, m_Gamma.m_pGrpPoint[m_Gamma.m_uiPointSel].y);

					if (m_Gamma.m_pGrpPoint[m_Gamma.m_uiPointSel].y < m_Gamma.m_pGrpPoint[m_Gamma.m_uiXStep - 1].x)
						m_Gamma.m_pGrpPoint[m_Gamma.m_uiPointSel].y += 1;
					else
						m_Gamma.m_pGrpPoint[m_Gamma.m_uiPointSel].y = m_Gamma.m_pGrpPoint[m_Gamma.m_uiXStep - 1].x;
				}

				m_Gamma.UpdateGraph();

				return TRUE;

			case VK_DOWN:
				if (m_Gamma.m_pGrpPoint == NULL) return TRUE;
				if (m_Gamma.m_uiPointSel != -1)
				{
					// Set Undo
					SetUndo(m_Gamma.m_uiPointSel, m_Gamma.m_pGrpPoint[m_Gamma.m_uiPointSel].y);

					if (m_Gamma.m_pGrpPoint[m_Gamma.m_uiPointSel].y > 0)
						m_Gamma.m_pGrpPoint[m_Gamma.m_uiPointSel].y -= 1;
					else
						m_Gamma.m_pGrpPoint[m_Gamma.m_uiPointSel].y = 0;
				}

				m_Gamma.UpdateGraph();

				return TRUE;
			}
		}
	}

	// Default Window Message
	if (DefaultWindowMessage(pMsg))	return TRUE;
	else							return CDialogEx::PreTranslateMessage(pMsg);
}


void CGammaDlg::OnCancel()
{
	delete m_iUndo;

	NetClo(ConnectSocket);
	ConnectSocket = NULL;

	NetClo(StateSocket);
	StateSocket = NULL;

	CDialogEx::OnCancel();
}


void CGammaDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRect graphRect;
	m_Pic_GammaGraph.GetWindowRect(graphRect);

	CRect thisRect;
	this->GetWindowRect(thisRect);

	// Graph
	if (INMIDDLE(point.x, graphRect.left - thisRect.left, graphRect.right - thisRect.left) &&
		INMIDDLE(point.y, graphRect.top - thisRect.top, graphRect.bottom - thisRect.top))
	{
		if (!m_Pic_GammaGraph.IsWindowEnabled()) return;
		if (m_Gamma.m_pGrpPoint == NULL) return;

		if (m_Gamma.ClickPoint(point.x - (graphRect.left - thisRect.left),
			point.y - (graphRect.top - thisRect.top)))
		{ // Point�� ������ ���
			// Save Undo Point
			SetUndo(m_Gamma.m_uiPointSel, m_Gamma.m_pGrpPoint[m_Gamma.m_uiPointSel].y);

			m_bPointMoveOn = TRUE;
			m_Gamma.UpdateGraph();
			SetCapture();
		}
		else
		{
			// Click ��ġ
			m_ptLDownPoint.x = point.x - (graphRect.left - thisRect.left);
			m_ptLDownPoint.y = point.y - (graphRect.top - thisRect.top);

			// ���� Graph ��ġ
			m_Gamma.m_ptMoveStart.x = m_Gamma.m_ptMove.x;
			m_Gamma.m_ptMoveStart.y = m_Gamma.m_ptMove.y;

			m_bGraphMoveOn = TRUE;
			SetCapture();
		}
	}
	else // Window
	{
		m_Gamma.m_uiPointSel = -1;
		m_Gamma.UpdateGraph();

		SetCapture();
		m_Point = point;

		SendMessage(WM_NCLBUTTONDOWN, HTCAPTION, 0);
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CGammaDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	CRect graphRect;
	m_Pic_GammaGraph.GetWindowRect(graphRect);

	CRect thisRect;
	this->GetWindowRect(thisRect);

	if (m_bPointMoveOn)
	{
		m_Gamma.MovePoint(point.x - (graphRect.left - thisRect.left), point.y - (graphRect.top - thisRect.top));

		m_Gamma.UpdateGraph();
	}
	else if (m_bGraphMoveOn)
	{
		m_Gamma.MoveGraph(m_ptLDownPoint.x,
			m_ptLDownPoint.y,
			point.x - (graphRect.left - thisRect.left),
			point.y - (graphRect.top - thisRect.top));

		m_Gamma.UpdateGraph();
	}
	else
	{
		if (this == GetCapture())
		{
			CRect rcDialog;
			GetWindowRect(&rcDialog);

			int x = rcDialog.left + point.x - m_Point.x;
			int y = rcDialog.top + point.y - m_Point.y;

			SetWindowPos(NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

			WriteIni(SEC_WININFO, KEY_GAMMADLGLEFT, x);
			WriteIni(SEC_WININFO, KEY_GAMMADLGTOP, y);
		}
	}
	CDialogEx::OnMouseMove(nFlags, point);
}


void CGammaDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_bPointMoveOn = FALSE;

	if (m_bGraphMoveOn)
	{
		m_bGraphMoveOn = FALSE;
		m_Gamma.m_ptMoveStart.x = m_Gamma.m_ptMove.x;
		m_Gamma.m_ptMoveStart.y = m_Gamma.m_ptMove.y;
	}

	ReleaseCapture();

	CDialogEx::OnLButtonUp(nFlags, point);
}


BOOL CGammaDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	//BOOL bReturn;
	CString str = _T("");

	CRect rect;
	m_Pic_GammaGraph.GetWindowRect(rect);

	int iGammaZoomRate = m_Gamma.GetGammaZoomRate();

	if (INMIDDLE(pt.x, rect.left, rect.right) && INMIDDLE(pt.y, rect.top, rect.bottom))
	{
		if (zDelta > 0) //Ȯ��
			m_Gamma.SetGammaZoomRate(iGammaZoomRate + 15);
		else if (zDelta < 0) //���
			m_Gamma.SetGammaZoomRate(iGammaZoomRate - 15);

		// Zoom Rate�� ������� ���
		if (iGammaZoomRate != m_Gamma.GetGammaZoomRate())
		{
			// Zoom Rate�� Gamma Zoom ComboBox�� ǥ���ϰ�
			// Graph Image�� Update�Ѵ�.
			iGammaZoomRate = m_Gamma.GetGammaZoomRate();

			str.Format(_T("%d"), iGammaZoomRate);
			m_Cbo_GammaZoom.SetWindowTextW(str);

			m_Gamma.UpdateGraph();
		}
	}

	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}


void CGammaDlg::OnBnClickedButtonGammaclose()
{
	CGammaDlg::OnCancel();
}


void CGammaDlg::OnBnClickedButtonMinimize()
{
	ShowWindow(SW_MINIMIZE);
}


void CGammaDlg::OnBnClickedButtonGammaapply()
{
	CString strGammaVal = _T("");
	CString strGammaTarget = _T("");

	m_Edit_GammaValue.GetWindowTextW(strGammaVal);
	m_Edit_GammaTarget.GetWindowTextW(strGammaTarget);

	float fGammaVal = (float)_ttof(strGammaVal);
	if (fGammaVal == 0) fGammaVal = 1;

	float fGammaTarget = (float)_ttoi(strGammaTarget);
	if (fGammaTarget == 0) fGammaTarget = -1;

	// Set Gamma Val/Target
	m_Gamma.SetGammaVal(fGammaVal, fGammaTarget);

	// Update Graph
	m_Gamma.UpdateGraph();
}


void CGammaDlg::OnCbnSelchangeComboGammatable()
{
	m_Pic_GammaGraph.SetFocus();
}


void CGammaDlg::OnBnClickedButtonGammawrite()
{
	if (!ConnectSocket) return;

	StartGammaWriteThread();
}


// ====================================================================================================
// CGammaDlg :: StartGammaWriteThread
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CGammaDlg::StartGammaWriteThread()
{
	// ----------------------------------------------------------------------------------------------------
	// Run Loading Thread
	AfxBeginThread(LoadingThreadGamma, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);

	// ----------------------------------------------------------------------------------------------------
	// Run Gamma Write Thread
	AfxBeginThread(GammaWriteThread, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
}


// ====================================================================================================
// LoadingThreadGamma
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
UINT LoadingThreadGamma(LPVOID pParam)
{
	// 1. �÷��� ����
	bRunGammaLoadingThread = TRUE;
	pGammaDlg->m_bLoading = TRUE;

	// 2. ��Ʈ�� ��Ȱ��ȭ
	pGammaDlg->EnableCtrl(FALSE);
	pGammaDlg->m_Btn_Close.EnableWindow(FALSE);

	// 3. ���
	while (pGammaDlg->m_bLoading){ 
		//Sleep(1);
		ProcessWindowMessage();
		Wait(1);
	}

	// 4. ��Ʈ�� Ȱ��ȭ
	pGammaDlg->EnableCtrl(TRUE);
	pGammaDlg->m_Btn_Close.EnableWindow(TRUE);
	pGammaDlg->m_Progress_Loading.ShowWindow(SW_HIDE);

	// 5. �÷��� ����
	bRunGammaLoadingThread = FALSE;

	return 0L;
}


// ====================================================================================================
// GammaWriteThread
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
UINT GammaWriteThread(LPVOID pParam)
{
	int i = 0;

	// ----------------------------------------------------------------------------------------------------
	// Gamma Flag On
	pGammaDlg->m_bGammaISP = TRUE;

// ----------------------------------------------------------------------------------------------------
// Gamma Write
	pGammaDlg->GammaWrite_EN673();

	// ----------------------------------------------------------------------------------------------------
	// Gamma Flag Off
	pGammaDlg->m_bGammaISP = FALSE;

	// ----------------------------------------------------------------------------------------------------
	// End Loading
	pGammaDlg->m_bLoading = FALSE;

	return 0L;
}


// ====================================================================================================
// CGammaDlg :: GammaWrite_EN771
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CGammaDlg::GammaWrite_EN673()
{
	int i = 0;
	BOOL bReturn = FALSE;
	CString str = _T("");

#if JTAG_UART
	// Set Protocol
	BYTE SendData[9] = { 0, };

	SendData[0] = PC_STX;
	SendData[1] = PC_CMD_REGW;
	SendData[2] = 0; //(BYTE)((dwAddr&0xff00)>>8);	// Addr
	SendData[3] = 0; //(BYTE)(dwAddr&0x00ff);
	SendData[4] = 0; //(BYTE)(dwData>>24);			// Data
	SendData[5] = 0; //(BYTE)(dwData>>16);
	SendData[6] = 0; //(BYTE)(dwData>>8);
	SendData[7] = 0; //(BYTE)(dwData);
	SendData[8] = PC_ETX;
#endif

	// Start Address ����
	int iStartAddr = 0;
//	int iPlatformSel = pECMDlg->GetPlatformSel();
	int iGmaTblSel = m_Cbo_GammaTable.GetCurSel();

	if (iGmaTblSel == 0/*YGMY*/)		iStartAddr = 0x0106;
	else if (iGmaTblSel == 1/*CGMY*/)	iStartAddr = 0x0110;

	// Addr Min/Max ����
	m_iAddrMin = iStartAddr;
	m_iAddrMax = iStartAddr + (EN673_GAMMAREGNUM - 1);

	// m_pwRxData �Ҵ� << �Ƹ��� �ʿ��������
	m_pwRxData = new DWORD[EN673_GAMMAREGNUM];
	for (i = 0; i < EN673_GAMMAREGNUM; i++)
		m_pwRxData[i] = -1;

	// Write
	int iCnt = 0;
	int iiCnt = 0;
	int iWriteCnt = 0;
	int iXCnt = 0;
	DWORD dwAddr = 0;
	DWORD dwData = 0;

	int state = 0;
#if JTAG_UART
	BYTE* flag;
#endif
	RxCheck_flag = TRUE;

	// Set ProgressCtrl
	m_Progress_Loading.ShowWindow(SW_SHOW);
	m_Progress_Loading.SetRange(0, EN673_GAMMAREGNUM);
	m_Progress_Loading.SetPos(0);
	while (iWriteCnt<EN673_GAMMAREGNUM)
	{
		ProcessWindowMessage();
		iCnt = 0;
		iiCnt = 0;
		switch (iWriteCnt)
		{
		case 0: // YGMA_ON[31],CGMA_ON[30],0[25:16],1[9:0]
			// Read
			dwAddr = iStartAddr + iWriteCnt;
#if JTAG_UART
			SendData[2] = (BYTE)((dwAddr & 0xff00) >> 8);
			SendData[3] = (BYTE)(dwAddr & 0x00ff);
			ReadISP(dwAddr);

			// Wait
			do{
				Sleep(10);
				state = getDataFromRemote(ConnectSocket, tx_addr, 4, WBCOM, &flag);
				if (state < 0 | iCnt > RETRY)
				{
					RxCheck_flag = FALSE;
					str.Format(_T("Fail Write Value. (Address : 0x%X)"), dwAddr);
					goto ENDGAMMAWRITE;
				}
				if ((((UINT32)flag & 0X0000ffff) == 0xd002) | iiCnt == RETRY)
				{
					iiCnt = 0;
					iCnt++;
					state = ReadISP(dwAddr);
				}
				iiCnt++;
			} while (((UINT32)flag & 0X0000ffff) != 0x2002);


			// Data
			dwData = m_pwRxData[iWriteCnt];

			dwData &= ValSft_L30(BitMask_02); // [31:30] mask
			dwData += (m_Gamma.m_pGrpPoint[iXCnt].y << 16) + (m_Gamma.m_pGrpPoint[iXCnt + 1].y);
#if JTAG_UART
			SendData[4] = (BYTE)(dwData >> 24);
			SendData[5] = (BYTE)(dwData >> 16);
			SendData[6] = (BYTE)(dwData >> 8);
			SendData[7] = (BYTE)(dwData);
#endif
#else
			state = getDataFromRemote(ConnectSocket, m_dwEN673BaseAdr + (dwAddr << 2), 4, WB0, &dwData);
			if (state < 0)
			{
				RxCheck_flag = FALSE;
				str.Format(_T("Fail Write Value. (Address : 0x%X)"), dwAddr);
				goto ENDGAMMAWRITE;
			}

			// Data
			dwData = m_pwRxData[iWriteCnt];

			dwData &= ValSft_L30(BitMask_02); // [31:30] mask
			dwData += (m_Gamma.m_pGrpPoint[iXCnt].y << 16) + (m_Gamma.m_pGrpPoint[iXCnt + 1].y);
#endif
			// Count Up
			iXCnt += 2;

			break;

		case 1: // 2[25:16],3[9:0]
		case 2: // 4[25:16],5[9:0]
		case 3: // 6[25:16],7[9:0]
		case 4: // 8[25:16],9[9:0]
		case 5: // 10[25:16],11[9:0]
		case 6: // 12[25:16],13[9:0]
		case 7: // 14[25:16],15[9:0]
			// Addr
			dwAddr = iStartAddr + iWriteCnt;
#if JTAG_UART
			SendData[2] = (BYTE)((dwAddr & 0xff00) >> 8);
			SendData[3] = (BYTE)(dwAddr & 0x00ff);
#endif

			// Data
			dwData = (m_Gamma.m_pGrpPoint[iXCnt].y << 16) + (m_Gamma.m_pGrpPoint[iXCnt + 1].y);
#if JTAG_UART
			SendData[4] = (BYTE)(dwData >> 24);
			SendData[5] = (BYTE)(dwData >> 16);
			SendData[6] = (BYTE)(dwData >> 8);
			SendData[7] = (BYTE)(dwData);
#endif
			// Count Up
			iXCnt += 2;

			break;

		case 8: // 16[25:16]
			// Addr
			dwAddr = iStartAddr + iWriteCnt;
#if JTAG_UART
			SendData[2] = (BYTE)((dwAddr & 0xff00) >> 8);
			SendData[3] = (BYTE)(dwAddr & 0x00ff);
#endif
			// Data
			dwData = (m_Gamma.m_pGrpPoint[iXCnt].y << 16);
#if JATG_UART
			SendData[4] = (BYTE)(dwData >> 24);
			SendData[5] = (BYTE)(dwData >> 16);
			SendData[6] = (BYTE)(dwData >> 8);
			SendData[7] = (BYTE)(dwData);
#endif
			// Count Up
			iXCnt += 1;
			break;
		}

#if JTAG_UART
		// Send Data
		WriteComm(SendData, 9);

		// Wait
		do{
			Sleep(10);
			state = getDataFromRemote(ConnectSocket, tx_addr, 4, WBCOM, &flag);
			if (state < 0 | iCnt > RETRY)
			{
				RxCheck_flag = FALSE;
				str.Format(_T("Fail Write Value. (Address : 0x%X)"), iStartAddr + iWriteCnt);
				goto ENDGAMMAWRITE;
			}
			if ((((UINT32)flag & 0X0000ffff) == 0xd002) | iiCnt == RETRY)
			{
				iiCnt = 0;
				iCnt++;
				WriteComm(SendData, 9);
			}
			iiCnt++;
		} while (((UINT32)flag & 0X0000ffff) != 0x2002);
#else
		dwData = ntohl(dwData);
		state = setDataFromRemote(ConnectSocket, m_dwEN673BaseAdr + (dwAddr << 2), 4, WB0, &dwData);
		if (state < 0)
		{
			RxCheck_flag = FALSE;
			str.Format(_T("Fail Write Value. (Address : 0x%X)"), iStartAddr + iWriteCnt);
			goto ENDGAMMAWRITE;
		}
#endif
		m_Progress_Loading.SetPos(m_Progress_Loading.GetPos() + 1);
		iWriteCnt++;
		//Sleep(1);
		Wait(1);
	}

	bReturn = TRUE;

ENDGAMMAWRITE:

	delete[] m_pwRxData;

	if (!bReturn)
		AfxMessageBox(str);

	if (!RxCheck_flag)
	{
		EnableCtrl(FALSE);
		ConnectSocket = NULL;
		m_Btn_Connect.SetIcon(IDI_DISCONNECT, NULL);
	}
}

void CGammaDlg::OnBnClickedButtonGammaload()
{
	CString strGmaFile = _T("");
	CString strDefExt = _T("txt");
	CString strFilter = _T("Text Document(*txt)|*.txt||");

	// Open Dialog
	if (!ShowOpenFileDlg(&strGmaFile, strDefExt, strFilter, this))
		return;

	// Open
	if (!LoadGamma(strGmaFile))
		AfxMessageBox(_T("Fail file load."));
}


// ====================================================================================================
// CGammaDlg :: LoadGamma
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
BOOL CGammaDlg::LoadGamma(CString strPath)
{
	int i = 0;
	int iRest = 0; // ��ǥ(,)
	BOOL bReturn = FALSE;
	DWORD* dwGammaVal = NULL;
	CString str = _T("");
	CString strData = _T("");

	CStdioFile GmaFile;
	if (!GmaFile.Open(strPath, CFile::modeRead))
	{
		goto ENDLOADGAMMA;
	}

	//int iPlatformSel = pECMDlg->GetPlatformSel();
	//int iGammaRegNum = GAMMAREGNUM[iPlatformSel];
	int iGammaRegNum = EN673_GAMMAREGNUM;

// ----------------------------------------------------------------------------------------------------
// Read String(�ּ� ����)
	int iSlash1 = -1;
	int iSlashNStart = -1;
	int iSlashNEnd = -1;

	while (GmaFile.ReadString(str))
	{
		ProcessWindowMessage();
		// �¿� ���� ����
		str = str.Trim(_T("\t "));

		// �ּ� ���� ó��
		if (iSlashNStart >= 0)
		{
			iSlashNEnd = str.Find(_T("*/"));
			if (iSlashNEnd >= 0) // ������ �ּ� ��
			{
				strData.Left(iSlashNStart);
				strData = strData + str.Right(iSlashNEnd);
				continue;
			}
		}
		else
		{
			// �ּ�(������)
			iSlashNStart = str.Find(_T("/*"));
			if (iSlashNStart == -1)
			{
				// �ּ�(����)
				iSlash1 = str.Find(_T("//"));
				if (iSlash1 >= 0)
				{
					str = str.Left(iSlash1);
				}
			}
		}
		strData = strData + str;
		//Sleep(1);
		Wait(1);
	}

	int iBrkS = strData.Find(_T("{"));
	if (iBrkS == -1) goto ENDLOADGAMMA;

	int iBrkE = strData.Find(_T("}"), iBrkS);
	if (iBrkE == -1) goto ENDLOADGAMMA;

	strData = strData.Mid(iBrkS + 1, iBrkE - iBrkS - 1);
	strData = strData.Trim(_T("\t "));

// ----------------------------------------------------------------------------------------------------
// Data �и�
	dwGammaVal = new DWORD[iGammaRegNum];
	for (i = 0; i < iGammaRegNum; i++)
	{
		// ����
		strData = strData.TrimLeft(_T("\t ")); // ���� ����

		// 
		iRest = strData.Find(_T(","));
		if (i < iGammaRegNum - 1) {
			if (iRest == -1) { goto ENDLOADGAMMA; } // ��ǥ �ʿ���
			str = strData.Left(iRest);
		}
		else {
			if (iRest >= 0) { goto ENDLOADGAMMA; } // ��ǥ �ʿ����
			str = strData;
		}

		if (str.Find(_T("0x") == 0))
		{
			str = str.Right(str.GetLength() - 2); // 0x ����
			if (!CheckHex(str)) { goto ENDLOADGAMMA; };
			dwGammaVal[i] = HexToDec(str);
		}
		else
		{
			if (!CheckDec(str)) { goto ENDLOADGAMMA; };
			dwGammaVal[i] = _ttoi(str);
		}

		strData = strData.Right(strData.GetLength() - iRest - 1);
	}
// ----------------------------------------------------------------------------------------------------
// �� ����
	int iCnt = 0;
	DWORD dwData = 0;

	for (i = 0; i < iGammaRegNum; i++)
	{
		dwData = dwGammaVal[i];
		switch (i)
		{
		case 0: // 0[25:16],1[9:0]
		case 1: // 2[25:16],3[9:0]
		case 2: // 4[25:16],5[9:0]
		case 3: // 6[25:16],7[9:0]
		case 4: // 8[25:16],9[9:0]
		case 5: // 10[25:16],11[9:0]
		case 6: // 12[25:16],13[9:0]
		case 7: // 14[25:16],15[9:0]
			m_Gamma.SetGammaY(iCnt, (dwData >> 16) & 0x3FF);
			m_Gamma.SetGammaY(iCnt + 1, dwData & 0x3FF);
			iCnt += 2;
			break;

		case 8: // 16[25:16]
			m_Gamma.SetGammaY(iCnt, (dwData >> 16) & 0x3FF);
			iCnt += 1;
			break;
		}
	}

	bReturn = TRUE;

ENDLOADGAMMA:
	if (dwGammaVal != NULL)
		delete[] dwGammaVal;

	m_Gamma.UpdateGraph();

	return bReturn;
}


void CGammaDlg::OnBnClickedButtonGammasave()
{
	CString strGmaFile = _T("");
	CString strDefExt = _T("txt");
	CString strFilter = _T("Text Document(*txt)|*.txt||");

	// Save Dialog
	if (!ShowSaveFileDlg(&strGmaFile, strDefExt, strFilter, this))
		return;

	// Save
	if (SaveGamma(strGmaFile))
	{
		AfxMessageBox(_T("Save Complate!"));
	}
	else
	{
		CFileFind ffind;
		if (ffind.FindFile(strGmaFile))
		{
			ffind.Close();
			DeleteFileW(strGmaFile);
		}

		AfxMessageBox(_T("Fail save file."));
	}
}


// ====================================================================================================
// CGammaDlg :: SaveGamma
// ----------------------------------------------------------------------------------------------------
/*
- ����� �����ִ� YGMA_ON, CGMA_ON ���� �� �Ű澲�� �ʾƵ� ��.
*/
// ====================================================================================================
BOOL CGammaDlg::SaveGamma(CString strPath)
{
	int i = 0;
	BOOL bReturn = FALSE;
	CString str = _T("");

	CStdioFile GmaFile;
	GmaFile.Open(strPath, CFile::modeCreate | CFile::modeWrite);

	CString strTitle = _T("");
	strTitle = GmaFile.GetFileTitle();
	if (strTitle.Find(_T(".txt")))
	{
		strTitle = strTitle.Left(strTitle.GetLength() - 4);
	}
	//int iPlatformSel = pECMDlg->GetPlatformSel();
	//int iGammaRegNum = GAMMAREGNUM[iPlatformSel];
	int iGammaRegNum = EN673_GAMMAREGNUM;
	
	int iXCnt = 0;

	str.Format(_T("%s[%d]={\n"), strTitle, iGammaRegNum);
	GmaFile.WriteString(str);

// ----------------------------------------------------------------------------------------------------
	for (i = 0; i < iGammaRegNum; i++)
	{
		switch (i)
		{
		case 0: // 0[25:16],1[9:0]
		case 1: // 2[25:16],3[9:0]
		case 2: // 4[25:16],5[9:0]
		case 3: // 6[25:16],7[9:0]
		case 4: // 8[25:16],9[9:0]
		case 5: // 10[25:16],11[9:0]
		case 6: // 12[25:16],13[9:0]
		case 7: // 14[25:16],15[9:0]
			str.Format(_T("%08x,\n"), ((m_Gamma.m_pGrpPoint[iXCnt].y << 16) & 0x3FF0000) |
				(m_Gamma.m_pGrpPoint[iXCnt + 1].y & 0x3FF));
			str = _T("0x") + str;
			iXCnt += 2;
			break;

		case 8: // 16[25:16]
			str.Format(_T("%08x\n"), (m_Gamma.m_pGrpPoint[iXCnt].y << 16) & 0x3FF0000);
			str = _T("0x") + str;
			iXCnt += 1;
			break;
		}

		GmaFile.WriteString(str);
	}

// ----------------------------------------------------------------------------------------------------
//END
	str.Format(_T("};\n"));
	GmaFile.WriteString(str);

	bReturn = TRUE;

//ENDSAVEGAMMA:

	GmaFile.Close();

	return bReturn;
}


// ====================================================================================================
// CGammaDlg :: SetPlatform
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CGammaDlg::SetPlatform()
{
	int i = 0;
	UINT uiXStepNum = 0;
	UINT* uiXStep = NULL;

	UINT uiXPoint17[17] = { 0, 2, 4, 8, 16, 32, 64, 128, 192, 256, 320, 384, 512, 640, 768, 896, 1023 };

	// ----------------------------------------------------------------------------------------------------
	uiXStepNum = 17;
	uiXStep = new UINT[uiXStepNum];
	memcpy(uiXStep, uiXPoint17, uiXStepNum*sizeof(int));


	m_Gamma.SetGammaStep(uiXStepNum, uiXStep);

	if (uiXStep != NULL) {
		delete[] uiXStep;
		uiXStep = NULL;
	}

	// Zoom
	m_Gamma.m_iZoomRate = 100; // ���� ������� ����
	m_Gamma.m_ptMove.x = 0;
	m_Gamma.m_ptMove.y = 0;

	// Undo (Ctrl+Z)
	InitUndo();

	m_Gamma.UpdateGraph(); // �ܰ谡 ����� �� �ֱ� ������ ������ �ٽ� �׷��־�� ��
}


void CGammaDlg::OnCbnSelchangeComboGammazoom()
{
	CString strZoom = _T("");
	m_Cbo_GammaZoom.GetLBText(m_Cbo_GammaZoom.GetCurSel(), strZoom);

	if (CheckDec(strZoom))
		m_Gamma.SetGammaZoomRate(_ttoi(strZoom));

	// Draw Graph
	m_Gamma.UpdateGraph();

	// SetFocus
	m_Pic_GammaGraph.SetFocus();

}


// ====================================================================================================
// CGammaDlg :: OnCbnSelchangeComboGammatable
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CGammaDlg::OnChangeGammazoom()
{
	// SetGammaZoomRate�� �����ؾߵ�
	int iZoom = 0;
	CString strZoom = _T("");
	m_Cbo_GammaZoom.GetWindowTextW(strZoom);

	// Check
	if (!CheckDec(strZoom))
	{
		strZoom.Format(_T("%d"), m_Gamma.m_iZoomRate);
		m_Cbo_GammaZoom.SetWindowTextW(strZoom);
		return;
	}

	// Calculate
	iZoom = _ttoi(strZoom);
	if (iZoom < MINZOOM)
	{
		m_Cbo_GammaZoom.SetCurSel(0);
		iZoom = MINZOOM;
	}
	else if (iZoom > MAXZOOM)
	{
		iZoom = MAXZOOM;
		m_Cbo_GammaZoom.SetCurSel(m_Cbo_GammaZoom.GetCount() - 1);
	}

	// Apply
	m_Gamma.m_iZoomRate = iZoom;

	// Draw Graph
	m_Gamma.UpdateGraph();

	// SetFocus
	m_Pic_GammaGraph.SetFocus();
}


// ====================================================================================================
// CGammaDlg :: EnableCtrl
// ----------------------------------------------------------------------------------------------------
/*
LoadingThreadGamma (����, ��)
*/
// ====================================================================================================
void CGammaDlg::EnableCtrl(BOOL bEnable)
{
	BOOL bEnableUart = !bEnable ? FALSE : TRUE;

	// ISP Register
	if (bEnable)
		m_Cbo_GammaTable.EnableWindow(TRUE);
	else
		m_Cbo_GammaTable.EnableWindow(FALSE);

#if USEGAMMAREAD==1
	m_Btn_GammaRead.EnableWindow(!pComPort->m_bConnected ? FALSE : bEnable);
#endif
	m_Btn_GammaWrite.EnableWindow(bEnableUart);
}


// ====================================================================================================
// CGammaDlg::InitUndo
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CGammaDlg::InitUndo()
{
	int i = 0;

	m_iUndoNum = 0;
	m_iUndoCnt = 0;

	if (m_iUndo != NULL)
		delete[] m_iUndo;

	m_iUndo = new GAMMAUNDO[UNDOMAX];

	for (i = 0; i < UNDOMAX; i++)
	{
		m_iUndo->iStep = 0;
		m_iUndo->iValue = 0;
	}
}

// ====================================================================================================
// CGammaDlg::SetUndo
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CGammaDlg::SetUndo(int iStep, int iValue)
{
	int i = 0;

	// Check :: m_iUndoCnt
	if (m_iUndoCnt != 0)
	{
		int iSpace = m_iUndoNum - m_iUndoCnt - 1;

		for (i = 0; i < UNDOMAX; i++)
		{
			if (i < m_iUndoNum - m_iUndoCnt)
			{
				m_iUndo[i].iStep = m_iUndo[i + m_iUndoCnt].iStep;
				m_iUndo[i].iValue = m_iUndo[i + m_iUndoCnt].iValue;
			}
			else
			{
				m_iUndo[i].iStep = 0;
				m_iUndo[i].iValue = 0;
			}
		}

		m_iUndoNum = m_iUndoNum - m_iUndoCnt;
		m_iUndoCnt = 0;
	}

	// Set Undo
	if (m_iUndoNum <= 0) // m_iUndoNum = 0
	{
		m_iUndoNum++;

		m_iUndo[0].iStep = iStep;
		m_iUndo[0].iValue = iValue;
	}
	else if (m_iUndoNum < UNDOMAX) // m_iUndoNum = 1 ~ (UNDOMAX-1)
	{
		m_iUndoNum++;

		for (i = m_iUndoNum - 1; i > 0; i--)
		{
			m_iUndo[i].iStep = m_iUndo[i - 1].iStep;
			m_iUndo[i].iValue = m_iUndo[i - 1].iValue;
		}

		m_iUndo[0].iStep = iStep;
		m_iUndo[0].iValue = iValue;
	}
	else // m_iUndoNum = UNDOMAX
	{
		for (i = UNDOMAX - 1; i > 0; i--)
		{
			m_iUndo[i].iStep = m_iUndo[i - 1].iStep;
			m_iUndo[i].iValue = m_iUndo[i - 1].iValue;
		}

		m_iUndo[0].iStep = iStep;
		m_iUndo[0].iValue = iValue;
	}
}

// ====================================================================================================
// CGammaDlg::OnUndo
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CGammaDlg::OnUndo() // Undo ���� (Ctrl+Z)
{
	if (m_iUndoNum == 0) return;
	if (m_iUndoCnt >= m_iUndoNum) return;

	if (m_iUndoCnt < m_iUndoNum)
	{
		int iStep = m_iUndo[m_iUndoCnt].iStep;

		m_Gamma.m_uiPointSel = iStep;
		m_Gamma.m_pGrpPoint[iStep].y = m_iUndo[m_iUndoCnt].iValue;
	}

	m_iUndoCnt++;

	m_Gamma.UpdateGraph();
}

// ====================================================================================================
// CGammaDlg::OnRedo
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CGammaDlg::OnRedo() // Redo ���� (Ctrl+Y)
{
	if (m_iUndoNum == (UNDOMAX - 1)) return;
}


void CGammaDlg::OnBnClickedButtonConnect()
{
#if 0
	UINT32 read = 0;
	int state = -1;

	if (ConnectSocket)
	{
		state = getDataFromRemote(ConnectSocket, 0x06fff004, 4, WBCOM, &read);
	}
	if ((state < 0) || !ConnectSocket)
	{
		ConnectSocket = NetCon(ch_ip, ch_port);
		if (ConnectSocket <= 0)
			ConnectSocket = NULL;
	}

	if (ConnectSocket) {
		EnableCtrl(TRUE);
		m_Btn_Connect.SetIcon(IDI_CONNECT, NULL);
	}
	else {
		EnableCtrl(FALSE);
		m_Btn_Connect.SetIcon(IDI_DISCONNECT, NULL);
	}
#endif
}


void CGammaDlg::OpenKeyFile()
{
	DWORD64 dwKeyPw = 0;
	CString strKeyFile = ReadIni(SEC_SETTING, KEY_PARAMETERKEY, DEF_PARAMETERKEY);
	CString strPath = _T("");
	CString str = _T("");
	CString strKeyPw = _T("");
	CString strKey = _T("");

	if (strKeyFile != _T("NULL"))
	{
		// ���� Key��
		dwKeyPw = _ttoi(strKeyFile);

		// ���� ����
		TCHAR cDir[256];
		::GetWindowsDirectory(cDir, 256);
		strPath.Format(_T("%s\\Temp\\TFP%x.tmp"), cDir, dwKeyPw);

		CStdioFile strFile;
		if (!strFile.Open(strPath, CFile::modeRead))
			goto ERRORKEY;

		// ��ȯ
		strFile.ReadString(str);
		strFile.Close();

		// ��������
		str = str.Right(4) + str.Left(str.GetLength() - 4);

		// 16���� Ȯ��
		if (!CheckHex(str))
			goto ERRORKEY;

		// 16���� -> 10����
		DWORD64 dwKey = HexToDec(str);

		// KeyPassword ����
		strKeyPw = str.Mid(0, 1) + str.Mid(5, 1) + str.Mid(10, 1);

		strKey = str.Mid(1, 4) + str.Mid(6, 4);
		if (!CheckHex(strKey))
			goto ERRORKEY;

		if (dwKeyPw == _ttoi(strKeyPw))
		{
			m_strKey = strKey;
			m_strKeyPw = strKeyPw;
			return;
		}
		else
			goto ERRORKEY;
	}

ERRORKEY:
	// strKeyPw
	srand((unsigned int)time(NULL));
	m_strKeyPw.Format(_T("%d"), rand() % 999 + 100); // ��������

	// default
	m_strKey = _T("12345678");
}

// ====================================================================================================
// CParameterDlg::SaveKeyFile
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CGammaDlg::SaveKeyFile()
{
	CString str = _T("");

	TCHAR cDir[256];
	::GetWindowsDirectory(cDir, 256);
	CString strPath = _T("");

	// ----------------------------------------------------------------------------------------------------
	// ��ȯ
	// 1. KeyPw �߰�
	// Key(Hex) : @
	// KeyPw(Dec) : *
	// *@@@@*@@@@*
	CString strKey = m_strKeyPw.Mid(0, 1) + m_strKey.Left(4) + m_strKeyPw.Mid(1, 1) + m_strKey.Right(4) + m_strKeyPw.Mid(2, 1);

	// 2. ��������
	str = strKey.Right(strKey.GetLength() - 4) + strKey.Left(4);

	// ----------------------------------------------------------------------------------------------------
	// ����
	// ����
	DWORD dwKeyPw = _ttoi(m_strKeyPw);
	strPath.Format(_T("%s\\Temp\\TFP%x.tmp"), cDir, dwKeyPw);
	CStdioFile strFile;

	if (strFile.Open(strPath, CFile::modeReadWrite | CFile::modeCreate))
	{
		strFile.WriteString(str);

		strFile.Close();
	}

	// ecm.ini
	WriteIni(SEC_SETTING, KEY_PARAMETERKEY, m_strKeyPw);
}


void CGammaDlg::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case ID_CHECK_TIMER:
		AfxBeginThread(State_Check_Thread, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
		break;
	case ID_CONNECT_TIMER:
		AfxBeginThread(Connect_Check_Thread, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CGammaDlg::Check_Timer_On()
{
	m_CheckTimerID = SetTimer(ID_CHECK_TIMER, Check_Time, NULL);
}

void CGammaDlg::Check_Timer_Off()
{
	if (m_CheckTimerID)
	{
		if (this->GetSafeHwnd())
			KillTimer(m_CheckTimerID);
		m_CheckTimerID = 0;
	}
}

void CGammaDlg::Connect_Timer_On()
{
	m_ConnectTimerID = SetTimer(ID_CONNECT_TIMER, Connect_Time, NULL);
}

void CGammaDlg::Connect_Timer_Off()
{
	if (m_ConnectTimerID)
	{
		if (this->GetSafeHwnd())
			KillTimer(m_ConnectTimerID);
		m_ConnectTimerID = 0;
	}
}


BOOL Invalidate_flsg = FALSE;
UINT State_Check_Thread(LPVOID pParam)
{
	int state = -1;

	if (StateSocket > 0)
		state = sendMsg(StateSocket, "rem_check ");
	else
		goto DISCONNECT;

	char ocd_flag;
	if (state != -1)
		state = recv(StateSocket, &ocd_flag, sizeof(ocd_flag), 0);
	else
		goto DISCONNECT;

	if ((state != -1))
	{
		if (ocd_flag == '0')
		{
			if (!Invalidate_flsg)
			{
				pGammaDlg->EnableCtrl(TRUE);
				pGammaDlg->m_Btn_Connect.SetIcon(IDI_CONNECT, NULL);

				Invalidate_flsg = TRUE;
			}

			return 0;
		}
		else
		{
			goto DISCONNECT;
		}
	}

DISCONNECT:
	pGammaDlg->EnableCtrl(FALSE);
	pGammaDlg->m_Btn_Connect.SetIcon(IDI_DISCONNECT, NULL);

	NetClo(ConnectSocket);
	ConnectSocket = NULL;

	Wait(1);

	NetClo(StateSocket);
	StateSocket = NULL;

	pGammaDlg->Check_Timer_Off();
	pGammaDlg->Connect_Timer_On();

	Invalidate_flsg = FALSE;

	return 0;
}



UINT Connect_Check_Thread(LPVOID pParam)
{
	ConnectSocket = NetCon(pGammaDlg->ch_ip, pGammaDlg->ch_port);
	//Sleep(1);
	Wait(1);
	StateSocket = NetCon(pGammaDlg->ch_ip, pGammaDlg->ch_port);

	if (ConnectSocket <= 0 || StateSocket <= 0)
	{
		NetClo(ConnectSocket);
		ConnectSocket = NULL;

		Wait(1);

		NetClo(StateSocket);
		StateSocket = NULL;
	}
	else
	{
		Invalidate_flsg = FALSE;

		pGammaDlg->Connect_Timer_Off();
		pGammaDlg->Check_Timer_On();
	}
	return 0;
}