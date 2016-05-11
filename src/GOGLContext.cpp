//
// Created by Gengxin Gu on 16/5/9.
//

#include "GOGLContext.h"
#if defined(GX_OPENGL)
#include "GApplication.h"
#include "GLog.h"

#if defined(GX_OS_WINDOWS)
#include <Windows.h>

#define M_OS_WND(p) GX_CAST_R(HWND,p)

static void ConfigDC(HDC dc)
{
	GApplication::Delegate* dge = GApplication::sharedDelegate();
	int depth = (int)dge->WindowsSuggestedDepth();
	int stencil = (int)dge->WindowsSuggestedStencil();
	int multiSamples = (int)dge->WindowsSuggestedSamples();

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
#endif

GOGLContext::GOGLContext()
{
#if defined(GX_OS_WINDOWS)
	static bool g_GLEWInit = GX::GLEWInit();
#endif
	m_Window = NULL;
}

GOGLContext::~GOGLContext()
{
#if defined(GX_OS_WINDOWS)
	if (m_Context) {
		wglDeleteContext(m_Context);
	}
	if (m_DC) {
		::ReleaseDC(M_OS_WND(m_Window->getOSWindow()), m_DC);
	}
#endif
}

bool GOGLContext::create(GWindow* win)
{
	m_Window = win;

#if defined(GX_OS_WINDOWS)
	m_DC = ::GetDC(M_OS_WND(m_Window->getOSWindow()));
	ConfigDC(m_DC);
	m_Context = ::wglCreateContext(m_DC);
	::wglMakeCurrent(m_DC, m_Context);

	if (GApplication::shared()->getWindowCount() > 0) {
		GWindow* aw = GApplication::shared()->getWindow(0);
		if (aw != m_Window) {
			wglShareLists(((GOGLContext*)&aw->m_Context)->m_Context, m_Context);
		}
	}
#endif


	return true;
}

void GOGLContext::destroy()
{
#if defined(GX_OS_WINDOWS)
	if (m_Context) {
		wglDeleteContext(m_Context);
		m_Context = NULL;
	}
	if (m_DC) {
		::ReleaseDC(M_OS_WND(m_Window->getOSWindow()), m_DC);
		m_DC = NULL;
	}
#endif
}

void GOGLContext::makeCurrent()
{
#if defined(GX_OS_WINDOWS)
	wglMakeCurrent(m_DC, m_Context);
#endif
}
void GOGLContext::makeClear()
{
#if defined(GX_OS_WINDOWS)
	wglMakeCurrent(NULL, NULL);
#endif
}



void GOGLContext::renderBegin()
{
	makeCurrent();

	glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}
void GOGLContext::renderEnd()
{
#if defined(GX_OS_WINDOWS)
	::SwapBuffers(m_DC);
#endif
	makeClear();
}




#endif