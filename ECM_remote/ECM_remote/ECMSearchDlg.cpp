// ECMSearchDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ECM_remote.h"
#include "ECMSearchDlg.h"
#include "afxdialogex.h"
#include <WtsApi32.h>
#pragma comment(lib, "Wtsapi32.lib")

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "WS2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#pragma warning(disable:4996)

// CECMSearchDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CECMSearchDlg, CDialogEx)

const UINT  ID_TIMER_SEARCH = 100;
const UINT  ID_TIMER_STOP = 200;
const UINT  ID_TIMER_FLAG = 300;

#define		Search_Time		100
#define		Stop_Time		500
#define		Flag_Time		Search_Time * 60

UINT Multicast_Server_thread(LPVOID pParam);
UINT Multicast_Client_thread(LPVOID pParam);

CECMSearchDlg::CECMSearchDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CECMSearchDlg::IDD, pParent)
{

}

CECMSearchDlg::~CECMSearchDlg()
{
}

void CECMSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDCANCEL, m_Btn_Close);
	DDX_Control(pDX, IDC_EDIT_ECMNAME, m_Edit_ECMName);
	DDX_Control(pDX, IDC_BUTTON_ECMNAMESET, m_Btn_ECMNameSet);
	DDX_Control(pDX, IDC_BUTTON_SEARCH, m_Btn_Search);
	DDX_Control(pDX, IDC_PROGRESS_SEARCH, m_Progress_Loading);
	DDX_Control(pDX, IDC_LIST_ECM, m_List_ECM);
	DDX_Control(pDX, IDC_BUTTON_ALLCLEAR, m_Btn_AllClear);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_Btn_Delete);
}


BEGIN_MESSAGE_MAP(CECMSearchDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDCANCEL, &CECMSearchDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_ECMNAMESET, &CECMSearchDlg::OnBnClickedButtonEcmnameset)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CECMSearchDlg::OnBnClickedButtonSearch)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_ECM, &CECMSearchDlg::OnNMDblclkListEcm)
	ON_MESSAGE(WM_SEARCH_DATA, &CECMSearchDlg::OnRecvSearch)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_ALLCLEAR, &CECMSearchDlg::OnBnClickedButtonAllclear)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CECMSearchDlg::OnBnClickedButtonDelete)
END_MESSAGE_MAP()


// CECMSearchDlg 메시지 처리기입니다.


BOOL CECMSearchDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	pCECMSearchDlg = this;

	// Create Wake Event
	m_hWake = CreateEvent(NULL, FALSE, FALSE, NULL);
// ----------------------------------------------------------------------------------------------------
// Control
	// Close
	m_Btn_Close.DrawBorder(FALSE);
	m_Btn_Close.SetColor(CButtonST::BTNST_COLOR_BK_OUT, DIALOGCOLOR);
	m_Btn_Close.SetColor(CButtonST::BTNST_COLOR_BK_IN, DIALOGSUBCOLOR);

	// ECM Name
	m_Edit_ECMName.SetWindowTextW(ReadIni(SEC_ECMREMOTE, KEY_ECMNAME, DEF_ECMNAME));

	// Progress
	m_Progress_Loading.SetRange(0, 50);
	m_Progress_Loading.SetPos(0);
	m_Progress_Loading.ShowWindow(SW_HIDE);

	// List
	m_List_ECM.DeleteAllItems();															// Set List Ctrl Init
	m_List_ECM.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);					// Set List Ctrl Style
	
	CRect List_rect;
	m_List_ECM.GetWindowRect(List_rect);													// List Ctrl Size
	m_List_ECM.InsertColumn(0, _T("No."), LVCFMT_CENTER, List_rect.Width() * 0.06);			// Set List Ctrl Insert Column
	m_List_ECM.InsertColumn(1, _T("ECM Name"), LVCFMT_CENTER, List_rect.Width() * 0.17);
	m_List_ECM.InsertColumn(2, _T("Server IP"), LVCFMT_CENTER, List_rect.Width() * 0.2);
	m_List_ECM.InsertColumn(3, _T("Port"), LVCFMT_CENTER, List_rect.Width() * 0.1);
	m_List_ECM.InsertColumn(4, _T("PC Name"), LVCFMT_CENTER, List_rect.Width() * 0.17);
	m_List_ECM.InsertColumn(5, _T("PC IP"), LVCFMT_CENTER, List_rect.Width() * 0.2);
	m_List_ECM.InsertColumn(6, _T("Server"), LVCFMT_CENTER, List_rect.Width() * 0.1);

// ----------------------------------------------------------------------------------------------------
// Value
	m_Search_flag = FALSE;
	m_CECMSearchDlg = FALSE;
	
	m_bSortAscending = TRUE;
	m_iOldColumn = -1;

	flag_cSend = FALSE;


// ----------------------------------------------------------------------------------------------------
// Multicast data Recv & Packet Send Thread
	//wVersionRequested = MAKEWORD(2, 2);
	//WSAStartup(wVersionRequested, &wsaData);

	g_pMulticastClient = AfxBeginThread(Multicast_Client_thread, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
	g_pMulticastServer = NULL;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CECMSearchDlg::OnPaint()
{
	// 아웃 라인
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

	dc.TextOutW(10, 6, DLG_ECMSEARCH);
}


BOOL CECMSearchDlg::PreTranslateMessage(MSG* pMsg)
{
	CWnd* wndFocus = GetFocus();

	switch (pMsg->wParam)
	{
	case VK_ESCAPE:
	case VK_RETURN:
			return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CECMSearchDlg::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case ID_TIMER_FLAG:
		flag_cSend = FALSE;
		break;
	case ID_TIMER_SEARCH:
		// Send Serarch Cmd
		SendSerarchCmd();

		if (50 > m_Progress_Loading.GetPos())
			m_Progress_Loading.SetPos(m_Progress_Loading.GetPos() + 1);

		if (50 == m_Progress_Loading.GetPos())
			OnBnClickedButtonSearch();

		break;
	case ID_TIMER_STOP:

		FinishStopTimer();

		// 검색 중이면 중단
		m_Search_flag = FALSE;

		closesocket(m_sock_sRecv);
		m_sock_sRecv = 0;
		//SetEvent(m_hWake);
		//WaitForSingleObject(g_pMulticastServer, INFINITE);
		//CloseHandle(g_pMulticastServer);
		g_pMulticastServer = NULL;

		// UI Button Enable
		EnableCtrl(TRUE);

		// List Heaer Lock
		CHeaderCtrl* pCLstCtrlHeader = m_List_ECM.GetHeaderCtrl();
		pCLstCtrlHeader->EnableWindow(TRUE);

		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}


BOOL CECMSearchDlg::StartStopTimer(void)
{
	FinishStopTimer();

	// Search Prograss & Serch MSG Start
	m_uiStopTimerID = SetTimer(ID_TIMER_STOP, Stop_Time, NULL);
	return TRUE;
}


BOOL CECMSearchDlg::FinishStopTimer(void)
{
	// Search Stop Kill
	if (m_uiStopTimerID) {
		if (this->GetSafeHwnd())
			KillTimer(m_uiStopTimerID);
		m_uiStopTimerID = 0;
	}
	return TRUE;
}


BOOL CECMSearchDlg::StartSearchTimer(void)
{
	FinishSearchTimer();

	// Search Prograss & Serch MSG Start
	m_uiSearchTimerID = SetTimer(ID_TIMER_SEARCH, Search_Time, NULL);

	return TRUE;
}


BOOL CECMSearchDlg::FinishSearchTimer(void)
{
	// Search Prograss Kill
	if (m_uiSearchTimerID) {
		if (this->GetSafeHwnd())
			KillTimer(m_uiSearchTimerID);
		m_uiSearchTimerID = 0;
		m_Progress_Loading.SetPos(0);
	}
	return TRUE;
}


BOOL CECMSearchDlg::StartFlagTimer(void)
{
	FinishFlagTimer();

	flag_cSend = TRUE;

	// Search Prograss & Serch MSG Start
	m_FlagTimerID = SetTimer(ID_TIMER_FLAG, Flag_Time, NULL);

	return TRUE;
}


BOOL CECMSearchDlg::FinishFlagTimer(void)
{
	// Search Prograss Kill
	if (m_FlagTimerID) {
		if (this->GetSafeHwnd())
			KillTimer(m_FlagTimerID);
		m_FlagTimerID = 0;
	}
	return TRUE;
}


void CECMSearchDlg::OnBnClickedCancel()
{
	if (pRemoteDlg->flag_close)
	{
		WaitForSingleObject(g_pMulticastServer, INFINITE);
		CloseHandle(g_pMulticastServer);
		g_pMulticastServer = NULL;

		WaitForSingleObject(g_pMulticastClient, INFINITE);
		CloseHandle(g_pMulticastClient);
		g_pMulticastClient = NULL;

		closesocket(m_sock_sSend);
		closesocket(m_sock_sRecv);
		closesocket(m_sock_cSend);
		closesocket(m_sock_cRecv);

		WSACleanup();
	}

	CString str;
	m_Edit_ECMName.GetWindowTextW(str);
	WriteIni(SEC_ECMREMOTE, KEY_ECMNAME, str);

	pRemoteDlg->m_ShowDlg_ECMSearch = FALSE;
	ShowWindow(SW_HIDE);
}


void CECMSearchDlg::OnBnClickedButtonEcmnameset()
{
	CString str;
	m_Edit_ECMName.GetWindowTextW(str);
	WriteIni(SEC_ECMREMOTE, KEY_ECMNAME, str);
}


void CECMSearchDlg::OnBnClickedButtonSearch()
{
	if (m_Search_flag)
	{
		FinishSearchTimer();

		StartStopTimer();
	}
	else
	{
		/* Search Start */
		// UI Button Status and UI Change
		EnableCtrl(FALSE);
		m_List_ECM.DeleteAllItems();

		g_pMulticastServer = AfxBeginThread(Multicast_Server_thread, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);

		// Search Prograss & Serch MSG Start
		StartSearchTimer();

		m_Search_flag = TRUE;

		// List Heaer Lock
		CHeaderCtrl* pCLstCtrlHeader = m_List_ECM.GetHeaderCtrl();
		pCLstCtrlHeader->EnableWindow(FALSE);
	}
}


BOOL CECMSearchDlg::SendSerarchCmd()
{
	if (FALSE == m_Search_flag)
		return FALSE;

	netMsg sNetMsg = { 0 };
	Make_netMsg(&sNetMsg);

#if 1
	int iSendLen = sendto(m_sock_sSend, (char*)&sNetMsg, sizeof(netMsg), 0, (struct sockaddr*)&m_addr_sSend, sizeof(SOCKADDR_IN));
#else
	AllinterfaceSend(&sNetMsg);
#endif
	return TRUE;
}


int CECMSearchDlg::AllinterfaceSend(netMsg *sNetMsg)
{
	int state = -1;

	char szHostName[128] = "";
	if (gethostname(szHostName, sizeof(szHostName))) {
		AfxMessageBox(L"gethostname Failed!"); return -1;
	}

	struct hostent *pHost = 0;
	pHost = gethostbyname(szHostName);
	if (!pHost) {
		AfxMessageBox(L"gethostbyname Failed!"); return -1;
	}

	struct in_addr addr;
	for (int i = 0; pHost->h_addr_list[i]; i++) {
		memcpy(&addr.s_addr, pHost->h_addr_list[i], pHost->h_length);
		state = setsockopt(m_sock_sSend, IPPROTO_IP, IP_MULTICAST_IF, (const char *)&addr, sizeof(addr));
		state = sendto(m_sock_sSend, (char*)sNetMsg, sizeof(netMsg), 0, (struct sockaddr*)&m_addr_sSend, sizeof(SOCKADDR_IN));
	}

	return state;
}


inline void CECMSearchDlg::UpdateColumnName(int column_index, BOOL is_ascending)
{
	CHeaderCtrl* header_ctrl1 = m_List_ECM.GetHeaderCtrl();
	WCHAR        text_buffer[255] = { 0, };
	LVCOLUMN     lvColumn;
	CString      str;
	//header_ctrl1->GetItemCount();
	for (int i = 0; i < 3; ++i)
	{
		lvColumn.mask = LVCF_TEXT;
		str.LoadString(0 + i);
		_stprintf_s(text_buffer, 255, _T("%s%s", (i == column_index) ? ((is_ascending) ? L"+ " : L"- ") : L"", str));
		lvColumn.pszText = text_buffer;
		m_List_ECM.SetColumn(i, &lvColumn);
	}
}


void CECMSearchDlg::OnNMDblclkListEcm(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (!m_CServerDlg)
	{
		LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

		if (m_List_ECM.GetItemCount() > 0)
		{
			// List Control Data 얻기
			CString strIP = _T("");
			CString strPort = _T("");
			strIP = m_List_ECM.GetItemText(pNMItemActivate->iItem, 2);
			strPort = m_List_ECM.GetItemText(pNMItemActivate->iItem, 3);

			// IP Address set
			CString temp_str[4];
			BYTE temp_IP[4];
			int temp[4];
			if (strIP != _T(""))
			{
				for (int i = 0; i < 4; i++)
				{
					AfxExtractSubString(temp_str[i], strIP, i, '.');
					temp[i] = _ttoi(temp_str[i]);
					temp_IP[i] = (BYTE)temp[i];
				}
				pRemoteDlg->m_ctrlIPAddr.SetAddress(temp_IP[0], temp_IP[1], temp_IP[2], temp_IP[3]);
			}

			// Port Number set
			if (strPort != _T(""))
				pRemoteDlg->m_Edit_Port.SetWindowTextW(strPort);
		}
	}
	*pResult = 0;
}


void CECMSearchDlg::Make_netMsg(netMsg* NetMsg)
{
	CString str = _T("");
	int iChangeIP = 0;

	// magic code
	NetMsg->magic = htonl(MAGIC);

	// ECM Name
	m_Edit_ECMName.GetWindowTextW(str);
	strcpy((char*)NetMsg->ecmname, CT2A(str));

	// Server IP
	BYTE	ServerIP_temp[4];

	pRemoteDlg->m_ctrlIPAddr.GetAddress(ServerIP_temp[0], ServerIP_temp[1], ServerIP_temp[2], ServerIP_temp[3]);
	str.Format(_T("%d.%d.%d.%d"), ServerIP_temp[0], ServerIP_temp[1], ServerIP_temp[2], ServerIP_temp[3]);

	for (int i = 0; i<4; i++){
		CString strTemp(_T(""));
		AfxExtractSubString(strTemp, str, i, '.');
		switch (i)
		{
		case 0:{ iChangeIP |= (_ttoi(strTemp) << 0);	break; }
		case 1:{ iChangeIP |= (_ttoi(strTemp) << 8);	break; }
		case 2:{ iChangeIP |= (_ttoi(strTemp) << 16);	break; }
		case 3:{ iChangeIP |= ((_ttoi(strTemp)) << 24);	break; }
		default:{ ASSERT(0); break; }
		}
	}

	NetMsg->ecmserverip = iChangeIP;

	// Server Port
	pRemoteDlg->m_Edit_Port.GetWindowTextW(str);
	NetMsg->ecmserverport = _ttoi(str);

	// PC Name
	DWORD dwCnt = 0;
	LPTSTR pStr = NULL;
	WTSQuerySessionInformation(WTS_CURRENT_SERVER_HANDLE, WTS_CURRENT_SESSION, WTSUserName, &pStr, &dwCnt);

	str = pStr;
	WTSFreeMemory(pStr);

	strcpy((char*)NetMsg->pcname, CT2A(str));

	// PC IP
	char name[255];
	CString PCIP; // 여기에 lcoal ip가 저장됩니다.
	PHOSTENT hostinfo;
	WORD wVersionRequested;
	WSADATA wsaData;
	wVersionRequested = MAKEWORD(2, 2);
	if (WSAStartup(wVersionRequested, &wsaData) == 0)
	{
		if (gethostname(name, sizeof(name)) == 0)
		{
			if ((hostinfo = gethostbyname(name)) != NULL)
			{
				PCIP = inet_ntoa(*(struct in_addr *)*hostinfo->h_addr_list);
			}
		}
		WSACleanup();
	}

	iChangeIP = 0;
	for (int i = 0; i<4; i++){
		CString strTemp(_T(""));
		AfxExtractSubString(strTemp, PCIP, i, '.');
		switch (i)
		{
		case 0:{ iChangeIP |= (_ttoi(strTemp) << 0);	break; }
		case 1:{ iChangeIP |= (_ttoi(strTemp) << 8);	break; }
		case 2:{ iChangeIP |= (_ttoi(strTemp) << 16);	break; }
		case 3:{ iChangeIP |= ((_ttoi(strTemp)) << 24);	break; }
		default:{ ASSERT(0); break; }
		}
	}

	NetMsg->pcip = iChangeIP;

	// EXR OCD State
	NetMsg->serverstate = m_CServerDlg;
}


void CECMSearchDlg::MakeIPAddressToString(u_int32_t addr1, CString& str)
{
	str.Format(L"%d.%d.%d.%d",
		(addr1 & 0xff),
		((addr1 >> 8) & 0xff),
		((addr1 >> 16) & 0xff),
		((addr1 >> 24) & 0xff)
		);
}


void CECMSearchDlg::ShowRecvMsg(netMsg* pNetMsg)
{
	int nSubItem = 0, nItem = m_List_ECM.GetItemCount();
	nItem = m_List_ECM.InsertItem(nItem, _T("ECMRemote"));

	// store netMsg information into list item data, it will be clear when list item deleted(delete callback message)
	netMsg* copyedNetMsg = new netMsg;
	*copyedNetMsg = *pNetMsg;
	m_List_ECM.SetItemData(nItem, (DWORD_PTR)copyedNetMsg);
	//m_cList.SetItemData(,0)

	CString str = _T("");
	// Item Number
	str.Format(L"%d", nItem + 1);
	m_List_ECM.SetItemText(nItem, nSubItem, str);
	str.ReleaseBuffer(); nSubItem++;

	// ECM Name
	USES_CONVERSION; // MultiByteToWideChar
	str.Format(_T("%s"), CA2T((char*)pNetMsg->ecmname));
	m_List_ECM.SetItemText(nItem, nSubItem, str);
	str.ReleaseBuffer(); nSubItem++;

	// Server IP Address
	//str = pNetMsg->ecmserverip;
	MakeIPAddressToString(pNetMsg->ecmserverip, str);
	m_List_ECM.SetItemText(nItem, nSubItem, str);
	str.ReleaseBuffer(); nSubItem++;

	// Server Port Number
	//str = pNetMsg->ecmserverport;
	str.Format(L"%d", pNetMsg->ecmserverport);
	m_List_ECM.SetItemText(nItem, nSubItem, str);
	str.ReleaseBuffer(); nSubItem++;

	// PC Name
	str.Format(_T("%s"), CA2T((char*)pNetMsg->pcname));
	m_List_ECM.SetItemText(nItem, nSubItem, str);
	str.ReleaseBuffer(); nSubItem++;

	// PC IP Address
	//str = pNetMsg->pcip;
	MakeIPAddressToString(pNetMsg->pcip, str);
	m_List_ECM.SetItemText(nItem, nSubItem, str);
	str.ReleaseBuffer(); nSubItem++;

	// EXR OCD State
	//str = pNetMsg->ocdstate;
	if (pNetMsg->serverstate)	str = _T("O");
	else						str = _T("X");
	m_List_ECM.SetItemText(nItem, nSubItem, str);

	str.ReleaseBuffer(); nSubItem++;
}

afx_msg LRESULT CECMSearchDlg::OnRecvSearch(WPARAM wParam, LPARAM lParam)
{
	if (NULL == wParam) return 0L;

	netMsg* pItem = (netMsg*)wParam;

	// Check Item Inspection
	if (pItem->magic == htonl(MAGIC))
		ShowRecvMsg(pItem);

	if (pItem){
		delete pItem;
		pItem = NULL;
	}
	return 0;
}


UINT Multicast_Server_thread(LPVOID pParam)
{
	// ----------------------------------------------------------------------------------------------------
	// Mulitcast Socket Create
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	while (1)
	{
		// Init Mulitcast Socket Create and Setup
		if ((pCECMSearchDlg->m_sock_sSend = socket(PF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
			//pRemoteDlg->m_Bt_ECMSearch.EnableWindow(FALSE);
			//AfxMessageBox(_T("Mulitdcast Sender Socket Create Failed!"));
			pCECMSearchDlg->m_sock_sSend = NULL;
			continue;
			return -1;
		}

		int timeLive = 64;
		if ((setsockopt(pCECMSearchDlg->m_sock_sSend, IPPROTO_IP, IP_MULTICAST_TTL, (char*)&timeLive, sizeof(timeLive))) == INVALID_SOCKET) {
			//pRemoteDlg->m_Bt_ECMSearch.EnableWindow(FALSE);
			//AfxMessageBox(_T("Mulitdcast Sender Socket Option Setting Failed!"));
			closesocket(pCECMSearchDlg->m_sock_sSend);
			pCECMSearchDlg->m_sock_sSend = NULL;
			continue;
			return -1;
		}

		memset(&pCECMSearchDlg->m_addr_sSend, 0, sizeof(pCECMSearchDlg->m_addr_sSend));
		pCECMSearchDlg->m_addr_sSend.sin_family = AF_INET;
		pCECMSearchDlg->m_addr_sSend.sin_port = htons(SEND_PORT);
		pCECMSearchDlg->m_addr_sSend.sin_addr.s_addr = inet_addr("239.255.255.250");


		/* Search Start */
		// Receive broadcast UDP socket Create and setup
		if ((pCECMSearchDlg->m_sock_sRecv = socket(PF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
			//AfxMessageBox(L"Recv Socket Create Failed!"); 
			closesocket(pCECMSearchDlg->m_sock_sSend);
			pCECMSearchDlg->m_sock_sSend = NULL;
			continue;
			return -1;
		}

		pCECMSearchDlg->m_addr_sRecv.sin_family = AF_INET;
		pCECMSearchDlg->m_addr_sRecv.sin_port = htons(LISTEN_PORT);
		pCECMSearchDlg->m_addr_sRecv.sin_addr.s_addr = htonl(INADDR_ANY);

		if (INVALID_SOCKET == bind(pCECMSearchDlg->m_sock_sRecv, (struct sockaddr*)&pCECMSearchDlg->m_addr_sRecv, sizeof(SOCKADDR_IN))) {
			//AfxMessageBox(L"Recv Socket Binding Failed!");
			closesocket(pCECMSearchDlg->m_sock_sSend);
			pCECMSearchDlg->m_sock_sSend = NULL;
			continue;
			return -1;
		}
		Sleep(1);
		break;
	}

	char buf[256] = { 0, };
	int nLen(0), nMsgLen = sizeof(netMsg);
	while (1) {
		ZeroMemory(&buf, 60);
		nLen = recvfrom(pCECMSearchDlg->m_sock_sRecv, (char*)buf, 60, 0, NULL, 0);

		if (nLen < 0) break;
		if (nLen == 0) {
			Sleep(100); continue;
		}

		// Make Dynamic Item
		netMsg* pItem = new netMsg;
		memset(pItem, 0, sizeof(netMsg));
		memcpy(pItem, (netMsg*)buf, sizeof(netMsg));

		if (pCECMSearchDlg->GetSafeHwnd()){
			pCECMSearchDlg->PostMessage(WM_SEARCH_DATA, (WPARAM)pItem);
		}

		Sleep(1);
	}
	WaitForSingleObject(pCECMSearchDlg->m_hWake, INFINITE);

	return 0;
}

UINT Multicast_Client_thread(LPVOID pParam)
{
	// UDP Socket 생성
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	struct ip_mreq joinAddr;

	int state = -1;

	while (1)
	{
		if ((pCECMSearchDlg->m_sock_cRecv = socket(PF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
		{
			AfxMessageBox(_T("Multicast Receiver Socket Create Failed! retry..."));
			Sleep(10);
			continue;
		}

#if 0
		// SO_REUSEADDR
		BOOL optval = TRUE;
		state = setsockopt(pCECMSearchDlg->m_sock_cRecv, SOL_SOCKET, SO_REUSEADDR, (char *)&optval, sizeof(optval));
		if (state == SOCKET_ERROR)
		{
			AfxMessageBox(_T("setsockopt()-SO_REUSEADDR"));
			closesocket(pCECMSearchDlg->m_sock_cRecv);
			Sleep(10);
			continue;
		}
#endif

		memset(&pCECMSearchDlg->m_addr_cRecv, 0, sizeof(pCECMSearchDlg->m_addr_cRecv));
		pCECMSearchDlg->m_addr_cRecv.sin_family = AF_INET;
		pCECMSearchDlg->m_addr_cRecv.sin_addr.s_addr = htonl(INADDR_ANY);	//IPADDR_BROADCAST;//INADDR_ANY;
		pCECMSearchDlg->m_addr_cRecv.sin_port = htons(SEND_PORT);

		state = bind(pCECMSearchDlg->m_sock_cRecv, (struct sockaddr *)&pCECMSearchDlg->m_addr_cRecv, sizeof(pCECMSearchDlg->m_addr_cRecv));
		if (state == -1)
		{
			AfxMessageBox(_T("Multicast Receiver Socket Bind Failed! retry..."));
			closesocket(pCECMSearchDlg->m_sock_cRecv);
			Sleep(10);
			continue;
		}

		joinAddr.imr_multiaddr.s_addr = inet_addr("239.255.255.250");			// 멀티캐스트 그룹 주소  반드시 클래스 D 그룹 IP 어야 한다.
		joinAddr.imr_interface.s_addr = htonl(INADDR_ANY);						// 자기 자신을 알려줌

		// 소켓 옵션 설정. IP_ADD_MEMBERSHIP : 멀티캐스트 그룹에 가입
		state = setsockopt(pCECMSearchDlg->m_sock_cRecv, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&joinAddr, sizeof(joinAddr));
		if (state == -1)
		{
			AfxMessageBox(_T("Multicast Receiver Socket Option Setting Failed! retry..."));
			closesocket(pCECMSearchDlg->m_sock_cRecv);
			Sleep(10);
			continue;
		}

		Sleep(1);
		break;
	}

#if 1
	while (1)
	{
		char buf[256] = { 0, };
		int nLen(0), nMsgLen = sizeof(netMsg);
		ZeroMemory(&buf, 256);

		int len = sizeof(pCECMSearchDlg->m_addr_cRecv);

		//nLen = recvfrom(pCECMSearchDlg->m_sock_cRecv, (char*)buf, sizeof(netMsg), 0, (struct sockaddr*)&pCECMSearchDlg->m_addr_cRecv, &len);
		if (!pCECMSearchDlg->flag_cSend)
			nLen = recvfrom(pCECMSearchDlg->m_sock_cRecv, (char*)buf, sizeof(netMsg), 0, 0, 0);
		else
		{
			Sleep(1); continue;
		}

		//if (nLen < 0) break;
		if (nLen < 0) {
			Sleep(1); continue;
		}

		// Make Dynamic Item
		netMsg* pItem = new netMsg;
		memset(pItem, 0, sizeof(netMsg));
		memcpy(pItem, (netMsg*)buf, sizeof(netMsg));

		if (htonl(pItem->magic) == MAGIC)
		{
			// Receive broadcast UDP socket Create and setup
			if ((pCECMSearchDlg->m_sock_cSend = socket(PF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
				AfxMessageBox(L"send_packet Socket Create Failed!");
				return -1;
			}

			struct ip_mreq mreq;

			mreq.imr_multiaddr.s_addr = htonl(INADDR_BROADCAST);
			mreq.imr_interface.s_addr = htonl(INADDR_BROADCAST);

			if (setsockopt(pCECMSearchDlg->m_sock_cSend, SOL_SOCKET, SO_BROADCAST, (char*)&mreq, sizeof(mreq)) == -1){
				//printf ("ERROR iputil : setsockopt\n");
				closesocket(pCECMSearchDlg->m_sock_cSend);
				return -2;
			}


			pCECMSearchDlg->m_addr_cSend.sin_family = AF_INET;
			pCECMSearchDlg->m_addr_cSend.sin_port = htons(LISTEN_PORT);
			pCECMSearchDlg->m_addr_cSend.sin_addr.s_addr = htonl(INADDR_BROADCAST); // inet_addr("192.168.0.199");

			if (connect(pCECMSearchDlg->m_sock_cSend, (struct sockaddr *)&pCECMSearchDlg->m_addr_cSend, sizeof(struct sockaddr)) == -1)
			{
				AfxMessageBox(_T("ERROR iputil : send_packet - connect\n"));
				closesocket(pCECMSearchDlg->m_sock_cSend);
				return -1;
			}

			if(pCECMSearchDlg->flag_cSend)
				continue;
			
			netMsg NetMsg;
			pCECMSearchDlg->Make_netMsg(&NetMsg);
			if (sendto(pCECMSearchDlg->m_sock_cSend, (char *)&NetMsg, sizeof(netMsg), 0, (struct sockaddr *)&pCECMSearchDlg->m_addr_cSend, sizeof(SOCKADDR_IN)) == -1)
			{
				AfxMessageBox(_T("ERROR : send_packet - sendto\n"));
				closesocket(pCECMSearchDlg->m_sock_cSend);
				return -1;
			}
			
			// 한번 응답하고나서 일정시간 응답 안하도록록 만듬
			pCECMSearchDlg->StartFlagTimer();

			closesocket(pCECMSearchDlg->m_sock_cSend);
		}
		else
		{
			AfxMessageBox(_T("Mismatch Magic Number"));
			continue;
		}
		Sleep(1);
	}
#endif
	WSACleanup();
	return 0;
}


void CECMSearchDlg::EnableCtrl(BOOL state)
{
	m_Edit_ECMName.EnableWindow(state);
	m_Btn_ECMNameSet.EnableWindow(state);
	m_Btn_AllClear.EnableWindow(state);
	m_Btn_Delete.EnableWindow(state);

	if (state)
	{
		m_Btn_Search.SetWindowTextW(_T("Search"));
		m_Progress_Loading.ShowWindow(SW_HIDE);
	}
	else
	{
		m_Btn_Search.SetWindowTextW(_T("Stop"));
		m_List_ECM.DeleteAllItems();
		m_Progress_Loading.ShowWindow(SW_SHOW);
	}
}

void CECMSearchDlg::OnBnClickedButtonAllclear()
{
	m_List_ECM.DeleteAllItems();
}


void CECMSearchDlg::OnBnClickedButtonDelete()
{
	POSITION pos = NULL;
	pos = m_List_ECM.GetFirstSelectedItemPosition();

	m_List_ECM.DeleteItem(m_List_ECM.GetNextSelectedItem(pos));
	pos = m_List_ECM.GetFirstSelectedItemPosition();
}
