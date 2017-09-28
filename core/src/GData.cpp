//
//  GData.cpp
//  GX
//
//  Created by Gengxin Gu on 16/4/27.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#include "GData.h"
#include "GXMemory.h"

#include "GXGObject.h"

GX_GOBJECT_IMPLEMENT(GData, GObject);

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
	if (m_IsStatic) {
		return (toSize == m_Bytes);
	}
	else {
		if (toSize == m_Bytes) {
			return true;
		}
	}
    
#if GX_PTR_32BIT
    if (toSize&0x80000000) {
        return false;
    }
#elif GX_PTR_64BIT
    if (toSize&0x8000000000000000ULL) {
        return false;
    }
#endif
    if (GX::grealloc(m_Buffer, m_Bytes, toSize)) {
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

bool GData::robOther(GData* other)
{
    freeSelf();
    
    m_Buffer=other->m_Buffer;
    m_Bytes=other->m_Bytes;
    m_IsStatic=other->m_IsStatic;
    
    other->m_Buffer=NULL;
    other->m_Bytes=0;
    other->m_IsStatic=0;
	return true;
}

void GData::zeroSelf()
{
    memset(m_Buffer, 0, m_Bytes);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const GX::UUID g_UUID(0x6364327B, 0x65633536, 0x34622D32, 0x342D6435);

const GX::UUID& GData::seGetUUID()
{
	return g_UUID;
}
gint GData::seGetBytes()
{
	gint res = seBytesOfKeyAndData(SKBuf, m_Bytes);
	return res;
}
gint GData::seEncodeFields(GEncoder& coder)
{
	gint res = seEncodeKeyAndData(coder, SKBuf, m_Buffer, m_Bytes);
	return res;
}


const GX::UUID& GData::ueGetUUID()
{
	return g_UUID;
}

gint GData::ueDecodeField(GDecoder& coder, guint32 key, guint32 len)
{
	switch (key)
	{
	case SKBuf:
	{
		if (changeBytes(len)) {
			return ueDecodeData(coder, m_Buffer, len);
		}
		return -1;
	}
	break;
	default:
		return 0;
	}
}
