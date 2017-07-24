//
//  GImage.cpp
//  GX
//
//  Created by GuGengxin.
//  Copyright by gxengine.com
//

#include "GImage.h"
//Down include other h file
#include "GSRTexture2D.h"
#include "GContext.h"
//Up include other h file
#include "GXGObject.h"

GX_GOBJECT_IMPLEMENT(GImage, GGraphBase);

GImage::GImage()
{
    setDataStride(sizeof(Data));
    m_Tex2D=NULL;
    m_Scale=1.0f;
}

GImage::~GImage()
{
    GO::release(m_Tex2D);
}

GTexture2D* GImage::getTexture() const
{
    return m_Tex2D;
}
void GImage::setTexture(GTexture2D* tex)
{
    GX_OBJECT_SET(m_Tex2D, tex);
}

float GImage::getScale() const
{
    return m_Scale;
}
void GImage::setScale(float v)
{
    m_Scale=v;
}

void GImage::draw(GContext& context,GCanvas* canvas)
{
    //context.getSRTexture2D(false, false, GSRTexture2D::MM_None)->draw(canvas, getDataBuffer(), GSRTexture2D::IT_Float_Float, m_Tex2D, m_Mode, 0, getDataCount(), NULL);
}
