//
// Created by Gengxin Gu on 16/5/9.
//

#include "GXOpenGL.h"
#if defined(GX_OPENGL)
#include "GLog.h"

#ifdef GLEW_MX
GLEWContext _glewctx;
#ifdef _WIN32
WGLEWContext _wglewctx;
#elif !defined(__APPLE__) || defined(GLEW_APPLE_GLX)
GLXEWContext _glxewctx;
#endif

#include "GXCWnd.h"

namespace GX
{

	static LRESULT GLEWWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	bool glewInit()
	{
		bool res = false;

		WNDCLASS wndClass;
		memset(&wndClass, 0, sizeof(wndClass));
		wndClass.lpfnWndProc = (WNDPROC)GLEWWndProc;
		wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS;

		GX::CWnd wnd;
		RECT rc = { 0, 0, 1, 1 };
		wnd.create(wndClass, WS_OVERLAPPEDWINDOW, WS_EX_APPWINDOW, rc, NULL);

		HDC hDC = ::GetDC(wnd.getHWND());
		::PIXELFORMATDESCRIPTOR pfd;
		int iPixelFormat = 1;
		HGLRC hRc = NULL;
		if (::SetPixelFormat(hDC, iPixelFormat, &pfd))
		{
			hRc = ::wglCreateContext(hDC);
			if (::wglMakeCurrent(hDC, hRc))
			{
				GLenum retVal = glewInit();
				if (retVal == GLEW_OK) {
					retVal = wglewInit();
				}

				if (!wglewIsSupported("WGLEW_ARB_pixel_format ""WGLEW_ARB_create_context ")) {
					GX_LOG_W(PrioDEBUG, "GXOpenGL::GlewInit", "Not support ARB");
				}

				wglMakeCurrent(NULL, NULL);
				wglDeleteContext(hRc);
				res = (retVal == GLEW_OK);
			}
			wglDeleteContext(hRc);
		}

		::ReleaseDC(wnd.getHWND(), hDC);

		return res;
	}

}
#endif


#if defined(GX_OS_QT)

namespace GX {

QOpenGLFunctions *openGLFuns()
{
    return QOpenGLContext::currentContext()->functions();
}

}
#endif

#endif
