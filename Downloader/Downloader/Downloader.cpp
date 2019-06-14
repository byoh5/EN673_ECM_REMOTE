
// Downloader.cpp : 응용 프로그램에 대한 클래스 동작을 정의합니다.
//

#include "stdafx.h"
#ifdef _DEBUG
#include "vld.h"
#endif
#include "Downloader.h"
#include "DownloaderDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDownloaderApp

BEGIN_MESSAGE_MAP(CDownloaderApp, CWinApp)
	//ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CDownloaderApp 생성

CDownloaderApp::CDownloaderApp()
{
	// 다시 시작 관리자 지원
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CDownloaderApp 개체입니다.

CDownloaderApp theApp;


// CDownloaderApp 초기화

BOOL CDownloaderApp::InitInstance()
{

	CWinApp::InitInstance();



	CDownloaderDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	return FALSE;
}

