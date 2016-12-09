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
#if defined(GX_METAL)

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

#endif

#endif /* GXMetal_h */
