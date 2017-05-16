//
//  GFont.cpp
//  GX
//
//  Created by GuGengxin.
//  Copyright by gxengine.com
//

#include "GFont.h"
//Down include other h file

//Up include other h file
#include "GXGObject.h"

GX_GOBJECT_IMPLEMENT(GFont::Glyph, GObject);

GFont::Glyph::Glyph()
{
    m_Code=0u;
    m_Index=0u;
}

GFont::Glyph::~Glyph()
{
    
}


GX_GOBJECT_IMPLEMENT(GFont, GObject);

GFont::GFont()
{
	
}

GFont::~GFont()
{
}


