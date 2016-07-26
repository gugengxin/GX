//
//  GRBReader.cpp
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#include "GRBReader.h"
//Down include other h file

//Up include other h file
#include "GXGObject.h"

GX_GOBJECT_IMPLEMENT(GRBReader, GReader);

GRBReader::GRBReader()
{
	
}

GRBReader::~GRBReader()
{
}


void GRBReader::close()
{


}

bool GRBReader::hasData()
{
	return false;
}
gint GRBReader::read(void* buf, guint len)
{
	return false;
}
bool GRBReader::skip(guint len)
{
	return false;
}
gint GRBReader::getBytes()
{
	return false;
}

bool GRBReader::canRollback()
{
	return false;
}
bool GRBReader::rollback(guint len)
{
	return false;
}

bool GRBReader::canGetLength()
{
	return false;
}
gint GRBReader::getLength()
{
	return false;
}


