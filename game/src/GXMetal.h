//
//  GXMetal_h
//  GX
//
//  Created by Gu Gengxin on 16/8/20.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GXMetal_h
#define GXMetal_h

#include "GXPrefix.h"
#include "GX3DAPIType.h"
#if defined(GX_METAL)
#include "GX3DAPIPre.h"
#include "GDataArray.h"

#ifdef __OBJC__
#import <Metal/Metal.h>

namespace GX {
    id<MTLDevice> metalDevice();
}

#endif

#define GX_POINTS               0
#define GX_LINES                1
#define GX_LINE_STRIP           2
#define GX_TRIANGLES            3
#define GX_TRIANGLE_STRIP       4
			
#define GX_INDEX16              0
#define GX_INDEX32              1

#define GX_FILTER_MIN_MAG_POINT             0
#define GX_FILTER_MIN_POINT_MAG_LINEAR      1
#define GX_FILTER_MIN_LINEAR_MAG_POINT      2
#define GX_FILTER_MIN_MAG_LINEAR            3

#define GX_WARP_REPEAT          2
#define GX_WARP_MIRRORED        3
#define GX_WARP_CLAMP           0


namespace GX {
    class MetalViewport {
    public:
        MetalViewport();
    public:
        double originX;
        double originY;
        double width;
        double height;
        double znear;
        double zfar;
    };
    
    class MetalBufferCache {
    public:
        static MetalBufferCache* shared();
    private:
        MetalBufferCache();
        ~MetalBufferCache();
    public:
        enum Type {
            TypeMatrixMVP,
            TypeColorMul,
            
            TypeCount,
        };
        class Buffer {
        public:
            Buffer(): buffer(NULL),offset(0) {}
            void* buffer;
            guint offset;
        };
        Buffer requestBuffer(Type type,guint8 ID[16],guint len);
        void pushBuffer();
        void popBuffer();
    private:
        class BufData {
        public:
            void* buffer;
            guint length;
        };
        class BufPos {
        public:
            gint index;
            guint offset;
        };
        class BufKey {
        public:
            bool enable;
            BufPos pos;
            guint8 ID[16];
        };
    private:
        GPDArray<BufData>   m_BufDatas;
        gint                m_BufIndex;
        GPDArray<BufPos>    m_BufPoss;
        BufKey              m_BufKeys[TypeCount];
    };
    
    class MetalCullFacer : public DCullFacer {
    public:
        MetalCullFacer();
        virtual ~MetalCullFacer();
        
        virtual void setCullFace(DCullFace v);
        
    protected:
        void applyToRCE(void* rce);
    };
    
    class MetalBlender : public DBlender {
    public:
        MetalBlender();
        virtual ~MetalBlender();
    };
}


#endif

#endif /* GXMetal_h */
