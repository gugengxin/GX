//
// Created by Gengxin Gu on 16/5/9.
//

#ifndef AS_GOGLCONTEXT_H
#define AS_GOGLCONTEXT_H

#include "GXPrefix.h"
#if defined(GX_OPENGL)
#include "GXOpenGL.h"

class GWindow;

class GOGLContext {
protected:
    GOGLContext();
    ~GOGLContext();
public:
	bool create(GWindow* win);
	void destroy();

	void renderBegin();
	void renderEnd();

	void makeCurrent();
	void makeClear();

private:
	GWindow* m_Window;
#if defined(GX_OS_WINDOWS)
	HDC   m_DC;
	HGLRC m_Context;
#endif
};

#endif
#endif //AS_GOGLCONTEXT_H
