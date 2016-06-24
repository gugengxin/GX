//
//  GZipWriter.cpp
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#include "GZipWriter.h"
#include "GXGObject.h"

GX_GOBJECT_IMPLEMENT(GZipWriter, GWriter);

GZipWriter::GZipWriter()
{
	
}

GZipWriter::~GZipWriter()
{
}


void GZipWriter::close()
{
}

bool GZipWriter::hasSpace()
{
    return false;
}

gint GZipWriter::write(void* buf,guint len)
{
    return 0;
}

bool GZipWriter::skip(guint len)
{
    return false;
}

gint GZipWriter::getBytes()
{
    return 0;
}

bool GZipWriter::canRollback()
{
    return false;
}

bool GZipWriter::rollback(guint len)
{
    return false;
}

