//
//  GWriter.h
//  GX
//
//  Created by Gengxin Gu on 16/6/22.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GWriter_h
#define GWriter_h

#include "GXPrefix.h"
#include "GObject.h"


#include "GXGObject.h"

class GWriter : public GObject {
    GX_VIRTUAL_GOBJECT(GWriter);
public:
    virtual void close()=0;
public:
	virtual bool hasSpace()=0;
    //<0:Error 0<=res<len:End >=len:Not end
    virtual gint write(const void* buf,guint len)=0;
    virtual bool skip(guint len)=0;
    virtual gint getBytes()=0;
public:
    virtual bool canRollback()=0;
    virtual bool rollback(guint len) {
        GX_UNUSED(len);
        return false;
    }
};

#include "GXGObjectUD.h"

#endif /* GWriter_h */
