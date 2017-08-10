//
//  GTexture.cpp
//  GX
//
//  Created by Gengxin Gu on 16/6/17.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#include "GTexture.h"
#include "GContext.h"

#include "GXGObject.h"

GX_GOBJECT_IMPLEMENT(GTexture, GObject);

GTexture::GTexture()
{
#if defined(GX_OPENGL)
	m_TextureID = 0;
#elif defined(GX_DIRECTX)
	m_ShaderResView = NULL;
	m_SamplerState = NULL;
#elif defined(GX_METAL)
	m_Texture = NULL;
	m_SamplerState = NULL;
#endif
}

GTexture::~GTexture()
{
#if defined(GX_OPENGL)
#error
#elif defined(GX_DIRECTX)
	if (m_ShaderResView) {
		m_ShaderResView->Release();
	}
	if (m_SamplerState) {
		m_SamplerState->Release();
	}
#elif defined(GX_METAL)
    [GX_CAST_R(id, m_Texture) release];
    [GX_CAST_R(id, m_SamplerState) release];
#endif
}

bool GTexture::isValid()
{
#if defined(GX_OPENGL)
	return m_TextureID!=0u;
#elif defined(GX_DIRECTX)
	return m_ShaderResView != NULL;
#elif defined(GX_METAL)
	return m_Texture!=NULL;
#endif
}

void GTexture::create(
#if defined(GX_OPENGL)
	GLuint texID
#elif defined(GX_DIRECTX)
	ID3D10ShaderResourceView* shaderResView, ID3D10SamplerState* samplerState
#elif defined(GX_METAL)
	void* texture, void* samplerState
#endif
)
{
#if defined(GX_OPENGL)
#error
#elif defined(GX_DIRECTX)
	m_ShaderResView = shaderResView;
	m_ShaderResView->AddRef();
	m_SamplerState = samplerState;
	m_SamplerState->AddRef();
#elif defined(GX_METAL)
    m_Texture=[GX_CAST_R(id, texture) retain];
    m_SamplerState=[GX_CAST_R(id, samplerState) retain];
#endif
}

void GTexture::destroy()
{
#if defined(GX_OPENGL)
#error
#elif defined(GX_DIRECTX)
	if (m_ShaderResView) {
		m_ShaderResView->Release();
		m_ShaderResView = NULL;
	}
	if (m_SamplerState) {
		m_SamplerState->Release();
		m_SamplerState = NULL;
	}
#elif defined(GX_METAL)
    [GX_CAST_R(id, m_Texture) release];
    m_Texture=NULL;
    [GX_CAST_R(id, m_SamplerState) release];
    m_SamplerState=NULL;
#endif
}
