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
#include <string.h>

#ifndef va_copy
#ifdef __va_copy
#define va_copy(DEST,SRC) __va_copy((DEST),(SRC))
#else
#define va_copy(DEST, SRC) memcpy((&DEST), (&SRC), sizeof(va_list))
#endif
#endif

#ifndef GX_DEBUG
#if defined(_DEBUG) || defined(DEBUG)
#define GX_DEBUG
#endif
#endif



#endif /* GXPrefix_h */
