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
#if defined(GX_OS_WINDOWS) || defined(GX_OS_APPLE) || defined(GX_OS_QT)
	GFileBundle
#elif defined(GX_OS_ANDROID)
	GZipBundle
#endif
{
	GX_GOBJECT_FINAL(GAppBundle);
public:
    static GAppBundle* main();
public:
    virtual GReader* openReader(const gchar* fileName);
    virtual void closeReader(GReader* reader);
};

// Up can't include other h file
#include "GXGObjectUD.h"

#endif /* GAppBundle_h */
