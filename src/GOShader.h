#pragma once

#include "GXPrefix.h"
#if defined(GX_OPENGL)
#include "GShader.h"
#include "GXOpenGL.h"



class GOShader :
	public GShader
{
public:
	GOShader();
	virtual ~GOShader();

    bool load(const gchar* srcVS,gint vsLen,const gchar* srcFP,gchar fpLen);

private:
    GLuint m_Program;
};


#endif

