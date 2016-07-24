//
//  GXPrefix.h
//  GX
//
//  Created by Gengxin Gu on 16/4/19.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GXPrefix_h
#define GXPrefix_h


#include "GXTypes.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdarg.h>
#include <memory.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#if defined(GX_OS_ANDROID)
#include <jni.h>
#elif defined(GX_OS_QT)

#endif

#ifndef va_copy
#ifdef __va_copy
#define va_copy(DEST,SRC) __va_copy((DEST),(SRC))
#else
#define va_copy(DEST,SRC) memcpy((&DEST), (&SRC), sizeof(va_list))
#endif
#endif

#ifndef GX_DEBUG
#if defined(_DEBUG) || defined(DEBUG) || defined(QT_DEBUG)
#define GX_DEBUG
#endif
#endif

#if _MSC_VER >= 1600    // VC2010
#pragma execution_character_set("utf-8")
#endif

#ifdef GX_DEBUG
#define GX_ASSERT(e) assert(e)
#else
#define GX_ASSERT(e) assert(e)
#endif

#if defined(GX_OS_WINDOWS) && GX_PTR_32BIT
#define GX_ASM
#endif

#if defined(GX_OS_QT)
#define GX_UNUSED(x) Q_UNUSED(x)
#else
#define GX_UNUSED(x)
#endif


#endif /* GXPrefix_h */
