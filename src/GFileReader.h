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

class GFileReader : public GReader {
    GX_OBJECT(GFileReader);
public:
    bool open(const gtchar* path);
    virtual void close();
public:
    //<0:Error 0<=res<len:End >=len:Not end
    virtual gint read(void* buf,guint len);
    virtual bool skip(guint len);
    virtual gint getBytes();
public:
    virtual bool canRollback();
    virtual bool rollback(guint len);
public:
    virtual bool canGetLength();
    virtual gint getLength();
    
private:
    FILE* m_FILE;
    gint  m_Length;
};



#endif /* GFileReader_h */
