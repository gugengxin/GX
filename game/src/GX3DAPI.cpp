//
//  GX3DAPI.cpp
//  GXGame
//
//  Created by Gu Gengxin on 2017/6/2.
//  Copyright © 2017年 Gengxin Gu. All rights reserved.
//

#include "GX3DAPI.h"

static gint g_DrawModes[]={
    GX_POINTS,
    GX_LINES,
    GX_LINE_STRIP,
    GX_TRIANGLES,
    GX_TRIANGLE_STRIP,
};

namespace GX {
    
    gint dmodeToDrawMode(DMode dmode)
    {
        return g_DrawModes[dmode];
    }
}




