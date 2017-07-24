//
//  GIndexBuffer.cpp
//  GX
//
//  Created by GuGengxin.
//  Copyright by gxengine.com
//

#include "GIndexBuffer.h"
//Down include other h file

//Up include other h file
#include "GXGObject.h"

GX_GOBJECT_IMPLEMENT(GIndexBuffer, GBuffer);

GIndexBuffer::GIndexBuffer()
{
	
}

GIndexBuffer::~GIndexBuffer()
{
}

#if defined(GX_DIRECTX)
UINT GIndexBuffer::getBindFlags()
{
	return D3D10_BIND_INDEX_BUFFER;
}
#endif



