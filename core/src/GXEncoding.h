//
//  GXEncoding.h
//  GX
//
//  Created by Gengxin Gu on 16/5/4.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GXEncoding_h
#define GXEncoding_h

#include "GXTypes.h"

namespace GX {
    typedef enum _StringEncoding {
        SE_Utf8     =0,
        SE_Utf16    =1,
        SE_Utf32    =2,
#if GX_WCHAR_16BIT
        SE_Unicode=SE_Utf16,
#elif GX_WCHAR_32BIT
        SE_Unicode=SE_Utf32,
#endif
    } StringEncoding;

	typedef enum _StringRadix {
		SR_Binary		=2,
		SR_Octal		=8,
		SR_Decimal		=10,
		SR_Hex			=16,
		SR_HEX			=17,
	} StringRadix;
}

#endif /* GXEncoding_h */
