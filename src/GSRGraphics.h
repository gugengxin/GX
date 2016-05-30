#pragma once
#include "GXPrefix.h"
#include "GShader.h"

class GSRGraphics : public GShader
{
	friend class GContext;
public:
	typedef enum _ID {
		ID_ColorMul=0,
		ID_Color,
		ID_CAndCM,
	} ID;
private:
	GSRGraphics(ID srID);
	virtual ~GSRGraphics();

#if defined(GX_DIRECTX)
	virtual bool createInputLayout(ID3D10Device* device, const void *pShaderBytecodeWithInputSignature, SIZE_T BytecodeLength);
	virtual bool createConstantBuffer(ID3D10Device* device);
#elif defined(GX_OPENGL)

#endif
private:
	
};

