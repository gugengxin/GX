//
//  GFTFont.cpp
//  GX
//
//  Created by GuGengxin.
//  Copyright by gxengine.com
//

#include "GFTFont.h"
//Down include other h file
#if __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#endif
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_ADVANCES_H
#include FT_STROKER_H
#include FT_OUTLINE_H
#if __clang__
#pragma clang diagnostic pop
#endif
#include "GFontManager.h"
//Up include other h file
#include "GXGObject.h"



#define M_LOAD_FLAGS() (FT_LOAD_DEFAULT | FT_LOAD_NO_HINTING | FT_LOAD_NO_AUTOHINT | FT_LOAD_NO_BITMAP)
#define M_GLYPH()   GX_CAST_R(FT_Glyph,m_Glyph)
#define M_OLGLYPH() GX_CAST_R(FT_OutlineGlyph,m_OLGlyph)

//typedef struct _Outline {
//    FT_Glyph   glyph;
//    GDib*      dib;
//    FT_Outline outline;
//} Outline;
//
//static Outline* _OLNew(FT_GlyphSlot gs,FT_Glyph gh)
//{
//    FT_Outline& ol=gs->outline;
//    Outline* res=GX_CAST_R(Outline*, malloc(sizeof(Outline) + ol.n_points*(sizeof(FT_Vector)+sizeof(char)) + ol.n_contours*sizeof(short)));
//    res->glyph=gh;
//    res->dib=NULL;
//    /*
//    typedef struct  FT_Outline_
//    {
//        short       n_contours;      
//        short       n_points;        
//        
//        FT_Vector*  points;          
//        char*       tags;            
//        short*      contours;        
//        
//        int         flags;
//        
//    } FT_Outline;
//    //*/
//    res->outline.n_contours=ol.n_contours;
//    res->outline.n_points=ol.n_points;
//    res->outline.points=GX_CAST_R(FT_Vector*, GX_CAST_R(guchar*, res)+sizeof(Outline));
//    memcpy(res->outline.points, ol.points, ol.n_points*sizeof(FT_Vector));
//    res->outline.tags=GX_CAST_R(char*, GX_CAST_R(guchar*, res)+sizeof(Outline)+ol.n_points*sizeof(FT_Vector));
//    memcpy(res->outline.tags, ol.tags, ol.n_points*sizeof(char));
//    res->outline.contours=GX_CAST_R(short*, GX_CAST_R(guchar*, res)+ol.n_points*(sizeof(FT_Vector)+sizeof(char)));
//    memcpy(res->outline.contours, ol.contours, ol.n_contours*sizeof(short));
//    res->outline.flags=ol.flags&(~FT_OUTLINE_OWNER);
//    return res;
//}
//
//static void _OLDone(Outline* ol)
//{
//    GO::release(ol->dib);
//    if (ol->glyph) {
//        FT_Done_Glyph(ol->glyph);
//    }
//    free(ol);
//}


GX_GOBJECT_IMPLEMENT(GFTFont::Glyph, GFont::Glyph);

GFTFont::Glyph::Glyph()
{
    m_UseNumber=0;
    memset(&m_Metrics, 0, sizeof(m_Metrics));
    m_Glyph=NULL;
    m_GlyphDib=NULL;
    m_OLGlyph=NULL;
    m_OLGlyphDib=NULL;
}

GFTFont::Glyph::~Glyph()
{
    GO::release(m_OLGlyphDib);
    if (m_OLGlyph) {
        FT_Done_Glyph(GX_CAST_R(FT_Glyph, m_OLGlyph));
    }
    GO::release(m_GlyphDib);
    if (m_Glyph) {
        FT_Done_Glyph(M_GLYPH());
    }
}

gint32 GFTFont::Glyph::getWidth()
{
	return m_Metrics.width;
}
gint32 GFTFont::Glyph::getHeight()
{
	return m_Metrics.height;
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

gint32 GFTFont::Glyph::getOutlineSize()
{
    return getFont()->getOutlineSize();
}
guint32 GFTFont::Glyph::getOutlinePointCount()
{
	if (m_OLGlyph) {
		return GX_CAST_S(guint32, M_OLGLYPH()->outline.n_points);
	}
	return 0;
}
gint32 GFTFont::Glyph::getOutlinePointX(guint32 index)
{
	if (m_OLGlyph) {
		return GX_CAST_S(gint32 , M_OLGLYPH()->outline.points[index].x);
	}
	return 0;
}
gint32 GFTFont::Glyph::getOutlinePointY(guint32 index)
{
	if (m_OLGlyph) {
		return GX_CAST_S(gint32, M_OLGLYPH()->outline.points[index].y);
	}
	return 0;
}

bool GFTFont::Glyph::load(GFTFont* font,guint32 index)
{
    FT_Face face=(FT_Face)font->getFace();
    if(FT_Load_Glyph( face, index, M_LOAD_FLAGS() )) {
        return false;
    }
    
    FT_Glyph glyph=NULL;
    if (FT_Get_Glyph( face->glyph, &glyph )) {
        return false;
    }
    
    if (font->hasOutline() && glyph->format!=FT_GLYPH_FORMAT_OUTLINE) {
        return false;
    }
    
    FT_Glyph_Metrics& metrics=face->glyph->metrics;
    m_Metrics.width=GX_CAST_S(gint32,metrics.width)+(font->getOutlineSize()<<1);
    m_Metrics.height=GX_CAST_S(gint32,metrics.height)+(font->getOutlineSize()<<1);
    m_Metrics.horiBearingX=GX_CAST_S(gint32,metrics.horiBearingX)+font->getOutlineSize();
    m_Metrics.horiBearingY=GX_CAST_S(gint32,metrics.horiBearingY)+font->getOutlineSize();
    //m_Metrics.horiAdvance=GX_CAST_S(gint32,metrics.horiAdvance)+font->getOutlineSize()*2;
    m_Metrics.vertBearingX=GX_CAST_S(gint32,metrics.vertBearingX)+font->getOutlineSize();
    m_Metrics.vertBearingY=GX_CAST_S(gint32,metrics.vertBearingY)+font->getOutlineSize();
    //m_Metrics.vertAdvance=GX_CAST_S(gint32,metrics.vertAdvance)+font->getOutlineSize()*2;
    
    FT_Glyph glyphOL=NULL;
    if (font->hasOutline()) {
        glyphOL=glyph;
        if(FT_Glyph_StrokeBorder(&glyphOL, (FT_Stroker)font->m_Stroker, 0, 0)) {
            FT_Done_Glyph(glyph);
            return false;
        }
        if (glyphOL->format!=FT_GLYPH_FORMAT_OUTLINE) {
            FT_Done_Glyph(glyph);
            FT_Done_Glyph(glyphOL);
            return false;
        }
    }
    
    setFont(font);
    setIndex(index);
    m_Glyph=glyph;
    GO::release(m_GlyphDib);
    m_GlyphDib=NULL;
    m_OLGlyph=glyphOL;
    GO::release(m_OLGlyphDib);
    m_OLGlyphDib=NULL;
    return true;
}

void GFTFont::Glyph::render()
{
    if (m_OLGlyph) {
        FT_BBox bbox;
        FT_Outline *outline = &M_OLGLYPH()->outline;
        FT_Glyph_Get_CBox(GX_CAST_R(FT_Glyph, m_OLGlyph),FT_GLYPH_BBOX_GRIDFIT,&bbox);
        int width = GX_CAST_S(int, (bbox.xMax - bbox.xMin)>>6);
        int rows = GX_CAST_S(int, (bbox.yMax - bbox.yMin)>>6);
        
        
        GDib* dib=GDib::alloc();
        dib->setWidth(width);
        dib->setHeight(rows);
        dib->setPixelFormat(GX::PixelFormatA8);
        dib->setStride(width);
        dib->changeDataBytes(width*rows*1);
        
        FT_Bitmap bmp;
        bmp.buffer = GX_CAST_R(unsigned char*, dib->getDataPtr());
        bmp.width = width;
        bmp.rows = rows;
        bmp.pitch = width;
        bmp.pixel_mode = FT_PIXEL_MODE_GRAY;
        bmp.num_grays = 256;
        
        FT_Raster_Params params;
        memset(&params, 0, sizeof (params));
        params.source = outline;
        params.target = &bmp;
        params.flags = FT_RASTER_FLAG_AA;
        FT_Outline_Translate(outline,-bbox.xMin,-bbox.yMin);
        
        if(FT_Outline_Render(GX_CAST_R(FT_Library, GFontManager::shared()->getFTLibrary()), outline, &params)) {
            GO::release(dib);
            return;
        }
        
        GO::release(m_OLGlyphDib);
        m_OLGlyphDib=dib;
    }
    
    
    if(FT_Glyph_To_Bitmap((FT_Glyph*)&m_Glyph, FT_RENDER_MODE_NORMAL, NULL, 1)==0) {
        GDib* dib=GDib::alloc();
        FT_Bitmap& bmp=GX_CAST_R(FT_BitmapGlyph, m_Glyph)->bitmap;
        
        dib->setWidth(bmp.width);
        dib->setHeight(bmp.rows);
        dib->setPixelFormat(GX::PixelFormatA8);
        dib->setStride(bmp.pitch);
        dib->setStaticData(bmp.buffer, bmp.pitch*bmp.rows);
        
        GO::release(m_GlyphDib);
        m_GlyphDib=dib;
    }
}

GDib* GFTFont::Glyph::getDib()
{
    if (!isBlank() && !m_GlyphDib) {
        render();
    }
    return m_GlyphDib;
}
GDib* GFTFont::Glyph::getOutlineDib()
{
    if (!isBlank() && m_OLGlyph && !m_GlyphDib) {
        render();
    }
    return m_OLGlyphDib;
}


#undef M_GLYPH
#undef M_OLGLYPH

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
	m_GlyphCache.removeAll();
    if (m_Stroker) {
        FT_Stroker_Done(M_STROKER());
    }
    if (m_Face) {
        FT_Done_Face(M_FACE());
    }
    GO::release(m_Data);
}

bool GFTFont::create(GData* data,float size,float outlineSize)
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
    
    if (FT_Select_Charmap(ftFace, FT_ENCODING_UNICODE)) {
        FT_Done_Face(ftFace);
        return false;
    }
    
    FT_F26Dot6 realSize=GX_CAST_S(FT_F26Dot6, size*64.0f);
    if (FT_Set_Char_Size(ftFace, realSize, realSize, 72, 72)) {
        FT_Done_Face(ftFace);
        return false;
    }
    
    FT_Fixed realOLSize=0;
    if (outlineSize>0.0f) {
        realOLSize=GX_CAST_S(FT_Fixed, outlineSize*64.0f);
        if(FT_Stroker_New(ftLib, (FT_Stroker*)&m_Stroker)) {
            FT_Done_Face(ftFace);
            return false;
        }
        FT_Stroker_Set(M_STROKER(), realOLSize, FT_STROKER_LINECAP_ROUND, FT_STROKER_LINEJOIN_ROUND, 0);
    }
    
    GX_OBJECT_SET(m_Data, data);
    m_OLSize=GX_CAST_S(gint32, realOLSize);
    m_Face=ftFace;
	GFont::create(GX_CAST_S(gint32, realSize));
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
    return GX_CAST_S(gint32, (M_FACE()->size->metrics.height)+(m_OLSize<<1));
}
gint32 GFTFont::getAscender()
{
    return GX_CAST_S(gint32, (M_FACE()->size->metrics.ascender)+(m_OLSize<<0));
}
gint32 GFTFont::getDescender()
{
    return GX_CAST_S(gint32, (M_FACE()->size->metrics.descender)+(m_OLSize<<0));
}
gint32 GFTFont::getAdvanceH(guint32 index)
{
    FT_Fixed v=0;
    
    if(FT_Get_Advance(M_FACE(),index,M_LOAD_FLAGS(),&v)) {
        return 0;
    }
    
    v=((v + (1<<9)) >> 10);
    
    return GX_CAST_S(gint32, v)+(m_OLSize<<1);
}
gint32 GFTFont::getAdvanceV(guint32 index)
{
    FT_Fixed v=0;
    
    if(FT_Get_Advance(M_FACE(),index,M_LOAD_FLAGS()|FT_LOAD_VERTICAL_LAYOUT,&v)) {
        return 0;
    }
    
    v=((v + (1<<9)) >> 10);
    
    return GX_CAST_S(gint32, v)+(m_OLSize<<1);
}
bool GFTFont::hasKerning()
{
    return FT_HAS_KERNING( M_FACE() )!=0;
}
gint32 GFTFont::getKerningX(guint32 index,guint32 next)
{
    FT_Vector delta;
    FT_Get_Kerning( M_FACE(), index, next, FT_KERNING_UNFITTED, &delta );
    return GX_CAST_S(gint32,(delta.x));
}

bool GFTFont::hasOutline()
{
	return m_Stroker != NULL;
}

gint32 GFTFont::getOutlineSize()
{
	return m_OLSize<<0;
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
            m_GlyphCache.removeLast(M_FTGLYPH_CACHE_COUNT/2);
        }
        
        gint j=m_GlyphCache.getCount()-1;
        for (; j>=0; j--) {
            Glyph* objTemp=GX_CAST_R(Glyph*, m_GlyphCache.get(j));
            if (objTemp->getUseNumber()>res->getUseNumber()) {
                break;
            }
        }
        m_GlyphCache.insert(j+1, res);
        GO::autorelease(res);
    }
    else {
        GO::release(res);
        res=NULL;
    }
    return res;
}

bool GFTFont::getGlyphName(guint32 index, char* name, guint32 size)
{
	bool ret = !FT_Get_Glyph_Name(M_FACE(), index, name, size);
	if (ret && (size && !*name))
		ret = false;
	return ret;
}

bool GFTFont::getGlyphNameIndex(guint32* idxOut, const char *name, gint32 len)
{
	if (len < 0)
		*idxOut = FT_Get_Name_Index(M_FACE(), (FT_String *)name);
	else {
		/* Make a nul-terminated version. */
		char buf[128];
		len = len<((int)sizeof(buf)-1)?len: ((int)sizeof(buf) - 1);
		strncpy(buf, name, len);
		buf[len] = '\0';
		*idxOut = FT_Get_Name_Index(M_FACE(), buf);
	}

	if (*idxOut == 0)
	{
		/* Check whether the given name was actually the name of glyph 0. */
		char buf[128];
		if (!FT_Get_Glyph_Name(M_FACE(), 0, buf, sizeof(buf)) &&
			len < 0 ? !strcmp(buf, name) : !strncmp(buf, name, len))
			return true;
	}

	return *idxOut != 0;
}


