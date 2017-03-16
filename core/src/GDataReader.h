//
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
#include "GData.h"

#include "GXGObject.h"

class GDataReader : public GReader {
    GX_GOBJECT(GDataReader);
public:
	bool open(GData* data);
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
	GData*	m_Data;
	guint	m_Cursor;
};

#include "GXGObjectUD.h"


#endif /* GDataReader_h */
