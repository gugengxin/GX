//
//  GImage.cpp
//  GX
//
//  Created by GuGengxin.
//  Copyright by gxengine.com
//

#include "GImage.h"
//Down include other h file

//Up include other h file
#include "GXGObject.h"

GX_GOBJECT_IMPLEMENT(GImage, GObject);

GImage::GImage()
{
    m_Tex2D=NULL;
    setDataStride(sizeof(Data));
}

GImage::~GImage()
{
    GO::release(m_Tex2D);
}

guint GImage::getDataStride()
{
    return GX_CAST_S(guint, m_DataBuf.getStride());
}
void GImage::setDataStride(guint v)
{
    m_DataBuf.setStride(GX_CAST_S(guint16, v));
}

void* GImage::mapData(gint index)
{
    return GX_CAST_R(guint8*, m_DataBuf.map())+index*m_DataBuf.getStride();
}
void GImage::unmapData()
{
    m_DataBuf.unmap();
}

bool GImage::changeDataCount(guint count)
{
    return m_DataBuf.changeCount(count);
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

