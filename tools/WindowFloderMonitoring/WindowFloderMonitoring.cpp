#include "stdafx.h"
#include "WindowFloderMonitoring.h"  
#include <cassert>  

CFloderMonitoring::CFloderMonitoring() : m_hDir(INVALID_HANDLE_VALUE), m_hThread(NULL)
{
	assert(FILTER_FILE_NAME == FILE_NOTIFY_CHANGE_FILE_NAME);
	assert(FILTER_DIR_NAME == FILE_NOTIFY_CHANGE_DIR_NAME);
	assert(FILTER_ATTR_NAME == FILE_NOTIFY_CHANGE_ATTRIBUTES);
	assert(FILTER_SIZE_NAME == FILE_NOTIFY_CHANGE_SIZE);
	assert(FILTER_LAST_WRITE_NAME == FILE_NOTIFY_CHANGE_LAST_WRITE);
	assert(FILTER_LAST_ACCESS_NAME == FILE_NOTIFY_CHANGE_LAST_ACCESS);
	assert(FILTER_CREATION_NAME == FILE_NOTIFY_CHANGE_CREATION);
	assert(FILTER_SECURITY_NAME == FILE_NOTIFY_CHANGE_SECURITY);

	assert(ACTION_ADDED == FILE_ACTION_ADDED);
	assert(ACTION_REMOVED == FILE_ACTION_REMOVED);
	assert(ACTION_MODIFIED == FILE_ACTION_MODIFIED);
	assert(ACTION_RENAMED_OLD == FILE_ACTION_RENAMED_OLD_NAME);
	assert(ACTION_RENAMED_NEW == FILE_ACTION_RENAMED_NEW_NAME);
}

CFloderMonitoring::~CFloderMonitoring()
{
	Close();
}

bool CFloderMonitoring::Run(LPCTSTR dir, bool bWatchSubtree, DWORD dwNotifyFilter, LPDEALFUNCTION dealfun, LPVOID lParam)
{
	Close();

	m_hDir = CreateFileW(//dir目录不能以'\'结尾，否则监测不到dir目录被删除，不以\结尾，可以检测到（仅限于空目录时）  
		dir,
		FILE_LIST_DIRECTORY,
		FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
		NULL,
		OPEN_EXISTING,
		FILE_FLAG_BACKUP_SEMANTICS,
		NULL
	);
	if (INVALID_HANDLE_VALUE == m_hDir) 
		return false;

	m_bWatchSubtree = bWatchSubtree;
	m_dwNotifyFilter = dwNotifyFilter;
	m_DealFun = dealfun;
	m_DealFunParam = lParam;
	m_bRequestStop = false;

	DWORD ThreadId;
	m_hThread = CreateThread(NULL, 0, Routine, this, 0, &ThreadId);
	if (NULL == m_hThread)
	{
		CloseHandle(m_hDir);
		m_hDir = INVALID_HANDLE_VALUE;
	}

	return NULL != m_hThread;
}

void CFloderMonitoring::Close(DWORD dwMilliseconds)
{
	if (NULL != m_hThread)
	{
		m_bRequestStop = true;
		if (WAIT_TIMEOUT == WaitForSingleObject(m_hThread, dwMilliseconds))
			TerminateThread(m_hThread, 0);
		CloseHandle(m_hThread);
		m_hThread = NULL;
	}
	if (INVALID_HANDLE_VALUE != m_hDir)
	{
		CloseHandle(m_hDir);
		m_hDir = INVALID_HANDLE_VALUE;
	}
}

DWORD WINAPI CFloderMonitoring::Routine(LPVOID lParam)
{
	//XLogError(L"扫描目录监控开始运行");
	CFolderMonitoring& obj = *(CFloderMonitoring*)lParam;
	BYTE buf[2 * (sizeof(FILE_NOTIFY_INFORMATION) + 2 * MAX_PATH) + 2];
	FILE_NOTIFY_INFORMATION* pNotify = (FILE_NOTIFY_INFORMATION *)buf;
	DWORD BytesReturned;
	while (!obj.m_bRequestStop)
	{
		if (ReadDirectoryChangesW(obj.m_hDir,
			pNotify,
			sizeof(buf) - 2,
			obj.m_bWatchSubtree,
			obj.m_dwNotifyFilter,
			&BytesReturned,
			NULL,
			NULL)) // 无限等待，应当使用异步方式  
		{
			for (FILE_NOTIFY_INFORMATION* pFileNotify = pNotify; pFileNotify; )
			{
				WCHAR chName = pFileNotify->FileName[pFileNotify->FileNameLength / 2];
				pFileNotify->FileName[pFileNotify->FileNameLength / 2] = L'\0';

				obj.m_DealFun((ACTION)pFileNotify->Action, pFileNotify->FileName, obj.m_DealFunParam);

				pFileNotify->FileName[pFileNotify->FileNameLength / 2] = chName;

				if (pFileNotify->NextEntryOffset)
					pFileNotify = (PFILE_NOTIFY_INFORMATION)((BYTE*)pFileNotify + pFileNotify->NextEntryOffset);
				else
					pFileNotify = 0;
			}
		}
		else
		{
			obj.m_DealFun((ACTION)ACTION_ERRSTOP, 0, obj.m_DealFunParam);
			break;
		}
	}
	//XLogInfo(L"监控目录函数退出");
	return 0;
}
