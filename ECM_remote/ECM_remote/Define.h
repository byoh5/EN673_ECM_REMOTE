#pragma once

#include <windows.h>

#define DEFAULT_PORT	"5556"

#define ECMSEARCHUSER	0

// >> Base Color
// ----------------------------------------------------------------------------------------------------
#define TITLECOLOR				RGB(255, 255, 255)
#define DIALOGBTNCOLOR			RGB(100, 100, 100)
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

// >> 경로
// ----------------------------------------------------------------------------------------------------
//#define EXR_OCD					_T(".\\EXR_OCD\\EXR_OCD.exe")
#define SERVER					_T(".\\JTAG_Control\\JtagControl.exe")
#define ECMSEARCH				_T(".\\EXE\\ECMSearch.exe")
#define DOWNLOADER				_T(".\\EXE\\Downloader.exe")
#define PARAMETER				_T(".\\EXE\\Parameter.exe")
#define VIEWER					_T(".\\EXE\\Viewer.exe")
//#define JTAGPRINTCPU			_T("JTAG Print CPU")
#define JTAGPRINTCPU0			_T(".\\EXE\\JTAGPrintCPU0.exe")
#define JTAGPRINTCPU1			_T(".\\EXE\\JTAGPrintCPU1.exe")
#define JTAGDEBUGGER			_T(".\\EXE\\JTAGDebugger.exe")	
#define ANALYZER				_T(".\\EXE\\Analyze.exe")
#define ISPCONTROL				_T(".\\EXE\\RegCtrl.exe")
#define GAMMA					_T(".\\EXE\\Gamma.exe")
#define COLORMAP				_T(".\\EXE\\ColorMap.exe")
#define REGCTRL					_T(".\\EXE\\RegCtrl.exe")
#define KEY						_T(".\\EXE\\Key.exe")
#define UARTSTRING				_T(".\\EXE\\UARTString.exe")
#define LUA						_T(".\\EXE\\Lua.exe")
#define IPCAMSEARCH				_T(".\\EXE\\IPCamSearch.exe")
//#define TASKMONITOR				_T("Task Monitor")

#define DLG_ECMREMOTE			_T("ECM Remote v1.2.0.0")
// VERSION INFOMATION	[역변].[큰기능추가].[기능수정/보완].[버그수정 등]

//#define DLG_EXROCD				_T("EXR OCD")
#define DLG_EXROCD				_T("JTAG Control")
#define DLG_ECMSEARCH			_T("ECM Search")
#define DLG_DOWNLOADER			_T("Downloader")
#define DLG_PARAMETER			_T("Parameter Control")
#define DLG_VIEWER				_T("Viewer")
#define DLG_JTAGPRINTCPU0		_T("JTAG Print CPU0")
#define DLG_JTAGPRINTCPU1		_T("JTAG Print CPU1")
#define DLG_JTAGDEBUGGER		_T("JTAG Debugger")
#define DLG_ANALYZE				_T("Analyze")
#define DLG_REG					_T("ISP Control")
#define DLG_GAMMA				_T("Gamma")
#define DLG_COLORMAP			_T("Color Map")
#define DLG_KEY					_T("Key")
#define DLG_UARTSTRING			_T("UART String")
#define DLG_LUA					_T("Lua")
#define DLG_IPCAMSEARCH			_T("IP Camera Search Utility")
//#define DLG_TASKMONITOR			_T("Task Monitor")

#define BT_CLOSE				_T("X")
#define BT_MINIMIZE				_T("_")
#define BT_RESTORE				_T("-")

// ====================================================================================================
// Initial (Default Value)
// ====================================================================================================
#define INIFILE					_T(".\\ecm.ini")

#define SEC_WININFO				_T("WinInfo")
#define KEY_MAINDLGLEFT			_T("MainDlgLeft")
#define KEY_MAINDLGTOP			_T("MainDlgTop")

#define DEF_MAINDLGWIDTH		140
#define DEF_MAINDLGHEIGHT		180
#define DEF_MAINDLGLEFT			520
#define DEF_MAINDLGTOP			0

#define SEC_ECMREMOTE			_T("ECMRemote")
#define KEY_IPADDR				_T("IPAddress")
#define KEY_PORT				_T("Port")
#define KEY_COMMAND				_T("Command")
#define KEY_CHANEL				_T("Chanel")
#define KEY_ECMNAME				_T("ECMName")
#define KEY_SHOWSPECIAL			_T("ShowSpecial")

//#define DEF_COMMAND				_T("ft2232")
#define DEF_COMMAND				_T("")
#define DEF_CHANEL				_T("A")
#define DEF_ECMNAME				_T("ECM_Remote")
#define DEF_SHOWSPECIAL			0

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
#define DEF_EXROCD				1
#define DEF_PARAMETERKEY		_T("12345678")
#define DEF_PARAMETERKEYSHOW	0
#define DEF_VIEWERSTART			0
#define DEF_PRINTSTART			0
#define DEF_PRINTAUTOSAVE		1
#define DEF_PRINTSAVEPATH		_T("")
#define DEF_ANALYZESAVEPATH		_T("")

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

enum ECM_Func {			// 열거형 정의
	Server = 0,			// 초깃값 할당
	ECMSearch,
	Downloader,
	Parameter,
	Viewer,
	JTAGPrintCPU0,
	JTAGPrintCPU1,
	JTAGDebugger,
	Analyzer,
	ISP,
	Gamma,
	ColorMap,
	Key,
	UartString,
	Lua,
	IPCamSearch,
	MAUE_END,
};

#define	MAUE_NUM			MAUE_END		// MAUE 개수

// Platform
// ----------------------------------------------------------------------------------------------------
enum {
	EN673,
	EN674,
	PLATFORM_END
};

#define	NUM_PLATFORM		PLATFORM_END	// Platform 개수

static CString	CBO_PLATFORM[NUM_PLATFORM] = {
	_T("EN673"),			// 0
	_T("EN674"),			// 1
};

// JTAGClkdiv
// ----------------------------------------------------------------------------------------------------
#define	NUM_JTAGCLKDIV		61
static CString CBO_JTAGCLKDIV[NUM_JTAGCLKDIV] = {
	_T("0"),	// 0
	_T("1"),	// 1
	_T("2"),	// 2
	_T("3"),	// 3
	_T("4"),	// 4
	_T("5"),	// 5
	_T("6"),	// 6
	_T("7"),	// 7
	_T("8"),	// 8
	_T("9"),	// 9
	_T("10"),	// 10
	_T("11"),	// 11
	_T("12"),	// 12
	_T("13"),	// 13
	_T("14"),	// 14
	_T("15"),	// 15
	_T("16"),	// 16
	_T("17"),	// 17
	_T("18"),	// 18
	_T("19"),	// 19
	_T("20"),	// 20
	_T("21"),	// 21
	_T("22"),	// 22
	_T("23"),	// 23
	_T("24"),	// 24
	_T("25"),	// 25
	_T("26"),	// 26
	_T("27"),	// 27
	_T("28"),	// 28
	_T("29"),	// 29
	_T("30"),	// 30
	_T("31"),	// 31
	_T("32"),	// 32
	_T("33"),	// 33
	_T("34"),	// 34
	_T("35"),	// 35
	_T("36"),	// 36
	_T("37"),	// 37
	_T("38"),	// 38
	_T("39"),	// 39
	_T("40"),	// 40
	_T("41"),	// 41
	_T("42"),	// 42
	_T("43"),	// 43
	_T("44"),	// 44
	_T("45"),	// 45
	_T("46"),	// 46
	_T("47"),	// 47
	_T("48"),	// 48
	_T("49"),	// 49
	_T("50"),	// 50
	_T("51"),	// 51
	_T("52"),	// 52
	_T("53"),	// 53
	_T("54"),	// 54
	_T("55"),	// 55
	_T("56"),	// 56
	_T("57"),	// 57
	_T("58"),	// 58
	_T("59"),	// 59
	_T("60")	// 60
};

// 경로
CString GetNowPath();
CString	RelativeToAbsolute(CString strRePath, CString strNowPath);

// Ini File
// Read
extern int ReadIni(CString strSector, CString strKey, int iDefault);
extern CString ReadIni(CString strSector, CString strKey, CString strDefault);
//Write
extern void WriteIni(CString strSector, CString strKey, CString strData);
extern void WriteIni(CString strSector, CString strKey, int iData);