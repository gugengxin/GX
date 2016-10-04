//
//  GFileWriter.h
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#ifndef GFileWriter_h
#define GFileWriter_h

#include "GXPrefix.h"
#include "GWriter.h"



#include "GXGObject.h"
// Down can't include other h file

class GFileWriter : public GWriter
{
	GX_GOBJECT(GFileWriter);
public:
    bool open(const gtchar* path,bool append);
    virtual void close();
public:
    virtual bool hasSpace();
    //<0:Error 0<=res<len:End >=len:Not end
    virtual gint write(const void* buf,guint len);
    virtual bool skip(guint len);
    virtual gint getBytes();
public:
    virtual bool canRollback();
    virtual bool rollback(guint len);

private:
    FILE* m_FILE;
    guint m_BytesStart;
};

// Up can't include other h file
#include "GXGObjectUD.h"

#endif /* GFileWriter_h */
