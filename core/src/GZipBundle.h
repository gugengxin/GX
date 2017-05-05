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
#include "GMutex.h"
#include "GString.h"

#include "GXGObject.h"
// Down can't include other h file
class GZipReader;

class GZipBundle : public GBundle
{
	GX_GOBJECT(GZipBundle);
public:
	bool open(const gtchar* path,bool createMap=true);
    virtual bool isOpened();
	virtual void close();

	using GBundle::openReader;
	virtual GReader* openReader(GString* fileName);
	virtual void closeReader(GReader* reader);
private:
    GString m_RootPath;
	GZipReader* m_Reader;
    GMutex m_Mutex;
};

// Up can't include other h file
#include "GXGObjectUD.h"

#endif /* GZipBundle_h */
