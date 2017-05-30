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

class GTypist : public GObject {
	GX_GOBJECT(GTypist);
public:
	void singleLine(GString* str, GFont* font);
private:
	GFont*	m_Font;
	void*	m_HBBuffer;
	GSizeF	m_Size;
};

#include "GXGObjectUD.h"

#endif /* GTypist_h */
