//
// Created by Gengxin Gu on 16/5/9.
//

#include "GOGLContext.h"
#if defined(GX_OPENGL)
#include "GApplication.h"
#include "GLog.h"
#include "GThread.h"
#include "GContext.h"
#include "GWindow.h"

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

#endif

//Up include other h file
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
	static bool g_GLEWInited = GX::openGLEWInit();
	if(!g_GLEWInited) {
		return false;
	}
#endif
    if (!GBaseContext::create(win)) {
        return false;
    }

#if defined(GX_OS_WINDOWS)
    m_Context.DC = ::GetDC(M_OS_WND(getWindow()->getOSWindow()));
	ConfigDC(m_Context.DC);
	m_Context.context = ::wglCreateContext(m_Context.DC);
    //shared
    GWindow* aw = GWindow::first();
	if (aw && aw != getWindow()) {
		wglShareLists(((GOGLContext*)&aw->m_Context)->m_Context.context, m_Context.context);
    }
#elif defined(GX_OS_IPHONE)
    EAGLSharegroup* group=nil;
    //shared
    GWindow* aw = GWindow::first();
    if (aw && aw != getWindow()) {
        group=GX_CAST_R(EAGLContext*, GX_CAST_R(GOGLContext*, &aw->m_Context)->m_Context.context).sharegroup;
    }
    m_Context.context=[[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2 sharegroup:group];
    [EAGLContext setCurrentContext:GX_CAST_R(EAGLContext*, m_Context.context)];
    
    GLuint oldFB,oldRB;
    GX_glGetIntegerv(GL_FRAMEBUFFER_BINDING, (GLint*)&oldFB);
    GX_glGetIntegerv(GL_RENDERBUFFER_BINDING, (GLint*)&oldRB);
    
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
    
    glBindRenderbuffer(GL_RENDERBUFFER, oldRB);
    glBindFramebuffer(GL_FRAMEBUFFER, oldFB);
    [EAGLContext setCurrentContext:nil];
    
    resize(0, 0);

#elif defined(GX_OS_MACOSX)
    NSOpenGLPixelFormat *pixelFormat=nil;
    NSOpenGLContext* shared=nil;
    //shared
    GWindow* aw = GWindow::first();
    if (aw && aw != getWindow()) {
        shared=GX_CAST_R(NSOpenGLContext*, GX_CAST_R(GOGLContext*, &aw->m_Context)->m_Context.context);
        pixelFormat=shared.pixelFormat;
    }
    else {
        pixelFormat=CreatePF();
        shared=nil;
    }
    
    m_Context.context=[[NSOpenGLContext alloc] initWithFormat:pixelFormat shareContext:shared];
    [GX_CAST_R(NSOpenGLContext*, m_Context.context) setView:GX_CAST_R(NSView*, getWindow()->getOSWindow())];
    [GX_CAST_R(NSOpenGLContext*, m_Context.context) update];
#elif defined(GX_OS_ANDROID)
	CreateDC();

    m_Context.display=g_Display;

	EGLint format;
	eglGetConfigAttrib(g_Display, g_Config, EGL_NATIVE_VISUAL_ID, &format);
	ANativeWindow_setBuffersGeometry(win->m_OSWin, 0, 0, format);

	m_Context.surface = eglCreateWindowSurface(g_Display, g_Config, win->m_OSWin, NULL);

	const EGLint attribs_context[] = {
			EGL_CONTEXT_CLIENT_VERSION, 2,
			EGL_NONE
	};
	EGLContext shared = g_Context;
	if (shared == EGL_NO_CONTEXT) {
		GWindow *aw = GWindow::first();
		if (aw && aw != getWindow()) {
			shared = GX_CAST_R(EGLContext, GX_CAST_R(GOGLContext * , &aw->m_Context)->m_Context.context);
		}
	}
	m_Context.context = eglCreateContext(g_Display, g_Config, shared, attribs_context);

	if (g_Surface==EGL_NO_SURFACE) {
		g_Surface = m_Context.surface;
		g_Context = m_Context.context;
	}
#elif defined(GX_OS_QT)
    m_Context.surface=getWindow()->m_OSWin;
    m_Context.context=new QOpenGLContext();
    m_Context.context->setFormat(getWindow()->m_OSWin->format());
    GWindow *aw = GWindow::first();
    if (aw && aw != getWindow()) {
        m_Context.context->setShareContext(GX_CAST_R(GOGLContext* , &aw->m_Context)->m_Context.context);
    }
    if(!m_Context.context->create()) {
        return false;
    }
    GX_ASSERT(!m_Context.context->isOpenGLES());
    m_Context.context->makeCurrent(getWindow()->m_OSWin);
    initializeOpenGLFunctions();
    m_Context.context->doneCurrent();
#endif
	return true;
}
//在这里反初始化
void GOGLContext::destroy()
{
#if defined(GX_OS_WINDOWS)
	if (m_Context.context) {
		wglDeleteContext(m_Context.context);
		m_Context.context = NULL;
	}
	if (m_Context.DC) {
		::ReleaseDC(M_OS_WND(getWindow()->getOSWindow()), m_Context.DC);
		m_Context.DC = NULL;
	}
#elif defined(GX_OS_APPLE)
#if defined(GX_OS_IPHONE)
    [EAGLContext setCurrentContext:GX_CAST_R(EAGLContext*, m_Context.context)];
    
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
    [GX_CAST_R(id, m_Context.context) release];
    m_Context.context=NULL;
#elif defined(GX_OS_ANDROID)
	if(m_Context.context!=EGL_NO_CONTEXT) {
		if(m_Context.context!=g_Context) {
			eglDestroyContext(g_Display, m_Context.context);
		}
		m_Context.context=EGL_NO_CONTEXT;
	}
	if(m_Context.surface!=EGL_NO_SURFACE) {
		if(m_Context.surface!=g_Surface) {
			eglDestroySurface(g_Display, m_Context.surface);
		}
        m_Context.surface=EGL_NO_SURFACE;
	}
#elif defined(GX_OS_QT)
    //delete m_Context;
    m_Context.context=NULL;
#endif
	GBaseContext::destroy();
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
    [EAGLContext setCurrentContext:GX_CAST_R(EAGLContext*, m_Context.context)];
    
    GLuint oldFB,oldRB;
    GX_glGetIntegerv(GL_FRAMEBUFFER_BINDING, (GLint*)&oldFB);
    GX_glGetIntegerv(GL_RENDERBUFFER_BINDING, (GLint*)&oldRB);
    
    glBindRenderbuffer(GL_RENDERBUFFER, m_ColorRenderbuffer);
    [GX_CAST_R(EAGLContext*, m_Context.context) renderbufferStorage:GL_RENDERBUFFER
                                               fromDrawable:(id<EAGLDrawable>)GX_CAST_R(UIView*, getWindow()->m_OSWin).layer];
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
        glBindFramebuffer(GL_FRAMEBUFFER, m_DefaultFramebuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, m_DepthRenderbuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24_OES, m_BackingWidth, m_BackingHeight);
    }
    
    bool res= (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
    
    glBindRenderbuffer(GL_RENDERBUFFER, oldRB);
    glBindFramebuffer(GL_FRAMEBUFFER, oldFB);
    [EAGLContext setCurrentContext:nil];
    
    return res;
#elif defined(GX_OS_MACOSX)
    [GX_CAST_R(NSOpenGLContext*, m_Context.context) update];
    return true;
#elif defined(GX_OS_ANDROID)
	if (m_Context.surface != EGL_NO_SURFACE) {
		if(m_Context.surface==g_Surface) {
			eglDestroySurface(g_Display, m_Context.surface);
            m_Context.surface = eglCreateWindowSurface(g_Display, g_Config, getWindow()->m_OSWin, NULL);
			g_Surface=m_Context.surface;
		}
		else {
			eglDestroySurface(g_Display, m_Context.surface);
            m_Context.surface = eglCreateWindowSurface(g_Display, g_Config, getWindow()->m_OSWin, NULL);
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
    return m_Context.isValid();
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
    
    const GColor4F& bgdClr=getWindow()->getBackgroundColor();
	GX_glClearColor(bgdClr.r, bgdClr.g, bgdClr.b, bgdClr.a);
	GX_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void GOGLContext::setViewport(float x, float y, float w, float h, float scale)
{
	GX_glViewport((GLint)(x*scale), (GLint)(y*scale), (GLint)(w*scale), (GLint)(h*scale));
}

void GOGLContext::renderEnd()
{
#if defined(GX_OS_WINDOWS)
	::SwapBuffers(m_Context.DC);
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
    GLuint oldRB;
    GX_glGetIntegerv(GL_RENDERBUFFER_BINDING, (GLint*)&oldRB);
	glBindRenderbuffer(GL_RENDERBUFFER, m_ColorRenderbuffer);
	[GX_CAST_R(EAGLContext*,m_Context.context) presentRenderbuffer:GL_RENDERBUFFER];
    glBindRenderbuffer(GL_RENDERBUFFER, oldRB);
#elif defined(GX_OS_MACOSX)
	[GX_CAST_R(NSOpenGLContext*,m_Context.context) flushBuffer];
#elif defined(GX_OS_ANDROID)
	eglSwapBuffers(g_Display, m_Context.surface);
#elif defined(GX_OS_QT)
    m_Context.context->swapBuffers(getWindow()->m_OSWin);
#endif
	makeClear();
}

void GOGLContext::makeCurrent()
{
    GX::openGLPushContext(m_Context);
}
void GOGLContext::makeClear()
{
    GX::openGLPopContext();
}

void GOGLContext::readyShader()
{
#if defined(GX_OS_ANDROID)
    GX::OGLContext ctt;
    ctt.display=g_Display;
    ctt.surface=g_Surface;
    ctt.context=g_Context;
    GX::openGLPushContext(ctt);
#else
    makeCurrent();
#endif
}

void GOGLContext::doneShader()
{
#if defined(GX_OS_ANDROID)
    GX::openGLPopContext();
#else
    makeClear();
#endif
}

void GOGLContext::readyTexture()
{
#if defined(GX_OS_ANDROID)
    GX::OGLContext ctt;
    ctt.display=g_Display;
    ctt.surface=g_Surface;
    ctt.context=g_Context;
    GX::openGLPushContext(ctt);
#else
    makeCurrent();
#endif
}
void GOGLContext::doneTexture()
{
#if defined(GX_OS_ANDROID)
    GX::openGLPopContext();
#else
    makeClear();
#endif
}

void GOGLContext::readyFrameBuffer()
{
#if defined(GX_OS_ANDROID)
    GX::OGLContext ctt;
    ctt.display=g_Display;
    ctt.surface=g_Surface;
    ctt.context=g_Context;
    GX::openGLPushContext(ctt);
#else
    makeCurrent();
#endif
}
void GOGLContext::doneFrameBuffer()
{
#if defined(GX_OS_ANDROID)
    GX::openGLPopContext();
#else
    makeClear();
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GDib* GOGLContext::loadTexture2DNodeReadyDib(GDib* dib)
{
    if (dib) {
        switch (dib->getPixelFormat()) {
            case GX::PixelFormatA8:
            case GX::PixelFormatRGB565:
            case GX::PixelFormatRGBA4444:
            case GX::PixelFormatRGBA5551:
            case GX::PixelFormatRGB888:
            case GX::PixelFormatRGBA8888:
            {
                return dib;
            }
                break;
            case GX::PixelFormatBGR565:
            {
                return GDib::convert(dib, GX::PixelFormatRGB565);
            }
                break;
            case GX::PixelFormatBGRA4444:
            {
                return GDib::convert(dib, GX::PixelFormatRGBA4444);
            }
                break;
            case GX::PixelFormatBGRA5551:
            {
                return GDib::convert(dib, GX::PixelFormatRGBA5551);
            }
                break;
                break;
            case GX::PixelFormatBGRA8888:
            {
                return GDib::convert(dib, GX::PixelFormatRGBA8888);
            }
                break;
            default:
                break;
        }
    }
	return NULL;
}

GX::PixelFormat GOGLContext::getPixelFormatForFB() const
{
    return GX::PixelFormatRGBA8888;
}

void GOGLContext::loadTexture2DNodeInMT(GObject* obj)
{
	GContext::T2DNodeLoadObjBase& nodeObj = *GX_CAST_R(GContext::T2DNodeLoadObjBase*, obj);
    GTexture::Handle& handle = nodeObj.nodeOut->getData();
    
    nodeObj.context->readyTexture();
    
	GX_glGenTextures(1, &handle.m_Name);
    
	if (handle.m_Name != 0) {

		GX::PixelFormat pf;
		gint32 w, h;
		void* data;

		if (obj->isKindOfClass(GContext::T2DNodeLoadCreateObj::gclass)) {
			pf = GX_CAST_R(GContext::T2DNodeLoadCreateObj*, obj)->pixelFormat;
			w = GX_CAST_R(GContext::T2DNodeLoadCreateObj*, obj)->width;
			h = GX_CAST_R(GContext::T2DNodeLoadCreateObj*, obj)->height;
			data = NULL;
		}
		else {
			GDib*& dib = GX_CAST_R(GContext::T2DNodeLoadObj*, obj)->dib;
			pf = dib->getPixelFormat();
			w = dib->getWidth();
			h = dib->getHeight();
			data = dib->getDataPtr();
		}

        GLuint oldTex;
        GX_glGetIntegerv(GL_TEXTURE_BINDING_2D,(GLint *)&oldTex);
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
        
        if (w%4==0) {
            GX_glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
        }
        else {
            GX_glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        }
        
        bool bTF=true;
        
        switch(pf) {
            case GX::PixelFormatRGBA8888:
            {
                GX_glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, w,h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            }
                break;
            case GX::PixelFormatRGB888:
            {
                GX_glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB,  w,h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            }
                break;
            case GX::PixelFormatRGB565:
            {
                GX_glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB,  w,h, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, data);
            }
                break;
            case GX::PixelFormatRGBA4444:
            {
                GX_glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA,  w,h, 0, GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4, data);
            }
                break;
            case GX::PixelFormatRGBA5551:
            {
                GX_glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA,  w,h, 0, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, data);
            }
                break;
            case GX::PixelFormatA8:
            {
                GX_glTexImage2D( GL_TEXTURE_2D, 0, GL_ALPHA, w,h, 0, GL_ALPHA, GL_UNSIGNED_BYTE, data);
            }
                break;
            default:
            {
                bTF=false;
            }
                break;
        }
        
        GX_glBindTexture(GL_TEXTURE_2D, oldTex);
        
        if (!bTF) {
			GX_glDeleteTextures(1, &handle.m_Name);
			handle.m_Name = 0;
        }
    }
    
    nodeObj.context->doneTexture();

    if (handle.isValid()) {
        nodeObj.nodeOut->m_Context=nodeObj.context;
        nodeObj.nodeOut->m_Context->addTextureNodeInMT(nodeObj.nodeOut);
    }
}

void GOGLContext::unloadTextureNodeForContext(GTexture::Node* node)
{
	if (node->isValid()) {

		GTexture::Handle& handle = node->getData();
		readyTexture();
		GX_glDeleteTextures(1, &handle.m_Name);
		handle.m_Name = 0;
		doneTexture();

		node->m_Context = NULL;
	}

}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void GOGLContext::loadFrameBufferNodeInMT(GObject* obj)
{
    GContext::FBNodeLoadObj& nodeObj= *GX_CAST_R(GContext::FBNodeLoadObj*, obj);
    GFrameBuffer::Handle& handle = nodeObj.nodeOut->getData();

    if (!nodeObj.texTarget->isKindOfClass(GTexture2D::gclass)) {
        return;
    }

    nodeObj.context->readyFrameBuffer();

    GX_glGenFramebuffers(1,&handle.m_Name);
    if (handle.m_Name) {
        if (nodeObj.use==GFrameBuffer::UseFor3D) {
            GX_glGenRenderbuffers(1,&handle.m_DepthName);

            if (!handle.m_DepthName) {
                GX_glDeleteFramebuffers(1,&handle.m_Name);
                handle.m_Name=0;
            }
        }

        if (handle.m_Name) {
            GLuint oldFB;
            GX_glGetIntegerv(GL_FRAMEBUFFER_BINDING, (GLint*)&oldFB);
            GX_glBindFramebuffer(GL_FRAMEBUFFER, handle.m_Name);
            GX_glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D, nodeObj.texTarget->getNode()->getData().getName(), 0);
            if (nodeObj.use==GFrameBuffer::UseFor3D) {
                GLuint oldRB;
                GX_glGetIntegerv(GL_RENDERBUFFER_BINDING, (GLint*)&oldRB);
                GX_glBindRenderbuffer(GL_RENDERBUFFER, handle.m_DepthName);
#if !defined(GL_DEPTH_COMPONENT24_OES)
#define GL_DEPTH_COMPONENT24_OES GL_DEPTH_COMPONENT
#endif
                GX_glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24_OES, GX_CAST_R(GTexture2D*, nodeObj.texTarget)->getWidth(), GX_CAST_R(GTexture2D*, nodeObj.texTarget)->getHeight());
                GX_glBindRenderbuffer(GL_RENDERBUFFER, oldRB);

                GX_glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, handle.m_DepthName);
            }
            GLenum cfs=GX_glCheckFramebufferStatus(GL_FRAMEBUFFER);
            if (cfs!=GL_FRAMEBUFFER_COMPLETE) {
                GX_LOG_P1(PrioDEBUG, "GOGLContext", "loadFrameBufferNodeInMT glCheckFramebufferStatus=%u", cfs);
            }
            GX_glBindFramebuffer(GL_FRAMEBUFFER, oldFB);
        }
    }

    nodeObj.context->doneFrameBuffer();

    if (handle.isValid()) {
        nodeObj.nodeOut->m_Context=nodeObj.context;
		nodeObj.nodeOut->m_TexTarget=nodeObj.texTarget;
		GO::retain(nodeObj.nodeOut->m_TexTarget);
        nodeObj.nodeOut->m_Context->addFrameBufferNodeInMT(nodeObj.nodeOut);
    }

}
void GOGLContext::unloadFrameBufferNodeForContext(GFrameBuffer::Node* node)
{
	if (node->isValid()) {
		GFrameBuffer::Handle& handle = node->getData();

		readyFrameBuffer();

		GX_glDeleteFramebuffers(1, &handle.m_Name);
		handle.m_Name = 0;
		if (handle.m_DepthName) {
			GX_glDeleteRenderbuffers(1, &handle.m_DepthName);
			handle.m_DepthName = 0;
		}

		doneFrameBuffer();

		node->m_Context = NULL;
		GO::release(node->m_TexTarget);
		node->m_TexTarget = NULL;
	}
}










#endif
