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
#include "GTexture2D.h"
#include "GReader.h"

class GContext : public GContextBase
{
    friend class GWindow;
#if defined(GX_OPENGL)
    friend class GOGLContext;
#elif defined(GX_DIRECTX)
    friend class GD3DContext;
#endif
private:
	enum ShaderID {
		SRID_Graphics = 0,
		SRID_GraphicsEnd = SRID_Graphics + GSRGraphics::IDCount - 1,


		SRIDCount,
	};
private:
    GContext();
	virtual ~GContext();
public:
    virtual bool create(GWindow* win);
    virtual void destroy();

#if defined(GX_OS_ANDROID)
private:
	virtual void androidDestroy();
	virtual void androidRecreate(GWindow* win);
#endif
public:
	GSRGraphics* getSRGraphics(GSRGraphics::ID srID);
public:
	GPainter& getPainter() {
		return m_Painter;
	}
public:
    GTexture2D* loadTexture2D(const gchar* fileName);
    
private:
    GTexture2D* loadTexture2D(GReader* reader,GDib::FileType suggestFT);

    void addTextureNodeInMT(GTexture::Node* node);
    
private:
	GPainter m_Painter;
	GShader* m_Shaders[SRIDCount];
    GDataList<GTexture*> m_Textures;
};


#endif //AS_GCONTEXT_H
