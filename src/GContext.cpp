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
	readyShader();
	for (gint i = 0; i < SRIDCount; i++) {
		delete m_Shaders[i];
	}
	doneShader();
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