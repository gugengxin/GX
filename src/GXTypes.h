//
//  GXTypes.h
//  GX
//
//  Created by Gengxin Gu on 16/4/19.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GXTypes_h
#define GXTypes_h

typedef char                gi8;
typedef unsigned char       gu8;
typedef short               gi16;
typedef unsigned short      gu16;
typedef int                 gi32;
typedef unsigned int        gu32;
typedef long long           gi64;
typedef unsigned long long  gu64;

typedef char gchar;
typedef wchar_t gwchar;

#if defined (__LP64__) || defined (__64BIT__) || defined (_LP64) || (__WORDSIZE == 64) || defined(WIN64)
#define GX_PTR_32BIT  0
#define GX_PTR_64BIT  1
#else
#define GX_PTR_32BIT  1
#define GX_PTR_64BIT  0
#endif

#if GX_PTR_32BIT
typedef gi32    gint;
typedef gu32    guint;
#elif GX_PTR_64BIT
typedef gi64    gint;
typedef gu64    guint;
#endif


#define GX_CAST_C(t,o)       const_cast<t>(o)
#define GX_CAST_S(t,o)       static_cast<t>(o)
#define GX_CAST_R(t,o)       reinterpret_cast<t>(o)
#define GX_CAST_D(t,o)       GX_CAST_R(t,o)//dynamic_cast<t>(o)
#define GX_CAST_PO(t,p,ot)   GX_CAST_R(t*, GX_CAST_R(unsigned char*,p)+ot)


#define GX_IN
#define GX_OUT
#define GX_IN_OUT
#define GX_NULLABLE
#define GX_NONNULL


#endif /* GXTypes_h */
