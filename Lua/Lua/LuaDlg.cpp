
// LuaDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "Lua.h"
#include "LuaDlg.h"
#include "afxdialogex.h"
#include <crtdbg.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.


UINT LuaRunThread(LPVOID pParam);

const UINT  ID_CHECK_TIMER = 100;
const UINT  ID_CONNECT_TIMER = 200;
UINT	State_Check_Thread(LPVOID pParam);
UINT	Connect_Check_Thread(LPVOID pParam);

#define		Check_Time		1000
#define		Connect_Time	5000

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


// CLuaDlg ��ȭ ����



CLuaDlg::CLuaDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLuaDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ECM);
}

void CLuaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_LUACLOSE, m_Btn_Close);
	DDX_Control(pDX, IDC_BUTTON_MINIMIZE, m_Btn_Minimize);
	DDX_Control(pDX, IDC_BUTTON_CONNECT, m_Btn_Connect);
	DDX_Control(pDX, IDC_EDIT_LUAFILE, m_Edit_LuaFile);
	DDX_Control(pDX, IDC_BUTTON_OPENLUA, m_Btn_OpenLua);
	DDX_Control(pDX, IDC_BUTTON_LUARUN, m_Btn_LuaRun);
}

BEGIN_MESSAGE_MAP(CLuaDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_LUACLOSE, &CLuaDlg::OnBnClickedButtonLuaclose)
	ON_BN_CLICKED(IDC_BUTTON_MINIMIZE, &CLuaDlg::OnBnClickedButtonMinimize)
	ON_BN_CLICKED(IDC_BUTTON_OPENLUA, &CLuaDlg::OnBnClickedButtonOpenlua)
	ON_BN_CLICKED(IDC_BUTTON_LUARUN, &CLuaDlg::OnBnClickedButtonLuarun)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CLuaDlg �޽��� ó����

BOOL CLuaDlg::OnInitDialog()
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
	pLuaDlg = this;
	int x = ReadIni(SEC_WININFO, KEY_LUADLGLEFT, DEF_LUADLGLEFT);
	int y = ReadIni(SEC_WININFO, KEY_LUADLGTOP, DEF_LUADLGTOP);
	SetWindowPos(NULL, x, y, 290, 90, NULL);
	SetWindowText(DLG_LUA);

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

	m_Btn_OpenLua.SetBitmaps(IDB_OPEN, RGB(255, 0, 255)); // ��Ʈ�� �����

	// Connect
	m_Btn_Connect.SetIcon(IDI_CONNECT, NULL);
	m_Btn_Connect.DrawTransparent(TRUE);

// ----------------------------------------------------------------------------------------------------
// Server ����
	CString strCmd = theApp.m_lpCmdLine;
	CString strAddr;
	CString strPort;
	AfxExtractSubString(strAddr, strCmd, 0, ' ');
	AfxExtractSubString(strPort, strCmd, 1, ' ');
	
	
	
	/*
#ifdef _DEBUG
	strAddr.Format(_T("192.168.0.167"));
	strPort = DEFAULT_PORT;
#endif
	*/
	if (strPort == _T("")) strPort = DEFAULT_PORT;

	CStringA addr;
	CStringA port;
	//char ch_ip[64];
	//char ch_port[64];
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

	Wait(1);

	StateSocket = NetCon(ch_ip, ch_port);

	// Connect Check Timer Set
	Check_Timer_On();

// ----------------------------------------------------------------------------------------------------
// etc
	m_bLua = FALSE;
	m_bLuaThread = FALSE;

	EnableCtrl(TRUE);

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CLuaDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CLuaDlg::OnPaint()
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
		//TOP
		CPaintDC dc(this);
		CRect rect;
		CWnd* pWnd = this;
		pWnd->GetWindowRect(rect);
		int iWidth = rect.Width();
		int iHeight = rect.Height();
		dc.FillSolidRect(0, 0, iWidth, 25, DIALOGCOLOR);

		//OutLine
		CPen NewPen(PS_SOLID, 2, DIALOGCOLOR);
		CPen * pOLdPen = dc.SelectObject(&NewPen);

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

		dc.SelectObject(pOLdPen);

		//Font
		LOGFONT lf;
		::ZeroMemory(&lf, sizeof(lf));
		lf.lfHeight = 15;
		lf.lfWeight = 700;
		wsprintf(lf.lfFaceName, _T("%s"), _T("Arial"));
		CFont NewFont;
		NewFont.CreateFontIndirectW(&lf);

		CFont * pOldFont = dc.SelectObject(&NewFont);
		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(TITLECOLOR);
		dc.TextOutW(10, 6, DLG_LUA);

		dc.SelectObject(pOldFont);
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CLuaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


BOOL CLuaDlg::PreTranslateMessage(MSG* pMsg)
{
	if (DefaultWindowMessage(pMsg))	return TRUE;
	else							return CDialogEx::PreTranslateMessage(pMsg);
}


void CLuaDlg::OnCancel()
{
	if (ConnectSocket != NULL)
	{
		NetClo(ConnectSocket);
		ConnectSocket = NULL;
	}

	Wait(10);

	if (StateSocket != NULL)
	{
		NetClo(StateSocket);
		StateSocket = NULL;
	}


	CDialogEx::OnCancel();
}


void CLuaDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetCapture();
	m_Point = point;
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CLuaDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (this == GetCapture())
	{
		CRect rcDialog;
		GetWindowRect(&rcDialog);

		int x = rcDialog.left + point.x - m_Point.x;
		int y = rcDialog.top + point.y - m_Point.y;

		SetWindowPos(NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		WriteIni(SEC_WININFO, KEY_LUADLGLEFT, x);
		WriteIni(SEC_WININFO, KEY_LUADLGTOP, y);

	}

	CDialogEx::OnMouseMove(nFlags, point);

}


void CLuaDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	ReleaseCapture();

	CDialogEx::OnLButtonUp(nFlags, point);
}

void CLuaDlg::OnBnClickedButtonLuaclose()
{
	OnCancel();
}


void CLuaDlg::OnBnClickedButtonMinimize()
{
	ShowWindow(SW_MINIMIZE);
}


void CLuaDlg::OnBnClickedButtonOpenlua()
{
	CString strLuaFile = _T("");
	CString strDefExt = _T("lua");
	CString strFilter = _T("Lua File(*.lua)|*.lua||");

	// Open Dialog
	if (!ShowOpenFileDlg(&strLuaFile, strDefExt, strFilter, this))
		return;

	// Open
	m_Edit_LuaFile.SetWindowTextW(strLuaFile);
}


void CLuaDlg::OnBnClickedButtonLuarun()
{
	// ���� ã��
	CString strLuaFile = _T("");
	m_Edit_LuaFile.GetWindowTextW(strLuaFile);
	CFileFind ffile;


	if (!ffile.FindFile(strLuaFile))
	{
		AfxMessageBox(_T("Fail open file."));
		return;
	}
	ffile.Close();

	// ���� ���� Ȯ�� 
	if (!ConnectSocket)
		return;

	// ----------------------------------------------------------------------------------------------------
	// Lua Run
	StartLuaRunThread();
}

//window frame
#define BUF_LENGTH 128

void CLuaDlg::StartLuaRunThread()
{

	/*
	char buf_info[BUF_LENGTH] = { 0, };
	char buf_message[BUF_LENGTH] = { 0, };
	char buf_lua[500] = { 0, };
	char buf_flag[100] = { 0, };
	char flag_close[4] = { 0, };
	CString test;
	CFile file;
	int filelength;
	int retval;
	int answer;
	int cnt = 0;
	*/
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//int *a = new int[10];
	if (!m_bLua)//��ư caption�� 'Run'�϶�
	{

		sendMsg(ConnectSocket, "rem_script_state ");
		m_bLua = TRUE;
		AfxBeginThread(LuaRunThread, pLuaDlg->GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
	}
	else//��ư Caption�� 'Stop'�϶�
	{
		sendMsg(ConnectSocket, "rem_script_stop ");

	}
}


UINT LuaRunThread(LPVOID pParam)
{

	char *script_state = NULL;
	char command_size[20] = { 0, };
	char file_size[50] = { 0, };
	int filelength;
	int answer;
	int retval;
	int size = 0;
	int cnt = 0;
	CFile file;
	char * file_content;
	int cfilename_length = 0;
	while (pLuaDlg->m_bLua)
	{

		retval = recv(ConnectSocket, command_size, sizeof(command_size), 0);

		if (retval == -1)
		{
			continue;
		}
		command_size[retval] = '\0';

		//���ƿ� ũ�⸸ŭ ���ڿ� �ޱ�(script���� Ȯ��)
		if (retval > 0)
		{

			if (command_size[0] == 's'&&command_size[1] == 'i'&&command_size[2] == 'z' && command_size[3] == 'e'&& command_size[4] == '_')
			{
				size = atoi((char*)command_size + 5);

			}

			if (size > 0)
			{

				script_state = (char*)malloc(size + 1);
				UINT pos;
				for (pos = 0; pos < size;)
				{
					retval = recv(ConnectSocket, script_state + pos, size - pos, 0);

					if (retval < 0)
					{
						printf("error\n");
					}
					pos += retval;
				}
				script_state[pos] = '\0';
			}

		}


		//script�� ���ư��� ������ 
		if (strcmp(script_state, "script_init") == 0)
		{


			pLuaDlg->m_Btn_LuaRun.SetWindowTextW(_T("STOP"));

			//lua file ��� ������
			CString filepath = _T("");
			pLuaDlg->m_Edit_LuaFile.GetWindowTextW(filepath);

			//lua file��ο��� �����̸��� �и�
			CString filename = filepath.Right(filepath.GetLength() - filepath.ReverseFind('\\') - 1);
			char cfilename[MAX_PATH];
			CStringA filename_array;
			filename_array = filename;
			strcpy(cfilename, filename_array.GetBuffer(filename_array.GetLength()));


		


			//cfilename_length = strlen(cfilename);
			//cfilename[cfilename_length] = '\0';




			// ���������6

			if (!file.Open(filepath, CFile::modeRead))
				AfxMessageBox(_T("fail"));

			filelength = file.GetLength();
			file_content = (char*)malloc(filelength+1);
			file_content[filelength] = '\0';
			file.Read(file_content, filelength);

			file.Close();

			retval = sendMsg(ConnectSocket, "rem_lua ");
			Sleep(10);
			
			retval = sendMsg(ConnectSocket, cfilename);
			
			Sleep(10);
			sprintf(file_size, "size %d ", filelength);
		
			
			retval = sendMsg(ConnectSocket, file_size);
			Sleep(10);
			
			sendMsg(ConnectSocket, file_content);
			Sleep(10);
			

			free(file_content);
			free(script_state);
		}
		//script�� ���� ���� ��
		else if (strcmp(script_state, "lua_running") == 0)
		{

			answer = AfxMessageBox(L"��ũ��Ʈ�� �������Դϴ�\n��� ���۽�Ű�ڽ��ϱ�?", MB_OKCANCEL);
			if (answer == IDOK)
			{
				pLuaDlg->m_Btn_LuaRun.SetWindowTextW(_T("STOP"));
			}
			else
			{

				sendMsg(ConnectSocket, "rem_script_stop  ");
			}
			free(script_state);
		}

		//script�� ���� �Ǿ��ٰ� ����� �� 
		else if (strcmp(script_state, "script_finished") == 0)
		{
			
			pLuaDlg->m_bLua = FALSE;
			pLuaDlg->m_Btn_LuaRun.SetWindowTextW(_T("Run"));
			free(script_state);
		}

		
	}

	return 0;
}

void CLuaDlg::EnableCtrl(BOOL bEnable)
{
	m_Edit_LuaFile.EnableWindow(bEnable);
	m_Btn_OpenLua.EnableWindow(bEnable);
	m_Btn_LuaRun.EnableWindow(bEnable);
}

void CLuaDlg::OnTimer(UINT_PTR nIDEvent)
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


void CLuaDlg::Check_Timer_On()
{
	m_CheckTimerID = SetTimer(ID_CHECK_TIMER, 1500, NULL);
}

void CLuaDlg::Check_Timer_Off()
{
	if (m_CheckTimerID)
	{
		if (this->GetSafeHwnd())
			KillTimer(m_CheckTimerID);
		m_CheckTimerID = 0;
	}
}

void CLuaDlg::Connect_Timer_On()
{
	m_ConnectTimerID = SetTimer(ID_CONNECT_TIMER, Connect_Time, NULL);
}

void CLuaDlg::Connect_Timer_Off()
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
				pLuaDlg->EnableCtrl(TRUE);
				pLuaDlg->m_Btn_Connect.SetIcon(IDI_CONNECT, NULL);

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

	pLuaDlg->EnableCtrl(FALSE);
	pLuaDlg->m_Btn_LuaRun.SetWindowTextW(_T("Run"));
	pLuaDlg->m_bLua = 0;
	pLuaDlg->m_Btn_Connect.SetIcon(IDI_DISCONNECT, NULL);

	NetClo(ConnectSocket);
	ConnectSocket = NULL;

	Wait(1);

	NetClo(StateSocket);
	StateSocket = NULL;

	pLuaDlg->Check_Timer_Off();
	pLuaDlg->Connect_Timer_On();

	Invalidate_flsg = FALSE;

	return 0;
}


UINT Connect_Check_Thread(LPVOID pParam)
{
	ConnectSocket = NetCon(pLuaDlg->ch_ip, pLuaDlg->ch_port);
	Sleep(1);
	StateSocket = NetCon(pLuaDlg->ch_ip, pLuaDlg->ch_port);

	if (ConnectSocket <= 0 || StateSocket <= 0)
	{
		ConnectSocket = NULL;
		StateSocket = NULL;
	}
	else
	{
		Invalidate_flsg = FALSE;
		pLuaDlg->Connect_Timer_Off();
		pLuaDlg->Check_Timer_On();
	}
	return 0;
}
