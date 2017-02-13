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
    
#elif defined(GX_METAL)
    
#endif
}

GFrameBuffer::~GFrameBuffer()
{
    if (m_Node && m_Node->getContext()) {
        m_Node->getContext()->unloadFrameBufferNode(m_Node);
    }
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

	ID3D10RenderTargetView* rtv = m_Node->getData().getName();
	ID3D10DepthStencilView* dsv = m_Node->getData().getDepthName();
	// 设置深度模版状态，使其生效
	device->OMSetDepthStencilState(m_Node->getData().getDepthName(), 1);
	// 绑定渲染目标视图和深度缓冲到渲染管线.
	
	device->OMSetRenderTargets(1, &rtv, dsv);
	//设置光栅化状态，使其生效
	device->RSSetState(m_Node->getData().getRasterState());

	const GColor4F& bgdClr = getBackgroundColor();
	const FLOAT color[] = { bgdClr.r, bgdClr.g, bgdClr.b, bgdClr.a };
	device->ClearRenderTargetView(rtv, color);
	device->ClearDepthStencilView(dsv, D3D10_CLEAR_DEPTH | D3D10_CLEAR_STENCIL, 1.0f, 0);
#elif defined(GX_METAL)
    
#endif
}

void GFrameBuffer::setViewport(float x, float y, float w, float h, float scale)
{
#if defined(GX_OPENGL)
    GX_glViewport((GLint)(x*scale), (GLint)(y*scale), (GLint)(w*scale), (GLint)(h*scale));
#elif defined(GX_DIRECTX)
    
#elif defined(GX_METAL)
    
#endif
}

void GFrameBuffer::renderEnd()
{
#if defined(GX_OPENGL)
    GX_glBindFramebuffer(GL_FRAMEBUFFER, m_PreBindName);
    GX_glViewport(m_PreViewport[0], m_PreViewport[1], m_PreViewport[2], m_PreViewport[3]);
#elif defined(GX_DIRECTX)
    
#elif defined(GX_METAL)
    
#endif
    m_Node->getContext()->makeClear();
}

