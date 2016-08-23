//
//  GMTLContext.cpp
//  GX
//
//  Created by Gu Gengxin on 16/8/20.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#include "GMTLContext.h"
#if defined(GX_METAL)
#if defined(GX_OS_IPHONE)
#import <UIKit/UIKit.h>
#elif defined(GX_OS_MACOSX)
#import <Cocoa/Cocoa.h>
#endif
#include "GApplication.h"
#include "GWindow.h"

//不用在这里初始化
GMTLContext::GMTLContext()
{
}
//不用在这里反初始化
GMTLContext::~GMTLContext()
{
}

bool GMTLContext::create(GWindow* win)
{
    m_Window=win;
    
    m_DepthPixelFormat=MTLPixelFormatInvalid;
    m_StencilPixelFormat=MTLPixelFormatInvalid;
    m_SampleCount=GApplication::sharedDelegate()->windowsSuggestedSamples();
    
    m_DepthTex=NULL;
    m_StencilTex=NULL;
    m_MsaaTex=NULL;
    m_RenderPassDescriptor=NULL;
    m_CurrentDrawable=NULL;
    
    return true;
}

void GMTLContext::destroy()
{
    [GX_CAST_R(id, m_DepthTex) release];
    [GX_CAST_R(id, m_StencilTex) release];
    [GX_CAST_R(id, m_MsaaTex) release];
    [GX_CAST_R(id, m_RenderPassDescriptor) release];
    [GX_CAST_R(id, m_CurrentDrawable) release];
    
    m_Window=NULL;
}

bool GMTLContext::resize(gfloat32 width,gfloat32 height)
{
    
}

bool GMTLContext::renderCheck()
{
    
}
void GMTLContext::renderBegin()
{
    
}
void GMTLContext::setViewport(float x, float y, float w, float h, float scale)
{
    
}
void GMTLContext::renderEnd()
{
    
}


void* GMTLContext::currentDrawable()
{
    if (!m_CurrentDrawable) {
        m_CurrentDrawable=[[GX_CAST_R(CAMetalLayer*,m_Window->getMetalLayer()) nextDrawable] retain];
    }
    return m_CurrentDrawable;
}
void GMTLContext::clearDrawable()
{
    [GX_CAST_R(id, m_CurrentDrawable) release];
    m_CurrentDrawable=NULL;
}

void GMTLContext::setupRenderPassDescriptor(void* texture)
{
#define _texture ((id<MTLTexture>)texture)
#define _msaaTex ((id<MTLTexture>)m_MsaaTex)
#define _depthTex ((id<MTLTexture>)m_DepthTex)
#define _stencilTex ((id<MTLTexture>)m_StencilTex)
    
    id<MTLDevice> device=GX_CAST_R(CAMetalLayer*,m_Window->getMetalLayer()).device;
    
    if (!m_RenderPassDescriptor) {
        m_RenderPassDescriptor=[[MTLRenderPassDescriptor renderPassDescriptor] retain];
    }
    
    // create a color attachment every frame since we have to recreate the texture every frame
    MTLRenderPassColorAttachmentDescriptor *colorAttachment = GX_CAST_R(MTLRenderPassDescriptor*, m_RenderPassDescriptor).colorAttachments[0];
    colorAttachment.texture = (id<MTLTexture>)texture;
    
    // make sure to clear every frame for best performance
    colorAttachment.loadAction = MTLLoadActionClear;
    GColor4F& bgdClr=m_Window->m_BgdColor;
    colorAttachment.clearColor = MTLClearColorMake(bgdClr.r, bgdClr.g, bgdClr.b, bgdClr.a);
    
    // if sample count is greater than 1, render into using MSAA, then resolve into our color texture
    if(m_SampleCount > 1)
    {
        BOOL doUpdate =( _msaaTex.width       != _texture.width  )
                   ||  ( _msaaTex.height      != _texture.height )
                   ||  ( _msaaTex.sampleCount != m_SampleCount   );
        
        if(!_msaaTex || (_msaaTex && doUpdate))
        {
            [_msaaTex release];
            
            MTLTextureDescriptor* desc = [MTLTextureDescriptor texture2DDescriptorWithPixelFormat: MTLPixelFormatRGBA8Unorm
                                                                                            width: _texture.width
                                                                                           height: _texture.height
                                                                                        mipmapped: NO];
            desc.textureType = MTLTextureType2DMultisample;
            
            // sample count was specified to the view by the renderer.
            // this must match the sample count given to any pipeline state using this render pass descriptor
            desc.sampleCount = m_SampleCount;
            m_MsaaTex = [[device newTextureWithDescriptor: desc] retain];
        }
        
        // When multisampling, perform rendering to _msaaTex, then resolve
        // to 'texture' at the end of the scene
        colorAttachment.texture = _msaaTex;
        colorAttachment.resolveTexture = _texture;
        
        // set store action to resolve in this case
        colorAttachment.storeAction = MTLStoreActionMultisampleResolve;
    }
    else
    {
        // store only attachments that will be presented to the screen, as in this case
        colorAttachment.storeAction = MTLStoreActionStore;
    } // color0
    
    // Now create the depth and stencil attachments
    
    if(m_DepthPixelFormat != MTLPixelFormatInvalid)
    {
        BOOL doUpdate = ( _depthTex.width       != _texture.width  )
                    ||  ( _depthTex.height      != _texture.height )
                    ||  ( _depthTex.sampleCount != m_SampleCount   );
        
        if(!_depthTex || doUpdate)
        {
            [_depthTex release];
            //  If we need a depth texture and don't have one, or if the depth texture we have is the wrong size
            //  Then allocate one of the proper size
            MTLTextureDescriptor* desc = [MTLTextureDescriptor texture2DDescriptorWithPixelFormat: (MTLPixelFormat)m_DepthPixelFormat
                                                                                            width: _texture.width
                                                                                           height: _texture.height
                                                                                        mipmapped: NO];
            
            desc.textureType = (m_SampleCount > 1) ? MTLTextureType2DMultisample : MTLTextureType2D;
            desc.sampleCount = m_SampleCount;
            desc.usage = MTLTextureUsageUnknown;
            desc.storageMode = MTLStorageModePrivate;
            
            m_DepthTex = [[device newTextureWithDescriptor: desc] retain];
            
            MTLRenderPassDepthAttachmentDescriptor *depthAttachment = GX_CAST_R(MTLRenderPassDescriptor*, m_RenderPassDescriptor).depthAttachment;
            depthAttachment.texture = _depthTex;
            depthAttachment.loadAction = MTLLoadActionClear;
            depthAttachment.storeAction = MTLStoreActionDontCare;
            depthAttachment.clearDepth = 1.0;
        }
    } // depth
    
    if(m_StencilPixelFormat != MTLPixelFormatInvalid)
    {
        BOOL doUpdate = ( _stencilTex.width       != _texture.width  )
                    ||  ( _stencilTex.height      != _texture.height )
                    ||  ( _stencilTex.sampleCount != m_SampleCount   );
        
        if(!_stencilTex || doUpdate)
        {
            [_stencilTex release];
            //  If we need a stencil texture and don't have one, or if the depth texture we have is the wrong size
            //  Then allocate one of the proper size
            MTLTextureDescriptor* desc = [MTLTextureDescriptor texture2DDescriptorWithPixelFormat: (MTLPixelFormat)m_StencilPixelFormat
                                                                                            width: _texture.width
                                                                                           height: _texture.height
                                                                                        mipmapped: NO];
            
            desc.textureType = (m_SampleCount > 1) ? MTLTextureType2DMultisample : MTLTextureType2D;
            desc.sampleCount = m_SampleCount;
            
            m_StencilTex = [[device newTextureWithDescriptor: desc] retain];
            
            MTLRenderPassStencilAttachmentDescriptor* stencilAttachment = GX_CAST_R(MTLRenderPassDescriptor*, m_RenderPassDescriptor).stencilAttachment;
            stencilAttachment.texture = _stencilTex;
            stencilAttachment.loadAction = MTLLoadActionClear;
            stencilAttachment.storeAction = MTLStoreActionDontCare;
            stencilAttachment.clearStencil = 0;
        }
    } //stencil
    
#undef _texture
#undef _msaaTex
#undef _depthTex
#undef _stencilTex
}

void* GMTLContext::renderPassDescriptor()
{
    id <CAMetalDrawable> drawable = (id <CAMetalDrawable>)currentDrawable();
    if(drawable) {
        setupRenderPassDescriptor(drawable.texture);
    }
    
    return m_RenderPassDescriptor;
}

#endif