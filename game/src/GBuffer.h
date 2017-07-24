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
#if defined(GX_DIRECTX)
	friend class GDShader;
#endif
    GX_GOBJECT(GBuffer);
public:
	typedef enum _Usage {
		UsageDefault,	//GPU RW
		UsageImmutable,	//GPU R
		UsageDynamic,	//GPU R & CPU W
		UsageStaging,	//GPU RW & CPU RW
	} Usage;

	class Writer {
		friend class GBuffer;
	private:
		Writer(GBuffer* buffer);
		~Writer();
	private:
		void start(guint offset);
	public:
		Writer& write(const void* data, guint bytes);
		void end();
	private:
		GBuffer* m_Buffer;
		void*	 m_MapData;	
	};
public:
	bool create(guint toSize,Usage usage,const void* pInitData);
	void destroy();
	Writer wirter(guint offset=0);
protected:
	void* map();
	void unmap();
#ifdef GX_OPENGL
	virtual void readyUse() = 0;
	virtual const GLvoid * getData() = 0;
	virtual void doneUse() = 0;

	inline const GLvoid* getData(gint offset) {
		return (const GLvoid*)(((guint8*)getData()) + getOffset() + offset);
	}
#elif defined(GX_DIRECTX)
	ID3D10Buffer** getBufferPtr();
	ID3D10Buffer*  getBuffer();
#elif defined(GX_METAL)
	virtual void* getBuffer() = 0;
#endif
private:
#if defined(GX_DIRECTX)
    virtual UINT getBindFlags();
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

#endif /* GBuffer_h */
