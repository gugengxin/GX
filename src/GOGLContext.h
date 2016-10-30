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
#include "GDataArray.h"
#include "GTexture2D.h"
#include "GFrameBuffer.h"

class GWindow;

class GOGLContext
#if defined(GX_OS_QT)
        : public QOpenGLFunctions
#endif
{
protected:
    GOGLContext();
    virtual ~GOGLContext();
public:
    virtual bool create(GWindow* win);
    virtual void destroy();
#if defined(GX_OS_ANDROID)
protected:
	virtual void androidDestroy();
	virtual void androidRecreate(GWindow* win);
#endif
public:
    bool resize(gfloat32 width,gfloat32 height);

	bool renderCheck();
	void renderBegin();
	void setViewport(float x, float y, float w, float h, float scale);
	void renderEnd();

public:
	void makeCurrent();
	void makeClear();
protected:
    void readyShader();
    void doneShader();
	void readyTexture();
	void doneTexture();
    void readyFrameBuffer();
    void doneFrameBuffer();
protected:
	GDib* loadTexture2DNodeReadyDib(GDib* dib);
	static void loadTexture2DNodeInMT(GObject* obj);
	void unloadTextureNodeForContext(GTexture::Node* node);
protected:
    static void loadFrameBufferNodeInMT(GObject* obj);
    void unloadFrameBufferNodeForContext(GFrameBuffer::Node* node);

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
#if defined(GX_OS_ANDROID)
    class OSHandle {
    public:
        EGLSurface surface;
        EGLContext context;
    };
    void pushOSHandle(EGLSurface surface,EGLContext context);
    void popOSHandle();

    GPDArray<OSHandle> m_OSHandles;
#else
    gint m_ContextMakeCount;
#endif
};

#endif
#endif //AS_GOGLCONTEXT_H
