//
// Created by Gengxin Gu on 16/5/9.
//

#include "GContext.h"

GContext::GContext()
{
	memset(m_Shaders, 0, sizeof(m_Shaders));
}

GContext::~GContext()
{
    for (gint i = 0; i < SRIDCount; i++) {
        delete m_Shaders[i];
    }
}

bool GContext::create(GWindow *win)
{
    return GContextBase::create(win);
}

void GContext::destroy()
{
    for (gint i = 0; i < SRIDCount; i++) {
        delete m_Shaders[i];
        m_Shaders[i]=NULL;
    }
    GContextBase::destroy();
}

GSRGraphics* GContext::getSRGraphics(GSRGraphics::ID srID)
{
	if (!m_Shaders[SRID_Graphics + srID]) {
        m_Shaders[SRID_Graphics + srID] = new GSRGraphics(srID);
	}
	return (GSRGraphics*)m_Shaders[SRID_Graphics + srID];
}
