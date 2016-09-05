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
    friend class GContext;
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
    void config(Node* node,GDib* dib,Parameter* param);
    
private:
    gint32 m_Width;
    gint32 m_Height;
};

#include "GXGObjectUD.h"

#endif /* GTexture2D_h */
