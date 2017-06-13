//
//  GDataBuffer.h
//  GX
//
//  Created by Gengxin Gu on 16/6/1.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GDataBuffer_h
#define GDataBuffer_h

#include "GXPrefix.h"
#include "GObject.h"
#include "GBuffer.h"
#include "GXData.h"

#include "GXGObject.h"

class GDataBufferBase
{
	friend class GDataBuffer;
	friend class GDataIndexBuffer;
protected:
	GDataBufferBase();
	~GDataBufferBase();
public:
    guint getBytes();
	bool changeBytes(guint toSize);
	bool changeBytesIfNeed(guint toSize);
	void freeSelf();
	void* map();
	void  unmap();
private:
#ifdef GX_OPENGL

#elif defined(GX_DIRECTX)
	virtual UINT getBindFlags() = 0;
#endif
private:
#if defined(GX_OPENGL)
	GX::Data m_Data;
#elif defined(GX_DIRECTX)
	ID3D10Buffer* m_Buffer;
	guint		  m_DataBytes;
#elif defined(GX_METAL)
    void* m_Buffer;
#endif
};

class GDataBuffer : public GObject, public GDataBufferBase, public GIBuffer
{
    friend class GGraphBase;
	GX_GOBJECT(GDataBuffer);
public:
	inline void setOffset(guint v) {
		m_Offset = GX_CAST_S(guint16, v);
	}
	inline void setStride(guint v) {
		m_Stride = GX_CAST_S(guint16, v);
	}

	virtual guint getOffset() const {
		return m_Offset;
	}
	virtual guint getStride() const {
		return m_Stride;
	}
    
    gint getCount();
    bool changeCount(guint offset,guint stride,gint count);
    bool changeCount(gint count);
    
#ifdef GX_OPENGL
	virtual void readyUse() {
	}
	virtual const GLvoid * getData() {
		return m_Data.getPtr();
	}
	virtual void doneUse() {
	}
#elif defined(GX_DIRECTX)
	virtual ID3D10Buffer** getBufferPtr() {
		return &m_Buffer;
	}
	virtual ID3D10Buffer*  getBuffer() {
		return m_Buffer;
	}
#elif defined(GX_METAL)
    virtual void* getBuffer() {
        return m_Buffer;
    }
#endif
private:
#ifdef GX_OPENGL

#elif defined(GX_DIRECTX)
	virtual UINT getBindFlags() {
		return D3D10_BIND_VERTEX_BUFFER;
	}
#endif
private:
	guint16 m_Offset;
	guint16 m_Stride;
};

class GDataIndexBuffer : public GObject, public GDataBufferBase, public GIIndexBuffer
{
	GX_GOBJECT(GDataIndexBuffer);
public:
	inline void setFormat(guint v) {
		m_Format = v;
	}
	virtual guint getFormat() const {
		return m_Format;
	}
#ifdef GX_OPENGL
	virtual void readyUse() {
	}
	virtual const GLvoid * getData() {
		return m_Data.getPtr();
	}
	virtual void doneUse() {
	}
#elif defined(GX_DIRECTX)
	virtual ID3D10Buffer** getBufferPtr() {
		return &m_Buffer;
	}
	virtual ID3D10Buffer*  getBuffer() {
		return m_Buffer;
    }
#elif defined(GX_METAL)
    virtual void* getBuffer() {
        return m_Buffer;
    }
#endif
private:
#ifdef GX_OPENGL

#elif defined(GX_DIRECTX)
	virtual UINT getBindFlags() {
		return D3D10_BIND_INDEX_BUFFER;
	}
#endif
private:
	guint m_Format;
};

#include "GXGObjectUD.h"


#endif /* GDataBuffer_h */
