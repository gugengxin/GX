//
//  GGraphBase.h
//  GX
//
//  Created by GuGengxin.
//  Copyright by gxengine.com
//

#ifndef GGraphBase_h
#define GGraphBase_h

#include "GXPrefix.h"
#include "GObject.h"
#include "GDataBuffer.h"



#include "GXGObject.h"
// Down can't include other h file

class GGraphBase : public GObject
{
	GX_GOBJECT(GGraphBase);
protected:
    guint getDataStride();
    void setDataStride(guint v);
    void* mapData();
    void* mapData(gint index);
    void unmapData();
    
    gint getDataCount();
    bool changeDataCount(guint count);
protected:
    GDataBuffer* getDataBuffer();
private:
    GDataBuffer m_DataBuf;
};

// Up can't include other h file
#include "GXGObjectUD.h"

#endif /* GGraphBase_h */
