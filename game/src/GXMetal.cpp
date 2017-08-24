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
    
    MetalViewport::MetalViewport()
    {
        originX=0.0;
        originY=0.0;
        width=0.0;
        height=0.0;
        znear=0.0;
        zfar=1.0;
    }
    
    ////////////////////////////////////////////////////////////////////////////
#define M_MBC_BUFFER_MAX_LEN    (1024*4)
#if defined(GX_OS_IPHONE)
#define M_MBC_BUFFER_STEP 16
#elif defined(GX_OS_MACOSX)
#define M_MBC_BUFFER_STEP 256
#endif
    
    MetalBufferCache* MetalBufferCache::shared()
    {
        static MetalBufferCache g_Obj;
        return &g_Obj;
    }
    
    MetalBufferCache::MetalBufferCache()
    {
        m_BufIndex=0;
        memset(m_BufKeys, 0, sizeof(m_BufKeys));
    }
    
    MetalBufferCache::~MetalBufferCache()
    {
        for (gint i=0; i<m_BufDatas.getCount(); i++) {
            [GX_CAST_R(id, m_BufDatas.get(i).buffer) release];
        }
    }
    
    MetalBufferCache::Buffer MetalBufferCache::requestBuffer(Type type,guint8 ID[16],guint len)
    {
        GX_ASSERT(len<=M_MBC_BUFFER_MAX_LEN);
        
        len=(len+M_MBC_BUFFER_STEP-1)/M_MBC_BUFFER_STEP*M_MBC_BUFFER_STEP;
        
        if (m_BufKeys[type].enable && memcmp(m_BufKeys[type].ID, ID, sizeof(m_BufKeys[type].ID))==0) {
            Buffer res;
            res.buffer=m_BufDatas.get(m_BufKeys[type].pos.index).buffer;
            res.offset=m_BufKeys[type].pos.offset;
            return res;
        }
        
        if (m_BufIndex>=m_BufDatas.getCount()) {
            BufData data;
            data.buffer=[[metalDevice() newBufferWithLength:M_MBC_BUFFER_MAX_LEN options:MTLResourceCPUCacheModeDefaultCache] retain];
            data.length=0;
            m_BufDatas.add(data);
        }
        BufData& bd=m_BufDatas.get(m_BufIndex);
        if (M_MBC_BUFFER_MAX_LEN-bd.length<len) {
            BufData data;
            data.buffer=[[metalDevice() newBufferWithLength:M_MBC_BUFFER_MAX_LEN options:MTLResourceCPUCacheModeDefaultCache] retain];
            data.length=0;
            m_BufDatas.add(data);
            
            bd=m_BufDatas.last();
            m_BufIndex++;
        }
        Buffer res;
        res.buffer=bd.buffer;
        res.offset=bd.length;
        bd.length+=len;
        
        m_BufKeys[type].pos.index=m_BufIndex;
        m_BufKeys[type].pos.offset=res.offset;
        memcpy(m_BufKeys[type].ID,ID,sizeof(m_BufKeys[type].ID));
        m_BufKeys[type].enable=true;
        return res;
    }
    void MetalBufferCache::pushBuffer()
    {
        BufPos pos;
        pos.index=m_BufIndex;
        if (pos.index<m_BufDatas.getCount()) {
            pos.offset=m_BufDatas.get(pos.index).length;
        }
        else {
            pos.offset=0;
        }
        
        m_BufPoss.push(pos);
        memset(m_BufKeys, 0, sizeof(m_BufKeys));
    }
    void MetalBufferCache::popBuffer()
    {
        BufPos pos=m_BufPoss.pop();
        m_BufIndex=pos.index;
        for (gint i=m_BufDatas.getCount(); i>=m_BufIndex+1; --i) {
            m_BufDatas.get(i).length=0;
        }
        if (pos.index<m_BufDatas.getCount()) {
            m_BufDatas.get(pos.index).length=pos.offset;
        }
        else {
            m_BufDatas.get(pos.index).length=0;
        }
        memset(m_BufKeys, 0, sizeof(m_BufKeys));
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
    }
    
    void MetalCullFacer::applyToRCE(void* rce)
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
}


#endif
