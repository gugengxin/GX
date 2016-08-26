#pragma once
#include "GXPrefix.h"
#include "GOShader.h"
#include "GDShader.h"
#include "GMShader.h"
#include "GBuffer.h"
#include "GPainter.h"

class GSRGraphics : public GShaderBase
{
	friend class GContext;
public:
	typedef enum _ID {
		ID_ColorMul=0,
		ID_Color,
		ID_CAndCM,

		IDCount,
	} ID;
	typedef enum _InputType {
		IT_Float,
	} InputType;
public:
	void draw(GPainter& painter, GIBuffer* buffer, InputType inputType, gint mode, gint first, gint count);

private:
	GSRGraphics(ID srID);
	virtual ~GSRGraphics();

#if defined(GX_DIRECTX)
	virtual bool createInputLayout(ID3D10Device* device, const void *pShaderBytecodeWithInputSignature, SIZE_T BytecodeLength);
	virtual bool createConstantBuffer(ID3D10Device* device);
#elif defined(GX_OPENGL)
	virtual void bindAttribLocations();
	virtual void bindUniformLocations();
#endif

	GX_SHADER_INPUT(2, 1, 2);
};

