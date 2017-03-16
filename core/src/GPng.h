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
#include "GDib.h"

class GPng
{
public:
	static bool check(GReader* reader);
	static GDib* read(GReader* reader);
};

#endif /* GPng_h */
