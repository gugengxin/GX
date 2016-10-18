//
//  GTexture2D.cpp
//  GX
//
//  Created by Gengxin Gu on 16/6/17.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#include "GTexture2D.h"


#include "GXGObject.h"

GX_GOBJECT_IMPLEMENT(GTexture2D, GTexture);


GTexture2D::GTexture2D()
{
    m_Width=0;
    m_Height=0;
}

GTexture2D::~GTexture2D()
{

}

void GTexture2D::config(Node* node,GDib* dib,Parameter* param)
{
    GX_UNUSED(param);

    setNode(node);
    m_Width=dib->getWidth();
    m_Height=dib->getHeight();
}

void GTexture2D::config(Node* node, GX::PixelFormat pixelFormat, gint32 width, gint32 height, Parameter* param)
{
	GX_UNUSED(pixelFormat);
	GX_UNUSED(param);

	setNode(node);
	m_Width = width;
	m_Height = height;
}
