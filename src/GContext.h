//
// Created by Gengxin Gu on 16/5/9.
//

#ifndef AS_GCONTEXT_H
#define AS_GCONTEXT_H

#include "GXPrefix.h"
#include "GOGLContext.h"
#include "GD3DContext.h"
#include "GMTLContext.h"
#include "GPainter.h"
#include "GSRGraphics.h"
#include "GSRTexture2D.h"
#include "GTexture2D.h"
#include "GReader.h"

#include "GXGObject.h"

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

        SRID_Texture2D,
        SRID_Texture2DEnd= SRID_Texture2D+ GSRTexture2D::MMCount - 1,

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
    
    GTexture2D* loadTexture2D(GReader* reader,GDib::FileType suggestFT,GTexture2D::Parameter* param);
private:
	void addTextureNodeInMT(GTexture::Node* node);
	void removeTextureNodeInMT(GTexture::Node* node);

	class T2DNodeLoadObj : public GObject {
		friend class GObject;
		GX_GOBJECT(T2DNodeLoadObj);
	public:
		GContext* context;
		GDib* dib;
		GTexture2D::Parameter* param;
		GTexture2D::Node* nodeOut;
	};
	class T2DNodeUnloadObj : public GObject {
		friend class GObject;
		GX_GOBJECT(T2DNodeUnloadObj);
	public:
		GContext* context;
		GTexture2D::Node* nodeOut;
	};
	bool loadTexture2DNode(GTexture::Node* node, GDib* dib, GTexture2D::Parameter* param);
	void unloadTextureNode(GTexture::Node* node);
    
private:
	GPainter m_Painter;
	GShader* m_Shaders[SRIDCount];
	GDataList<GTexture::Handle> m_Textures;
};

#include "GXGObjectUD.h"

#endif //AS_GCONTEXT_H
