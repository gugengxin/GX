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
#elif defined(GX_OS_IOS)

#define GX_OS_APPLE
#define GX_OS_MOBILE
#define GX_OS_IPHONE
#define GX_IDE_XCODE

#elif defined(GX_OS_APPLETV)

#define GX_OS_APPLE
#define GX_OS_MOBILE
#define GX_OS_IPHONE
#define GX_IDE_XCODE

#elif defined(GX_OS_MACOSX)

#define GX_OS_APPLE
#define GX_OS_DESKTOP
#define GX_IDE_XCODE

#elif defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP)

#define GX_OS_MICROSOFT
#define GX_OS_MOBILE
#define GX_OS_WINPHONE
#define GX_IDE_VS

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
#if defined(GX_OS_APPLE) || defined(GX_OS_ANDROID) || defined(GX_OS_QT) //|| defined(GX_OS_WINDOWS)
#define GX_OPENGL
#if defined(GX_OS_MOBILE)
#define GX_OPENGL_ES
#endif
#endif
#endif

#if !defined(GX_OPENGL) && !defined(GX_DIRECTX)
#if defined(GX_OS_WINDOWS)
#define GX_DIRECTX
#endif
#endif



#endif /* GXOSs_h */
