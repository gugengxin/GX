#pragma once

#include "GXPrefix.h"

#if defined(GX_OS_WINDOWS)
#include <Windows.h>

namespace GX
{
	class CWnd
	{
	public:
		CWnd();
		~CWnd();

		void create(WNDCLASS& wc, DWORD style, DWORD exStyle, RECT& rc, HWND parentWnd);
		void destroy();

		inline HWND getHWND() {
			return m_Wnd;
		}

	private:
		HWND	m_Wnd;
	};

	class CChildWnd
	{
	public:
		CChildWnd();
		~CChildWnd();

		void create(WNDCLASS& wc, DWORD style, DWORD exStyle, RECT& rc, HWND parentWnd);
		void destroy();
		void releaseHWND() {
			m_Wnd = NULL;
		}

		inline HWND getHWND() {
			return m_Wnd;
		}

	private:
		HWND	m_Wnd;
		TCHAR   m_ClsName[33];
	};
}

#endif

