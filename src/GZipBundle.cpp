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


bool GZipBundle::open(const gtchar* path)
{


	//TODO
}

void GZipBundle::close()
{

}

GReader* GZipBundle::openReader(const gchar* fileName)
{
	return NULL;
}
void GZipBundle::closeReader(GReader* reader)
{

}

