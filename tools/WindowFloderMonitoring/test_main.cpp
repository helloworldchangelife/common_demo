//使用
#include "stdafx.h"
#include "WindowFloderMonitoring.h"
#include <stdio.h>
#include <locale.h>
#include <assert.h>
#include <tchar.h>
#include <conio.h>

void __stdcall MyDeal(CFloderMonitoring::ACTION act, LPCWSTR file_name, LPVOID lParam)
{
	static CFloderMonitoring::ACTION pre = CFloderMonitoring::ACTION_ERRSTOP;
	switch (act)
	{
	case CFloderMonitoring::ACTION_ADDED:
		XLogInfo(L"add file %s", file_name);
		break;
	case CFloderMonitoring::ACTION_REMOVED:
		XLogInfo(L"removed file %s", file_name);
		break;
	case CFloderMonitoring::ACTION_MODIFIED:
		XLogInfo(L"modified file %s", file_name);
		break;
	case CFloderMonitoring::ACTION_RENAMED_OLD:
		XLogInfo(L"renamed old file %s", file_name);
		break;
	case CFloderMonitoring::ACTION_RENAMED_NEW:
		assert(pre == CFloderMonitoring::ACTION_RENAMED_OLD);
		XLogInfo(L"renamed new file %s", file_name);
		break;
	case CFloderMonitoring::ACTION_ERRSTOP:
	default:
		XLogError(L"unknown action type!!!");
		break;
	}
	pre = act;
}

int main()
{
	LPCTSTR sDir = TEXT("E:\\work"); //监控目录
	DWORD dwNotifyFilter = CFloderMonitoring::FILTER_FILE_NAME | CFloderMonitoring::FILTER_DIR_NAME;

	CFloderMonitoring flodermonitor;
	bool r = flodermonitor.Run(sDir, true, dwNotifyFilter, &MyDeal, 0);
	if (!r)
		return -1;

	_tsetlocale(LC_CTYPE, TEXT("chs"));
	_tprintf_s(TEXT("Watch%s\n"), sDir);
	_tprintf_s(TEXT("Press <q> to quit.\n"));

	while (_getch() != 'q');

	flodermonitor.Close(100);

	return 0;
}
