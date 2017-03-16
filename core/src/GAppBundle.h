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

#if defined(GX_OS_WINDOWS) || defined(GX_OS_APPLE) || defined(GX_OS_QT)
#define GX_APPBUNDLE_BASE GFileBundle
#elif defined(GX_OS_ANDROID)
#define GX_APPBUNDLE_BASE GZipBundle
#endif

class GAppBundle : public GX_APPBUNDLE_BASE
{
	GX_FINAL_GOBJECT(GAppBundle);
public:
    static GAppBundle* main();
public:
	using GX_APPBUNDLE_BASE::openReader;
    virtual GReader* openReader(GString* fileName);
    virtual void closeReader(GReader* reader);
};

// Up can't include other h file
#include "GXGObjectUD.h"

#endif /* GAppBundle_h */
