
// Downloader.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
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


// CDownloaderApp ����

CDownloaderApp::CDownloaderApp()
{
	// �ٽ� ���� ������ ����
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}


// ������ CDownloaderApp ��ü�Դϴ�.

CDownloaderApp theApp;


// CDownloaderApp �ʱ�ȭ

BOOL CDownloaderApp::InitInstance()
{

	CWinApp::InitInstance();



	CDownloaderDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	return FALSE;
}

