//
//  GBundle.h
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#ifndef GBundle_h
#define GBundle_h

#include "GXPrefix.h"
#include "GObject.h"
#include "GReader.h"
#include "GString.h"


#include "GXGObject.h"
// Down can't include other h file

class GBundle : public GObject
{
	GX_VIRTUAL_GOBJECT(GBundle);
public:
	virtual void close()=0;

	GReader* openReader(const gchar* fileName);
	virtual GReader* openReader(GString* fileName) = 0;
	virtual void closeReader(GReader* reader)=0;
};

// Up can't include other h file
#include "GXGObjectUD.h"

#endif /* GBundle_h */
