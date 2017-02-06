//
//  GXOSs.h
//  GX
//
//  Created by Gengxin Gu on 16/4/19.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GXOSs_h
#define GXOSs_h


#define GX_LITTLE_ENDIAN 1234
#define GX_BIG_ENDIAN 4321

#if defined(GX_OS_QT)
#include <QtCore>
#if defined(Q_OS_WIN)
#define GX_OS_QT_WINDOWS
#elif defined(Q_OS_OSX)
#define GX_OS_QT_MACOSX
#else
#error
#endif
#elif defined(__APPLE__)
#include <TargetConditionals.h>

#define GX_OS_APPLE
#define GX_IDE_XCODE

/* record
    #if defined(_WIN32) || defined(__SYMBIAN32__)
        #define SK_BUILD_FOR_WIN32
    #elif defined(ANDROID) || defined(__ANDROID__)
        #define SK_BUILD_FOR_ANDROID
    #elif defined(linux) || defined(__linux) || defined(__FreeBSD__) || \
          defined(__OpenBSD__) || defined(__sun) || defined(__NetBSD__) || \
          defined(__DragonFly__) || defined(__Fuchsia__) || \
          defined(__GLIBC__) || defined(__GNU__) || defined(__unix__)
        #define SK_BUILD_FOR_UNIX
    #elif TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
        #define SK_BUILD_FOR_IOS
    #else
        #define SK_BUILD_FOR_MAC
    #endif
//*/



#if TARGET_OS_IOS

#define GX_OS_IOS
#define GX_OS_MOBILE
#define GX_OS_IPHONE

#elif TARGET_OS_TV

#define GX_OS_APPLETV
#define GX_OS_MOBILE
#define GX_OS_IPHONE

#elif TARGET_OS_OSX

#define GX_OS_MACOSX
#define GX_OS_DESKTOP

#else

#error Unsupport OS

#endif



#elif defined(WIN32) || defined(WIN64)

#define GX_OS_MICROSOFT
#define GX_OS_DESKTOP
#define GX_OS_WINDOWS
#define GX_IDE_VS

#elif defined(GX_OS_ANDROID)

#define GX_OS_GOOGLE
#define GX_OS_MOBILE
#define GX_IDE_AS

#endif

#define GX_BYTE_ORDER GX_LITTLE_ENDIAN

#ifndef GX_OPENGL
#if defined(GX_OS_QT) \
    || defined(GX_OS_ANDROID) \
    || defined(GX_OS_APPLE) \
    || defined(GX_OS_WINDOWS) \

#define GX_OPENGL

#endif

#endif

#if defined(GX_OPENGL)

#if defined(GX_OS_MOBILE)
#define GX_OPENGL_ES
#endif

#else

#if !defined(GX_METAL) && defined(GX_OS_APPLE)
#define GX_METAL
#endif

#if !defined(GX_DIRECTX) && defined(GX_OS_WINDOWS)
#define GX_DIRECTX
#endif

#endif




#endif /* GXOSs_h */
