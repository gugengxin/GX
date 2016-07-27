//
//  GDib.h
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#ifndef GDib_h
#define GDib_h

#include "GXPrefix.h"
#include "GXPixel.h"
#include "GData.h"

class GDib
{
public:
	class Info {
	public:
		Info() {
			pixelFormat = GX::PixelFormatUnknown;
			width = 0;
			height = 0;
			stride = 0;
		}
		GX::PixelFormat pixelFormat;
		gint32 width;
		gint32 height;
		gint32 stride;
	};
    
};

#endif /* GDib_h */
