//
//  GXMetal.cpp
//  GX
//
//  Created by Gu Gengxin on 16/8/20.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#include "GXMetal.h"
#if defined(GX_METAL)


namespace GX {
    
    static id<MTLDevice> g_Device = NULL;
    
    id<MTLDevice> metalDevice()
    {
        if (!g_Device) {
            g_Device=[MTLCreateSystemDefaultDevice() retain];
        }
        return g_Device;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    
    MetalCullFacer::MetalCullFacer()
    {
        
    }
    
    MetalCullFacer::~MetalCullFacer()
    {
        
    }
    
    void MetalCullFacer::setCullFace(DCullFace v)
    {
        DCullFacer::setCullFace(v);
        
        id<MTLRenderCommandEncoder> rce=GX_CAST_R(id<MTLRenderCommandEncoder>, metalCFNeedRenderEncoder());
        
        if (rce) {
            [rce setCullMode:(MTLCullMode)v];
            [rce setFrontFacingWinding:MTLWindingCounterClockwise];
        }
    }
    
    void MetalCullFacer::metalCFUpdate(void* rce)
    {
        [GX_CAST_R(id<MTLRenderCommandEncoder>, rce) setCullMode:(MTLCullMode)getCullFace()];
        [GX_CAST_R(id<MTLRenderCommandEncoder>, rce) setFrontFacingWinding:MTLWindingCounterClockwise];
    }
    
    ////////////////////////////////////////////////////////////////////////////
    
    MetalBlender::MetalBlender()
    {
        
    }
    
    MetalBlender::~MetalBlender()
    {
        
    }
    
//    void MetalBlender::setBlend(DBlend v)
//    {
//        DBlender::setBlend(v);
//        
//        
//    }
}


#endif
