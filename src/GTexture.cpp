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

GTexture::Node::Node(GContext* cnt) : GDataList<GTexture*>::Node()
{
    m_Context=cnt;
#ifdef GX_OPENGL
    m_Name=0;
#elif defined(GX_DIRECTX)
    m_Name=NULL;
    m_SamplerState=NULL;
#endif
}
GTexture::Node::~Node()
{
#ifdef GX_OPENGL
    if (m_Name) {
        glDeleteTextures(1, &m_Name);
    }
#elif defined(GX_DIRECTX)
#error
#endif
}



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
