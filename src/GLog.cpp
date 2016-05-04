#include "GLog.h"


#if defined(GX_OS_WINDOWS)
#ifdef GX_DEBUG
#include <stdarg.h>
#include <stdio.h>
#include <consoleapi.h>
#include <tchar.h>
#include <locale.h>

static FILE* fpDebugOut = NULL;
static FILE* fpDebugIn = NULL;
static bool _ConsoleInit()
{
	if (!AllocConsole()) {
		return false;
	}
	SetConsoleTitle(_T("GX Console"));
	SetConsoleCP(95001);
	SetConsoleOutputCP(95001);
	_tfreopen_s(&fpDebugOut, _T("CONOUT$"), _T("w"), stdout);
	_tfreopen_s(&fpDebugIn, _T("CONIN$"), _T("r"), stdin);
	_tsetlocale(LC_ALL, _T("chs"));
	return true;
}

static void _ConsoleFina()
{
	fclose(fpDebugOut);
	fclose(fpDebugIn);
	FreeConsole();
}

#endif
#endif

