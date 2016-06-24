//
//  GFileBundle.cpp
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#include "GFileBundle.h"
#include "GXGObject.h"

GX_GOBJECT_IMPLEMENT(GFileBundle, GBundle);

GFileBundle::GFileBundle()
{
}

GFileBundle::~GFileBundle()
{
}

GReader* GFileBundle::openReader(const gtchar* fileName)
{
	return NULL;
}
void GFileBundle::closeReader(GReader* reader)
{

}


