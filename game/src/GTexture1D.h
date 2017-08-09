//
//  GTexture1D.h
//  GX
//
//  Created by GuGengxin.
//  Copyright by gxengine.com
//

#ifndef GTexture1D_h
#define GTexture1D_h

#include "GXPrefix.h"
#include "GTexture.h"



#include "GXGObject.h"
// Down can't include other h file

class GTexture1D : public GTexture
{
	GX_GOBJECT(GTexture1D);
public:
	virtual gint32 getWidth() {
		return 0;
	}
	virtual gint32 getHeight() {
		return 0;
	}
	virtual gint32 getDepth() {
		return 0;
	}
private:

};

// Up can't include other h file
#include "GXGObjectUD.h"

#endif /* GTexture1D_h */
