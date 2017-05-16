//
//  GFTFont.cpp
//  GX
//
//  Created by GuGengxin.
//  Copyright by gxengine.com
//

#include "GFTFont.h"
//Down include other h file
#if __llvm__
#pragma clang diagnostic push
#pragma clang diagnostic ignored"-Wdocumentation"
#endif
#include <ft2build.h>
#include FT_FREETYPE_H
#if __llvm__
#pragma clang diagnostic pop
#endif
//Up include other h file
#include "GXGObject.h"


GX_GOBJECT_IMPLEMENT(GFTFont::Glyph, GFont::Glyph);

GFTFont::Glyph::Glyph()
{
    
}

GFTFont::Glyph::~Glyph()
{
    
}


GX_GOBJECT_IMPLEMENT(GFTFont, GFont);

GFTFont::GFTFont()
{
    m_Data=NULL;
    m_Face=NULL;
    m_Stroker=NULL;
    m_OLSize=0;
    //m_GlyphCache;
}

GFTFont::~GFTFont()
{
    GO::release(m_Data);
}

bool GFTFont::create(GData* data,gint32 size,gint32 outlineSize)
{
    
    
    return false;
}


