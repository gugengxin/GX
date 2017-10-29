//
//  GTex2DFont.cpp
//  GX
//
//  Created by GuGengxin.
//  Copyright by gxengine.com
//

#include "GTex2DFont.h"
//Down include other h file
#include "GVector.h"
#include "GLog.h"
//Up include other h file
#include "GXGObject.h"


GX_GOBJECT_IMPLEMENT(GTex2DFont::Glyph, GFont::Glyph);

GTex2DFont::Glyph::Glyph()
{
    m_UseNumber=0;
    m_FTGlyph=NULL;
    m_Tex2D=NULL;
    m_OLTex2D=NULL;
    m_Buffer=NULL;
}

GTex2DFont::Glyph::~Glyph()
{
    GO::release(m_FTGlyph);
    GO::release(m_Buffer);
    GO::release(m_Tex2D);
    GO::release(m_OLTex2D);
}

gint32 GTex2DFont::Glyph::getWidth()
{
    return m_FTGlyph->getWidth();
}
gint32 GTex2DFont::Glyph::getHeight()
{
    return m_FTGlyph->getHeight();
}
gint32 GTex2DFont::Glyph::getHoriBearingX()
{
    return m_FTGlyph->getHoriBearingX();
}
gint32 GTex2DFont::Glyph::getHoriBearingY()
{
    return m_FTGlyph->getHoriBearingY();
}
gint32 GTex2DFont::Glyph::getVertBearingX()
{
    return m_FTGlyph->getVertBearingX();
}
gint32 GTex2DFont::Glyph::getVertBearingY()
{
    return m_FTGlyph->getVertBearingY();
}
gint32 GTex2DFont::Glyph::getOutlineSize()
{
    return m_FTGlyph->getOutlineSize();
}
guint32 GTex2DFont::Glyph::getOutlinePointCount()
{
    return m_FTGlyph->getOutlinePointCount();
}
gint32 GTex2DFont::Glyph::getOutlinePointX(guint32 index)
{
    return m_FTGlyph->getOutlinePointX(index);
}
gint32 GTex2DFont::Glyph::getOutlinePointY(guint32 index)
{
    return m_FTGlyph->getOutlinePointY(index);
}

void GTex2DFont::Glyph::load(GTex2DFont* font, GFTFont::Glyph* ftGlyph, guint32 index)
{
    setFont(font);
	setIndex(index);
    GX_OBJECT_SET(m_FTGlyph, ftGlyph);
}

void GTex2DFont::Glyph::render()
{
    m_Buffer=GBuffer::alloc();
    
    GTex2DFont* font=GX_CAST_R(GTex2DFont*, getFont());
    float l=m_FTGlyph->getHoriBearingX()/64.0f;
    float r=(m_FTGlyph->getHoriBearingX()+m_FTGlyph->getWidth())/64.0f;
    float t=m_FTGlyph->getHoriBearingY()/64.0f;
    float b=(m_FTGlyph->getHoriBearingY()-m_FTGlyph->getHeight())/64.0f;
#pragma pack (1)
    struct {
        float pos[3];
        guint16 tc[2];
    } data[]={
        {{l,b,0.0f},{0,0xFFFF}},
        {{r,b,0.0f},{0xFFFF,0xFFFF}},
        {{l,t,0.0f},{0,0}},
        {{r,t,0.0f},{0xFFFF,0}},
    };
#pragma pack ()
    m_Buffer->create(sizeof(data), GBuffer::UsageImmutable, data);
    
    
    if (font->getOutlineSize()<=0) {
        m_Tex2D=GTexture2D::alloc();
        m_Tex2D->create(m_FTGlyph->getDib(), NULL);
    }
    else {
        GDib* dib=m_FTGlyph->getDib();
        GDib* dibOL=m_FTGlyph->getOutlineDib();
        GDib* dibTo=GDib::autoAlloc();
        dibTo->changeData(dibOL->getPixelFormat(), dibOL->getWidth(), dibOL->getHeight(), dibOL->getStride());

        gint32 olSize=font->getOutlineSize();
        guint8* pS=GX_CAST_R(guint8*, dib->getDataPtr());
        guint8* pD=GX_CAST_R(guint8*, dibTo->getDataPtr(olSize, olSize));
        for (gint i=0; i<dib->getHeight(); i++) {
            GX::gmemcpy(pD, pS, dib->getStride());
            pS+=dib->getStride();
            pD+=dibTo->getStride();
        }
        m_Tex2D=GTexture2D::alloc();
        m_Tex2D->create(dibTo, NULL);
        m_OLTex2D=GTexture2D::alloc();
        m_OLTex2D->create(dibOL, NULL);
    }
}

GBuffer* GTex2DFont::Glyph::getBuffer()
{
    if (!m_Buffer && !isBlank()) {
        render();
    }
    return m_Buffer;
}
GTexture2D* GTex2DFont::Glyph::getTexture()
{
    if (!m_Buffer && !isBlank()) {
        render();
    }
    return m_Tex2D;
}
GTexture2D* GTex2DFont::Glyph::getOLTexture()
{
    if (!m_Buffer && !isBlank()) {
        render();
    }
    return m_OLTex2D;
}


#define M_GLYPH_CACHE_COUNT 256


GX_GOBJECT_IMPLEMENT(GTex2DFont, GFont);

GTex2DFont::GTex2DFont()
{
    m_FTFont=NULL;
    m_Density=1.0f;
}

GTex2DFont::~GTex2DFont()
{
    GO::release(m_FTFont);
}

void GTex2DFont::create(GFTFont* ftFont,float density)
{
    GX_OBJECT_SET(m_FTFont, ftFont);
    m_Density=density;
    if (m_Density<=0.0f) {
        m_Density=1.0f;
    }
    GFont::create(ftFont->getSize());
}

float GTex2DFont::getDensity() const {
    return m_Density;
}

gint32 GTex2DFont::getScaleX()
{
    return m_FTFont->getScaleX();
}
gint32 GTex2DFont::getScaleY()
{
    return m_FTFont->getScaleY();
}
gint32 GTex2DFont::getHeight()
{
    return m_FTFont->getHeight();
}
gint32 GTex2DFont::getAscender()
{
    return m_FTFont->getAscender();
}
gint32 GTex2DFont::getDescender()
{
    return m_FTFont->getDescender();
}
gint32 GTex2DFont::getAdvanceH(guint32 index)
{
    return m_FTFont->getAdvanceH(index);
}
gint32 GTex2DFont::getAdvanceV(guint32 index)
{
    return m_FTFont->getAdvanceV(index);
}
bool GTex2DFont::hasKerning()
{
    return m_FTFont->hasKerning();
}
gint32 GTex2DFont::getKerningX(guint32 index,guint32 next)
{
    return m_FTFont->getKerningX(index, next);
}
bool GTex2DFont::hasOutline()
{
    return m_FTFont->hasOutline();
}
gint32 GTex2DFont::getOutlineSize()
{
    return m_FTFont->getOutlineSize();
}
guint32 GTex2DFont::getIndex(guint32 code)
{
    return m_FTFont->getIndex(code);
}
guint32 GTex2DFont::getVariantIndex(guint32 code,guint32 variation_selector)
{
    return m_FTFont->getVariantIndex(code, variation_selector);
}
guint32 GTex2DFont::getGlyphCount()
{
    return m_FTFont->getGlyphCount();
}
GFont::Glyph* GTex2DFont::getGlyph(guint32 index)
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
    
    GFTFont::Glyph* ftGlyph=GX_CAST_R(GFTFont::Glyph*, m_FTFont->getGlyph(index));
    
    if (ftGlyph) {
        Glyph* res=Glyph::alloc();
        res->load(this, ftGlyph, index);
        res->addUseNumber(1);
        
        if (m_GlyphCache.getCount()>M_GLYPH_CACHE_COUNT) {
            m_GlyphCache.removeLast(M_GLYPH_CACHE_COUNT/2);
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
        return res;
    }
    return NULL;
}
bool GTex2DFont::getGlyphName(guint32 index, char* name, guint32 size)
{
    return m_FTFont->getGlyphName(index,name,size);
}
bool GTex2DFont::getGlyphNameIndex(guint32* idxOut, const char *name, gint32 len)
{
    return m_FTFont->getGlyphNameIndex(idxOut, name, len);
}


