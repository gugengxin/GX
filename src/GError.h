//
//  GError.h
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#ifndef GError_h
#define GError_h

#include "GXPrefix.h"
#include "GObject.h"
#include "GString.h"


#include "GXGObject.h"
// Down can't include other h file

class GError : public GObject
{
	GX_GOBJECT(GError);
public:

private:
    GString* m_Domain;
    gint     m_Code;
};

// Up can't include other h file
#include "GXGObjectUD.h"

#endif /* GError_h */
