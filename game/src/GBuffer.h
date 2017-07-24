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
#include "GObject.h"
#if defined(GX_OPENGL)
#include "GXData.h"
#elif defined(GX_DIRECTX)

#elif defined(GX_METAL)

#endif





#include "GXGObject.h"
// Down can't include other h file

class GBuffer : public GObject {
    GX_GOBJECT(GBuffer);
public:
	typedef enum _Usage {
		UsageDefault,	//GPU RW
		UsageImmutable,	//GPU R
		UsageDynamic,	//GPU R & CPU W
		UsageStaging,	//GPU RW & CPU RW
	} Usage;
public:
	bool create(guint toSize,Usage usage,const void* pInitData);
	void destroy();
private:
#if defined(GX_OPENGL)
    
#elif defined(GX_DIRECTX)
    virtual UINT getBindFlags() = 0;
#endif
private:
#if defined(GX_OPENGL)
    GX::Data m_Data;
#elif defined(GX_DIRECTX)
    ID3D10Buffer* m_Buffer;
#elif defined(GX_METAL)
    void* m_Buffer;
#endif
};


// Up can't include other h file
#include "GXGObjectUD.h"










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
