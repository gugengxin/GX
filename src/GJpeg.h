//
//  GJpeg.h
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#ifndef GJpeg_h
#define GJpeg_h

#include "GXPrefix.h"
#include "GXPixel.h"
#include "GDib.h"

class GReader;

class GJpeg
{
public:
	static bool check(GReader* reader);
	static bool read(GReader* reader, GDib::Info* infoOut, GData* dataOut);
};

#endif /* GJpeg_h */
