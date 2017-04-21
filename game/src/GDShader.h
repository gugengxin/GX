#ifndef GDShader_h
#define GDShader_h

#include "GXPrefix.h"
#include "GX3DAPIType.h"
#if defined(GX_DIRECTX)
#include "GShader.h"
#include "GXDirectX.h"


class GDShader : public GShader
{
protected:
	
protected:
	GDShader(GContext* ctx,guint8 idxA, guint8 idxB, guint8 idxC, guint8 idxD);
	virtual ~GDShader();

	bool load(const gchar* srcVS, const gchar* srcFP, const Macro* macro);
	bool setInputLayout(gint idx, ID3D10Device* device, const void *pShaderBytecodeWithInputSignature, SIZE_T BytecodeLength, D3D10_INPUT_ELEMENT_DESC* elements, UINT numElements);
	bool setConstantBuffer(gint idx, ID3D10Device* device, const D3D10_BUFFER_DESC *pDesc, const D3D10_SUBRESOURCE_DATA *pInitialData);

	inline ID3D10VertexShader* getVertexShader() {
		return m_VertexShader;
	}
	inline ID3D10PixelShader* getPixelShader() {
		return m_PixelShader;
	}

private:
	virtual ID3D10InputLayout** getILs()=0;
	virtual ID3D10Buffer** getCBs() = 0;
	virtual bool createInputLayout(ID3D10Device* device, const void *pShaderBytecodeWithInputSignature, SIZE_T BytecodeLength) = 0;
	virtual bool createConstantBuffer(ID3D10Device* device) = 0;

private:
	ID3D10VertexShader*	m_VertexShader;
	ID3D10PixelShader*	m_PixelShader;
};

typedef GDShader GShaderBase;

#define GX_SHADER_INPUT(OU,DIL,DCB,MPS,MUB) \
private:\
	virtual ID3D10InputLayout** getILs() { return m_Layouts; }\
	virtual ID3D10Buffer** getCBs() { return m_ConstBuffers; }\
	ID3D10InputLayout*	m_Layouts[DIL];\
	ID3D10Buffer*		m_ConstBuffers[DCB]
	
#define GX_SHADER_INPUT_INIT() \
	memset(m_Layouts,0,sizeof(m_Layouts));\
	memset(m_ConstBuffers,0,sizeof(m_ConstBuffers))
#define GX_SHADER_INPUT_FINA() \
	for(int i=0;i<sizeof(m_Layouts)/sizeof(m_Layouts[0]);i++) {\
		if(m_Layouts[i])\
			m_Layouts[i]->Release();\
	}\
	for(int i=0;i<sizeof(m_ConstBuffers)/sizeof(m_ConstBuffers[0]);i++) {\
		if(m_ConstBuffers[i])\
			m_ConstBuffers[i]->Release();\
	}


#endif

#endif

