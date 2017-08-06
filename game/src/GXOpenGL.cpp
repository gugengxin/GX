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

#endif





namespace GX {
    OpenGLContext::OpenGLContext()
    {
#if defined(GX_OS_WINDOWS)
        DC=NULL;
        context=NULL;
        _DC=NULL;
        _context=NULL;
#elif defined(GX_OS_APPLE)
        context=NULL;
        _context=NULL;
#elif defined(GX_OS_ANDROID)
        display=EGL_NO_DISPLAY;
        surface=EGL_NO_SURFACE;
        context=EGL_NO_CONTEXT;
        _display=EGL_NO_DISPLAY;
        _surfaceD=EGL_NO_SURFACE;
        _surfaceR=EGL_NO_SURFACE;
        _context=EGL_NO_CONTEXT;
#elif defined(GX_OS_QT)
        surface=NULL;
        context=NULL;
        _surface=NULL;
        _context=NULL;
#endif
    }
    OpenGLContext::OpenGLContext(
#if defined(GX_OS_WINDOWS)
        HDC   DC_,
        HGLRC context_
#elif defined(GX_OS_APPLE)
        void* context_
#elif defined(GX_OS_ANDROID)
        EGLDisplay display_,
        EGLSurface surface_,
        EGLContext context_
#elif defined(GX_OS_QT)
        QSurface*       surface_,
        QOpenGLContext* context_
#endif
    )
    {
#if defined(GX_OS_WINDOWS)
        DC=DC_;
        context=context_;
        _DC=NULL;
        _context=NULL;
#elif defined(GX_OS_APPLE)
        context=context_;
        _context=NULL;
#elif defined(GX_OS_ANDROID)
        display=display_;
        surface=surface_;
        context=context_;
        _display=EGL_NO_DISPLAY;
        _surfaceD=EGL_NO_SURFACE;
        _surfaceR=EGL_NO_SURFACE;
        _context=EGL_NO_CONTEXT;
#elif defined(GX_OS_QT)
        surface=surface_;
        context=context_;
        _surface=NULL;
        _context=NULL;
#endif
    }
    
    bool OpenGLContext::isValid()
    {
#if defined(GX_OS_WINDOWS)
        return context!=NULL;
#elif defined(GX_OS_APPLE)
        return context!=NULL;
#elif defined(GX_OS_ANDROID)
        return context!=EGL_NO_CONTEXT;
#elif defined(GX_OS_QT)
        return context!=NULL;
#endif
    }
    
    bool OpenGLContext::isCurrent()
    {
#if defined(GX_OS_WINDOWS)
        return context== wglGetCurrentContext();
#elif defined(GX_OS_IPHONE)
        return context==[EAGLContext currentContext];
#elif defined(GX_OS_MACOSX)
        return context==[NSOpenGLContext currentContext];
#elif defined(GX_OS_ANDROID)
        return context==eglGetCurrentContext();
#elif defined(GX_OS_QT)
        return context==QOpenGLContext::currentContext();
#endif
    }
    
    bool OpenGLContext::currentIsNone()
    {
#if defined(GX_OS_WINDOWS)
        return NULL== wglGetCurrentContext();
#elif defined(GX_OS_IPHONE)
        return nil==[EAGLContext currentContext];
#elif defined(GX_OS_MACOSX)
        return nil==[NSOpenGLContext currentContext];
#elif defined(GX_OS_ANDROID)
        return EGL_NO_CONTEXT==eglGetCurrentContext();
#elif defined(GX_OS_QT)
        return NULL==QOpenGLContext::currentContext();
#endif
    }
    
    void OpenGLContext::makeCurrent()
    {
#if defined(GX_OS_WINDOWS)
        _DC=wglGetCurrentDC();
        _context= wglGetCurrentContext();
        wglMakeCurrent(DC, context);
#elif defined(GX_OS_IPHONE)
        _context=[EAGLContext currentContext];
        [EAGLContext setCurrentContext:GX_CAST_R(EAGLContext*,context)];
#elif defined(GX_OS_MACOSX)
        _context=[NSOpenGLContext currentContext];
        [GX_CAST_R(NSOpenGLContext*,context) makeCurrentContext];
#elif defined(GX_OS_ANDROID)
        _display=eglGetCurrentDisplay();
        _surfaceD=eglGetCurrentSurface(EGL_DRAW);
        _surfaceR=eglGetCurrentSurface(EGL_READ);
        _context=eglGetCurrentContext();
        eglMakeCurrent(display, surface, surface, context);
#elif defined(GX_OS_QT)
        _context=QOpenGLContext::currentContext();
        if(_context) {
            _surface=_context->surface();
        }
        else {
            _surface=NULL;
        }
        context->makeCurrent(surface);
#endif
    }
    void OpenGLContext::makeClear()
    {
#if defined(GX_OS_WINDOWS)
        wglMakeCurrent(_DC, _context);
        _DC=NULL;
        _context=NULL;
#elif defined(GX_OS_IPHONE)
        [EAGLContext setCurrentContext:GX_CAST_R(EAGLContext*,context)];
        _context=NULL;
#elif defined(GX_OS_MACOSX)
        if (_context) {
            [GX_CAST_R(NSOpenGLContext*,_context) makeCurrentContext];
            _context=NULL;
        }
        else {
            [NSOpenGLContext clearCurrentContext];
        }
#elif defined(GX_OS_ANDROID)
        eglMakeCurrent(_display, _surfaceD, _surfaceR, _context);
        _display=EGL_NO_DISPLAY;
        _surfaceD=EGL_NO_SURFACE;
        _surfaceR=EGL_NO_SURFACE;
        _context=EGL_NO_CONTEXT;
#elif defined(GX_OS_QT)
        if (_context) {
            _context->makeCurrent(_surface);
            _context=NULL;
            _surface=NULL;
        }
        else {
            context->doneCurrent();
        }
#endif
    }
    

    //////////////////////////////////////////////////////////////////////////
    
    
    OpenGLCullFacer::OpenGLCullFacer()
    {
        
    }
    
    OpenGLCullFacer::~OpenGLCullFacer()
    {
        
    }
    
    void OpenGLCullFacer::setCullFace(DCullFace v)
    {
        DCullFacer::setCullFace(v);
        
        openGLCFUpdate();
    }
    
    bool OpenGLCullFacer::openGLCFNeedReverse()
    {
        return false;
    }
    
    void OpenGLCullFacer::openGLCFUpdate()
    {
        if(OpenGLContext::currentIsNone()) {
            return;
        }
        switch (getCullFace()) {
            case DCullFaceNone:
                GX_glDisable(GL_CULL_FACE);
                break;
            case DCullFaceFront:
                GX_glEnable(GL_CULL_FACE);
                GX_glCullFace(openGLCFNeedReverse()?GL_BACK:GL_FRONT);
                break;
            case DCullFaceBack:
                GX_glEnable(GL_CULL_FACE);
                GX_glCullFace(openGLCFNeedReverse()?GL_FRONT:GL_BACK);
                break;
            default:
                break;
        }
    }
    
    
    //////////////////////////////////////////////////////////////////////////
    
    
    OpenGLBlender::OpenGLBlender()
    {
        
    }
    OpenGLBlender::~OpenGLBlender()
    {
        
    }
    
    void OpenGLBlender::setBlend(DBlend v)
    {
        DBlender::setBlend(v);
        
        openGLBDUpdate();
    }
    
    void OpenGLBlender::openGLBDUpdate()
    {
        if(OpenGLContext::currentIsNone()) {
            return;
        }
        
        switch (getBlend()) {
            case DBlendNone:
                GX_glDisable(GL_BLEND);
                break;
            case DBlendSsaAddD1msa:
                GX_glEnable(GL_BLEND);
                GX_glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
                break;
            case DBlendS1AddD1:
                GX_glEnable(GL_BLEND);
                GX_glBlendFunc(GL_ONE,GL_ONE);
                break;
            default:
                break;
        }
    }
    
}


#endif
