//
//  GXTypes.h
//  GX
//
//  Created by Gengxin Gu on 16/4/19.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GXTypes_h
#define GXTypes_h

#include "GXOSs.h"

typedef char                gint8;
typedef unsigned char       guint8;
typedef short               gint16;
typedef unsigned short      guint16;
typedef int                 gint32;
typedef unsigned int        guint32;
typedef long long           gint64;
typedef unsigned long long  guint64;

typedef float gfloat32;
typedef double gfloat64;

typedef char gchar;
typedef wchar_t gwchar;

#if defined(GX_OS_WINDOWS)
#define GX_WCHAR_16BIT 1
#define GX_WCHAR_32BIT 0
#else
#define GX_WCHAR_16BIT 0
#define GX_WCHAR_32BIT 1
#endif

#if defined(GX_OS_WINDOWS) && (defined(UNICODE) || defined(_UNICODE))
#define _GX_T(x) L##x
#define GX_T(x) _GX_T(x)
#define GX_PATH_IS_CHAR
#else
#define GX_T(x) x
#define GX_PATH_IS_WCHAR
#endif

#if defined (__LP64__) || defined (__64BIT__) || defined (_LP64) || (__WORDSIZE == 64) || defined(WIN64)
#define GX_PTR_32BIT  0
#define GX_PTR_64BIT  1
#else
#define GX_PTR_32BIT  1
#define GX_PTR_64BIT  0
#endif

#if GX_PTR_32BIT
typedef gint32    gint;
typedef guint32    guint;
typedef float gfloat;
#elif GX_PTR_64BIT
typedef gint64    gint;
typedef guint64    guint;
typedef double gfloat;
#endif


#define GX_CAST_C(t,o)       const_cast<t>(o)
#define GX_CAST_S(t,o)       static_cast<t>(o)
#define GX_CAST_R(t,o)       reinterpret_cast<t>(o)
#define GX_CAST_D(t,o)       GX_CAST_R(t,o)//dynamic_cast<t>(o)
#define GX_CAST_PO(t,p,ot)   GX_CAST_R(t*, GX_CAST_R(unsigned char*,p)+ot)

#define GX_COMMA ,

#define GX_IN
#define GX_OUT
#define GX_IN_OUT
#define GX_NULLABLE
#define GX_NONNULL

#endif /* GXTypes_h */
