#pragma once

#include <windows.h>

#define DLG_EN673_CONFIG	_T("Configuration Generator")

// ----------------------------------------------------------------------------------------------------
// Combo Box
// ----------------------------------------------------------------------------------------------------
// Combo Box ÀÎÀÚ¼ö
#define	NUM_MODE			3
#define	NUM_DEVICE			2
#define	NUM_FRAMERATE		4
#define	NUM_RESOLUTION		8
#define	NUM_HWIDTH			2
#define	NUM_VWIDTH			2

#define	NUM_MODEL			11
#define	NUM_CONTROL			2

#define	NUM_KEY				3
#define	NUM_LENS			2
#define	NUM_MORORIZED		5
#define	NUM_IRIS			3
#define	NUM_TDN				3
#define	NUM_CDS				2
#define	NUM_LED				2
#define	NUM_MOTION			2

#define	NUM_SHADE			2
#define	NUM_SAVE			3
#define	NUM_PARUSE			2
#define	NUM_PARSAVE			2

#define	NUM_GPTO			24
#define	NUM_ADC				3

#define	NUM_WIFIMODEL		4

// Image Mode
static CString	CBO_MODE[NUM_MODE] = {
	_T("Sensor"),				// 0
	_T("BT656"),				// 1 -> 2
	_T("BT1120")				// 2 -> 3
};

// Image Device
static CString	CBO_DEVICE[NUM_DEVICE] = {
	_T("No use"),				// 0
	_T("EN332T")				// 1
};

// Image Frame Rate
static CString	CBO_FRAMERATE[NUM_FRAMERATE] = {
	_T("30P"),					// 0
	_T("25P"),					// 1
	_T("60P"),					// 2
	_T("50P")					// 3
};

// Image Resolution
static CString	CBO_RESOLUTION[NUM_RESOLUTION] = {
	_T("1920x1080"),			// 0
	_T("1280x720"),				// 1
	_T("800x600"),				// 2
	_T("704x480"),				// 3
	_T("704x400"),				// 4
	_T("640x480"),				// 5
	_T("640x360"),				// 6
	_T("320x240")				// 7
};

// Image H-Widrh
static CString	CBO_HWIDTH[NUM_HWIDTH] = {
	_T("Disable"),				// 0
	_T("Enable")				// 1
};

// Image V-Widrh
static CString	CBO_VWIDTH[NUM_VWIDTH] = {
	_T("Disable"),				// 0
	_T("Enable")				// 1
};


// Sensor Model
static CString	CBO_MODEL[NUM_MODEL] = {
	_T("MN34210"),			// 0	-> 1
	_T("IMX225"),			// 1	-> 4
	_T("MN34229"),			// 2	-> 11
	_T("MN34420"),			// 3	-> 12
	_T("IMX307"),			// 4	-> 13
	_T("IMX327"),			// 5	-> 14
	_T("IMX291"),			// 6	-> 15
	_T("AR0237CSH"),		// 7	-> 18
	_T("MN34227"),			// 8	-> 21
	_T("OV2718"),			// 9	-> 22
	_T("IMX323")			// 10	-> 24
};

// Sensor Control
static CString	CBO_CONTROL[NUM_CONTROL] = {
	_T("SPI"),					// 0
	_T("TWI")					// 1
};

// ISP Key
static CString	CBO_KEY[NUM_KEY] = {
	_T("ADC"),					// 0
	_T("GPIO"),					// 1
	_T("No use")				// 2
};

// ISP Lens
static CString	CBO_LENS[NUM_LENS] = {
	_T("Fixed Lens"),			// 0
	_T("Motorized Lens"),		// 1
};

// ISP Motorized Model
static CString	CBO_MORORIZED[NUM_MORORIZED] = {
	_T("YT2812"),				// 0
	_T("YT3013"),				// 1
	_T("YT3017"),				// 2
	_T("YT30022"),				// 3
	_T("Custom Lens")			// 4
};

// ISP Iris
static CString	CBO_IRIS[NUM_IRIS] = {
	_T("No use"),				// 0
	_T("KIWI Device"),			// 1
	_T("Micom PWM")				// 2
};

// ISP TDN
static CString	CBO_TDN[NUM_TDN] = {
	_T("1 port 2 state"),		// 0
	_T("1 port 3 state"),		// 1
	_T("2 ports")				// 2
};

// ISP CDS
static CString	CBO_CDS[NUM_CDS] = {
	_T("ADC"),					// 0
	_T("GPIO")					// 1
};

// ISP LED
static CString	CBO_LED[NUM_LED] = {
	_T("LPWM"),					// 0
	_T("GPIO")					// 1
};

// ISP Motion
static CString	CBO_MOTION[NUM_MOTION] = {
	_T("Disable"),				// 0
	_T("Enable"),				// 1
};

// Etc Shard
static CString	CBO_SHADE[NUM_SHADE] = {
	_T("Use"),					// 0
	_T("No use"),				// 1
};

// Etc Save
static CString	CBO_SAVE[NUM_SAVE] = {
	_T("EEPROM"),				// 0
	_T("Flash"),				// 1
	_T("No use")				// 2
};

// Etc Parameter Use
static CString	CBO_PARUSE[NUM_PARUSE] = {
	_T("No use"),				// 0
	_T("Use")					// 1
};

// Etc Parameter Save
static CString	CBO_PARSAVE[NUM_PARSAVE] = {
	_T("No use"),				// 0
	_T("Use")					// 1
};


static CString	CBO_GPIO[NUM_GPTO] = {
	_T("GPIO_00"),				// 0
	_T("GPIO_01"),				// 1
	_T("GPIO_02"),				// 2
	_T("GPIO_03"),				// 3
	_T("GPIO_04"),				// 4
	_T("GPIO_05"),				// 5
	_T("GPIO_06"),				// 6
	_T("GPIO_07"),				// 7
	_T("GPIO_08"),				// 8
	_T("GPIO_09"),				// 9
	_T("GPIO_10"),				// 10
	_T("GPIO_11"),				// 11
	_T("GPIO_12"),				// 12
	_T("GPIO_13"),				// 13
	_T("GPIO_14"),				// 14
	_T("GPIO_15"),				// 15
	_T("GPIO_16"),				// 16
	_T("GPIO_17"),				// 17
	_T("GPIO_18"),				// 18
	_T("GPIO_19"),				// 19
	_T("GPIO_20"),				// 20
	_T("GPIO_21"),				// 21
	_T("GPIO_22"),				// 22
	_T("GPIO_23")				// 23
};


static CString	CBO_ADC[NUM_ADC] = {
	_T("ADC0"),					// 0
	_T("ADC1"),					// 1
	_T("ADC2")					// 2
};


static CString	TR_CBO_ADC[NUM_ADC] = {
	_T("ADC0_RDATr"),			// 0
	_T("ADC1_RDATr"),			// 1
	_T("ADC2_RDATr")			// 2
};


static CString	CBO_WIFIMODEL[NUM_WIFIMODEL] = {
	_T("sd8787"),				// 0
	_T("sd8782"),				// 1
	_T("sd8777"),				// 2
	_T("TICC3100")				// 3
};

// ----------------------------------------------------------------------------------------------------
// Config Generator Base String
// ----------------------------------------------------------------------------------------------------
#define BASE_CONFIG_STRING					_T("export EXTRA_CFLAGS")
#define USING_CONFIG_IMGPATH_SCRIPT_STRING	_T("-DUSING_CONFIG_IMGPATH_SCRIPT")
#define USING_CONFIG_ISP_SCRIPT_STRING		_T("-DUSING_CONFIG_ISP_SCRIPT")
#define USING_CONFIG_GPIO_SCRIPT_STRING		_T("-DUSING_CONFIG_GPIO_SCRIPT")

#define BUILD_COMMANT_STRING		_T("# Build Option")
#define ETHSUPPORT_STRING			_T("export  CONFIG_ETH_SUPPORT")
#define WIFISUPPORT_STRING			_T("export  CONFIG_WIFI_SUPPORT")
#define ONVIFSUPPORT_STRING			_T("export  CONFIG_ONVIF_SUPPORT")
#define ACTIVEXSUPPORT_STRING		_T("export  CONFIG_ACTIVEX_SUPPORT")
#define WIFIMODULE_STRING			_T("export  WIFI_MODULE")

#define IMAGEPATH_COMMANT_STRING	_T("# Image Path settings")
#define INPUTMODE_STRING			_T("-DIMAGE_INPUT_MODE")
#define DIGITAL_STRING				_T("-DUSE_DIGITAL_INPUT")
#define FRAMERATE_STRING			_T("-DDIGITAL_INPUT_FPS")
#define REEOLUTION_STRING			_T("-DDIGITAL_INPUT_RES")
#define HWIDTH_STRING				_T("-DDIGITAL_INPUT_HW")
#define VWIDTH_STRING				_T("-DDIGITAL_INPUT_VW")

#define ISP_COMMANT_STRING			_T("# ISP settings")
#define SENSOR_STRING				_T("-Dmodel_Sens")
#define CONTROL_STRING				_T("-DSENS_CONTROL_MODE")
#define KEY_STRING					_T("-Dmodel_Key")
#define LENS_STRING					_T("-Dmodel_Lens")
#define MORORIZED_STRING			_T("-Dmodel_MAF_Lens")
#define IRIS_STRING					_T("-Dmodel_Iris")
#define TDN_STRING					_T("-Dmodel_Tdn")
#define CDS_STRING					_T("-Dmodel_Cds")
#define LED_STRING					_T("-Dmodel_Led")
#define MOTION_STRING				_T("-Dmodel_MotionOut")
#define SHADE_STRING				_T("-Dmodel_Shade")
#define SAVE_STRING					_T("-Dmodel_Save")
#define PARUSE_STRING				_T("-Dmodel_Par")
#define PARSAVE_STRING				_T("-Dmodel_Par_Save")
#define OPTIONFLAGNUM_STRING		_T("OPTION_FLAG_NO")
#define OPTIONFLAG_STRING			_T("-DOPTION_FLAG_")

#define PERIPHERAL_COMMANT_STRING	_T("# GPIO assign settings")
#define SENSOERESET_STRING			_T("-DGPIO_SENS_RSTN")
#define ISPIRQLED_STRING			_T("-DGPIO_ISP_VI_LED")
#define ENCLED_STRING				_T("-DGPIO_H264_ENC_LED")
#define ICRP0_STRING				_T("-DGPIO_TDN_1")
#define ICRP1_STRING				_T("-DGPIO_TDN_2")
#define FOCUSAP_STRING				_T("-DGPIO_MTR_FCS_AP")
#define FOCUSAM_STRING				_T("-DGPIO_MTR_FCS_AM")
#define FOCUSBP_STRING				_T("-DGPIO_MTR_FCS_BP")
#define FOCUSBM_STRING				_T("-DGPIO_MTR_FCS_BM")
#define ZOOMAP_STRING				_T("-DGPIO_MTR_ZOOM_AP")
#define ZOOMAM_STRING				_T("-DGPIO_MTR_ZOOM_AM")
#define IRLED_STRING				_T("-DGPIO_LED_CTL")
#define ZOOMBP_STRING				_T("-DGPIO_MTR_ZOOM_BP")
#define IRISPWM_STRING				_T("-DGPIO_MPWM")
#define ETHIRQ_STRING				_T("-DGPIO_ETH_IRQ")
#define PERMOTION_STRING			_T("-DGPIO_MOTION")
#define UARTRX1_STRING				_T("-")
#define UARTTX1_STRING				_T("-")
#define I2C2SDA_STRING				_T("-")
#define I2C2SCL_STRING				_T("-")
#define ZOOMBM_STRING				_T("-DGPIO_MTR_ZOOM_BM")
#define SDIO1RESET_STRING			_T("-DGPIO_SDIO1_RST")
#define ETHRESET_STRING				_T("-DGPIO_ETH_RST")
#define AUDIORESET_STRING			_T("-DGPIO_AUD_RST")
#define ADKEY_STRING				_T("-DADC_KEYr")
#define CDSINADC_STRING				_T("-DADC_CDSr")
#define CDSINGPIO_STRING			_T("-DGPIO_CDS_IN")

#define KEY_C_STRING				_T("-DGPIO_KEY_C")
#define KEY_U_STRING				_T("-DGPIO_KEY_U")
#define KEY_D_STRING				_T("-DGPIO_KEY_D")
#define KEY_L_STRING				_T("-DGPIO_KEY_L")
#define KEY_R_STRING				_T("-DGPIO_KEY_R")
