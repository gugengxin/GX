//
// Created by Gengxin Gu on 16/5/9.
//

#include "GD3DContext.h"
#if defined(GX_DIRECTX)
#include "GWindow.h"
#include "GApplication.h"


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
	m_Window = win;
	ID3D10Device* device = GX::D3DDevice();
	UINT width = (UINT)m_Window->getWidth();
	UINT height = (UINT)m_Window->getHeight();

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
	swapChainDesc.OutputWindow = (HWND)m_Window->getOSWindow();

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

	// rasterizer state
	D3D10_RASTERIZER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));

	desc.FillMode = D3D10_FILL_SOLID;
	desc.CullMode = D3D10_CULL_BACK;
	desc.FrontCounterClockwise = TRUE;
	desc.DepthBias = 0;
	desc.DepthBiasClamp = 0.0f;
	desc.SlopeScaledDepthBias = 0.0f;
	desc.DepthClipEnable = TRUE;
	desc.ScissorEnable = FALSE;
	desc.MultisampleEnable = (m_Samples>1);
	desc.AntialiasedLineEnable = FALSE;

	if (S_OK != device->CreateRasterizerState(&desc, &m_RasterState))
		return false;


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
	if (m_RasterState) {
		m_RasterState->Release();
		m_RasterState = NULL;
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
}

bool GD3DContext::createView(UINT width,UINT height)
{
	ID3D10Device* device = GX::D3DDevice();
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
	ID3D10Device* device = GX::D3DDevice();
    // 设置深度模版状态，使其生效
    device->OMSetDepthStencilState(m_DepthStencilState, 1);
    // 绑定渲染目标视图和深度缓冲到渲染管线.
    device->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencilView);
    //设置光栅化状态，使其生效
    device->RSSetState(m_RasterState);

	const FLOAT color[] = { m_Window->m_BgdColor.r, m_Window->m_BgdColor.g, m_Window->m_BgdColor.b, m_Window->m_BgdColor.a };
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

	GX::D3DDevice()->RSSetViewports(1, &viewport);
}
void GD3DContext::renderEnd()
{
	m_SwapChain->Present(0,0);

    ID3D10Device* device = GX::D3DDevice();
    device->RSSetState(NULL);
    device->OMSetRenderTargets(0, NULL, NULL);
    device->OMSetDepthStencilState(NULL, 1);
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
void GD3DContext::readyTexture()
{
}
void GD3DContext::doneTexture()
{
}
void GD3DContext::readyFrameBuffer()
{
}
void GD3DContext::doneFrameBuffer()
{
}

GDib* GD3DContext::loadTexture2DNodeReadyDib(GDib* dib)
{
	if (dib) {
		switch (dib->getPixelFormat()) {
		case GX::PixelFormatA8:
		case GX::PixelFormatBGR565:
		case GX::PixelFormatBGRA4444:
		case GX::PixelFormatBGRA5551:
		case GX::PixelFormatRGBA8888:
		case GX::PixelFormatBGRA8888:
			return dib;
		case GX::PixelFormatRGB565:
			return GDib::convert(dib, GX::PixelFormatBGR565);
		case GX::PixelFormatRGBA4444:
			return GDib::convert(dib, GX::PixelFormatBGRA4444);
		case GX::PixelFormatRGBA5551:
			return GDib::convert(dib, GX::PixelFormatBGRA5551);
		case GX::PixelFormatRGB888:
			return GDib::convert(dib, GX::PixelFormatRGBA8888);
		default:
			break;
		}
	}
	return NULL;
}

void GD3DContext::loadTexture2DNodeInMT(GObject* obj)
{
	GContext::T2DNodeLoadObjBase& nodeObj = *GX_CAST_R(GContext::T2DNodeLoadObjBase*, obj);
	GTexture::Handle& handle = nodeObj.nodeOut->getData();

	nodeObj.context->readyTexture();

	GX::PixelFormat pf;
	gint32 w, h, s;
	void* dibData;

	if (obj->isKindOfClass(GContext::T2DNodeLoadCreateObj::gclass)) {
		pf = GX_CAST_R(GContext::T2DNodeLoadCreateObj*, obj)->pixelFormat;
		w = GX_CAST_R(GContext::T2DNodeLoadCreateObj*, obj)->width;
		h = GX_CAST_R(GContext::T2DNodeLoadCreateObj*, obj)->height;
		s = 0;
		dibData = NULL;
	}
	else {
		GDib*& dib = GX_CAST_R(GContext::T2DNodeLoadObj*, obj)->dib;
		pf = dib->getPixelFormat();
		w = dib->getWidth();
		h = dib->getHeight();
		s = dib->getStride();
		dibData = dib->getDataPtr();
	}

	D3D10_TEXTURE2D_DESC desc = { 0 };
	switch (pf)
	{
	case GX::PixelFormatA8:
	{
		desc.Format = DXGI_FORMAT_A8_UNORM;
	}
	break;
	case GX::PixelFormatBGR565:
	{
		desc.Format = DXGI_FORMAT_B5G6R5_UNORM;
	}
	break;
	case GX::PixelFormatBGRA4444:
	{
		desc.Format = DXGI_FORMAT_B4G4R4A4_UNORM;
	}
	break;
	case GX::PixelFormatBGRA5551:
	{
		desc.Format = DXGI_FORMAT_B5G5R5A1_UNORM;
	}
	break;
	case GX::PixelFormatRGBA8888:
	{
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	}
	break;
	case GX::PixelFormatBGRA8888:
	{
		desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	}
	break;
	default:
		break;
	}
	if (desc.Format!=0) {
		desc.Width = w;
		desc.Height = h;
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.BindFlags = D3D10_BIND_SHADER_RESOURCE;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.CPUAccessFlags = 0;
		desc.Usage = D3D10_USAGE_IMMUTABLE;
		desc.MiscFlags = 0;

		D3D10_SUBRESOURCE_DATA data = { 0 };

		ID3D10Texture2D* pTex2D = NULL;

		ID3D10Device* device = GX::D3DDevice();

		HRESULT hr;
		if (dibData) {
			D3D10_SUBRESOURCE_DATA initialData;
			initialData.pSysMem = dibData;
			initialData.SysMemPitch = s;
			initialData.SysMemSlicePitch = 0;
			hr = device->CreateTexture2D(&desc, &initialData, &pTex2D);
		}
		else {
			hr = device->CreateTexture2D(&desc, NULL, &pTex2D);
		}
		if (SUCCEEDED(hr)) {
			hr=device->CreateShaderResourceView(pTex2D, NULL, &handle.m_Name);
			pTex2D->Release();

			if (SUCCEEDED(hr)) {
				D3D10_SAMPLER_DESC samplerDesc;
				if (nodeObj.param) {
					samplerDesc.Filter = (D3D10_FILTER)nodeObj.param->filter;
					samplerDesc.AddressU = (D3D10_TEXTURE_ADDRESS_MODE)nodeObj.param->wrapU;
					samplerDesc.AddressV = (D3D10_TEXTURE_ADDRESS_MODE)nodeObj.param->wrapV;
				}
				else {
					samplerDesc.Filter = D3D10_FILTER_MIN_MAG_MIP_LINEAR;
					samplerDesc.AddressU = D3D10_TEXTURE_ADDRESS_CLAMP;
					samplerDesc.AddressV = D3D10_TEXTURE_ADDRESS_CLAMP;
				}
				samplerDesc.AddressW = samplerDesc.AddressV;
				samplerDesc.MipLODBias = 0.0f;
				samplerDesc.MaxAnisotropy = 1;
				samplerDesc.ComparisonFunc = D3D10_COMPARISON_ALWAYS;
				samplerDesc.BorderColor[0] = 0;
				samplerDesc.BorderColor[1] = 0;
				samplerDesc.BorderColor[2] = 0;
				samplerDesc.BorderColor[3] = 0;
				samplerDesc.MinLOD = 0;
				samplerDesc.MaxLOD = D3D10_FLOAT32_MAX;
				hr=device->CreateSamplerState(&samplerDesc, &handle.m_SamplerState);
				if (FAILED(hr)) {
					handle.m_Name->Release();
					handle.m_Name = NULL;
				}
			}
		}
	}
	
	nodeObj.context->doneTexture();

	if (handle.isValid()) {
		nodeObj.nodeOut->m_Context = nodeObj.context;
		nodeObj.nodeOut->m_Context->addTextureNodeInMT(nodeObj.nodeOut);
	}
}
void GD3DContext::unloadTextureNodeInMT(GObject* obj)
{
	GContext::T2DNodeUnloadObj& nodeObj = *GX_CAST_R(GContext::T2DNodeUnloadObj*, obj);
	GTexture::Handle& handle = nodeObj.nodeOut->getData();

	nodeObj.context->readyTexture();

	handle.m_Name->Release();
	handle.m_Name = NULL;
	handle.m_SamplerState->Release();
	handle.m_SamplerState = NULL;

	nodeObj.context->doneTexture();

	nodeObj.nodeOut->m_Context->removeTextureNodeInMT(nodeObj.nodeOut);
	nodeObj.nodeOut->m_Context = NULL;
}
void GD3DContext::unloadTextureNodeForContext(GTexture::Node* node)
{
	GTexture::Handle& handle = node->getData();
	handle.m_Name->Release();
	handle.m_Name = NULL;
	handle.m_SamplerState->Release();
	handle.m_SamplerState = NULL;
}


void GD3DContext::loadFrameBufferNodeInMT(GObject* obj)
{
	GContext::FBNodeLoadObj& nodeObj = *GX_CAST_R(GContext::FBNodeLoadObj*, obj);
	GFrameBuffer::Handle& handle = nodeObj.nodeOut->getData();

	if (!nodeObj.texTarget->isKindOfClass(GTexture2D::gclass)) {
		return;
	}

	nodeObj.context->readyFrameBuffer();

	

	nodeObj.context->doneFrameBuffer();

	if (handle.isValid()) {
		nodeObj.nodeOut->m_Context = nodeObj.context;
		nodeObj.nodeOut->m_TexTarget = nodeObj.texTarget;
		GO::retain(nodeObj.nodeOut->m_TexTarget);
		nodeObj.nodeOut->m_Context->addFrameBufferNodeInMT(nodeObj.nodeOut);
	}
}
void GD3DContext::unloadFrameBufferNodeInMT(GObject* obj)
{

}
void GD3DContext::unloadFrameBufferNodeForContext(GFrameBuffer::Node* node)
{

}

#endif