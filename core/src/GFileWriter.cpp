//
//  GFileWriter.cpp
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#include "GFileWriter.h"
#include "GXFILE.h"

#include "GXGObject.h"

GX_GOBJECT_IMPLEMENT(GFileWriter, GWriter);

GFileWriter::GFileWriter()
{
    m_FILE=NULL;
    m_BytesStart=0;
}

GFileWriter::~GFileWriter()
{
    if (m_FILE) {
        fclose(m_FILE);
    }
}

bool GFileWriter::open(const gtchar* path,bool append)
{
    m_FILE=GX::fopen(path, append?GX_T("ab"):GX_T("wb"));
    if (m_FILE) {
        m_BytesStart=(guint)GX::ftell(m_FILE);
        return true;
    }
    return false;
}

void GFileWriter::close()
{
    if (m_FILE) {
        fclose(m_FILE);
        m_FILE=NULL;
    }
}

bool GFileWriter::hasSpace()
{
    return true;
}

gint GFileWriter::write(const void* buf,guint len)
{
    return (gint)fwrite(buf, 1, len, m_FILE);
}

bool GFileWriter::skip(guint len)
{
    return GX::fseek(m_FILE, (gint)len, SEEK_CUR)==0;
}

gint GFileWriter::getBytes()
{
    return (gint)GX::ftell(m_FILE)-(gint)m_BytesStart;
}

bool GFileWriter::canRollback()
{
    return true;
}

bool GFileWriter::rollback(guint len)
{
    return GX::fseek(m_FILE, -(gint)len, SEEK_CUR)==0;
}


