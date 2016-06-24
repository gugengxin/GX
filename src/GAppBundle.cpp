//
//  GAppBundle.cpp
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#include "GAppBundle.h"
#include "GXGObject.h"

#if defined(GX_OS_WINDOWS)
GX_GOBJECT_IMPLEMENT(GAppBundle, GFileBundle);
#elif defined(GX_OS_ANDROID)
GX_GOBJECT_IMPLEMENT(GAppBundle, GZipBundle);
#endif

GAppBundle::GAppBundle()
{
	
}

GAppBundle::~GAppBundle()
{
}


