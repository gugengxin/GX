//
//  GGraphBase.cpp
//  GX
//
//  Created by GuGengxin.
//  Copyright by gxengine.com
//

#include "GGraphBase.h"
//Down include other h file

//Up include other h file
#include "GXGObject.h"

GX_GOBJECT_IMPLEMENT(GGraphBase, GObject);

GGraphBase::GGraphBase()
{
	
}

GGraphBase::~GGraphBase()
{
}

guint GGraphBase::getDataStride()
{
    return GX_CAST_S(guint, m_DataBuf.getStride());
}
void GGraphBase::setDataStride(guint v)
{
    m_DataBuf.setStride(GX_CAST_S(guint16, v));
}

void* GGraphBase::mapData()
{
    return m_DataBuf.map();
}

void* GGraphBase::mapData(gint index)
{
    return GX_CAST_R(guint8*, m_DataBuf.map())+index*m_DataBuf.getStride();
}
void GGraphBase::unmapData()
{
    m_DataBuf.unmap();
}

gint GGraphBase::getDataCount()
{
    return m_DataBuf.getCount();
}

bool GGraphBase::changeDataCount(guint count)
{
    return m_DataBuf.changeCount(count);
}

GDataBuffer* GGraphBase::getDataBuffer()
{
    return &m_DataBuf;
}
