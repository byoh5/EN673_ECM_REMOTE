#pragma once
#include "BtnST.h"
#include "afxwin.h"
#include "afxcmn.h"


// CECMSearchDlg 대화 상자입니다.


#define LISTEN_PORT             59162
#define SEND_PORT               59161
#define MAGIC                   0x73747279      // magic of strx configuration


#define WM_SEARCH_DATA			WM_USER + 100

typedef	unsigned char	u_int8_t;
typedef unsigned int	u_int32_t;

#pragma pack(push, IPCAMPACK, 1)
struct netMsg {
	u_int32_t		magic;			// magic code
	u_int8_t		ecmname[20];	// ECM Name
	u_int32_t		ecmserverip;	// Server IP
	u_int32_t		ecmserverport;	// Server Port
	u_int8_t		pcname[20];		// PC Name
	u_int32_t		pcip;			// PC IP
	u_int32_t		serverstate;		// EXR OCD State
}; //__attribute__((packed));
#pragma pack(pop, IPCAMPACK)

class CECMSearchDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CECMSearchDlg)

public:
	CECMSearchDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CECMSearchDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ECMSEARCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	afx_msg LRESULT OnRecvSearch(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	// Close
	CButtonST		m_Btn_Close;
	afx_msg void OnBnClickedCancel();
	

	// ECM Name
	CEdit			m_Edit_ECMName;
	CButton			m_Btn_ECMNameSet;
	afx_msg void OnBnClickedButtonEcmnameset();

	// Search
	BOOL			m_Search_flag;
	CButton			m_Btn_Search;
	CProgressCtrl	m_Progress_Loading;
	afx_msg void OnBnClickedButtonSearch();

	// List
	CListCtrl		m_List_ECM;
	BOOL            m_bSortAscending;
	int             m_iOldColumn;
	afx_msg void OnNMDblclkListEcm(NMHDR *pNMHDR, LRESULT *pResult);
	void UpdateColumnName(int column_index, BOOL is_ascending);

	HANDLE		    m_hWake;

	// Multicast Server
	CWinThread*		g_pMulticastServer;
	SOCKET		    m_sock_sSend, m_sock_sRecv;
	SOCKADDR_IN	    m_addr_sSend, m_addr_sRecv;

	// Multicast Client
	CWinThread*		g_pMulticastClient;
	SOCKET		    m_sock_cSend, m_sock_cRecv;
	SOCKADDR_IN	    m_addr_cSend, m_addr_cRecv;
	BOOL			flag_cSend;

	BOOL SendSerarchCmd();
	int AllinterfaceSend(netMsg *sNetMsg);

	void Make_netMsg(netMsg* NetMsg);
	void MakeIPAddressToString(u_int32_t addr1, CString& str);
	void ShowRecvMsg(netMsg* pNetMsg);
	void RunRecv();

	// etc
	void EnableCtrl(BOOL state);


	// Time
	UINT            m_uiSearchTimerID;
	UINT            m_uiStopTimerID;
	UINT            m_FlagTimerID;
	BOOL            StartStopTimer(void);
	BOOL            FinishStopTimer(void);
	BOOL            StartSearchTimer(void);
	BOOL            FinishSearchTimer(void);
	BOOL            StartFlagTimer(void);
	BOOL            FinishFlagTimer(void);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	//WSADATA wsaData;
	//WORD wVersionRequested;

	CButton m_Btn_AllClear;
	afx_msg void OnBnClickedButtonAllclear();

	CButton m_Btn_Delete;
	afx_msg void OnBnClickedButtonDelete();
};
