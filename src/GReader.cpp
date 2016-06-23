//
//  GReader.cpp
//  GX
//
//  Created by Gengxin Gu on 16/6/22.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#include "GReader.h"
#include "GXGObject.h"

GX_GOBJECT_IMPLEMENT(GReader, GObject);

GReader::GReader()
{

}

GReader::~GReader()
{

}

bool GReader::rollbackAll()
{
    gint pos=getBytes();
    if (pos<0) {
        return false;
    }
    return rollback(GX_CAST_S(guint, pos));
}