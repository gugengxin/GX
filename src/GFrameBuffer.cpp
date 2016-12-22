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

GFrameBuffer::Node::Node()
{
    m_Context = NULL;
	m_TexTarget = NULL;
    m_BgdColor.set(0.0f, 0.0f, 0.0f, 1.0f);
}

GFrameBuffer::Node::~Node()
{

}

float GFrameBuffer::Node::getWidth()
{
    return m_TexTarget->getWidth();
}
float GFrameBuffer::Node::getHeight()
{
    return m_TexTarget->getHeight();
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


void GFrameBuffer::renderBegin()
{
    
}
void GFrameBuffer::setViewport(float x, float y, float w, float h, float scale)
{
    
}
void GFrameBuffer::renderEnd()
{
    
}

