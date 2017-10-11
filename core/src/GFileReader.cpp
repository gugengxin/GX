//
//  GFileReader.cpp
//  GX
//
//  Created by Gengxin Gu on 16/6/22.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#include "GFileReader.h"
#include "GXGObject.h"
#include "GLog.h"

GX_GOBJECT_IMPLEMENT(GFileReader, GReader);


GFileReader::GFileReader()
{
    m_Length=-1;
}

GFileReader::~GFileReader()
{

}

bool GFileReader::open(const gtchar* path)
{
    return m_File.open(path, GX::File::ModeRead);
}

void GFileReader::close()
{
    m_File.close();
}
bool GFileReader::hasData()
{
    guint8 eofData;
    gint res=m_File.read(&eofData, 1);
    if (res>=1) {
        m_File.seek(-1, GX::File::SeekCur);
        return true;
    }
    return false;
}
gint GFileReader::read(void* buf,guint len)
{
    return m_File.read(buf, len);
}
bool GFileReader::skip(guint len)
{
    return m_File.seek(GX_CAST_S(guint, len), GX::File::SeekCur);
}
gint GFileReader::getBytes()
{
    return m_File.tell();
}
bool GFileReader::canRollback()
{
    return true;
}
bool GFileReader::rollback(guint len)
{
    return m_File.seek(-GX_CAST_S(gint, len), GX::File::SeekCur);
}
bool GFileReader::canGetLength()
{
    return true;
}
gint GFileReader::getLength()
{
    if (m_Length<0) {
        gint cur=m_File.tell();
        if(!m_File.seek(0, GX::File::SeekEnd)) {
            return -1;
        }
        m_Length=m_File.tell();
        if(!m_File.seek(cur, GX::File::SeekSet)) {
			m_Length = -1;
            return -1;
        }
    }
    return m_Length;
}


