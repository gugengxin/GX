#include "GLog.h"
#ifdef GX_DEBUG

#if defined(GX_OS_WINDOWS)
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
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	HANDLE toScreen = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_FONT_INFOEX font;
	font.cbSize = sizeof(font);
	GetCurrentConsoleFontEx(toScreen, FALSE, &font);
	font.dwFontSize.X = 10;
	font.dwFontSize.Y = 14;
	font.FontFamily = FF_DONTCARE;
	_tcscpy(font.FaceName, _T("Lucida Console"));
	SetCurrentConsoleFontEx(toScreen, FALSE, &font);

	_tfreopen_s(&fpDebugOut, _T("CONOUT$"), _T("w"), stdout);
	_tfreopen_s(&fpDebugIn, _T("CONIN$"), _T("r"), stdin);
	//setlocale(LC_CTYPE, "C");
	//setlocale(LC_ALL, "chs");
	return true;
}

static void _ConsoleFina()
{
	fclose(fpDebugOut);
	fclose(fpDebugIn);
	FreeConsole();
}
#define M_CONSOLE_INIT() if(!fpDebugOut) _ConsoleInit()
#else
#define M_CONSOLE_INIT()
#endif

#ifdef GX_OS_ANDROID

#else
static const gchar* PrioString[] = {
	"UNKNOWN",
	"DEFAULT",
	"VERBOSE",
	"DEBUG",
	"INFO",
	"WARN",
	"ERROR",
	"FATAL",
	"SILENT",
};
#endif

#endif


void GLog::Print(gint prio, const gchar* tag, const gchar* fmt, ...)
{
#ifdef GX_DEBUG
	M_CONSOLE_INIT();
#ifdef GX_OS_ANDROID
	va_list args;
	va_start(args, fmt);
	__android_log_vprint(prio, tag, fmt, args);
	va_end(args);
#else
	printf("[%-7s]", PrioString[prio]);
	printf("%s ", tag);
	va_list args;
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);
	printf("\n");
#endif
#endif
}
void GLog::Write(gint prio, const gchar* tag, const gchar* msg)
{
#ifdef GX_DEBUG
	M_CONSOLE_INIT();
#ifdef GX_OS_ANDROID
	__android_log_write(prio, tag, msg);
#else
	printf("[%-7s]%s %s\n", PrioString[prio], tag, msg);
#endif
#endif
}

