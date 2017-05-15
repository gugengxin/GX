//
//  GFT.cpp
//  GX
//
//  Created by GuGengxin.
//  Copyright by gxengine.com
//

#include "GFT.h"
#if __llvm__
#pragma clang diagnostic push
#pragma clang diagnostic ignored"-Wdocumentation"
#endif
#include <ft2build.h>
#include FT_FREETYPE_H
#if __llvm__
#pragma clang diagnostic pop
#endif


#include "GXGObject.h"

GX_GOBJECT_IMPLEMENT(GFT::Glyph, GObject);

GFT::Glyph::Glyph()
{
    
}

GFT::Glyph::~Glyph()
{
    
}


GX_GOBJECT_IMPLEMENT(GFT::Font, GObject);

GFT::Font::Font()
{
    m_Data=NULL;
    m_Face=NULL;
    m_Stroker=NULL;
    m_Size=0;
    m_OLSize=0;
}

GFT::Font::~Font()
{
    GO::release(m_Data);
}


