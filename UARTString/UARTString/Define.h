#pragma once

#include <windows.h>

#define DLG_UARTSTRING				_T("UART String")
#define DLG_UARTSTRINGCMDLOG		_T("UART String Command Log")

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


// Platform
// ----------------------------------------------------------------------------------------------------
// ★GammaDlg.h도 같이 변경해줘야 됨. 무조건!★
enum {
	EN673,
	EN674,
	PLATFORM_END
};

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

//*************************************************************************
// States of COM Port (Connect or DisConnect)

//#define		BUFF_SIZE						(64)
#define		WM_COMM_READ					(WM_USER+1)
#define		WM_COMM_KEY						(WM_USER+2)

//*************************************************************************
//

#define		VIEW_HSP			4
#define		VIEW_VSP			55
#define		DRAWWIDTH			545
#define		DRAWHEIGHT			512

//*************************************************************************
//
#define		CHANNELTOTAL		8

//*************************************************************************
//

#define	PC_STX				0x02		// STX

#define	PC_CMD_REGW			0x10		// Cmd : Register write request Rx
#define	PC_CMD_REG			0x20		// Cmd : Register read  request Rx
#define	PC_CMD_KEY			0x30		// Cmd : Key set request Rx
#define	PC_CMD_CHA			0x40		// Cmd : Character set request Rx

#define	PC_CMD_PARW			0x50		// Cmd : Write parameter in F/W. 		2 addr, 1 data.
#define PC_CMD_PARR			0x58		// Cmd : Read paramter in F/W. 			2 addr, 1 data.
#define PC_CMD_EEPW			0x60		// Cmd : Write paramter from F/W to EEP.
#define PC_CMD_EEPR			0x61		// Cmd : Read paramter from EEP to F/W.
#define PC_CMD_EEPD		 	0x62 		// Cmd : Write / Read for EEPROM is done.
#define PC_CMD_PARK			0x68		// Cmd : Parameter Enable Key

#define PC_CMD_SENW			0x70 		// Cmd : Write register in Sensor. 			2 addr, 4 data
#define PC_CMD_SENR			0x78 		// Cmd : Read register from Sensor.

#define PD_STG				0x90		// Pelco-D : xFF ADD CMD CMD DAT DAT CRC
#define PP_STG				0xa0		// Pelco-P : xA0 ADD DAT DAT DAT DAT xAF CRC

#define PC_CMD_AWBI 		0xaa 		// Cmd : AWB Init Rx
#define	PC_CMD_STR			0xb0		// Cmd : String display request Rx
#define	PC_CMD_GRP			0xc0		// Cmd : OSD display request Rx
#define	PC_CMD_ERR			0xd0		// Cmd : Error message Rx

#define	PC_CMD_INI			0xe0		// Cmd : Initial request Rx/Tx
#define	PC_CMD_ACK			0xf0		// Cmd : Acknowledge Rx/Tx

#define	PC_ETX				0x03		// ETX

#define ON_SUCCESS_STR_RX	0
#define ON_SUCCESS_ACK_RX	1
#define	ON_SUCCESS_OSD_RX	2
#define ON_SUCCESS_KEY_RX	3
#define	ON_SUCCESS_INI_RX	4
#define	ON_SUCCESS_REGR_RX	5
#define	ON_SUCCESS_REGW_RX	6
#define ON_SUCCESS_PARR_RX	7
#define ON_SUCCESS_PARW_RX	8
#define ON_SUCCESS_PARK_RX	9
#define ON_SUCCESS_EEPR_RX	10
#define ON_SUCCESS_EEPW_RX	11

#define ON_ERR_CMD_RX		20
#define ON_ERR_ETX_RX		21
#define ON_ERR_SEC_RX		22
#define ON_ERR_DAT_RX		23

#define ON_CTRLCAM_UP		30
#define ON_CTRLCAM_DOWN		31
#define ON_CTRLCAM_LEFT		32
#define ON_CTRLCAM_RIGHT	33
#define ON_CTRLCAM_ENTER	34
#define	ON_CTRLCAM_EXIT		35

#define ALL_NOT				0
#define	ALL_ING				1
#define	ALL_RX				2

#define	ASCII_CR			0x0D		// \r  : Carriage Return
#define	ASCII_LF			0x0A		// \n  : Line Feed

#define RXSTG_STX			10000
#define RXSTG_CMD			20000
#define RXSTG_DAT			30000
#define RXSTG_ETX			40000

//*************************************************************************
//

union uDOUBLE {
	int				m_int;
	float			m_float;
};

// >> Serial Port
// ----------------------------------------------------------------------------------------------------
// Port
#define	NUM_PORT		32
#define	DEF_PORT		0
static CString CBO_PORT[NUM_PORT] = {
	_T("COM1"),
	_T("COM2"),
	_T("COM3"),
	_T("COM4"),
	_T("COM5"),
	_T("COM6"),
	_T("COM7"),
	_T("COM8"),
	_T("COM9"),
	_T("COM10"),
	_T("COM11"),
	_T("COM12"),
	_T("COM13"),
	_T("COM14"),
	_T("COM15"),
	_T("COM16"),
	_T("COM17"),
	_T("COM18"),
	_T("COM19"),
	_T("COM20"),
	_T("COM21"),
	_T("COM22"),
	_T("COM23"),
	_T("COM24"),
	_T("COM25"),
	_T("COM26"),
	_T("COM27"),
	_T("COM28"),
	_T("COM29"),
	_T("COM30"),
	_T("COM31"),
	_T("COM32"),
};

// Bps
#define	NUM_BPS			10
#define	DEF_BPS			6
static CString	CBO_BPS[NUM_BPS] = {
	_T("2400"),		// 0
	_T("4800"),		// 1
	_T("9600"),		// 2
	_T("19200"),	// 3
	_T("38400"),	// 4
	_T("57600"),	// 5
	_T("115200"),	// 6
	_T("230400"),	// 7
	_T("460800"),	// 8
	_T("921600"),	// 9
};

// DataBit
#define	NUM_DATABIT		4
#define	DEF_DATABIT		3
static CString	CBO_DATABIT[NUM_DATABIT] = {
	_T("5"),		// 0
	_T("6"),		// 1
	_T("7"),		// 2
	_T("8")			// 3
};

// ParityBit
#define	NUM_PARITYBIT	3
#define	DEF_PARITYBIT	0
static CString	CBO_PARITYBIT[NUM_PARITYBIT] = {
	_T("None"),		// 0
	_T("Even"),		// 1
	_T("Odd")		// 2
};

// StopBit
#define	NUM_STOPBIT			3
#define	DEF_STOPBIT			0
static CString	CBO_STOPBIT[NUM_STOPBIT] = {
	_T("1"),		// 0
	_T("1.5"),		// 1
	_T("2")			// 2
};

// FlowControl
#define	NUM_FLOWCONTROL		3
#define	DEF_FLOWCONTROL		2
static CString	CBO_FLOWCONTROL[NUM_FLOWCONTROL] = {
	_T("Xon/Xoff"),	// 0
	_T("Hardware"),	// 1
	_T("None")		// 2
};


// ====================================================================================================
// Macro
// ====================================================================================================
#define	COMBO_ADDSTRING(STR, NUM, COMBO, ARRAY) \
	for(i = 0; i < NUM; i++)\
		{\
		COMBO.AddString(ARRAY[i]);\
		if(STR == ARRAY[i]) iCurSel = i;\
		}\
	COMBO.SetCurSel(iCurSel);

#define INMIDDLE(VALUE, MIN, MAX) (VALUE>=MIN)&&(VALUE<=MAX)


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

// 기타
void copyClipboard(const CString& str);

// ====================================================================================================
// Initial (Default Value)
// ====================================================================================================
#define INIFILE					_T(".\\ecm.ini")

#define SEC_WININFO				_T("WinInfo")

#define KEY_STRINGDLGLEFT		_T("StringDlgLeft")
#define KEY_STRINGDLGTOP		_T("StringDlgTop")

#define DEF_STRINGDLGWIDTH		520
#define DEF_STRINGDLGHEIGHT		570
#define DEF_STRINGDLGLEFT		399
#define DEF_STRINGDLGTOP		390

// Serial
// ----------------------------------------------------------------------------------------------------
#define SEC_UARTSTRING			_T("UARTString")
#define	KEY_PORT				_T("Port")
#define KEY_BPS					_T("Bps")
#define	KEY_DATABIT				_T("DataBit")
#define KEY_PARITYBIT			_T("ParityBit")
#define KEY_STOPBIT				_T("StopBit")
#define	KEY_FLOWCONTROL			_T("FlowControl")

// Ini File
// Read
int ReadIni(CString strSector, CString strKey, int iDefault);
CString ReadIni(CString strSector, CString strKey, CString strDefault);
//Write
void WriteIni(CString strSector, CString strKey, CString strData);
void WriteIni(CString strSector, CString strKey, int iData);

UINT32 jtag_htonl(UINT32 n);