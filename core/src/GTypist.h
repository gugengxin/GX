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



#include "GXGObject.h"

class GTypist : GObject {
	GX_PRIVATE_GOBJECT(GTypist);
public:
	static GTypist* singleLine(GString* str,GFont* font);
private:
	bool create(GString* str, GFont* font);
private:
	GFont* m_Font;
	void* m_HBBuffer;
};

#include "GXGObjectUD.h"

#endif /* GTypist_h */
