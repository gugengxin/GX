#ifndef GOShader_h
#define GOShader_h


#include "GXPrefix.h"
#include "GX3DAPIType.h"
#if defined(GX_OPENGL)
#include "GShader.h"
#include "GXOpenGL.h"
#include "GBuffer.h"


class GOShader : public GShader
{
protected:
	GOShader(GContext* ctx,guint8 idxA, guint8 idxB, guint8 idxC, guint8 idxD);
	virtual ~GOShader();

	bool load(const gchar* srcVS, const gchar* srcFP, const Macro* macro);
protected:
	inline void setAttribLocation(GLuint index, const GLchar* name) {
        GX_glBindAttribLocation(m_Program, index, name);
	}
	inline void setUniformLocation(GLuint index, const GLchar* name) {
        getUs()[index] = GX_glGetUniformLocation(m_Program, name);
	}

    inline void useProgram() {
        GX_glUseProgram(m_Program);
    }
    inline void unuseProgram() {
        GX_glUseProgram(0);
    }
	inline void setUniform1f(int index, GLfloat x) {
        GX_glUniform1f(getUs()[index], x);
	}
	inline void setUniform1fv(int index, GLsizei count, const GLfloat* v) {
        GX_glUniform1fv(getUs()[index], count, v);
	}
	inline void setUniform1i(int index, GLint x) {
        GX_glUniform1i(getUs()[index], x);
	}
	inline void setUniform1iv(int index, GLsizei count, const GLint* v) {
        GX_glUniform1iv(getUs()[index], count, v);
	}
	inline void setUniform2f(int index, GLfloat x, GLfloat y) {
        GX_glUniform2f(getUs()[index], x, y);
	}
	inline void setUniform2fv(int index, GLsizei count, const GLfloat* v) {
        GX_glUniform2fv(getUs()[index], count, v);
	}
	inline void setUniform2i(int index, GLint x, GLint y){
        GX_glUniform2i(getUs()[index], x, y);
	}
	inline void setUniform2iv(int index, GLsizei count, const GLint* v) {
        GX_glUniform2iv(getUs()[index], count, v);
	}
	inline void setUniform3f(int index, GLfloat x, GLfloat y, GLfloat z) {
        GX_glUniform3f(getUs()[index], x, y, z);
	}
	inline void setUniform3fv(int index, GLsizei count, const GLfloat* v) {
        GX_glUniform3fv(getUs()[index], count, v);
	}
	inline void setUniform3i(int index, GLint x, GLint y, GLint z){
        GX_glUniform3i(getUs()[index], x, y, z);
	}
	inline void setUniform3iv(int index, GLsizei count, const GLint* v) {
        GX_glUniform3iv(getUs()[index], count, v);
	}
	inline void setUniform4f(int index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
        GX_glUniform4f(getUs()[index], x, y, z, w);
	}
	inline void setUniform4fv(int index, GLsizei count, const GLfloat* v) {
        GX_glUniform4fv(getUs()[index], count, v);
	}
	inline void setUniform4i(int index, GLint x, GLint y, GLint z, GLint w) {
        GX_glUniform4i(getUs()[index], x, y, z, w);
	}
	inline void setUniform4iv(int index, GLsizei count, const GLint* v) {
        GX_glUniform4iv(getUs()[index], count, v);
	}
	inline void setUniformMatrix2fv(int index, GLsizei count, GLboolean transpose, const GLfloat* value) {
        GX_glUniformMatrix2fv(getUs()[index], count, transpose, value);
	}
	inline void setUniformMatrix3fv(int index, GLsizei count, GLboolean transpose, const GLfloat* value) {
        GX_glUniformMatrix3fv(getUs()[index], count, transpose, value);
	}
	inline void setUniformMatrix4fv(int index, GLsizei count, GLboolean transpose, const GLfloat* value) {
        GX_glUniformMatrix4fv(getUs()[index], count, transpose, value);
	}
    
    static void readyUseBuffer(GBuffer* buffer);
    static const GLvoid* getBufferData(GBuffer* buffer,guint offset);
    static void doneUseBuffer(GBuffer* buffer);
    
private:
	virtual GLint* getUs() = 0;
	virtual void  bindAttribLocations() = 0;
	virtual void  bindUniformLocations() = 0;
private:
	bool compileShader(GLuint* shader, GLenum type, const GLchar* pGLchars);
	bool linkProgram(GLuint prog);
	bool validateProgram(GLuint prog);

private:
    GLuint m_Program;
};

typedef GOShader GShaderBase;

#define GX_SHADER_INPUT(OU,DIL,DCB,MPS,MUB) \
private:\
	virtual GLint* getUs() { return (GLint*)&m_Uniforms; }\
	GLint m_Uniforms[OU]
#define GX_SHADER_INPUT_INIT() memset(m_Uniforms,0,sizeof(m_Uniforms))
#define GX_SHADER_INPUT_FINA() 

#endif

#endif
