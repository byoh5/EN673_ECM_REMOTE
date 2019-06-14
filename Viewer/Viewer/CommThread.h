#if !defined(__COMMTHREAD__H__)
#define __COMMTHREAD__H__

//---------------------------- ��� ���� --------------------------//


#define	ASCII_XON		0x11
#define	ASCII_XOFF		0x13

#define BUFF_SIZE		(4096*100)
#define CHANNELTOTAL	8

// Queue Ŭ���� ���� //
class	CQueue
{
public:
	BYTE	buff[BUFF_SIZE];
	UINT32	m_iHead, m_iTail;
	CQueue();
	void	Clear();
	int		GetSize();
	BOOL	PutByte(BYTE b);		// 1 byte �ֱ�
	BOOL	GetByte(BYTE *pb);		// 1 byte ������
};


//	��� Ŭ����	CCommThread 

// ��Ʈ ���� : OpenPort("COM1", CBR_9600);
// ��Ʈ���� �б� :
//   ��Ʈ�� �� �Ŀ� ��Ʈ�� �ڷᰡ �����ϸ� WM_COMM_READ �޽����� ���� 
//   �����쿡 ���޵ȴ�. ON_MESSAGE ��ũ�θ� �̿�, �Լ��� �����ϰ�
//   m_ReadData String�� ����� �����͸� �̿� �б�
// ��Ʈ�� ���� : WriteComm(buff, 30)�� ���� ���ۿ� �� ũ�⸦ �ǳ׸� �ȴ�.

class	CCommThread
{
public:
	CCommThread();
	void ReadBuffer();
	//--------- ȯ�� ���� -----------------------------------------//
	HANDLE		m_hComm;				// ��� ��Ʈ ���� �ڵ�
	CString		m_sPortName;			// ��Ʈ �̸� (COM1 ..)
	BOOL		m_bConnected;			// ��Ʈ�� ���ȴ��� ������ ��Ÿ��.
	OVERLAPPED	m_osRead;				// ��Ʈ ���� Overlapped structure
	OVERLAPPED	m_osWrite;				//              "
	HANDLE		m_hThreadWatchComm;		// Watch�Լ� Thread �ڵ�.
	WORD		m_wPortID;				// WM_COMM_READ�� �Բ� ������ �μ�. (COM1-> 0, COM2->1,,,,,)

	//--------- ��� ���� -----------------------------------------//
	CQueue	m_QueueRead;

	//--------- �ܺ� ��� �Լ� ------------------------------------//
	BOOL	OpenPort(CString sPortName, DWORD dwBaud, WORD wParam);
	void	ClosePort();
	DWORD	WriteComm(BYTE *pBuff, DWORD nToWrite);

	//--------- ���� ��� �Լ� ------------------------------------//
	DWORD	ReadComm(BYTE *pBuff, DWORD nToRead);
	int		rxcnt;

	//*******************************************************
	
	bool	m_RefChk;
	bool	m_DataChk;

	int		m_DataCnt;
	int		m_LabelCnt;

	int		m_Label[CHANNELTOTAL][4];
	int		m_LabelPtr;

	int		gbRxStg;								// Rx Stage Counter
	int		m_LFCRCheck;							// Check Line Feed, Carriage Return
	int		m_Cmd;
	int		sTime;
	int		eTime;
	int		m_InitCnt;

	void	InitEnv();								// Init. Environment Variable
	void	CheckInitSignal(BYTE bBuff);			// Always Check Init. Signal ( STX + INI + ETX )
};

// Thread�� ����� �Լ� 
DWORD	ThreadWatchComm(CCommThread* pComm);

#endif