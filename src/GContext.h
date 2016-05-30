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

#include "GShader.h"
#include "GSRGraphics.h"

class GContext : public
#if defined(GX_OPENGL)
                 GOGLContext
#elif defined(GX_DIRECTX)
                 GD3DContext
#endif
{
	friend class GWindow;
private:
	enum ShaderID {
		SRID_Graphics = 0,
		SRID_GraphicsEnd = SRID_Graphics + 3 - 1,
		SRIDCount,
	};
private:
    GContext();
    ~GContext();
public:
	GSRGraphics* getSRGraphics(GSRGraphics::ID srID);

private:
	GShader* m_Shaders[SRIDCount];
};


#endif //AS_GCONTEXT_H
