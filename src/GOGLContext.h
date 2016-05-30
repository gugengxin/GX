//
// Created by Gengxin Gu on 16/5/9.
//

#ifndef AS_GOGLCONTEXT_H
#define AS_GOGLCONTEXT_H

#include "GXPrefix.h"
#if defined(GX_OPENGL)
#include "GXOpenGL.h"
#if defined(GX_OS_ANDROID)
#include <EGL/egl.h>
#elif defined(GX_OS_QT)
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#endif

class GWindow;

class GOGLContext
#if defined(GX_OS_QT)
        : protected QOpenGLFunctions
#endif
{
protected:
    GOGLContext();
    ~GOGLContext();
public:
	bool create(GWindow* win);
    void destroy();
    bool resize(gfloat32 width,gfloat32 height);

	void renderBegin();
	void renderEnd();

public:
	void makeCurrent();
	void makeClear();
protected:
	void readyShader();
	void doneShader();
	void readyTexture();
	void doneTexture();

private:
	GWindow* m_Window;
#if defined(GX_OS_WINDOWS)
	HDC   m_DC;
	HGLRC m_Context;
#elif defined(GX_OS_APPLE)
    void* m_Context;
#if defined(GX_OS_IPHONE)
    
    gint32   m_BackingWidth;
    gint32   m_BackingHeight;
    gint32   m_Samples;
    guint32  m_DefaultFramebuffer;
    guint32  m_ColorRenderbuffer;
    guint32  m_DepthRenderbuffer;
    guint32  m_SaaFramebuffer;
    guint32  m_SaaRenderbuffer;
#endif
#elif defined(GX_OS_ANDROID)
	EGLSurface m_Surface;
	EGLContext m_Context;
#elif defined(GX_OS_QT)
    QOpenGLContext* m_Context;
#endif
};

#endif
#endif //AS_GOGLCONTEXT_H
