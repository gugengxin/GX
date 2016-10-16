//
//  GFrameBuffer.cpp
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#include "GFrameBuffer.h"
//Down include other h file

//Up include other h file
#include "GXGObject.h"

GX_GOBJECT_IMPLEMENT(GFrameBuffer, GObject);

GFrameBuffer::Node::Node()
{
    m_Context=NULL;
}

GFrameBuffer::Node::~Node()
{

}



GFrameBuffer::GFrameBuffer()
{
    m_Node=NULL;
}

GFrameBuffer::~GFrameBuffer()
{
    if (m_Node) {
        
    }
}


