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
#endif

#define GX_POINTS			GL_POINTS
#define GX_LINES			GL_LINES
#define GX_LINE_STRIP		GL_LINE_STRIP
#define GX_TRIANGLES		GL_TRIANGLES
#define GX_TRIANGLE_STRIP	GL_TRIANGLE_STRIP

#define GX_UINT8		GL_UNSIGNED_BYTE
#define GX_UINT16		GL_UNSIGNED_SHORT


#endif
#endif //AS_GXOPENGL_H
