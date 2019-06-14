#pragma once
#include "afxwin.h"
#include "jtag_flash.h"

// CDownDownOption673 대화 상자입니다.

class CDownDownOption673 : public CDialogEx
{
	DECLARE_DYNAMIC(CDownDownOption673)

public:
	CDownDownOption673(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDownDownOption673();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DOWN_DOWNOPTION_673 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CEdit m_Edit_FlashSize;

	CButton m_Radio_JTAG;
	CButton m_Radio_SPI;

	// Flash Read
	afx_msg void OnBnClickedButtonEn673flashread();
	void JTAGFlashRead();

	// Flash Erase
	afx_msg void OnBnClickedButtonEn673flasherase();
	void JTAGFlashErase();

	// Flash Test (함수는 CDownloaderDlg에 있음)
	afx_msg void OnBnClickedButtonEn673flashtest();

	// User Area Read
	afx_msg void OnBnClickedButtonUserarearead();
	void JTAGUserAreaRead();

	// User Area Erase
	afx_msg void OnBnClickedButtonUserareaerase();
	void JTAGUserAreaErase();

	// User Area Write
	afx_msg void OnBnClickedButtonUserareawrite();
	void JTAGUserAreaWrite();
	CEdit m_Edit_UserAddress;
	CEdit m_Edit_BootAddress;

	// Boot Address
	afx_msg void OnEnUpdateEditBootaddress();

	// Mac Address
	afx_msg void OnEnUpdateEditMacaddress1();
	afx_msg void OnEnUpdateEditMacaddress2();
	afx_msg void OnEnUpdateEditMacaddress3();
	afx_msg void OnEnUpdateEditMacaddress4();
	afx_msg void OnEnUpdateEditMacaddress5();
	afx_msg void OnEnUpdateEditMacaddress6();
	void OnEnUpdateEditMacaddress(int iNum);
	afx_msg void OnEnChangeEditMacaddress1();
	afx_msg void OnEnChangeEditMacaddress2();
	afx_msg void OnEnChangeEditMacaddress3();
	afx_msg void OnEnChangeEditMacaddress4();
	afx_msg void OnEnChangeEditMacaddress5();
	afx_msg void OnEnChangeEditMacaddress6();
	void OnEnChangeEditMacaddress(int iNum);
	CEdit m_Edit_MacAddress[6];
	BOOL m_bOnChangeEditMacaddress; // 

	BYTE m_byDeviceSize; // 저장용
	UINT32 m_uiUserAddress;
	UINT32 m_uiBootAddress;
	BYTE m_byMacAddress[6];

	void SetDeviceSize(BYTE byDeviceSize); // MB
	void SetUserAddress(UINT32 uiUserAddress);
	void SetBootAddress(UINT32 uiBootAddress);
	void SetMacAddress(BYTE by1, BYTE by2, BYTE by3, BYTE by4, BYTE by5, BYTE by6);
};
