//
//  GBuffer.h
//  GX
//
//  Created by Gengxin Gu on 16/6/1.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GBuffer_h
#define GBuffer_h

#include "GXPrefix.h"
#include "GX3DAPI.h"

class GIBuffer
{
public:
	virtual guint getOffset() const = 0;
	virtual guint getStride() const = 0;
#ifdef GX_OPENGL
	virtual void readyUse() = 0;
	virtual const GLvoid * getData() = 0;
	virtual void doneUse() = 0;

	inline const GLvoid* getData(gint offset) {
		return (const GLvoid*)(((guint8*)getData()) + getOffset() + offset);
	}
#elif defined(GX_DIRECTX)
	virtual ID3D10Buffer** getBufferPtr() = 0;
	virtual ID3D10Buffer*  getBuffer() = 0;
#elif defined(GX_METAL)
    virtual void* getBuffer() = 0;
#endif
};

class GIIndexBuffer
{
public:
	virtual guint getFormat() const = 0;
#ifdef GX_OPENGL
	virtual void readyUse() = 0;
	virtual const GLvoid * getData() = 0;
	virtual void doneUse() = 0;
#elif defined(GX_DIRECTX)
	virtual ID3D10Buffer** getBufferPtr() = 0;
	virtual ID3D10Buffer*  getBuffer() = 0;
#elif defined(GX_DIRECTX)
    virtual void* getBuffer() = 0;
#endif
};


#endif /* GBuffer_h */
