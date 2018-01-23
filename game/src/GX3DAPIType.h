//
//  GX3DAPIType.h
//  GXGame
//
//  Created by Gengxin Gu on 2017/4/19.
//  Copyright © 2017年 Gengxin Gu. All rights reserved.
//

#ifndef GX3DAPIType_h
#define GX3DAPIType_h

#include "GXOS.h"

#ifndef GX_OPENGL

#if defined(GX_OS_QT) || defined(GX_OS_ANDROID) || defined(GX_OS_APPLE) || defined(GX_OS_WINDOWS)
#define GX_OPENGL
#endif

#endif

#if defined(GX_OPENGL)

#if !defined(GX_OS_DESKTOP)
#define GX_OPENGL_ES
#endif

#else

#if !defined(GX_METAL) && defined(GX_OS_APPLE)
#define GX_METAL
#endif

#if !defined(GX_DIRECTX) && defined(GX_OS_WINDOWS)
#define GX_DIRECTX
#endif

#endif


#endif /* GX3DAPIType_h */
