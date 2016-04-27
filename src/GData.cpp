//
//  GData.cpp
//  GX
//
//  Created by Gengxin Gu on 16/4/27.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#include "GData.h"
#include <stdlib.h>
#include <memory.h>


bool GData::galloc(void*& buf,guint size,guint toSize)
{
    if(toSize<=0) {
        if (buf) {
            ::free(buf);
            buf=NULL;
        }
    }
    else if (buf) {
        void* p=realloc(buf, (size_t)toSize);
        if (p) {
            if (toSize>size) {
                memset(((char*)p)+size, 0, toSize-size);
            }
            buf=p;
        }
        else {
            return false;
        }
    }
    else {
        buf=calloc(1, toSize);
        return buf!=NULL;
    }
    return true;
}


GX_OBJECT_IMPLEMENT(GData, GObject);

GData::GData()
{
    m_Buffer=NULL;
#if GX_PTR_32BIT
    m_Bytes=0;
#elif GX_PTR_64BIT
    m_Bytes=0ULL;
#endif
    m_IsStatic=0;
}

GData::~GData()
{
    if (!m_IsStatic && m_Buffer) {
        ::free(m_Buffer);
    }
}

bool GData::changeBytes(guint toSize)
{
    if(m_IsStatic && toSize!=m_Bytes)
        return false;
    
#if GX_PTR_32BIT
    if (toSize&0x80000000) {
        return false;
    }
#elif GX_PTR_64BIT
    if (toSize&0x8000000000000000ULL) {
        return false;
    }
#endif
    if (galloc(m_Buffer, m_Bytes, toSize)) {
        m_Bytes=toSize;
        return true;
    }
    return false;
}

bool GData::changeBytesIfNeed(guint toSize)
{
    if (toSize<=m_Bytes) {
        return true;
    }
    return changeBytes(toSize);
}

void GData::setStatic(const void* data,guint bytes)
{
    freeSelf();
    m_Buffer=(void*)data;
    m_Bytes=bytes;
    m_IsStatic=1;
}

void GData::freeSelf()
{
    if(!m_IsStatic && m_Buffer) {
        ::free(m_Buffer);
    }
    m_Buffer=NULL;
    m_Bytes=0;
    m_IsStatic=0;
}

void GData::robOther(GData* other)
{
    freeSelf();
    
    m_Buffer=other->m_Buffer;
    m_Bytes=other->m_Bytes;
    m_IsStatic=other->m_IsStatic;
    
    other->m_Buffer=NULL;
    other->m_Bytes=0;
    other->m_IsStatic=0;
}
