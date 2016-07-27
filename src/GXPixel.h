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
        PixelFormatUnknown      =0,
        PixelFormatA8           =0x180,
        PixelFormatRGB565       =0x200,
        PixelFormatRGBA4444     =0x281,
        PixelFormatRGBA5551     =0x282,
        PixelFormatRGB888       =0x300,
        PixelFormatRGBA8888     =0x480,
        
        //以下暂不支持
        PixelFormatOther        =0x10000,
        
        PixelFormatPVRTC4RGB    =0x10001,
        PixelFormatPVRTC4RGBA   =0x10082,
        PixelFormatPVRTC2RGB    =0x10003,
        PixelFormatPVRTC2RGBA   =0x10084,
    };
    
    typedef guint32 PixelFormat;
    
#define GX_PIXEL_FORMAT_SIZE(x) (((x)>>8)&0xFF)
#define GX_PIXEL_FORMAT_HAVEALPHA(x) ((x)&0x80)
#define GX_PIXEL_FORMAT_ISOTHER(x) ((x)>>16)
    
    enum {
        PixelChannelRed=0,
        PixelChannelGreen,
        PixelChannelBlue,
        PixelChannelAlpha,
    };
    
    typedef guint32 PixelChannel;
}




#endif /* GXPixel_h */
