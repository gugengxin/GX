//
//  GBundle.cpp
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#include "GBundle.h"
#include "GXGObject.h"

GX_GOBJECT_IMPLEMENT(GBundle, GObject);

GBundle::GBundle()
{
	
}

GBundle::~GBundle()
{
}

GReader* GBundle::openReader(const gchar* fileName)
{
	GString str;
	str.setChars(fileName);
	return openReader(&str);
}

