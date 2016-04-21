//
//  GCShared.h
//  gx_sed
//
//  Created by Gengxin Gu on 16/4/20.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GCShared_h
#define GCShared_h

#if (defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP)) || defined(WIN32) || defined(WIN64)
#define GC_OS_MICROSOFT
#elif defined(GC_OS_MACOSX)
#define GC_OS_APPLE
#endif

#endif /* GCShared_h */
