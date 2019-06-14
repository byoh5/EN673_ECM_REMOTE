#include "stdafx.h"
#include "CommThread.h"

// �޼����� ���� ������ �ڵ�, �θ� �����쿡�� HWND hCommWnd= this->m_hWnd��
// ������ �ش�.
extern HWND hCommWnd;
BYTE rxData[1024];

// CQueue ������========================================= 

// Queue�� ������
CQueue::CQueue()
{
	Clear();
}

// Queue�� �ʱ�ȭ
void CQueue::Clear()
{
	m_iHead = m_iTail = 0;
	memset(buff, 0, BUFF_SIZE);
}

// Queue�� ��� �ִ� �ڷ� ����.
int CQueue::GetSize()
{
	return (m_iHead - m_iTail + BUFF_SIZE) % BUFF_SIZE;
}

// Queue�� 1 byte ����.
BOOL CQueue::PutByte(BYTE b)
{
	if (GetSize() == (BUFF_SIZE-1)) return FALSE;
	buff[m_iHead++] = b;
	if(m_iHead>=BUFF_SIZE)
	m_iHead -= BUFF_SIZE;

	return TRUE;
}

// Queue���� 1 byte ����.
BOOL CQueue::GetByte(BYTE* pb)
{
	if (GetSize() == 0) return FALSE;
	*pb = buff[m_iTail++];
	if(m_iTail>=BUFF_SIZE)
	m_iTail -= BUFF_SIZE;

	return TRUE;
}

CCommThread::CCommThread()
{
	gbRxStg = 10000;
	rxcnt = 0;
	m_LFCRCheck = 0;
	m_Cmd = -1;
	m_InitCnt = 0;
	m_bConnected = FALSE;
}

// ��Ʈ sPortName�� dwBaud �ӵ��� ����.
// ThreadWatchComm �Լ����� ��Ʈ�� ���� ������ �� MainWnd�� �˸���
// ���� WM_COMM_READ�޽����� ������ ���� ���� wPortID���� ���� �޴´�.
BOOL CCommThread::OpenPort(CString sPortName, DWORD dwBaud, WORD wPortID)
{
	// Local ����.
	COMMTIMEOUTS	timeouts;
	DCB				dcb;
	DWORD			dwThreadID;

	// ���� �ʱ�ȭ
	rxcnt			= 0;
	m_bConnected	= FALSE;
	m_wPortID		= wPortID; // COM1-> 0, COM2->1,,,,,

	// overlapped structure ���� �ʱ�ȭ.
	m_osRead.Offset			= 0;
	m_osRead.OffsetHigh		= 0;
	if (! (m_osRead.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL)))	
		return FALSE;

	m_osWrite.Offset		= 0;
	m_osWrite.OffsetHigh	= 0;
	if (! (m_osWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL)))
		return FALSE;
	
	// ��Ʈ ����
	m_sPortName = sPortName;
	
	m_hComm = CreateFileW( m_sPortName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);
	
	if (m_hComm == (HANDLE) -1)
	{
		return FALSE;
	}

	// ��Ʈ ���� ����.

	// EV_RXCHAR event ����
	SetCommMask( m_hComm, EV_RXCHAR);	

	// InQueue, OutQueue ũ�� ����.
	SetupComm( m_hComm, BUFF_SIZE, BUFF_SIZE);

	// ��Ʈ ����.
	PurgeComm( m_hComm, PURGE_TXABORT | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_RXCLEAR);

	// timeout ����.
	timeouts.ReadIntervalTimeout = 0xFFFFFFFF;
	timeouts.ReadTotalTimeoutMultiplier = 0;
	timeouts.ReadTotalTimeoutConstant = 0;
	timeouts.WriteTotalTimeoutMultiplier = 2*CBR_9600 / dwBaud;
	timeouts.WriteTotalTimeoutConstant = 0;
	SetCommTimeouts( m_hComm, &timeouts);

	// dcb ����
	dcb.DCBlength = sizeof(DCB);
	GetCommState(m_hComm, &dcb);	// ���� ���� ����.
	dcb.BaudRate = dwBaud;
	dcb.ByteSize = 8;
	dcb.Parity = 0;
	dcb.StopBits = 2; 
	dcb.fInX = dcb.fOutX = 0; //1;		// Xon, Xoff ���.
	dcb.XonChar = ASCII_XON;
	dcb.XoffChar = ASCII_XOFF;
	dcb.XonLim = 100;
	dcb.XoffLim = 100;
	if (! SetCommState( m_hComm, &dcb))	return FALSE;

	// ��Ʈ ���� ������ ����.
	m_bConnected = TRUE;
	m_hThreadWatchComm = CreateThread( NULL, 0, 
		(LPTHREAD_START_ROUTINE)ThreadWatchComm, this, 0, &dwThreadID);

	// DispString ������ ����
	pUARTStringDlg->StartDispStringThread();

	if (! m_hThreadWatchComm)
	{
		ClosePort();
		return FALSE;
	}

	return TRUE;
}
	
// ��Ʈ�� �ݴ´�.
void CCommThread::ClosePort()
{
	m_bConnected = FALSE;
	SetCommMask( m_hComm, 0);
	PurgeComm( m_hComm,					
		PURGE_TXABORT | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_RXCLEAR);
	CloseHandle( m_hComm);
}

// ��Ʈ�� pBuff�� ������ nToWrite��ŭ ����.
// ������ ������ Byte���� �����Ѵ�.
DWORD CCommThread::WriteComm(BYTE *pBuff, DWORD nToWrite)
{
	DWORD	dwWritten, dwError, dwErrorFlags;
	COMSTAT	comstat;

	if (! WriteFile( m_hComm, pBuff, nToWrite, &dwWritten, &m_osWrite))
	{
		if (GetLastError() == ERROR_IO_PENDING)
		{
			// ���� ���ڰ� ���� �ְų� ������ ���ڰ� ���� ���� ��� Overapped IO��
			// Ư���� ���� ERROR_IO_PENDING ���� �޽����� ���޵ȴ�.
			//timeouts�� ������ �ð���ŭ ��ٷ��ش�.
			while (! GetOverlappedResult( m_hComm, &m_osWrite, &dwWritten, TRUE))
			{
				dwError = GetLastError();
				if (dwError != ERROR_IO_INCOMPLETE)
				{
					ClearCommError( m_hComm, &dwErrorFlags, &comstat);
					break;
				}
			}
		}
		else
		{
			dwWritten = 0;
			ClearCommError( m_hComm, &dwErrorFlags, &comstat);
		}
	}

	return dwWritten;
}

// ��Ʈ�κ��� pBuff�� nToWrite��ŭ �д´�.
// ������ ������ Byte���� �����Ѵ�.
DWORD CCommThread::ReadComm(BYTE *pBuff, DWORD nToRead)
{
	DWORD	dwRead, dwError, dwErrorFlags;
	COMSTAT	comstat;

	//----------------- system queue�� ������ byte���� �̸� �д´�.
	ClearCommError( m_hComm, &dwErrorFlags, &comstat);
	dwRead = comstat.cbInQue;
	
	if (dwRead > 0)
	{
		if (! ReadFile( m_hComm, pBuff, nToRead, &dwRead, &m_osRead))
		{
			if (GetLastError() == ERROR_IO_PENDING)
			{
				//--------- timeouts�� ������ �ð���ŭ ��ٷ��ش�.
				while (! GetOverlappedResult( m_hComm, &m_osRead, &dwRead, TRUE))
				{
					dwError = GetLastError();
					if (dwError != ERROR_IO_INCOMPLETE)
					{
						ClearCommError( m_hComm, &dwErrorFlags, &comstat);
						break;
					}
					Sleep(0);
				}
			}
			else
			{
				dwRead = 0;
				ClearCommError( m_hComm, &dwErrorFlags, &comstat);
			}
		}
	}

	return dwRead;
}

// ��Ʈ�� �����ϰ�, ���� ������ ������ 
// m_ReadData�� ������ �ڿ� MainWnd�� �޽����� ������ Buffer�� ������
// �о��� �Ű��Ѵ�.
DWORD	ThreadWatchComm(CCommThread* pComm)
{
	CString		str = _T("");
	DWORD		dwEvent;
	OVERLAPPED	os;
	BOOL		bOk = TRUE;
	BYTE		buff[BUFF_SIZE];	 // �б� ����
	DWORD		dwRead;	 // ���� ����Ʈ��.

	// Event, OS ����.
	memset( &os, 0, sizeof(OVERLAPPED));
	if (! (os.hEvent = CreateEvent( NULL, TRUE, FALSE, NULL)))
		bOk = FALSE;
	if (! SetCommMask( pComm->m_hComm, EV_RXCHAR))
		bOk = FALSE;
	if (! bOk)
	{
		AfxMessageBox(_T("Error while creating ThreadWatchComm, ") + pComm->m_sPortName);
		return FALSE;
	}

	// ��Ʈ�� �����ϴ� ����.
	while (pComm->m_bConnected)
	{
		dwEvent = 0;

		// ��Ʈ�� ���� �Ÿ��� �ö����� ��ٸ���.
		WaitCommEvent( pComm->m_hComm, &dwEvent, NULL);

		if ((dwEvent & EV_RXCHAR) == EV_RXCHAR)
		{
			// ��Ʈ���� ���� �� �ִ� ��ŭ �д´�.
			do	
			{
				dwRead = pComm->ReadComm(buff, BUFF_SIZE);
				
				if (BUFF_SIZE - pComm->m_QueueRead.GetSize() > (int)dwRead)
				{
					for ( DWORD i = 0; i < dwRead; i++){
						pComm->m_QueueRead.PutByte(buff[i]);
						pComm->ReadBuffer();
					}
				}
				//else
					//AfxMessageBox(_T("m_QueueRead FULL!"));
				Sleep(0);
			} while (dwRead);
		}
		Sleep(0);
	}	
	
	// ��Ʈ�� ClosePort�� ���� ������ m_bConnected �� FALSE�� �Ǿ� ����.
	CloseHandle( os.hEvent);
	pComm->m_hThreadWatchComm = NULL;

	return TRUE;
}

void CCommThread::ReadBuffer()
{
	//if(!m_bConnected) return;

	CQueue* pQ;
	BYTE bBuff;
	pQ = &m_QueueRead;										// Rx data read from register
	pQ->GetByte(&bBuff);									//			"

	int i = 0;

	// gbRxStg  = 0 : STX	(RXSTG_STX)
	//			= 1 : CMD	(RXSTG_CMD)
	//			= 2 : DATA	(RXSTG_DAT)
	//			= 3 : ETX	(RXSTG_ETX)

	// Description of Packet
	//****************************************************************************************************************
	// STR : STX | PC_CMD_STR | Number of string | Character 0 | Character 1 | .... | Character N - 1 | ETX 
	//----------------------------------------------------------------------------------------------------------------
	// GRP : STX | PC_CMD_GRP | Data of graph 0 | Data of graph 1 | ............... | Data of graph 7 | ETX
	//----------------------------------------------------------------------------------------------------------------
	// REG : STX | PC_CMD_REG | Address Bit 0 | Address Bit 1 | Data Bit 0 | ........... | Data Bit 3 | ETX				<- MayBe!!
	//----------------------------------------------------------------------------------------------------------------
	// INI : STX | PC_CMD_INI | ETX
	//****************************************************************************************************************

	//CheckInitSignal(bBuff);									// Always check init. signal (STX + INI + ETX)
	
	switch (gbRxStg)
	{
	//****************************************************************************************************************
	// STAGE : STX
	case RXSTG_STX:
		
		if (bBuff == PC_STX)
			gbRxStg = RXSTG_CMD;
		else
			InitEnv();

		break;

	//****************************************************************************************************************
	// STAGE : COMMAND
	case RXSTG_CMD:
		if (bBuff == PC_CMD_STR)
		{
			gbRxStg = RXSTG_DAT;
			m_Cmd = bBuff;
		}
		else
		{
			InitEnv();
		}
		
	//****************************************************************************************************************
	// STAGE : DATA

	case RXSTG_DAT:
		switch (m_Cmd)
		{
		case PC_CMD_STR:
			rxData[rxcnt++] = bBuff;

			// Check Total Character
			if(rxcnt > 1)
			{
				if( (pUARTStringDlg->m_iPlatformSel == EN673))
				{
					if(rxcnt == rxData[1] + 2) gbRxStg = RXSTG_ETX;

					if(rxcnt > rxData[1] + 2)
						InitEnv();
				}
				else
				{
					// Check Carriage Return
					if (rxcnt == rxData[1] + 1) {
						if (rxData[rxcnt - 1] == ASCII_CR && m_LFCRCheck == 0)		m_LFCRCheck = 1;
						else														InitEnv();
					}

					// Check Line Feed
					if (rxcnt == rxData[1] + 2) {
						if (rxData[rxcnt - 1] == ASCII_LF && m_LFCRCheck == 1){		m_LFCRCheck = 2; gbRxStg = RXSTG_ETX; }
						else														InitEnv();
					}

					// Check Overflow
					if (rxcnt > rxData[1] + 2)										InitEnv();
				}
			}
			break;
		default:
			InitEnv();
			break;
		}
		
		break;

	//****************************************************************************************************************
	// STAGE : ETX
	case RXSTG_ETX:

		if (bBuff == PC_ETX)															// Check ETX
		{
			switch (m_Cmd)
			{
			case PC_CMD_STR:
				if( (pUARTStringDlg->m_iPlatformSel == EN673)) {

				}
				else {
					if(m_LFCRCheck != 2) {
						break;
					}
				}
				//::SendMessage(hCommWnd, WM_COMM_READ, ON_SUCCESS_STR_RX, 0);		// Send Message to Main Dialog

				//while(bStringFlag) {Sleep(0);};
				memcpy(pUARTStringDlg->rxData, rxData, 1024);
				//bStringFlag = TRUE;
				pUARTStringDlg->RxStr();

				break;
			default:
				break;
			}

			InitEnv();
					
		}
		else
			InitEnv();

		break;	
	}
}

void CCommThread::InitEnv()
{
	m_LFCRCheck = 0;
	rxcnt = 0;
	gbRxStg = RXSTG_STX;
	m_Cmd = -1;
}

void CCommThread::CheckInitSignal(BYTE bBuff)
{
	if (bBuff == PC_STX)					//**********************************
		m_InitCnt = RXSTG_CMD;				// STX
	else if (m_InitCnt == RXSTG_CMD)		//**********************************
	{										// INI
		if (bBuff == PC_CMD_INI)
			m_InitCnt = RXSTG_ETX;
		else
			m_InitCnt = -1;
	}
	else if (m_InitCnt == RXSTG_ETX)		//**********************************
	{										// ETX
		if (bBuff == PC_ETX) 
			InitEnv();
		else
			m_InitCnt = -1;
	}
}
