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
#include "GDib.h"

class GJpeg
{
public:
	static bool check(GReader* reader);
	static GDib* read(GReader* reader);
};

#endif /* GJpeg_h */
