﻿//
// Created by Gengxin Gu on 16/5/9.
//

#include "GD3DContext.h"
#if defined(GX_DIRECTX)
#include "GWindow.h"
#include "GApplication.h"


void GD3DContext::initialize()
{
    
}

//不用在这里初始化
GD3DContext::GD3DContext()
{
}
//不用在这里反初始化
GD3DContext::~GD3DContext()
{
}

//在这里初始化
bool GD3DContext::create(GWindow* win)
{
	if (!GBaseContext::create(win)) {
		return false;
	}
	ID3D10Device* device = GX::direct3DDevice();
	UINT width = (UINT)(getWindow()->getWidth()*getWindow()->getScale());
	UINT height = (UINT)(getWindow()->getHeight()*getWindow()->getScale());

	m_Samples = (UINT)GApplication::sharedDelegate()->windowsSuggestedSamples();

	if (m_Samples <= 1) {
		// 不使用多重采样 
		m_Samples = 1;
		m_SampleQuality = 0;
	}
	else {

		device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, m_Samples, &m_SampleQuality);

		if (m_SampleQuality>1) {
			m_SampleQuality -= 1;
		}
		else {
			m_Samples = 1;
			m_SampleQuality = 0;
		}
	}


	HRESULT result;
	

	DXGI_SWAP_CHAIN_DESC swapChainDesc;

	// Attempt to create the DXGI Factory.

	IDXGIDevice * pDXGIDevice;
	result = device->QueryInterface(__uuidof(IDXGIDevice), (void **)&pDXGIDevice);

	IDXGIAdapter * pDXGIAdapter;
	result = pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void **)&pDXGIAdapter);

	IDXGIFactory * pFactory;
	pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void **)&pFactory);

	// Attempt to create the swap chain.
	// 初始化交换链描述 
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	// 用1个后缓冲 
	swapChainDesc.BufferCount = 1;

	//帧缓冲的大小和应用程序窗口大小相等. 
	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = height;

	// 后缓冲的surface的格式为DXGI_FORMAT_R8G8B8A8_UNORM. 
	// surface的每个像素用4个无符号的8bit[映射到0-1]来表示。NORM表示归一化。 
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	// 如果使用垂直同步，设置后缓冲的刷新率.

	//刷新率就是一秒钟把后缓冲内容在屏幕上画出的次数。 
	//如果开启垂直同步，则锁定刷新率，则fps是固定的 
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;

	// 设置后缓冲的用途 
	// 我们的渲染目标缓冲为后缓冲。 
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	// 后缓冲输出的窗口句柄. 
	swapChainDesc.OutputWindow = (HWND)getWindow()->getOSWindow();

	swapChainDesc.SampleDesc.Count = m_Samples;
	swapChainDesc.SampleDesc.Quality = m_SampleQuality;


	// 设置全屏或者窗口模式. 
	swapChainDesc.Windowed = true;

	// 设定扫描线ordering以及缩放为unspecified. 
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// 后缓冲内容呈现到屏幕后，放弃其内容 
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	//不设置标志 
	swapChainDesc.Flags = 0;

	result = pFactory->CreateSwapChain(device, &swapChainDesc, &m_SwapChain);

	// Release the factory regardless of pass or fail.
	pDXGIDevice->Release();
	pDXGIAdapter->Release();
	pFactory->Release();

	if (FAILED(result)) {
		return false;
	}

	createView(width, height);
	
	//// sampler state / texture filter
	//{
	//	D3D10_SAMPLER_DESC desc;
	//	ZeroMemory(&desc, sizeof(desc));

	//	desc.ComparisonFunc = D3D10_COMPARISON_NEVER;
	//	desc.BorderColor[0] = desc.BorderColor[1] = desc.BorderColor[2] = desc.BorderColor[3] = 0;
	//	desc.MinLOD = 0;
	//	desc.MaxLOD = D3D10_FLOAT32_MAX;
	//	desc.MipLODBias = 0.0f;
	//	desc.MaxAnisotropy = 16;
	//	desc.Filter = D3D10_FILTER_MIN_MAG_MIP_LINEAR;
	//	desc.AddressU = D3D10_TEXTURE_ADDRESS_WRAP;
	//	desc.AddressV = D3D10_TEXTURE_ADDRESS_WRAP;
	//	desc.AddressW = D3D10_TEXTURE_ADDRESS_WRAP;
	//	

	//	device->CreateSamplerState(&desc, &m_SamplerState);

	//	for (int i = 0; i<4; i++)
	//	{
	//		g_pd3dDevice->PSSetSamplers(i, 1, &g_pSamplerState);
	//	}
	//}

	//深度设置
	D3D10_DEPTH_STENCIL_DESC dsDesc;
	dsDesc.DepthEnable = false;                      //启用深度测试
	dsDesc.DepthWriteMask = D3D10_DEPTH_WRITE_MASK_ALL;//启用深度缓存写入功能
	dsDesc.DepthFunc = D3D10_COMPARISON_LESS;     //深度测试函数（该值为普通的深度测试）

	//模板设置 
	dsDesc.StencilEnable = false;                      //启用模板测试
	dsDesc.StencilReadMask = 0xff;                      //模板测试（读取）时的掩码
	dsDesc.StencilWriteMask = 0xff;                      //更新（写入）模板的掩码
	//下面两部分是关键
	//告诉模板缓冲区如何处理朝前的三角片
	dsDesc.FrontFace.StencilFailOp = D3D10_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilDepthFailOp = D3D10_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilPassOp = D3D10_STENCIL_OP_REPLACE;
	dsDesc.FrontFace.StencilFunc = D3D10_COMPARISON_ALWAYS;
	//如何处理朝后的三角片 
	dsDesc.BackFace.StencilFailOp = D3D10_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilDepthFailOp = D3D10_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilPassOp = D3D10_STENCIL_OP_REPLACE;
	dsDesc.BackFace.StencilFunc = D3D10_COMPARISON_ALWAYS;

	//使用描述创建深度模板缓冲区
	if (S_OK != device->CreateDepthStencilState(&dsDesc, &m_DepthStencilState))
		return false;

	return true;
}
//在这里反初始化
void GD3DContext::destroy()
{
	if (m_DepthStencilState) {
		m_DepthStencilState->Release();
		m_DepthStencilState = NULL;
	}
	if (m_DepthStencilView) {
		m_DepthStencilView->Release();
		m_DepthStencilView = NULL;
	}
	if (m_RenderTargetView) {
		m_RenderTargetView->Release();
		m_RenderTargetView = NULL;
	}
	if (m_SwapChain) {
		m_SwapChain->Release();
		m_SwapChain = NULL;
	}
	GBaseContext::destroy();
}

bool GD3DContext::createView(UINT width,UINT height)
{
	ID3D10Device* device = GX::direct3DDevice();
	HRESULT result;
	// `取出第一个display buffer`
	ID3D10Texture2D *pBuffer = NULL;
	result = m_SwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), (LPVOID*)&pBuffer);
	if (FAILED(result))
		return false;
	// `打开一个合乎display buffer格式的RenderTargetView`
	result = device->CreateRenderTargetView(pBuffer, NULL, &m_RenderTargetView);
	pBuffer->Release();
	if (FAILED(result))
		return false;

	ID3D10Texture2D	*pDepthStencil = NULL;
	// `设置Depth/Stencil buffer的数据格式`
	D3D10_TEXTURE2D_DESC descDepth;
	ZeroMemory(&descDepth, sizeof(descDepth));
	descDepth.Width = width;
	descDepth.Height = height;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc.Count = m_Samples;
	descDepth.SampleDesc.Quality = m_SampleQuality;
	descDepth.Usage = D3D10_USAGE_DEFAULT;
	descDepth.BindFlags = D3D10_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	// `分配Depth/Stencil buffer的空间`
	result = device->CreateTexture2D(&descDepth, NULL, &pDepthStencil);
	if (FAILED(result))
		return false;

	// `设置Depth/Stencil View的格式`
	D3D10_DEPTH_STENCIL_VIEW_DESC descDSV;
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = m_Samples>1 ? D3D10_DSV_DIMENSION_TEXTURE2DMS:D3D10_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	// `打开DepthStencil Buffer的View`
	result = device->CreateDepthStencilView(pDepthStencil, &descDSV, &m_DepthStencilView);

	pDepthStencil->Release();

	if (FAILED(result)) {
		return false;
	}
	return true;
}

bool GD3DContext::resize(gfloat32 width, gfloat32 height)
{
	if (m_DepthStencilView) {
		m_DepthStencilView->Release();
		m_DepthStencilView = NULL;
	}
	if (m_RenderTargetView) {
		m_RenderTargetView->Release();
		m_RenderTargetView = NULL;
	}

	if (S_OK != m_SwapChain->ResizeBuffers(1, (UINT)width, (UINT)height, DXGI_FORMAT_R8G8B8A8_UNORM, 0))
		return false;

	return createView((UINT)width, (UINT)height);
}

bool GD3DContext::renderCheck()
{
	return true;
}

void GD3DContext::renderBegin()
{
	ID3D10Device* device = GX::direct3DDevice();
    // 设置深度模版状态，使其生效
    device->OMSetDepthStencilState(m_DepthStencilState, 1);
    // 绑定渲染目标视图和深度缓冲到渲染管线.
    device->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencilView);
    //设置光栅化状态，使其生效
	direct3DCFUpdate();
	direct3DBDUpdate();

	const GColor4F& bgdClr=getWindow()->getBackgroundColor();
	const FLOAT color[] = { bgdClr.r, bgdClr.g, bgdClr.b, bgdClr.a };
	device->ClearRenderTargetView(m_RenderTargetView, color);
	device->ClearDepthStencilView(m_DepthStencilView, D3D10_CLEAR_DEPTH | D3D10_CLEAR_STENCIL, 1.0f, 0);
}
void GD3DContext::setViewport(float x, float y, float w, float h, float scale)
{
	D3D10_VIEWPORT viewport;
	viewport.TopLeftX = (INT)(x*scale);
	viewport.TopLeftY = (INT)(y*scale);
	viewport.Width = (UINT)(w*scale);
	viewport.Height = (UINT)(h*scale);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	GX::direct3DDevice()->RSSetViewports(1, &viewport);
}
void GD3DContext::renderEnd()
{
	m_SwapChain->Present(0,0);

    ID3D10Device* device = GX::direct3DDevice();
	{
		const FLOAT factor[4] = { 0.0f,0.0f,0.0f,0.0f };
		UINT mask = 0xFFFFFFFF;
		device->OMSetBlendState(NULL, factor, mask);
	}
    device->RSSetState(NULL);
    device->OMSetRenderTargets(0, NULL, NULL);
    device->OMSetDepthStencilState(NULL, 1);
}

bool GD3DContext::direct3DCFNeedMultisampleEnabled()
{
	return m_Samples > 1;
}


void GD3DContext::makeCurrent()
{
}
void GD3DContext::makeClear()
{
}

void GD3DContext::readyShader()
{
}
void GD3DContext::doneShader()
{
}
void GD3DContext::readyFrameBuffer()
{
}
void GD3DContext::doneFrameBuffer()
{
}

GX::PixelFormat GD3DContext::getPixelFormatForFB() const
{
    return GX::PixelFormatRGBA8888;
}

void GD3DContext::loadFrameBufferNodeInMT(GObject* obj)
{
	GContext::FBNodeLoadObj& nodeObj = *GX_CAST_R(GContext::FBNodeLoadObj*, obj);
	GFrameBuffer::Handle& handle = nodeObj.nodeOut->getData();

	if (!nodeObj.texTarget->isKindOfClass(GTexture2D::gclass)) {
		return;
	}

	nodeObj.context->readyFrameBuffer();

	ID3D10RenderTargetView* outRTView = NULL;
	ID3D10DepthStencilView* outDSView = NULL;
	ID3D10DepthStencilState* outDepthStencilState = NULL;

	ID3D10Device* device = GX::direct3DDevice();
	// 分配RGBA动态贴图
	ID3D10ShaderResourceView* pTextureView = nodeObj.texTarget->getShaderResView();
	ID3D10Texture2D* pTex2D = NULL;
	pTextureView->GetResource((ID3D10Resource**)&pTex2D);
	D3D10_TEXTURE2D_DESC dstex;
	pTex2D->GetDesc(&dstex);

	D3D10_RENDER_TARGET_VIEW_DESC descRT;
	descRT.Format = dstex.Format;
	descRT.ViewDimension = D3D10_RTV_DIMENSION_TEXTURE2D;
	descRT.Texture2D.MipSlice = 0;
	// for rendertarget
	device->CreateRenderTargetView(pTex2D, &descRT, &outRTView);
	pTex2D->Release();

	if (nodeObj.use==GFrameBuffer::UseFor3D) {// 分配DepthStencil动态贴图
		ID3D10Texture2D* pDSTex2D = NULL;
		
		dstex.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		dstex.Usage = D3D10_USAGE_DEFAULT;
		dstex.BindFlags = D3D10_BIND_DEPTH_STENCIL;

		device->CreateTexture2D(&dstex, NULL, &pDSTex2D);

		D3D10_DEPTH_STENCIL_VIEW_DESC target_desc;
		ZeroMemory(&target_desc, sizeof(target_desc));
		target_desc.Format = dstex.Format;
		target_desc.ViewDimension = D3D10_DSV_DIMENSION_TEXTURE2D;
		target_desc.Texture2D.MipSlice = 0;

		device->CreateDepthStencilView(pDSTex2D, &target_desc, &outDSView);

		pDSTex2D->Release();
	}
	if (nodeObj.use == GFrameBuffer::UseFor3D) {
		//深度设置
		D3D10_DEPTH_STENCIL_DESC dsDesc;
		dsDesc.DepthEnable = false;                      //启用深度测试
		dsDesc.DepthWriteMask = D3D10_DEPTH_WRITE_MASK_ALL;//启用深度缓存写入功能
		dsDesc.DepthFunc = D3D10_COMPARISON_LESS;     //深度测试函数（该值为普通的深度测试）

		//模板设置 
		dsDesc.StencilEnable = false;                      //启用模板测试
		dsDesc.StencilReadMask = 0xff;                      //模板测试（读取）时的掩码
		dsDesc.StencilWriteMask = 0xff;                      //更新（写入）模板的掩码
		//下面两部分是关键
		//告诉模板缓冲区如何处理朝前的三角片
		dsDesc.FrontFace.StencilFailOp = D3D10_STENCIL_OP_KEEP;
		dsDesc.FrontFace.StencilDepthFailOp = D3D10_STENCIL_OP_KEEP;
		dsDesc.FrontFace.StencilPassOp = D3D10_STENCIL_OP_REPLACE;
		dsDesc.FrontFace.StencilFunc = D3D10_COMPARISON_ALWAYS;
		//如何处理朝后的三角片 
		dsDesc.BackFace.StencilFailOp = D3D10_STENCIL_OP_KEEP;
		dsDesc.BackFace.StencilDepthFailOp = D3D10_STENCIL_OP_KEEP;
		dsDesc.BackFace.StencilPassOp = D3D10_STENCIL_OP_REPLACE;
		dsDesc.BackFace.StencilFunc = D3D10_COMPARISON_ALWAYS;

		//使用描述创建深度模板缓冲区
		device->CreateDepthStencilState(&dsDesc, &outDepthStencilState);
	}
	
	handle.m_Name = outRTView;
	handle.m_DepthName = outDSView;
	handle.m_DepthStencilState = outDepthStencilState;
	

	nodeObj.context->doneFrameBuffer();

	if (handle.isValid()) {
		nodeObj.nodeOut->m_Context = nodeObj.context;
		nodeObj.nodeOut->m_TexTarget = nodeObj.texTarget;
		GO::retain(nodeObj.nodeOut->m_TexTarget);
		nodeObj.nodeOut->m_Context->addFrameBufferNodeInMT(nodeObj.nodeOut);
	}
}
void GD3DContext::unloadFrameBufferNodeForContext(GFrameBuffer::Node* node)
{
	if (node->isValid()) {
		GFrameBuffer::Handle& handle = node->getData();

		readyFrameBuffer();

		handle.m_Name->Release();
		handle.m_Name = NULL;
		if (handle.m_DepthName) {
			handle.m_DepthName->Release();
			handle.m_DepthName = NULL;
		}
		handle.m_DepthStencilState->Release();
		handle.m_DepthStencilState = NULL;

		doneFrameBuffer();

		node->m_Context = NULL;
		GO::release(node->m_TexTarget);
		node->m_TexTarget = NULL;
	}
}

#endif
