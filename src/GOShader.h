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
	virtual void  bindAttribLocations() = 0;
	virtual void  bindUniformLocations() = 0;
private:
	bool compileShader(GLuint* shader, GLenum type, const GLchar* pGLchars);
	bool linkProgram(GLuint prog);
	bool validateProgram(GLuint prog);

private:
    GLuint m_Program;
};


#endif

