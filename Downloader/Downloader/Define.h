#pragma once

#include <windows.h>

#define DEFAULT_PORT "5556"

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

#define DLG_DOWNLOADER			_T("Downloader")

#define CHANGE_EN674		0
#define INSERT_EN674		1

#define SDRAM_BASE 0x04000000

#define JTAG_UART_ADDR			0xf0010128
#define JTAG_UART_NOTIFY		0x00002000
#define JTAG_SHELL_NOTIFY_ADDR	0xf94000c8
#define JTAG_CPU_IRQ1			0x00000002
#define JTAG_CPU_IRQ0			0x00000001
#define JTAG_CPU_IRQ_ADDR		0xf9400000

#define SECTOR_SIZE		(1024 * 4)		// KB
#define	BLOCK_SIZE		(1024 * 64)		// KB
#define PAGE_SIZE		256				// Byte
#define	CMD_CE			0xC7			// Chip Erase
#define CMD_BE			0xD8			// Block Erase
#define CMD_SE			0x20			// Sector Erase

#define	BINNUM		4

// ====================================================================================================
// Initial (Default Value)
// ====================================================================================================
#define INIFILE					_T(".\\ecm.ini")

#define SEC_WININFO				_T("WinInfo")

#define KEY_DOWNDLGLEFT			_T("DownloaderDlgLeft")
#define KEY_DOWNDLGTOP			_T("DownloaderDlgTop")

#define DEF_DOWNDLGLEFT			0
#define DEF_DOWNDLGTOP			0

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

// Download
// ----------------------------------------------------------------------------------------------------
#define DEF_BINUSE0			0
#define DEF_BINUSE1			0
#define DEF_BINUSE2			0
#define DEF_BINUSE3			0
#define DEF_BINPATH0		_T("")
#define DEF_BINPATH1		_T("")
#define DEF_BINPATH2		_T("")
#define DEF_BINPATH3		_T("")
#define	DEF_BINSECBGN0		0
#define	DEF_BINSECBGN1		0
#define	DEF_BINSECBGN2		0
#define	DEF_BINSECBGN3		0
#define DEF_TABSET			4


// Download
// ----------------------------------------------------------------------------------------------------
#define SEC_DOWN				_T("Download")
#define	KEY_BINUSE0				_T("BinUse0")
#define	KEY_BINUSE1				_T("BinUse1")
#define	KEY_BINUSE2				_T("BinUse2")
#define	KEY_BINUSE3				_T("BinUse3")
#define KEY_BINPATH0			_T("BinPath0")
#define KEY_BINPATH1			_T("BinPath1")
#define KEY_BINPATH2			_T("BinPath2")
#define KEY_BINPATH3			_T("BinPath3")
#define KEY_BINSECBGN0			_T("BinSecBgn0")
#define KEY_BINSECBGN1			_T("BinSecBgn1")
#define KEY_BINSECBGN2			_T("BinSecBgn2")
#define KEY_BINSECBGN3			_T("BinSecBgn3")
#define KEY_TABSET				_T("TabSet")

#define KEY_673BUILDOPTION_COMPILE		_T("673BuildOptionCompile")
#define KEY_673BUILDOPTION_MODE			_T("673BuildOptionMode")
#define KEY_673BUILDOPTION_DISASSEMBLE	_T("673BuildOptionDisassemble")
#define KEY_673BUILDOPTION_SECTION		_T("673BuildOptionSection")
#define KEY_673BUILDOPTION_ETHERNET		_T("673BuildOptionEthernet")
#define KEY_673BUILDOPTION_WIFI			_T("673BuildOptionWifi")
#define KEY_673BUILDOPTION_ONVIF		_T("673BuildOptionOnvif")
#define KEY_673BUILDOPTION_ACTIVEX		_T("673BuildOptionActiveX")

#define KEY_673DOWNOPTION_COM			_T("673DownOptionCom")
#define KEY_673DOWNOPTION_SIZE			_T("673DownOptionSize")
#define KEY_673DOWNOPTION_USERADDR		_T("673DownOptionUseraddr")
#define KEY_673DOWNOPTION_BOOTADDR		_T("673DownOptionBootaddr")
#define KEY_673DOWNOPTION_MACADDR		_T("673DownOptionMacaddr")

#define KEY_673SECTIONWRITE_DONGLE1		_T("673SectionWriteDongle1")
#define KEY_673SECTIONWRITE_DONGLE2		_T("673SectionWriteDongle2")
#define KEY_673SECTIONWRITE_DONGLE3		_T("673SectionWriteDongle3")
#define KEY_673SECTIONWRITE_DONGLE4		_T("673SectionWriteDongle4")
#define KEY_673SECTIONWRITE_DONGLE5		_T("673SectionWriteDongle5")
#define KEY_673SECTIONWRITE_DONGLE6		_T("673SectionWriteDongle6")
#define KEY_673SECTIONWRITE_DONGLE7		_T("673SectionWriteDongle7")
#define KEY_673SECTIONWRITE_DONGLE8		_T("673SectionWriteDongle8")
#define KEY_673SECTIONWRITE_SELECTBIN1	_T("673SectionWriteSelectBin1")
#define KEY_673SECTIONWRITE_SELECTBIN2	_T("673SectionWriteSelectBin2")
#define KEY_673SECTIONWRITE_SELECTBIN3	_T("673SectionWriteSelectBin3")
#define KEY_673SECTIONWRITE_SELECTBIN4	_T("673SectionWriteSelectBin4")
#define KEY_673SECTIONWRITE_SELECTBIN5	_T("673SectionWriteSelectBin5")
#define KEY_673SECTIONWRITE_SELECTBIN6	_T("673SectionWriteSelectBin6")
#define KEY_673SECTIONWRITE_SELECTBIN7	_T("673SectionWriteSelectBin7")
#define KEY_673SECTIONWRITE_SELECTBIN8	_T("673SectionWriteSelectBin8")

#define KEY_EISCPATH			_T("EISCCtudioPath")
#define KEY_EDITERPATH			_T("EditerPath")
#define KEY_UARTBUFFER			_T("UartBuffer")
#define KEY_AUTOBUILD			_T("AutoBuild")

static CString KEY_BINUSE[BINNUM] = { KEY_BINUSE0, KEY_BINUSE1, KEY_BINUSE2, KEY_BINUSE3 };
static CString KEY_BINPATH[BINNUM] = { KEY_BINPATH0, KEY_BINPATH1, KEY_BINPATH2, KEY_BINPATH3 };
static CString KEY_BINSECBGN[BINNUM] = { KEY_BINSECBGN0, KEY_BINSECBGN1, KEY_BINSECBGN2, KEY_BINSECBGN3 };

// EN673 Build Option
// Compile Option - Compile
#define NUM_673BUILDOPTION_COMPILE		7
#define DEF_673BUILDOPTION_COMPILE		0
static CString CBO_673BUILDOPTION_COMPILE[NUM_673BUILDOPTION_COMPILE] = {
	_T("make all"),		// 0
	_T("make boot"),	// 1
	_T("make cpu0"),	// 2
	_T("make cpu1"),	// 3
	_T("make install"),	// 4
	_T("all clean"),	// 5
	_T("none")			// 6
};
// Compile Option - Mode
#define NUM_673BUILDOPTION_MODE	3
#define	DEF_673BUILDOPTION_MODE	0
static CString CBO_673BUILDOPTION_MODE[NUM_673BUILDOPTION_MODE] = {
	_T("release"),	// 0
	_T("debug"),	// 1
	_T("trace")		// 2
};
// Compile Option - Disassemble (n = 0, y = 1)
#define DEF_673BUILDOPTION_DISASSEMBLE	0
#define DEF_673BUILDOPTION_SECTION		0
// Application Option (n = 0, y = 1)
#define DEF_673BUILDOPTION_ETHERNET		1	// Ethernet
#define DEF_673BUILDOPTION_WIFI			0	// Wi-Fi
#define DEF_673BUILDOPTION_ONVIF		0	// ONVIF
#define DEF_673BUILDOPTION_ACTIVEX		0	// ActiveX

static int DEF_BINUSE[BINNUM] = { DEF_BINUSE0, DEF_BINUSE1, DEF_BINUSE2, DEF_BINUSE3 };
static CString DEF_BINPATH[BINNUM] = { DEF_BINPATH0, DEF_BINPATH1, DEF_BINPATH2, DEF_BINPATH3 };
static int DEF_BINSECBGN[BINNUM] = { DEF_BINSECBGN0, DEF_BINSECBGN1, DEF_BINSECBGN2, DEF_BINSECBGN3 };

// Download Option - JTAG(0)/SPI(1)
#define NUM_673DOWNOPTION_COM			2	// JTAG, SPI
#define DEF_673DOWNOPTION_COM			0
#define DEF_673DOWNOPTION_SIZE			16
#define DEF_673DOWNOPTION_USERADDR		_T("0xFFF000")	// Flash Size - 4KB 지만 사이즈조차 읽어지지 않으면 0xFFF000 을 default로 
#define DEF_673DOWNOPTION_BOOTADDR		_T("0x10000")
#define DEF_673DOWNOPTION_MACADDR		_T("00:00:00:00:00:00")

// Section Write
#define NUM_673SECTIONWRITE_DONGLE			2	// Uncheck, Check
#define DEF_673SECTIONWRITE_DONGLE1			0
#define DEF_673SECTIONWRITE_DONGLE2			0
#define DEF_673SECTIONWRITE_DONGLE3			0
#define DEF_673SECTIONWRITE_DONGLE4			0
#define DEF_673SECTIONWRITE_DONGLE5			0
#define DEF_673SECTIONWRITE_DONGLE6			0
#define DEF_673SECTIONWRITE_DONGLE7			0
#define DEF_673SECTIONWRITE_DONGLE8			0

#define NUM_673SECTIONWRITE_SELECTBIN		4
#define DEF_673SECTIONWRITE_SELECTBIN1		0
#define DEF_673SECTIONWRITE_SELECTBIN2		0
#define DEF_673SECTIONWRITE_SELECTBIN3		0
#define DEF_673SECTIONWRITE_SELECTBIN4		0
#define DEF_673SECTIONWRITE_SELECTBIN5		0
#define DEF_673SECTIONWRITE_SELECTBIN6		0
#define DEF_673SECTIONWRITE_SELECTBIN7		0
#define DEF_673SECTIONWRITE_SELECTBIN8		0

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


// Platform
// ----------------------------------------------------------------------------------------------------
enum {
	EN673,
#if INSERT_EN674
	EN674,
#endif
	PLATFORM_END
};


// Struct
typedef struct tagBINFILE
{
	BOOL	bBinUse;		// User Setting
	CString	strBinPath;		// User Setting
	UINT	uiSectorBgn;	// User Setting
	UINT	uiSectorEnd;
	UINT	uiSectorNum;
	CString	strMkPath;
	CString	strEpxPath;
	CString strConPath;
} BINFILE;


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
BOOL	ShowOpenFileDlg(CString* strPath, CString strDefExt, CString strFilter, CWnd* pWnd, CString strStartPath = _T(""));
BOOL	ShowSaveFileDlg(CString *strPath, CString strDefExt, CString strFilter, CWnd* pWnd, CString strStartPath = _T(""));

UINT32 jtag_htonl(UINT32 n);

// Ini File
// Read
int ReadIni(CString strSector, CString strKey, int iDefault);
CString ReadIni(CString strSector, CString strKey, CString strDefault);
//Write
void WriteIni(CString strSector, CString strKey, CString strData);
void WriteIni(CString strSector, CString strKey, int iData);

void Wait(DWORD deMillisecond);
void ProcessWindowMessage();


void DrawWinBg(CWnd* pWnd, CBitmap* bmpBg, const CString& strTitle, BOOL bLogoOn = FALSE);// Draw Window BackGround
void Trace(char* szFormat, ...);