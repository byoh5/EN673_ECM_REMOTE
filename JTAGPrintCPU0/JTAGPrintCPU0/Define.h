#pragma once

#include <windows.h>

#define DEFAULT_PORT "5556"

#define DLG_JTAGPRINTCPU0		_T("JTAG Print CPU0")

// >> Base Color
// ----------------------------------------------------------------------------------------------------
#define TITLECOLOR				RGB(255, 255, 255)
#if 0
#define DIALOGCOLOR				RGB(73, 85, 118) /*저채도파랑*/
//#define DIALOGCOLOR				RGB(125, 138, 147) /*파란빛 감도는 회색*/
#define	DIALOGSUBCOLOR			RGB(110, 135, 170)
#define DIALOGOUTLINE			RGB(27, 39, 67)
#else
#define DIALOGCOLOR				RGB(117, 94, 72)
#define	DIALOGSUBCOLOR			RGB(170, 140, 110)
#define DIALOGOUTLINE			RGB(66, 46, 26)
#endif

#define JTAG_PRINT_SIZE		(0xF0010014)	
#define JTAG_PRINT0_START	(0xF0010018)
#define JTAG_PRINT0_POINT	(0xF001001C)
#define JTAG_PRINT1_START	(0xF0010020)
#define JTAG_PRINT1_POINT	(0xF0010024)

#define JTAG_WB0_MODULE_IDX 0
#define JTAG_WB1_MODULE_IDX 1
#define JTAG_COMMON_MODULE_IDX 3
#define JTAG_CPU0_MODULE_IDX 4
#define JTAG_CPU1_MODULE_IDX 5

#define JTAG_SHELL_ADDR			0xf0010028
#define JTAG_SHELL_NOTIFY		0x00001000
#define JTAG_SHELL_NOTIFY_ADDR	0xf94000c8
#define JTAG_CPU_IRQ1			0x00000002
#define JTAG_CPU_IRQ0			0x00000001
#define JTAG_CPU_IRQ_ADDR		0xf9400000

// ====================================================================================================
// etc.
// ====================================================================================================
// Define
// ----------------------------------------------------------------------------------------------------
// ASCII
#define VK_A	65
#define VK_B	66
#define VK_C	67
#define VK_D	68
#define VK_E	69
#define VK_F	70
#define VK_G	71
#define VK_H	72
#define VK_I	73
#define VK_J	74
#define VK_K	75
#define VK_L	76
#define VK_M	77
#define VK_N	78
#define VK_O	79
#define VK_P	80
#define VK_Q	81
#define VK_R	82
#define VK_S	83
#define VK_T	84
#define VK_U	85
#define VK_V	86
#define VK_W	87
#define VK_X	88
#define VK_Y	89
#define VK_Z	90



#define INIFILE					_T(".\\ecm.ini")

#define SEC_WININFO				_T("WinInfo")

#define KEY_JTAGPRINTCPU0DLGLEFT	_T("JTAGPrintCPU0DlgLeft")
#define KEY_JTAGPRINTCPU0DLGTOP		_T("JTAGPrintCPU0DlgTop")

#define DEF_JTAGPRINTCPU0DLGLEFT	450
#define DEF_JTAGPRINTCPU0DLGTOP		440

#define SEC_JTAGPRINT0				_T("JTAGPrintCPU0")
#define KEY_JTAGPRINTMAXLINE		_T("MaxLine")
#define DEF_JTAGPRINTMAXLINE		50000000

#define SEC_SETTING				_T("Setting")
#define KEY_PARAMETERKEY		_T("ParameterKey")
#define KEY_VIEWERSTART			_T("ViewerStart")
#define KEY_PRINTSTART			_T("PrintStart")
#define KEY_PRINTAUTOSAVE		_T("PrintAutoSave")
#define KEY_PRINTSAVEPATH		_T("PrintSavePath")
#define KEY_ANALYZESAVEPATH		_T("AnalyzeSavePath")

#define DEF_PARAMETERKEY		_T("12345678")
#define DEF_VIEWERSTART			0
#define DEF_PRINTSTART			0
#define DEF_PRINTAUTOSAVE		1
#define DEF_PRINTSAVEPATH		_T("")
#define DEF_ANALYZESAVEPATH		_T("")


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

// Window Message Default Processing
BOOL DefaultWindowMessage(MSG* pMsg);

// Get
CString	GetNowPath();	// 응용프로그램 위치 디렉토리

// 변환
CString	RelativeToAbsolute(CString strRePath, CString strNowPath); // 상대경로->절대경로
CString	AbsoluteToRelative(CString strAbPath, CString strNowPath); // 절대경로->상대경로

DWORD	HexToDec(const CString& sHex); // 16진수 -> 10진수
CString	HexToBin(const CString& sHex); // 16진수 -> 2진수
int		BinToDec(const CString& sBin); // 2진수 -> 10진수
CString	HexStringOut(unsigned int i);

// 검사
BOOL	CheckHex(const CString& str);
BOOL	CheckDec(const CString& str);

// 파일
BOOL	ShowOpenFileDlg(CString* strPath, CString strDefExt, CString strFilter, CWnd* pWnd);
BOOL	ShowSaveFileDlg(CString *strPath, CString strDefExt, CString strFilter, CWnd* pWnd);

// Ini File
// Read
int ReadIni(CString strSector, CString strKey, int iDefault);
CString ReadIni(CString strSector, CString strKey, CString strDefault);
//Write
void WriteIni(CString strSector, CString strKey, CString strData);
void WriteIni(CString strSector, CString strKey, int iData);

UINT32 jtag_htonl(UINT32 n);

// JTAG Print
#define MR_READBUFFER (1024*8)

void resetpos(UINT32 cpu);
UINT32 JTAGPrint_define(UINT8* pbuf, UINT32 cpu);
UINT32 ReadJTAGPrintData(UINT32 last_pos, UINT32 size, UINT8* pbuf, UINT32 cpu);

// Auto Save
#define REMOVE_RATE		20/100
void AutoSave();
void AutoSave_Re();

void Wait(DWORD deMillisecond);
void ProcessWindowMessage();