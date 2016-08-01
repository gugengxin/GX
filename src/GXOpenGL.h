//
// Created by Gengxin Gu on 16/5/9.
//

#ifndef AS_GXOPENGL_H
#define AS_GXOPENGL_H

#include "GXPrefix.h"
#if defined(GX_OPENGL)


#if defined(GX_OS_WINDOWS)
#include <GL/glew.h>
#include <GL/wglew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#ifdef GLEW_MX  
extern GLEWContext _glewctx;
#define glewGetContext() (&_glewctx)  
#ifdef _WIN32  
extern WGLEWContext _wglewctx;
#define wglewGetContext() (&_wglewctx)  
#elif !defined(__APPLE__) || defined(GLEW_APPLE_GLX)  
extern GLXEWContext _glxewctx;
#define glxewGetContext() (&_glxewctx)  
#endif  
#endif

namespace GX
{
	bool GLEWInit();
}

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

#elif defined(GX_OS_ANDROID)
#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#elif defined(GX_OS_IPHONE)
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#elif defined(GX_OS_MACOSX)
#import <OpenGL/gl.h>
#import <OpenGL/glu.h>
#elif defined(GX_OS_QT)
#include <QtOpenGL>
namespace GX {
    QOpenGLFunctions* openGLFuns();
}
#endif

#if defined(GX_OS_QT)

#define GX_glBindTexture                           GX::openGLFuns()->glBindTexture
#define GX_glBlendFunc                             GX::openGLFuns()->glBlendFunc
#define GX_glClear                                 GX::openGLFuns()->glClear
#define GX_glClearColor                            GX::openGLFuns()->glClearColor
#define GX_glClearStencil                          GX::openGLFuns()->glClearStencil
#define GX_glColorMask                             GX::openGLFuns()->glColorMask
#define GX_glCopyTexImage2D                        GX::openGLFuns()->glCopyTexImage2D
#define GX_glCopyTexSubImage2D                     GX::openGLFuns()->glCopyTexSubImage2D
#define GX_glCullFace                              GX::openGLFuns()->glCullFace
#define GX_glDeleteTextures                        GX::openGLFuns()->glDeleteTextures
#define GX_glDepthFunc                             GX::openGLFuns()->glDepthFunc
#define GX_glDepthMask                             GX::openGLFuns()->glDepthMask
#define GX_glDisable                               GX::openGLFuns()->glDisable
#define GX_glDrawArrays                            GX::openGLFuns()->glDrawArrays
#define GX_glDrawElements                          GX::openGLFuns()->glDrawElements
#define GX_glEnable                                GX::openGLFuns()->glEnable
#define GX_glFinish                                GX::openGLFuns()->glFinish
#define GX_glFlush                                 GX::openGLFuns()->glFlush
#define GX_glFrontFace                             GX::openGLFuns()->glFrontFace
#define GX_glGenTextures                           GX::openGLFuns()->glGenTextures
#define GX_glGetBooleanv                           GX::openGLFuns()->glGetBooleanv
#define GX_glGetError();                           GX::openGLFuns()->glGetError();
#define GX_glGetFloatv                             GX::openGLFuns()->glGetFloatv
#define GX_glGetIntegerv                           GX::openGLFuns()->glGetIntegerv
#define GX_glGetString                             GX::openGLFuns()->glGetString
#define GX_glGetTexParameterfv                     GX::openGLFuns()->glGetTexParameterfv
#define GX_glGetTexParameteriv                     GX::openGLFuns()->glGetTexParameteriv
#define GX_glHint                                  GX::openGLFuns()->glHint
#define GX_glIsEnabled                             GX::openGLFuns()->glIsEnabled
#define GX_glIsTexture                             GX::openGLFuns()->glIsTexture
#define GX_glLineWidth                             GX::openGLFuns()->glLineWidth
#define GX_glPixelStorei                           GX::openGLFuns()->glPixelStorei
#define GX_glPolygonOffset                         GX::openGLFuns()->glPolygonOffset
#define GX_glReadPixels                            GX::openGLFuns()->glReadPixels
#define GX_glScissor                               GX::openGLFuns()->glScissor
#define GX_glStencilFunc                           GX::openGLFuns()->glStencilFunc
#define GX_glStencilMask                           GX::openGLFuns()->glStencilMask
#define GX_glStencilOp                             GX::openGLFuns()->glStencilOp
#define GX_glTexImage2D                            GX::openGLFuns()->glTexImage2D
#define GX_glTexParameterf                         GX::openGLFuns()->glTexParameterf
#define GX_glTexParameterfv                        GX::openGLFuns()->glTexParameterfv
#define GX_glTexParameteri                         GX::openGLFuns()->glTexParameteri
#define GX_glTexParameteriv                        GX::openGLFuns()->glTexParameteriv
#define GX_glTexSubImage2D                         GX::openGLFuns()->glTexSubImage2D
#define GX_glViewport                              GX::openGLFuns()->glViewport
#define GX_glActiveTexture                         GX::openGLFuns()->glActiveTexture
#define GX_glAttachShader                          GX::openGLFuns()->glAttachShader
#define GX_glBindAttribLocation                    GX::openGLFuns()->glBindAttribLocation
#define GX_glBindBuffer                            GX::openGLFuns()->glBindBuffer
#define GX_glBindFramebuffer                       GX::openGLFuns()->glBindFramebuffer
#define GX_glBindRenderbuffer                      GX::openGLFuns()->glBindRenderbuffer
#define GX_glBlendColor                            GX::openGLFuns()->glBlendColor
#define GX_glBlendEquation                         GX::openGLFuns()->glBlendEquation
#define GX_glBlendEquationSeparate                 GX::openGLFuns()->glBlendEquationSeparate
#define GX_glBlendFuncSeparate                     GX::openGLFuns()->glBlendFuncSeparate
#define GX_glBufferData                            GX::openGLFuns()->glBufferData
#define GX_glBufferSubData                         GX::openGLFuns()->glBufferSubData
#define GX_glCheckFramebufferStatus                GX::openGLFuns()->glCheckFramebufferStatus
#define GX_glClearDepthf                           GX::openGLFuns()->glClearDepthf
#define GX_glCompileShader                         GX::openGLFuns()->glCompileShader
#define GX_glCompressedTexImage2D                  GX::openGLFuns()->glCompressedTexImage2D
#define GX_glCompressedTexSubImage2D               GX::openGLFuns()->glCompressedTexSubImage2D
#define GX_glCreateProgram                         GX::openGLFuns()->glCreateProgram
#define GX_glCreateShader                          GX::openGLFuns()->glCreateShader
#define GX_glDeleteBuffers                         GX::openGLFuns()->glDeleteBuffers
#define GX_glDeleteFramebuffers                    GX::openGLFuns()->glDeleteFramebuffers
#define GX_glDeleteProgram                         GX::openGLFuns()->glDeleteProgram
#define GX_glDeleteRenderbuffers                   GX::openGLFuns()->glDeleteRenderbuffers
#define GX_glDeleteShader                          GX::openGLFuns()->glDeleteShader
#define GX_glDepthRangef                           GX::openGLFuns()->glDepthRangef
#define GX_glDetachShader                          GX::openGLFuns()->glDetachShader
#define GX_glDisableVertexAttribArray              GX::openGLFuns()->glDisableVertexAttribArray
#define GX_glEnableVertexAttribArray               GX::openGLFuns()->glEnableVertexAttribArray
#define GX_glFramebufferRenderbuffer               GX::openGLFuns()->glFramebufferRenderbuffer
#define GX_glFramebufferTexture2D                  GX::openGLFuns()->glFramebufferTexture2D
#define GX_glGenBuffers                            GX::openGLFuns()->glGenBuffers
#define GX_glGenerateMipmap                        GX::openGLFuns()->glGenerateMipmap
#define GX_glGenFramebuffers                       GX::openGLFuns()->glGenFramebuffers
#define GX_glGenRenderbuffers                      GX::openGLFuns()->glGenRenderbuffers
#define GX_glGetActiveAttrib                       GX::openGLFuns()->glGetActiveAttrib
#define GX_glGetActiveUniform                      GX::openGLFuns()->glGetActiveUniform
#define GX_glGetAttachedShaders                    GX::openGLFuns()->glGetAttachedShaders
#define GX_glGetAttribLocation                     GX::openGLFuns()->glGetAttribLocation
#define GX_glGetBufferParameteriv                  GX::openGLFuns()->glGetBufferParameteriv
#define GX_glGetFramebufferAttachmentParameteriv   GX::openGLFuns()->glGetFramebufferAttachmentParameteriv
#define GX_glGetProgramiv                          GX::openGLFuns()->glGetProgramiv
#define GX_glGetProgramInfoLog                     GX::openGLFuns()->glGetProgramInfoLog
#define GX_glGetRenderbufferParameteriv            GX::openGLFuns()->glGetRenderbufferParameteriv
#define GX_glGetShaderiv                           GX::openGLFuns()->glGetShaderiv
#define GX_glGetShaderInfoLog                      GX::openGLFuns()->glGetShaderInfoLog
#define GX_glGetShaderPrecisionFormat              GX::openGLFuns()->glGetShaderPrecisionFormat
#define GX_glGetShaderSource                       GX::openGLFuns()->glGetShaderSource
#define GX_glGetUniformfv                          GX::openGLFuns()->glGetUniformfv
#define GX_glGetUniformiv                          GX::openGLFuns()->glGetUniformiv
#define GX_glGetUniformLocation                    GX::openGLFuns()->glGetUniformLocation
#define GX_glGetVertexAttribfv                     GX::openGLFuns()->glGetVertexAttribfv
#define GX_glGetVertexAttribiv                     GX::openGLFuns()->glGetVertexAttribiv
#define GX_glGetVertexAttribPointerv               GX::openGLFuns()->glGetVertexAttribPointerv
#define GX_glIsBuffer                              GX::openGLFuns()->glIsBuffer
#define GX_glIsFramebuffer                         GX::openGLFuns()->glIsFramebuffer
#define GX_glIsProgram                             GX::openGLFuns()->glIsProgram
#define GX_glIsRenderbuffer                        GX::openGLFuns()->glIsRenderbuffer
#define GX_glIsShader                              GX::openGLFuns()->glIsShader
#define GX_glLinkProgram                           GX::openGLFuns()->glLinkProgram
#define GX_glReleaseShaderCompiler                 GX::openGLFuns()->glReleaseShaderCompiler
#define GX_glRenderbufferStorage                   GX::openGLFuns()->glRenderbufferStorage
#define GX_glSampleCoverage                        GX::openGLFuns()->glSampleCoverage
#define GX_glShaderBinary                          GX::openGLFuns()->glShaderBinary
#define GX_glShaderSource                          GX::openGLFuns()->glShaderSource
#define GX_glStencilFuncSeparate                   GX::openGLFuns()->glStencilFuncSeparate
#define GX_glStencilMaskSeparate                   GX::openGLFuns()->glStencilMaskSeparate
#define GX_glStencilOpSeparate                     GX::openGLFuns()->glStencilOpSeparate
#define GX_glUniform1f                             GX::openGLFuns()->glUniform1f
#define GX_glUniform1fv                            GX::openGLFuns()->glUniform1fv
#define GX_glUniform1i                             GX::openGLFuns()->glUniform1i
#define GX_glUniform1iv                            GX::openGLFuns()->glUniform1iv
#define GX_glUniform2f                             GX::openGLFuns()->glUniform2f
#define GX_glUniform2fv                            GX::openGLFuns()->glUniform2fv
#define GX_glUniform2i                             GX::openGLFuns()->glUniform2i
#define GX_glUniform2iv                            GX::openGLFuns()->glUniform2iv
#define GX_glUniform3f                             GX::openGLFuns()->glUniform3f
#define GX_glUniform3fv                            GX::openGLFuns()->glUniform3fv
#define GX_glUniform3i                             GX::openGLFuns()->glUniform3i
#define GX_glUniform3iv                            GX::openGLFuns()->glUniform3iv
#define GX_glUniform4f                             GX::openGLFuns()->glUniform4f
#define GX_glUniform4fv                            GX::openGLFuns()->glUniform4fv
#define GX_glUniform4i                             GX::openGLFuns()->glUniform4i
#define GX_glUniform4iv                            GX::openGLFuns()->glUniform4iv
#define GX_glUniformMatrix2fv                      GX::openGLFuns()->glUniformMatrix2fv
#define GX_glUniformMatrix3fv                      GX::openGLFuns()->glUniformMatrix3fv
#define GX_glUniformMatrix4fv                      GX::openGLFuns()->glUniformMatrix4fv
#define GX_glUseProgram                            GX::openGLFuns()->glUseProgram
#define GX_glValidateProgram                       GX::openGLFuns()->glValidateProgram
#define GX_glVertexAttrib1f                        GX::openGLFuns()->glVertexAttrib1f
#define GX_glVertexAttrib1fv                       GX::openGLFuns()->glVertexAttrib1fv
#define GX_glVertexAttrib2f                        GX::openGLFuns()->glVertexAttrib2f
#define GX_glVertexAttrib2fv                       GX::openGLFuns()->glVertexAttrib2fv
#define GX_glVertexAttrib3f                        GX::openGLFuns()->glVertexAttrib3f
#define GX_glVertexAttrib3fv                       GX::openGLFuns()->glVertexAttrib3fv
#define GX_glVertexAttrib4f                        GX::openGLFuns()->glVertexAttrib4f
#define GX_glVertexAttrib4fv                       GX::openGLFuns()->glVertexAttrib4fv
#define GX_glVertexAttribPointer                   GX::openGLFuns()->glVertexAttribPointer

#else

#define GX_glBindTexture                           glBindTexture
#define GX_glBlendFunc                             glBlendFunc
#define GX_glClear                                 glClear
#define GX_glClearColor                            glClearColor
#define GX_glClearStencil                          glClearStencil
#define GX_glColorMask                             glColorMask
#define GX_glCopyTexImage2D                        glCopyTexImage2D
#define GX_glCopyTexSubImage2D                     glCopyTexSubImage2D
#define GX_glCullFace                              glCullFace
#define GX_glDeleteTextures                        glDeleteTextures
#define GX_glDepthFunc                             glDepthFunc
#define GX_glDepthMask                             glDepthMask
#define GX_glDisable                               glDisable
#define GX_glDrawArrays                            glDrawArrays
#define GX_glDrawElements                          glDrawElements
#define GX_glEnable                                glEnable
#define GX_glFinish                                glFinish
#define GX_glFlush                                 glFlush
#define GX_glFrontFace                             glFrontFace
#define GX_glGenTextures                           glGenTextures
#define GX_glGetBooleanv                           glGetBooleanv
#define GX_glGetError();                           glGetError();
#define GX_glGetFloatv                             glGetFloatv
#define GX_glGetIntegerv                           glGetIntegerv
#define GX_glGetString                             glGetString
#define GX_glGetTexParameterfv                     glGetTexParameterfv
#define GX_glGetTexParameteriv                     glGetTexParameteriv
#define GX_glHint                                  glHint
#define GX_glIsEnabled                             glIsEnabled
#define GX_glIsTexture                             glIsTexture
#define GX_glLineWidth                             glLineWidth
#define GX_glPixelStorei                           glPixelStorei
#define GX_glPolygonOffset                         glPolygonOffset
#define GX_glReadPixels                            glReadPixels
#define GX_glScissor                               glScissor
#define GX_glStencilFunc                           glStencilFunc
#define GX_glStencilMask                           glStencilMask
#define GX_glStencilOp                             glStencilOp
#define GX_glTexImage2D                            glTexImage2D
#define GX_glTexParameterf                         glTexParameterf
#define GX_glTexParameterfv                        glTexParameterfv
#define GX_glTexParameteri                         glTexParameteri
#define GX_glTexParameteriv                        glTexParameteriv
#define GX_glTexSubImage2D                         glTexSubImage2D
#define GX_glViewport                              glViewport
#define GX_glActiveTexture                         glActiveTexture
#define GX_glAttachShader                          glAttachShader
#define GX_glBindAttribLocation                    glBindAttribLocation
#define GX_glBindBuffer                            glBindBuffer
#define GX_glBindFramebuffer                       glBindFramebuffer
#define GX_glBindRenderbuffer                      glBindRenderbuffer
#define GX_glBlendColor                            glBlendColor
#define GX_glBlendEquation                         glBlendEquation
#define GX_glBlendEquationSeparate                 glBlendEquationSeparate
#define GX_glBlendFuncSeparate                     glBlendFuncSeparate
#define GX_glBufferData                            glBufferData
#define GX_glBufferSubData                         glBufferSubData
#define GX_glCheckFramebufferStatus                glCheckFramebufferStatus
#define GX_glClearDepthf                           glClearDepthf
#define GX_glCompileShader                         glCompileShader
#define GX_glCompressedTexImage2D                  glCompressedTexImage2D
#define GX_glCompressedTexSubImage2D               glCompressedTexSubImage2D
#define GX_glCreateProgram                         glCreateProgram
#define GX_glCreateShader                          glCreateShader
#define GX_glDeleteBuffers                         glDeleteBuffers
#define GX_glDeleteFramebuffers                    glDeleteFramebuffers
#define GX_glDeleteProgram                         glDeleteProgram
#define GX_glDeleteRenderbuffers                   glDeleteRenderbuffers
#define GX_glDeleteShader                          glDeleteShader
#define GX_glDepthRangef                           glDepthRangef
#define GX_glDetachShader                          glDetachShader
#define GX_glDisableVertexAttribArray              glDisableVertexAttribArray
#define GX_glEnableVertexAttribArray               glEnableVertexAttribArray
#define GX_glFramebufferRenderbuffer               glFramebufferRenderbuffer
#define GX_glFramebufferTexture2D                  glFramebufferTexture2D
#define GX_glGenBuffers                            glGenBuffers
#define GX_glGenerateMipmap                        glGenerateMipmap
#define GX_glGenFramebuffers                       glGenFramebuffers
#define GX_glGenRenderbuffers                      glGenRenderbuffers
#define GX_glGetActiveAttrib                       glGetActiveAttrib
#define GX_glGetActiveUniform                      glGetActiveUniform
#define GX_glGetAttachedShaders                    glGetAttachedShaders
#define GX_glGetAttribLocation                     glGetAttribLocation
#define GX_glGetBufferParameteriv                  glGetBufferParameteriv
#define GX_glGetFramebufferAttachmentParameteriv   glGetFramebufferAttachmentParameteriv
#define GX_glGetProgramiv                          glGetProgramiv
#define GX_glGetProgramInfoLog                     glGetProgramInfoLog
#define GX_glGetRenderbufferParameteriv            glGetRenderbufferParameteriv
#define GX_glGetShaderiv                           glGetShaderiv
#define GX_glGetShaderInfoLog                      glGetShaderInfoLog
#define GX_glGetShaderPrecisionFormat              glGetShaderPrecisionFormat
#define GX_glGetShaderSource                       glGetShaderSource
#define GX_glGetUniformfv                          glGetUniformfv
#define GX_glGetUniformiv                          glGetUniformiv
#define GX_glGetUniformLocation                    glGetUniformLocation
#define GX_glGetVertexAttribfv                     glGetVertexAttribfv
#define GX_glGetVertexAttribiv                     glGetVertexAttribiv
#define GX_glGetVertexAttribPointerv               glGetVertexAttribPointerv
#define GX_glIsBuffer                              glIsBuffer
#define GX_glIsFramebuffer                         glIsFramebuffer
#define GX_glIsProgram                             glIsProgram
#define GX_glIsRenderbuffer                        glIsRenderbuffer
#define GX_glIsShader                              glIsShader
#define GX_glLinkProgram                           glLinkProgram
#define GX_glReleaseShaderCompiler                 glReleaseShaderCompiler
#define GX_glRenderbufferStorage                   glRenderbufferStorage
#define GX_glSampleCoverage                        glSampleCoverage
#define GX_glShaderBinary                          glShaderBinary
#define GX_glShaderSource                          glShaderSource
#define GX_glStencilFuncSeparate                   glStencilFuncSeparate
#define GX_glStencilMaskSeparate                   glStencilMaskSeparate
#define GX_glStencilOpSeparate                     glStencilOpSeparate
#define GX_glUniform1f                             glUniform1f
#define GX_glUniform1fv                            glUniform1fv
#define GX_glUniform1i                             glUniform1i
#define GX_glUniform1iv                            glUniform1iv
#define GX_glUniform2f                             glUniform2f
#define GX_glUniform2fv                            glUniform2fv
#define GX_glUniform2i                             glUniform2i
#define GX_glUniform2iv                            glUniform2iv
#define GX_glUniform3f                             glUniform3f
#define GX_glUniform3fv                            glUniform3fv
#define GX_glUniform3i                             glUniform3i
#define GX_glUniform3iv                            glUniform3iv
#define GX_glUniform4f                             glUniform4f
#define GX_glUniform4fv                            glUniform4fv
#define GX_glUniform4i                             glUniform4i
#define GX_glUniform4iv                            glUniform4iv
#define GX_glUniformMatrix2fv                      glUniformMatrix2fv
#define GX_glUniformMatrix3fv                      glUniformMatrix3fv
#define GX_glUniformMatrix4fv                      glUniformMatrix4fv
#define GX_glUseProgram                            glUseProgram
#define GX_glValidateProgram                       glValidateProgram
#define GX_glVertexAttrib1f                        glVertexAttrib1f
#define GX_glVertexAttrib1fv                       glVertexAttrib1fv
#define GX_glVertexAttrib2f                        glVertexAttrib2f
#define GX_glVertexAttrib2fv                       glVertexAttrib2fv
#define GX_glVertexAttrib3f                        glVertexAttrib3f
#define GX_glVertexAttrib3fv                       glVertexAttrib3fv
#define GX_glVertexAttrib4f                        glVertexAttrib4f
#define GX_glVertexAttrib4fv                       glVertexAttrib4fv
#define GX_glVertexAttribPointer                   glVertexAttribPointer

#endif

#define GX_POINTS			GL_POINTS
#define GX_LINES			GL_LINES
#define GX_LINE_STRIP		GL_LINE_STRIP
#define GX_TRIANGLES		GL_TRIANGLES
#define GX_TRIANGLE_STRIP	GL_TRIANGLE_STRIP

#define GX_UINT8		GL_UNSIGNED_BYTE
#define GX_UINT16		GL_UNSIGNED_SHORT


#define GX_FILTER_MIN_MAG_POINT			0x0
#define GX_FILTER_MIN_POINT_MAG_LINEAR	0x1
#define GX_FILTER_MIN_LINEAR_MAG_POINT	0x2
#define GX_FILTER_MIN_MAG_LINEAR		0x3

#define GX_WARP_REPEAT		GL_REPEAT
#define GX_WARP_MIRRORED	GL_MIRRORED_REPEAT
#define GX_WARP_CLAMP		GL_CLAMP_TO_EDGE


#endif
#endif //AS_GXOPENGL_H
