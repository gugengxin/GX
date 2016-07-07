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
#include "GTString.h"



#include "GXGObject.h"
// Down can't include other h file

class GFileBundle : public GBundle
{
	GX_GOBJECT(GFileBundle);
public:
	bool open(const gtchar* path);
	virtual void close();

	virtual GReader* openReader(const gchar* fileName);
	virtual void closeReader(GReader* reader);
private:
	GPath m_RootPath;
};

// Up can't include other h file
#include "GXGObjectUD.h"

#endif /* GFileBundle_h */
