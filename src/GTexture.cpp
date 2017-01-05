//
//  GTexture.cpp
//  GX
//
//  Created by Gengxin Gu on 16/6/17.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#include "GTexture.h"
#include "GContext.h"

#include "GXGObject.h"

GX_GOBJECT_IMPLEMENT(GTexture, GObject);

GTexture::Handle::Handle()
{
#if defined(GX_OPENGL)
    m_Name = 0;
#elif defined(GX_DIRECTX)
    m_Name = NULL;
    m_SamplerState = NULL;
#elif defined(GX_METAL)
    m_Name=NULL;
    m_SamplerState=NULL;
#endif
}

GTexture::Handle::~Handle()
{
    
}

bool GTexture::Handle::isValid()
{
#if defined(GX_OPENGL)
    return m_Name != 0;
#elif defined(GX_DIRECTX) || defined(GX_METAL)
    return m_Name != NULL;
#endif
}

GTexture::Node::Node()
{
    m_Context=NULL;
}

GTexture::Node::~Node()
{

}

GTexture::GTexture()
{
    m_Node=NULL;
}

GTexture::~GTexture()
{
    if (m_Node && m_Node->getContext()) {
        m_Node->getContext()->unloadTextureNode(m_Node);
    }
}

GTexture::Name GTexture::getName()
{
    if (m_Node) {
        return m_Node->getData().getName();
    }
#if defined(GX_OPENGL)
    return 0;
#else
    return NULL;
#endif
}
