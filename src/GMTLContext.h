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

class GWindow;

class GMTLContext {
protected:
    GMTLContext();
    virtual ~GMTLContext();

public:
    virtual bool create(GWindow* win);
    virtual void destroy();
    
public:
    bool resize(gfloat32 width,gfloat32 height);
    
    bool renderCheck();
    void renderBegin();
    void setViewport(float x, float y, float w, float h, float scale);
    void renderEnd();
    
private:
    void* currentDrawable();
    void clearDrawable();
    void setupRenderPassDescriptor(void* texture);
    void* renderPassDescriptor();

private:
    GWindow* m_Window;
    
    // set these pixel formats to have the main drawable framebuffer get created with depth and/or stencil attachments
    guint m_DepthPixelFormat;
    guint m_StencilPixelFormat;
    guint m_SampleCount;
    
    void* m_DepthTex;
    void* m_StencilTex;
    void* m_MsaaTex;
    void* m_RenderPassDescriptor;
    void* m_CurrentDrawable;
};



typedef GMTLContext GContextBase;

#endif


#endif /* GMTLContext_h */
