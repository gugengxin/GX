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
#include "GData.h"


#include "GXGObject.h"
// Down can't include other h file

class GDataWriter : public GWriter
{
	GX_GOBJECT(GDataWriter);
public:
    bool open(GData* data);
    bool openNotHold(GData& data);//不会增加引用计数
    bool open(void* buf,gint len);
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
    GData* m_Data;
#if GX_PTR_32BIT
    guint m_Bytes:31;
#elif GX_PTR_64BIT
    guint m_Bytes:63;
#endif
    guint m_IsHold:1;
};

// Up can't include other h file
#include "GXGObjectUD.h"

#endif /* GDataWriter_h */
