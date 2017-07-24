//
//  GIndexBuffer.h
//  GX
//
//  Created by GuGengxin.
//  Copyright by gxengine.com
//

#ifndef GIndexBuffer_h
#define GIndexBuffer_h

#include "GXPrefix.h"
#include "GBuffer.h"



#include "GXGObject.h"
// Down can't include other h file

class GIndexBuffer : public GBuffer
{
	GX_GOBJECT(GIndexBuffer);
public:
private:
#if defined(GX_DIRECTX)
	virtual UINT getBindFlags();
#endif
private:

};

// Up can't include other h file
#include "GXGObjectUD.h"

#endif /* GIndexBuffer_h */
