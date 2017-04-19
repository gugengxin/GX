//
//  GXContext.h
//  GX
//
//  Created by Gengxin Gu on 2016/10/30.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GXContext_h
#define GXContext_h

#include "GXPrefix.h"
#include "GX3DAPIType.h"

#if defined(GX_OPENGL)
#define GX_CONTEXT_BASE GOGLContext
#elif defined(GX_DIRECTX)
#define GX_CONTEXT_BASE GD3DContext
#elif defined(GX_METAL)
#define GX_CONTEXT_BASE GMTLContext
#endif

#endif /* GXContext_h */
