//
//  GBaseContext.cpp
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#include "GBaseContext.h"
#include "GWindow.h"


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

GWindow* GBaseContext::getWindow() const
{
	return m_Window;
}

