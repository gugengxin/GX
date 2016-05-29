#include "GOShader.h"


GOShader::GOShader()
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

bool GOShader::load(const gchar* srcVS,gint vsLen,const gchar* srcFP,gchar fpLen)
{
    GAString strMarco;

    GXShaderMacro* pSM=(GXShaderMacro*)marco;
    while (pSM->name) {
        strMarco.AppendFormat(40, "#define %s\n",pSM->name);
        pSM++;
    }

    gxInt smLen=strMarco.GetLength();

    strMarco.AppendString(srcVS, vsLen);

    GLuint vertShader=0;

    if (!this->CompileShader(&vertShader,GL_VERTEX_SHADER,(const GLchar*)strMarco.GetDataPtr()))
    {
        return false;
    }

    GLuint fragShader=0;

    strMarco.CutOff(smLen);
    strMarco.AppendString(srcPS, psLen);

    if (!this->CompileShader(&fragShader,GL_FRAGMENT_SHADER,(const GLchar*)strMarco.GetDataPtr()))
    {
        if (vertShader)
        {
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

    this->BindAttribLocations();

    // Link program
    if (!this->LinkProgram(m_Program))
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

    this->BindUniformLocations();

    // Release vertex and fragment shaders
    if (vertShader)
        glDeleteShader(vertShader);
    if (fragShader)
        glDeleteShader(fragShader);

    return true;
}
