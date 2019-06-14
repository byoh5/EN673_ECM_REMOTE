#pragma once

#include <windows.h>

#define DEFAULT_PORT "5556"

#define DLG_REG						_T("ISP Control")
#define DLG_PARAMETER			_T("Parameter Control")

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

// TreeList
//#define ROOTCOLOR				RGB(241, 245, 251) // Root
#define ROOTCOLOR				RGB(245, 245, 245) // Root
#define ERRORCOLOR				RGB(228, 203, 221) // Root


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



// ====================================================================================================
// Dialog
// ====================================================================================================
// >> Parameter Control
// ----------------------------------------------------------------------------------------------------
#define IDC_PARAMETERTREELIST	124

// Tree Column
#define TC_PAR_ADDR		0
#define TC_PAR_NAME		1
#define	TC_PAR_BYTE		2
#define	TC_PAR_RX		3
#define TC_PAR_TX		4


// ISP
// ----------------------------------------------------------------------------------------------------
#define DEF_FDBACKREAD		1
#define DEF_FDBACKWRITE		0
#define	DEF_INVERSERW		0 // Parameter와 공통으로 사용

// Parameter
// ----------------------------------------------------------------------------------------------------
#define	DEF_PARFDBACKREAD		1
#define	DEF_PARFDBACKWRITE		0


// >>ISP Control
// ----------------------------------------------------------------------------------------------------
// TreeColumn (Parameter 공통)
#define TC_ADDR					0 
#define TC_NAME					1
#define TC_RX					2
#define TC_TX					3

#define IDC_REGTREELIST			123

// Button Color
#define DEF_BITCOLOR RGB(190, 190, 190)

#define BTN_BITCOLORNUM	5
static COLORREF	BITCOLOR[BTN_BITCOLORNUM] = {
	RGB(237, 28, 36), // Red
	RGB(255, 127, 39), // Orange
	RGB(34, 177, 76), // Green
	RGB(0, 162, 232), // Blue
	RGB(163, 73, 164)	 // Pupple
};
static COLORREF	BITCOLORH[BTN_BITCOLORNUM] = {
	RGB(255, 174, 201),
	RGB(255, 201, 14),
	RGB(181, 230, 29),
	RGB(153, 217, 234),
	RGB(200, 191, 231)
};

// Other Color
//RGB( 136,   0,  21), // Brown
//RGB( 185, 122,  87), // Brown(Highlight)
//RGB( 255, 242,   0), // Yellow
//RGB( 239, 228, 176), // Yellow(Highlight)
//RGB(  63,  72, 204), // Dark blue
//RGB( 112, 146, 190), // Dark blue(Highlight)

// Struct
typedef struct tagBIT
{
	CString strName[32];
	int		iStart[32];
	int		iEnd[32];
	int		iNum;
} BIT;

typedef struct tagHAS
{
	BOOL	bOn; // 존재여부
	DWORD	dwTxValue; // Tx값
} HAS;

typedef struct tagMNE
{
	BOOL	bOn; // 존재여부. 만들어놓긴 했는데 쓸 일 없음
	CString strLine;
	int		iBitNum;
	int		iStart[32];
	int		iEnd[32];
} MNE;

typedef struct tagPAR
{
	CString	strAddr;		// Addr
	CString	strName;		// Name
	CString	strByte;		// Byte
	CString	strTx;			// Tx
	CString strDescription;	// Description
} PAR;

// ISP(Reg)
// ----------------------------------------------------------------------------------------------------
#define	SEC_REG					_T("Reg")
#define KEY_HASFILE				_T("HasFile")
#define KEY_MNEFILE				_T("MneFile")
#define	KEY_DESFILE				_T("DesFile")
#define KEY_FDBACKREAD			_T("FeedbackRead")
#define KEY_FDBACKWRITE			_T("FeedbackWrite")
#define KEY_INVERSERW			_T("InveseReadWrite") // Reg, Parameter 공통

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
void	copyClipboard(const CString& str);
// ====================================================================================================
// Initial (Default Value)
// ====================================================================================================
#define INIFILE				_T(".\\ecm.ini")

#define DEF_PARAMETERDLGWIDTH	580
#define DEF_PARAMETERDLGHEIGHT	670
#define DEF_PARAMETERDLGLEFT	689
#define DEF_PARAMETERDLGTOP		469

// ====================================================================================================
// SECTOR, KEY Name
// ====================================================================================================
// WinInfo
// ----------------------------------------------------------------------------------------------------
#define SEC_WININFO				_T("WinInfo")

#define KEY_PARAMETERDLGLEFT	_T("ParameterDlgLeft")
#define KEY_PARAMETERDLGTOP		_T("ParameterDlgTop")

// Parameter
#define SEC_PARAMETER			_T("Parameter")
#define KEY_PARFILE				_T("ParFile")
#define KEY_PARFDBACKREAD		_T("ParFeedbackRead")
#define KEY_PARFDBACKWRITE		_T("ParFeedbackWrite")

// Ini File
// Read
int ReadIni(CString strSector, CString strKey, int iDefault);
CString ReadIni(CString strSector, CString strKey, CString strDefault);
//Write
void WriteIni(CString strSector, CString strKey, CString strData);
void WriteIni(CString strSector, CString strKey, int iData);

UINT32 jtag_htonl(UINT32 n);

// JtagUart
#define JTAG_UART_ADDR			0xf0010128
#define JTAG_UART_TX			0xf0010134
#define JTAG_UART_ISP			0xF0010140
#define JTAG_UART_PARA			0xF001014c
#define JTAG_UART_GAMMA			0xF0010158
#define JTAG_UART_COLOR			0xF0010164
#define JTAG_UART_VIEWER		0xF0010170

#define JTAG_UART_NOTIFY		0x00002000
#define JTAG_SHELL_NOTIFY_ADDR	0xf94000c8
#define JTAG_CPU_IRQ1			0x00000002
#define JTAG_CPU_IRQ0			0x00000001
#define JTAG_CPU_IRQ_ADDR		0xf9400000

#define TX						0x00
#define ISP						0x01
#define PARA					0x02
#define GAMMA					0x03
#define COLOR					0x04
#define VIEWER					0x05

#define tx_typr	PARA
#define tx_addr	JTAG_UART_PARA

#define RETRY					10

// ----------------------------------------------------------------------------------------------------
// Parameter
int ReadParameter(DWORD dwAddr, int iByte);
int WriteParameter(DWORD dwAddr, int iByte, DWORD dwData);
int WriteComm(BYTE *pBuff, int nToWrite);
int	JtagUartAck();
BOOL TxParameterKey();


// ----------------------------------------------------------------------------------------------------
// EEPROM
void ReadEEPROMAll(); // 전체코드
void WriteEEPROMAll(); // 전체코드
void ReadEEP(); // EEPROM Read 커맨드만 보내는 함수
void WriteEEP(); // EEPROM Write 커맨드만 보내는 함수


void Wait(DWORD deMillisecond);
void ProcessWindowMessage();

void	DrawWinBg(CWnd* pWnd, CBitmap* bmpBg, const CString& strTitle, BOOL bLogoOn = FALSE);// Draw Window BackGround