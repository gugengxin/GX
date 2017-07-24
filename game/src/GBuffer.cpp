//
//  GBuffer.cpp
//  GX
//
//  Created by Gengxin Gu on 16/6/1.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#include "GBuffer.h"


#include "GXGObject.h"


GX_GOBJECT_IMPLEMENT(GBuffer, GObject);

GBuffer::GBuffer()
{
#ifdef GX_OPENGL

#elif defined(GX_DIRECTX)
	m_Buffer = NULL;
#elif defined(GX_METAL)

#endif
}

GBuffer::~GBuffer()
{
#ifdef GX_OPENGL

#elif defined(GX_DIRECTX)
	if (m_Buffer) {
		m_Buffer->Release();
	}
#elif defined(GX_METAL)

#endif
}

bool GBuffer::create(guint toSize, Usage usage, const void* pInitData)
{
#ifdef GX_OPENGL

#elif defined(GX_DIRECTX)
	ID3D10Device* device = GX::direct3DDevice();

	ID3D10Buffer* bufNew;

	D3D10_BUFFER_DESC bd = { 0 };
	switch (usage)
	{
	case UsageDefault:
	default:
		if (!pInitData) {
			return false;
		}
		bd.Usage = D3D10_USAGE_DEFAULT;
		bd.CPUAccessFlags = 0;
		break;
	case UsageImmutable:
		if (!pInitData) {
			return false;
		}
		bd.Usage = D3D10_USAGE_IMMUTABLE;
		bd.CPUAccessFlags = 0;
		break;
	case UsageDynamic:
		bd.Usage = D3D10_USAGE_DYNAMIC;
		bd.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
		break;
	case UsageStaging:
		bd.Usage = D3D10_USAGE_STAGING;
		bd.CPUAccessFlags = D3D10_CPU_ACCESS_READ|D3D10_CPU_ACCESS_WRITE;
		break;
	}
	bd.ByteWidth = (UINT)toSize;
	bd.BindFlags = getBindFlags();

	D3D10_SUBRESOURCE_DATA sd = {0};
	sd.pSysMem = pInitData;

	if (FAILED(device->CreateBuffer(&bd, &sd, &bufNew))) {
		return false;
	}

	if (m_Buffer) {
		m_Buffer->Release();
	}
	m_Buffer = bufNew;
	return true;
#elif defined(GX_METAL)

#endif
}

void GBuffer::destroy()
{
#ifdef GX_OPENGL

#elif defined(GX_DIRECTX)
	if (m_Buffer) {
		m_Buffer->Release();
		m_Buffer = NULL;
	}
#elif defined(GX_METAL)

#endif
}
