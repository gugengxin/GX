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
#include "GBaseContext.h"
#include "GDataArray.h"
#include "GTexture2D.h"
#include "GFrameBuffer.h"

class GOGLContext : public GBaseContext
#if defined(GX_OS_QT)
        , public QOpenGLFunctions
#endif
{
protected:
    GOGLContext();
    virtual ~GOGLContext();
protected:
    virtual bool create(GWindow* win);
    virtual void destroy();
#if defined(GX_OS_ANDROID)
protected:
	virtual void androidDestroy();
	virtual void androidRecreate(GWindow* win);
#endif
protected:
    bool resize(gfloat32 width,gfloat32 height);

	bool renderCheck();
	void renderBegin();
	void setViewport(float x, float y, float w, float h, float scale);
	void renderEnd();

protected:
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
    GX::PixelFormat getPixelFormatForFB() const;
	static void loadTexture2DNodeInMT(GObject* obj);
	void unloadTextureNodeForContext(GTexture::Node* node);
protected:
    static void loadFrameBufferNodeInMT(GObject* obj);
    void unloadFrameBufferNodeForContext(GFrameBuffer::Node* node);

private:
    GX::OGLContext m_Context;

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
};

#endif
#endif //AS_GOGLCONTEXT_H
