//
//  GXPixel.h
//  GX
//
//  Created by Gengxin Gu on 16/7/27.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GXPixel_h
#define GXPixel_h

#include "GXTypes.h"

namespace GX {
    
    enum {
        PixelFormatUnknown      = 0,
        PixelFormatA8           = ((1 << 9) | (1 << 8) | 1),//O&D
        PixelFormatRGB565       = ((2 << 9) | (0 << 8) | 2),//O
		PixelFormatBGR565		= ((2 << 9) | (0 << 8) | 3),//D
		PixelFormatRGBA4444		= ((2 << 9) | (1 << 8) | 4),//O
		PixelFormatBGRA4444		= ((2 << 9) | (1 << 8) | 5),//D
		PixelFormatRGBA5551		= ((2 << 9) | (1 << 8) | 6),//O
		PixelFormatBGRA5551		= ((2 << 9) | (1 << 8) | 7),//D
		PixelFormatRGB888		= ((3 << 9) | (0 << 8) | 8),//O
		PixelFormatRGBA8888		= ((4 << 9) | (1 << 8) | 9),//O&D
		PixelFormatBGRA8888		= ((4 << 9) | (1 << 8) | 10),//D
    };
    typedef guint32 PixelFormat;
    
#define GX_PIXEL_FORMAT_SIZE(x)			(((x)>>9)&0x7F)
#define GX_PIXEL_FORMAT_HAVEALPHA(x)	(((x)>>8)&0x1)
#define GX_PIXEL_FORMAT_ID(x)			((x)&0xFF)
    
    enum {
        PixelChannelRed=0,
        PixelChannelGreen,
        PixelChannelBlue,
        PixelChannelAlpha,
    };
    typedef guint32 PixelChannel;
}




#endif /* GXPixel_h */
