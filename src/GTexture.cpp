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


GTexture::Node::Node(GContext* cnt,GTexture* tex) :
GDataList<GTexture*>::Node()
{
    m_Context=cnt;
    setData(tex);
}
GTexture::Node::~Node()
{
    
}



GTexture::GTexture()
{
    m_Node=NULL;
#ifdef GX_OPENGL
    m_Name=0;
#elif defined(GX_DIRECTX)
	m_Name=NULL;
	m_SamplerState=NULL;
#endif
}

GTexture::~GTexture()
{
    if (m_Node) {
        
    }
}
