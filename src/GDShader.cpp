#include "GDShader.h"
#if defined(GX_DIRECTX)
#include <D3Dcompiler.h>
#include "GLog.h"

GDShader::GDShader()
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


bool GDShader::load(const gchar* srcVS, gint vsLen, const gchar* srcFP, gchar fpLen)
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
	
	result = D3DCompile(srcVS, vsLen, 0, (const D3D_SHADER_MACRO*)NULL, 0, "main", "vs_4_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, &vertexShaderBuffer, &errorMessage);
	if (FAILED(result))
	{
		// 如果vs编译失败，输出错误消息. 
		if (errorMessage)
		{
			GX_LOG_W(PrioDEBUG, "GDShader", "load:error");
			errorMessage->Release();
			errorMessage = 0;
		}
		return false;
	}

	// 编译ps. 
	result = D3DCompile(srcFP, fpLen, 0, (const D3D_SHADER_MACRO*)NULL, 0, "main", "ps_4_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, &pixelShaderBuffer, &errorMessage);
	if (FAILED(result))
	{
		// 如果ps编译失败，输出错误信息. 
		if (errorMessage)
		{
			GX_LOG_W(PrioDEBUG, "GDShader", "load:error");
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


#endif
