//
// Created by Gengxin Gu on 16/5/9.
//

#include "GXOpenGL.h"
#if defined(GX_OPENGL)
#include "GLog.h"
#include "GDataArray.h"

#if defined(GX_OS_WINDOWS)
#include "GXCWnd.h"
#elif defined(GX_OS_IPHONE)
#import <OpenGLES/EAGL.h>
#elif defined(GX_OS_MACOSX)
#include <Cocoa/Cocoa.h>
#endif

#include "GXGObject.h"

#if defined(GX_OS_WINDOWS)

/* GLEW_MX
#ifdef GLEW_MX
GLEWContext _glewctx;
#ifdef _WIN32
WGLEWContext _wglewctx;
#elif !defined(__APPLE__) || defined(GLEW_APPLE_GLX)
GLXEWContext _glxewctx;
#endif
//*/

namespace GX
{

	static LRESULT GLEWWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	bool openGLEWInit()
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
					GX_LOG_W(PrioDEBUG, "GXOpenGL::openGLEWInit", "Not support ARB");
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
/* GLEW_MX
#endif
//*/

#elif defined(GX_OS_QT)

namespace GX {

QOpenGLFunctions *openGLFuns()
{
    return QOpenGLContext::currentContext()->functions();
}

}
#endif





namespace GX {
    
    static class _ContextStack : public GPDArray<OGLContext> {
        GX_GOBJECT_DECLARE(_ContextStack, public, public);
    public:
        
    } g_CttStack;
    
    GX_GOBJECT_IMPLEMENT(_ContextStack, GPDArray<OGLContext>);
    
    _ContextStack::_ContextStack()
    {
        
    }
    _ContextStack::~_ContextStack()
    {
        
    }
    
    OGLContext::OGLContext()
    {
#if defined(GX_OS_WINDOWS)
        DC=NULL;
        context=NULL;
#elif defined(GX_OS_APPLE)
        context=NULL;
#elif defined(GX_OS_ANDROID)
        display=EGL_NO_DISPLAY;
        surface=EGL_NO_SURFACE;
        context=EGL_NO_CONTEXT;
#elif defined(GX_OS_QT)
        surface=NULL;
        context=NULL;
#endif
    }
    
#if defined(GX_OS_ANDROID)
    static EGLDisplay g_Display=EGL_NO_DISPLAY;
#endif
    static void openGLContextMakeCurrent(const OGLContext& ctt)
    {
#if defined(GX_OS_WINDOWS)
        wglMakeCurrent(ctt.DC, ctt.context);
#elif defined(GX_OS_IPHONE)
        [EAGLContext setCurrentContext:GX_CAST_R(EAGLContext*,ctt.context)];
#elif defined(GX_OS_MACOSX)
        [GX_CAST_R(NSOpenGLContext*,ctt.context) makeCurrentContext];
#elif defined(GX_OS_ANDROID)
        g_Display=ctt.display;
        eglMakeCurrent(g_Display, ctt.surface, ctt.surface, ctt.context);
#elif defined(GX_OS_QT)
        ctt.context->makeCurrent(ctt.surface);
#endif
    }
    
    static void openGLContextMakeClear()
    {
#if defined(GX_OS_WINDOWS)
        wglMakeCurrent(NULL, NULL);
#elif defined(GX_OS_IPHONE)
        [EAGLContext setCurrentContext:nil];
#elif defined(GX_OS_MACOSX)
        [NSOpenGLContext clearCurrentContext];
#elif defined(GX_OS_ANDROID)
        eglMakeCurrent(g_Display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        g_Display=EGL_NO_DISPLAY;
#elif defined(GX_OS_QT)
        QOpenGLContext* cur=QOpenGLContext::currentContext();
        if(cur) {
            cur->doneCurrent();
        }
#endif
    }
    
    void openGLPushContext(const OGLContext& ctt)
    {
        g_CttStack.add(ctt);
        openGLContextMakeCurrent(ctt);
    }
    void openGLPopContext()
    {
        g_CttStack.removeLast();
        if (g_CttStack.isEmpty()) {
            openGLContextMakeClear();
        }
        else {
            openGLContextMakeCurrent(g_CttStack.last());
        }
    }
    
    
}


#endif
