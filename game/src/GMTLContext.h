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
#include "GX3DAPIType.h"
#if defined(GX_METAL)
#include "GXMetal.h"
#include "GBaseContext.h"
#include "GTexture2D.h"
#include "GFrameBuffer.h"

class GMTLContext : public GBaseContext, public GX::MetalCullFacer, public GX::MetalBlender {
    friend class GMShader;
protected:
    static void initialize();
public:
    static guint layerPixelFormat();
    static guint depthPixelFormat();
    static guint stencilPixelFormat();
    static guint sampleCount();
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
    static void readyShader();
    static void doneShader();
    void readyFrameBuffer();
    void doneFrameBuffer();
protected:
    GX::PixelFormat getPixelFormatForFB() const;
    static void loadFrameBufferNodeInMT(GObject* obj);
    void unloadFrameBufferNodeForContext(GFrameBuffer::Node* node);
protected:
    void* getDevice();
    void* getMetalLayer();
    void* currentDrawable();
    void clearDrawable();
    void setupRenderPassDescriptor(void* texture);
    void* getCommandQueue();
    void* getCommandBuffer();
    void* newRenderCommandEncoder();
    
    
private:
    void* m_DepthTex;
    void* m_StencilTex;
    void* m_MsaaTex;
    void* m_RenderPassDescriptor;
    void* m_CurrentDrawable;
    
    void* m_CommandQueue;
    void* m_DepthStencilState;
    /////
    void* m_CommandBuffer;
    GX::MetalViewport m_Viewport;
};

#endif


#endif /* GMTLContext_h */
