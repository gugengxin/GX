//
//  GTexture.cpp
//  GX
//
//  Created by Gengxin Gu on 16/6/17.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#include "GTexture.h"


#include "GXGObject.h"

GX_GOBJECT_IMPLEMENT(GTexture, GObject);


GTexture::GTexture()
{
    m_Context=NULL;
    m_Node=NULL;
}

GTexture::~GTexture()
{
    if (m_Node) {
        
    }
}
