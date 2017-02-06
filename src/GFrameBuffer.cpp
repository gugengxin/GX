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
        m_Node->getTexture();
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

void GFrameBuffer::renderBegin()
{
    
}
void GFrameBuffer::setViewport(float x, float y, float w, float h, float scale)
{
    
}
void GFrameBuffer::renderEnd()
{
    
}

