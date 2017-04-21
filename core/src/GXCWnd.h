#ifndef GXCWnd_h
#define GXCWnd_h


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
}

#endif

#endif