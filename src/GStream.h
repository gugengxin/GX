//
//  GStream.h
//  GX
//
//  Created by Gengxin Gu on 16/6/17.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GStream_h
#define GStream_h

#include "GXPrefix.h"
#include "GObject.h"

class GStream : public GObject {
    GX_VIRTUAL_OBJECT(GStream);
public:
    virtual bool canRead()=0;
    virtual gint read(const void* buffer,guint length) {
        return 0;
    }
    virtual gint readBack(guint length) {
        return 0;
    }
    virtual gint readSkip(guint length) {
        return 0;
    }
    virtual gint bytesOfRead() {
        return 0;
    }
    
public:
    virtual bool canWrite()=0;
    virtual gint write(const void* buffer,guint length) {
        return 0;
    }
    virtual gint writeBack(guint length) {
        return 0;
    }
    virtual gint writeSkip(guint length) {
        return 0;
    }
    virtual gint bytesOfWrite() {
        return 0;
    }
    
public:
    virtual void close()=0;
};

#endif /* GStream_h */
