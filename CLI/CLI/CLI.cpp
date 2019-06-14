// CLI.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "CLI.h"

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

#include <mstcpip.h>

#include "list.h"

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define MAX_IN_STRING		256
#define DEFAULT_BUFLEN		1024

SOCKET con_sock;

CLI_API int sendMsg(int fd, char* msg)
{
	Sleep(10);	//for interval of Message!!
	UINT sendmsgsize;
	sendmsgsize = strlen(msg);
	return send(fd, msg, sendmsgsize, 0);
}

CLI_API int NetCon(char* addr, char* port)
{


	WSADATA wsaData;

	int iResult;
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return -1;
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
		return -1;
	}

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

		// Create a SOCKET for connecting to server
		con_sock = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);
		if (con_sock == INVALID_SOCKET) {
			printf("socket failed with error: %ld\n", WSAGetLastError());
			WSACleanup();
			return -1;
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

	// Receive Time Out 
	int nTimeoutValue = 5000;
	iResult = setsockopt(con_sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&nTimeoutValue, sizeof(nTimeoutValue));
	if (iResult == SOCKET_ERROR) {
		closesocket(con_sock);
		con_sock = INVALID_SOCKET;
	}

#if 1
	// Set the keepalive values   
	// 
	DWORD         dwBytesRet = 0;
	struct tcp_keepalive   alive;
	alive.onoff = TRUE;
	alive.keepalivetime = 7200000;
	alive.keepaliveinterval = 6000;

	if (WSAIoctl(con_sock, SIO_KEEPALIVE_VALS, &alive, sizeof(alive), NULL, 0, &dwBytesRet, NULL, NULL) == SOCKET_ERROR)
	{
		printf("WSAIotcl(SIO_KEEPALIVE_VALS) failed; %d\n", WSAGetLastError());
		closesocket(con_sock);
		con_sock = INVALID_SOCKET;
	}
	printf("SIO_KEEPALIVE_VALS set:\n");
	printf("   Keepalive Time     = %lu\n", alive.keepalivetime);
	printf("   Keepalive Interval = %lu\n", alive.keepaliveinterval);
#endif

	freeaddrinfo(result);

	if (con_sock == INVALID_SOCKET) {
		printf("Unable to connect to server!\n");
		WSACleanup();
		return -1;
	}

	return con_sock;
}

CLI_API int NetClo(int fd)
{
	int iResult;
	char instr[MAX_IN_STRING] = { 0, 0 };

	sprintf(instr, "EXIT ");
	iResult = send(fd, instr, (int)strlen(instr) + 1, 0);
	if (iResult < 0) {
		printf("Send EXIT error: %d\n", iResult);
		WSACleanup();
		return -1;
	}
	// cleanup
	Sleep(100);
	closesocket(fd);
	WSACleanup();
	return 0;
}



CLI_API int getImagefromRemote(int fd, int cnt){
	//NetConn(0, NULL);

	int iResult;
	char instr[MAX_IN_STRING] = { 0, 0 };
	sprintf(instr, "sendimg ");// sendimg
	iResult = send(fd, instr, (int)strlen(instr) + 1, 0);

	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;
	char* buf = NULL;
	FILE*	pFile = NULL;
	int size = 0;
	UINT retry = 0;
	int err = 1;

	while (1){
		if (((retry >= cnt) && (cnt != 0))){
			//	ReadImageKill(0, NULL);
			break;
		}
		size = 0;
		iResult = recv(fd, recvbuf, DEFAULT_BUFLEN, 0);
		//printf("iResult %d", iResult);
		if (iResult > 0){
			if (iResult<DEFAULT_BUFLEN){
				recvbuf[iResult] = '\0';
				if ((recvbuf[0] == 's' && recvbuf[1] == 'i' && recvbuf[2] == 'z' && recvbuf[3] == 'e')){
					size = atoi((char*)recvbuf + 4);
						printf("%s", recvbuf);
				}
			}
			if (size>0){
				buf = (char*)malloc(size);
				UINT a;
				for (a = 0; a < size;){
					iResult = recv(fd, buf + a, size - a, 0);
					if (iResult < 0){
						printf("Error\n");
					}
					a += iResult;
					//	printf("recv %d\n", a);

				}
				addNode(buf, size);
				retry++;
				free(buf);
			}
		}
		else{
			printf("iResult %d", iResult);
			return -1;
		}

		Sleep(1);
	}

	sprintf(instr, "killsendimg ");// sendimg
	iResult = send(fd, instr, (int)strlen(instr) + 1, 0);

	return err;
}

CLI_API int getImgDataSizeFromList(int n, int* size, void* data){
	struct Node* tmp;
	tmp = searchNode(n);
	*size = tmp->size;
	memcpy(data, tmp->data,tmp->size);
	return 0;
}

CLI_API int getImgSizeFromList(int n){
	struct Node* tmp;
	tmp = searchNode(n);
	return tmp->size;
}

CLI_API int getImgDataFromList(int n,void* data){
	struct Node* tmp;
	tmp = searchNode(n);
	memcpy(data, tmp->data, tmp->size);
	return 0;
}


CLI_API int deleteList_ALL(void){
	deleteList();
	return 0;
}
#include "time.h"
CLI_API int getDataFromRemote(int fd, int addr, int size,int module ,void* value)
{
	clock_t before;
	double result;
	before = clock();
	char instr[MAX_IN_STRING] = { 0, 0 };
	sprintf(instr, "rem_mr %x %d %d ", addr, size, module);
	send(fd, instr, (int)strlen(instr) + 1, 0);

	char recvbuf[DEFAULT_BUFLEN];
	int iResult = 0;
	char* buf = NULL;

	while (1){
		//printf("*");
		//if (EscapeLoop()) break;
		iResult = recv(fd, recvbuf, DEFAULT_BUFLEN, 0);
		//printf("iResult %d", iResult);
		if (iResult > 0){
			if (iResult<DEFAULT_BUFLEN){
				recvbuf[iResult] = '\0';
				if ((recvbuf[0] == 's' && recvbuf[1] == 'i' && recvbuf[2] == 'z' && recvbuf[3] == 'e')){
					size = atoi((char*)recvbuf + 4);
					printf("%s", recvbuf);
				}
			}
			if (size>0){
				buf = (char*)malloc(size);
				UINT a;
				for (a = 0; a < size;){
					iResult = recv(fd, buf + a, size - a, 0);
					if (iResult < 0){
						printf("Error\n");
					}
					a += iResult;
						printf("recv %d\n", a);

				}
				// Add file save 

				if (value) memcpy(value, buf, size);

				free(buf);
				break;
			}

		}
		else{
			printf("iResult %d", iResult);
			return -1;
		}

		Sleep(1);
	}
	result = (double)(clock() - before) / CLOCKS_PER_SEC;
	printf("%f\n", result);
	return 0;
}


int AckFromRemote(int fd, char* str)
{
	char recvbuf[DEFAULT_BUFLEN];
	int iResult = 0;
	char* buf = NULL;

	while (1){
		
		iResult = recv(fd, recvbuf, DEFAULT_BUFLEN, 0);
		if (iResult > 0){
			if (iResult<DEFAULT_BUFLEN){
				recvbuf[iResult] = '\0';
				if (strcmp(recvbuf,str)== 0){
					printf("%s", recvbuf);
				}
			}
			break;
		}
		else{
			printf("iResult %d", iResult);
			return -1;
		}
		Sleep(1);
	}
	return 0;

}



CLI_API int setDataFromRemote(int fd, int addr, int size,int module ,void* value)
{
	UINT32 iResult;
	char instr[MAX_IN_STRING] = { 0, 0 };
	sprintf(instr, "rem_mw %x %d %d ", addr, size, module);
	
	iResult = send(fd, instr, (int)strlen(instr) + 1, 0);
	if (iResult < 0)
		return -1;

	printf("send size %d\n", (int)strlen(instr) + 1);

	if (AckFromRemote(fd, "OK ") == -1)
		return -1;

	UINT32 a;
	for (a = 0; a < size;){
		iResult = send(fd,(char*) value + a, size - a, 0);
		if (iResult < 0){
			printf("Error\n");
			return -1;
		}
		a += iResult;
	}

	if (AckFromRemote(fd, "OK ") == -1)
		return -1;

	return 0;
}