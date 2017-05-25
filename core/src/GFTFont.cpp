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
#include FT_ADVANCES_H
#include FT_STROKER_H
#if __llvm__
#pragma clang diagnostic pop
#endif
#include "GFontManager.h"
//Up include other h file
#include "GXGObject.h"



#define M_LOAD_FLAGS() (FT_LOAD_DEFAULT | FT_LOAD_NO_HINTING | FT_LOAD_NO_AUTOHINT | FT_LOAD_NO_BITMAP)
#define M_GLYPH()   ((FT_Glyph)m_Glyph)
#define M_OLGLYPH() ((FT_Glyph)m_OLGlyph)
//#define M_OLDATA() ((OLData*)m_OLData)
//
//typedef struct _OLData {
//    FT_Bitmap bitmap;
//} OLData;

GX_GOBJECT_IMPLEMENT(GFTFont::Glyph, GFont::Glyph);

GFTFont::Glyph::Glyph()
{
    m_UseNumber=0;
    memset(&m_Metrics, 0, sizeof(m_Metrics));
    m_Glyph=NULL;
    m_OLGlyph=NULL;
    m_OLSize=0;
    //m_OLData=NULL;
}

GFTFont::Glyph::~Glyph()
{
//    if (m_OLData) {
//        free(m_OLData);
//    }
    if (m_OLGlyph) {
        FT_Done_Glyph(M_OLGLYPH());
    }
    if (m_Glyph) {
        FT_Done_Glyph(M_GLYPH());
    }
}

gint32 GFTFont::Glyph::getHoriBearingX()
{
    return m_Metrics.horiBearingX;
}
gint32 GFTFont::Glyph::getHoriBearingY()
{
    return m_Metrics.horiBearingY;
}
gint32 GFTFont::Glyph::getVertBearingX()
{
    return m_Metrics.vertBearingX;
}
gint32 GFTFont::Glyph::getVertBearingY()
{
    return m_Metrics.vertBearingY;
}

bool GFTFont::Glyph::load(GFTFont* font,guint32 index)
{
    FT_Face face=(FT_Face)font->getFace();
    
    setIndex(index);
    if(FT_Load_Glyph( face, getIndex(), M_LOAD_FLAGS() )) {
        return false;
    }
    
    FT_Glyph_Metrics& metrics=face->glyph->metrics;
    m_Metrics.width=GX_CAST_S(gint32,metrics.width);
    m_Metrics.height=GX_CAST_S(gint32,metrics.height);
    m_Metrics.horiBearingX=GX_CAST_S(gint32,metrics.horiBearingX);
    m_Metrics.horiBearingY=GX_CAST_S(gint32,metrics.horiBearingY);
    //m_Metrics.horiAdvance=GX_CAST_S(gint32,metrics.horiAdvance);
    m_Metrics.vertBearingX=GX_CAST_S(gint32,metrics.vertBearingX);
    m_Metrics.vertBearingY=GX_CAST_S(gint32,metrics.vertBearingY);
    //m_Metrics.vertAdvance=GX_CAST_S(gint32,metrics.vertAdvance);
    
    FT_Glyph glyph=NULL;
    if (FT_Get_Glyph( face->glyph, &glyph )) {
        return false;
    }
    
    if (font->hasOutline() && M_GLYPH()->format==FT_GLYPH_FORMAT_OUTLINE) {
        FT_Glyph glyphOL=glyph;
        if(FT_Glyph_StrokeBorder(&glyphOL, (FT_Stroker)font->m_Stroker, 0, 0)) {
            FT_Done_Glyph(glyphOL);
            return false;
        }
        if (glyphOL->format!=FT_GLYPH_FORMAT_OUTLINE) {
            FT_Done_Glyph(glyphOL);
            return false;
        }
        m_OLGlyph=glyphOL;
        m_OLSize=font->getOutlineSize();
    }
    else {
        m_OLGlyph=NULL;
        m_OLSize=0;
    }
    
    m_Glyph=glyph;
    return true;
}


#undef M_GLYPH
#undef M_OLGLYPH
#undef M_OLDATA

#define M_FTGLYPH_CACHE_COUNT 256
#define M_FACE()    ((FT_Face)m_Face)
#define M_STROKER() ((FT_Stroker)m_Stroker)

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
    if (m_Stroker) {
        FT_Stroker_Done(M_STROKER());
    }
    if (m_Face) {
        FT_Done_Face(M_FACE());
    }
    GO::release(m_Data);
}

bool GFTFont::create(GData* data,gint32 size,gint32 outlineSize)
{
    FT_Library ftLib=GX_CAST_R(FT_Library, GFontManager::shared()->getFTLibrary());
    FT_Face ftFace=NULL;
    if (FT_New_Memory_Face(ftLib,
                           (const FT_Byte*)data->getPtr(),
                           (FT_Long)data->getBytes(),
                           0,
                           &ftFace)) {
        return false;
    }
    
    if (FT_Select_Charmap(M_FACE(), FT_ENCODING_UNICODE)) {
        FT_Done_Face(ftFace);
        return false;
    }
    
    if (FT_Set_Char_Size(M_FACE(), size<<6, size<<6, 72, 72)) {
        FT_Done_Face(ftFace);
        return false;
    }
    
    if (outlineSize>0) {
        if(FT_Stroker_New(ftLib, (FT_Stroker*)&m_Stroker)) {
            FT_Done_Face(ftFace);
            return false;
        }
        FT_Stroker_Set(M_STROKER(), (FT_Fixed)(outlineSize<<6), FT_STROKER_LINECAP_ROUND, FT_STROKER_LINEJOIN_ROUND, 0);
    }
    
    setSize(size);
    GX_OBJECT_SET(m_Data, data);
    m_OLSize=outlineSize;
    m_Face=ftFace;
    
    return true;
}

gint32 GFTFont::getScaleX()
{
    return (gint32) (((guint64) M_FACE()->size->metrics.x_scale * (guint64) M_FACE()->units_per_EM + (1u<<15)) >> 16);
}
gint32 GFTFont::getScaleY()
{
    return (gint32) (((guint64) M_FACE()->size->metrics.y_scale * (guint64) M_FACE()->units_per_EM + (1u<<15)) >> 16);
}

gint32 GFTFont::getHeight()
{
    return GX_CAST_S(gint32, (M_FACE()->size->metrics.height)+((m_OLSize*2)<<6));
}
gint32 GFTFont::getAscender()
{
    return GX_CAST_S(gint32, (M_FACE()->size->metrics.ascender)+(m_OLSize<<6));
}
gint32 GFTFont::getDescender()
{
    return GX_CAST_S(gint32, (M_FACE()->size->metrics.descender)+(m_OLSize<<6));
}
gint32 GFTFont::getAdvanceH(guint32 index)
{
    FT_Fixed v=0;
    
    if(FT_Get_Advance(M_FACE(),index,M_LOAD_FLAGS(),&v)) {
        return 0;
    }
    
    return GX_CAST_S(gint32, v);
}
gint32 GFTFont::getAdvanceV(guint32 index)
{
    FT_Fixed v=0;
    
    if(FT_Get_Advance(M_FACE(),index,M_LOAD_FLAGS()|FT_LOAD_VERTICAL_LAYOUT,&v)) {
        return 0;
    }
    
    return GX_CAST_S(gint32, v);
}
bool GFTFont::hasKerning()
{
    return FT_HAS_KERNING( M_FACE() )!=0;
}
gint32 GFTFont::getKerningX(guint32 index,guint32 next)
{
    FT_Vector delta;
    FT_Get_Kerning( M_FACE(), index, next, ft_kerning_default, &delta );
    return GX_CAST_S(gint32,(delta.x));
}

guint32 GFTFont::getIndex(guint32 code)
{
    return FT_Get_Char_Index(M_FACE(), code);
}
guint32 GFTFont::getVariantIndex(guint32 code,guint32 variantSelector)
{
    return FT_Face_GetCharVariantIndex(M_FACE(), code, variantSelector);
}
guint32 GFTFont::getGlyphCount()
{
    return (guint32)M_FACE()->num_glyphs;
}
GFont::Glyph* GFTFont::getGlyph(guint32 index)
{
    for (gint i=0; i<m_GlyphCache.getCount(); i++) {
        Glyph* obj=GX_CAST_R(Glyph*, m_GlyphCache.get(i));
        if (obj->getIndex()==index) {
            obj->addUseNumber(1);
            gint j=i-1;
            for (; j>=0; j--) {
                Glyph* objTemp=GX_CAST_R(Glyph*, m_GlyphCache.get(j));
                if (objTemp->getUseNumber()>obj->getUseNumber()) {
                    break;
                }
            }
            m_GlyphCache.move(i, j+1);
            return obj;
        }
    }
    
    Glyph* res=Glyph::alloc();
    if (res->load(this, index)) {
        res->addUseNumber(1);
        
        if (m_GlyphCache.getCount()>M_FTGLYPH_CACHE_COUNT) {
            m_GlyphCache.removeLast(M_FTGLYPH_CACHE_COUNT-32);
        }
        
        gint j=m_GlyphCache.getCount()-1;
        for (; j>=0; j--) {
            Glyph* objTemp=GX_CAST_R(Glyph*, m_GlyphCache.get(j));
            if (objTemp->getUseNumber()>res->getUseNumber()) {
                break;
            }
        }
        m_GlyphCache.insert(j+1, res);
        GO::release(res);
    }
    else {
        GO::release(res);
        res=NULL;
    }
    return res;
}


