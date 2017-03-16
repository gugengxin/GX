//
//  GError.cpp
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#include "GError.h"
//Down include other h file

//Up include other h file
#include "GXGObject.h"

GX_GOBJECT_IMPLEMENT(GError, GObject);

GError::GError()
{
    m_Domain=NULL;
    m_Code=0;
}

GError::~GError()
{
    GO::release(m_Domain);
}


