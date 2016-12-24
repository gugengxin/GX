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
    m_RootPath.set(path);
    return true;
}

void GFileBundle::close()
{
	m_RootPath.clear();
}

GReader* GFileBundle::openReader(const gchar* fileName)
{
	GString path;
    path.set(&m_RootPath);
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


