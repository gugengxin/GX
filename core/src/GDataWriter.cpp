//
//  GDataWriter.cpp
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#include "GDataWriter.h"
#include "GXGObject.h"

GX_GOBJECT_IMPLEMENT(GDataWriter, GWriter);

GDataWriter::GDataWriter()
{
    m_Data=NULL;
    m_Bytes=0;
    m_IsHold=0;
}

GDataWriter::~GDataWriter()
{
    if (m_IsHold) {
        GO::release(m_Data);
    }
}

bool GDataWriter::open(GData* data)
{
    if (!data) {
        return false;
    }
    GO::retain(data);
    GO::release(m_Data);
    m_Data=data;
    m_Bytes=0;
    m_IsHold=1;
    return true;
}
bool GDataWriter::openNotHold(GData& data)
{
    m_Data=&data;
    m_Bytes=0;
    m_IsHold=0;
    return true;
}
bool GDataWriter::open(void* buf,gint len)
{
    if (!buf || len<=0) {
        return false;
    }
    
    m_Data=GData::alloc();
    m_Data->setStatic(buf, len);
    m_Bytes=0;
    m_IsHold=1;
    return true;
}

void GDataWriter::close()
{
    if (m_IsHold) {
        GO::release(m_Data);
        m_Data=NULL;
        m_IsHold=0;
    }
    m_Bytes=0;
}

bool GDataWriter::hasSpace()
{
    return !m_Data->isStatic() || m_Bytes<m_Data->getBytes();
}

gint GDataWriter::write(const void* buf,guint len)
{
    if (m_Data->isStatic()) {
        if (m_Bytes>=m_Data->getBytes()) {
            return 0;
        }
        else if (m_Bytes+len>m_Data->getBytes()) {
            guint tempLen=m_Data->getBytes()-len;
            GX::gmemcpy(m_Data->getPtr(m_Bytes), buf, tempLen);
            m_Bytes+=tempLen;
            return (gint)tempLen;
        }
        else {
            GX::gmemcpy(m_Data->getPtr(m_Bytes), buf, len);
            m_Bytes+=len;
            return (gint)len;
        }
    }
    else {
        if (m_Bytes+len>m_Data->getBytes() && !m_Data->changeBytes(m_Bytes+len)) {
            return -1;
        }
        GX::gmemcpy(m_Data->getPtr(m_Bytes), buf, len);
        m_Bytes+=len;
        return (gint)len;
    }
}

bool GDataWriter::skip(guint len)
{
    if (m_Data->isStatic()) {
        if (m_Bytes+len>m_Data->getBytes()) {
            return false;
        }
    }
    else {
        if (m_Bytes+len>m_Data->getBytes() && !m_Data->changeBytes(m_Bytes+len)) {
            return false;
        }
    }
    return true;
}

gint GDataWriter::getBytes()
{
    return m_Bytes;
}

bool GDataWriter::canRollback()
{
    return true;
}

bool GDataWriter::rollback(guint len)
{
    if (m_Bytes>=len) {
        m_Bytes-=len;
        return true;
    }
    return false;
}


