//
//  GZipBundle.cpp
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#include "GZipBundle.h"
#include "GXGObject.h"

GX_GOBJECT_IMPLEMENT(GZipBundle, GBundle);

GZipBundle::GZipBundle()
{
	
}

GZipBundle::~GZipBundle()
{

}

GReader* GZipBundle::openReader(const gtchar* fileName)
{
	return NULL;
}
void GZipBundle::closeReader(GReader* reader)
{

}

