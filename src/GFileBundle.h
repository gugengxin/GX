//
//  GFileBundle.h
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#ifndef GFileBundle_h
#define GFileBundle_h

#include "GXPrefix.h"
#include "GBundle.h"



#include "GXGObject.h"
// Down can't include other h file

class GFileBundle : public GBundle
{
	GX_GOBJECT(GFileBundle);
public:
	virtual GReader* openReader(const gtchar* fileName);
	virtual void closeReader(GReader* reader);
};

// Up can't include other h file
#include "GXGObjectUD.h"

#endif /* GFileBundle_h */
