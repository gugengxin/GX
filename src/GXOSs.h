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

#if defined(GX_OS_IOS)

#define GX_OS_APPLE
#define GX_OS_IPHONE
#define GX_IDE_XCODE

#elif defined(GX_OS_APPLETV)

#define GX_OS_APPLE
#define GX_OS_IPHONE
#define GX_IDE_XCODE

#elif defined(GX_OS_MACOSX)

#define GX_OS_APPLE
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

#endif

#define GX_BYTE_ORDER GX_LITTLE_ENDIAN



#endif /* GXOSs_h */
