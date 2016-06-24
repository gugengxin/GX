//
//  GAppBundle.h
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#ifndef GAppBundle_h
#define GAppBundle_h

#include "GXPrefix.h"
#include "GFileBundle.h"
#include "GZipBundle.h"



#include "GXGObject.h"
// Down can't include other h file

class GAppBundle : public 
#if defined(GX_OS_WINDOWS)
	GFileBundle
#elif defined(GX_OS_ANDROID)
	GZipBundle
#endif
{
	GX_GOBJECT(GAppBundle);
public:

private:

};

// Up can't include other h file
#include "GXGObjectUD.h"

#endif /* GAppBundle_h */
