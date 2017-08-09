//
//  GTexture.h
//  GX
//
//  Created by Gengxin Gu on 16/6/17.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GTexture_h
#define GTexture_h

#include "GXPrefix.h"
#include "GX3DAPIType.h"
#include "GX3DAPI.h"
#include "GObject.h"

#include "GXGObject.h"

class GTexture : public GObject {
    GX_VIRTUAL_GOBJECT(GTexture);
public:
	bool isValid();
    virtual gint32 getWidth()=0;
    virtual gint32 getHeight()=0;
    virtual gint32 getDepth()=0;
protected:
	void create(
#if defined(GX_OPENGL)
		GLuint texID
#elif defined(GX_DIRECTX)
		ID3D10ShaderResourceView* shaderResView,ID3D10SamplerState* samplerState
#elif defined(GX_METAL)
		void* texture, void* samplerState
#endif
	);
public:
	virtual void destroy();
protected:
#if defined(GX_OPENGL)

#elif defined(GX_DIRECTX)
	inline ID3D10ShaderResourceView** getShaderResViewPtr() {
		return &m_ShaderResView;
	}
	inline ID3D10SamplerState** getSamplerStatePtr() {
		return &m_SamplerState;
	}
#elif defined(GX_METAL)
	inline void* getSamplerState() {
		return m_SamplerState;
	}
#endif
private:

public:
#if defined(GX_OPENGL)
	GLuint m_TextureID;
#elif defined(GX_DIRECTX)
	ID3D10ShaderResourceView* m_ShaderResView;
	ID3D10SamplerState* m_SamplerState;
#elif defined(GX_METAL)
	void* m_Texture;
	void* m_SamplerState;
#endif
};

#include "GXGObjectUD.h"


#endif /* GTexture_h */
