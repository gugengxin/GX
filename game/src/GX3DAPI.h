//
//  GX3DAPI.h
//  GX
//
//  Created by Gengxin Gu on 2016/10/30.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GX3DAPI_h
#define GX3DAPI_h


#include "GX3DAPIType.h"
#include "GX3DAPIPre.h"

#include "GXOpenGL.h"
#include "GXDirectX.h"
#include "GXMetal.h"

#if defined(GX_OPENGL)
#define GX_3D_CULL_FACER    GX::OpenGLCullFacer
#define GX_3D_BLENDER       GX::OpenGLBlender
#elif defined(GX_DIRECTX)
#define GX_3D_CULL_FACER    GX::Direct3DCullFacer
#define GX_3D_BLENDER       GX::Direct3DBlender
#elif defined(GX_METAL)
#define GX_3D_CULL_FACER    GX::MetalCullFacer
#define GX_3D_BLENDER       GX::MetalBlender
#endif

namespace GX {
    
    gint DToplogyToDrawMode(DToplogy dt);
	DToplogy DToplogyFromDrawMode(gint mode);
    
}


#endif /* GX3DAPI_h */
