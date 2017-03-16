//
//  GReader.h
//  GX
//
//  Created by Gengxin Gu on 16/6/22.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GReader_h
#define GReader_h

#include "GXPrefix.h"
#include "GObject.h"


#include "GXGObject.h"

class GReader : public GObject {
    GX_VIRTUAL_GOBJECT(GReader);
public:
    virtual void close()=0;
public:
	virtual bool hasData()=0;
    // <0:Error 0<=res<len:End >=len:Not end
    virtual gint read(void* buf,guint len)=0;
    virtual bool skip(guint len)=0;
    virtual gint getBytes()=0;
public:
    virtual bool canRollback()=0;
    virtual bool rollback(guint len) {
        GX_UNUSED(len);
        return false;
    }
    virtual bool rollbackAll();
public:
    virtual bool canGetLength()=0;
    virtual gint getLength() {
        return 0;
    }
};


#include "GXGObjectUD.h"

#endif /* GReader_h */
