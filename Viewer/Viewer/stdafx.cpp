
// stdafx.cpp : ǥ�� ���� ���ϸ� ��� �ִ� �ҽ� �����Դϴ�.
// Viewer.pch�� �̸� �����ϵ� ����� �˴ϴ�.
// stdafx.obj���� �̸� �����ϵ� ���� ������ ���Ե˴ϴ�.

#include "stdafx.h"

int					ConnectSocket;

CViewerDlg*			pViewerDlg;
CViewerSet*			pViewerSet;
CViewerSnap*		pViewerSnap;
CViewerCapture*		pViewerCapture;

CWinThread*			g_pDrawViewerThread;
BOOL				bGraphFlag;