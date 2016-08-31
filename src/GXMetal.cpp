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
    
    id<MTLDevice> MetalDevice()
    {
        if (!g_Device) {
            g_Device=[MTLCreateSystemDefaultDevice() retain];
        }
        return g_Device;
    }
}


#endif