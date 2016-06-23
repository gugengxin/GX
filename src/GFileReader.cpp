//
//  GFileReader.cpp
//  GX
//
//  Created by Gengxin Gu on 16/6/22.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#include "GFileReader.h"
#include "GXGObject.h"
#include "GXFILE.h"

GX_GOBJECT_IMPLEMENT(GFileReader, GReader);


GFileReader::GFileReader()
{
    m_FILE=NULL;
    m_Length=-1;
}

GFileReader::~GFileReader()
{
    if (m_FILE) {
        fclose(m_FILE);
    }
}

bool GFileReader::open(const gtchar* path)
{
	m_FILE = GX::fopen(path, GX_T("rb"));
    return m_FILE!=NULL;
}

void GFileReader::close()
{
    if (m_FILE) {
        fclose(m_FILE);
        m_FILE=NULL;
    }
}
gint GFileReader::read(void* buf,guint len)
{
    size_t res=fread(buf, 1, len, m_FILE);
    if (res<len && ferror(m_FILE)!=0) {
        return -1;
    }
    return GX_CAST_S(gint, res);
}
bool GFileReader::skip(guint len)
{
	return GX::fseek(m_FILE, GX_CAST_S(gint, len), SEEK_CUR);
}
gint GFileReader::getBytes()
{
	return GX::ftell(m_FILE);
}
bool GFileReader::canRollback()
{
    return true;
}
bool GFileReader::rollback(guint len)
{
    return GX::fseek(m_FILE, -GX_CAST_S(gint, len), SEEK_CUR);
}
bool GFileReader::canGetLength()
{
    return true;
}
gint GFileReader::getLength()
{
    if (m_Length<0) {
        gint cur=GX::ftell(m_FILE);
        if(GX::fseek(m_FILE, 0, SEEK_END)) {
            return -1;
        }
        m_Length=GX::ftell(m_FILE);
        if(GX::fseek(m_FILE, cur, SEEK_SET)) {
            return -1;
        }
    }
    return m_Length;
}


