//
//  GDataReader.cpp
//  GX
//
//  Created by Gengxin Gu on 16/6/22.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#include "GDataReader.h"
#include "GXGObject.h"

GX_GOBJECT_IMPLEMENT(GDataReader, GReader);

GDataReader::GDataReader()
{
	m_Data=NULL;
	m_Cursor=0;
}

GDataReader::~GDataReader()
{
	GO::release(m_Data);
}

bool GDataReader::open(GData* data)
{
	GO::retain(data);
	GO::release(m_Data);
	m_Data = data;
	m_Cursor = 0;
	return m_Data != NULL;
}

void GDataReader::close()
{
	GO::release(m_Data);
	m_Data = NULL;
	m_Cursor = 0;
}
bool GDataReader::hasData()
{
	return m_Cursor < m_Data->getBytes();
}
gint GDataReader::read(void* buf,guint len)
{
	guint lenAll=m_Data->getBytes();
	if (m_Cursor >= lenAll) {
		return 0;
	}
	guint res;
	if (m_Cursor + len > lenAll) {
		res = lenAll - m_Cursor;
	}
	else {
		res = len;
	}
	GX::gmemcpy(buf, m_Data->getPtr(GX_CAST_S(guint, m_Cursor)), res);
	m_Cursor += res;
    return GX_CAST_S(gint,res);
}
bool GDataReader::skip(guint len)
{
	guint lenAll = m_Data->getBytes();
	if (m_Cursor +len > lenAll) {
		return false;
	}
	m_Cursor += len;
	return true;
}
gint GDataReader::getBytes()
{
	return GX_CAST_S(gint, m_Cursor);
}
bool GDataReader::canRollback()
{
    return true;
}
bool GDataReader::rollback(guint len)
{
	if (m_Cursor < len) {
		return false;
	}
	m_Cursor -= len;
    return true;
}
bool GDataReader::canGetLength()
{
    return true;
}
gint GDataReader::getLength()
{
	return GX_CAST_S(gint, m_Data->getBytes());
}
