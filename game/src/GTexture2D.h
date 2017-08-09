//
//  GTexture2D.h
//  GX
//
//  Created by Gengxin Gu on 16/6/17.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GTexture2D_h
#define GTexture2D_h

#include "GXPrefix.h"
#include "GX3DAPIType.h"
#include "GTexture.h"
#include "GDib.h"

#include "GXGObject.h"

class GTexture2D : public GTexture {
    GX_GOBJECT(GTexture2D);
public:
	class Parameter {
	public:
		gint32 filter;
		gint32 wrapU;
		gint32 wrapV;
	};
public:
	static GTexture2D* autoCreate(GReader* reader, GDib::FileType suggestFT, GTexture2D::Parameter* param);
	static GTexture2D* autoCreate(GDib* dib, Parameter* param);
	static GTexture2D* autoCreate(GX::PixelFormat pixelFormat, gint32 width, gint32 height, Parameter* param);
public:
    virtual gint32 getWidth() {
        return m_Width;
    }
    virtual gint32 getHeight() {
        return m_Height;
    }
    virtual gint32 getDepth() {
        return 0;
    }
	bool create(GReader* reader, GDib::FileType suggestFT, GTexture2D::Parameter* param);
	bool create(GDib* dib, Parameter* param);
	bool create(GX::PixelFormat pixelFormat, gint32 width, gint32 height, Parameter* param);
	virtual void destroy();
protected:
	GDib* prepareDib(GDib* dib);
	bool create(const void * dibData, GX::PixelFormat pf, gint32 w, gint32 h, gint32 s, Parameter * param);
private:
    gint32 m_Width;
    gint32 m_Height;
};

#include "GXGObjectUD.h"

#endif /* GTexture2D_h */
