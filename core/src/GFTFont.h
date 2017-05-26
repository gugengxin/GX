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
    class Glyph : public GFont::Glyph {
        friend class GFTFont;
        GX_GOBJECT(Glyph);
    public:
		virtual gint32 getWidth();
		virtual gint32 getHeight();
        virtual gint32 getHoriBearingX();
        virtual gint32 getHoriBearingY();
        virtual gint32 getVertBearingX();
        virtual gint32 getVertBearingY();
    private:
        inline gint getUseNumber() {
            return m_UseNumber;
        }
        inline void addUseNumber(gint step) {
            m_UseNumber+=step;
        }
        bool load(GFTFont* font,guint32 index);
    private:
        gint   m_UseNumber;
    private:
        struct Metrics {
            gint32  width;
            gint32  height;
            
            gint32  horiBearingX;
            gint32  horiBearingY;
            //gint32  horiAdvance;
            
            gint32  vertBearingX;
            gint32  vertBearingY;
            //gint32  vertAdvance;
        } m_Metrics;
        
    private:
        void*  m_Glyph;
        void*  m_Outline;
    };
public:
    bool create(GData* data,gint32 size,gint32 outlineSize);
public:
    virtual gint32 getScaleX();
    virtual gint32 getScaleY();
    virtual gint32 getHeight();
    virtual gint32 getAscender();
    virtual gint32 getDescender();
    virtual gint32 getAdvanceH(guint32 index);
    virtual gint32 getAdvanceV(guint32 index);
    virtual bool hasKerning();
    virtual gint32 getKerningX(guint32 index,guint32 next);
	virtual bool hasOutline();
	virtual gint32 getOutlineSize();
public:
    virtual guint32 getIndex(guint32 code);
    virtual guint32 getVariantIndex(guint32 code,guint32 variantSelector);
    virtual guint32 getGlyphCount();
    virtual GFont::Glyph* getGlyph(guint32 index);
public:
    inline void* getFace() const {
        return m_Face;
    }
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
