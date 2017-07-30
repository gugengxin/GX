//
//  GXML.h
//  GX
//
//  Created by GuGengxin.
//  Copyright by gxengine.com
//

#ifndef GXML_h
#define GXML_h

#include "GXPrefix.h"
#include "GObject.h"
#include "GList.h"
#include "GString.h"
#include "GReader.h"



#include "GXGObject.h"
// Down can't include other h file

class GXML
{
public:
    class Data : public GObject {
        GX_GOBJECT(Data);
    public:
        
    };
public:
    //static GMap<GString, GString>* read(GReader* reader);
};

// Up can't include other h file
#include "GXGObjectUD.h"

#endif /* GXML_h */
