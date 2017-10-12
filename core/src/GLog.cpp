#include "GLog.h"
#ifdef GX_DEBUG
#include <stdarg.h>

#if defined(GX_OS_WINDOWS)
#include <stdio.h>
#include <consoleapi.h>
#include <tchar.h>
#include <locale.h>

static FILE* fpDebugOut = NULL;
static FILE* fpErrorOut = NULL;
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
	_tcscpy_s(font.FaceName, 31, _T("Lucida Console"));
	SetCurrentConsoleFontEx(toScreen, FALSE, &font);

	_tfreopen_s(&fpDebugOut, _T("CONOUT$"), _T("w"), stdout);
	_tfreopen_s(&fpErrorOut, _T("CONOUT$"), _T("w"), stderr);
	_tfreopen_s(&fpDebugIn, _T("CONIN$"), _T("r"), stdin);
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
#include <android/log.h>
#elif defined(GX_OS_QT)
#include <QDebug>
#else
#include <stdio.h>
#endif

#if !defined(GX_OS_ANDROID)
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


void GLog::print(gint prio, const gchar* tag, const gchar* fmt, ...)
{
#ifdef GX_DEBUG
	M_CONSOLE_INIT();
#ifdef GX_OS_ANDROID
	va_list args;
	va_start(args, fmt);
	__android_log_vprint(prio, tag, fmt, args);
	va_end(args);
#elif defined(GX_OS_QT)
    va_list args;
    va_start(args, fmt);
    qDebug()<<"["<<PrioString[prio]<<"]"<<tag<<" "<<QString().vsprintf(fmt,args);
    va_end(args);
#else
    printf("[%s]", PrioString[prio]);
	printf("%s ", tag);
	va_list args;
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);
	printf("\n");
#endif
#else
    GX_UNUSED(prio);
    GX_UNUSED(tag);
    GX_UNUSED(fmt);
#endif
}
void GLog::write(gint prio, const gchar* tag, const gchar* msg)
{
#ifdef GX_DEBUG
	M_CONSOLE_INIT();
#ifdef GX_OS_ANDROID
	__android_log_write(prio, tag, msg);
#elif defined(GX_OS_QT)
    qDebug()<<"["<<PrioString[prio]<<"]"<<tag<<" "<<msg;
#else
    printf("[%s]%s %s\n", PrioString[prio], tag, msg);
#endif
#else
    GX_UNUSED(prio);
    GX_UNUSED(tag);
    GX_UNUSED(msg);
#endif
}

