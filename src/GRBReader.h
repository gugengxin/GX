//
//  GRBReader.h
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#ifndef GRBReader_h
#define GRBReader_h

#include "GXPrefix.h"
#include "GReader.h"



#include "GXGObject.h"
// Down can't include other h file

class GRBReader : public GReader
{
	GX_GOBJECT(GRBReader);
public:
	virtual void close();
public:
	virtual bool hasData();
	virtual gint read(void* buf, guint len);
	virtual bool skip(guint len);
	virtual gint getBytes();
public:
	virtual bool canRollback();
	virtual bool rollback(guint len);
public:
	virtual bool canGetLength();
	virtual gint getLength();
private:

};

// Up can't include other h file
#include "GXGObjectUD.h"

#endif /* GRBReader_h */
