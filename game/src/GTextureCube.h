//
//  GTextureCube.h
//  GX
//
//  Created by GuGengxin.
//  Copyright by gxengine.com
//

#ifndef GTextureCube_h
#define GTextureCube_h

#include "GXPrefix.h"
#include "GTexture.h"



#include "GXGObject.h"
// Down can't include other h file

class GTextureCube : public GTexture
{
	GX_GOBJECT(GTextureCube);
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

#endif /* GTextureCube_h */
