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
