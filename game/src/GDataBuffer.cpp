//
//  GDataBuffer.cpp
//  GX
//
//  Created by Gengxin Gu on 16/6/1.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#include "GDataBuffer.h"
#include "GXGObject.h"

GDataBufferBase::GDataBufferBase()
{
#ifdef GX_OPENGL

#elif defined(GX_DIRECTX)
	m_Buffer = NULL;
	m_DataBytes = 0;
#elif defined(GX_METAL)
    m_Buffer=NULL;
#endif
}

GDataBufferBase::~GDataBufferBase()
{
#ifdef GX_OPENGL

#elif defined(GX_DIRECTX)
	if (m_Buffer) {
		m_Buffer->Release();
	}
#elif defined(GX_METAL)
    [GX_CAST_R(id, m_Buffer) release];
#endif
}

bool GDataBufferBase::changeBytes(guint toSize)
{
#ifdef GX_OPENGL
	return m_Data.changeBytes(toSize);
#elif defined(GX_DIRECTX)
	ID3D10Device* device = GX::d3dDevice();

	ID3D10Buffer* bufNew;

	D3D10_BUFFER_DESC bd={0};

	bd.Usage = D3D10_USAGE_DYNAMIC;//D3D11_USAGE_STAGING
	bd.ByteWidth = (UINT)toSize;
	bd.BindFlags = getBindFlags();
	bd.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;//|D3D11_CPU_ACCESS_READ;

	if (FAILED(device->CreateBuffer(&bd, NULL, &bufNew))) {
		return false;
	}

	if (m_Buffer) {
		m_Buffer->Release();
	}
	m_Buffer = bufNew;
	m_DataBytes = toSize;
	return true;
#elif defined(GX_METAL)
    id<MTLBuffer> bufNew=[GX::metalDevice() newBufferWithLength:toSize options:0];
    if (!bufNew) {
        return false;
    }
    [GX_CAST_R(id<MTLBuffer>, m_Buffer) release];
    m_Buffer=[bufNew retain];
    return true;
#endif
}
bool GDataBufferBase::changeBytesIfNeed(guint toSize)
{
#ifdef GX_OPENGL
	return m_Data.changeBytesIfNeed(toSize);
#elif defined(GX_DIRECTX)
	if (toSize>m_DataBytes) {
		return changeBytes(toSize);
	}
	return true;
#elif defined(GX_METAL)
    if (toSize>[GX_CAST_R(id<MTLBuffer>, m_Buffer) length]) {
        return changeBytes(toSize);
    }
    return true;
#endif
}
void GDataBufferBase::freeSelf()
{
#ifdef GX_OPENGL
	m_Data.freeSelf();
#elif defined(GX_DIRECTX)
	if (m_Buffer) {
		m_Buffer->Release();
		m_Buffer = NULL;
	}
	m_DataBytes = 0;
#elif defined(GX_METAL)
    [GX_CAST_R(id<MTLBuffer>, m_Buffer) release];
    m_Buffer=NULL;
#endif
}
void* GDataBufferBase::map()
{
#ifdef GX_OPENGL
	return m_Data.getPtr();
#elif defined(GX_DIRECTX)
	if (m_Buffer) {
		void* res = NULL;
		if (SUCCEEDED(m_Buffer->Map(D3D10_MAP_WRITE_DISCARD, 0, &res))) {
			return res;
		}
	}
	return NULL;
#elif defined(GX_METAL)
    return [GX_CAST_R(id<MTLBuffer>, m_Buffer) contents];
#endif
}
void GDataBufferBase::unmap()
{
#ifdef GX_OPENGL

#elif defined(GX_DIRECTX)
	if (m_Buffer) {
		m_Buffer->Unmap();
	}
#elif defined(GX_METAL)

#endif
}




GX_GOBJECT_IMPLEMENT(GDataBuffer, GObject);


GDataBuffer::GDataBuffer()
{
	m_Offset = 0U;
	m_Stride = 0U;
}

GDataBuffer::~GDataBuffer()
{

}




GX_GOBJECT_IMPLEMENT(GDataIndexBuffer, GObject);

GDataIndexBuffer::GDataIndexBuffer()
{
	m_Format = 0U;
}

GDataIndexBuffer::~GDataIndexBuffer()
{

}

