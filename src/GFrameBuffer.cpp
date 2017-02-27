//
//  GFrameBuffer.cpp
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#include "GFrameBuffer.h"
//Down include other h file
#include "GContext.h"
#include "GTexture.h"

//Up include other h file
#include "GXGObject.h"

GX_GOBJECT_IMPLEMENT(GFrameBuffer, GCanvas);


GFrameBuffer::Handle::Handle()
{
#if defined(GX_OPENGL)
    m_Name = 0;
    m_DepthName=0;
#elif defined(GX_DIRECTX)
    m_Name=NULL;
    m_DepthName=NULL;
    m_RasterState=NULL;
#elif defined(GX_METAL)
    m_Name=NULL;
    m_DepthName=NULL;
    m_StencilTex=NULL;
    m_DepthStencilState=NULL;
#endif
}

GFrameBuffer::Handle::~Handle()
{
    
}

bool GFrameBuffer::Handle::isValid()
{
#if defined(GX_OPENGL)
    return m_Name != 0;
#elif defined(GX_DIRECTX) || defined(GX_METAL)
    return m_Name != NULL;
#endif
}




GFrameBuffer::Node::Node()
{
    m_Context = NULL;
	m_TexTarget = NULL;
    m_BgdColor.set(0.0f, 0.0f, 0.0f, 1.0f);
}

GFrameBuffer::Node::~Node()
{

}

GFrameBuffer::Name GFrameBuffer::getName()
{
    if (m_Node) {
        return m_Node->getData().getName();
    }
#if defined(GX_OPENGL)
    return 0;
#else
    return NULL;
#endif
}
GTexture* GFrameBuffer::getTexture()
{
    if (m_Node) {
        return m_Node->getTexture();
    }
    return NULL;
}

float GFrameBuffer::Node::getWidth()
{
    return GX_CAST_S(float,m_TexTarget->getWidth());
}
float GFrameBuffer::Node::getHeight()
{
	return GX_CAST_S(float, m_TexTarget->getHeight());
}



GFrameBuffer::GFrameBuffer()
{
    m_Node=NULL;
    m_Scale=1.0f;
#if defined(GX_OPENGL)
    m_PreBindName=0;
    m_PreViewport[0]=0;
    m_PreViewport[1]=0;
    m_PreViewport[2]=0;
    m_PreViewport[3]=0;
#elif defined(GX_DIRECTX)
	m_PreName=NULL;
	m_PreDepthName=NULL;
	m_PreRasterState=NULL;
	m_PreDepthStencilState=NULL;
	//m_PreViewport;
#elif defined(GX_METAL)
    m_CommandBuffer=NULL;
    m_RenderEncoder=NULL;
#endif
}

GFrameBuffer::~GFrameBuffer()
{
    if (m_Node && m_Node->getContext()) {
        m_Node->getContext()->unloadFrameBufferNode(m_Node);
    }
}

void GFrameBuffer::enable2D(float width, float height)
{
	GCanvas::enable2D(width, height);
#if defined(GX_OPENGL)
	getMatrix(MatrixProjection).scale(1.0f, -1.0f, 1.0f);
#endif
}
void GFrameBuffer::enable3D(float width, float height, float fovy, float zNear, float zFar)
{
	GCanvas::enable3D(width, height, fovy, zNear, zFar);
#if defined(GX_OPENGL)
	getMatrix(MatrixProjection).scale(1.0f, -1.0f, 1.0f);
#endif
}

float GFrameBuffer::getWidth()
{
    return m_Node->getWidth()/m_Scale;
}
float GFrameBuffer::getHeight()
{
    return m_Node->getHeight()/m_Scale;
}
float GFrameBuffer::getScale()
{
    return m_Scale;
}

void GFrameBuffer::config(Node* node)
{
    setNode(node);
}

bool GFrameBuffer::renderCheck()
{
    if (!m_Node) {
        return false;
    }
    return true;
}

void GFrameBuffer::renderBegin()
{
    m_Node->getContext()->makeCurrent();
    
#if defined(GX_OPENGL)
    
    GX_glGetIntegerv(GL_FRAMEBUFFER_BINDING, (GLint*)&m_PreBindName);
    GX_glGetIntegerv(GL_VIEWPORT, m_PreViewport);
    GX_glBindFramebuffer(GL_FRAMEBUFFER, m_Node->getData().getName());
    
    const GColor4F& bgdClr=getBackgroundColor();
    GX_glClearColor(bgdClr.r, bgdClr.g, bgdClr.b, bgdClr.a);
    GX_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
#elif defined(GX_DIRECTX)
	ID3D10Device* device = GX::d3dDevice();

	device->OMGetRenderTargets(1, &m_PreName, &m_PreDepthName);
	device->OMGetDepthStencilState(&m_PreDepthStencilState,NULL);
	device->RSGetState(&m_PreRasterState);
	UINT numVP = 1;
	device->RSGetViewports(&numVP, &m_PreViewport);

	ID3D10RenderTargetView* rtv = m_Node->getData().getName();
	ID3D10DepthStencilView* dsv = m_Node->getData().getDepthName();
	// 设置深度模版状态，使其生效
	device->OMSetDepthStencilState(m_Node->getData().getDepthStencilState(), 1);
	// 绑定渲染目标视图和深度缓冲到渲染管线.
	
	device->OMSetRenderTargets(1, &rtv, dsv);
	//设置光栅化状态，使其生效
	device->RSSetState(m_Node->getData().getRasterState());

	const GColor4F& bgdClr = getBackgroundColor();
	const FLOAT color[] = { bgdClr.r, bgdClr.g, bgdClr.b, bgdClr.a };
	device->ClearRenderTargetView(rtv, color);
	device->ClearDepthStencilView(dsv, D3D10_CLEAR_DEPTH | D3D10_CLEAR_STENCIL, 1.0f, 0);
#elif defined(GX_METAL)
    
#define M_COMMAND_BUFFER()      GX_CAST_R(id<MTLCommandBuffer>, m_CommandBuffer)
#define M_RENDER_ENCODER()      GX_CAST_R(id<MTLRenderCommandEncoder>, m_RenderEncoder)
#define M_DEPTH_STENCIL_STATE() GX_CAST_R(id<MTLDepthStencilState>, m_DepthStencilState)
    
    m_CommandBuffer=[[GX_CAST_R(id<MTLCommandQueue>, m_Node->getContext()->getCommandQueue()) commandBuffer] retain];
    m_RenderEncoder = [[GX_CAST_R(id<MTLCommandBuffer>, m_CommandBuffer) renderCommandEncoderWithDescriptor:GX_CAST_R(MTLRenderPassDescriptor*, m_Node->getData().getName())] retain];
    if (m_Node->getData().isEnableDepth()) {
        [GX_CAST_R(id<MTLRenderCommandEncoder>, m_RenderEncoder) setDepthStencilState:GX_CAST_R(id<MTLDepthStencilState>, m_Node->getData().getDepthStencilState())];
    }
#if defined(GX_DEBUG)
    [GX_CAST_R(id<MTLRenderCommandEncoder>, m_RenderEncoder) pushDebugGroup:@"GFrameBuffer"];
#endif
#endif
}

void GFrameBuffer::setViewport(float x, float y, float w, float h, float scale)
{
#if defined(GX_OPENGL)
    GX_glViewport((GLint)(x*scale), (GLint)(y*scale), (GLint)(w*scale), (GLint)(h*scale));
#elif defined(GX_DIRECTX)
	D3D10_VIEWPORT viewport;
	viewport.TopLeftX = (INT)(x*scale);
	viewport.TopLeftY = (INT)(y*scale);
	viewport.Width = (UINT)(w*scale);
	viewport.Height = (UINT)(h*scale);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	GX::d3dDevice()->RSSetViewports(1, &viewport);
#elif defined(GX_METAL)
    MTLViewport vt;
    vt.originX=x*scale;
    vt.originY=y*scale;
    vt.width=w*scale;
    vt.height=h*scale;
    vt.znear=0;
    vt.zfar=1;
    [GX_CAST_R(id<MTLRenderCommandEncoder>, m_RenderEncoder) setViewport:vt];
#endif
}

void GFrameBuffer::renderEnd()
{
#if defined(GX_OPENGL)
    GX_glBindFramebuffer(GL_FRAMEBUFFER, m_PreBindName);
    GX_glViewport(m_PreViewport[0], m_PreViewport[1], m_PreViewport[2], m_PreViewport[3]);
#elif defined(GX_DIRECTX)
	ID3D10Device* device = GX::d3dDevice();
	device->OMSetRenderTargets(1, &m_PreName, m_PreDepthName);
	if (m_PreName) {
		m_PreName->Release();
	}
	if (m_PreDepthName) {
		m_PreDepthName->Release();
	}
	device->OMSetDepthStencilState(m_PreDepthStencilState, 1);
	if (m_PreDepthStencilState) {
		m_PreDepthStencilState->Release();
	}
	device->RSSetState(m_PreRasterState);
	if (m_PreRasterState) {
		m_PreRasterState->Release();
	}
	device->RSSetViewports(1, &m_PreViewport);
#elif defined(GX_METAL)
#if defined(GX_DEBUG)
    [GX_CAST_R(id<MTLRenderCommandEncoder>, m_RenderEncoder) popDebugGroup];
#endif
    [GX_CAST_R(id<MTLRenderCommandEncoder>, m_RenderEncoder) endEncoding];
    [GX_CAST_R(id<MTLCommandBuffer>, m_CommandBuffer) commit];
    [GX_CAST_R(id<MTLCommandBuffer>, m_CommandBuffer) waitUntilCompleted];
    
    [GX_CAST_R(id, m_RenderEncoder) release];
    m_RenderEncoder=NULL;
    [GX_CAST_R(id, m_CommandBuffer) release];
    m_CommandBuffer=NULL;
#endif
    m_Node->getContext()->makeClear();
}

