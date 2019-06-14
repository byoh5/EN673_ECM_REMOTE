#include "stdafx.h"
#include "Net_command.h"

#pragma warning(disable:4996)

SOCKET NetCon(char* addr, char* port)
{
	WSADATA wsaData;
	SOCKET con_sock;
	int iResult;
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return 0;
	}
	struct addrinfo *result = NULL,
		*ptr = NULL,
		hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	iResult = getaddrinfo(addr, port, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return 0;
	}

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

		// Create a SOCKET for connecting to server
		con_sock = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);
		if (con_sock == INVALID_SOCKET) {
			printf("socket failed with error: %ld\n", WSAGetLastError());
			WSACleanup();
			return 0;
		}

		// Connect to server.
		iResult = connect(con_sock, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			closesocket(con_sock);
			con_sock = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);

	if (con_sock == INVALID_SOCKET) {
		printf("Unable to connect to server!\n");
		WSACleanup();
		return 0;
	}
	return con_sock;
}


UINT32 NetClo(SOCKET fd)
{
	int iResult;
	char instr[MAX_IN_STRING] = { 0, 0 };

	sprintf(instr, "EXIT ");
	iResult = send(fd, instr, (int)strlen(instr) + 1, 0);
	// cleanup
	closesocket(fd);
	WSACleanup();
	return 0;
}


UINT32 ReadImageKill()
{
	int iResult;
	char instr[MAX_IN_STRING] = { 0, 0 };

	sprintf(instr, "killsendimg ");
	iResult = send(ConnectSocket, instr, (int)strlen(instr) + 1, 0);

	Sleep(100);

	return iResult;
}


UINT32 ReadImage()
{
	int iResult;
	char instr[MAX_IN_STRING] = { 0, 0 };
	//DWORD dwThreadID0;

	sprintf(instr, "sendimg ");// sendimg (cnt)
	iResult = send(ConnectSocket, instr, (int)strlen(instr) + 1, 0);

	return 0;
}


UINT32 ReadImageCheck()
{
	int iResult;
	char instr[MAX_IN_STRING] = { 0, 0 };
	//DWORD dwThreadID0;

	sprintf(instr, "rem_imagecheck ");
	iResult = send(ConnectSocket, instr, (int)strlen(instr) + 1, 0);

	char imagecheck_flag;
	iResult = recv(ConnectSocket, &imagecheck_flag, sizeof(imagecheck_flag), 0);
	
	if (imagecheck_flag == '1')
		return 1;
	else if (imagecheck_flag == '0')
		return 0;
	else
		return -1;
}

UINT32 ReadImageFlag(int flag)
{
	int iResult;
	char instr[MAX_IN_STRING] = { 0, 0 };
	//DWORD dwThreadID0;

	sprintf(instr, "rem_imageflag %d ", flag);
	iResult = send(ConnectSocket, instr, (int)strlen(instr) + 1, 0);

	return iResult;
}
// ====================================================================================================
// DefaultWindowMessage
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
BOOL DefaultWindowMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_ESCAPE:
		case VK_RETURN:
			return TRUE;
		}
	}
	return FALSE;
}

// ====================================================================================================
// ReadIni
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
int ReadIni(CString strSector, CString strKey, int iDefault)
{
	return ::GetPrivateProfileIntW(strSector, strKey, iDefault, INIFILE);
}

CString ReadIni(CString strSector, CString strKey, CString strDefault)
{
	TCHAR tCh[MAX_PATH];
	CString strResult = _T("");

	::GetPrivateProfileStringW(strSector, strKey, strDefault, tCh, MAX_PATH, INIFILE);

	strResult = (CString)tCh;

	return strResult;
}

// ====================================================================================================
// WriteIni
// ----------------------------------------------------------------------------------------------------
// ====================================================================================================
void WriteIni(CString strSector, CString strKey, CString strData)
{
	::WritePrivateProfileStringW(strSector, strKey, strData, INIFILE);
}

void WriteIni(CString strSector, CString strKey, int iData)
{
	CString strData = _T("");
	strData.Format(_T("%d"), iData);

	::WritePrivateProfileStringW(strSector, strKey, strData, INIFILE);
}