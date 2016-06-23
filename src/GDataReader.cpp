//
//  GDataReader.cpp
//  GX
//
//  Created by Gengxin Gu on 16/6/22.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#include "GDataReader.h"

GX_OBJECT_IMPLEMENT(GDataReader, GReader);

GDataReader::GDataReader()
{

}

GDataReader::~GDataReader()
{

}


void GDataReader::close()
{
    
}
gint GDataReader::read(void* buf,guint len)
{
    return 0;
}
bool GDataReader::skip(guint len)
{
    return false;
}
gint GDataReader::getBytes()
{
    return 0;
}
bool GDataReader::canRollback()
{
    return false;
}
bool GDataReader::rollback(guint len)
{
    return false;
}
bool GDataReader::canGetLength()
{
    return false;
}
gint GDataReader::getLength()
{
    return 0;
}