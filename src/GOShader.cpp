#include "GOShader.h"
#if defined(GX_OPENGL)
#include "GLog.h"
#include "GString.h"


GOShader::GOShader(guint8 idxA, guint8 idxB, guint8 idxC, guint8 idxD) :
GShader(idxA,idxB,idxC,idxD)
{
    m_Program=0;
}


GOShader::~GOShader()
{
    //Not need release
    if (m_Program) {
        GX_glDeleteProgram(m_Program);
    }
}

bool GOShader::load(const gchar* srcVS, const gchar* srcFP, const Macro* macro)
{

	GString str;
	const Macro* pSM = macro;
	while (pSM->name) {
		str.append("#define ");
		str.append(pSM->name);
		str.append("\n");
		pSM++;
	}
	gint mlen = str.getLength();
    str.append(srcVS);

    GLuint vertShader=0;
	if (!compileShader(&vertShader, GL_VERTEX_SHADER, (const GLchar*)str.c_str())) {
        return false;
    }

	str.cutOff(mlen);
    str.append(srcFP);

    GLuint fragShader=0;
	if (!compileShader(&fragShader, GL_FRAGMENT_SHADER, (const GLchar*)str.c_str())) {
        if (vertShader) {
            GX_glDeleteShader(vertShader);
            vertShader = 0;
        }
        return false;
    }

    // Create shader program
    m_Program = GX_glCreateProgram();

    // Attach vertex shader to program
    GX_glAttachShader(m_Program, vertShader);
    // Attach fragment shader to program
    GX_glAttachShader(m_Program, fragShader);

    this->bindAttribLocations();

    // Link program
    if (!this->linkProgram(m_Program))
    {
        if (vertShader)
        {
            GX_glDeleteShader(vertShader);
            vertShader = 0;
        }
        if (fragShader)
        {
            GX_glDeleteShader(fragShader);
            fragShader = 0;
        }
        if (m_Program)
        {
            GX_glDeleteProgram(m_Program);
            m_Program = 0;
        }

        return false;
    }

    this->bindUniformLocations();

    // Release vertex and fragment shaders
    if (vertShader)
        GX_glDeleteShader(vertShader);
    if (fragShader)
        GX_glDeleteShader(fragShader);

    return true;
}

bool GOShader::compileShader(GLuint* shader, GLenum type, const GLchar* pGLchars)
{
	GLint status;

    *shader = GX_glCreateShader(type);
    GX_glShaderSource(*shader, 1, &pGLchars, NULL);
    GX_glCompileShader(*shader);

#if defined(GX_DEBUG)
	GLint logLength;
    GX_glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 1)
	{
		GLchar *log = (GLchar *)malloc((size_t)logLength);
        GX_glGetShaderInfoLog(*shader, logLength, &logLength, log);
		GX_LOG_P1(PrioDEBUG, "GOShader", "compileShader:%s", log);
		free(log);
	}
#endif

    GX_glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);
	if (status == 0)
	{
        GX_glDeleteShader(*shader);
		*shader = 0;
		return false;
	}

	return true;
}
bool GOShader::linkProgram(GLuint prog)
{
	GLint status;

    GX_glLinkProgram(prog);

#if defined(GX_DEBUG)
	GLint logLength;
    GX_glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 1)
	{
		GLchar *log = (GLchar *)malloc((size_t)logLength);
        GX_glGetProgramInfoLog(prog, logLength, &logLength, log);
		GX_LOG_P1(PrioDEBUG, "GOShader", "linkProgram:%s", log);
		free(log);
	}
#endif

    GX_glGetProgramiv(prog, GL_LINK_STATUS, &status);
	if (status == 0)
		return false;

	return true;
}
bool GOShader::validateProgram(GLuint prog)
{
    GX_glValidateProgram(prog);
#if defined(GX_DEBUG)
	GLint logLength;
    GX_glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 1)
	{
		GLchar *log = (GLchar *)malloc((size_t)logLength);
        GX_glGetProgramInfoLog(prog, logLength, &logLength, log);
		GX_LOG_P1(PrioDEBUG, "GOShader", "validateProgram:%s", log);
		free(log);
	}
#endif
	GLint status;
    GX_glGetProgramiv(prog, GL_VALIDATE_STATUS, &status);
	if (status == 0)
		return false;

	return true;
}



#endif
