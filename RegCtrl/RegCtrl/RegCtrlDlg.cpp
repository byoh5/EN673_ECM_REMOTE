
// RegCtrlDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "RegCtrl.h"
#include "RegCtrlDlg.h"
#include "afxdialogex.h"
#include "afxwin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define ISPtoJTAG
#define DEFAULT_PORT "5556"
DWORD m_dwEN673BaseAdr;		// EN673 Dongle Base Address

// Thread Function
UINT			LoadingThread(LPVOID pParam);
UINT			DispRegInfoThread(LPVOID pParam);			// Display ISP Infomation
UINT			ReadAllThread(LPVOID pParam);				// All Read
UINT			WriteAllThread(LPVOID pParam);				// All Write

const UINT  ID_CHECK_TIMER = 100;
const UINT  ID_CONNECT_TIMER = 200;
UINT	State_Check_Thread(LPVOID pParam);
UINT	Connect_Check_Thread(LPVOID pParam);

#define		Check_Time		1000
#define		Connect_Time	5000

// CRegCtrlDlg ��ȭ ����
CRegCtrlDlg::CRegCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRegCtrlDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ECM);
}

void CRegCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_REGCLOSE, m_Btn_Close);
	DDX_Control(pDX, IDC_EDIT_HASFILE, m_Edit_HasFile);
	DDX_Control(pDX, IDC_EDIT_MNEFILE, m_Edit_MneFile);
	DDX_Control(pDX, IDC_BUTTON_OPENHAS, m_Btn_OpenHas);
	DDX_Control(pDX, IDC_BUTTON_SAVEHAS, m_Btn_SaveHas);
	DDX_Control(pDX, IDC_BUTTON_OPENMNE, m_Btn_OpenMne);
	DDX_Control(pDX, IDC_BUTTON_SAVEMNE, m_Btn_SaveMne);
	DDX_Control(pDX, IDC_COMBO_SEARCH, m_Cbo_Search);
	DDX_Control(pDX, IDC_COMBO_SEARCHOPTION, m_Cbo_SearchOption);
	DDX_Control(pDX, IDC_BUTTON_SEARCH, m_Btn_Search);
	DDX_Control(pDX, IDC_LOADING_REG, m_PicLoading);
	DDX_Control(pDX, IDC_SPIN_VALUE, m_Spin_Value);
	DDX_Control(pDX, IDC_BUTTON_REGREAD, m_Btn_RegRead);
	DDX_Control(pDX, IDC_BUTTON_REGWRITE, m_Btn_RegWrite);
	DDX_Control(pDX, IDC_SPIN_READ, m_Spin_Read);
	DDX_Control(pDX, IDC_SPIN_WRITE, m_Spin_Write);
	DDX_Control(pDX, IDC_COMBO_READSTART, m_Cbo_ReadStart);
	DDX_Control(pDX, IDC_COMBO_READEND, m_Cbo_ReadEnd);
	DDX_Control(pDX, IDC_BUTTON_REGREADALL, m_Btn_RegReadAll);
	DDX_Control(pDX, IDC_COMBO_WRITESTART, m_Cbo_WriteStart);
	DDX_Control(pDX, IDC_COMBO_WRITEEND, m_Cbo_WriteEnd);
	DDX_Control(pDX, IDC_BUTTON_REGWRITEALL, m_Btn_RegWriteAll);
	DDX_Control(pDX, IDC_EDIT_DESCRIPTION, m_Edit_Description);
	DDX_Control(pDX, IDC_EDIT_DESFILE, m_Edit_DesFile);
	DDX_Control(pDX, IDC_BUTTON_NEWDES, m_Btn_NewDes);
	DDX_Control(pDX, IDC_BUTTON_OPENDES, m_Btn_OpenDes);
	DDX_Control(pDX, IDC_BUTTON_SAVEDES, m_Btn_SaveDes);
	DDX_Control(pDX, IDC_CHECK_FDBACKREAD, m_Chk_FeedBackRead);
	DDX_Control(pDX, IDC_CHECK_FDBACKWRITE, m_Chk_FeedBackWrite);
	DDX_Control(pDX, IDC_BUTTON_CLEARRX, m_Btn_ClearRx);
	DDX_Control(pDX, IDC_BUTTON_BIT31, m_Btn_Bit[31]);
	DDX_Control(pDX, IDC_BUTTON_BIT30, m_Btn_Bit[30]);
	DDX_Control(pDX, IDC_BUTTON_BIT29, m_Btn_Bit[29]);
	DDX_Control(pDX, IDC_BUTTON_BIT28, m_Btn_Bit[28]);
	DDX_Control(pDX, IDC_BUTTON_BIT27, m_Btn_Bit[27]);
	DDX_Control(pDX, IDC_BUTTON_BIT26, m_Btn_Bit[26]);
	DDX_Control(pDX, IDC_BUTTON_BIT25, m_Btn_Bit[25]);
	DDX_Control(pDX, IDC_BUTTON_BIT24, m_Btn_Bit[24]);
	DDX_Control(pDX, IDC_BUTTON_BIT23, m_Btn_Bit[23]);
	DDX_Control(pDX, IDC_BUTTON_BIT22, m_Btn_Bit[22]);
	DDX_Control(pDX, IDC_BUTTON_BIT21, m_Btn_Bit[21]);
	DDX_Control(pDX, IDC_BUTTON_BIT20, m_Btn_Bit[20]);
	DDX_Control(pDX, IDC_BUTTON_BIT19, m_Btn_Bit[19]);
	DDX_Control(pDX, IDC_BUTTON_BIT18, m_Btn_Bit[18]);
	DDX_Control(pDX, IDC_BUTTON_BIT17, m_Btn_Bit[17]);
	DDX_Control(pDX, IDC_BUTTON_BIT16, m_Btn_Bit[16]);
	DDX_Control(pDX, IDC_BUTTON_BIT15, m_Btn_Bit[15]);
	DDX_Control(pDX, IDC_BUTTON_BIT14, m_Btn_Bit[14]);
	DDX_Control(pDX, IDC_BUTTON_BIT13, m_Btn_Bit[13]);
	DDX_Control(pDX, IDC_BUTTON_BIT12, m_Btn_Bit[12]);
	DDX_Control(pDX, IDC_BUTTON_BIT11, m_Btn_Bit[11]);
	DDX_Control(pDX, IDC_BUTTON_BIT10, m_Btn_Bit[10]);
	DDX_Control(pDX, IDC_BUTTON_BIT9, m_Btn_Bit[9]);
	DDX_Control(pDX, IDC_BUTTON_BIT8, m_Btn_Bit[8]);
	DDX_Control(pDX, IDC_BUTTON_BIT7, m_Btn_Bit[7]);
	DDX_Control(pDX, IDC_BUTTON_BIT6, m_Btn_Bit[6]);
	DDX_Control(pDX, IDC_BUTTON_BIT5, m_Btn_Bit[5]);
	DDX_Control(pDX, IDC_BUTTON_BIT4, m_Btn_Bit[4]);
	DDX_Control(pDX, IDC_BUTTON_BIT3, m_Btn_Bit[3]);
	DDX_Control(pDX, IDC_BUTTON_BIT2, m_Btn_Bit[2]);
	DDX_Control(pDX, IDC_BUTTON_BIT1, m_Btn_Bit[1]);
	DDX_Control(pDX, IDC_BUTTON_BIT0, m_Btn_Bit[0]);
	DDX_Control(pDX, IDC_STATIC_NAME, m_Static_Name);
	DDX_Control(pDX, IDC_STATIC_TXVALUE, m_Static_Txvalue);
	DDX_Control(pDX, IDC_BUTTON_MINIMIZE, m_Btn_Minimize);
	DDX_Control(pDX, IDC_BUTTON_CONNECT, m_Btn_Connect);
}

BEGIN_MESSAGE_MAP(CRegCtrlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_NOTIFY(TVN_BEGINLABELEDIT, IDC_REGTREELIST, &CRegCtrlDlg::OnBeginLabelEditTreelist)
	ON_NOTIFY(TVN_SELCHANGED, IDC_REGTREELIST, &CRegCtrlDlg::OnSelChangedTreelist)
	ON_NOTIFY(TVN_ENDLABELEDIT, IDC_REGTREELIST, &CRegCtrlDlg::OnEndLabelEditTreelist)
	ON_BN_CLICKED(IDC_BUTTON_REGCLOSE, &CRegCtrlDlg::OnBnClickedButtonRegclose)
	ON_BN_CLICKED(IDC_BUTTON_OPENHAS, &CRegCtrlDlg::OnBnClickedButtonOpenhas)
	ON_BN_CLICKED(IDC_BUTTON_OPENMNE, &CRegCtrlDlg::OnBnClickedButtonOpenmne)
	ON_BN_CLICKED(IDC_BUTTON_SAVEHAS, &CRegCtrlDlg::OnBnClickedButtonSavehas)
	ON_BN_CLICKED(IDC_BUTTON_SAVEMNE, &CRegCtrlDlg::OnBnClickedButtonSavemne)
	ON_CBN_SELCHANGE(IDC_COMBO_SEARCH, &CRegCtrlDlg::OnCbnSelchangeComboSearch)
	ON_CBN_SELCHANGE(IDC_COMBO_SEARCHOPTION, &CRegCtrlDlg::OnCbnSelchangeComboSearchoption)
	ON_CBN_EDITUPDATE(IDC_COMBO_SEARCH, &CRegCtrlDlg::OnCbnEditchangeComboSearch)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CRegCtrlDlg::OnBnClickedButtonSearch)
	ON_BN_CLICKED(IDC_BUTTON_BIT31, &CRegCtrlDlg::OnBnClickedButtonBit31)
	ON_BN_CLICKED(IDC_BUTTON_BIT30, &CRegCtrlDlg::OnBnClickedButtonBit30)
	ON_BN_CLICKED(IDC_BUTTON_BIT29, &CRegCtrlDlg::OnBnClickedButtonBit29)
	ON_BN_CLICKED(IDC_BUTTON_BIT28, &CRegCtrlDlg::OnBnClickedButtonBit28)
	ON_BN_CLICKED(IDC_BUTTON_BIT27, &CRegCtrlDlg::OnBnClickedButtonBit27)
	ON_BN_CLICKED(IDC_BUTTON_BIT26, &CRegCtrlDlg::OnBnClickedButtonBit26)
	ON_BN_CLICKED(IDC_BUTTON_BIT25, &CRegCtrlDlg::OnBnClickedButtonBit25)
	ON_BN_CLICKED(IDC_BUTTON_BIT24, &CRegCtrlDlg::OnBnClickedButtonBit24)
	ON_BN_CLICKED(IDC_BUTTON_BIT23, &CRegCtrlDlg::OnBnClickedButtonBit23)
	ON_BN_CLICKED(IDC_BUTTON_BIT22, &CRegCtrlDlg::OnBnClickedButtonBit22)
	ON_BN_CLICKED(IDC_BUTTON_BIT21, &CRegCtrlDlg::OnBnClickedButtonBit21)
	ON_BN_CLICKED(IDC_BUTTON_BIT20, &CRegCtrlDlg::OnBnClickedButtonBit20)
	ON_BN_CLICKED(IDC_BUTTON_BIT19, &CRegCtrlDlg::OnBnClickedButtonBit19)
	ON_BN_CLICKED(IDC_BUTTON_BIT18, &CRegCtrlDlg::OnBnClickedButtonBit18)
	ON_BN_CLICKED(IDC_BUTTON_BIT17, &CRegCtrlDlg::OnBnClickedButtonBit17)
	ON_BN_CLICKED(IDC_BUTTON_BIT16, &CRegCtrlDlg::OnBnClickedButtonBit16)
	ON_BN_CLICKED(IDC_BUTTON_BIT15, &CRegCtrlDlg::OnBnClickedButtonBit15)
	ON_BN_CLICKED(IDC_BUTTON_BIT14, &CRegCtrlDlg::OnBnClickedButtonBit14)
	ON_BN_CLICKED(IDC_BUTTON_BIT13, &CRegCtrlDlg::OnBnClickedButtonBit13)
	ON_BN_CLICKED(IDC_BUTTON_BIT12, &CRegCtrlDlg::OnBnClickedButtonBit12)
	ON_BN_CLICKED(IDC_BUTTON_BIT11, &CRegCtrlDlg::OnBnClickedButtonBit11)
	ON_BN_CLICKED(IDC_BUTTON_BIT10, &CRegCtrlDlg::OnBnClickedButtonBit10)
	ON_BN_CLICKED(IDC_BUTTON_BIT9, &CRegCtrlDlg::OnBnClickedButtonBit9)
	ON_BN_CLICKED(IDC_BUTTON_BIT8, &CRegCtrlDlg::OnBnClickedButtonBit8)
	ON_BN_CLICKED(IDC_BUTTON_BIT7, &CRegCtrlDlg::OnBnClickedButtonBit7)
	ON_BN_CLICKED(IDC_BUTTON_BIT6, &CRegCtrlDlg::OnBnClickedButtonBit6)
	ON_BN_CLICKED(IDC_BUTTON_BIT5, &CRegCtrlDlg::OnBnClickedButtonBit5)
	ON_BN_CLICKED(IDC_BUTTON_BIT4, &CRegCtrlDlg::OnBnClickedButtonBit4)
	ON_BN_CLICKED(IDC_BUTTON_BIT3, &CRegCtrlDlg::OnBnClickedButtonBit3)
	ON_BN_CLICKED(IDC_BUTTON_BIT2, &CRegCtrlDlg::OnBnClickedButtonBit2)
	ON_BN_CLICKED(IDC_BUTTON_BIT1, &CRegCtrlDlg::OnBnClickedButtonBit1)
	ON_BN_CLICKED(IDC_BUTTON_BIT0, &CRegCtrlDlg::OnBnClickedButtonBit0)
	ON_BN_CLICKED(IDC_BUTTON_REGREAD, &CRegCtrlDlg::OnBnClickedButtonRegread)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_READ, &CRegCtrlDlg::OnDeltaposSpinRead)
	ON_BN_CLICKED(IDC_BUTTON_REGREADALL, &CRegCtrlDlg::OnBnClickedButtonRegreadall)
	ON_BN_CLICKED(IDC_BUTTON_REGWRITE, &CRegCtrlDlg::OnBnClickedButtonRegwrite)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_WRITE, &CRegCtrlDlg::OnDeltaposSpinWrite)
	ON_BN_CLICKED(IDC_BUTTON_REGWRITEALL, &CRegCtrlDlg::OnBnClickedButtonRegwriteall)
	ON_BN_CLICKED(IDC_BUTTON_OPENDES, &CRegCtrlDlg::OnBnClickedButtonOpendes)
	ON_BN_CLICKED(IDC_BUTTON_SAVEDES, &CRegCtrlDlg::OnBnClickedButtonSavedes)
	ON_EN_CHANGE(IDC_EDIT_DESCRIPTION, &CRegCtrlDlg::OnEnChangeEditDescription)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_VALUE, &CRegCtrlDlg::OnDeltaposSpinValue)
	ON_BN_CLICKED(IDC_BUTTON_CLEARRX, &CRegCtrlDlg::OnBnClickedButtonClearrx)
	ON_BN_CLICKED(IDC_BUTTON_NEWDES, &CRegCtrlDlg::OnBnClickedButtonNewdes)
	ON_BN_CLICKED(IDC_BUTTON_MINIMIZE, &CRegCtrlDlg::OnBnClickedButtonMinimize)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CRegCtrlDlg::OnBnClickedButtonConnect)
	ON_WM_TIMER()
	ON_MESSAGE(WM_REG_ENDLABELEDIT, &CRegCtrlDlg::OnRegEndLabelEdit)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CRegCtrlDlg �޽��� ó����

BOOL CRegCtrlDlg::OnInitDialog()
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
	SetWindowText(DLG_REG);

	int i = 0;

	pRegDlg = this;

	int x = ReadIni(SEC_WININFO, KEY_REGDLGLEFT, DEF_REGDLGLEFT);
	int y = ReadIni(SEC_WININFO, KEY_REGDLGTOP, DEF_REGDLGTOP);

	SetWindowPos(NULL, x, y, 0, 0, SWP_NOSIZE);
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
// Control
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

// ----------------------------------------------------------------------------------------------------
// Draw Background
	DrawWinBg((CWnd*)this, &m_bmpBg, DLG_REG);

// ----------------------------------------------------------------------------------------------------
// Initial Variable
	// Has, Mne, Des Data
	// Addr
	m_iAddr = 0;

	// Data
	m_Has = NULL;
	m_Mne = NULL;
	m_Des = NULL;

	// Open Flag
	m_bOpenHas = FALSE;
	m_bOpenMne = FALSE;
	m_bOpenDes = FALSE;

	m_iHasNum = 0;
	m_iMneNum = 0;
	m_iDesNum = 0;

	m_bInitTree = FALSE;

	m_bUpdateHas = FALSE;
	m_bUpdateMne = FALSE;
	m_bUpdateDes = FALSE;

	m_hItem = NULL;
	m_hSelItem = NULL;
	m_hOldItem = NULL;

	m_iSelAddr = 0;
	m_iSelCol = 0;
	m_strSelTx = _T("");
	m_strBeforeTx = _T("");

	m_bRunCmd = FALSE;

	m_iSearchIdx = 0;
	m_iSearchAddrNum = 0;
	m_iSearchNameNum = 0;
	for (i = 0; i < 10; i++){
		m_strSearchAddr[i] = _T("");
		m_strSearchName[i] = _T("");
	}

	m_bLoading = FALSE;

	m_bESC = FALSE;
	m_bEnter = FALSE;
	m_bEdit = FALSE;
	m_bLabelEdit = FALSE;
	m_bPressedCtrl = FALSE;
	m_iEditAddr = 0;

	m_bStopAll = FALSE;

// ----------------------------------------------------------------------------------------------------
// Control
	// Search
	m_Cbo_SearchOption.AddString(_T("Addr"));
	m_Cbo_SearchOption.AddString(_T("Name"));
	m_Cbo_SearchOption.SetCurSel(0);
	for (i = 0; i < 32; i++)
	{
		m_Btn_Bit[i].m_iBitNum = i;
		m_Btn_Bit[i].DrawBorder(FALSE);
		EnableBtnBit(i, FALSE);
	}

	m_Static_Name.SetWindowTextW(_T(""));

	m_Btn_OpenHas.SetBitmaps(IDB_OPEN, RGB(255, 0, 255));
	m_Btn_SaveHas.SetBitmaps(IDB_SAVE, RGB(255, 0, 255));
	m_Btn_OpenMne.SetBitmaps(IDB_OPEN, RGB(255, 0, 255));
	m_Btn_SaveMne.SetBitmaps(IDB_SAVE, RGB(255, 0, 255));
	m_Btn_OpenDes.SetBitmaps(IDB_OPEN, RGB(255, 0, 255));
	m_Btn_SaveDes.SetBitmaps(IDB_SAVE, RGB(255, 0, 255));
	m_Btn_Search.SetBitmaps(IDB_SEARCH, RGB(255, 0, 255));
	m_Btn_NewDes.SetBitmaps(IDB_DOCUMENT, RGB(255, 0, 255));

	// Spin Control ���� ��� ����
	// CECMDlg::OnInitDialog ���� �ϴ°ɷ� ����
#if 0
	m_bInverseRW = ReadIni(SEC_REG, KEY_INVERSERW, DEF_INVERSERW);
	SetSpinRange();
	pParameterDlg->SetSpinRange();
#endif

// ----------------------------------------------------------------------------------------------------
// TreeList
	CRect	sRect;
	CPoint	sPoint(0, 0);

	GetDlgItem(IDC_LISTFRAME)->GetWindowRect(sRect);
	ClientToScreen(&sPoint);

	sRect.left -= sPoint.x;
	sRect.right -= sPoint.x;
	sRect.top -= sPoint.y;
	sRect.bottom -= sPoint.y;

	DWORD	dwStyle = TVS_LINESATROOT |
		TVS_FULLROWSELECT |
		TVS_EDITLABELS;

	DWORD	dwExStyle = TVS_EX_FULLROWMARK |
		TVS_EX_ITEMLINES |
		TVS_EX_SUBSELECT |
		TVS_EX_AUTOHSCROLL |
		TVS_EX_GRAYEDDISABLE |
		TVS_EX_NOCOLUMNRESIZE |
		TVS_EX_NOCHARSELCET |
		TVS_EX_EDITCLICK;

	m_List_Reg.Create(dwStyle | WS_CHILD | WS_VISIBLE | WS_BORDER, sRect, this, IDC_REGTREELIST);
	m_List_Reg.SetExtendedStyle(dwExStyle);

	// Set Column
	m_List_Reg.InsertColumn(TC_ADDR, _T("Addr"), LVCFMT_CENTER, 50);
	m_List_Reg.InsertColumn(TC_NAME, _T("Name"), 0);
	m_List_Reg.InsertColumn(TC_RX, _T("Rx"), 0, 65);
	m_List_Reg.InsertColumn(TC_TX, _T("Tx"), 0, 65);

	m_List_Reg.SetColumnAutoEdit(TC_TX, TVAE_EDIT | TVAE_DBLCLICK);

	// Init TreeList
	InitTreeCtrl(0);

// ----------------------------------------------------------------------------------------------------
// Load Has, Mne and Des, Option
	// Has
	m_Edit_HasFile.SetWindowTextW(ReadIni(SEC_REG, KEY_HASFILE, _T("")));

	// Mne
	m_Edit_MneFile.SetWindowTextW(ReadIni(SEC_REG, KEY_MNEFILE, _T("")));

	// Des
	m_Edit_DesFile.SetWindowTextW(_T(""));

	// Feedback
	//m_Chk_FeedBackRead.SetCheck(ReadIni(SEC_REG, KEY_FDBACKREAD, DEF_FDBACKREAD));
	//m_Chk_FeedBackWrite.SetCheck(ReadIni(SEC_REG, KEY_FDBACKWRITE, DEF_FDBACKWRITE));
	m_Chk_FeedBackRead.SetCheck(TRUE);
	m_Chk_FeedBackWrite.SetCheck(FALSE);

	// Open Has, Mne
	CString strHasFile = _T("");
	CString strMasFile = _T("");
	m_Edit_HasFile.GetWindowTextW(strHasFile);
	m_Edit_MneFile.GetWindowTextW(strMasFile);
	if (strHasFile != _T("") && strHasFile != _T(""))
	{
		if (OpenHas(strHasFile) && OpenMne(strMasFile))
			StartDispRegInfoThread();
		else
		{
			m_Edit_HasFile.SetWindowTextW(_T(""));
			m_Edit_MneFile.SetWindowTextW(_T(""));
		}
	}
	else
	{
		if (strMasFile != _T(""))
		{
			OpenMne(strMasFile);
			StartDispRegInfoThread();
		}
	}

// ----------------------------------------------------------------------------------------------------
// etc
	m_Cbo_ReadStart.InsertString(0, _T("0"));
	m_Cbo_ReadStart.SetCurSel(0);
	m_Cbo_ReadEnd.InsertString(0, _T("0"));
	m_Cbo_ReadEnd.SetCurSel(0);
	m_Cbo_WriteStart.InsertString(0, _T("0"));
	m_Cbo_WriteStart.SetCurSel(0);
	m_Cbo_WriteEnd.InsertString(0, _T("0"));
	m_Cbo_WriteEnd.SetCurSel(0);

	// Thread Flag
	g_pLoadingThread = NULL;
	g_pDispRegInfoThread = NULL;
	g_pRegReadAllThread = NULL;
	g_pRegWriteAllThread = NULL;

	bRunLoadingThread = FALSE;
	bRunDispRegInfoThread = FALSE;
	bRunReadAllThread = FALSE;
	bRunWriteAllThread = FALSE;
	g_iRxAddress = -1;

//	EN673_JTAG_SET_ISP_BASE(m_dwEN673BaseAdr);
	m_dwEN673BaseAdr = 0xf1100000;

	RxCheck_flag = TRUE;
	
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CRegCtrlDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialogEx::OnSysCommand(nID, lParam);
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CRegCtrlDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

void CRegCtrlDlg::OnCancel()
{
	m_List_Reg.DeleteAllItems();

	int i = 0;

	if (m_hItem != nullptr)
	{
		delete[] m_hItem;
		m_hItem = NULL;
	}

	if (m_Des != nullptr)
	{
		for (i = 0; i < m_iAddr; i++)
			delete m_Des[i];
		delete[] m_Des;

		m_Des = NULL;
	}

#if 1
	if (m_Mne != NULL)
	{
		delete[] m_Mne;
		m_Mne = NULL;
	}

	if (m_Has != NULL)
	{
		delete[] m_Has;
		m_Has = NULL;
	}
#endif

	SaveValue();

	NetClo(ConnectSocket);
	ConnectSocket = NULL;

	NetClo(StateSocket);
	StateSocket = NULL;

	//ExitProcess(0);

	CDialogEx::OnCancel();
}


// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CRegCtrlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CRegCtrlDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetCapture();
	m_Point = point;

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CRegCtrlDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (this == GetCapture())
	{
		CRect rcDialog;
		GetWindowRect(&rcDialog);

		int x = rcDialog.left + point.x - m_Point.x;
		int y = rcDialog.top + point.y - m_Point.y;

		SetWindowPos(NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		WriteIni(SEC_WININFO, KEY_REGDLGLEFT, x);
		WriteIni(SEC_WININFO, KEY_REGDLGTOP, y);
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void CRegCtrlDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	ReleaseCapture();
	CDialogEx::OnLButtonUp(nFlags, point);
}


void CRegCtrlDlg::OnBnClickedButtonRegclose()
{
	//CRegCtrlDlg::OnClose();
	CRegCtrlDlg::OnCancel();
}


void CRegCtrlDlg::OnBnClickedButtonMinimize()
{
	ShowWindow(SW_MINIMIZE);
}


// ====================================================================================================
// CRegCtrlDlg :: PreTranslateMessage
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
BOOL CRegCtrlDlg::PreTranslateMessage(MSG* pMsg)
{
	int i = 0;
	int iStart = 0;
	int iEnd = 0;
	DWORD dwSel = 0;
	CString str = 0;
	CEdit* edit = NULL;
	HTREEITEM hItem = NULL;
	CWnd* wndFocus = GetFocus();

	if (pMsg->message == WM_KEYDOWN) {
		if ((GetKeyState(VK_LCONTROL) & 0x8000) ||
			(GetKeyState(VK_RCONTROL) & 0x8000))
		{
			switch (pMsg->wParam)
			{
			case VK_A: // KEYDOWN - Ctrl + A
				if (wndFocus == NULL) return FALSE;
				if (wndFocus == (CWnd*)&m_Edit_Description)
				{
					m_Edit_Description.SetSel(0, m_Edit_Description.GetWindowTextLengthW());
					return TRUE;
				}
				break;

			case VK_C: // KEYDOWN - Ctrl + C
				if (wndFocus == NULL) return FALSE;
				if (wndFocus == m_List_Reg.GetEditControl()) // TX Editâ
				{
					edit = m_List_Reg.GetEditControl();
					edit->GetWindowTextW(str);
					copyClipboard(str);
					return TRUE;
				}
				else if (wndFocus == (CWnd*)&m_List_Reg) // �������� ������
				{
					if (m_hSelItem == NULL) return FALSE;
					copyClipboard(m_List_Reg.GetItemText(m_hSelItem, m_iSelCol));
					return TRUE;
				}
				break;

			case VK_Z: // KEYDOWN - Ctrl + Z
				if (THREAD_ON) return 0L;
				OnCtrlZ();
				break;

			case VK_UP: // KEYDOWN - Ctrl + UP
				if (THREAD_ON) return 0L;
				if ((ConnectSocket != NULL) && (m_hSelItem != NULL))
				{
					NMUPDOWN nmUpDn;
					nmUpDn.iDelta = -1;
					nmUpDn.iPos = m_Spin_Value.GetPos();
					nmUpDn.hdr.code = UDN_DELTAPOS;
					nmUpDn.hdr.hwndFrom = m_Spin_Value.m_hWnd;
					nmUpDn.hdr.idFrom = ::GetDlgCtrlID(m_Spin_Value.m_hWnd);

					m_bPressedCtrl = TRUE;
					::SendMessage(::GetParent(m_Spin_Value.m_hWnd), WM_NOTIFY, WPARAM(nmUpDn.hdr.idFrom), LPARAM(&nmUpDn));
					return TRUE;
				}
				break;

			case VK_DOWN: // KEYDOWN - Ctrl + DOWN
				if (THREAD_ON) return 0L;

				if ((ConnectSocket != NULL) && (m_hSelItem != NULL))
				{
					NMUPDOWN nmUpDn;
					nmUpDn.iDelta = 1;
					nmUpDn.iPos = m_Spin_Value.GetPos();
					nmUpDn.hdr.code = UDN_DELTAPOS;
					nmUpDn.hdr.hwndFrom = m_Spin_Value.m_hWnd;
					nmUpDn.hdr.idFrom = ::GetDlgCtrlID(m_Spin_Value.m_hWnd);

					m_bPressedCtrl = TRUE;
					::SendMessage(::GetParent(m_Spin_Value.m_hWnd), WM_NOTIFY, WPARAM(nmUpDn.hdr.idFrom), LPARAM(&nmUpDn));
					return TRUE;
				}
				break;
			}
		}
		switch (pMsg->wParam)
		{
		case VK_SPACE: // KEYDOWN - Space Bar
			if (wndFocus == NULL) return FALSE;
			if (wndFocus->m_hWnd == m_List_Reg.m_hWnd)
			{
				if (m_List_Reg.GetParentItem(m_hSelItem) == NULL)
				{
					m_List_Reg.EnsureVisible(m_hSelItem);

					i = m_List_Reg.GetItemState(m_hSelItem, TVIS_EXPANDED);
					if (i == 0)	i |= TVIS_EXPANDED;
					else		i = 0;
					m_List_Reg.SetItemState(m_hSelItem, i, TVIS_EXPANDED);
					return TRUE;
				}
			}
			break;

		case VK_RETURN: // KEYDOWN - Enter
			if (wndFocus == NULL) return FALSE;
			// Search Reg
			if ((wndFocus == m_Cbo_Search.GetNextDlgTabItem(GetDlgItem(IDC_COMBO_SEARCH))) ||
				(wndFocus == m_Cbo_SearchOption.GetNextDlgTabItem(GetDlgItem(IDC_COMBO_SEARCHOPTION))) ||
				(wndFocus->m_hWnd == m_Btn_Search.m_hWnd))
			{
				if (THREAD_ON) return 0L;
				SearchReg();
				return TRUE;
			}
			// Edit Control
			else if (wndFocus == m_List_Reg.GetEditControl())
			{
				if (THREAD_ON) return 0L;
				m_bEnter = TRUE;
				return CDialog::PreTranslateMessage(pMsg);
			}
			// TreeList Control
			else if (wndFocus->m_hWnd == m_List_Reg.m_hWnd)
			{
				m_List_Reg.EnsureVisible(m_hSelItem);

				i = m_List_Reg.GetSelectionColumn();

				switch (i)
				{
				case TC_ADDR:
				case TC_NAME:
				case TC_RX:
					if (m_List_Reg.GetParentItem(m_hSelItem) == NULL)
					{
						i = m_List_Reg.GetItemState(m_hSelItem, TVIS_EXPANDED);
						if (i == 0)	i |= TVIS_EXPANDED;
						else		i = 0;
						m_List_Reg.SetItemState(m_hSelItem, i, TVIS_EXPANDED);
					}
					break;
				case TC_TX:
					if (THREAD_ON) return 0L;

					if (m_iHasNum)
					{
						m_List_Reg.EditLabel(m_hSelItem, TC_TX);
						PostMessage(VK_RETURN);
					//	OnBnClickedButtonRegwrite();
					}
					break;
				}
				return TRUE;
			}
			break;
			// KEYDOWN - UP
		case VK_UP:
			if (wndFocus == NULL) return FALSE;
			if (wndFocus == m_List_Reg.GetEditControl()){
				m_List_Reg.EndEditLabelNow(TRUE);
				OnRegEndLabelEdit(NULL, NULL);
				hItem = m_List_Reg.GetPrevVisibleItem(m_hSelItem);
				if (hItem != NULL)
					m_List_Reg.SelectItem(hItem, m_iSelCol);
				return TRUE;
			}
			break;
			// KEYDOWN - DOWN
		case VK_DOWN:
			if (wndFocus == NULL) return FALSE;
			if (wndFocus == m_List_Reg.GetEditControl()){
				m_List_Reg.EndEditLabelNow(TRUE);
				OnRegEndLabelEdit(NULL, NULL);
				hItem = m_List_Reg.GetNextVisibleItem(m_hSelItem);
				if (hItem != NULL)
					m_List_Reg.SelectItem(hItem, m_iSelCol);
				return TRUE;
			}
			break;
			// KEYDOWN - ESC
		case VK_ESCAPE:
			if (wndFocus == NULL) return FALSE;
			if (wndFocus == m_List_Reg.GetEditControl())
			{
				m_bESC = TRUE;
				m_List_Reg.EndEditLabelNow(TRUE);
			}
			return TRUE;
			// KEYDOWN - Page Up
		case VK_PRIOR:
			if (wndFocus == NULL) return FALSE;
			if (wndFocus == m_List_Reg.GetEditControl())
			{
				m_bESC = TRUE;
				m_List_Reg.EndEditLabelNow(TRUE);
				return CDialog::PreTranslateMessage(pMsg);
			}
			break;
			// KEYDOWN - Page Down
		case VK_NEXT:
			if (wndFocus == NULL) return FALSE;
			if (wndFocus == m_List_Reg.GetEditControl())
			{
				m_bESC = TRUE;
				m_List_Reg.EndEditLabelNow(TRUE);
				return CDialog::PreTranslateMessage(pMsg);
			}
			break;
		}
	}
	// MOUSE WHEEL
	else if (pMsg->message == WM_MOUSEWHEEL)
	{
		if (wndFocus == NULL) return FALSE;
		if (wndFocus->m_hWnd == m_List_Reg.m_hWnd)
		{
			return CDialog::PreTranslateMessage(pMsg);
		}
		else if (wndFocus->m_hWnd == m_Spin_Read.m_hWnd ||
			wndFocus->m_hWnd == m_Spin_Write.m_hWnd ||
			wndFocus->m_hWnd == m_Spin_Value.m_hWnd ||
			wndFocus->m_hWnd == m_Btn_RegRead.m_hWnd ||
			wndFocus->m_hWnd == m_Btn_RegWrite.m_hWnd ||
			wndFocus->m_hWnd == m_Static_Txvalue.m_hWnd)
		{
			m_List_Reg.SetFocus();
			return TRUE;
		}
		else if (wndFocus == m_List_Reg.GetEditControl())
		{
			m_List_Reg.EndEditLabelNow(FALSE);
			return TRUE;
		}
		else
		{
			return TRUE;
		}
	}

	// Default Window Message
	if (DefaultWindowMessage(pMsg))	return TRUE;
	else							return CDialog::PreTranslateMessage(pMsg);
}

int CRegCtrlDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetWindowLongPtr(m_hWnd, GWL_STYLE, WS_SYSMENU | WS_MINIMIZEBOX);

	RedrawWindow();

	return 0;
}

// ====================================================================================================
// CRegCtrlDlg :: InitTreeCtrl
// ----------------------------------------------------------------------------------------------------
/*
(HTREEITEM) m_hItem �Ҵ�, Ʈ�� �ʱ�ȭ
*/
// ====================================================================================================
void CRegCtrlDlg::InitTreeCtrl(int iNum)
{
	int i = 0;
	CString	str = 0;

	m_bInitTree = TRUE;

	m_List_Reg.DeleteAllItems();

	// ----------------------------------------------------------------------------------------------------
	// 1. HTREEITEM �Ҵ� ����
	if (m_hItem != NULL)
	{
		delete[] m_hItem;
		m_hItem = NULL;
	}

	// ----------------------------------------------------------------------------------------------------
	// 2. �Ҵ�
	if (iNum > 0)
		m_hItem = new HTREEITEM[iNum];
	else
		return;

	// ----------------------------------------------------------------------------------------------------
	// 3. Tree List �ʱ�ȭ
	if (m_hItem == NULL) return;

	// Mne ������ �ִ� �� ���� ǥ��
	for (i = 0; i < iNum; i++)
	{
		// MNE X
		if (m_Mne != NULL)
		{
			if (m_Mne[i].strLine == _T("")) continue;
		}

		// HAS O / MNE X
		if ((m_Has != NULL) && (m_Mne == NULL)) // HAS : VALUE X
		{
			if (m_Has[i].bOn == FALSE) continue;
		}

		str.Format(_T("%x"), i);
		m_hItem[i] = m_List_Reg.InsertItem(str);

		m_List_Reg.SetItemBkColor(m_hItem[i], 0, ROOTCOLOR);
		m_List_Reg.SetItemBkColor(m_hItem[i], 1, ROOTCOLOR);
		m_List_Reg.SetItemBkColor(m_hItem[i], 2, ROOTCOLOR);
		m_List_Reg.SetItemBkColor(m_hItem[i], 3, ROOTCOLOR);

		//Sleep(0);
		Wait(0);
	}
}


void CRegCtrlDlg::OnBnClickedButtonOpenhas()
{
	int iMsgBoxReturn = 0;
	CString strHasFile = _T("");
	CString strDefExt = _T("has");
	CString strFilter = _T("Register File(*.has)|*.has||");

	m_Edit_HasFile.GetWindowTextW(strHasFile);
	/*
// ----------------------------------------------------------------------------------------------------
	// Save Has File
	if (m_bUpdateHas)
	{
		iMsgBoxReturn = AfxMessageBox(_T("Register File is modified. Do you want to save?"), MB_YESNOCANCEL);
		if (iMsgBoxReturn == IDCANCEL)
		{
			return;
		}
		else if (iMsgBoxReturn == IDYES)
		{
			if (ShowSaveFileDlg(&strHasFile, strDefExt, strFilter, this))
				SaveHas(strHasFile);
		}
	}
	*/
	// Open Dialog
	if (!ShowOpenFileDlg(&strHasFile, strDefExt, strFilter, this))
		return;

	// Open
	//if(!OpenHas(strHasFile))
	//	AfxMessageBox(_T("Fail file open."));
	OpenHas(strHasFile);

// ----------------------------------------------------------------------------------------------------
// 3. Display Register Infomation
	if (m_Mne != NULL)
		StartDispRegInfoThread();
}


// ====================================================================================================
// CRegCtrlDlg :: OpenHas
// ----------------------------------------------------------------------------------------------------
/*
- m_HasFile : HasFile Path.
FALSE = _T("")

- m_Has : HasFile Data.
�Լ� ���۰� ���ÿ� ������Ű�� m_iHasNum ũ�⸸ŭ ���Ҵ�

- m_iHasNum : Has ������ Address / Has ����. ������ �о ���� ū Address�� ����.
FALSE = 0

- m_iAddr : m_iMneNum�� ����

- m_bOpenHas : TRUE -> ���� ���� ������ ��.
FALSE -> OpenHas ��������. �ʱ�ȭ ���ص� ��.

- _bUpdateHas : HasFile�� ������Ʈ��. ������ �� ��. (FALSE)

*/
// ====================================================================================================
BOOL CRegCtrlDlg::OpenHas(CString strPath)
{
	int i = 0;
	int iNum = 0;
	int iLine = 0;
	BOOL bReturn = FALSE;
	CString str = _T("");
	CString strValue = _T("");
	CString strNum = _T("");
	CString strMsg = _T("");
	CStdioFile hasFile;

	// ----------------------------------------------------------------------------------------------------
	// 1. ������� �ʱ�ȭ
	// On OpenHas
	m_bOpenHas = TRUE;
	m_iHasNum = 0;

	if (m_Has != NULL)
	{
		delete[] m_Has;
		m_Has = NULL;
	}

	// ----------------------------------------------------------------------------------------------------
	// 2. ���� Ȯ��
	// 1) Open File
	if (!hasFile.Open(strPath, CFile::modeRead))
		goto ENDOPENHAS;

	// 2) m_iHasNum
	while (hasFile.ReadString(str))
	{
		str = str.TrimLeft();
		i = str.FindOneOf(_T("\t "));

		if (i != -1) strNum = str.Left(i);
		else		strNum = str;

		if (strNum == _T("")) continue;

		if (!CheckHex(strNum))
		{
			hasFile.Close();
			goto ENDOPENHAS;
		}

		iNum = HexToDec(strNum);
		if (iNum + 1 > m_iHasNum) m_iHasNum = iNum + 1;
	}

	if (m_iHasNum <= 0)
	{
		hasFile.Close();
		strMsg.Format(_T("Fail file open."), iLine);
		AfxMessageBox(strMsg);
		goto ENDOPENHAS;
	}

	// ----------------------------------------------------------------------------------------------------
	// 3. m_Has ����
	// 1) �Ҵ�, �ʱ�ȭ 
	// m_iAddr
	if (!m_iMneNum)	m_iAddr = m_iHasNum;
	else			m_iAddr = m_iMneNum;

	// m_Has �Ҵ�
	// (m_iAddr > m_iHasNum ? m_iAddr : m_iHasNum) �� OpenHas�� SaveHas������ ���
	m_Has = new HAS[(m_iAddr > m_iHasNum ? m_iAddr : m_iHasNum)];

	// m_Has �ʱ�ȭ
	for (i = 0; i < (m_iAddr > m_iHasNum ? m_iAddr : m_iHasNum); i++)
	{
		m_Has[i].bOn = FALSE;
		m_Has[i].dwTxValue = 0;
	}

	// 2) m_Has�� ������ ����
	hasFile.SeekToBegin();

	while (hasFile.ReadString(str))
	{
		iLine++;

		str = str.Trim();
		if (str == _T("")) continue;

		// Num
		i = str.FindOneOf(_T("\t ")); // ������
		if (i == -1)
		{
			hasFile.Close();
			strMsg.Format(_T("Fail file open. (Line : %d)"), iLine);
			AfxMessageBox(strMsg);
			goto ENDOPENHAS;
		}

		strNum = str.Left(i);
		if (!CheckHex(strNum))
		{
			hasFile.Close();
			strMsg.Format(_T("Fail file open. (Line : %d)"));
			AfxMessageBox(strMsg);
			goto ENDOPENHAS;
		}
		iNum = HexToDec(strNum);
		str = str.Right(str.GetLength() - i - 1);

		// Value
		str = str.TrimLeft();
		i = str.FindOneOf(_T("\t "));
		if (i == -1)
		{
			strValue = str;
		}
		else
		{
			strValue = str.Left(i);
			str = str.Right(str.GetLength() - i - 1);
			str.Trim();

			if (str.GetLength() > 0)
			{
				hasFile.Close();
				strMsg.Format(_T("Fail file open. (Address : %x)"), iNum);
				AfxMessageBox(strMsg);
				goto ENDOPENHAS;
			}
		}

		// 0x ����
		i = strValue.Find(_T("0x"));
		if (i == 0)
		{
			strValue = strValue.Right(str.GetLength() - 2);
		}

		// Tx �˻�
		if (!CheckHex(strValue))
		{
			hasFile.Close();
			strMsg.Format(_T("Fail File open. (Address : %x)"));
			goto ENDOPENHAS;
		}

		m_Has[iNum].dwTxValue = HexToDec(strValue);
		m_Has[iNum].bOn = TRUE;
	}
	hasFile.Close();

	m_Edit_HasFile.SetWindowTextW(strPath);
	bReturn = TRUE;

	// ----------------------------------------------------------------------------------------------------
	// 4. Open Has ��
ENDOPENHAS:
	// Open Has ���нÿ� ó��
	if (!bReturn)
	{
		// �Ҵ� ����, �ʱ�ȭ
		m_Edit_HasFile.SetWindowTextW(_T(""));

		m_iHasNum = 0;
		m_iAddr = m_iMneNum;

		if (!m_iAddr){
			m_hSelItem = NULL;
			m_hOldItem = NULL;
			m_iSelAddr = 0;
			m_iSelCol = 0;
			m_strSelTx = _T("");
			m_strBeforeTx = _T("");
		}

		if (m_Has != NULL){
			delete[] m_Has;
			m_Has = NULL;
		}
	}

	m_bUpdateHas = FALSE;

	if (!bRunDispRegInfoThread)
		EnableCtrl(TRUE);

	return bReturn;
}



void CRegCtrlDlg::OnBnClickedButtonOpenmne()
{
	int iMsgBoxReturn = 0;
	CString strMneFile = _T("");
	CString strDesFile = _T("");
	CString strDefExtMne = _T("mne");
	CString strFilterMne = _T("Mnemonic File(*.mne)|*.mne||");
	CString strDefExtDes = _T("des");
	CString strFilterDes = _T("Description File(*.des)|*.des||");

	m_Edit_MneFile.GetWindowTextW(strMneFile);
	m_Edit_DesFile.GetWindowTextW(strDesFile);

	// ----------------------------------------------------------------------------------------------------
	// Save Des
	if (m_bUpdateDes)
	{
		iMsgBoxReturn = AfxMessageBox(_T("Do you want to save modified Description file?"), MB_YESNOCANCEL);
		if (iMsgBoxReturn == IDCANCEL)
		{
			return;
		}
		else if (iMsgBoxReturn == IDYES)
		{
			if (ShowSaveFileDlg(&strDesFile, strDefExtDes, strFilterDes, this))
				SaveDes(strDesFile);
		}
	}

	m_Edit_DesFile.SetWindowTextW(_T(""));

	// ----------------------------------------------------------------------------------------------------
	// Open Dialog
	if (!ShowOpenFileDlg(&strMneFile, strDefExtMne, strFilterMne, this))
		return;

	// Open
	if (!OpenMne(strMneFile))
		AfxMessageBox(_T("Fail file open"));

	OpenDes(strDesFile);

	// ----------------------------------------------------------------------------------------------------
	// Display Register Info.
	if (m_Has != NULL)
		StartDispRegInfoThread();
}


// ====================================================================================================
// CRegCtrlDlg :: OpenMne
// ----------------------------------------------------------------------------------------------------
/*
- m_MneFile : MneFile Path
FALSE = _T("")

- m_Mne : MneFile Data
�Լ� ���۰� ���ÿ� ������Ű�� m_iMneNum ũ�⸸ŭ ���Ҵ�

- m_iMneNum : Mne ������ Address / Mne ����. ������ �о ���� ū Address�� ����
FALSE = 0

- m_iAddr : m_iHasNum�� m_iMneNum �� 0�� �ƴ� ���� ������ ����.

- m_bOpenMne : TRUE -> ������ ���� ������ ����.
FALSE -> OpenMne �������� �ʱ�ȭ ���ص� ��.

- m_bUpdateMne : MneFile�� ������Ʈ��. ������ �� ��. (FALSE)
*/
// ====================================================================================================
BOOL CRegCtrlDlg::OpenMne(CString strPath)
{
	int i = 0;
	int j = 0;
	int iNum = 0;
	int iNameCnt = 0;
	BOOL bReturn = FALSE;
	CString str = _T("");
	CString strNum = _T("");
	CString strLine = _T("");
	CString strName = _T("");
	CStdioFile mneFile;

	// ----------------------------------------------------------------------------------------------------
	// 1. ������� ����, �ʱ�ȭ
	m_iMneNum = 0;
	m_bOpenMne = TRUE;

	if (m_Mne != NULL)
	{
		delete[] m_Mne;
		m_Mne = NULL;
	}

	// ----------------------------------------------------------------------------------------------------
	// 2. ���� Ȯ��
	// 1) Open File
	if (!mneFile.Open(strPath, CFile::modeRead))
	{
		bReturn = FALSE;
		goto ENDMNE;
	}

	// 2) m_iMneNum
	while (mneFile.ReadString(str))
	{
		str = str.TrimLeft();
		i = str.FindOneOf(_T("\t "));

		if (i != -1)	strNum = str.Left(i);
		else		strNum = str;

		if ((strNum == _T(""))) continue;
		if (!CheckHex(strNum)){
			bReturn = FALSE;
			goto ENDMNE;
		}

		iNum = HexToDec(strNum);
		if (iNum + 1 > m_iMneNum) m_iMneNum = iNum + 1;
	}

	if (m_iMneNum < 0)
	{
		bReturn = FALSE;
		mneFile.Close();
		goto ENDMNE;
	}

	// ----------------------------------------------------------------------------------------------------
	// 3. m_Mne ����
	m_iAddr = m_iMneNum;

	// 1) �Ҵ�, �ʱ�ȭ
	m_Mne = new MNE[m_iMneNum];
	for (i = 0; i < m_iMneNum; i++)
	{
		m_Mne[i].bOn = FALSE;
		m_Mne[i].strLine = _T("");
		for (j = 0; j < 32; j++)
		{
			m_Mne[i].iStart[j] = 0;
			m_Mne[i].iEnd[j] = 0;
			m_Mne[i].iBitNum = 0;
		}
	}

	// 2) m_Mne�� ������ ����
	mneFile.SeekToBegin();

	while (mneFile.ReadString(str))
	{
		// strNum
		str = str.Trim();
		if (str == _T("")) continue;

		i = str.FindOneOf(_T("\t "));
		if (i != -1)
		{
			strNum = str.Left(i);
			if (!CheckHex(strNum))
			{
				bReturn = FALSE;
				mneFile.Close();
				goto ENDMNE;
			}

			iNum = HexToDec(strNum);

			strLine = str.Right(str.GetLength() - i - 1);
			strLine = strLine.Trim();
		}
		else
		{
			strNum = str;
			if ((strNum == _T(""))) continue;
			if (!CheckHex(strNum))
			{
				bReturn = FALSE;
				mneFile.Close();
				goto ENDMNE;
			}

			iNum = HexToDec(strNum);

			strLine = _T("");
		}

		m_Mne[iNum].strLine = strLine;
		m_Mne[iNum].bOn = TRUE;
	}

	mneFile.Close();

	m_Edit_MneFile.SetWindowTextW(strPath);

	// ----------------------------------------------------------------------------------------------------
	// 4. Has ���� �� Has �Ҵ�
	if (m_Has == NULL)
	{
		m_iHasNum = m_iMneNum;
		m_Has = new HAS[m_iHasNum];

		for (i = 0; i < m_iHasNum; i++)
			m_Has[i].dwTxValue = 0;
	}

	// ----------------------------------------------------------------------------------------------------
	// 5. Open Mne ��
	bReturn = TRUE;
ENDMNE:
	// Open Mne ���нÿ� ó��
	if (!bReturn)
	{
		// �Ҵ� ����, �ʱ�ȭ
		m_Edit_MneFile.SetWindowTextW(_T(""));

		m_iMneNum = 0;
		m_iAddr = m_iHasNum;

		if (!m_iAddr){
			m_hSelItem = NULL;
			m_hOldItem = NULL;
			m_iSelAddr = 0;
			m_iSelCol = 0;
			m_strSelTx = _T("");
			m_strBeforeTx = _T("");
		}

		if (m_Mne != NULL)
		{
			delete[] m_Mne;
			m_Mne = NULL;
		}
	}

	m_bUpdateMne = FALSE;
	m_Btn_SaveMne.EnableWindow(FALSE);

	EnableCtrl(TRUE);

	return bReturn;
}


void CRegCtrlDlg::OnBnClickedButtonSavehas()
{
	CString strHasFile = _T("");
	CString strDefExt = _T("has");
	CString strFilter = _T("Register File(*.has)|*.has||");

	m_Edit_HasFile.GetWindowTextW(strHasFile);

	// Save Dialog
	if (!ShowSaveFileDlg(&strHasFile, strDefExt, strFilter, this))
		return;

	// Save
	if (!SaveHas(strHasFile))
	{
		CFileFind ffind;
		if (ffind.FindFile(strHasFile))
		{
			ffind.Close();
			DeleteFileW(strHasFile);
		}
		AfxMessageBox(_T("Fail save file."));
	}
	else
	{
		m_Edit_HasFile.SetWindowTextW(strHasFile);
	}

	m_bUpdateHas = FALSE;
}


// ====================================================================================================
// CRegDlg :: SaveHas
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
BOOL CRegCtrlDlg::SaveHas(CString strPath)
{
	int i = 0;
	CString	str = _T("");

	if (!m_iHasNum) return FALSE;

	CStdioFile hasFile;
	hasFile.Open(strPath, CFile::modeCreate | CFile::modeWrite);

	int iAddr = 0;
	HTREEITEM hItem = m_List_Reg.GetFirstItem();
	while (TRUE)
	{
		if (hItem == NULL) break; // Check HTREEITEM

		iAddr = HexToDec(m_List_Reg.GetItemText(hItem, TC_ADDR));
		str.Format(_T("%x\t%x\n"), iAddr, m_Has[iAddr].dwTxValue);

		hasFile.WriteString(str); // Write String

		hItem = m_List_Reg.GetNextItem(hItem);// Select Next Item
	}

	/*
	for(i = 0; i < (m_iAddr > m_iHasNum ? m_iAddr : m_iHasNum); i++)
	{
	str.Format(_T("%x\t%x\n"), i, m_Has[i].dwTxValue);

	hasFile.WriteString(str);
	}
	*/

	hasFile.Close();

	return TRUE;
}


void CRegCtrlDlg::OnBnClickedButtonSavemne()
{
	// ����X
}


// ====================================================================================================
// CRegCtrlDlg :: DispRegInfo
// ----------------------------------------------------------------------------------------------------
/*
m_iHasNum, m_iMneNum, m_Has, m_Mne ������ ��� ������ �ʱ�ȭ

StartDispRegInfoThread() �� ���� -> DispRegInfoThread���� ����
StartDispRegInfoThread �Լ����� �ε� �̹����� �Բ� ����

m_hItem ���� (InitTreeCtrl �Լ�)
*/
// ====================================================================================================
BOOL CRegCtrlDlg::DispRegInfo()
{
	int i = 0;
	int j = 0;
	int iStart = 0;
	int iEnd = 0;
	int iNameCnt = 0;
	CString str = _T("");
	CString strLine = _T("");
	CString strValue = _T("");
	CString strName[32];

	for (i = 0; i < 32; i++)
		strName[i] = _T("");

	// ----------------------------------------------------------------------------------------------------
	// 1. ������ ���� �� �ʱ�ȭ.
	if ((m_iHasNum == 0) && (m_iMneNum == 0))
	{
		for (i = m_Cbo_ReadStart.GetCount() - 1; i >= 0; i--)
			m_Cbo_ReadStart.DeleteString(i);
		for (i = m_Cbo_ReadEnd.GetCount() - 1; i >= 0; i--)
			m_Cbo_ReadEnd.DeleteString(i);
		for (i = m_Cbo_WriteStart.GetCount() - 1; i >= 0; i--)
			m_Cbo_WriteStart.DeleteString(i);
		for (i = m_Cbo_WriteEnd.GetCount() - 1; i >= 0; i--)
			m_Cbo_WriteEnd.DeleteString(i);

		m_Cbo_ReadStart.InsertString(0, _T(""));
		m_Cbo_ReadEnd.InsertString(0, _T(""));
		m_Cbo_WriteStart.InsertString(0, _T(""));
		m_Cbo_WriteEnd.InsertString(0, _T(""));

		m_Cbo_ReadStart.SetCurSel(0);
		m_Cbo_ReadEnd.SetCurSel(0);
		m_Cbo_WriteStart.SetCurSel(0);
		m_Cbo_WriteEnd.SetCurSel(0);

		m_iSelAddr = 0;
		goto ENDDISPLAY;
	}

	m_List_Reg.SetRedraw(FALSE);

	// ----------------------------------------------------------------------------------------------------
	// 2. Tree List �ʱ�ȭ (m_hItem)
	// 1) m_iHasNum Ȯ��
	if (m_bOpenMne && (!m_bOpenHas)) // Mne ���� ������ ��
	{
		if (m_iMneNum > m_iHasNum) // Mne�� ���� Has���� ������ ũ��
		{
			m_Edit_HasFile.GetWindowText(str);
			pRegDlg->OpenHas(str);
		}
	}

	// 2) TreeList �ʱ�ȭ
	if ((m_hItem == NULL) || (m_bOpenHas) || (m_bOpenMne))
	{
		InitTreeCtrl(m_iAddr);
	}

	BOOL bHasFlag = (m_iHasNum != 0) ? TRUE : FALSE;
	BOOL bMneFlag = (m_iMneNum != 0) ? TRUE : FALSE;

	// 3) m_List_Reg�� �θ� ������ �߰�
	for (i = 0; i < m_iAddr; i++)
	{
		//ProcessWindowMessage();
		str.Format(_T("%x"), i);

		// MNE : NAME X
		if (m_Mne != NULL)								{ if (m_Mne[i].strLine == _T("")) continue; }
		// HAS : VALUE X
		if (bHasFlag && (m_iAddr > i) && (!bMneFlag))	{ if (m_Has[i].bOn == 0) continue; }
		//if(m_Has != NULL)								{ if(m_Has[i].bOn == FALSE) continue; }

		m_List_Reg.SetItem(m_hItem[i], TC_ADDR, TVIF_TEXT, str);
	}

	// ----------------------------------------------------------------------------------------------------
	// 3. Disp Reg Info ���η���
	int iLb = 0; // Left Bracket	[
	int iRb = 0; // Right Bracket	]
	int	iCc = 0; // Center Colon	:
	HTREEITEM hChildItem = NULL;

	for (i = 0; i < m_iAddr; i++)
	{
		// 1) Skip
		// MNE : NAME X
		if (bMneFlag && (m_iMneNum > i))              { if (m_Mne[i].strLine == _T("")) continue; }
		// HAS : VALUE X
		if (bHasFlag && (m_iAddr > i) && (!bMneFlag)) { if (m_Has[i].bOn == FALSE) continue; }

		// 2) Ʈ�� : Address, Rx, Tx
		// Ʈ�� ���� �߰� : Address
		str.Format(_T("%x"), i);
		m_List_Reg.SetItem(m_hItem[i], TC_ADDR, TVIF_TEXT, str);

		// Ʈ�� ���� �߰� : Rx
		m_List_Reg.SetItem(m_hItem[i], TC_RX, TVIF_TEXT, _T("0"));

		// Ʈ�� ���� �߰� : TX
		if (bHasFlag && (m_iAddr > i))
		{
			str.Format(_T("%x"), m_Has[i].dwTxValue);
			m_List_Reg.SetItem(m_hItem[i], TC_TX, TVIF_TEXT, str);
		}
		else
		{
			m_List_Reg.SetItem(m_hItem[i], TC_TX, TVIF_TEXT, _T("0"));
		}

		// 3) Ʈ�� : Mnemonic
		if (bMneFlag && (m_iMneNum > i))
		{
			// Ʈ�� ���� �߰� : Name
			strLine = m_Mne[i].strLine;
			m_List_Reg.SetItem(m_hItem[i], TC_NAME, TVIF_TEXT, strLine);

			// Name �и�.
			iNameCnt = 0;
			strLine = strLine + _T(",");
			while (iNameCnt < 32)
			{
				j = strLine.Find(',', 0);
				if (j == -1 || j == 0 && strLine.GetLength() == 1) break;

				strName[iNameCnt] = strLine.Left(j);
				iNameCnt++;

				strLine = strLine.Right(strLine.GetLength() - j - 1);
			}
			m_Mne[i].iBitNum = iNameCnt;

			// Display Bit Name
			for (j = 0; j < iNameCnt; j++)
			{
				//ProcessWindowMessage();
				if (m_bInitTree) hChildItem = m_List_Reg.InsertItem(_T(""), m_hItem[i]);
				else continue;
				// �� m_bInitTree�� FALSE�� ���?

				m_List_Reg.SetItem(hChildItem, TC_NAME, TVIF_TEXT, strName[j]);
				m_List_Reg.SetItem(hChildItem, TC_RX, TVIF_TEXT, _T("0"));
				m_List_Reg.SetItem(hChildItem, TC_TX, TVIF_TEXT, _T("0"));

				// Bit�� Tx �и�
				if (bHasFlag && m_iAddr > i)
				{
					iLb = strName[j].Find(_T("["));
					iRb = strName[j].Find(_T("]"));
					iCc = strName[j].Find(_T(":"));

					if (((iLb != -1) && (iRb != -1)) || (iLb < iRb))
					{
						//[n:n-x]
						if (iCc != -1)
						{
							str = strName[j].Mid(iLb + 1, iCc - iLb - 1);
							iStart = (!CheckDec(str)) ? -1 : _ttoi(str);

							str = strName[j].Mid(iCc + 1, iRb - iCc - 1);
							iEnd = (!CheckDec(str)) ? -1 : _ttoi(str);

							if (INMIDDLE(iStart, 0, 31) && INMIDDLE(iEnd, 0, 31) && iStart >= iEnd)
							{
								strValue.Format(_T("%x"), m_Has[i].dwTxValue);
								str.Format(_T("%x"), SliceVal(strValue, iStart, iEnd));

								m_List_Reg.SetItem(hChildItem, TC_TX, TVIF_TEXT, str);

								m_Mne[i].iStart[j] = iStart;
								m_Mne[i].iEnd[j] = iEnd;
							}
							else
							{
								m_Mne[i].iStart[j] = -1;
								m_Mne[i].iEnd[j] = -1;
							}
						}
						//[n]
						else
						{
							str = strName[j].Mid(iLb + 1, iRb - iLb - 1);
							iStart = (!CheckDec(str)) ? -1 : _ttoi(str);
							iEnd = iStart;

							if (INMIDDLE(iStart, 0, 31))
							{
								strValue.Format(_T("%x"), m_Has[i].dwTxValue);
								str.Format(_T("%x"), SliceVal(strValue, iStart));

								m_List_Reg.SetItem(hChildItem, TC_TX, TVIF_TEXT, str);

								m_Mne[i].iStart[j] = iStart;
								m_Mne[i].iEnd[j] = iEnd;
							}
							else
							{
								m_Mne[i].iStart[j] = -1;
								m_Mne[i].iEnd[j] = -1;
							}
						}
					}
					else
					{
						m_Mne[i].iStart[j] = -1;
						m_Mne[i].iEnd[j] = -1;
					}
				}
				//Sleep(0);
				Wait(0);
			}
		}
		//Sleep(0);
		Wait(0);;
	}

	m_List_Reg.SetRedraw(TRUE);

	// ----------------------------------------------------------------------------------------------------
	// 4. Read, Write ComboBox
	if (m_iAddr > 0)
	{
		for (i = m_Cbo_ReadStart.GetCount() - 1; i >= 0; i--)	m_Cbo_ReadStart.DeleteString(i);
		for (i = m_Cbo_ReadEnd.GetCount() - 1; i >= 0; i--)	m_Cbo_ReadEnd.DeleteString(i);
		for (i = m_Cbo_WriteStart.GetCount() - 1; i >= 0; i--)	m_Cbo_WriteStart.DeleteString(i);
		for (i = m_Cbo_WriteEnd.GetCount() - 1; i >= 0; i--)	m_Cbo_WriteEnd.DeleteString(i);

		j = 0;

		for (i = 0; i < m_iAddr; i++)
		{
			//ProcessWindowMessage();
			if (bMneFlag && m_iMneNum > i) // MNE : O
				if (m_Mne[i].strLine == _T("")) continue;

			if ((m_Has != NULL) && (m_Mne == NULL)) // HAS : O / MNE : X
				if (m_Has[i].bOn == FALSE) continue;

			str.Format(_T("%x"), i);
			m_Cbo_ReadStart.InsertString(j, str);
			m_Cbo_ReadEnd.InsertString(j, str);
			m_Cbo_WriteStart.InsertString(j, str);
			m_Cbo_WriteEnd.InsertString(j, str);
			j++;
			//Sleep(0);
			Wait(0);
		}

		m_Cbo_ReadStart.SetCurSel(0);
		m_Cbo_ReadEnd.SetCurSel(m_Cbo_ReadEnd.GetCount() - 1);
		m_Cbo_WriteStart.SetCurSel(0);
		m_Cbo_WriteEnd.SetCurSel(m_Cbo_WriteEnd.GetCount() - 1);
	}

	// ----------------------------------------------------------------------------------------------------
	// 5. End Display
ENDDISPLAY:
	m_bInitTree = FALSE;
	m_bOpenHas = FALSE;
	m_bOpenMne = FALSE;
	m_bOpenDes = FALSE;

	// m_iSelAddr ����
	// m_iAddr���� ������ �ʱ�ȭ
	if (m_iSelAddr > m_iAddr - 1)						m_iSelAddr = 0;
	// m_Has�� m_Mne �� �� ������ �ʱ�ȭ
	if (m_Has == NULL && m_Mne == NULL)				m_iSelAddr = 0;
	// m_Mne�� ���� �� ǥ������ �ʴ� �����̸� �ʱ�ȭ
	if (m_Mne != NULL){
		if (m_Mne[m_iSelAddr].strLine == _T(""))		m_iSelAddr = 0;
	}

	// ������ ����
	if (m_hItem != NULL)
	{
		if (m_hSelItem != NULL)
		{
			m_iSelCol = TC_NAME;
			m_hSelItem = m_hItem[m_iSelAddr];
			m_List_Reg.SelectItem(m_hSelItem, m_iSelCol);	// m_bInitTree�� TRUE�� SelChangedTreelist���� Return�ϱ� ������ m_bInitTree = FALSE�� �̰� ���� �;ߵ�...
			m_List_Reg.EnsureVisible(m_hSelItem, m_iSelCol);
			m_List_Reg.SetFocusItem(m_hSelItem, m_iSelCol);
		}
		else
		{
			m_iSelCol = TC_NAME;
			m_iSelAddr = 0;
			m_hSelItem = m_hItem[m_iSelAddr];
			m_List_Reg.SelectItem(m_hSelItem, m_iSelCol);
			m_List_Reg.EnsureVisible(m_hSelItem, m_iSelCol);
			m_List_Reg.SetFocusItem(m_hSelItem, m_iSelCol);
		}
	}

	// m_strBeforeTx ����
	if (m_Has != NULL) {
		m_strBeforeTx.Format(_T("%x"), m_Has[m_iSelAddr].dwTxValue);
	}

	SetBitButton();
	DispDes();

	this->UpdateWindow();
	m_List_Reg.UpdateWindow();
	m_List_Reg.RedrawWindow();

	return TRUE;
}

//i = m_List_Reg.GetSelectionColumn(); -> Column ��ġ ��ȯ
//HTREEITEM hChild = m_List_Reg.GetChildItem(hTree); -> ù ��° �ڽ� ��ȯ

//hTree = m_List_Reg.GetParentItem(hTree);
// GetParentItem����, �θ� ������ 0 ��ȯ

// ====================================================================================================
// CRegCtrlDlg :: OnSelChangedTreelist
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CRegCtrlDlg::OnSelChangedTreelist(NMHDR *pNmHdr, LRESULT *pResult)
{
	int i = 0;
	if (m_bInitTree) return; // DispRegInfo �Լ� �������̰�, ���� Ʈ�� �ʱ�ȭ �� ��.

	// ----------------------------------------------------------------------------------------------------
	// 1. �������(m_hSelItem, m_iSelAddr, m_iSelCol, m_strBeforeTx) ����
	m_hSelItem = m_List_Reg.GetSelectedItem();
	HTREEITEM hParentItem = m_List_Reg.GetParentItem(m_hSelItem);

	if (hParentItem == NULL)
	{
		m_iSelAddr = HexToDec(m_List_Reg.GetItemText(m_hSelItem, TC_ADDR));
		m_strBeforeTx = m_List_Reg.GetItemText(m_hSelItem, TC_TX);
	}
	else
	{
		m_iSelAddr = HexToDec(m_List_Reg.GetItemText(hParentItem, TC_ADDR));
		m_strBeforeTx = m_List_Reg.GetItemText(hParentItem, TC_TX);
	}

	m_iSelCol = m_List_Reg.GetSelectionColumn();
	m_iSearchIdx = m_iSelAddr;

	// ----------------------------------------------------------------------------------------------------
	// 2. ������ ������(m_hSelItem)�� Boldü ����, ������ ������ ������(m_hOldItem) Boldü ���
	SetBoldItem(m_hOldItem, TC_NAME, FALSE);
	SetBoldItem(m_hSelItem, TC_NAME, TRUE);

	m_hOldItem = m_hSelItem;

	// ----------------------------------------------------------------------------------------------------
	// 3. Bit Button ����
	SetBitButton();

	// ----------------------------------------------------------------------------------------------------
	// 4. ��Ÿ ����
	m_Static_Name.SetWindowTextW(m_List_Reg.GetItemText(m_hSelItem, TC_NAME));

	// ----------------------------------------------------------------------------------------------------
	// 5. Display Edit Label
	int iNum = 0;
	int iStart = 0;
	int iEnd = 0;
	DWORD dwStyle = m_List_Reg.GetStyle();

	// Has�� �������� ���� ���� Editâ�� ����� ����
	if (m_iHasNum == 0)
	{
		if (dwStyle&TVS_EDITLABELS)
		{
			m_List_Reg.SetStyle(dwStyle^TVS_EDITLABELS);
			m_List_Reg.SetColumnAutoEdit(TC_TX, NULL);
		}
		goto ENDSELCHANGEDTREELIST;
	}

	// �ڽ� �������� �����ϰ� ���� �� iStart, iEnd�� ���������� �ȵǾ������� Edit �ȶ��.
	if (hParentItem != NULL)
	{
		iNum = GetChildItemNum(hParentItem, m_hSelItem);
		if (iNum >= 0)
		{
			iStart = m_Mne[m_iSelAddr].iStart[iNum];
			iEnd = m_Mne[m_iSelAddr].iEnd[iNum];

			if (!INMIDDLE(iStart, 0, 31) || !INMIDDLE(iEnd, 0, 31))
			{
				if (dwStyle&TVS_EDITLABELS)
				{
					m_List_Reg.SetStyle(dwStyle^TVS_EDITLABELS);
					m_List_Reg.SetColumnAutoEdit(TC_TX, NULL);
				}
				goto ENDSELCHANGEDTREELIST;
			}
		}
	}

	m_List_Reg.SetStyle(dwStyle | TVS_EDITLABELS);
	m_List_Reg.SetColumnAutoEdit(TC_TX, TVAE_EDIT | TVAE_DBLCLICK);

	switch (m_iSelCol)
	{
	case TC_TX:
		m_strSelTx = m_List_Reg.GetItemText(m_hSelItem, TC_TX);
		m_List_Reg.EditLabel(m_hSelItem, TC_TX);
		break;
	}

	// ----------------------------------------------------------------------------------------------------
	// 6. End
ENDSELCHANGEDTREELIST:
	// Description ǥ��
	DispDes();

	// RedrawWindow ���ϸ� ��ũ�� ������ �� ��û ����
	m_List_Reg.RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

// ====================================================================================================
// CRegCtrlDlg :: SliceVal
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
int CRegCtrlDlg::SliceVal(CString strVal, int iStart, int iEnd)
{
	int i = 0;
	CString	strBin = _T("");
	CString	strOut = _T("");

	int iLen = strVal.GetLength();
	if (iLen < 8) {
		for (i = 0; i < 8 - iLen; i++)
			strVal = _T("0") + strVal;
	}

	strBin = HexToBin(strVal);

	if (iEnd == -1)	{ strOut = strBin.Mid(31 - iStart, 1); }
	else			{ strOut = strBin.Mid(31 - iStart, iStart - iEnd + 1); }

	return BinToDec(strOut);
}

int CRegCtrlDlg::SliceVal(DWORD iVal, int iStart, int iEnd)
{
	if (iEnd == -1) {
		iVal = (iVal >> iStart) & 1;
	}
	else {
		iVal = iVal >> iEnd;

		if ((iStart - iEnd + 1) < 32) //32�� �� �ʿ� ����)
			iVal -= (iVal >> (iStart - iEnd + 1)) << (iStart - iEnd + 1);
	}

	return iVal;
}

// ====================================================================================================
// CRegDlg :: SaveMne
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CRegCtrlDlg::SaveMne(CString strPath)
{
}


void CRegCtrlDlg::OnCbnEditchangeComboSearch()
{
	m_iSearchIdx = 0;
	EnableComboSearchCtrl(TRUE);
}

void CRegCtrlDlg::OnCbnSelchangeComboSearch()
{
	int iCurSel = 0;
	CString str = _T("");

	iCurSel = m_Cbo_Search.GetCurSel();
	m_Cbo_Search.GetLBText(iCurSel, str);

	m_Cbo_Search.DeleteString(iCurSel);
	m_Cbo_Search.InsertString(0, str);
	m_Cbo_Search.SetCurSel(0);
}


void CRegCtrlDlg::OnCbnSelchangeComboSearchoption()
{
	int i = 0;
	CString str = _T("");
	CString	strSearchOption = _T("");
	m_Cbo_SearchOption.GetWindowTextW(strSearchOption);

	if (strSearchOption == _T("Addr"))
	{	// Name -> Addr

		// Name ���� ����
		m_iSearchNameNum = m_Cbo_Search.GetCount();

		// Name �迭 �ʱ�ȭ
		for (i = 0; i < 10; i++) m_strSearchName[i] = _T("");

		// ����
		for (i = 0; i < m_iSearchNameNum; i++)
		{
			m_Cbo_Search.GetLBText(i, str);
			m_strSearchName[i] = str;
		}

		// m_Cbo_Search ������ ����
		for (i = m_iSearchNameNum; i >= 0; i--)
			m_Cbo_Search.DeleteString(i);

		// Addr ����
		for (i = 0; i < m_iSearchAddrNum; i++)
			m_Cbo_Search.InsertString(i, m_strSearchAddr[i]);
	}
	else if (strSearchOption == _T("Name"))
	{	// Addr -> Name

		// Addr ���� ����
		m_iSearchAddrNum = m_Cbo_Search.GetCount();

		// Addr �迭 �ʱ�ȭ
		for (i = 0; i < 10; i++) m_strSearchAddr[i] = _T("");

		for (i = 0; i < m_iSearchAddrNum; i++)
		{
			m_Cbo_Search.GetLBText(i, str);
			m_strSearchAddr[i] = str;
		}

		// m_Cbo_Search ������ ����
		for (i = m_iSearchAddrNum; i >= 0; i--)
			m_Cbo_Search.DeleteString(i);

		// Name ����
		for (i = 0; i < m_iSearchNameNum; i++)
			m_Cbo_Search.InsertString(i, m_strSearchName[i]);
	}

	//m_Cbo_Search.SetCurSel(0);

	m_Cbo_Search.SetFocus();
	m_Cbo_Search.SetEditSel(0, m_Cbo_Search.GetWindowTextLengthW());

	EnableComboSearchCtrl(TRUE);
}

void CRegCtrlDlg::EnableComboSearchCtrl(BOOL bEnable)
{
	if (!bEnable)
	{
		m_Btn_Search.EnableWindow(FALSE);
		return;
	}

	CString strSearch = _T("");
	CString strSearchOption = _T("");
	m_iSearchIdx = 0;

	m_Cbo_Search.GetWindowTextW(strSearch);
	m_Cbo_SearchOption.GetWindowTextW(strSearchOption);

	if (strSearch == _T(""))
	{
		m_Btn_Search.EnableWindow(FALSE);
	}
	else if (strSearchOption == _T("Addr"))
	{
		if ((m_iHasNum > 0) || (m_iMneNum > 0))	m_Btn_Search.EnableWindow(TRUE);
		else									m_Btn_Search.EnableWindow(FALSE);
	}
	else if (strSearchOption == _T("Name"))
	{
		if (m_iMneNum > 0)						m_Btn_Search.EnableWindow(TRUE);
		else									m_Btn_Search.EnableWindow(FALSE);
	}
	else										m_Btn_Search.EnableWindow(FALSE);
}



void CRegCtrlDlg::OnBnClickedButtonSearch()
{
	DWORD dwStyle = m_Btn_Search.GetStyle();
	if (dwStyle & WS_DISABLED) return;

	SearchReg();
}

void CRegCtrlDlg::SearchReg()
{
	// ��ư�� ��Ȱ��ȭ�Ǿ������� ���� X
	DWORD dwStyle = m_Btn_Search.GetStyle();
	if (dwStyle & WS_DISABLED) return;

	int i = 0;
	BOOL bFlag = FALSE;
	CString str = _T("");
	CString str1 = _T("");
	CString str2 = _T("");
	CString strSearch = _T("");
	CString strSearchOption = _T("");

	m_Cbo_Search.GetWindowTextW(strSearch); // �˻��� ��
	m_Cbo_SearchOption.GetWindowTextW(strSearchOption); // �˻� �ɼ�(Addr&Name)

	// Add Search ComboBox
	if (0 == m_iSearchIdx)
	{
		// �˻�
		for (i = 0; i < m_Cbo_Search.GetCount(); i++)
		{
			m_Cbo_Search.GetLBText(i, str);

			// ��Ͽ� ����
			if (strSearch == str)
			{
				m_Cbo_Search.DeleteString(i);
				m_Cbo_Search.InsertString(0, strSearch);
				m_Cbo_Search.SetCurSel(0);
				bFlag = TRUE;
				break;
			}
		}

		// ��Ͽ� ����
		if (!bFlag)
		{
			if (m_Cbo_Search.GetCount() >= 10)
				m_Cbo_Search.DeleteString(9);

			m_Cbo_Search.InsertString(0, strSearch);
			m_Cbo_Search.SetCurSel(0);
		}
	}

	// Search by Address
	if (strSearchOption == _T("Addr"))
	{
		// �����Ͱ� ���� ��� Search �Ұ���
		if ((m_iHasNum == 0) && (m_iMneNum == 0)) return;

		if (!CheckHex(strSearch))
		{
			AfxMessageBox(_T("Please, input Hex address value."));
			return;
		}

		i = HexToDec(strSearch);
		if ((i >= m_iAddr))
		{
			AfxMessageBox(_T("Address Value is too big."));
			return;
		}
		if (m_Mne != NULL)
		{
			if (m_Mne[i].strLine == _T(""))
			{
				AfxMessageBox(_T("Search finished."));
				return;
			}
		}

		m_List_Reg.SelectItem(m_hItem[i], m_iSelCol);
		m_List_Reg.SetFocusItem(m_hItem[i], m_iSelCol);
		m_List_Reg.EnsureVisible(m_hItem[i], m_iSelCol);
	}
	// Search by Name
	else if (strSearchOption == _T("Name"))
	{
		if (!m_iMneNum) return;

		while (m_iAddr > m_iSearchIdx)
		{
			//ProcessWindowMessage();
			str1 = m_Mne[m_iSearchIdx].strLine;
			str2 = strSearch;

			str1.MakeLower();
			str2.MakeLower();

			if (str1.Find(str2) >= 0)
			{
				m_List_Reg.SelectItem(m_hItem[m_iSearchIdx], m_iSelCol);
				m_List_Reg.SetFocusItem(m_hItem[m_iSearchIdx], m_iSelCol);
				m_List_Reg.EnsureVisible(m_hItem[m_iSearchIdx], m_iSelCol);
				m_iSearchIdx++;
				break;
			}
			m_iSearchIdx++;
		}

		if (m_iAddr <= m_iSearchIdx)
		{
			m_iSearchIdx = 0;
			AfxMessageBox(_T("Search finished."));
		}
	}

}

void CRegCtrlDlg::OnBeginLabelEditTreelist(NMHDR* pNMHDR, LRESULT* pResult)
{
	CEdit* edit = m_List_Reg.GetEditControl();

	edit->SetLimitText(8);
	//edit->SetLimitText(10); //�� �̰ɷ� �����ϰ� OnEndLabelEditTreelist�� 0x �˻��ϴ� �ڵ� �߰�(0x �Ⱥپ������� ������ 8����)
	m_bEdit = TRUE;
}

void CRegCtrlDlg::OnEndLabelEditTreelist(NMHDR* pNMHDR, LRESULT* pResult)
{
	TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;

	int i = 0;
	int j = 0;
	int k = 0;
	int iStart = 0;
	int iEnd = 0;
	int iLen = 0;
	int iBit[32] = { 0, };
	int iNum = 0;
	DWORD64 dwNum = 0;
	DWORD64 dwMax = 0;
	CString str = _T("");
	CString strName = _T("");
	CString strTx = _T("");
	CString strOldTx = _T("");
	CString strBin = _T("");
	CString strValue = _T("");
	HTREEITEM hParentItem = m_List_Reg.GetParentItem(m_hSelItem);

	CEdit* edit = m_List_Reg.GetEditControl();
	edit->GetWindowTextW(strTx);

	m_bEdit = FALSE;

	// ESC�� ������ ��� �������� ����.
	if (m_bESC)
	{
		m_bESC = FALSE;
		pTVDispInfo->item.pszText = (LPWSTR)(LPCWSTR)m_strSelTx;
		return;
	}

	// ENTER�� �����ų�, �� �� Editâ�� ������ ��쿡�� ���� ����Ǿ��� ���� ����/����.
	if (!m_bEnter)
	{
		if (m_strSelTx == strTx)
		{
			pTVDispInfo->item.pszText = (LPWSTR)(LPCWSTR)m_strSelTx;
			return;
		}
		m_bEnter = TRUE;
	}
	// �� �Լ��� ���� �� ������ OnRegEndLabelEdit�� ȣ��Ǳ� ������
	// m_bEnter�� ���� ����/�����ϰ� ��.

	// ----------------------------------------------------------------------------------------------------
	// 1. �˻�
	// Register File
	if (m_Has == NULL)
	{
		m_bEnter = FALSE;
		pTVDispInfo->item.pszText = (LPWSTR)(LPCWSTR)m_strSelTx;
		return;
	}
	// Mnemonic File
	if (m_Mne == NULL)
	{
		m_bEnter = FALSE;
		pTVDispInfo->item.pszText = (LPWSTR)(LPCWSTR)m_strSelTx;
		return;
	}
	// Name Ȯ��
	strName = m_List_Reg.GetItemText(m_hSelItem, TC_NAME);
	if ((strName == _T("")) || (strName.Find('[') == -1) || (strName.Find(']') == -1))
	{
		m_bEnter = FALSE;
		return;
	}

	// Tx(Hex)
	if (!CheckHex(strTx))
	{
		AfxMessageBox(_T("Please, input Hex value."));

		m_bEnter = FALSE;
		pTVDispInfo->item.pszText = (LPWSTR)(LPCWSTR)m_strSelTx;
		return;
	}

	// ���ڹ���
	// Child
	if (hParentItem)
	{
		iNum = GetChildItemNum(hParentItem, m_hSelItem);
		if (iNum == -1) iNum = (int)m_hSelItem - (int)m_List_Reg.GetChildItem(hParentItem);

		iStart = m_Mne[m_iSelAddr].iStart[iNum];
		iEnd = m_Mne[m_iSelAddr].iEnd[iNum];

		if (!INMIDDLE(iStart, 0, 31) || !INMIDDLE(iEnd, 0, 31))
		{
			AfxMessageBox(_T("Please, check item name."));

			m_bEnter = FALSE;
			pTVDispInfo->item.pszText = (LPWSTR)(LPCWSTR)m_strSelTx;
			return;
		}

		dwNum = HexToDec(strTx);
		dwMax = (DWORD64)(pow((double)2, (iStart - iEnd + 1)));

		if (dwNum >= dwMax)
		{
			AfxMessageBox(_T("Tx value is too big."));

			m_bEnter = FALSE;
			pTVDispInfo->item.pszText = (LPWSTR)(LPCWSTR)m_strSelTx;
			return;
		}
	}
	// Root
	else
	{
		if (strTx.GetLength() > 8)
		{
			m_bEnter = FALSE;
			pTVDispInfo->item.pszText = (LPWSTR)(LPCWSTR)m_strSelTx;
			return;
		}
	}

	// 2. ����
	// ���۾��� OnRegEndLabelEdit�� DispTxReg ���� ���ְ�
	// �ϴ� �θ� �������� Tx Column���� ����.
	if (hParentItem)
	{
		strValue = m_List_Reg.GetItemText(hParentItem, TC_TX);
		strOldTx = strValue;

		iLen = strValue.GetLength();
		if (iLen < 8)
		{
			for (i = 0; i < 8 - iLen; i++)
				strValue = _T("0") + strValue;
		}
		strValue = HexToBin(strValue);

		strBin = HexToBin(strTx);
		iLen = strBin.GetLength();
		if (iLen < (iStart - iEnd + 1))
		{
			for (i = 0; i < iStart - iEnd + 1 - iLen; i++)
				strBin = _T("0") + strBin;
		}
		else if (iLen >(iStart - iEnd + 1))
			strBin = strBin.Right(iStart - iEnd + 1);

		strValue = strValue.Left(31 - iStart) + strBin + strValue.Right(iEnd);
		strValue.Format(_T("%x"), BinToDec(strValue));
		m_List_Reg.SetItemText(hParentItem, strValue, TC_TX);
	}
	else
	{
		strOldTx = m_strSelTx;
		m_List_Reg.SetItemText(m_hSelItem, strTx, TC_TX);
	}

	m_strBeforeTx = strOldTx;
	m_bLabelEdit = TRUE;
	m_iEditAddr = m_iSelAddr;
}

LRESULT	CRegCtrlDlg::OnRegEndLabelEdit(WPARAM wParam, LPARAM lParam)
{
	if (m_Has == NULL || m_Mne == NULL)
		return 0L;

	CString	strTx = m_List_Reg.GetItemText(m_hItem[m_iEditAddr], TC_TX);

	if (!m_bEnter) return 0L;
	m_bEnter = FALSE;

	// ǥ��
	DispTxReg(m_iEditAddr, strTx);

	// ����
#ifndef ISPtoJTAG
	if ((pComPort->m_bConnected) && (!pLuaDlg->m_bLua))
		pUART->WriteISP(m_iEditAddr, HexToDec(strTx));
#else

#if 0
	CString strMsg = _T("");
	// Initial JTAG
	pJTAG->JTAGInitial(strMsg);

	if (!pLuaDlg->m_bLua)
		EN673_REG_WRITE(UINT32(m_dwEN673BaseAdr) + UINT32(m_iEditAddr << 2), (UINT32)HexToDec(strTx));

#endif
	BYTE* temp;
	int state;

	//temp = (BYTE *)(ntohl(BinToDec(strTx)));
	temp = (BYTE *)(ntohl(m_Has[m_iEditAddr].dwTxValue));
	if (ConnectSocket != NULL)
	{
		if (m_iEditAddr < 8000)
			state = setDataFromRemote(ConnectSocket, m_dwEN673BaseAdr + (m_iEditAddr << 2), 4, WB0, &temp);
		else
			state = WriteISP(m_iEditAddr, HexToDec(strTx));
		if (state < 0)
			AfxMessageBox(_T("Read Fail"));
	}
	else
	{
		AfxMessageBox(_T("Not Connect"));
	}


	// Check Feedback
	if (pRegDlg->m_Chk_FeedBackWrite.GetCheck())
		pRegDlg->DispRxReg(m_iEditAddr, HexToDec(strTx));
#endif
	return 0L;
}

void CRegCtrlDlg::SetBitButton()
{
	int i = 0;
	int j = 0;
	int iLen = 0;
	int iStart = 0;
	int iEnd = 0;
	int iSelBit = -1;
	BOOL bHas = m_iHasNum > 0 ? TRUE : FALSE;
	BOOL bMne = m_iMneNum > 0 ? TRUE : FALSE;
	BOOL iFlag[32] = { 0, };
	CString strValue = _T(""); // Tx Binary
	HTREEITEM hParentItem = NULL;

	// ----------------------------------------------------------------------------------------------------
	// 1. �˻�
	// Has, Mne
	if (!bHas || (m_hSelItem == NULL))
	{
		for (i = 0; i < 32; i++)
			EnableBtnBit(i, FALSE);
		return;
	}

	// ----------------------------------------------------------------------------------------------------
	// 2. strValue -> Binary�� ����
	strValue.Format(_T("%08x"), m_Has[m_iSelAddr].dwTxValue);
	strValue = HexToBin(strValue);

	// ��ư ���� ����
	if (bMne)
	{
		if (m_Mne[m_iSelAddr].strLine == _T(""))
		{
			for (i = 0; i < 32; i++)
				iFlag[i] = 1;
		}
		else
		{
			if (m_Mne[m_iSelAddr].iBitNum == 1)
			{
				for (i = 0; i < 32; i++)
					iFlag[i] = 1;
			}
			else
			{
				for (i = 0; i < m_Mne[m_iSelAddr].iBitNum; i++)
				{
					iStart = m_Mne[m_iSelAddr].iStart[i];
					iEnd = m_Mne[m_iSelAddr].iEnd[i];

					if (!INMIDDLE(iStart, 0, 31) || !INMIDDLE(iEnd, 0, 31)) continue;

					for (j = iStart; j >= iEnd; j--)
						iFlag[j] = (i % BTN_BITCOLORNUM) + 1;
				}
			}
		}
	}
	else
	{
		for (i = 0; i < 32; i++)
			iFlag[i] = 1;
	}

	// iSelBit
	hParentItem = m_List_Reg.GetParentItem(m_hSelItem);
	if (hParentItem)
	{
		iSelBit = GetChildItemNum(hParentItem, m_hSelItem);
	}

	if (iSelBit >= 0)
	{
		iStart = m_Mne[m_iSelAddr].iStart[iSelBit];
		iEnd = m_Mne[m_iSelAddr].iEnd[iSelBit];
	}

	// ��ư ���� ����
	for (i = 0; i < 32; i++)
	{
		m_Btn_Bit[i].SetWindowTextW(strValue.Mid(31 - i, 1));

		// ��Ȱ��ȭ
		if (!iFlag[i])
			EnableBtnBit(i, FALSE);
		//Ȱ��ȭ
		else
		{
			// ������ ������ = �θ�
			if (iSelBit == -1)
			{
				m_Btn_Bit[i].EnableWindow(TRUE);
				m_Btn_Bit[i].SetReverseBg(TRUE);
				m_Btn_Bit[i].SetColor(CButtonST::BTNST_COLOR_BK_OUT, BITCOLOR[iFlag[i] - 1]);
				m_Btn_Bit[i].SetColor(CButtonST::BTNST_COLOR_BK_IN, BITCOLORH[iFlag[i] - 1]);
			}
			// ������ ������ = �ڽ�
			else
			{
				if (!INMIDDLE(iStart, 0, 31) || !INMIDDLE(iEnd, 0, 31))
					return;

				m_Btn_Bit[i].EnableWindow(TRUE);
				m_Btn_Bit[i].SetReverseBg(TRUE);

				if (i <= iStart && i >= iEnd)
					m_Btn_Bit[i].SetColor(CButtonST::BTNST_COLOR_BK_OUT, BITCOLOR[iFlag[i] - 1]);
				else
					m_Btn_Bit[i].SetColor(CButtonST::BTNST_COLOR_BK_OUT, DEF_BITCOLOR);

				m_Btn_Bit[i].SetColor(CButtonST::BTNST_COLOR_BK_IN, BITCOLORH[iFlag[i] - 1]);
			}
		}
		// if((i^8) == 0) Sleep(0);
	}
}



void CRegCtrlDlg::OnBnClickedButtonBit31() { OnBnClickedButtonBit(31); }
void CRegCtrlDlg::OnBnClickedButtonBit30() { OnBnClickedButtonBit(30); }
void CRegCtrlDlg::OnBnClickedButtonBit29() { OnBnClickedButtonBit(29); }
void CRegCtrlDlg::OnBnClickedButtonBit28() { OnBnClickedButtonBit(28); }
void CRegCtrlDlg::OnBnClickedButtonBit27() { OnBnClickedButtonBit(27); }
void CRegCtrlDlg::OnBnClickedButtonBit26() { OnBnClickedButtonBit(26); }
void CRegCtrlDlg::OnBnClickedButtonBit25() { OnBnClickedButtonBit(25); }
void CRegCtrlDlg::OnBnClickedButtonBit24() { OnBnClickedButtonBit(24); }
void CRegCtrlDlg::OnBnClickedButtonBit23() { OnBnClickedButtonBit(23); }
void CRegCtrlDlg::OnBnClickedButtonBit22() { OnBnClickedButtonBit(22); }
void CRegCtrlDlg::OnBnClickedButtonBit21() { OnBnClickedButtonBit(21); }
void CRegCtrlDlg::OnBnClickedButtonBit20() { OnBnClickedButtonBit(20); }
void CRegCtrlDlg::OnBnClickedButtonBit19() { OnBnClickedButtonBit(19); }
void CRegCtrlDlg::OnBnClickedButtonBit18() { OnBnClickedButtonBit(18); }
void CRegCtrlDlg::OnBnClickedButtonBit17() { OnBnClickedButtonBit(17); }
void CRegCtrlDlg::OnBnClickedButtonBit16() { OnBnClickedButtonBit(16); }
void CRegCtrlDlg::OnBnClickedButtonBit15() { OnBnClickedButtonBit(15); }
void CRegCtrlDlg::OnBnClickedButtonBit14() { OnBnClickedButtonBit(14); }
void CRegCtrlDlg::OnBnClickedButtonBit13() { OnBnClickedButtonBit(13); }
void CRegCtrlDlg::OnBnClickedButtonBit12() { OnBnClickedButtonBit(12); }
void CRegCtrlDlg::OnBnClickedButtonBit11() { OnBnClickedButtonBit(11); }
void CRegCtrlDlg::OnBnClickedButtonBit10() { OnBnClickedButtonBit(10); }
void CRegCtrlDlg::OnBnClickedButtonBit9() { OnBnClickedButtonBit(9); }
void CRegCtrlDlg::OnBnClickedButtonBit8() { OnBnClickedButtonBit(8); }
void CRegCtrlDlg::OnBnClickedButtonBit7() { OnBnClickedButtonBit(7); }
void CRegCtrlDlg::OnBnClickedButtonBit6() { OnBnClickedButtonBit(6); }
void CRegCtrlDlg::OnBnClickedButtonBit5() { OnBnClickedButtonBit(5); }
void CRegCtrlDlg::OnBnClickedButtonBit4() { OnBnClickedButtonBit(4); }
void CRegCtrlDlg::OnBnClickedButtonBit3() { OnBnClickedButtonBit(3); }
void CRegCtrlDlg::OnBnClickedButtonBit2() { OnBnClickedButtonBit(2); }
void CRegCtrlDlg::OnBnClickedButtonBit1() { OnBnClickedButtonBit(1); }
void CRegCtrlDlg::OnBnClickedButtonBit0() { OnBnClickedButtonBit(0); }

// ====================================================================================================
// CRegDlg :: OnBnClickedButtonBit
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CRegCtrlDlg::OnBnClickedButtonBit(int iNum)
{
	if (m_iAddr == 0) return;

	int i = 0;
	int iStart = 0;
	int iEnd = 0;
	int iBitNum = -1;
	CString str = _T("");
	CString strBin = _T("");
	DWORD dwValue = 0;
	HTREEITEM hItem = m_hItem[m_iSelAddr];

	BOOL bHas = m_iHasNum > 0 ? TRUE : FALSE;
	BOOL bMne = m_iMneNum > 0 ? TRUE : FALSE;

	if (!bHas && !bMne) return;

	// ----------------------------------------------------------------------------------------------------
	// 1. iBitNum (���� ����)
	if (m_Mne != NULL)
	{
		for (i = 0; i < m_Mne[m_iSelAddr].iBitNum; i++)
		{
			iStart = m_Mne[m_iSelAddr].iStart[i];
			iEnd = m_Mne[m_iSelAddr].iEnd[i];

			if (INMIDDLE(iNum, iEnd, iStart))
			{
				iBitNum = i;
				break;
			}
		}
		if (iBitNum == -1) return;
	}
	else
	{
		iBitNum = 0;
	}

	// ----------------------------------------------------------------------------------------------------
	// 2. ���� �� ����
	dwValue = m_Has[m_iSelAddr].dwTxValue;
	dwValue ^= (1 << iNum);

	DispTxReg(m_iSelAddr, dwValue);

	// ----------------------------------------------------------------------------------------------------
	// 3. Select hItem
	HTREEITEM hChildItem = GetNumChildItem(hItem, iBitNum);
	if (hChildItem)
	{
		m_List_Reg.SelectItem(hChildItem, m_iSelCol);
		m_List_Reg.EnsureVisible(hChildItem, m_iSelCol);
	}

	// ----------------------------------------------------------------------------------------------------
	// 4. Ʈ�� ����
	i = m_List_Reg.GetItemState(hItem, TVIS_EXPANDED);
	if (i == 0)
	{
		i |= TVIS_EXPANDED;
		m_List_Reg.SetItemState(hItem, i, TVIS_EXPANDED);
	}

#ifndef ISPtoJTAG
	if (pComPort->m_bConnected)
		pUART->WriteISP(m_iSelAddr, dwValue);
#else
#if 0
	if (pJTAG->m_bJTAGOpen)
		EN673_REG_WRITE(UINT32(m_dwEN673BaseAdr) + UINT32(m_iSelAddr << 2), UINT32(dwValue));
#endif
	BYTE* temp;
	int state;

	temp = (BYTE *)(ntohl(dwValue));

	if (ConnectSocket != NULL)
	{
		if (m_iSelAddr < 8000)
			state = setDataFromRemote(ConnectSocket, m_dwEN673BaseAdr + (m_iSelAddr << 2), 4, WB0, &temp);
		else
			state = WriteISP(m_iSelAddr, dwValue);

		if (state < 0)
			AfxMessageBox(_T("Read Fail"));
	}
	else
	{
		AfxMessageBox(_T("Not Connect"));
	}

	// Check Feedback
	if (pRegDlg->m_Chk_FeedBackWrite.GetCheck())
		pRegDlg->DispRxReg(m_iSelAddr, HexStringOut(dwValue));

#endif

}

void CRegCtrlDlg::EnableBtnBit(int iIndex, BOOL bFlag)
{
	if (bFlag)
	{
		m_Btn_Bit[iIndex].EnableWindow(TRUE);
		m_Btn_Bit[iIndex].SetReverseBg(TRUE);
		m_Btn_Bit[iIndex].SetColor(CButtonST::BTNST_COLOR_BK_OUT, DEF_BITCOLOR);
		m_Btn_Bit[iIndex].SetColor(CButtonST::BTNST_COLOR_BK_IN, DEF_BITCOLOR + RGB(100, 100, 120));
	}
	else
	{
		m_Btn_Bit[iIndex].EnableWindow(FALSE);
		m_Btn_Bit[iIndex].SetReverseBg(FALSE);
		m_Btn_Bit[iIndex].SetColor(CButtonST::BTNST_COLOR_BK_OUT, GetSysColor(COLOR_BTNFACE));
		m_Btn_Bit[iIndex].SetColor(CButtonST::BTNST_COLOR_BK_IN, GetSysColor(COLOR_3DHILIGHT));
	}
}


void CRegCtrlDlg::OnBnClickedButtonRegread()
{
#ifndef ISPtoJTAG
	if (!pComPort->m_bConnected) return;

	pUART->ReadISP(m_iSelAddr);
#else

#if 0
	CString strMsg = _T("");
	// Initial JTAG
	pJTAG->JTAGInitial(strMsg);

	UINT32 data;
	EN673_REG_READ(UINT32(m_dwEN673BaseAdr) + UINT32(m_iSelAddr << 2), &data);
	//state = jtag_read32(UINT32(m_dwEN673BaseAdr) + UINT32(m_iSelAddr << 2), &data, WB0);
#endif

	BYTE* temp = NULL;
	BYTE* flag;
	UINT32 data;
	int state;
	RxCheck_flag = TRUE;
	if (ConnectSocket != NULL)
	{
		if (m_iSelAddr < 0x8000)
		{
			state = getDataFromRemote(ConnectSocket, m_dwEN673BaseAdr + (m_iSelAddr << 2), 4, WB0, &temp);
		}
		else
		{
			state = ReadISP(m_iSelAddr);
			int iCnt = 0;
			int iiCnt = 0;
			do{
				//Sleep(10);
				//ProcessWindowMessage();
				Wait(10);
				state = getDataFromRemote(ConnectSocket, tx_addr, 4, WBCOM, &flag);
				if (state < 0 | iCnt > RETRY)
				{
					RxCheck_flag = FALSE;
					break;
				}
				if ((((UINT32)flag & 0X0000ffff) == 0xd002) | iiCnt == RETRY)
				{
					iiCnt = 0;
					iCnt++;
					state = ReadISP(m_iSelAddr);
				}
				iiCnt++;
			} while (((UINT32)flag & 0X0000ffff) != 0x2002);
			if (RxCheck_flag)
				state = getDataFromRemote(ConnectSocket, tx_addr + (1 << 2), 4, WBCOM, &temp);
		}

		if (state < 0 | !RxCheck_flag)
		{
			if (ConnectSocket)
			{
				NetClo(ConnectSocket);
				ConnectSocket = NULL;
			}

			if (StateSocket)
			{
				NetClo(StateSocket);
				StateSocket = NULL;
			}
			pRegDlg->EnableCtrl(FALSE);
			pRegDlg->m_Btn_Connect.SetIcon(IDI_DISCONNECT, NULL);
			AfxMessageBox(_T("Read Fail"));
		}
	}
	else
	{
		AfxMessageBox(_T("Not Connect"));
	}

	data = ntohl((UINT32)temp);

	// Reg
	// Display Rx
	pRegDlg->DispRxReg(m_iSelAddr, HexStringOut(data));

	// Check Feedback
	if (pRegDlg->m_Chk_FeedBackRead.GetCheck())
		pRegDlg->DispTxReg(m_iSelAddr, data);
#endif
}


void CRegCtrlDlg::OnDeltaposSpinRead(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	m_Btn_RegRead.SetFocus();

	if (m_iHasNum == 0 && m_iMneNum == 0) return;

	if (m_bEdit) return; // �������� �� �۵����� ����

	HTREEITEM hItem = NULL;
	HTREEITEM hParentItem = m_List_Reg.GetParentItem(m_hSelItem);

	if (hParentItem) m_hSelItem = hParentItem;

	// Down (�ּ� ����)
	if (pNMUpDown->iDelta > 0)
	{
		hItem = m_List_Reg.GetNextItem(m_hSelItem);
	}
	// Up (�ּ� ����)
	else if (pNMUpDown->iDelta < 0)
	{
		if (hParentItem)
			hItem = m_hSelItem;
		else
			hItem = m_List_Reg.GetPrevSiblingItem(m_hSelItem);
	}

	if (hItem == NULL) return;

	// ��ġ �̵�
	m_List_Reg.SelectItem(hItem, m_iSelCol);
	m_List_Reg.EnsureVisible(hItem, m_iSelCol);

	// ��Ʈ�� ���������� �� �̻� �������� ����.
#ifndef ISPtoJTAG
	if (!pComPort->m_bConnected) return;
#else
#if 0
	if (!pJTAG->m_bJTAGOpen) return;
#endif
	if (!ConnectSocket) return;
#endif	

	if (m_List_Reg.GetParentItem(m_List_Reg.GetSelectedItem()) != NULL) return;

#ifndef ISPtoJTAG
	pUART->ReadISP(m_iSelAddr);
#else

#if 0
	CString strMsg = _T("");
	// Initial JTAG
	pJTAG->JTAGInitial(strMsg);

	UINT32 data;
	EN673_REG_READ(UINT32(m_dwEN673BaseAdr) + UINT32(m_iSelAddr << 2), &data);

#endif

	BYTE* temp = NULL;
	BYTE* flag;
	UINT32 data;
	int state;
	RxCheck_flag = TRUE;
	if (ConnectSocket != NULL)
	{
		if (m_iSelAddr < 8000)
			state = getDataFromRemote(ConnectSocket, m_dwEN673BaseAdr + (m_iSelAddr << 2), 4, WB0, &temp);
		else
		{
			state = ReadISP(m_iSelAddr);
			int iCnt = 0;
			int iiCnt = 0;
			do{
				//Sleep(10);
				//ProcessWindowMessage();
				Wait(10);
				state = getDataFromRemote(ConnectSocket, tx_addr, 4, WBCOM, &flag);
				if (state < 0 | iCnt > RETRY)
				{
					RxCheck_flag = FALSE;
					break;
				}
				if ((((UINT32)flag & 0X0000ffff) == 0xd002) | iiCnt == RETRY)
				{
					iiCnt = 0;
					iCnt++;
					state = ReadISP(m_iSelAddr);
				}
				iiCnt++;
			} while (((UINT32)flag & 0X0000ffff) != 0x2002);
			if (RxCheck_flag)
				state = getDataFromRemote(ConnectSocket, tx_addr + (1 << 2), 4, WBCOM, &temp);
		}

		if (state < 0 | !RxCheck_flag)
		{
			if (ConnectSocket)
			{
				NetClo(ConnectSocket);
				ConnectSocket = NULL;
			}

			if (StateSocket)
			{
				NetClo(StateSocket);
				StateSocket = NULL;
			}
			pRegDlg->EnableCtrl(FALSE);
			pRegDlg->m_Btn_Connect.SetIcon(IDI_DISCONNECT, NULL);
			AfxMessageBox(_T("Read Fail"));
		}
	}
	else
	{
		AfxMessageBox(_T("Not Connect"));
	}

	data = ntohl((UINT32)temp);

	// Reg
	// Display Rx
	pRegDlg->DispRxReg(m_iSelAddr, HexStringOut(data));

	// Check Feedback
	if (pRegDlg->m_Chk_FeedBackRead.GetCheck())
		pRegDlg->DispTxReg(m_iSelAddr, data);
#endif

	*pResult = 0;
}



void CRegCtrlDlg::OnBnClickedButtonRegreadall()
{
	int i = 0;
	int iStart = 0;
	int iEnd = 0;
	CString str = _T("");

	// 1. JTAG
	// ���� Ȯ��
	if (!ConnectSocket) return;

	// ���� ����
	if (bRunReadAllThread) {
		m_bStopAll = TRUE;
		return;
	}

	// 2. ���� Ȯ��
	// Start : Hex���� Ȯ��
	m_Cbo_ReadStart.GetWindowTextW(str);
	if (!CheckHex(str))
	{
		AfxMessageBox(_T("Read start value is wrong."));
		::SetFocus(m_Cbo_ReadStart.m_hWnd);
		return;
	}
	iStart = HexToDec(str);

	// End : Hex���� Ȯ��
	m_Cbo_ReadEnd.GetWindowTextW(str);
	if (!CheckHex(str))
	{
		AfxMessageBox(_T("Read end value is wrong."));
		::SetFocus(m_Cbo_ReadEnd.m_hWnd);
		return;
	}
	iEnd = HexToDec(str);

	// Start�� m_iAddr���� ū�� Ȯ��
	if (iStart > m_iAddr)
	{
		str.Format(_T("Read start value is too big. (Max : 0x%x)"), m_iAddr);
		AfxMessageBox(str);
		return;
	}

	// End�� m_iAddr���� ū�� Ȯ��
	if (iEnd > m_iAddr)
	{
		str.Format(_T("Read end value is too big. (Max : 0x%x)"), m_iAddr);
		AfxMessageBox(str);
		return;
	}

	// iStart�� iEnd���� ū�� Ȯ��
	if (iStart > iEnd)
	{
		AfxMessageBox(_T("Start address is too big than End address."));
		return;
	}

	// ���� ������ ����
	HTREEITEM hItem = NULL;
	for (i = iStart; i <= iEnd; i++)
	{
		str = m_List_Reg.GetItemText(m_hItem[i], TC_ADDR);
		if (str != _T(""))
		{
			m_List_Reg.SelectItem(m_hItem[i]);
			break;
		}
	}

	StartReadAllThread();
}


void CRegCtrlDlg::StartReadAllThread()
{
	// ====================================================================================================
	// Run Loading Thread
	g_pLoadingThread = AfxBeginThread(LoadingThread, pRegDlg->GetSafeHwnd(), THREAD_PRIORITY_NORMAL);

	// ====================================================================================================
	// Read All Thread
	g_pRegReadAllThread = AfxBeginThread(ReadAllThread, pRegDlg->GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
}

// ====================================================================================================
// ReadAllThread
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
UINT ReadAllThread(LPVOID pParam)
{
	//Sleep(100);
	Wait(100);

	bRunReadAllThread = TRUE;

	int i = 0;
	int iCnt = 0;
	CString	str = _T("");

	// ----------------------------------------------------------------------------------------------------
	// On Stop
	pRegDlg->m_Btn_RegReadAll.SetWindowTextW(_T("Stop"));
	pRegDlg->m_Btn_RegReadAll.EnableWindow(TRUE);

	// ----------------------------------------------------------------------------------------------------
	// Set Area
	// Start Address
	pRegDlg->m_Cbo_ReadStart.GetWindowTextW(str);
	int iStartAddr = HexToDec(str);

	// End Address
	pRegDlg->m_Cbo_ReadEnd.GetWindowTextW(str);
	int iEndAddr = HexToDec(str);

	// ----------------------------------------------------------------------------------------------------
	// Initialize
	g_iRxAddress = -1;

	// ----------------------------------------------------------------------------------------------------
	// Read
	// Start
	int iAddr = 0;
	HTREEITEM hItem = pRegDlg->m_hSelItem;
	HTREEITEM hItemTemp = pRegDlg->m_hItem[iStartAddr];

	while (1)
	{
		if (pRegDlg->m_bStopAll) break; // Stop Read All
		if (hItemTemp == NULL) break; // Check HTREEITEM
		iAddr = HexToDec(pRegDlg->m_List_Reg.GetItemText(hItemTemp, TC_ADDR));
		if (iAddr > iEndAddr) break; // Check Address

		hItem = hItemTemp; // Check Complate
		pRegDlg->m_List_Reg.EnsureVisible(hItem);	// Move TreeList
		pRegDlg->m_List_Reg.SelectItem(hItem);		// TreeList Select

		BYTE* temp = NULL;
		BYTE* flag;
		UINT32 data;
		int state;
		pRegDlg->RxCheck_flag = TRUE;
		if (ConnectSocket != NULL)
		{
			if (iAddr < 0x8000)
				state = getDataFromRemote(ConnectSocket, m_dwEN673BaseAdr + (iAddr << 2), 4, WB0, &temp);
			else
			{
				state = ReadISP(iAddr);
				int iCnt = 0;
				int iiCnt = 0;
				do{
					if (pRegDlg->m_bStopAll) break; // Stop Read All
					//Sleep(10);
					//ProcessWindowMessage();
					Wait(10);
					state = getDataFromRemote(ConnectSocket, tx_addr, 4, WBCOM, &flag);
					if (state < 0 | iCnt > RETRY)
					{
						pRegDlg->RxCheck_flag = FALSE;
						break;
					}
					if ((((UINT32)flag & 0X0000ffff) == 0xd002) | iiCnt == RETRY)
					{
						iiCnt = 0;
						iCnt++;
						state = ReadISP(iAddr);
					}
					iiCnt++;
				} while (((UINT32)flag & 0X0000ffff) != 0x2002);
				if (pRegDlg->RxCheck_flag)
					state = getDataFromRemote(ConnectSocket, tx_addr + (1 << 2), 4, WBCOM, &temp);
			}
			
			if (state < 0 | !pRegDlg->RxCheck_flag)
			{
				if (ConnectSocket)
				{
					NetClo(ConnectSocket);
					ConnectSocket = NULL;
				}

				if (StateSocket)
				{
					NetClo(StateSocket);
					StateSocket = NULL;
				}

				pRegDlg->EnableCtrl(FALSE);
				pRegDlg->m_Btn_Connect.SetIcon(IDI_DISCONNECT, NULL);
				AfxMessageBox(_T("Read Fail"));
				goto ENDREADALL;
			}
		}
		else
		{
			AfxMessageBox(_T("Not Connect"));
			goto ENDREADALL;
		}

		data = ntohl((UINT32)temp);


		iCnt = 0;

		while (iAddr > g_iRxAddress) // Wait
		{
			if (pRegDlg->m_bStopAll) break; // Stop Read All
			iCnt++;
			if (iCnt == 1000)
			{
				str.Format(_T("Fail Read Value. (Address : %x)"), iAddr);
				AfxMessageBox(str);

				pRegDlg->m_List_Reg.SelectItem(hItem);
				pRegDlg->m_List_Reg.EnsureVisible(hItem);
				goto ENDREADALL;
			}
			//Sleep(1);
			//ProcessWindowMessage();
			Wait(1);

			g_iRxAddress = iAddr;
		}

		// Reg
		// Display Rx
		pRegDlg->DispRxReg(iAddr, HexStringOut(data));

		// Check Feedback
		if (pRegDlg->m_Chk_FeedBackRead.GetCheck())
			pRegDlg->DispTxReg(iAddr, data);

		if (iAddr >= iEndAddr) break; // Check End Address

		hItemTemp = pRegDlg->m_List_Reg.GetNextItem(hItem); // Next HTREEITEM

		//Sleep(0);
		//ProcessWindowMessage();
		Wait(0);
	}

	pRegDlg->m_List_Reg.SelectItem(hItem);
	pRegDlg->m_List_Reg.EnsureVisible(hItem);

	// ----------------------------------------------------------------------------------------------------
	// End Read All
ENDREADALL:
	pRegDlg->m_Btn_RegReadAll.SetWindowTextW(_T("Read All"));
	pRegDlg->m_bStopAll = FALSE;

	bRunReadAllThread = FALSE;
	pRegDlg->m_bLoading = FALSE;

	//::CloseHandle(g_pRegReadAllThread->m_hThread);
	return 0L;
}

void CRegCtrlDlg::OnBnClickedButtonRegwrite()
{
#ifndef ISPtoJTAG
	if (!pComPort->m_bConnected) return;

	pUART->WriteISP(m_iSelAddr, m_Has[m_iSelAddr].dwTxValue);
#else
#if 0
	CString strMsg = _T("");
	// Initial JTAG
	pJTAG->JTAGInitial(strMsg);
#endif

#if 1
	m_List_Reg.EditLabel(m_hSelItem, TC_TX);

	CString strValue;
	HTREEITEM hParentItem = m_List_Reg.GetParentItem(m_hSelItem);
	if (!hParentItem)
		strValue = m_List_Reg.GetItemText(m_hSelItem, TC_TX);
	else
		strValue = m_List_Reg.GetItemText(hParentItem, TC_TX);
	DispTxReg(m_iSelAddr, strValue);
	//DispTxReg(m_iSelAddr, m_Has[m_iSelAddr].dwTxValue);

	// Reg
	// Display Tx
	pRegDlg->DispTxReg(m_iSelAddr, HexStringOut(m_Has[m_iSelAddr].dwTxValue));

#endif

#if 0
	EN673_REG_WRITE(UINT32(m_dwEN673BaseAdr) + UINT32(m_iSelAddr << 2), (UINT32)m_Has[m_iSelAddr].dwTxValue);
#endif
	BYTE* temp;
	int state;
	BYTE* flag;
	RxCheck_flag = TRUE;

	temp = (BYTE *)(ntohl(m_Has[m_iSelAddr].dwTxValue));

	if (ConnectSocket != NULL)
	{
		if (m_iSelAddr < 8000)
			state = setDataFromRemote(ConnectSocket, m_dwEN673BaseAdr + (m_iSelAddr << 2), 4, WB0, &temp);
		else
		{
			state = WriteISP(m_iSelAddr, m_Has[m_iSelAddr].dwTxValue);
			int iCnt = 0;
			int iiCnt = 0;
			do{
				//Sleep(10);
				//ProcessWindowMessage();
				Wait(10);
				state = getDataFromRemote(ConnectSocket, tx_addr, 4, WBCOM, &flag);
				if (state < 0 | iCnt > RETRY)
				{
					RxCheck_flag = FALSE;
					break;
				}
				if ((((UINT32)flag & 0X0000ffff) == 0xd002) | iiCnt == RETRY)
				{
					iiCnt = 0;
					iCnt++;
					state = WriteISP(m_iSelAddr, m_Has[m_iSelAddr].dwTxValue);
				}
				iiCnt++;
			} while (((UINT32)flag & 0X0000ffff) != 0x2002);
		}
		if (state < 0 | !RxCheck_flag)
		{
			if (ConnectSocket)
			{
				NetClo(ConnectSocket);
				ConnectSocket = NULL;
			}

			if (StateSocket)
			{
				NetClo(StateSocket);
				StateSocket = NULL;
			}
			pRegDlg->EnableCtrl(FALSE);
			pRegDlg->m_Btn_Connect.SetIcon(IDI_DISCONNECT, NULL);
			AfxMessageBox(_T("Write Fail"));
		}
	}
	else
	{
		AfxMessageBox(_T("Not Connect"));
	}

	// Check Feedback
	if (pRegDlg->m_Chk_FeedBackWrite.GetCheck())
		pRegDlg->DispRxReg(m_iSelAddr, HexStringOut(m_Has[m_iSelAddr].dwTxValue));
#endif
}


void CRegCtrlDlg::OnDeltaposSpinWrite(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	m_Btn_RegWrite.SetFocus();
	if (!m_iHasNum && !m_iMneNum) return;

	if (m_bEdit) return;

	HTREEITEM hItem = NULL;
	HTREEITEM hParentItem = m_List_Reg.GetParentItem(m_hSelItem);

	if (hParentItem)
		m_hSelItem = hParentItem;

	// Down ( �ּ� ���� )
	if (pNMUpDown->iDelta > 0)
	{
		hItem = m_List_Reg.GetNextItem(m_hSelItem);
	}
	// Up ( �ּ� ���� )
	else if (pNMUpDown->iDelta < 0)
	{
		if (hParentItem)
			hItem = m_hSelItem;
		else
			hItem = m_List_Reg.GetPrevSiblingItem(m_hSelItem);
	}

	if (hItem == NULL) return;

	m_List_Reg.SelectItem(hItem, m_iSelCol);
	m_List_Reg.EnsureVisible(hItem, m_iSelCol);

	if(!ConnectSocket)	return;
	if (m_List_Reg.GetParentItem(m_List_Reg.GetSelectedItem()) != NULL) return;
	
	CString strValue = m_List_Reg.GetItemText(m_hSelItem, TC_TX);
	DispTxReg(m_iSelAddr, strValue);

	// Reg
	// Display Tx
	pRegDlg->DispTxReg(m_iSelAddr, HexStringOut(m_Has[m_iSelAddr].dwTxValue));

	BYTE* temp;
	int state;
	BYTE* flag;
	RxCheck_flag = TRUE;

	temp = (BYTE *)(ntohl(m_Has[m_iSelAddr].dwTxValue));

	if (m_iSelAddr < 8000)
		state = setDataFromRemote(ConnectSocket, m_dwEN673BaseAdr + (m_iSelAddr << 2), 4, WB0, &temp);
	else
	{
		state = WriteISP(m_iSelAddr, m_Has[m_iSelAddr].dwTxValue);
		int iCnt = 0;
		int iiCnt = 0;
		do{
			//Sleep(10);
			//ProcessWindowMessage();
			Wait(10);
			state = getDataFromRemote(ConnectSocket, tx_addr, 4, WBCOM, &flag);
			if (state < 0 | iCnt > RETRY)
			{
				RxCheck_flag = FALSE;
				break;
			}
			if ((((UINT32)flag & 0X0000ffff) == 0xd002) | iiCnt == RETRY)
			{
				iiCnt = 0;
				iCnt++;
				state = WriteISP(m_iSelAddr, m_Has[m_iSelAddr].dwTxValue);
			}
			iiCnt++;

		} while (((UINT32)flag & 0X0000ffff) != 0x2002);
	}

	if (state < 0 | !RxCheck_flag)
	{
		if (ConnectSocket)
		{
			NetClo(ConnectSocket);
			ConnectSocket = NULL;
		}

		if (StateSocket)
		{
			NetClo(StateSocket);
			StateSocket = NULL;
		}
		pRegDlg->EnableCtrl(FALSE);
		pRegDlg->m_Btn_Connect.SetIcon(IDI_DISCONNECT, NULL);
		AfxMessageBox(_T("Write Fail"));
	}

	// Check Feedback
	if (pRegDlg->m_Chk_FeedBackWrite.GetCheck())
		pRegDlg->DispRxReg(m_iSelAddr, m_Has[m_iSelAddr].dwTxValue);

	*pResult = 0;
}


void CRegCtrlDlg::OnBnClickedButtonRegwriteall()
{
	int i = 0;
	int iStart = 0;
	int iEnd = 0;
	CString str = _T("");

#ifndef ISPtoJTAG
	// 1. Uart
	// ���� Ȯ��
	if (!pComPort->m_bConnected) return;
#else
	// 1. JTAG
	// ���� Ȯ��
	//	if (!pJTAG->m_bJTAGOpen) return;
	if (!ConnectSocket) return;
#endif	

	// ���� ����
	if (bRunWriteAllThread) {
		m_bStopAll = TRUE;
		return;
	}

	// 2. ���� Ȯ��
	// Start : Hex���� Ȯ��
	m_Cbo_WriteStart.GetWindowTextW(str);
	if (!CheckHex(str))
	{
		AfxMessageBox(_T("Write start value is wrong"));
		::SetFocus(m_Cbo_WriteStart.m_hWnd);
		return;
	}
	iStart = HexToDec(str);

	// End
	m_Cbo_WriteEnd.GetWindowTextW(str);
	if (!CheckHex(str))
	{
		AfxMessageBox(_T("Write end value is wrong."));
		::SetFocus(m_Cbo_WriteEnd.m_hWnd);
		return;
	}
	iEnd = HexToDec(str);

	// Start�� m_iAddr���� ū�� Ȯ��
	if (iStart > m_iAddr)
	{
		str.Format(_T("Write start value is too big. (Max : 0x%x)"), m_iAddr);
		AfxMessageBox(str);
		return;
	}

	// End�� m_iAddr���� ū�� Ȯ��
	if (iEnd > m_iAddr)
	{
		str.Format(_T("Write end value is too big. (Max : 0x%x)"), m_iAddr);
		AfxMessageBox(str);
		return;
	}

	// iStart�� iEnd���� ū�� Ȯ��
	if (iStart>iEnd)
	{
		AfxMessageBox(_T("Start address is too big than End address."));
		return;
	}

	// ���� ������ ����
	for (i = iStart; i <= iEnd; i++)
	{
		str = m_List_Reg.GetItemText(m_hItem[i], TC_ADDR);
		if (str != _T(""))
		{
			m_List_Reg.SelectItem(m_hItem[i]);
			break;
		}
	}

	StartWriteAllThread();
}

void CRegCtrlDlg::StartWriteAllThread()
{
	// ====================================================================================================
	// Run Loading Thread
	g_pLoadingThread = AfxBeginThread(LoadingThread, pRegDlg->GetSafeHwnd(), THREAD_PRIORITY_NORMAL);

	// ====================================================================================================
	// Write All Thread
	g_pRegWriteAllThread = AfxBeginThread(WriteAllThread, pRegDlg->GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
}

// ====================================================================================================
// WriteAllThread
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
UINT WriteAllThread(LPVOID pParam)
{
	//Sleep(100);
	Wait(100);

	bRunWriteAllThread = TRUE;

	int i = 0;
	int iCnt = 0;
	DWORD dwData = 0;
	CString	str = _T("");

	// ----------------------------------------------------------------------------------------------------
	// On Stop
	pRegDlg->m_Btn_RegWriteAll.SetWindowTextW(_T("Stop"));
	pRegDlg->m_Btn_RegWriteAll.EnableWindow(TRUE);

	// ----------------------------------------------------------------------------------------------------
	// Set Area
	// Start Address
	pRegDlg->m_Cbo_WriteStart.GetWindowTextW(str);
	int iStartAddr = HexToDec(str);

	// End Address
	pRegDlg->m_Cbo_WriteEnd.GetWindowTextW(str);
	int iEndAddr = HexToDec(str);

	// ----------------------------------------------------------------------------------------------------
	// Initialize
	g_iRxAddress = -1;

	// ----------------------------------------------------------------------------------------------------
	// Read
#if 1
	// Start
	int iAddr = 0;
	HTREEITEM hItem = pRegDlg->m_hSelItem;
	HTREEITEM hItemTemp = pRegDlg->m_hItem[iStartAddr];

	while (1)
	{
		if (pRegDlg->m_bStopAll) break; // Stop Read All
		if (hItemTemp == NULL) break; // Check HTREEITEM
		iAddr = HexToDec(pRegDlg->m_List_Reg.GetItemText(hItemTemp, TC_ADDR));
		if (iAddr > iEndAddr) break; // Check Address

		hItem = hItemTemp;	// Check Complate
		pRegDlg->m_List_Reg.EnsureVisible(hItem);	// Move TreeList
		pRegDlg->m_List_Reg.SelectItem(hItem);		// TreeList Select

		CString strValue = pRegDlg->m_List_Reg.GetItemText(hItem, TC_TX);
		pRegDlg->DispTxReg(iAddr, strValue);

#ifndef ISPtoJTAG
		pUART->WriteISP(iAddr, pRegDlg->m_Has[iAddr].dwTxValue); // Send Data
#else
#if 0
		CString strMsg = _T("");
		// Initial JTAG
		pJTAG->JTAGInitial(strMsg);

		UINT32 state;
		state = EN673_REG_WRITE(UINT32(m_dwEN673BaseAdr) + UINT32(iAddr << 2), (UINT32)pRegDlg->m_Has[iAddr].dwTxValue);
#endif
		BYTE* temp;
		int state;
		BYTE* flag;
		pRegDlg->RxCheck_flag = TRUE;

		temp = (BYTE *)(ntohl(pRegDlg->m_Has[iAddr].dwTxValue));

		if (ConnectSocket != NULL)
		{
			if (iAddr < 8000)
				state = setDataFromRemote(ConnectSocket, m_dwEN673BaseAdr + (iAddr << 2), 4, WB0, &temp);
			else
			{
				state = WriteISP(iAddr, pRegDlg->m_Has[iAddr].dwTxValue);
				int iCnt = 0;
				int iiCnt = 0;
				do{
					if (pRegDlg->m_bStopAll) break; // Stop Read All
					//Sleep(10);
					//ProcessWindowMessage();
					Wait(10);
					state = getDataFromRemote(ConnectSocket, tx_addr, 4, WBCOM, &flag);
					if (state < 0 | iCnt > RETRY)
					{
						pRegDlg->RxCheck_flag = FALSE;
						break;
					}
					if ((((UINT32)flag & 0X0000ffff) == 0xd002) | iiCnt == RETRY)
					{
						iiCnt = 0;
						iCnt++;
						state = WriteISP(iAddr, pRegDlg->m_Has[iAddr].dwTxValue);
					}
					iiCnt++;
				} while (((UINT32)flag & 0X0000ffff) != 0x2002);
			}
			if (state < 0 | !pRegDlg->RxCheck_flag)
			{
				if (ConnectSocket)
				{
					NetClo(ConnectSocket);
					ConnectSocket = NULL;
				}

				if (StateSocket)
				{
					NetClo(StateSocket);
					StateSocket = NULL;
				}
				pRegDlg->EnableCtrl(FALSE);
				pRegDlg->m_Btn_Connect.SetIcon(IDI_DISCONNECT, NULL);
				AfxMessageBox(_T("Write Fail"));
			}
		}
		else
		{
			AfxMessageBox(_T("Not Connect"));
			goto ENDWRITEALL;
		}
#endif
		iCnt = 0;

		while (iAddr > g_iRxAddress) // Wait
		{
			if (pRegDlg->m_bStopAll) break; // Stop Read All
			iCnt++;
			if (iCnt == 1000)
			{
				str.Format(_T("Fail Write Value (Address : %x)"), iAddr);
				AfxMessageBox(str);

				pRegDlg->m_List_Reg.SelectItem(hItem);
				pRegDlg->m_List_Reg.EnsureVisible(hItem);
				goto ENDWRITEALL;
			}
			//Sleep(1);
			//ProcessWindowMessage();
			Wait(1);

#ifndef ISPtoJTAG
#else
			if (state == 0)
				g_iRxAddress = iAddr;
#endif
		}

#ifndef ISPtoJTAG
#else
		// Check Feedback
		if (pRegDlg->m_Chk_FeedBackWrite.GetCheck())
			pRegDlg->DispRxReg(iAddr, HexStringOut(pRegDlg->m_Has[iAddr].dwTxValue));
#endif

		if (iAddr >= iEndAddr) break; // Check End Address

		hItemTemp = pRegDlg->m_List_Reg.GetNextItem(hItem); // Next HTREEITEM

		//Sleep(0);
		//ProcessWindowMessage();
		Wait(0);
	}

	pRegDlg->m_List_Reg.SelectItem(hItem);
	pRegDlg->m_List_Reg.EnsureVisible(hItem);

#else
	for (i = iStartAddr; i <= iEndAddr; i++)
	{
		// Stop Write All
		if (pRegDlg->m_bStopAll)
		{
			pRegDlg->m_List_Reg.SelectItem(pRegDlg->m_hItem[i]);
			pRegDlg->m_List_Reg.EnsureVisible(pRegDlg->m_hItem[i]);
			goto ENDWRITEALL;
		}

		if (pRegDlg->m_iAddr <= i) break;

		// Select Item
		pRegDlg->m_List_Reg.EnsureVisible(pRegDlg->m_hItem[i]);

		// SendData
		pUART->WriteISP(i, pRegDlg->m_Has[i].dwTxValue);

		// Wait
		iCnt = 0;
		while (i > g_iRxAddress)
		{
			iCnt++;
			if (iCnt == 1000)
			{
				str.Format(_T("Fail Write Value (Address : %x)"), i);
				AfxMessageBox(str);

				pRegDlg->m_List_Reg.SelectItem(pRegDlg->m_hItem[i]);
				pRegDlg->m_List_Reg.EnsureVisible(pRegDlg->m_hItem[i]);
				goto ENDWRITEALL;
			}
			Sleep(1);
		}

		Sleep(0);
	}

	pRegDlg->m_List_Reg.SelectItem(pRegDlg->m_hItem[iEndAddr]);
	pRegDlg->m_List_Reg.EnsureVisible(pRegDlg->m_hItem[iEndAddr]);
#endif

	// ----------------------------------------------------------------------------------------------------
ENDWRITEALL:
	pRegDlg->m_Btn_RegWriteAll.SetWindowTextW(_T("Write All"));
	pRegDlg->m_bStopAll = FALSE;

	bRunWriteAllThread = FALSE;
	pRegDlg->m_bLoading = FALSE;

	//::CloseHandle(g_pRegWriteAllThread->m_hThread);
	return 0L;
}


// ====================================================================================================
// CRegCtrlDlg :: DispTxReg
// ----------------------------------------------------------------------------------------------------
/*
iAddr  : Address
strTx : _T("") - m_Has[iAddr].strTx�� ���� �״�� �����.
else	  - ���� strTx�� �����. (m_Has[iAddr].strTx�� ���뵵 ������)

1. ���� strTx�� Tree�� ���
- m_hItem[iAddr]�� TC_TX
2. ���� ���� ��...
- m_Has[iAddr].strTx
- m_strSelTx (Update�ϴ� Tx�� ������ Tx�� ��츸.)
- m_strBeforeTx
- m_bUpdateHas = TRUE
3. Set Bit Button
*/
// ====================================================================================================
void CRegCtrlDlg::DispTxReg(int iAddr)
{
	DispTxReg(iAddr, m_Has[iAddr].dwTxValue);
}

void CRegCtrlDlg::DispTxReg(int iAddr, CString strTxValue)
{
	DispTxReg(iAddr, HexToDec(strTxValue));
}

void CRegCtrlDlg::DispTxReg(int iAddr, DWORD dwTxValue)
{
	if (m_hItem == NULL) return;
	if ((m_Has == NULL) && (m_Mne == NULL)) return;

	int i = 0;
	int iStart = 0;
	int iEnd = 0;

	CString strTxValue = _T("");
	CString strOldTx = m_List_Reg.GetItemText(m_hItem[iAddr], TC_TX);

	// (SET) m_Has[iAddr].dwTxValue
	m_Has[iAddr].dwTxValue = dwTxValue;
	strTxValue.Format(_T("%x"), dwTxValue);

	// (SET) m_hItem[iAddr] Tx
	m_List_Reg.SetItemText(m_hItem[iAddr], strTxValue, TC_TX);

	// (SET) ChileItem Tx
	HTREEITEM hChildItem = m_List_Reg.GetChildItem(m_hItem[iAddr]);

	if (m_iMneNum)
	{
		for (i = 0; i < m_Mne[iAddr].iBitNum; i++)
		{
			iStart = m_Mne[iAddr].iStart[i];
			iEnd = m_Mne[iAddr].iEnd[i];
			if (!INMIDDLE(iStart, 0, 31) || !INMIDDLE(iEnd, 0, 31)) continue;

			strTxValue.Format(_T("%x"), SliceVal(dwTxValue, iStart, iEnd));

			if (!hChildItem) break;
			m_List_Reg.SetItemText(hChildItem, strTxValue, TC_TX);

			hChildItem = m_List_Reg.GetNextSiblingItem(hChildItem);
		}
	}

	// (SET) m_strSelTx, m_strBeforeTx
	if (m_iSelAddr == iAddr)
	{
		if (m_bLabelEdit)
			m_bLabelEdit = FALSE; // EndLabelEdit���� m_strBeforeTx�� ������.
		else
			m_strBeforeTx = strOldTx;

		m_strSelTx = m_List_Reg.GetItemText(m_hSelItem, TC_TX);
	}

	SetBitButton();

	m_bUpdateHas = TRUE;
}

// ====================================================================================================
// CRegCtrlDlg :: DispRxReg	
// ----------------------------------------------------------------------------------------------------
/*
iAddr  : Address
strRx : ���� strRx�� ����� m_hItem�� TC_RX�� ���.
*/
// ====================================================================================================
void CRegCtrlDlg::DispRxReg(int iAddr, CString strRxValue)
{
	DispRxReg(iAddr, HexToDec(strRxValue));
}

// ====================================================================================================
// CRegCtrlDlg :: DispRxReg	
// ----------------------------------------------------------------------------------------------------
/*
iAddr  : Address
strRx : ���� strRx�� ����� m_hItem�� TC_RX�� ���.
*/
// ====================================================================================================
void CRegCtrlDlg::DispRxReg(int iAddr, DWORD dwRxValue)
{
	if (m_hItem == NULL) return;
	if ((m_Has == NULL) && (m_Mne == NULL)) return;

	int i = 0;
	int iStart = 0;
	int iEnd = 0;
	int iRx = 0;
	CString strRxValue = _T("");

	strRxValue.Format(_T("%x"), dwRxValue);

	// (SET) m_hItem[iAddr] Rx
	m_List_Reg.SetItemText(m_hItem[iAddr], strRxValue, TC_RX);

	// (SET) ChildItem Rx
	HTREEITEM hChildItem = m_List_Reg.GetChildItem(m_hItem[iAddr]);
	if (m_iMneNum)
	{
		for (i = 0; i < m_Mne[iAddr].iBitNum; i++)
		{
			iStart = m_Mne[iAddr].iStart[i];
			iEnd = m_Mne[iAddr].iEnd[i];

			if (!INMIDDLE(iStart, 0, 31) || !INMIDDLE(iEnd, 0, 31)) continue;

			iRx = SliceVal(dwRxValue, iStart, iEnd);
			strRxValue.Format(_T("%x"), iRx);

			if (!hChildItem) break;
			m_List_Reg.SetItemText(hChildItem, strRxValue, TC_RX);

			hChildItem = m_List_Reg.GetNextSiblingItem(hChildItem);
		}
	}
}

// ====================================================================================================
// CRegCtrlDlg :: EnableCtrl
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CRegCtrlDlg::EnableCtrl(BOOL bEnable)
{
	int i = 0;
	BOOL b = 0;
	BOOL bFileOpen = (m_iHasNum > 0) || (m_iMneNum > 0);

	if (!bEnable)
		b = FALSE;
	else
	{
		if (!ConnectSocket) {
			b = FALSE;
		}
		else {
			if (bFileOpen)	b = TRUE;
			else			b = FALSE;
		}
		if (bFileOpen)	b = TRUE;
		else			b = FALSE;
	}

	// Read
	m_Btn_RegRead.EnableWindow(b);
	m_Spin_Read.EnableWindow(b);
	m_Cbo_ReadStart.EnableWindow(b);
	m_Cbo_ReadEnd.EnableWindow(b);
	m_Btn_RegReadAll.EnableWindow(b);

	// Write
	m_Btn_RegWrite.EnableWindow(b);
	m_Spin_Write.EnableWindow(b);
	m_Cbo_WriteStart.EnableWindow(b);
	m_Cbo_WriteEnd.EnableWindow(b);
	m_Btn_RegWriteAll.EnableWindow(b);
	m_Spin_Value.EnableWindow(b);

	// FeedBack
	m_Chk_FeedBackRead.EnableWindow(b);
	m_Chk_FeedBackWrite.EnableWindow(b);

	// Bit
	if (bEnable){
		SetBitButton();
	}
	else {
		for (i = 0; i < 32; i++)
			EnableBtnBit(i, bEnable && bFileOpen);
	}

	// File
	if (bRunLoadingThread)
	{
		m_Btn_OpenHas.EnableWindow(bEnable);
		m_Btn_OpenMne.EnableWindow(bEnable);
		m_Btn_SaveHas.EnableWindow(bEnable && bFileOpen);

		// Search
		m_Cbo_Search.EnableWindow(bEnable);
		m_Cbo_SearchOption.EnableWindow(bEnable);
		EnableComboSearchCtrl(bEnable);
		
		m_List_Reg.EnableWindow(bEnable);
	}
	else
	{
		m_Btn_OpenHas.EnableWindow(TRUE);
		m_Btn_OpenMne.EnableWindow(TRUE);
		m_Btn_SaveHas.EnableWindow(TRUE);

		// Search
		m_Cbo_Search.EnableWindow(TRUE);
		m_Cbo_SearchOption.EnableWindow(TRUE);
		EnableComboSearchCtrl(TRUE);

		m_List_Reg.EnableWindow(TRUE);
	}

	// etc
	m_Btn_ClearRx.EnableWindow(bEnable && bFileOpen);
}

// ====================================================================================================
// CRegCtrlDlg::OnBnClickedButtonOpendes
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CRegCtrlDlg::OnBnClickedButtonOpendes()
{
	if (!m_iMneNum)
	{
		AfxMessageBox(_T("Please open Mnemonic file."));
		return;
	}

	int iMsgBoxReturn = 0;
	CString strDesFile = _T("");
	CString strDefExt = _T("des");
	CString strFilter = _T("Description File(*.des)|*.des||");

	m_Edit_DesFile.GetWindowTextW(strDesFile);

	// ----------------------------------------------------------------------------------------------------
	// Save Des File
	if (m_bUpdateDes)
	{
		iMsgBoxReturn = AfxMessageBox(_T("Description file is modified. Do you want to save?"), MB_YESNOCANCEL);
		if (iMsgBoxReturn == IDCANCEL)
		{
			return;
		}
		else if (iMsgBoxReturn == IDYES)
		{
			if (ShowSaveFileDlg(&strDesFile, strDefExt, strFilter, this))
				SaveDes(strDesFile);
		}
	}

	// Open Dialog
	if (!ShowOpenFileDlg(&strDesFile, strDefExt, strFilter, this))
		return;

	// Open
	if (!OpenDes(strDesFile))
		AfxMessageBox(_T("Fail file open."));

	// ----------------------------------------------------------------------------------------------------
	// Display Description Infomation
	DispDes();
}

// ====================================================================================================
// CRegDlg::OpenDes
// ----------------------------------------------------------------------------------------------------
// Mne�� �����ִ� ���¿����� �� �� ����.
// �Ҵ�Ǵ� ������ m_iMneNum ��ŭ.
// ====================================================================================================
BOOL CRegCtrlDlg::OpenDes(CString strPath)
{
	int i = 0, j = 0, k = 0;

	int	iNum = 0;
	int	iStg = 0;
	int	iAddr = 0; // ������ HexToDec(strAddr) �Ǿ��ִ°� �˴� �߰�(??)
	BOOL bReturn = FALSE;
	CString str = _T("");
	CString strNum = _T("");
	CString strAddr = _T("");
	CString strName = _T("");
	CString strDes = _T("");
	CStdioFile desFile;
	HTREEITEM hChildItem = NULL;

	// ----------------------------------------------------------------------------------------------------
	// 1. ������� ����, �ʱ�ȭ
	m_bOpenDes = TRUE; // �ٸ���... m_bOpenHas�� m_bOpenMne�� InitTree�� ���̴µ�... �̰� ���� �Ⱦ�
	if (m_Des != NULL)
	{
		for (i = 0; i < m_iDesNum; i++)
			delete[] m_Des[i];
		delete[] m_Des;

		m_Des = NULL;
	}

	// ----------------------------------------------------------------------------------------------------
	// 2. m_Des ����
	// 1) Mne File Ȯ��
	if (!m_iMneNum)
	{
		bReturn = FALSE;
		goto ENDDES;
	}

	// 2) �Ҵ�, �ʱ�ȭ
	m_iDesNum = m_iMneNum;
	m_Des = new CString*[m_iDesNum];
	for (i = 0; i< m_iDesNum; i++)
	{
		m_Des[i] = new CString[32];
	}

	// 3) Open File
	if (!desFile.Open(strPath, CFile::modeRead))
	{
		bReturn = FALSE;
		goto ENDDES;
	}

	// 4) m_Des�� ������ ����

	/*
	���� ���

	//	ADDR	NAME
	::
	DES(������)
	::

	*/
	desFile.SeekToBegin();

	while (desFile.ReadString(str))
	{
		switch (iStg)
		{
		case 0:
			if (str.Find(_T("//")) != 0) break;

			// �ʱ�ȭ 
			strAddr = _T("");
			strName = _T("");
			strDes = _T("");

			// Addr �и�, Ȯ��
			str = str.Right(str.GetLength() - 2);
			str = str.TrimLeft();
			k = str.FindOneOf(_T("\t "));
			if (k == -1) k = str.GetLength();

			strAddr = str.Left(k);
			if (!CheckHex(strAddr))
			{
				bReturn = FALSE;
				goto ENDDES;
			}
			else
			{
				if (m_Mne[HexToDec(strAddr)].strLine == _T("")) break;
				if ((int)HexToDec(strAddr) >= m_iDesNum) break;
			}

			// Name �и�, Ȯ��
			str = str.Right(str.GetLength() - k);
			str = str.TrimLeft();
			k = str.FindOneOf(_T("\t "));
			if (k == -1) k = str.GetLength();

			strName = str.Left(k);
			if (strName == _T("")) break;

			// Name ��ġ Ȯ��
			iNum = -1;
			hChildItem = m_List_Reg.GetChildItem(m_hItem[HexToDec(strAddr)]);
			for (i = 0; i < m_Mne[HexToDec(strAddr)].iBitNum; i++)
			{
				if (!hChildItem) break;

				str = m_List_Reg.GetItemText(hChildItem, TC_NAME);
				if (str.Find(strName) == 0)
				{
					iNum = i;
					break;
				}

				hChildItem = m_List_Reg.GetNextSiblingItem(m_hItem[HexToDec(strAddr)]);
			}

			if (iNum != -1) iStg = 1;

			break;

			// 1. ���� �ݷ�
		case 1:
			i = str.Find(_T("::"));
			if (i == 0)
				iStg = 2;

			break;

			// 2, 3 Description ����, ���� �ݷ�
		case 2:
			i = str.Find(_T("::"));
			if (i == 0)
			{
				iStg = 0;

				if (HexToDec(strAddr) < m_iMneNum && INMIDDLE(iNum, 0, 31))
					m_Des[HexToDec(strAddr)][iNum] = strDes;

				break;
			}
			strDes = str;
			iStg = 3;

			break;

		case 3:
			i = str.Find(_T("::"));
			if (i == 0)
			{
				iStg = 0;
				if (HexToDec(strAddr) < m_iMneNum && INMIDDLE(iNum, 0, 31))
					m_Des[HexToDec(strAddr)][iNum] = strDes;

				break;
			}
			strDes = strDes + _T("\r\n") + str;

			break;

		}
	}
	desFile.Close();

	m_Edit_DesFile.SetWindowTextW(strPath);
	bReturn = TRUE;

	// ----------------------------------------------------------------------------------------------------
	// 3. Open Des ��
ENDDES:
	if (!bReturn)
	{
		m_Edit_DesFile.SetWindowTextW(_T(""));

		if (m_iMneNum)
		{
			for (i = 0; i < m_iDesNum; i++)
			{
				for (j = 0; j < 32; j++)
				{
					m_Des[i][j] = _T("");
				}
			}
		}
		else
		{
			if (m_Des != NULL)
			{
				for (i = 0; i < m_iDesNum; i++)
					delete[] m_Des[i];
				delete[] m_Des;

				m_Des = NULL;
			}
			m_iDesNum = 0;
		}
	}

	m_bUpdateDes = FALSE;

	return bReturn;
}

// ====================================================================================================
// CRegDlg :: DispDes
// ----------------------------------------------------------------------------------------------------
// m_hSelItem �������� Description ǥ��.
// ====================================================================================================
void CRegCtrlDlg::DispDes()
{
	int i = 0;

#if 1
	// Description ǥ��
	if (m_hSelItem == NULL || m_Mne == NULL || m_Des == NULL)
	{
		m_Edit_Description.SetWindowTextW(_T(""));
		m_Edit_Description.EnableWindow(FALSE);
	}
	else
	{
		HTREEITEM hParentItem = m_List_Reg.GetParentItem(m_hSelItem);

		if ((hParentItem != NULL) && (m_iSelAddr < m_iDesNum)) // �ڽ� Ʈ��
		{
			i = GetChildItemNum(hParentItem, m_hSelItem);

			if (INMIDDLE(i, 0, 31))
				m_Edit_Description.SetWindowTextW(m_Des[m_iSelAddr][i]);

			m_Edit_Description.EnableWindow(TRUE);
		}
		else if ((hParentItem == NULL) && (m_Mne[m_iSelAddr].iBitNum == 1)) // �θ� Ʈ��
		{
			m_Edit_Description.SetWindowTextW(m_Des[m_iSelAddr][0]);
			m_Edit_Description.EnableWindow(TRUE);
		}
		else
		{
			m_Edit_Description.SetWindowTextW(_T(""));
			m_Edit_Description.EnableWindow(FALSE);
		}
	}

#else

	if (m_hSelItem == NULL) return;
	HTREEITEM hParentItem = m_List_Reg.GetParentItem(m_hSelItem);

	// �ʱ�ȭ
	m_Edit_Description.SetWindowTextW(_T(""));

	// Mne ������ ��Ȱ��ȭ
	if ((m_Des == NULL) || (m_Mne == NULL))
	{
		m_Edit_Description.EnableWindow(FALSE);
		return;
	}

	// Description ǥ��
	if ((hParentItem != NULL) && (m_Des != NULL) && (m_iSelAddr < m_iDesNum))
		// m_hSelItem�� �ڽ�Ʈ���̸鼭, Des Data�� �ְ�, ������ Ʈ���� Addr�� DesFile Data �� �������� ���� ��.
	{
		i = GetChildItemNum(hParentItem, m_hSelItem);

		if (INMIDDLE(i, 0, 31))
			m_Edit_Description.SetWindowTextW(m_Des[m_iSelAddr][i]);

		m_Edit_Description.EnableWindow(TRUE);
	}
	else if (hParentItem == NULL && (m_Mne[m_iSelAddr].iBitNum == 1))
	{
		m_Edit_Description.SetWindowTextW(m_Des[m_iSelAddr][0]);
		m_Edit_Description.EnableWindow(TRUE);
	}
	else
	{
		m_Edit_Description.EnableWindow(FALSE);
	}

#endif
}


// ====================================================================================================
// CRegCtrlDlg :: OnBnClickedButtonSavedes
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CRegCtrlDlg::OnBnClickedButtonSavedes()
{
	CString strDesFile = _T("");
	CString strDefExt = _T("des");
	CString strFilter = _T("Description File(*.des)|*.des||");

	m_Edit_DesFile.GetWindowTextW(strDesFile);

	// Save Dialog
	if (!ShowSaveFileDlg(&strDesFile, strDefExt, strFilter, this))
		return;

	// Save
	if (!SaveDes(strDesFile))
	{
		CFileFind ffind;

		if (ffind.FindFile(strDesFile))
		{
			ffind.Close();
			DeleteFileW(strDesFile);
		}

		AfxMessageBox(_T("Save data does not existed."));
	}
	else
	{
		m_Edit_DesFile.SetWindowTextW(strDesFile);
	}

	m_bUpdateDes = FALSE;
}

// ====================================================================================================
// CRegCtrlDlg :: SaveDes
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
BOOL CRegCtrlDlg::SaveDes(CString strPath)
{
	int i = 0;
	int j = 0;
	int iFind = 0;
	BOOL bReturn = FALSE;
	CString str = _T("");
	CString strName = _T("");
	HTREEITEM hChildItem = NULL;

	if (m_iMneNum == 0) return bReturn;

	CStdioFile desFile;
	desFile.Open(strPath, CFile::modeCreate | CFile::modeWrite);

	for (i = 0; i < m_iDesNum; i++)
	{
		if (i > m_iMneNum) break;
		if (!m_hItem[i]) continue;

		hChildItem = m_List_Reg.GetChildItem(m_hItem[i]);

		for (j = 0; j < m_Mne[i].iBitNum; j++)
		{
			if (m_Des[i][j] == _T("")) continue;

			bReturn = TRUE;

			if (!hChildItem) break;
			strName = m_List_Reg.GetItemText(hChildItem, TC_NAME);

			hChildItem = m_List_Reg.GetNextSiblingItem(hChildItem);

			// [���� ����
			iFind = strName.Find('[');
			if (iFind != -1)
				strName.Left(strName.GetLength() - iFind);

			str.Format(_T("//\t%x\t%s"), i, strName);
			desFile.WriteString(str);
			desFile.WriteString(_T("\n::\n"));
			desFile.WriteString(m_Des[i][j]);
			desFile.WriteString(_T("\n::\n\n"));
		}
	}

	desFile.Close();

	return bReturn;
}

// ====================================================================================================
// CRegCtrlDlg::OnEnChangeEditDescription
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CRegCtrlDlg::OnEnChangeEditDescription()
{
	if ((m_Des == NULL) || (m_hSelItem == NULL)) return;

	int iNum = 0;
	HTREEITEM hParentItem = m_List_Reg.GetParentItem(m_hSelItem);

	if (hParentItem == NULL)
	{
		if (m_Mne[m_iSelAddr].iBitNum != 1) return;
		iNum = 0;
	}
	else
	{
		iNum = GetChildItemNum(hParentItem, m_hSelItem);
		if (iNum == -1) return;
	}

	CString str = _T("");
	m_Edit_Description.GetWindowTextW(str);

	m_Des[m_iSelAddr][iNum] = str;

	m_bUpdateDes = TRUE;
}

// ====================================================================================================
// CRegCtrlDlg::StartDispRegInfoThread
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CRegCtrlDlg::StartDispRegInfoThread()
{
	// ====================================================================================================
	// Run Loading Thread
	g_pLoadingThread = AfxBeginThread(LoadingThread, pRegDlg->GetSafeHwnd(), THREAD_PRIORITY_NORMAL);

	// ====================================================================================================
	// DispRegInfo Thread
	g_pDispRegInfoThread = AfxBeginThread(DispRegInfoThread, pRegDlg->GetSafeHwnd(), THREAD_PRIORITY_NORMAL);

}

// ====================================================================================================
// DispRegInfoThread
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
UINT DispRegInfoThread(LPVOID pParam)
{
	// �� �Լ� ������ ��κ��� ECMDlg.cpp�� InitRegDlgThread�� ���ٰ� ����
	// �Ŀ� �� ���� �����Ǵ� ������ �����Ѵٸ� �װ��� ���� Ȯ���ؾ� �� �ʿ伺�� ����.

	// ----------------------------------------------------------------------------------------------------
	// 1. On Thread Flag
	bRunDispRegInfoThread = TRUE;

	// ----------------------------------------------------------------------------------------------------
	// 2. DispRegInfo
	pRegDlg->DispRegInfo();

	// ----------------------------------------------------------------------------------------------------
	// 3. Off Thread Flag
	bRunDispRegInfoThread = FALSE;

	// 4. End Loading
	pRegDlg->m_bLoading = FALSE;

	return TRUE;
}

// ====================================================================================================
// LoadingThread
// ----------------------------------------------------------------------------------------------------
// ��Ʈ�� ��Ȱ��ȭ �Ŀ� �ε� �̹��� ���
// ====================================================================================================
UINT LoadingThread(LPVOID pParam)
{
	sendMsg(ConnectSocket, "rem_hold ");

	int i = 0;

	// ----------------------------------------------------------------------------------------------------
	// 1. �÷��� ����
	bRunLoadingThread = TRUE;
	pRegDlg->m_bLoading = TRUE;

	// ----------------------------------------------------------------------------------------------------
	// 2. ��Ʈ�� ��Ȱ��ȭ
//	GlobalEnableCtrl(FALSE);
	pRegDlg->EnableCtrl(FALSE);
	pRegDlg->m_Btn_Close.EnableWindow(FALSE);

	// ----------------------------------------------------------------------------------------------------
	// 3. �ε� �̹��� ���
	if (pRegDlg->m_PicLoading.Load(MAKEINTRESOURCE(IDR_LOADING), _T("GIF")))
	{
		pRegDlg->m_PicLoading.ShowWindow(SW_SHOW);
		pRegDlg->m_PicLoading.Draw();
	}

	// ----------------------------------------------------------------------------------------------------
	// 4. ���
	while (pRegDlg->m_bLoading) { 
		//Sleep(50); 
		//ProcessWindowMessage();
		Wait(50);
	}

	// ----------------------------------------------------------------------------------------------------
	// 5. �ε� �̹��� ����
	pRegDlg->m_PicLoading.Stop();
	pRegDlg->m_PicLoading.ShowWindow(SW_HIDE);

	// ----------------------------------------------------------------------------------------------------
	// 6. ��Ʈ�� Ȱ��ȭ
//	GlobalEnableCtrl(TRUE);
	pRegDlg->EnableCtrl(TRUE);
	pRegDlg->m_Btn_Close.EnableWindow(TRUE);

	// ----------------------------------------------------------------------------------------------------
	// 7. �÷��� ����
	bRunLoadingThread = FALSE;

	sendMsg(ConnectSocket, "rem_release ");
	return TRUE;
}

// ====================================================================================================
// CRegCtrlDlg::SaveValue
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CRegCtrlDlg::SaveValue()
{
	// Has, Mne, Des File
	CString strHasFile = _T("");
	CString strMneFile = _T("");
	CString strDesFile = _T("");

	m_Edit_HasFile.GetWindowTextW(strHasFile);
	m_Edit_MneFile.GetWindowTextW(strMneFile);
	m_Edit_DesFile.GetWindowTextW(strDesFile);

	WriteIni(SEC_REG, KEY_HASFILE, strHasFile);
	WriteIni(SEC_REG, KEY_MNEFILE, strMneFile);
	WriteIni(SEC_REG, KEY_DESFILE, strDesFile);

	// FeedBack
	WriteIni(SEC_REG, KEY_FDBACKREAD, m_Chk_FeedBackRead.GetCheck());
	WriteIni(SEC_REG, KEY_FDBACKWRITE, m_Chk_FeedBackWrite.GetCheck());

//	// Spin Control Option
//	WriteIni(SEC_REG, KEY_INVERSERW, (int)pECMDlg->m_bInverseRW);
}

// ====================================================================================================
// CRegCtrlDlg::OnDeltaposSpinValue(NMHDR *pNMHDR, LRESULT *pResult)
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CRegCtrlDlg::OnDeltaposSpinValue(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	m_Static_Txvalue.SetFocus();

	if ((m_hSelItem == NULL)) return;
	if ((m_Has == NULL) && (m_Mne == NULL)) return;

	if (m_bEdit) return;

	CString strValue = m_List_Reg.GetItemText(m_hSelItem, TC_TX);

	int i = 0;
	int iLen = 0;
	int iStart = 0;
	int iEnd = 0;
	DWORD64 dwValue = HexToDec(strValue);
	DWORD64 dwMax = 0;
	CString str = _T("");
	CString strBin = _T("");
	HTREEITEM hParentItem = m_List_Reg.GetParentItem(m_hSelItem);

	// 1. Max Value
	if (hParentItem == NULL) // Parent
	{
		dwMax = 0x100000000;
	}
	else // Child
	{
		i = GetChildItemNum(hParentItem, m_hSelItem);

		if (i<0) return;

		iStart = m_Mne[m_iSelAddr].iStart[i];
		iEnd = m_Mne[m_iSelAddr].iEnd[i];

		if (!INMIDDLE(iStart, 0, 31) || !INMIDDLE(iEnd, 0, 31)) return;

		dwMax = pow((double)2, (iStart - iEnd + 1));
	}

	// 2. �� ���
	if (pNMUpDown->iDelta < 0)
	{
		dwValue++;
		if (dwValue >= dwMax)
			dwValue = 0;
	}
	else if (pNMUpDown->iDelta > 0)
	{
		dwValue--;
		if (dwValue < 0)
			dwValue = dwMax;
	}

	strValue.Format(_T("%x"), dwValue);

	// 3. �� ����
	strBin = strValue;

	// Child Item�� ���
	if (hParentItem != NULL)
	{
		strValue = m_List_Reg.GetItemText(hParentItem, TC_TX);
		strBin = HexToBin(strBin);

		// Tx ����
		iLen = strBin.GetLength();
		if (iLen < (iStart - iEnd + 1))
		{
			for (i = 0; i < iStart - iEnd + 1 - iLen; i++)
			{
				strBin = _T("0") + strBin;
			}
		}
		else if (iLen >(iStart - iEnd + 1))
		{
			strBin = strBin.Right(iStart - iEnd + 1);
		}

		// ��ü Tx
		iLen = strValue.GetLength();
		if (iLen < 8)
		{
			for (i = iLen; i < 8; i++)
			{
				strValue = _T("0") + strValue;
			}
		}
		else if (iLen > 8)
		{
			strValue = strValue.Right(8);
		}
		strValue = HexToBin(strValue);

		strValue = strValue.Left(31 - iStart) + strBin + strValue.Right(iEnd);
		strValue.Format(_T("%x"), BinToDec(strValue));
	}

	// 4. Display Tx Value
	DispTxReg(m_iSelAddr, strValue);

#ifndef ISPtoJTAG
	// 5. Write
	if (pComPort->m_bConnected)
		pUART->WriteISP(m_iSelAddr, HexToDec(strValue));
#else
#if 0
	// 5. Write
	//	if (pJTAG->m_bJTAGOpen)
	CString strMsg = _T("");
	// Initial JTAG
	pJTAG->JTAGInitial(strMsg);

	EN673_REG_WRITE(UINT32(m_dwEN673BaseAdr) + UINT32(m_iSelAddr << 2), (UINT32)HexToDec(strValue));
#endif
	BYTE* temp;
	int state;
	BYTE* flag;
	RxCheck_flag = TRUE;
	
	temp = (BYTE *)(ntohl(m_Has[m_iSelAddr].dwTxValue));

	if (ConnectSocket != NULL)
	{
		if (m_iSelAddr < 8000)
			state = setDataFromRemote(ConnectSocket, m_dwEN673BaseAdr + (m_iSelAddr << 2), 4, WB0, &temp);
		else
		{
			state = WriteISP(m_iSelAddr, m_Has[m_iSelAddr].dwTxValue);
			int iCnt = 0;
			int iiCnt = 0;
			do{
				//Sleep(10);
				//ProcessWindowMessage();
				Wait(10);
				state = getDataFromRemote(ConnectSocket, tx_addr, 4, WBCOM, &flag);
				if (state < 0 | iCnt > RETRY)
				{
					RxCheck_flag = FALSE;
					break;
				}
				if ((((UINT32)flag & 0X0000ffff) == 0xd002) | iiCnt == RETRY)
				{
					iiCnt = 0;
					iCnt++;
					state = WriteISP(m_iSelAddr, m_Has[m_iSelAddr].dwTxValue);
				}
				iiCnt++;
			} while (((UINT32)flag & 0X0000ffff) != 0x2002);
		}

		if (state < 0 | !RxCheck_flag)
			AfxMessageBox(_T("Write Fail"));

		//Sleep(10);
		//ProcessWindowMessage();
		Wait(10);
	}
	else
	{
		AfxMessageBox(_T("Not Connect"));
	}

	// Check Feedback
	if (pRegDlg->m_Chk_FeedBackWrite.GetCheck())
		pRegDlg->DispRxReg(m_iSelAddr, HexStringOut(m_Has[m_iSelAddr].dwTxValue));

#endif

	// 6. Focus
	if (m_bPressedCtrl)
	{
		m_bPressedCtrl = FALSE;
		m_List_Reg.SetFocus();
	}

	if (!RxCheck_flag)
	{
		if (ConnectSocket)
		{
			NetClo(ConnectSocket);
			ConnectSocket = NULL;
		}

		if (StateSocket)
		{
			NetClo(StateSocket);
			StateSocket = NULL;
		}
		EnableCtrl(FALSE);
		m_Btn_Connect.SetIcon(IDI_DISCONNECT, NULL);
	}

	*pResult = 0;
}


// ====================================================================================================
// CRegCtrlDlg::OnCtrlZ()
// ----------------------------------------------------------------------------------------------------
// m_strBeforeTx ����
// ====================================================================================================
void CRegCtrlDlg::OnCtrlZ()
{
	if (m_strBeforeTx == _T("")) return;

	if (HexToDec(m_strBeforeTx) == m_Has[m_iSelAddr].dwTxValue) return;
	CString str = _T("");

	// Swap Tx
	str = m_strBeforeTx;

	m_strBeforeTx.Format(_T("%x"), m_Has[m_iSelAddr].dwTxValue);

	DispTxReg(m_iSelAddr, HexToDec(str));

#ifndef ISPtoJTAG
	// Write
	if (pComPort->m_bConnected)
	{
		pUART->WriteISP(m_iSelAddr, m_Has[m_iSelAddr].dwTxValue);
	}
#else
#if 0
	// Write
	CString strMsg = _T("");
	// Initial JTAG
	pJTAG->JTAGInitial(strMsg);

	EN673_REG_WRITE(UINT32(m_dwEN673BaseAdr) + UINT32(m_iSelAddr << 2), (UINT32)m_Has[m_iSelAddr].dwTxValue);
#endif

	BYTE* temp;
	int state;

	temp = (BYTE *)(ntohl(m_Has[m_iSelAddr].dwTxValue));

	if (ConnectSocket != NULL)
	{
		if (m_iSelAddr < 8000)
			state = setDataFromRemote(ConnectSocket, m_dwEN673BaseAdr + (m_iSelAddr << 2), 4, WB0, &temp);
		else
			state = WriteISP(m_iSelAddr, m_Has[m_iSelAddr].dwTxValue);

		if (state < 0)
		{
			ConnectSocket = NULL;
			pRegDlg->EnableCtrl(FALSE);
			pRegDlg->m_Btn_Connect.SetIcon(IDI_DISCONNECT, NULL);
			AfxMessageBox(_T("Read Fail"));
		}
	}
	else
	{
		AfxMessageBox(_T("Not Connect"));
	}

	// Check Feedback
	if (pRegDlg->m_Chk_FeedBackWrite.GetCheck())
		pRegDlg->DispRxReg(m_iSelAddr, m_Has[m_iSelAddr].dwTxValue);
#endif
}

// ====================================================================================================
// CRegCtrlDlg::GetChildItemNum
// ----------------------------------------------------------------------------------------------------
/*
return -1 -> ��ã��
*/
// ====================================================================================================
int CRegCtrlDlg::GetChildItemNum(HTREEITEM hParentItem, HTREEITEM hItem)
{
	if (hItem == NULL || hParentItem == NULL) return -1;

	int	i = 0;
	CString strAddr = m_List_Reg.GetItemText(hParentItem, TC_ADDR);
	if (!CheckHex(strAddr)) return -1;

	int iAddr = HexToDec(m_List_Reg.GetItemText(hParentItem, TC_ADDR));

	HTREEITEM hChildItem = m_List_Reg.GetChildItem(hParentItem);

	for (i = 0; i < m_Mne[iAddr].iBitNum; i++)
	{
		if (!hChildItem) return -1;

		if (hChildItem == hItem)
			return i;

		hChildItem = m_List_Reg.GetNextSiblingItem(hChildItem);
	}

	return -1;
}

// ====================================================================================================
// CRegCtrlDlg::GetNumChildItem
// ----------------------------------------------------------------------------------------------------
/*
return NULL -> ��ã��
*/
// ====================================================================================================
HTREEITEM CRegCtrlDlg::GetNumChildItem(HTREEITEM hParentItem, UINT iChildNum)
{
	if (!hParentItem) return NULL;

	HTREEITEM hChildItem = m_List_Reg.GetChildItem(hParentItem);
	if (!hChildItem) return NULL;

	UINT iAddr = HexToDec(m_List_Reg.GetItemText(hParentItem, TC_ADDR));

	for (UINT i = 0; i < m_Mne[iAddr].iBitNum; i++)
	{
		if (iChildNum == i) return hChildItem;

		hChildItem = m_List_Reg.GetNextSiblingItem(hChildItem);
		if (!hChildItem) return NULL;
	}

	return NULL;
}

// ====================================================================================================
// CRegCtrlDlg::SetBoldItem
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CRegCtrlDlg::SetBoldItem(HTREEITEM hItem, int iCol, BOOL bFlag)
{
	UINT iState = m_List_Reg.GetItemState(hItem, TVIS_BOLD, iCol);

	if (bFlag)
		iState |= TVIS_BOLD;
	else
		iState ^= TVIS_BOLD;

	m_List_Reg.SetItemState(hItem, iCol, iState, TVIS_BOLD);
}

// ====================================================================================================
// CRegCtrlDlg :: OnBnClickedButtonClearrx
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CRegCtrlDlg::OnBnClickedButtonClearrx()
{
	if (m_hItem == NULL) return;

	int i = 0;
	CString str = _T("");
	HTREEITEM hItem = m_List_Reg.GetFirstItem();

	for (i = 0; i < m_iAddr; i++)
	{
		if (m_Mne != NULL)
		{
			if (m_Mne[i].strLine == _T("")) continue;
		}

		DispRxReg(i, _T("0"));
	}
}

// ====================================================================================================
// CRegCtrlDlg :: OnBnClickedButtonNewdes
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CRegCtrlDlg::OnBnClickedButtonNewdes()
{
	int iMsgBoxReturn = 0;
	_TCHAR szFilter[] = _T("Description File(*.des)|*.des||");
	CString strDesFile = _T("");
	CFileFind ffind;

	// �������� ����?
	if (m_bUpdateDes == TRUE)
	{
		iMsgBoxReturn = AfxMessageBox(_T("Description File is modified. Do you want to save?"), MB_YESNOCANCEL);

		// CANCEL
		if (iMsgBoxReturn == IDCANCEL)
		{
			return;
		}
		// YES
		else if (iMsgBoxReturn == IDYES)
		{
			m_Edit_DesFile.GetWindowTextW(strDesFile);
			if (ffind.FindFile(strDesFile))
				ffind.Close();
			else
				strDesFile = _T("");

			CFileDialog FileDlg(FALSE, _T("des"), strDesFile, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);

			if (FileDlg.DoModal() == IDOK)
				pRegDlg->SaveDes(FileDlg.GetPathName());
		}

		m_bUpdateDes = FALSE;
	}

	strDesFile = _T("");

	OpenDes(strDesFile);
	DispDes();
}

// ====================================================================================================
// CRegDlg::SetSpinRange
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void CRegCtrlDlg::SetSpinRange()
{
#if 0
	if (pECMDlg->m_bInverseRW)
	{
		// �̷���(?) ���۹��. Ŭ���ϴ� ���⿡ ���� �������Ͱ� ����.
		m_Spin_Read.SetRange(0, 100);
		m_Spin_Write.SetRange(0, 100);
	}
	else
#endif
	{
		// �������� ���۹��. Ŭ���ϴ� ���⿡ ���� ĭ�� ������.
		m_Spin_Read.SetRange(100, 0);
		m_Spin_Write.SetRange(100, 0);
	}
}


void CRegCtrlDlg::OnBnClickedButtonConnect()
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


void CRegCtrlDlg::OnTimer(UINT_PTR nIDEvent)
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


void CRegCtrlDlg::Check_Timer_On()
{
	m_CheckTimerID = SetTimer(ID_CHECK_TIMER, Check_Time, NULL);
}

void CRegCtrlDlg::Check_Timer_Off()
{
	if (m_CheckTimerID)
	{
		if (this->GetSafeHwnd())
			KillTimer(m_CheckTimerID);
		m_CheckTimerID = 0;
	}
}

void CRegCtrlDlg::Connect_Timer_On()
{
	m_ConnectTimerID = SetTimer(ID_CONNECT_TIMER, Connect_Time, NULL);
}

void CRegCtrlDlg::Connect_Timer_Off()
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
				pRegDlg->EnableCtrl(TRUE);
				pRegDlg->m_Btn_Connect.SetIcon(IDI_CONNECT, NULL);

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
	pRegDlg->EnableCtrl(FALSE);
	pRegDlg->m_Btn_Connect.SetIcon(IDI_DISCONNECT, NULL);

	NetClo(ConnectSocket);
	ConnectSocket = NULL;

	Wait(1);

	NetClo(StateSocket);
	StateSocket = NULL;

	pRegDlg->Check_Timer_Off();
	pRegDlg->Connect_Timer_On();

	Invalidate_flsg = FALSE;

	return 0;
}


UINT Connect_Check_Thread(LPVOID pParam)
{
	ConnectSocket = NetCon(pRegDlg->ch_ip, pRegDlg->ch_port);
	//Sleep(1);
	Wait(1);
	StateSocket = NetCon(pRegDlg->ch_ip, pRegDlg->ch_port);

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
		pRegDlg->Connect_Timer_Off();
		pRegDlg->Check_Timer_On();

		Invalidate_flsg = FALSE;
	}
	return 0;
}

BOOL CRegCtrlDlg::OnEraseBkgnd(CDC* pDC)
{
	CDC dcBg;
	dcBg.CreateCompatibleDC(pDC);
	CBitmap* pOldBmpBg = (CBitmap*)dcBg.SelectObject(&m_bmpBg);

	CRect thisRect;
	GetWindowRect(thisRect);
	
	pDC->BitBlt(0, 0, thisRect.Width(), thisRect.Height(), &dcBg, 0, 0, SRCCOPY);
	dcBg.SelectObject(pOldBmpBg);

	return TRUE;

	//return CDialogEx::OnEraseBkgnd(pDC);
}