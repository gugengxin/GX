﻿//
//  GDataReader.h
//  GX
//
//  Created by Gengxin Gu on 16/6/22.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GDataReader_h
#define GDataReader_h

#include "GXPrefix.h"
#include "GReader.h"

class GDataReader : public GReader {
    GX_OBJECT(GDataReader);
public:
    virtual void close();
    virtual gint read(void* buf,guint len);
    virtual bool skip(guint len);
    virtual gint getBytes();
    virtual bool canRollback();
    virtual bool rollback(guint len);
    virtual bool canGetLength();
    virtual gint getLength();
    
    
};



#endif /* GDataReader_h */
