//
//  GXFreeTypeLib.h
//  GXFreeTypeLib
//
//  Created by Gu Gengxin on 15/1/10.
//  Copyright (c) 2015 Gu Gengxin. All rights reserved.
//

#ifndef GXFreeType_GXFreeTypeLib_h
#define GXFreeType_GXFreeTypeLib_h

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_OUTLINE_H
#include FT_STROKER_H
#include FT_GLYPH_H

#if (defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP)) || (defined(WIN32) || defined(WIN64))
#if defined (__LP64__) || defined (__64BIT__) || defined (_LP64) || (__WORDSIZE == 64) || defined(WIN64)
#if defined(_DEBUG)
#pragma comment(lib, "GXFreeTypex64Debug.lib")
#else
#pragma comment(lib, "GXFreeTypex64.lib")
#endif
#else
#if defined(_DEBUG)
#pragma comment(lib, "GXFreeTypeWin32Debug.lib")
#else
#pragma comment(lib, "GXFreeTypeWin32.lib")
#endif
#endif
#endif

#endif
