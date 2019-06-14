#pragma once

#include <windows.h>

#define JTAG_UART 0

#define DEFAULT_PORT "5556"

#define DLG_GAMMA				_T("Gamma")

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

// Bitwise operation
#define BitMask_01			0x1
#define BitMask_02			0x3
#define BitMask_03			0x7
#define BitMask_04			0xf
#define BitMask_05			0x1f
#define BitMask_06			0x3f
#define BitMask_07			0x7f
#define BitMask_08			0xff
#define BitMask_09			0x1ff
#define BitMask_10			0x3ff
#define BitMask_11			0x7ff
#define BitMask_12			0xfff
#define BitMask_13			0x1fff
#define BitMask_14			0x3fff
#define BitMask_15			0x7fff
#define BitMask_16			0xffff
#define BitMask_17			0x1ffff
#define BitMask_18			0x3ffff
#define BitMask_19			0x7ffff
#define BitMask_20			0xfffff
#define BitMask_21			0x1fffff
#define BitMask_22			0x3fffff
#define BitMask_23			0x7fffff
#define BitMask_24			0xffffff
#define BitMask_25			0x1ffffff
#define BitMask_26			0x3ffffff
#define BitMask_27			0x7ffffff
#define BitMask_28			0xfffffff
#define BitMask_29			0x1fffffff
#define BitMask_30			0x3fffffff
#define BitMask_31			0x7fffffff
#define BitMask_32			0xffffffff

const DWORD BitMask[32] = { BitMask_01, BitMask_02, BitMask_03, BitMask_04, BitMask_05, BitMask_06, BitMask_07, BitMask_08,
BitMask_09, BitMask_10, BitMask_11, BitMask_12, BitMask_13, BitMask_14, BitMask_15, BitMask_16,
BitMask_17, BitMask_18, BitMask_19, BitMask_20, BitMask_21, BitMask_22, BitMask_23, BitMask_24,
BitMask_25, BitMask_26, BitMask_27, BitMask_28, BitMask_29, BitMask_30, BitMask_31, BitMask_32 };

#define ValSft_R00(val)		((val)>> 0)
#define ValSft_R01(val)		((val)>> 1)
#define ValSft_R02(val)		((val)>> 2)
#define ValSft_R03(val)		((val)>> 3)
#define ValSft_R04(val)		((val)>> 4)
#define ValSft_R05(val)		((val)>> 5)
#define ValSft_R06(val)		((val)>> 6)
#define ValSft_R07(val)		((val)>> 7)
#define ValSft_R08(val)		((val)>> 8)
#define ValSft_R09(val)		((val)>> 9)
#define ValSft_R10(val)		((val)>>10)
#define ValSft_R11(val)		((val)>>11)
#define ValSft_R12(val)		((val)>>12)
#define ValSft_R13(val)		((val)>>13)
#define ValSft_R14(val)		((val)>>14)
#define ValSft_R15(val)		((val)>>15)
#define ValSft_R16(val)		((val)>>16)
#define ValSft_R17(val)		((val)>>17)
#define ValSft_R18(val)		((val)>>18)
#define ValSft_R19(val)		((val)>>19)
#define ValSft_R20(val)		((val)>>20)
#define ValSft_R21(val)		((val)>>21)
#define ValSft_R22(val)		((val)>>22)
#define ValSft_R23(val)		((val)>>23)
#define ValSft_R24(val)		((val)>>24)
#define ValSft_R25(val)		((val)>>25)
#define ValSft_R26(val)		((val)>>26)
#define ValSft_R27(val)		((val)>>27)
#define ValSft_R28(val)		((val)>>28)
#define ValSft_R29(val)		((val)>>29)
#define ValSft_R30(val)		((val)>>30)
#define ValSft_R31(val)		((val)>>31)

#define ValSft_L00(val)		((val)<< 0)
#define ValSft_L01(val)		((val)<< 1)
#define ValSft_L02(val)		((val)<< 2)
#define ValSft_L03(val)		((val)<< 3)
#define ValSft_L04(val)		((val)<< 4)
#define ValSft_L05(val)		((val)<< 5)
#define ValSft_L06(val)		((val)<< 6)
#define ValSft_L07(val)		((val)<< 7)
#define ValSft_L08(val)		((val)<< 8)
#define ValSft_L09(val)		((val)<< 9)
#define ValSft_L10(val)		((val)<<10)
#define ValSft_L11(val)		((val)<<11)
#define ValSft_L12(val)		((val)<<12)
#define ValSft_L13(val)		((val)<<13)
#define ValSft_L14(val)		((val)<<14)
#define ValSft_L15(val)		((val)<<15)
#define ValSft_L16(val)		((val)<<16)
#define ValSft_L17(val)		((val)<<17)
#define ValSft_L18(val)		((val)<<18)
#define ValSft_L19(val)		((val)<<19)
#define ValSft_L20(val)		((val)<<20)
#define ValSft_L21(val)		((val)<<21)
#define ValSft_L22(val)		((val)<<22)
#define ValSft_L23(val)		((val)<<23)
#define ValSft_L24(val)		((val)<<24)
#define ValSft_L25(val)		((val)<<25)
#define ValSft_L26(val)		((val)<<26)
#define ValSft_L27(val)		((val)<<27)
#define ValSft_L28(val)		((val)<<28)
#define ValSft_L29(val)		((val)<<29)
#define ValSft_L30(val)		((val)<<30)
#define ValSft_L31(val)		((val)<<31)


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

void	DrawWinBg(CWnd* pWnd, CBitmap* bmpBg, const CString& strTitle, BOOL bLogoOn = FALSE);// Draw Window BackGround

// ====================================================================================================
// Initial (Default Value)
// ====================================================================================================
#define INIFILE					_T(".\\ecm.ini")

#define SEC_WININFO				_T("WinInfo")

#define KEY_GAMMADLGLEFT		_T("GammaDlgLeft")
#define KEY_GAMMADLGTOP			_T("GammaDlgTop")

#define DEF_GAMMADLGLEFT		50
#define DEF_GAMMADLGTOP			390

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

// Ini File
// Read
int ReadIni(CString strSector, CString strKey, int iDefault);
CString ReadIni(CString strSector, CString strKey, CString strDefault);
//Write
void WriteIni(CString strSector, CString strKey, CString strData);
void WriteIni(CString strSector, CString strKey, int iData);

UINT32 jtag_htonl(UINT32 n);


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
#define GAMMA1					0x03
#define COLOR					0x04
#define VIEWER					0x05

#define tx_typr	GAMMA1
#define tx_addr	JTAG_UART_GAMMA

#define RETRY					10

//JTAG UART
int ReadISP(DWORD dwAddr);
int WriteISP(DWORD dwAddr, DWORD dwData);
int WriteComm(BYTE *pBuff, int nToWrite);
int	JtagUartAck();

void Wait(DWORD deMillisecond);
void ProcessWindowMessage();

void Trace(char* szFormat, ...);