//
// Created by Gengxin Gu on 16/5/9.
//

#include "GOGLContext.h"
#if defined(GX_OPENGL)
#include "GApplication.h"
#include "GLog.h"
#include "GThread.h"
#include "GContext.h"

#if defined(GX_OS_WINDOWS)
#include <Windows.h>

#define M_OS_WND(p) GX_CAST_R(HWND,p)

static void ConfigDC(HDC dc)
{
	GApplication::Delegate* dge = GApplication::sharedDelegate();
	int depth = (int)dge->windowsSuggestedDepth();
	int stencil = (int)dge->windowsSuggestedStencil();
	int multiSamples = (int)dge->windowsSuggestedSamples();

	int		pixelFormat;			// 保存查找匹配的结果
	PIXELFORMATDESCRIPTOR pfd;

	if (!wglChoosePixelFormatARB) {
		wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
	}
	GX_ASSERT(wglChoosePixelFormatARB != NULL);

	int iAttributes[] = {
		WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
		WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
		WGL_COLOR_BITS_ARB, 24,
		WGL_ALPHA_BITS_ARB, 8,
		WGL_DEPTH_BITS_ARB, depth,
		WGL_STENCIL_BITS_ARB, stencil,
		WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
		WGL_SAMPLE_BUFFERS_ARB, multiSamples>1 ? GL_TRUE : GL_FALSE,
		WGL_SAMPLES_ARB, multiSamples, // Multi-Sampling的测试数量
		0, 0 };
	float fAttributes[] = { 0, 0 };

	UINT numFormats = 0;

	BOOL valid = wglChoosePixelFormatARB(dc, iAttributes, fAttributes, 1, &pixelFormat, &numFormats);

	GX_ASSERT(valid || numFormats != 0);

	DescribePixelFormat(dc, pixelFormat, sizeof(pfd), &pfd);

	SetPixelFormat(dc, pixelFormat, &pfd);
}

#elif defined(GX_OS_IPHONE)
#import <UIKit/UIKit.h>
#import <OpenGLES/EAGL.h>
#import <OpenGLES/EAGLDrawable.h>

#elif defined(GX_OS_MACOSX)
#import <Cocoa/Cocoa.h>

static NSOpenGLPixelFormat* CreatePF()
{
    NSOpenGLPixelFormat* pixelFormat=nil;
    GApplication::Delegate* appDge=GApplication::sharedDelegate();
    uint32_t depth=(uint32_t)appDge->windowsSuggestedDepth();
    uint32_t samples=(uint32_t)appDge->windowsSuggestedSamples();
    uint32_t stencil=(uint32_t)appDge->windowsSuggestedStencil();
    if (samples>0) {
        NSOpenGLPixelFormatAttribute attribs[] =
        {
            NSOpenGLPFAAccelerated,
            NSOpenGLPFAClosestPolicy,
            //NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFAColorSize, 24,
            NSOpenGLPFAAlphaSize, 8,
            NSOpenGLPFADepthSize, depth,
            NSOpenGLPFAStencilSize, stencil,
            NSOpenGLPFAMultisample, 1,
            NSOpenGLPFASampleBuffers, 1,
            NSOpenGLPFASamples, samples,
            NSOpenGLPFANoRecovery,
            0
        };
        pixelFormat = [[[NSOpenGLPixelFormat alloc] initWithAttributes:attribs] autorelease];
    }
    if (!pixelFormat) {
        NSOpenGLPixelFormatAttribute attribs[] =
        {
            NSOpenGLPFAAccelerated,
            NSOpenGLPFAClosestPolicy,
            //NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFAColorSize, 24,
            NSOpenGLPFAAlphaSize, 8,
            NSOpenGLPFADepthSize, depth,
            NSOpenGLPFAStencilSize, stencil,
            NSOpenGLPFASampleBuffers, 0,
            NSOpenGLPFANoRecovery,
            0
        };
        pixelFormat = [[[NSOpenGLPixelFormat alloc] initWithAttributes:attribs] autorelease];
    }
    return pixelFormat;
}

#elif defined(GX_OS_ANDROID)

static EGLDisplay 	g_Display=EGL_NO_DISPLAY;
static EGLConfig 	g_Config=NULL;
static EGLSurface 	g_Surface=EGL_NO_SURFACE;
static EGLContext 	g_Context=EGL_NO_CONTEXT;

static void CreateDC()
{
	if(g_Display==EGL_NO_DISPLAY) {
		GApplication::Delegate* appDge=GApplication::sharedDelegate();
		EGLint depth = (EGLint)appDge->windowsSuggestedDepth();
		EGLint stencil = (EGLint)appDge->windowsSuggestedStencil();
		EGLint samples = (EGLint)appDge->windowsSuggestedSamples();

		{
			EGLint attribs[] = {
				EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
				EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
				EGL_BLUE_SIZE, 8,
				EGL_GREEN_SIZE, 8,
				EGL_RED_SIZE, 8,
				EGL_ALPHA_SIZE, 8,
				EGL_DEPTH_SIZE, depth,
				EGL_STENCIL_SIZE, stencil,
				EGL_SAMPLES, samples,
				EGL_NONE };
			EGLint numConfigs;
			g_Display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
			eglInitialize(g_Display, 0, 0);

			if(!eglChooseConfig(g_Display, attribs, &g_Config, 1, &numConfigs) || numConfigs==0) {
				EGLint attChanged[][6] = {
					{ EGL_DEPTH_SIZE, 0,EGL_STENCIL_SIZE, stencil,EGL_SAMPLES, samples, },
					{ EGL_DEPTH_SIZE, depth,EGL_STENCIL_SIZE, 0,EGL_SAMPLES, samples, },
					{ EGL_DEPTH_SIZE, depth,EGL_STENCIL_SIZE, stencil,EGL_SAMPLES, 0, },

					{ EGL_DEPTH_SIZE, 0,EGL_STENCIL_SIZE, 0,EGL_SAMPLES, samples, },
					{ EGL_DEPTH_SIZE, 0,EGL_STENCIL_SIZE, stencil,EGL_SAMPLES, 0, },
					{ EGL_DEPTH_SIZE, depth,EGL_STENCIL_SIZE, 0,EGL_SAMPLES, 0, },

					{ EGL_DEPTH_SIZE, 0,EGL_STENCIL_SIZE, 0,EGL_SAMPLES, 0, },
				};
				for(int i=0;i<sizeof(attChanged)/sizeof(attChanged[0]);++i) {
					for(int j=0;j<6;j++) {
						attribs[sizeof(attribs)/sizeof(attribs[0])-1-6+j]=attChanged[i][j];
					}
					if(eglChooseConfig(g_Display, attribs, &g_Config, 1, &numConfigs) && numConfigs) {
						break;
					}
				}
			}
		}
	}
}

void GOGLContext::pushOSHandle(EGLSurface surface,EGLContext context)
{
    OSHandle handle;
    handle.surface=surface;
    handle.context=context;
    m_OSHandles.add(handle);

    eglMakeCurrent(g_Display, surface, surface, context);

	GX_LOG_P2(PrioINFO,"GOGLContext","pushOSHandle %p %p",surface,context);
}

void GOGLContext::popOSHandle()
{
	GX_LOG_W(PrioINFO,"GOGLContext","popOSHandle");
    if(m_OSHandles.getCount()>0) {
        OSHandle& handle=m_OSHandles.last();
        eglMakeCurrent(g_Display, handle.surface, handle.surface, handle.context);
        m_OSHandles.removeLast();
    }
    else {
        eglMakeCurrent(g_Display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    }
}

#endif

#include "GXGObject.h"

//不用在这里初始化
GOGLContext::GOGLContext()
{
}
//不用在这里反初始化
GOGLContext::~GOGLContext()
{
}
//在这里初始化
bool GOGLContext::create(GWindow* win)
{
#if defined(GX_OS_WINDOWS)
	static bool g_GLEWInit = GX::GLEWInit();
	if(!g_GLEWInit) {
		return false;
	}
#endif
	m_Window = win;

#if defined(GX_OS_WINDOWS)
    m_DC = ::GetDC(M_OS_WND(m_Window->getOSWindow()));
    ConfigDC(m_DC);
    m_Context = ::wglCreateContext(m_DC);
    //shared
    GWindow* aw = GApplication::shared()->firstWindow();
    if (aw && aw != m_Window) {
        wglShareLists(((GOGLContext*)&aw->m_Context)->m_Context, m_Context);
    }
#elif defined(GX_OS_IPHONE)
    EAGLSharegroup* group=nil;
    //shared
    GWindow* aw = GApplication::shared()->firstWindow();
    if (aw && aw != m_Window) {
        group=GX_CAST_R(EAGLContext*, GX_CAST_R(GOGLContext*, &aw->m_Context)->m_Context).sharegroup;
    }
    m_Context=[[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2 sharegroup:group];
    [EAGLContext setCurrentContext:GX_CAST_R(EAGLContext*, m_Context)];
    
    glGenFramebuffers(1, &m_DefaultFramebuffer);
    glGenRenderbuffers(1, &m_ColorRenderbuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_DefaultFramebuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_ColorRenderbuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_ColorRenderbuffer);
    
    GLint samples=(GLint)GApplication::sharedDelegate()->windowsSuggestedSamples();
    
    if (samples>0) {
        GLint maxSamplesAllowed;
        glGetIntegerv(GL_MAX_SAMPLES_APPLE, &maxSamplesAllowed);
        if (samples > maxSamplesAllowed) {
            samples=maxSamplesAllowed;
        }
    }
    if (samples>0) {
        glGenFramebuffers(1, &m_SaaFramebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, m_SaaFramebuffer);
        
        glGenRenderbuffers(1, &m_SaaRenderbuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, m_SaaRenderbuffer);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_SaaRenderbuffer);
    }
    else {
        m_SaaFramebuffer=0;
        m_SaaRenderbuffer=0;
    }
    m_Samples=samples;
    
    glGenRenderbuffers(1, &m_DepthRenderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_DepthRenderbuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_DepthRenderbuffer);
    
    [EAGLContext setCurrentContext:nil];
    
    resize(0, 0);

#elif defined(GX_OS_MACOSX)
    NSOpenGLPixelFormat *pixelFormat=nil;
    NSOpenGLContext* shared=nil;
    //shared
    GWindow* aw = GApplication::shared()->firstWindow();
    if (aw && aw != m_Window) {
        shared=GX_CAST_R(NSOpenGLContext*, GX_CAST_R(GOGLContext*, &aw->m_Context)->m_Context);
        pixelFormat=shared.pixelFormat;
    }
    else {
        pixelFormat=CreatePF();
        shared=nil;
    }
    
    m_Context=[[NSOpenGLContext alloc] initWithFormat:pixelFormat shareContext:shared];
    [GX_CAST_R(NSOpenGLContext*, m_Context) setView:GX_CAST_R(NSView*, m_Window->getOSWindow())];
    [GX_CAST_R(NSOpenGLContext*, m_Context) update];
#elif defined(GX_OS_ANDROID)
	CreateDC();

	EGLint format;
	eglGetConfigAttrib(g_Display, g_Config, EGL_NATIVE_VISUAL_ID, &format);
	ANativeWindow_setBuffersGeometry(win->m_OSWin, 0, 0, format);

	m_Surface = eglCreateWindowSurface(g_Display, g_Config, win->m_OSWin, NULL);

	const EGLint attribs_context[] = {
			EGL_CONTEXT_CLIENT_VERSION, 2,
			EGL_NONE
	};
	EGLContext shared = g_Context;
	if (shared == EGL_NO_CONTEXT) {
		GWindow *aw = GApplication::shared()->firstWindow();
		if (aw && aw != m_Window) {
			shared = GX_CAST_R(EGLContext, GX_CAST_R(GOGLContext * , &aw->m_Context)->m_Context);
		}
	}
	m_Context = eglCreateContext(g_Display, g_Config, shared, attribs_context);

	if (g_Surface==EGL_NO_SURFACE) {
		g_Surface = m_Surface;
		g_Context = m_Context;
	}
#elif defined(GX_OS_QT)
    m_Context=new QOpenGLContext();
    m_Context->setFormat(m_Window->m_OSWin->format());
    GWindow *aw = GApplication::shared()->firstWindow();
    if (aw && aw != m_Window) {
        m_Context->setShareContext(GX_CAST_R(GOGLContext* , &aw->m_Context)->m_Context);
    }
    bool res=m_Context->create();
    res=m_Context->makeCurrent(m_Window->m_OSWin);
    initializeOpenGLFunctions();
    m_Context->doneCurrent();
#endif

#if defined(GX_OS_ANDROID)
    m_OSHandles.removeAll();
#else
    m_ContextMakeCount=0;
#endif
	return true;
}
//在这里反初始化
void GOGLContext::destroy()
{
#if defined(GX_OS_ANDROID)
    m_OSHandles.removeAll();
#else
    m_ContextMakeCount=0;
#endif
#if defined(GX_OS_WINDOWS)
	if (m_Context) {
		wglDeleteContext(m_Context);
		m_Context = NULL;
	}
	if (m_DC) {
		::ReleaseDC(M_OS_WND(m_Window->getOSWindow()), m_DC);
		m_DC = NULL;
	}
#elif defined(GX_OS_APPLE)
#if defined(GX_OS_IPHONE)
    [EAGLContext setCurrentContext:GX_CAST_R(EAGLContext*, m_Context)];
    
    if (m_DefaultFramebuffer) {
        glDeleteFramebuffers(1, &m_DefaultFramebuffer);
        m_DefaultFramebuffer = 0;
    }
    if (m_ColorRenderbuffer) {
        glDeleteRenderbuffers(1, &m_ColorRenderbuffer);
        m_ColorRenderbuffer = 0;
    }
    if (m_DepthRenderbuffer) {
        glDeleteRenderbuffers(1, &m_DepthRenderbuffer);
        m_DepthRenderbuffer = 0;
    }
    if (m_SaaFramebuffer) {
        glDeleteFramebuffers(1, &m_SaaFramebuffer);
        m_SaaFramebuffer = 0;
    }
    if (m_SaaRenderbuffer) {
        glDeleteRenderbuffers(1, &m_SaaRenderbuffer);
        m_SaaRenderbuffer = 0;
    }
    
    [EAGLContext setCurrentContext:nil];
#endif
    [GX_CAST_R(id, m_Context) release];
    m_Context=NULL;
#elif defined(GX_OS_ANDROID)
	if(m_Context!=EGL_NO_CONTEXT) {
		if(m_Context!=g_Context) {
			eglDestroyContext(g_Display, m_Context);
		}
		m_Context=EGL_NO_CONTEXT;
	}
	if(m_Surface!=EGL_NO_SURFACE) {
		if(m_Surface!=g_Surface) {
			eglDestroySurface(g_Display, m_Surface);
		}
		m_Surface=EGL_NO_SURFACE;
	}
#elif defined(GX_OS_QT)
    //delete m_Context;
    m_Context=NULL;
#endif
}

#if defined(GX_OS_ANDROID)
void GOGLContext::androidDestroy()
{
	GOGLContext::destroy();
}
void GOGLContext::androidRecreate(GWindow* win)
{
	GOGLContext::create(win);
}
#endif

bool GOGLContext::resize(gfloat32 width,gfloat32 height)
{
#if defined(GX_OS_WINDOWS)
	return true;
#elif defined(GX_OS_IPHONE)
    if(m_BackingWidth>0 && m_BackingHeight>0 && width == m_BackingWidth && height == m_BackingHeight) {
        return true;
    }
    [EAGLContext setCurrentContext:GX_CAST_R(EAGLContext*, m_Context)];
    
    glBindRenderbuffer(GL_RENDERBUFFER, m_ColorRenderbuffer);
    [GX_CAST_R(EAGLContext*, m_Context) renderbufferStorage:GL_RENDERBUFFER
                                               fromDrawable:(id<EAGLDrawable>)GX_CAST_R(UIView*, m_Window->m_OSWin).layer];
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &m_BackingWidth);
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &m_BackingHeight);
    
    if (m_SaaFramebuffer)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_SaaFramebuffer);
        
        glBindRenderbuffer(GL_RENDERBUFFER, m_SaaRenderbuffer);
        glRenderbufferStorageMultisampleAPPLE(GL_RENDERBUFFER, m_Samples, GL_RGBA8_OES, m_BackingWidth, m_BackingHeight);
        
        glBindRenderbuffer(GL_RENDERBUFFER, m_DepthRenderbuffer);
        glRenderbufferStorageMultisampleAPPLE(GL_RENDERBUFFER, m_Samples, GL_DEPTH_COMPONENT24_OES, m_BackingWidth, m_BackingHeight);
    }
    else {
        glBindRenderbuffer(GL_RENDERBUFFER, m_DepthRenderbuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24_OES, m_BackingWidth, m_BackingHeight);
    }
    
    bool res=glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
    
    [EAGLContext setCurrentContext:nil];
    
    return res;
#elif defined(GX_OS_MACOSX)
    [GX_CAST_R(NSOpenGLContext*, m_Context) update];
    return true;
#elif defined(GX_OS_ANDROID)
	if (m_Surface != EGL_NO_SURFACE) {
		if(m_Surface==g_Surface) {
			eglDestroySurface(g_Display, m_Surface);
			m_Surface = eglCreateWindowSurface(g_Display, g_Config, m_Window->m_OSWin, NULL);
			g_Surface=m_Surface;
		}
		else {
			eglDestroySurface(g_Display, m_Surface);
			m_Surface = eglCreateWindowSurface(g_Display, g_Config, m_Window->m_OSWin, NULL);
		}
	}
	return true;
#elif defined(GX_OS_QT)
    GX_UNUSED(width)
    GX_UNUSED(height)
    return true;
#endif
}

bool GOGLContext::renderCheck()
{
#if defined(GX_OS_ANDROID)
    return m_Surface != EGL_NO_SURFACE;
#else
	return true;
#endif
}

void GOGLContext::renderBegin()
{
	makeCurrent();

#if defined(GX_OS_IPHONE)
	if (m_SaaFramebuffer) {
		glBindFramebuffer(GL_FRAMEBUFFER, m_SaaFramebuffer);
	}
	else {
		glBindFramebuffer(GL_FRAMEBUFFER, m_DefaultFramebuffer);
	}
#endif

	glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void GOGLContext::setViewport(float x, float y, float w, float h, float scale)
{
	glViewport((GLint)(x*scale), (GLint)(y*scale), (GLint)(w*scale), (GLint)(h*scale));
}

void GOGLContext::renderEnd()
{
#if defined(GX_OS_WINDOWS)
	::SwapBuffers(m_DC);
#elif defined(GX_OS_IPHONE)
	if (m_SaaFramebuffer)
	{
		glBindFramebuffer(GL_READ_FRAMEBUFFER_APPLE, m_SaaFramebuffer);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER_APPLE, m_DefaultFramebuffer);
		glResolveMultisampleFramebufferAPPLE();

		GLenum attachments[] = { GL_COLOR_ATTACHMENT0, GL_DEPTH_ATTACHMENT, GL_STENCIL_ATTACHMENT };
		glDiscardFramebufferEXT(GL_READ_FRAMEBUFFER_APPLE, 3, attachments);
	}
	else
	{
		GLenum attachments[] = { GL_COLOR_ATTACHMENT0, GL_DEPTH_ATTACHMENT };
		glDiscardFramebufferEXT(GL_READ_FRAMEBUFFER_APPLE, 2, attachments);
	}
	glBindRenderbuffer(GL_RENDERBUFFER, m_ColorRenderbuffer);
	[GX_CAST_R(EAGLContext*,m_Context) presentRenderbuffer:GL_RENDERBUFFER];
#elif defined(GX_OS_MACOSX)
	[GX_CAST_R(NSOpenGLContext*,m_Context) flushBuffer];
#elif defined(GX_OS_ANDROID)
	eglSwapBuffers(g_Display, m_Surface);
#elif defined(GX_OS_QT)
	m_Context->swapBuffers(m_Window->m_OSWin);
#endif
	makeClear();
}

void GOGLContext::makeCurrent()
{
#if defined(GX_OS_ANDROID)
    pushOSHandle(m_Surface,m_Context);
#else
    if(m_ContextMakeCount==0) {
#if defined(GX_OS_WINDOWS)
        wglMakeCurrent(m_DC, m_Context);
#elif defined(GX_OS_IPHONE)
        [EAGLContext setCurrentContext:GX_CAST_R(EAGLContext*,m_Context)];
#elif defined(GX_OS_MACOSX)
        [GX_CAST_R(NSOpenGLContext*,m_Context) makeCurrentContext];
#elif defined(GX_OS_QT)
        m_Context->makeCurrent(m_Window->m_OSWin);
#endif
    }
    m_ContextMakeCount++;
#endif
}
void GOGLContext::makeClear()
{
#if defined(GX_OS_ANDROID)
    popOSHandle();
#else
    m_ContextMakeCount--;
    if(m_ContextMakeCount==0) {
#if defined(GX_OS_WINDOWS)
        wglMakeCurrent(NULL, NULL);
#elif defined(GX_OS_IPHONE)
        [EAGLContext setCurrentContext:nil];
#elif defined(GX_OS_MACOSX)
        [NSOpenGLContext clearCurrentContext];
#elif defined(GX_OS_QT)
        m_Context->doneCurrent();
#endif
    }
#endif
}

void GOGLContext::readyShader()
{
#if defined(GX_OS_ANDROID)
	pushOSHandle(g_Surface,g_Context);
#else
    makeCurrent();
#endif
}

void GOGLContext::doneShader()
{
#if defined(GX_OS_ANDROID)
    popOSHandle();
#else
    makeClear();
#endif
}

void GOGLContext::readyTexture()
{
#if defined(GX_OS_ANDROID)
	pushOSHandle(g_Surface,g_Context);
#else
    makeCurrent();
#endif
}
void GOGLContext::doneTexture()
{
#if defined(GX_OS_ANDROID)
    popOSHandle();
#else
    makeClear();
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class _OGLLoadTex2DNodeObj : public GObject {
    GX_GOBJECT(_OGLLoadTex2DNodeObj);
public:
    GOGLContext* context;
    GDib* dib;
    GTexture2D::Parameter* param;
    GTexture2D::Node* nodeOut;
};

GX_GOBJECT_IMPLEMENT(_OGLLoadTex2DNodeObj,GObject);

_OGLLoadTex2DNodeObj::_OGLLoadTex2DNodeObj()
{
}

_OGLLoadTex2DNodeObj::~_OGLLoadTex2DNodeObj()
{
    
}

void GOGLContext::loadTexture2DNodeInMT(GObject* obj)
{
    _OGLLoadTex2DNodeObj& nodeObj=*GX_CAST_R(_OGLLoadTex2DNodeObj*, obj);
    
    nodeObj.context->readyTexture();

	GTexture::Handle& handle = nodeObj.nodeOut->getData();
    
	GX_glGenTextures(1, &handle.m_Name);
    
	if (handle.m_Name != 0) {
        
		GX_glBindTexture(GL_TEXTURE_2D, handle.m_Name);
        
        if (nodeObj.param) {
            switch (nodeObj.param->filter) {
                case GX_FILTER_MIN_MAG_POINT:
                {
                    GX_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
                    GX_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
                }
                    break;
                case GX_FILTER_MIN_POINT_MAG_LINEAR:
                {
                    GX_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
                    GX_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
                }
                    break;
                case GX_FILTER_MIN_LINEAR_MAG_POINT:
                {
                    GX_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
                    GX_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
                }
                    break;
                default:
                case GX_FILTER_MIN_MAG_LINEAR:
                {
                    GX_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
                    GX_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
                }
                    break;
            }
            GX_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, nodeObj.param->wrapU );
            GX_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, nodeObj.param->wrapV );
        }
        else {
            GX_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
            GX_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
            GX_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
            GX_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
        }
        
        if (nodeObj.dib->getWidth()%4==0) {
            GX_glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
        }
        else {
            GX_glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        }
        
        bool bTF=true;
        
        switch(nodeObj.dib->getPixelFormat()) {
            case GX::PixelFormatRGBA8888:
            {
                GX_glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, nodeObj.dib->getWidth(),nodeObj.dib->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, nodeObj.dib->getDataPtr());
            }
                break;
            case GX::PixelFormatRGB888:
            {
                GX_glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB,  nodeObj.dib->getWidth(),nodeObj.dib->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, nodeObj.dib->getDataPtr());
            }
                break;
            case GX::PixelFormatRGB565:
            {
                GX_glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB,  nodeObj.dib->getWidth(),nodeObj.dib->getHeight(), 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, nodeObj.dib->getDataPtr());
            }
                break;
            case GX::PixelFormatRGBA4444:
            {
                GX_glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA,  nodeObj.dib->getWidth(),nodeObj.dib->getHeight(), 0, GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4, nodeObj.dib->getDataPtr());
            }
                break;
            case GX::PixelFormatRGBA5551:
            {
                GX_glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA,  nodeObj.dib->getWidth(),nodeObj.dib->getHeight(), 0, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, nodeObj.dib->getDataPtr());
            }
                break;
            case GX::PixelFormatA8:
            {
                GX_glTexImage2D( GL_TEXTURE_2D, 0, GL_ALPHA, nodeObj.dib->getWidth(),nodeObj.dib->getHeight(), 0, GL_ALPHA, GL_UNSIGNED_BYTE, nodeObj.dib->getDataPtr());
            }
                break;
            default:
            {
                bTF=false;
            }
                break;
        }
        
        GX_glBindTexture(GL_TEXTURE_2D, 0);
        
        if (!bTF) {
			GX_glDeleteTextures(1, &handle.m_Name);
			handle.m_Name = 0;
        }
    }
    
    nodeObj.context->doneTexture();

    if (handle.isValid()) {
        nodeObj.nodeOut->m_Context=GX_CAST_R(GContext*, nodeObj.context);
        nodeObj.nodeOut->m_Context->addTextureNodeInMT(nodeObj.nodeOut);
    }
}

bool GOGLContext::loadTexture2DNode(GTexture::Node* node,GDib* dib, GTexture2D::Parameter* param)
{
    _OGLLoadTex2DNodeObj* obj=_OGLLoadTex2DNodeObj::alloc();
    obj->context=this;
    obj->dib=dib;
    obj->param=param;
    obj->nodeOut=node;
    if (GThread::current()->isMain()) {
		loadTexture2DNodeInMT(obj);
    }
    else {
		GThread::current()->getRunLoop()->perform(loadTexture2DNodeInMT, obj, 0, true);
    }
    GO::release(obj);
    
    return node->isValid();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class _OGLUnloadTex2DNodeObj : public GObject {
    GX_GOBJECT(_OGLUnloadTex2DNodeObj);
public:
    GOGLContext* context;
    GTexture2D::Node* nodeOut;
};

GX_GOBJECT_IMPLEMENT(_OGLUnloadTex2DNodeObj,GObject);

_OGLUnloadTex2DNodeObj::_OGLUnloadTex2DNodeObj()
{
}

_OGLUnloadTex2DNodeObj::~_OGLUnloadTex2DNodeObj()
{

}

void GOGLContext::unloadTextureNodeInMT(GObject* obj)
{
    _OGLUnloadTex2DNodeObj& nodeObj=*GX_CAST_R(_OGLUnloadTex2DNodeObj*, obj);
    GTexture::Handle& handle = nodeObj.nodeOut->getData();

    nodeObj.context->readyTexture();

    GX_glDeleteTextures(1, &handle.m_Name);
    handle.m_Name = 0;

    nodeObj.context->doneTexture();

    nodeObj.nodeOut->m_Context->removeTextureNodeInMT(nodeObj.nodeOut);
    nodeObj.nodeOut->m_Context=NULL;
}

void GOGLContext::unloadTextureNodeForContext(GTexture::Node* node)
{
    GTexture::Handle& handle = node->getData();
    GX_glDeleteTextures(1, &handle.m_Name);
    handle.m_Name = 0;
}

void GOGLContext::unloadTextureNode(GTexture::Node* node)
{
    _OGLUnloadTex2DNodeObj* obj=_OGLUnloadTex2DNodeObj::alloc();
    obj->context=this;
    obj->nodeOut=node;

    if (GThread::current()->isMain()) {
        unloadTextureNodeInMT(obj);
    }
    else {
        GThread::current()->getRunLoop()->perform(unloadTextureNodeInMT, obj, 0, true);
    }

    GO::release(obj);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
