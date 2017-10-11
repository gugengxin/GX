//
//  GFileReader.h
//  GX
//
//  Created by Gengxin Gu on 16/6/22.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GFileReader_h
#define GFileReader_h

#include "GXPrefix.h"
#include "GReader.h"
#include "GXFile.h"

#include "GXGObject.h"

class GFileReader : public GReader {
    GX_GOBJECT(GFileReader);
public:
    bool open(const gtchar* path);
    virtual void close();
	virtual bool hasData();
    virtual gint read(void* buf,guint len);
    virtual bool skip(guint len);
    virtual gint getBytes();
    virtual bool canRollback();
    virtual bool rollback(guint len);
    virtual bool canGetLength();
    virtual gint getLength();
    
private:
    GX::File m_File;
    gint  m_Length;
};

#include "GXGObjectUD.h"

#endif /* GFileReader_h */
