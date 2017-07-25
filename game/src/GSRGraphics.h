#ifndef GSRGraphics_h
#define GSRGraphics_h

#include "GXPrefix.h"
#include "GOShader.h"
#include "GDShader.h"
#include "GMShader.h"
#include "GBuffer.h"
#include "GCanvas.h"

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
	void draw(GCanvas* canvas, GBuffer* buffer, guint bufOffset, guint bufStride, InputType inputType, gint mode, gint first, gint count);

private:
	GSRGraphics(GContext* ctx,ID srID);
	virtual ~GSRGraphics();

#if defined(GX_OPENGL)
	virtual void bindAttribLocations();
	virtual void bindUniformLocations();
    
    typedef void(*InputBeginFunction)(gint idx, GBuffer* buffer, guint offset, guint stride);
    typedef void(*InputEndFunction)(gint idx);
    static void _InputBFunFloat(gint idx, GBuffer* buffer, guint offset, guint stride);
    static void _InputEFunFloat(gint idx);
    static InputBeginFunction g_InputBFuns[];
    static InputEndFunction g_InputEFuns[];
#elif defined(GX_DIRECTX)
    virtual bool createInputLayout(ID3D10Device* device, const void *pShaderBytecodeWithInputSignature, SIZE_T BytecodeLength);
    virtual bool createConstantBuffer(ID3D10Device* device);
#elif defined(GX_METAL)
    virtual void deployPLState(gint inputType,void* plStateDescriptor);
    virtual void createUniformBuffer(void* device);
#endif

	GX_SHADER_INPUT(2, 1, 2, 1, 2);
};

#endif
