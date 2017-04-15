//
//  GMTLContext.hpp
//  GX
//
//  Created by Gu Gengxin on 16/8/20.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GMTLContext_h
#define GMTLContext_h

#include "GXPrefix.h"

#if defined(GX_METAL)
#include "GXMetal.h"
#include "GBaseContext.h"
#include "GTexture2D.h"
#include "GFrameBuffer.h"

class GMTLContext : public GBaseContext {
    friend class GMShader;
protected:
    GMTLContext();
    virtual ~GMTLContext();
protected:
    virtual bool create(GWindow* win);
    virtual void destroy();
    
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
protected:
    inline guint getDepthPixelFormat() {
        return m_DepthPixelFormat;
    }
    inline guint getStencilPixelFormat() {
        return m_StencilPixelFormat;
    }
    inline guint getSampleCount() {
        return m_SampleCount;
    }
    
    void* getDevice();
    void* getMetalLayer();
    void* currentDrawable();
    void clearDrawable();
    void setupRenderPassDescriptor(void* texture);
    void* renderPassDescriptor();
    void* getCommandQueue();
    void* getCommandBuffer();
    void* getRenderEncoder();
    
    
private:
    guint m_DepthPixelFormat;
    guint m_StencilPixelFormat;
    guint m_SampleCount;
    
    void* m_DepthTex;
    void* m_StencilTex;
    void* m_MsaaTex;
    void* m_RenderPassDescriptor;
    void* m_CurrentDrawable;
    
    void* m_CommandQueue;
    void* m_DepthStencilState;
    /////
    void* m_CommandBuffer;
    void* m_RenderEncoder;
};

#endif


#endif /* GMTLContext_h */
