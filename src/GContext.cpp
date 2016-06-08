//
// Created by Gengxin Gu on 16/5/9.
//

#include "GContext.h"

//不用在这里初始化
GContext::GContext()
{
}
//不用在这里反初始化
GContext::~GContext()
{
}

//在这里初始化
bool GContext::create(GWindow *win)
{
    memset(m_Shaders, 0, sizeof(m_Shaders));
    return GContextBase::create(win);
}
//在这里反初始化
void GContext::destroy()
{
    for (gint i = 0; i < SRIDCount; i++) {
        readyShader();
        delete m_Shaders[i];
        m_Shaders[i]=NULL;
        doneShader();
    }
    GContextBase::destroy();
}

GSRGraphics* GContext::getSRGraphics(GSRGraphics::ID srID)
{
	if (!m_Shaders[SRID_Graphics + srID]) {
        readyShader();
        m_Shaders[SRID_Graphics + srID] = new GSRGraphics(srID);
        doneShader();
	}
	return (GSRGraphics*)m_Shaders[SRID_Graphics + srID];
}
