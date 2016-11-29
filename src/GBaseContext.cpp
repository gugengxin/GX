//
//  GBaseContext.cpp
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#include "GBaseContext.h"
//Down include other h file

//Up include other h file
#include "GXGObject.h"

GX_GOBJECT_IMPLEMENT(GBaseContext, GCanvas);

GBaseContext::GBaseContext()
{
    m_Window=NULL;
}

GBaseContext::~GBaseContext()
{
}

bool GBaseContext::create(GWindow* win)
{
    m_Window=win;
    return true;
}
void GBaseContext::destroy()
{
    m_Window=NULL;
}


