//
//  GFileBundle.cpp
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#include "GFileBundle.h"
#include "GFileReader.h"


#include "GXGObject.h"

GX_GOBJECT_IMPLEMENT(GFileBundle, GBundle);

GFileBundle::GFileBundle()
{
}

GFileBundle::~GFileBundle()
{
}

bool GFileBundle::open(const gtchar* path)
{
    m_RootPath.setChars(path);
    return true;
}

bool GFileBundle::isOpened()
{
    return m_RootPath.getLength()>0;
}

void GFileBundle::close()
{
	m_RootPath.clear();
}

GReader* GFileBundle::openReader(GString* fileName)
{
	GString path;
    path.setString(&m_RootPath);
	path.appendPathComponent(fileName);
	GFileReader* res = GFileReader::alloc();
	if (!res->open(path.pathString())) {
		GO::release(res);
		return NULL;
	}
	return res;
}
void GFileBundle::closeReader(GReader* reader)
{
	reader->close();
	GO::release(reader);
}


