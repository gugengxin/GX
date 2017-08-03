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
    m_Buffer = NULL;
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
    [GX_CAST_R(id,m_Buffer) release];
#endif
}

bool GBuffer::create(guint toSize, Usage usage, const void* pInitData)
{
#ifdef GX_OPENGL
    GX_UNUSED(usage);
    if (m_Data.changeBytes(toSize)) {
        if (pInitData) {
            memcpy(m_Data.getPtr(), pInitData, toSize);
        }
        return true;
    }
    return false;
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
		break;
	case UsageImmutable:
		if (!pInitData) {
			return false;
		}
		bd.Usage = D3D10_USAGE_IMMUTABLE;
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
    
    MTLResourceOptions ro=0;
    switch (usage)
    {
        case UsageDefault:
        case UsageImmutable:
        default:
            if (!pInitData) {
                return false;
            }
            ro=MTLResourceCPUCacheModeDefaultCache;
            break;
        case UsageDynamic:
            ro=MTLResourceCPUCacheModeWriteCombined;
            break;
        case UsageStaging:
            break;
    }
    
    id<MTLBuffer> bufNew;
    if (pInitData) {
        bufNew=[GX::metalDevice() newBufferWithBytes:pInitData length:toSize options:ro];
    }
    else {
        bufNew=[GX::metalDevice() newBufferWithLength:toSize options:ro];
    }
    if (!bufNew) {
        return false;
    }
    [GX_CAST_R(id<MTLBuffer>, m_Buffer) release];
    m_Buffer=[bufNew retain];
    return true;

#endif
}

void GBuffer::destroy()
{
#ifdef GX_OPENGL
    m_Data.freeSelf();
#elif defined(GX_DIRECTX)
	if (m_Buffer) {
		m_Buffer->Release();
		m_Buffer = NULL;
	}
#elif defined(GX_METAL)
    [GX_CAST_R(id,m_Buffer) release];
    m_Buffer = NULL;
#endif
}

GBuffer::Writer GBuffer::wirter(guint offset)
{
	Writer res(this);
	res.start(offset);
	return res;
}

void* GBuffer::map()
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
	return[GX_CAST_R(id<MTLBuffer>, m_Buffer) contents];
#endif
}

void GBuffer::unmap()
{
#ifdef GX_OPENGL

#elif defined(GX_DIRECTX)
	if (m_Buffer) {
		m_Buffer->Unmap();
	}
#elif defined(GX_METAL)

#endif
}


#if defined(GX_OPENGL)

void GBuffer::readyUse()
{
    
}
const GLvoid * GBuffer::getData()
{
    return m_Data.getPtr();
}
void GBuffer::doneUse()
{
    
}

#elif defined(GX_DIRECTX)

ID3D10Buffer** GBuffer::getBufferPtr()
{
	return &m_Buffer;
}
ID3D10Buffer*  GBuffer::getBuffer()
{
	return m_Buffer;
}

UINT GBuffer::getBindFlags()
{
	return D3D10_BIND_VERTEX_BUFFER;
}

#elif defined(GX_METAL)

void* GBuffer::getBuffer()
{
    return m_Buffer;
}

#endif



GBuffer::Writer::Writer(GBuffer* buffer)
{
	m_Buffer = buffer;
	m_MapData = NULL;
}

GBuffer::Writer::~Writer()
{
	if (m_MapData) {
		end();
	}
}

void GBuffer::Writer::start(guint offset)
{
	m_MapData = GX_CAST_R(guint8*, m_Buffer->map())+offset;
}

GBuffer::Writer& GBuffer::Writer::write(const void * data, guint bytes)
{
	memcpy(m_MapData, data, bytes);
	m_MapData= GX_CAST_R(guint8*, m_MapData) + bytes;
	return *this;
}

void GBuffer::Writer::end()
{
	m_Buffer->unmap();
	m_MapData = NULL;
}
