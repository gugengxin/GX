#pragma once
#include "GXPrefix.h"
#if defined(GX_DIRECTX)
#include "GShader.h"
#include "GXDirectX.h"


class GDShader :
	public GShader
{
public:
	GDShader();
	virtual ~GDShader();

	bool load(const gchar* srcVS, gint vsLen, const gchar* srcFP, gchar fpLen);

private:
	virtual bool  createInputLayout(ID3D10Device* device, const void *pShaderBytecodeWithInputSignature, SIZE_T BytecodeLength) = 0;
	virtual bool  createConstantBuffer(ID3D10Device* device) = 0;

private:
	ID3D10VertexShader*	m_VertexShader;
	ID3D10PixelShader*	m_PixelShader;
};


#endif

