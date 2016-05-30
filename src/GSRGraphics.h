#pragma once
#include "GXPrefix.h"
#include "GOShader.h"
#include "GDShader.h"

class GSRGraphics : public GShaderBase
{
	friend class GContext;
public:
	typedef enum _ID {
		ID_ColorMul=0,
		ID_Color,
		ID_CAndCM,
	} ID;
	typedef enum _InputType {
		ITFloat,
	} InputType;
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

