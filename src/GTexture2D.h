//
//  GTexture2D.h
//  GX
//
//  Created by Gengxin Gu on 16/6/17.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GTexture2D_h
#define GTexture2D_h

#include "GXPrefix.h"
#include "GTexture.h"
#include "GDib.h"

#include "GXGObject.h"

class GTexture2D : public GTexture {
    GX_GOBJECT(GTexture2D);
public:
	class Parameter {
	public:
		gint32 filter;
		gint32 wrapU;
		gint32 wrapV;
	};


public:
    
    
private:
    
};

#include "GXGObjectUD.h"

#endif /* GTexture2D_h */
