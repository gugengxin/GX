//
//  GDataWriter.h
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#ifndef GDataWriter_h
#define GDataWriter_h

#include "GXPrefix.h"
#include "GWriter.h"



#include "GXGObject.h"
// Down can't include other h file

class GDataWriter : public GWriter
{
	GX_GOBJECT(GDataWriter);
public:
    virtual void close();
public:
    virtual bool hasSpace();
    //<0:Error 0<=res<len:End >=len:Not end
    virtual gint write(void* buf,guint len);
    virtual bool skip(guint len);
    virtual gint getBytes();
public:
    virtual bool canRollback();
    virtual bool rollback(guint len);
private:

};

// Up can't include other h file
#include "GXGObjectUD.h"

#endif /* GDataWriter_h */
