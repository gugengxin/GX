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
    
    gint DToplogyToDrawMode(DToplogy dt)
    {
        return g_DrawModes[dt];
    }
	DToplogy DToplogyFromDrawMode(gint mode)
	{
		for (size_t i = 0; i < sizeof(g_DrawModes)/sizeof(g_DrawModes[0]); i++) {
			if (mode == g_DrawModes[i]) {
				return GX_CAST_S(DToplogy, i);
			}
		}
		return DToplogyUnknown;
	}
    
    
    
    DCullFacer::DCullFacer()
    {
        m_Value=DCullFaceBack;
    }
    
    DCullFacer::~DCullFacer()
    {
        
    }
    
    DCullFace DCullFacer::getCullFace() const
    {
        return m_Value;
    }
    void DCullFacer::setCullFace(DCullFace v)
    {
        m_Value = v;
    }
    
}




