//
//  GAppBundle.cpp
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#include "GAppBundle.h"
#include "GXGObject.h"


#if defined(GX_OS_IPHONE)
#include <CoreFoundation/CoreFoundation.h>
#elif defined(GX_OS_MACOSX) || defined(GX_OS_QT_MACOSX)
#include <CoreFoundation/CoreFoundation.h>
#define M_RESOURCE_DIR_NAME "Contents/Resources"
#elif defined(GX_OS_ANDROID)
#include "GAndroidApp.h"
#define M_RESOURCE_DIR_NAME "assets"
#elif defined(GX_OS_WINDOWS) || defined(GX_OS_QT_WINDOWS)
#include <Windows.h>
#define M_RESOURCE_DIR_NAME "assets"
#endif

GX_GOBJECT_IMPLEMENT(GAppBundle, GX_APPBUNDLE_BASE);

GAppBundle* GAppBundle::main()
{
    static GAppBundle g_Obj;
    return &g_Obj;
}

GAppBundle::GAppBundle()
{
#if defined(GX_OS_APPLE) || defined(GX_OS_QT_MACOSX)
    CFBundleRef pBE=CFBundleGetMainBundle();
    CFURLRef url=CFBundleCopyBundleURL(pBE);
    CFStringRef str=CFURLCopyFileSystemPath(url, kCFURLPOSIXPathStyle);

    int num=(int)CFStringGetLength(str)*3+1;//这里需要多一个字节
    char* p=(char*)calloc((size_t)num, sizeof(char));
    CFStringGetCString(str, p, num, kCFStringEncodingUTF8);

    open(p);

    free(p);
    CFRelease(str);
    CFRelease(url);
#elif defined(GX_OS_ANDROID)
    GString* path=GAndroidApp::shared()->getPackageCodePath();
    if(path) {
        open(path->utf8String(),true);
    }
#elif defined(GX_OS_WINDOWS) || defined(GX_OS_QT_WINDOWS)
	TCHAR buf[1024];
	::GetCurrentDirectory(1024,buf);
	open(buf);
#else
#error
#endif
}

GAppBundle::~GAppBundle()
{
}

GReader* GAppBundle::openReader(GString* fileName)
{
#if defined(GX_OS_IPHONE)
	return GX_APPBUNDLE_BASE::openReader(fileName);
#elif defined(GX_OS_MACOSX) || defined(GX_OS_WINDOWS) || defined(GX_OS_ANDROID) || defined(GX_OS_QT)
    GString path;
    path.append(M_RESOURCE_DIR_NAME);
    path.appendPathComponent(fileName);
	return GX_APPBUNDLE_BASE::openReader(&path);
#else
#error
    return NULL;
#endif
}

void GAppBundle::closeReader(GReader* reader)
{
	GX_APPBUNDLE_BASE::closeReader(reader);
}
