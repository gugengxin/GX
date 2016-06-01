#include "GDShader.h"
#if defined(GX_DIRECTX)
#include <D3Dcompiler.h>
#include "GLog.h"

GDShader::GDShader(guint8 idxA, guint8 idxB, guint8 idxC, guint8 idxD) :
GShader(idxA,idxB,idxC,idxD)
{
	m_PixelShader = NULL;
	m_VertexShader = NULL;
}


GDShader::~GDShader()
{
	// 释放ps
	if (m_PixelShader) {
		m_PixelShader->Release();
	}
	// 释放vs
	if (m_VertexShader) {
		m_VertexShader->Release();
	}
}


bool GDShader::load(const gchar* srcVS, const gchar* srcFP, const Macro* macro)
{
	HRESULT result;
	ID3D10Blob* errorMessage;
	ID3D10Blob* vertexShaderBuffer;
	ID3D10Blob* pixelShaderBuffer;

	ID3D10Device* device = GX::D3DDevice();

	// 初始化指针为空. 
	errorMessage = 0;
	vertexShaderBuffer = 0;
	pixelShaderBuffer = 0;

	// 编译vs代码. 
	
	result = D3DCompile(srcVS, strlen(srcVS), NULL, (const D3D_SHADER_MACRO*)macro, NULL, "main", "vs_4_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, &vertexShaderBuffer, &errorMessage);
	if (FAILED(result))
	{
		// 如果vs编译失败，输出错误消息. 
		if (errorMessage)
		{
			GX_LOG_P1(PrioDEBUG, "GDShader", "load error:%s", (const char*)errorMessage->GetBufferPointer());
			errorMessage->Release();
			errorMessage = 0;
		}
		return false;
	}

	// 编译ps. 
	result = D3DCompile(srcFP, strlen(srcFP), 0, (const D3D_SHADER_MACRO*)macro, 0, "main", "ps_4_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, &pixelShaderBuffer, &errorMessage);
	if (FAILED(result))
	{
		// 如果ps编译失败，输出错误信息. 
		if (errorMessage)
		{
			GX_LOG_P1(PrioDEBUG, "GDShader", "load error:%s", (const char*)errorMessage->GetBufferPointer());
			errorMessage->Release();
			errorMessage = 0;
		}
		return false;
	}

	bool resTF = true;

	// 从缓冲创建vs shader. 
	result = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &m_VertexShader);
	if (FAILED(result))
	{
		resTF = false;
		goto END;
	}
	// 从缓冲创建ps shader. 
	result = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), &m_PixelShader);
	if (FAILED(result))
	{
		resTF = false;
		goto END;
	}

	resTF = createInputLayout(device, vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize());
	if (!resTF) {
		goto END;
	}
	resTF = createConstantBuffer(device);

END:
	if (!resTF) {
		if (m_VertexShader) {
			m_VertexShader->Release();
			m_VertexShader = NULL;
		}
		if (m_PixelShader) {
			m_PixelShader->Release();
			m_PixelShader = NULL;
		}
	}
	//释放顶点和像素缓冲. 
	vertexShaderBuffer->Release();
	vertexShaderBuffer = 0;

	pixelShaderBuffer->Release();
	pixelShaderBuffer = 0;

	return resTF;
}

bool GDShader::setInputLayout(gint idx, ID3D10Device* device, const void *pShaderBytecodeWithInputSignature, SIZE_T BytecodeLength, D3D10_INPUT_ELEMENT_DESC* elements, UINT numElements)
{
	ID3D10InputLayout* layout;
	HRESULT result = device->CreateInputLayout(elements, numElements, pShaderBytecodeWithInputSignature, BytecodeLength, &layout);
	if (FAILED(result))
	{
		return false;
	}
	getILs()[idx] = layout;
	return true;
}
bool GDShader::setConstantBuffer(gint idx, ID3D10Device* device, const D3D10_BUFFER_DESC *pDesc, const D3D10_SUBRESOURCE_DATA *pInitialData)
{
	ID3D10Buffer* constBuf;
	HRESULT result = device->CreateBuffer(pDesc, pInitialData, &constBuf);
	if (FAILED(result))
	{
		return false;
	}
	getCBs()[idx] = constBuf;
	return true;
}



#endif
