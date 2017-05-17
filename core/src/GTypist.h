//
//  GTypist.h
//  GX
//
//  Created by GuGengxin.
//  Copyright by gxengine.com
//

#ifndef GTypist_h
#define GTypist_h

#include "GXPrefix.h"
#include "GString.h"
#include "GFont.h"
#include "GGeometry.h"


class GTypist {
public:
	class Layout {

	};
public:
	static GSizeF sizeOfString(GString* str, GFont* font);
};

#endif /* GTypist_h */
