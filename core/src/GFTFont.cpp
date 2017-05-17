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
#include FT_STROKER_H
#if __llvm__
#pragma clang diagnostic pop
#endif
#include "GFontManager.h"
//Up include other h file
#include "GXGObject.h"




#define M_GLYPH()   ((FT_Glyph)m_Glyph)
#define M_OLGLYPH() ((FT_Glyph)m_OLGlyph)
#define M_OLDATA() ((OLData*)m_OLData)
typedef struct _OLData {
    FT_Bitmap bitmap;
} OLData;

GX_GOBJECT_IMPLEMENT(GFTFont::Glyph, GFont::Glyph);

GFTFont::Glyph::Glyph()
{
    m_UseNumber=0;
    m_Glyph=NULL;
    m_OLGlyph=NULL;
    m_OLSize=0;
    m_OLData=NULL;
    m_CBox.set(0, 0, -1, 0);
}

GFTFont::Glyph::~Glyph()
{
    if (m_OLGlyph) {
        FT_Done_Glyph(M_OLGLYPH());
    }
    if (m_OLData) {
        free(m_OLData);
    }
    if (m_Glyph) {
        FT_Done_Glyph(M_GLYPH());
    }
}

bool GFTFont::Glyph::load(GFTFont* font,guint32 code)
{
    FT_Face face=(FT_Face)font->getFace();
    
    setIndex(FT_Get_Char_Index( face, (FT_ULong)code ));
    if(FT_Load_Glyph( face, getIndex(), FT_LOAD_NO_HINTING | FT_LOAD_NO_AUTOHINT | FT_LOAD_NO_BITMAP )) {
        return false;
    }
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

gint32 GFTFont::getHeight()
{
    return GX_CAST_S(gint32, (M_FACE()->size->metrics.height>>6)+m_OLSize*2);
}
gint32 GFTFont::getAscender()
{
    return GX_CAST_S(gint32, (M_FACE()->size->metrics.ascender>>6)+m_OLSize);
}
bool GFTFont::hasKerning()
{
    return FT_HAS_KERNING( M_FACE() )!=0;
}
gint32 GFTFont::getKerningX(guint32 index,guint32 next)
{
    FT_Vector delta;
    FT_Get_Kerning( M_FACE(), index, next, ft_kerning_default, &delta );
    return GX_CAST_S(gint32,(delta.x >> 6));
}
guint32 GFTFont::getGlyphCount()
{
    return (guint32)M_FACE()->num_glyphs;
}
GFont::Glyph* GFTFont::getGlyph(guint32 code)
{
    for (gint i=0; i<m_GlyphCache.getCount(); i++) {
        Glyph* obj=GX_CAST_R(Glyph*, m_GlyphCache.get(i));
        if (obj->getCode()==code) {
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
    if (res->load(this, code)) {
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


