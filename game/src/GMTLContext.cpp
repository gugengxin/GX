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
#import <QuartzCore/QuartzCore.h>

#include "GApplication.h"
#include "GWindow.h"

#define M_METAL_LAYER()         GX_CAST_R(CAMetalLayer*,getWindow()->getMetalLayer())
#define M_COMMAND_QUEUE()       GX_CAST_R(id<MTLCommandQueue>, m_CommandQueue)
#define M_COMMAND_BUFFER()      GX_CAST_R(id<MTLCommandBuffer>, m_CommandBuffer)
#define M_RENDER_ENCODER()      GX_CAST_R(id<MTLRenderCommandEncoder>, m_RenderEncoder)
#define M_DEPTH_STENCIL_STATE() GX_CAST_R(id<MTLDepthStencilState>, m_DepthStencilState)


static guint g_DepthPixelFormat=MTLPixelFormatInvalid;
static guint g_StencilPixelFormat=MTLPixelFormatInvalid;
static guint g_SampleCount=0;

void GMTLContext::initialize()
{
    GApplication::Delegate* appDge=GApplication::sharedDelegate();
    g_DepthPixelFormat=appDge->windowsSuggestedDepth()>0?MTLPixelFormatDepth32Float:MTLPixelFormatInvalid;
    g_StencilPixelFormat=appDge->windowsSuggestedStencil()>0?MTLPixelFormatStencil8:MTLPixelFormatInvalid;
    g_SampleCount=appDge->windowsSuggestedSamples()>1?appDge->windowsSuggestedSamples():1;
    if (g_DepthPixelFormat!=MTLPixelFormatInvalid && g_StencilPixelFormat!=MTLPixelFormatInvalid) {
        g_DepthPixelFormat=MTLPixelFormatDepth32Float_Stencil8;
        g_StencilPixelFormat=g_DepthPixelFormat;
    }
}

guint GMTLContext::layerPixelFormat()
{
    return MTLPixelFormatBGRA8Unorm;
}
guint GMTLContext::depthPixelFormat()
{
    return g_DepthPixelFormat;
}
guint GMTLContext::stencilPixelFormat()
{
    return g_StencilPixelFormat;
}
guint GMTLContext::sampleCount()
{
    return g_SampleCount;
}

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
    if (!GBaseContext::create(win)) {
        return false;
    }
    
    id <MTLDevice> device=M_METAL_LAYER().device;
    
    m_DepthTex=NULL;
    m_StencilTex=NULL;
    m_MsaaTex=NULL;
    m_RenderPassDescriptor=NULL;
    m_CurrentDrawable=NULL;
    
    m_CommandQueue=[[device newCommandQueue] retain];
    
    if (g_DepthPixelFormat!=MTLPixelFormatInvalid || g_StencilPixelFormat!=MTLPixelFormatInvalid) {
        MTLDepthStencilDescriptor *dsStateDesc = [[MTLDepthStencilDescriptor alloc] init];
        dsStateDesc.depthCompareFunction = MTLCompareFunctionAlways;
        dsStateDesc.depthWriteEnabled = YES;
        m_DepthStencilState = [[device newDepthStencilStateWithDescriptor:dsStateDesc] retain];
        [dsStateDesc release];
    }
    else {
        m_DepthStencilState=NULL;
    }

    m_CommandBuffer=NULL;
    m_RenderEncoder=NULL;
    
    return true;
}

void GMTLContext::destroy()
{
    [GX_CAST_R(id, m_RenderEncoder) release];
    [GX_CAST_R(id, m_CommandBuffer) release];

    [GX_CAST_R(id, m_CommandQueue) release];
    [GX_CAST_R(id, m_DepthStencilState) release];
    
    [GX_CAST_R(id, m_DepthTex) release];
    [GX_CAST_R(id, m_StencilTex) release];
    [GX_CAST_R(id, m_MsaaTex) release];
    [GX_CAST_R(id, m_RenderPassDescriptor) release];
    [GX_CAST_R(id, m_CurrentDrawable) release];
    
    GBaseContext::destroy();
}

bool GMTLContext::resize(gfloat32 width,gfloat32 height)
{
    return true;
}

bool GMTLContext::renderCheck()
{
    return true;
}
void GMTLContext::renderBegin()
{
    currentDrawable();
    
    M_METAL_LAYER().drawableSize=CGSizeMake(getWindow()->getWidth()*getWindow()->getScale(), getWindow()->getHeight()*getWindow()->getScale());
    m_CommandBuffer = [[M_COMMAND_QUEUE() commandBuffer] retain];
    m_RenderEncoder = [[M_COMMAND_BUFFER() renderCommandEncoderWithDescriptor:GX_CAST_R(MTLRenderPassDescriptor*, renderPassDescriptor())] retain];
    if (m_DepthStencilState) {
        [M_RENDER_ENCODER() setDepthStencilState:M_DEPTH_STENCIL_STATE()];
    }
#if defined(GX_DEBUG)
    [M_RENDER_ENCODER() pushDebugGroup:@"GMTLContext"];
#endif
    
    metalCFUpdate(m_RenderEncoder);
}
void GMTLContext::setViewport(float x, float y, float w, float h, float scale)
{
    MTLViewport vt;
    vt.originX=x*scale;
    vt.originY=y*scale;
    vt.width=w*scale;
    vt.height=h*scale;
    vt.znear=0;
    vt.zfar=1;
    [M_RENDER_ENCODER() setViewport:vt];
}
void GMTLContext::renderEnd()
{
#if defined(GX_DEBUG)
    [M_RENDER_ENCODER() popDebugGroup];
#endif
    [M_RENDER_ENCODER() endEncoding];
    [M_COMMAND_BUFFER() presentDrawable:(id<CAMetalDrawable>)currentDrawable()];
    [M_COMMAND_BUFFER() commit];

    [M_RENDER_ENCODER() release];
    m_RenderEncoder=NULL;
    [M_COMMAND_BUFFER() release];
    m_CommandBuffer=NULL;
    
    clearDrawable();
}

void* GMTLContext::metalCFNeedRenderEncoder()
{
    return m_RenderEncoder;
}

void GMTLContext::makeCurrent()
{
}
void GMTLContext::makeClear()
{
}

void GMTLContext::readyShader()
{
}
void GMTLContext::doneShader()
{
}
void GMTLContext::readyFrameBuffer()
{
}
void GMTLContext::doneFrameBuffer()
{
}

void* GMTLContext::getDevice()
{
    return M_METAL_LAYER().device;
}

void* GMTLContext::getMetalLayer()
{
    return M_METAL_LAYER();
}

void* GMTLContext::currentDrawable()
{
    if (!m_CurrentDrawable) {
        m_CurrentDrawable=[[M_METAL_LAYER() nextDrawable] retain];
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
#define M_TEXTURE() ((id<MTLTexture>)texture)
#define M_MSAATEX() ((id<MTLTexture>)m_MsaaTex)
#define M_DEPTHTEX() ((id<MTLTexture>)m_DepthTex)
#define M_STENCILTEX() ((id<MTLTexture>)m_StencilTex)
    
    id<MTLDevice> device=M_METAL_LAYER().device;
    
    if (!m_RenderPassDescriptor) {
        m_RenderPassDescriptor=[[MTLRenderPassDescriptor renderPassDescriptor] retain];
    }
    
    // create a color attachment every frame since we have to recreate the texture every frame
    MTLRenderPassColorAttachmentDescriptor *colorAttachment = GX_CAST_R(MTLRenderPassDescriptor*, m_RenderPassDescriptor).colorAttachments[0];
    colorAttachment.texture = (id<MTLTexture>)texture;
    
    // make sure to clear every frame for best performance
    colorAttachment.loadAction = MTLLoadActionClear;
    const GColor4F& bgdClr=getWindow()->getBackgroundColor();
    colorAttachment.clearColor = MTLClearColorMake(bgdClr.r, bgdClr.g, bgdClr.b, bgdClr.a);
    
    // if sample count is greater than 1, render into using MSAA, then resolve into our color texture
    if(g_SampleCount > 1)
    {
        BOOL doUpdate =( M_MSAATEX().width       != M_TEXTURE().width  )
        ||  ( M_MSAATEX().height      != M_TEXTURE().height )
        ||  ( M_MSAATEX().sampleCount != g_SampleCount   );
        
        if(!M_MSAATEX() || (M_MSAATEX() && doUpdate))
        {
            [M_MSAATEX() release];
            
            MTLTextureDescriptor* desc = [MTLTextureDescriptor texture2DDescriptorWithPixelFormat: MTLPixelFormatBGRA8Unorm
                                                                                            width: M_TEXTURE().width
                                                                                           height: M_TEXTURE().height
                                                                                        mipmapped: NO];
            desc.textureType = MTLTextureType2DMultisample;
            
            // sample count was specified to the view by the renderer.
            // this must match the sample count given to any pipeline state using this render pass descriptor
            desc.sampleCount = g_SampleCount;
            
            if ([desc respondsToSelector:@selector(setUsage:)]) {
                desc.usage=MTLTextureUsageRenderTarget;
                desc.storageMode = MTLStorageModePrivate;
            }
            
            m_MsaaTex = [[device newTextureWithDescriptor: desc] retain];
        }
        
        // When multisampling, perform rendering to M_MSAATEX(), then resolve
        // to 'texture' at the end of the scene
        colorAttachment.texture = M_MSAATEX();
        colorAttachment.resolveTexture = M_TEXTURE();
        
        // set store action to resolve in this case
        colorAttachment.storeAction = MTLStoreActionMultisampleResolve;
    }
    else
    {
        // store only attachments that will be presented to the screen, as in this case
        colorAttachment.storeAction = MTLStoreActionStore;
    } // color0
    
    // Now create the depth and stencil attachments
    
    if (g_DepthPixelFormat != MTLPixelFormatInvalid && g_StencilPixelFormat != MTLPixelFormatInvalid) {
        BOOL doUpdate = ( M_DEPTHTEX().width       != M_TEXTURE().width  )
        ||  ( M_DEPTHTEX().height      != M_TEXTURE().height )
        ||  ( M_DEPTHTEX().sampleCount != g_SampleCount   );
        
        if(!M_DEPTHTEX() || doUpdate)
        {
            [M_DEPTHTEX() release];
            [M_STENCILTEX() release];
            //  If we need a depth texture and don't have one, or if the depth texture we have is the wrong size
            //  Then allocate one of the proper size
            MTLTextureDescriptor* desc = [MTLTextureDescriptor texture2DDescriptorWithPixelFormat: (MTLPixelFormat)g_DepthPixelFormat
                                                                                            width: M_TEXTURE().width
                                                                                           height: M_TEXTURE().height
                                                                                        mipmapped: NO];
            
            desc.textureType = (g_SampleCount > 1) ? MTLTextureType2DMultisample : MTLTextureType2D;
            desc.sampleCount = g_SampleCount;
            if ([desc respondsToSelector:@selector(setUsage:)]) {
                desc.usage = MTLTextureUsageUnknown;
                desc.storageMode = MTLStorageModePrivate;
            }
            m_DepthTex = [[device newTextureWithDescriptor:desc] retain];
            m_StencilTex = [M_DEPTHTEX() retain];
            
            MTLRenderPassDepthAttachmentDescriptor *depthAttachment = GX_CAST_R(MTLRenderPassDescriptor*, m_RenderPassDescriptor).depthAttachment;
            depthAttachment.texture = M_DEPTHTEX();
            depthAttachment.loadAction = MTLLoadActionClear;
            depthAttachment.storeAction = MTLStoreActionDontCare;
            depthAttachment.clearDepth = 1.0;
            
            MTLRenderPassStencilAttachmentDescriptor* stencilAttachment = GX_CAST_R(MTLRenderPassDescriptor*, m_RenderPassDescriptor).stencilAttachment;
            stencilAttachment.texture = M_STENCILTEX();
            stencilAttachment.loadAction = MTLLoadActionClear;
            stencilAttachment.storeAction = MTLStoreActionDontCare;
            stencilAttachment.clearStencil = 0;
        }
    }
    else  if(g_DepthPixelFormat != MTLPixelFormatInvalid) {
        BOOL doUpdate = ( M_DEPTHTEX().width       != M_TEXTURE().width  )
        ||  ( M_DEPTHTEX().height      != M_TEXTURE().height )
        ||  ( M_DEPTHTEX().sampleCount != g_SampleCount   );
        
        if(!M_DEPTHTEX() || doUpdate)
        {
            [M_DEPTHTEX() release];
            //  If we need a depth texture and don't have one, or if the depth texture we have is the wrong size
            //  Then allocate one of the proper size
            MTLTextureDescriptor* desc = [MTLTextureDescriptor texture2DDescriptorWithPixelFormat: (MTLPixelFormat)g_DepthPixelFormat
                                                                                            width: M_TEXTURE().width
                                                                                           height: M_TEXTURE().height
                                                                                        mipmapped: NO];
            
            desc.textureType = (g_SampleCount > 1) ? MTLTextureType2DMultisample : MTLTextureType2D;
            desc.sampleCount = g_SampleCount;
            if ([desc respondsToSelector:@selector(setUsage:)]) {
                desc.usage = MTLTextureUsageUnknown;
                desc.storageMode = MTLStorageModePrivate;
            }
            m_DepthTex = [[device newTextureWithDescriptor: desc] retain];
            
            MTLRenderPassDepthAttachmentDescriptor *depthAttachment = GX_CAST_R(MTLRenderPassDescriptor*, m_RenderPassDescriptor).depthAttachment;
            depthAttachment.texture = M_DEPTHTEX();
            depthAttachment.loadAction = MTLLoadActionClear;
            depthAttachment.storeAction = MTLStoreActionDontCare;
            depthAttachment.clearDepth = 1.0;
        }
    } // depth
    else if(g_StencilPixelFormat != MTLPixelFormatInvalid) {
        BOOL doUpdate = ( M_STENCILTEX().width       != M_TEXTURE().width  )
        ||  ( M_STENCILTEX().height      != M_TEXTURE().height )
        ||  ( M_STENCILTEX().sampleCount != g_SampleCount   );
        
        if(!M_STENCILTEX() || doUpdate)
        {
            [M_STENCILTEX() release];
            //  If we need a stencil texture and don't have one, or if the depth texture we have is the wrong size
            //  Then allocate one of the proper size
            MTLTextureDescriptor* desc = [MTLTextureDescriptor texture2DDescriptorWithPixelFormat: (MTLPixelFormat)g_StencilPixelFormat
                                                                                            width: M_TEXTURE().width
                                                                                           height: M_TEXTURE().height
                                                                                        mipmapped: NO];
            
            desc.textureType = (g_SampleCount > 1) ? MTLTextureType2DMultisample : MTLTextureType2D;
            desc.sampleCount = g_SampleCount;
#if defined(GX_OS_IPHONE)
            if ([[[UIDevice currentDevice] systemVersion] floatValue]>=9.0) {
#endif
                desc.usage = MTLTextureUsageUnknown;
                desc.storageMode = MTLStorageModePrivate;
#if defined(GX_OS_IPHONE)
            }
#endif
            m_StencilTex = [[device newTextureWithDescriptor: desc] retain];
            
            MTLRenderPassStencilAttachmentDescriptor* stencilAttachment = GX_CAST_R(MTLRenderPassDescriptor*, m_RenderPassDescriptor).stencilAttachment;
            stencilAttachment.texture = M_STENCILTEX();
            stencilAttachment.loadAction = MTLLoadActionClear;
            stencilAttachment.storeAction = MTLStoreActionDontCare;
            stencilAttachment.clearStencil = 0;
        }
    } //stencil
    
#undef M_TEXTURE
#undef M_MSAATEX
#undef M_DEPTHTEX
#undef M_STENCILTEX
}

void* GMTLContext::renderPassDescriptor()
{
    id <CAMetalDrawable> drawable = (id <CAMetalDrawable>)currentDrawable();
    if(drawable) {
        setupRenderPassDescriptor(drawable.texture);
    }
    
    return m_RenderPassDescriptor;
}

void* GMTLContext::getCommandQueue()
{
    return m_CommandQueue;
}

void* GMTLContext::getCommandBuffer()
{
    return m_CommandBuffer;
}
void* GMTLContext::getRenderEncoder()
{
    return m_RenderEncoder;
}

GX::PixelFormat GMTLContext::getPixelFormatForFB() const
{
    return M_METAL_LAYER().pixelFormat==MTLPixelFormatBGRA8Unorm?GX::PixelFormatBGRA8888:GX::PixelFormatRGBA8888;
}

void GMTLContext::loadFrameBufferNodeInMT(GObject* obj)
{
    GContext::FBNodeLoadObj& nodeObj = *GX_CAST_R(GContext::FBNodeLoadObj*, obj);
    GFrameBuffer::Handle& handle = nodeObj.nodeOut->getData();
    
    if (!nodeObj.texTarget->isKindOfClass(GTexture2D::gclass)) {
        return;
    }
    
    nodeObj.context->readyFrameBuffer();
    
    MTLRenderPassDescriptor* rpdOut=nil;
    id<MTLTexture> dsTexOut=nil;
    id<MTLTexture> ssTexOut=nil;
    id <MTLDepthStencilState> dssOut=nil;
    
    id<MTLDevice> device=GX_CAST_R(CAMetalLayer*,nodeObj.context->getWindow()->getMetalLayer()).device;
    
    rpdOut=[MTLRenderPassDescriptor renderPassDescriptor];
    
    // create a color attachment every frame since we have to recreate the texture every frame
    MTLRenderPassColorAttachmentDescriptor *colorAttachment = rpdOut.colorAttachments[0];
    colorAttachment.texture = (id<MTLTexture>)nodeObj.texTarget->getTexture();
    colorAttachment.loadAction = MTLLoadActionClear;
    GColor4F& bgdClr=nodeObj.nodeOut->m_BgdColor;
    colorAttachment.clearColor = MTLClearColorMake(bgdClr.r, bgdClr.g, bgdClr.b, bgdClr.a);
    colorAttachment.storeAction = MTLStoreActionStore;
    
    MTLPixelFormat dpFmt=(MTLPixelFormat)g_DepthPixelFormat;
    MTLPixelFormat spFmt=(MTLPixelFormat)g_StencilPixelFormat;
    if (dpFmt!=MTLPixelFormatInvalid && spFmt!=MTLPixelFormatInvalid) {
        
        MTLTextureDescriptor* desc = [MTLTextureDescriptor texture2DDescriptorWithPixelFormat:dpFmt
                                                                                        width:colorAttachment.texture.width
                                                                                       height:colorAttachment.texture.height
                                                                                    mipmapped:NO];
        
        desc.textureType = MTLTextureType2D;
        desc.sampleCount = 1;
        
        if ([desc respondsToSelector:@selector(setUsage:)]) {
            desc.usage = MTLTextureUsageUnknown;
            desc.storageMode = MTLStorageModePrivate;
        }
        
        dsTexOut = [device newTextureWithDescriptor:desc];
        
        MTLRenderPassDepthAttachmentDescriptor *depthAttachment = rpdOut.depthAttachment;
        depthAttachment.texture = dsTexOut;
        depthAttachment.loadAction = MTLLoadActionClear;
        depthAttachment.storeAction = MTLStoreActionDontCare;
        depthAttachment.clearDepth = 1.0;
        
        ssTexOut=dsTexOut;
        
        MTLRenderPassStencilAttachmentDescriptor* stencilAttachment = rpdOut.stencilAttachment;
        stencilAttachment.texture = ssTexOut;
        stencilAttachment.loadAction = MTLLoadActionClear;
        stencilAttachment.storeAction = MTLStoreActionDontCare;
        stencilAttachment.clearStencil = 0;
    }
    else if (dpFmt!=MTLPixelFormatInvalid) {
        MTLTextureDescriptor* desc = [MTLTextureDescriptor texture2DDescriptorWithPixelFormat:dpFmt
                                                                                        width:colorAttachment.texture.width
                                                                                       height:colorAttachment.texture.height
                                                                                    mipmapped:NO];
        
        desc.textureType = MTLTextureType2D;
        desc.sampleCount = 1;
        
        if ([desc respondsToSelector:@selector(setUsage:)]) {
            desc.usage = MTLTextureUsageUnknown;
            desc.storageMode = MTLStorageModePrivate;
        }
        
        dsTexOut = [device newTextureWithDescriptor:desc];
        
        MTLRenderPassDepthAttachmentDescriptor *depthAttachment = rpdOut.depthAttachment;
        depthAttachment.texture = dsTexOut;
        depthAttachment.loadAction = MTLLoadActionClear;
        depthAttachment.storeAction = MTLStoreActionDontCare;
        depthAttachment.clearDepth = 1.0;
        
    }
    else if (spFmt!=MTLPixelFormatInvalid) {
        MTLTextureDescriptor* desc = [MTLTextureDescriptor texture2DDescriptorWithPixelFormat:spFmt
                                                                                        width:colorAttachment.texture.width
                                                                                       height:colorAttachment.texture.height
                                                                                    mipmapped:NO];
        
        desc.textureType = MTLTextureType2D;
        desc.sampleCount = 1;
        
        if ([desc respondsToSelector:@selector(setUsage:)]) {
            desc.usage = MTLTextureUsageUnknown;
            desc.storageMode = MTLStorageModePrivate;
        }
        
        ssTexOut=dsTexOut;
        
        MTLRenderPassStencilAttachmentDescriptor* stencilAttachment = rpdOut.stencilAttachment;
        stencilAttachment.texture = ssTexOut;
        stencilAttachment.loadAction = MTLLoadActionClear;
        stencilAttachment.storeAction = MTLStoreActionDontCare;
        stencilAttachment.clearStencil = 0;
    }
    
    
    if (dpFmt!=MTLPixelFormatInvalid || spFmt!=MTLPixelFormatInvalid) {
        MTLDepthStencilDescriptor *dsStateDesc = [[MTLDepthStencilDescriptor alloc] init];
        dsStateDesc.depthCompareFunction = MTLCompareFunctionAlways;
        dsStateDesc.depthWriteEnabled = YES;
        dssOut=[[device newDepthStencilStateWithDescriptor:dsStateDesc] retain];
    }
    
    handle.m_Name=[rpdOut retain];
    handle.m_DepthName=[dsTexOut retain];
    handle.m_StencilTex=[ssTexOut retain];
    handle.m_DepthStencilState =[dssOut retain];
    
    nodeObj.context->doneFrameBuffer();
    
    if (handle.isValid()) {
        nodeObj.nodeOut->m_Context = nodeObj.context;
        nodeObj.nodeOut->m_TexTarget = nodeObj.texTarget;
        GO::retain(nodeObj.nodeOut->m_TexTarget);
        nodeObj.nodeOut->m_Context->addFrameBufferNodeInMT(nodeObj.nodeOut);
    }
}
void GMTLContext::unloadFrameBufferNodeForContext(GFrameBuffer::Node* node)
{
    if (node->isValid()) {
        GFrameBuffer::Handle& handle = node->getData();
        
        readyFrameBuffer();
        
        [GX_CAST_R(id, handle.m_Name) release];
        handle.m_Name = NULL;
        [GX_CAST_R(id, handle.m_DepthName) release];
        handle.m_DepthName = NULL;
        [GX_CAST_R(id, handle.m_StencilTex) release];
        handle.m_StencilTex = NULL;
        [GX_CAST_R(id, handle.m_DepthStencilState) release];
        handle.m_DepthStencilState = NULL;
        
        doneFrameBuffer();
        
        node->m_Context = NULL;
        GO::release(node->m_TexTarget);
        node->m_TexTarget = NULL;
    }
}





#endif
