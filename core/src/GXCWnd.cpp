#include "GXCWnd.h"

#if defined(GX_OS_WINDOWS)
#include "GUUID.h"
#include <tchar.h>

namespace GX
{
	CWnd::CWnd()
	{
		m_Wnd = NULL;
	}

	CWnd::~CWnd()
	{
		if (m_Wnd) {
			::DestroyWindow(m_Wnd);
		}
	}

	void CWnd::create(WNDCLASS& wc, DWORD style, DWORD exStyle, RECT& rc, HWND parentWnd)
	{
		wc.hInstance = ::GetModuleHandle(NULL);

		TCHAR cn[33];
		if (!wc.lpszClassName) {
			GUUID uuid;
			_stprintf_s(cn, 33, _T("%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X"),
				(guint32)uuid.m_Bytes[0],
				(guint32)uuid.m_Bytes[1],
				(guint32)uuid.m_Bytes[2],
				(guint32)uuid.m_Bytes[3],
				(guint32)uuid.m_Bytes[4],
				(guint32)uuid.m_Bytes[5],
				(guint32)uuid.m_Bytes[6],
				(guint32)uuid.m_Bytes[7],
				(guint32)uuid.m_Bytes[8],
				(guint32)uuid.m_Bytes[9],
				(guint32)uuid.m_Bytes[10],
				(guint32)uuid.m_Bytes[11],
				(guint32)uuid.m_Bytes[12],
				(guint32)uuid.m_Bytes[13],
				(guint32)uuid.m_Bytes[14],
				(guint32)uuid.m_Bytes[15]);
			wc.lpszClassName = cn;
		}
		::RegisterClass(&wc);

		m_Wnd = ::CreateWindowEx(exStyle,
			wc.lpszClassName,			
			NULL,
			style,
			rc.left,
			rc.top,
			rc.right - rc.left,
			rc.bottom - rc.top,
			parentWnd,
			NULL,				
			wc.hInstance,		
			NULL);
		::UnregisterClass(wc.lpszClassName, wc.hInstance);
	}
	void CWnd::destroy()
	{
		::DestroyWindow(m_Wnd);
		m_Wnd = NULL;
	}
}

#endif
