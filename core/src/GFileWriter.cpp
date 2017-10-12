//
//  GFileWriter.cpp
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#include "GFileWriter.h"
#include "GXFile.h"

#include "GXGObject.h"

GX_GOBJECT_IMPLEMENT(GFileWriter, GWriter);

GFileWriter::GFileWriter()
{
    m_BytesStart=0;
}

GFileWriter::~GFileWriter()
{

}

bool GFileWriter::open(const gtchar* path,bool append)
{
    return m_File.open(path, append?GX::File::ModeWriteAppend:GX::File::ModeWrite);
}

void GFileWriter::close()
{
    m_File.close();
}

bool GFileWriter::hasSpace()
{
    return true;
}

gint GFileWriter::write(const void* buf,guint len)
{
    return m_File.write(buf, len);
}

bool GFileWriter::skip(guint len)
{
    return m_File.seek((gint)len, GX::File::SeekCur);
}

gint GFileWriter::getBytes()
{
    return m_File.tell()-(gint)m_BytesStart;
}

bool GFileWriter::canRollback()
{
    return true;
}

bool GFileWriter::rollback(guint len)
{
    return m_File.seek(-GX_CAST_S(gint, len), GX::File::SeekCur);
}


