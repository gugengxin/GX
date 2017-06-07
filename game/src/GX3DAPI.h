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

#elif defined(GX_DIRECTX)

#elif defined(GX_METAL)
#define GX_3D_CULLFACER GX::MetalCullFacer
#endif

namespace GX {
    

    
    gint DToplogyToDrawMode(DToplogy dt);
	DToplogy DToplogyFromDrawMode(gint mode);
    
    
}


#endif /* GX3DAPI_h */
