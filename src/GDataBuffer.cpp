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
#endif
}

GDataBufferBase::~GDataBufferBase()
{
#ifdef GX_OPENGL

#elif defined(GX_DIRECTX)
	if (m_Buffer) {
		m_Buffer->Release();
	}
#endif
}

bool GDataBufferBase::changeBytes(guint toSize)
{
#ifdef GX_OPENGL
	return m_Data.changeBytes(toSize);
#elif defined(GX_DIRECTX)
	ID3D10Device* device = GX::D3DDevice();

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
#endif
}
void GDataBufferBase::unmap()
{
#ifdef GX_OPENGL

#elif defined(GX_DIRECTX)
	if (m_Buffer) {
		m_Buffer->Unmap();
	}
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

