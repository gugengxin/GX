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
    m_Mode=GX_TRIANGLE_STRIP;
}

GImage::~GImage()
{
    GO::release(m_Tex2D);
}

GVector2 GImage::getPosition(gint index)
{
    Data* p=GX_CAST_R(Data*, mapData(index));
    GVector2 res=(*p).position;
    unmapData();
    return res;
}
void GImage::setPosition(gint index,const GVector2 v)
{
    Data* p=GX_CAST_R(Data*, mapData(index));
    (*p).position=v;
    unmapData();
}
void GImage::setPosition(gint index,float x, float y)
{
    Data* p=GX_CAST_R(Data*, mapData(index));
    (*p).position.set(x, y);
    unmapData();
}

GVector2 GImage::getTexcoord(gint index)
{
    Data* p=GX_CAST_R(Data*, mapData(index));
    GVector2 res=(*p).texcoord;
    unmapData();
    return res;
}
void GImage::setTexcoord(gint index,const GVector2 v)
{
    Data* p=GX_CAST_R(Data*, mapData(index));
    (*p).texcoord=v;
    unmapData();
}
void GImage::setTexcoord(gint index,float x, float y)
{
    Data* p=GX_CAST_R(Data*, mapData(index));
    (*p).texcoord.set(x, y);
    unmapData();
}

void GImage::setDataPT(gint index,GVector2 pos,GVector2 tc)
{
    Data* p=GX_CAST_R(Data*, mapData(index));
    (*p).position=pos;
    (*p).texcoord=tc;
    unmapData();
}
void GImage::setDataPT(gint index,float posX,float posY,float tcX,float tcY)
{
    Data* p=GX_CAST_R(Data*, mapData(index));
    (*p).position.set(posX, posY);
    (*p).texcoord.set(tcX, tcY);
    unmapData();
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
gint GImage::getMode() const
{
    return m_Mode;
}
void GImage::setMode(gint v)
{
    m_Mode=v;
}
GX::DToplogy GImage::getToplogy() const
{
    return GX::DToplogyFromDrawMode(m_Mode);
}
void GImage::setToplogy(GX::DToplogy v)
{
    m_Mode=GX::DToplogyToDrawMode(v);
}

void GImage::draw(GContext& context,GCanvas* canvas)
{
    context.getSRTexture2D(false, false, GSRTexture2D::MM_None)->draw(canvas, getDataBuffer(), GSRTexture2D::IT_Float_Float, m_Tex2D, m_Mode, 0, getDataCount(), NULL);
}
