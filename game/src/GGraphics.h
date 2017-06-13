//
//  GGraphics.h
//  GX
//
//  Created by GuGengxin.
//  Copyright by gxengine.com
//

#ifndef GGraphics_h
#define GGraphics_h

#include "GXPrefix.h"
#include "GGraphBase.h"



#include "GXGObject.h"
// Down can't include other h file

class GGraphics : public GGraphBase
{
	GX_GOBJECT(GGraphics);
public:

private:
    gint m_Mode;
};

// Up can't include other h file
#include "GXGObjectUD.h"

#endif /* GGraphics_h */
