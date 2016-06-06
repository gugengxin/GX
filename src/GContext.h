//
// Created by Gengxin Gu on 16/5/9.
//

#ifndef AS_GCONTEXT_H
#define AS_GCONTEXT_H

#include "GXPrefix.h"
#if defined(GX_OPENGL)
#include "GOGLContext.h"
#elif defined(GX_DIRECTX)
#include "GD3DContext.h"
#endif
#include "GPainter.h"
#include "GSRGraphics.h"

class GContext : public GContextBase
{
	friend class GWindow;
private:
	enum ShaderID {
		SRID_Graphics = 0,
		SRID_GraphicsEnd = SRID_Graphics + GSRGraphics::IDCount - 1,


		SRIDCount,
	};
private:
    GContext();
    ~GContext();
public:
    virtual bool create(GWindow* win);
    virtual void destroy();

	GSRGraphics* getSRGraphics(GSRGraphics::ID srID);
public:
	GPainter& getPainter() {
		return m_Painter;
	}
private:
	GPainter m_Painter;
	GShader* m_Shaders[SRIDCount];
};


#endif //AS_GCONTEXT_H
