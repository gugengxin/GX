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
	
}

GDataWriter::~GDataWriter()
{
}

void GDataWriter::close()
{
}

bool GDataWriter::hasSpace()
{
    return false;
}

gint GDataWriter::write(void* buf,guint len)
{
    return 0;
}

bool GDataWriter::skip(guint len)
{
    return false;
}

gint GDataWriter::getBytes()
{
    return 0;
}

bool GDataWriter::canRollback()
{
    return false;
}

bool GDataWriter::rollback(guint len)
{
    return false;
}


