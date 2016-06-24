//
//  GZipBundle.h
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#ifndef GZipBundle_h
#define GZipBundle_h

#include "GXPrefix.h"
#include "GBundle.h"



#include "GXGObject.h"
// Down can't include other h file

class GZipBundle : public GBundle
{
	GX_GOBJECT(GZipBundle);
public:
	virtual GReader* openReader(const gtchar* fileName);
	virtual void closeReader(GReader* reader);
private:

};

// Up can't include other h file
#include "GXGObjectUD.h"

#endif /* GZipBundle_h */
