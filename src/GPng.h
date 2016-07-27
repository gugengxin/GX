//
//  GPng.h
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#ifndef GPng_h
#define GPng_h

#include "GXPrefix.h"
#include "GXPixel.h"
#include "GDib.h"

class GReader;

class GPng
{
public:
	static bool check(GReader* reader);
	static bool read(GReader* reader, GDib::Info* infoOut, GData* dataOut);
};

#endif /* GPng_h */
