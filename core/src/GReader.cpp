//
//  GReader.cpp
//  GX
//
//  Created by Gengxin Gu on 16/6/22.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#include "GReader.h"
#include "GData.h"

#include "GXGObject.h"

GX_GOBJECT_IMPLEMENT(GReader, GObject);

GReader::GReader()
{

}

GReader::~GReader()
{

}

GData* GReader::readAllToData()
{
    GData* res=GData::autoAlloc();
    
    if (canGetLength()) {
        gint len=getLength()-getBytes();
        if (len>0) {
            if (res->changeBytes(GX_CAST_S(guint, len))) {
                gint lenTemp=read(res->getPtr(), GX_CAST_S(guint, len));
                if (lenTemp<=0) {
                    res->freeSelf();
                }
                else if(lenTemp<len) {
                    if(!res->changeBytes(lenTemp)) {
                        res->freeSelf();
                    }
                }
            }
        }
        
    }
    else {
        guint8 buf[1024*4];
        while (hasData()) {
            gint len=read(buf, sizeof(buf));
            if (len>0) {
                guint lenCur=res->getBytes();
                if (res->changeBytes(lenCur+GX_CAST_S(guint,len))) {
                    memcpy(res->getPtr(lenCur), buf, GX_CAST_S(size_t, len));
                }
                else {
                    break;
                }
            }
        }
    }
    return res;
}

bool GReader::rollbackAll()
{
    gint pos=getBytes();
    if (pos<0) {
        return false;
    }
    return rollback(GX_CAST_S(guint, pos));
}
