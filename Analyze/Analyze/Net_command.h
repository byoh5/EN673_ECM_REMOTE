#ifndef _NET_COMMAND_H_
#define _NET_COMMAND_H_

#include "stdafx.h"

// win
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#pragma warning(disable:4996)

#define DEFAULT_BUFLEN 1024
#define DEFAULT_PORT "5556"
#define MAX_IN_STRING		256


// ====================================================================================================
// Initial (Default Value)
// ====================================================================================================
#define INIFILE					_T(".\\ecm.ini")

#define SEC_WININFO				_T("WinInfo")

#define	KEY_ANALYZEDLGLEFT		_T("AnalyzeDlgLeft")
#define KEY_ANALYZEDLGTOP		_T("AnalyzeDlgTop")

#define DEF_ANALYZEDLGLEFT		689
#define DEF_ANALYZEDLGTOP		0

#define SEC_ANALYZE				_T("Analyze")
#define KEY_VECTORSCOPE			_T("Vectorscope")
#define KEY_WAVEFORM_R			_T("Waveform_R")
#define KEY_WAVEFORM_G			_T("Waveform_G")
#define KEY_WAVEFORM_B			_T("Waveform_B")
#define KEY_WAVEFORM_Y			_T("Waveform_Y")
#define KEY_CAPTURE				_T("Capture")

#define DEF_VECTORSCOPE			0
#define DEF_WAVEFORM_R			0
#define DEF_WAVEFORM_G			0
#define DEF_WAVEFORM_B			0
#define DEF_WAVEFORM_Y			0
#define DEF_CAPTURE				0

#define SEC_SETTING				_T("Setting")
#define KEY_PLATFORM			_T("Platform")
#define KEY_JTAGCLKDIV			_T("JTAGClkdiv")
#define KEY_EXROCD				_T("EXROCDView")
#define KEY_PARAMETERKEY		_T("ParameterKey")
#define KEY_PARAMETERKEYSHOW	_T("ParameterKeyShow")
#define KEY_VIEWERSTART			_T("ViewerStart")
#define KEY_PRINTSTART			_T("PrintStart")
#define KEY_PRINTAUTOSAVE		_T("PrintAutoSave")
#define KEY_PRINTSAVEPATH		_T("PrintSavePath")
#define KEY_ANALYZESAVEPATH		_T("AnalyzeSavePath")

#define	DEF_PLATFORM			0				// ComboBox CulSel
#define DEF_JTAGCLKDIV			0
#define DEF_EXROCD				0
#define DEF_PARAMETERKEY		_T("12345678")
#define DEF_PARAMETERKEYSHOW	0
#define DEF_VIEWERSTART			0
#define DEF_PRINTSTART			0
#define DEF_PRINTAUTOSAVE		1
#define DEF_PRINTSAVEPATH		_T("")
#define DEF_ANALYZESAVEPATH		_T("")

SOCKET NetCon(char* addr, char* port);
UINT32 NetClo(SOCKET fd);
UINT32 ReadImageKill();
UINT32 ReadImage();
UINT32 ReadImageCheck();
UINT32 ReadImageFlag(int flag);

BOOL DefaultWindowMessage(MSG* pMsg);

// Ini File
// Read
extern int ReadIni(CString strSector, CString strKey, int iDefault);
extern CString ReadIni(CString strSector, CString strKey, CString strDefault);
//Write
extern void WriteIni(CString strSector, CString strKey, CString strData);
extern void WriteIni(CString strSector, CString strKey, int iData);

#endif	//_NET_COMMAND_H_