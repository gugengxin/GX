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
    if (m_Program) {
        glDeleteProgram(m_Program);
        m_Program=0;
    }
}

bool GOShader::load(const gchar* srcVS, gint vsLen, const gchar* srcFP, gint fpLen, const Macro* macro)
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
	str.append(srcVS, vsLen);

    GLuint vertShader=0;
	if (!compileShader(&vertShader, GL_VERTEX_SHADER, (const GLchar*)str.c_str())) {
        return false;
    }

	str.cutOff(mlen);
	str.append(srcFP, fpLen);

    GLuint fragShader=0;
	if (!compileShader(&fragShader, GL_FRAGMENT_SHADER, (const GLchar*)str.c_str())) {
        if (vertShader) {
            glDeleteShader(vertShader);
            vertShader = 0;
        }
        return false;
    }

    // Create shader program
    m_Program = glCreateProgram();

    // Attach vertex shader to program
    glAttachShader(m_Program, vertShader);
    // Attach fragment shader to program
    glAttachShader(m_Program, fragShader);

    this->bindAttribLocations();

    // Link program
    if (!this->linkProgram(m_Program))
    {
        if (vertShader)
        {
            glDeleteShader(vertShader);
            vertShader = 0;
        }
        if (fragShader)
        {
            glDeleteShader(fragShader);
            fragShader = 0;
        }
        if (m_Program)
        {
            glDeleteProgram(m_Program);
            m_Program = 0;
        }

        return false;
    }

    this->bindUniformLocations();

    // Release vertex and fragment shaders
    if (vertShader)
        glDeleteShader(vertShader);
    if (fragShader)
        glDeleteShader(fragShader);

    return true;
}

bool GOShader::compileShader(GLuint* shader, GLenum type, const GLchar* pGLchars)
{
	GLint status;

	*shader = glCreateShader(type);
	glShaderSource(*shader, 1, &pGLchars, NULL);
	glCompileShader(*shader);

#if defined(GX_DEBUG)
	GLint logLength;
	glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 1)
	{
		GLchar *log = (GLchar *)malloc((size_t)logLength);
		glGetShaderInfoLog(*shader, logLength, &logLength, log);
		GX_LOG_P1(PrioDEBUG, "GOShader", "compileShader:%s", log);
		free(log);
	}
#endif

	glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);
	if (status == 0)
	{
		glDeleteShader(*shader);
		*shader = 0;
		return false;
	}

	return true;
}
bool GOShader::linkProgram(GLuint prog)
{
	GLint status;

	glLinkProgram(prog);

#if defined(GX_DEBUG)
	GLint logLength;
	glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 1)
	{
		GLchar *log = (GLchar *)malloc((size_t)logLength);
		glGetProgramInfoLog(prog, logLength, &logLength, log);
		GX_LOG_P1(PrioDEBUG, "GOShader", "linkProgram:%s", log);
		free(log);
	}
#endif

	glGetProgramiv(prog, GL_LINK_STATUS, &status);
	if (status == 0)
		return false;

	return true;
}
bool GOShader::validateProgram(GLuint prog)
{
	glValidateProgram(prog);
#if defined(GX_DEBUG)
	GLint logLength;
	glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 1)
	{
		GLchar *log = (GLchar *)malloc((size_t)logLength);
		glGetProgramInfoLog(prog, logLength, &logLength, log);
		GX_LOG_P1(PrioDEBUG, "GOShader", "validateProgram:%s", log);
		free(log);
	}
#endif
	GLint status;
	glGetProgramiv(prog, GL_VALIDATE_STATUS, &status);
	if (status == 0)
		return false;

	return true;
}



#endif