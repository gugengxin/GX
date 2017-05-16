//
//  GFTFont.h
//  GX
//
//  Created by GuGengxin.
//  Copyright by gxengine.com
//

#ifndef GFTFont_h
#define GFTFont_h

#include "GXPrefix.h"
#include "GFont.h"
#include "GData.h"


#include "GXGObject.h"
// Down can't include other h file

class GFTFont : public GFont
{
    friend class GFontManager;
	GX_GOBJECT(GFTFont);
public:
    class Glyph : public GObject {
        GX_GOBJECT(Glyph);
    public:
        virtual gint32 getAdvanceX();
        virtual GRectN getCBox();
    private:
        
    };
public:
    bool create(GData* data,gint32 size,gint32 outlineSize);
public:
    virtual gint32 getHeight();
    virtual gint32 getAscender();
    virtual bool hasKerning();
    virtual gint32 getKerningX(guint32 index,guint32 next);
    virtual guint32 getGlyphCount();
    virtual GFont::Glyph* getGlyph(guint32 code);
private:
    GData*          m_Data;
    void*           m_Face;
    void*           m_Stroker;
    gint32          m_OLSize;
    GArray<Glyph>   m_GlyphCache;
};

// Up can't include other h file
#include "GXGObjectUD.h"

#endif /* GFTFont_h */
