//
//  GTypist.cpp
//  GX
//
//  Created by GuGengxin.
//  Copyright by gxengine.com
//

#include "GTypist.h"

#if __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#pragma clang diagnostic ignored "-Wshorten-64-to-32"
#endif
#include <hb.h>
#if __clang__
#pragma clang diagnostic pop
#endif

#include "GXGObject.h"


GTypist::Paper::Paper()
{
    
}

GTypist::Paper::~Paper()
{
    
}


GX_GOBJECT_IMPLEMENT(GTypist::Word, GObject);

GTypist::Word::Word()
{
    m_String=NULL;
    m_Start=0;
    m_Length=0;
    m_HBBuffer=NULL;
}

GTypist::Word::~Word()
{
    if (m_HBBuffer) {
        hb_buffer_destroy(GX_CAST_R(hb_buffer_t*, m_HBBuffer));
    }
    GO::release(m_String);
}

void GTypist::Word::create(GString* str, gint start, gint len, GFont* font)
{
    if (len<0) {
        len=str->getLength()-start;
    }
    GX_OBJECT_SET(m_String, str);
    m_Start=GX_CAST_S(guint32, start);
    m_Length=GX_CAST_S(guint32, len);
    
    
    hb_font_t* hb_font = GX_CAST_R(hb_font_t*, font->getHBFont());
    
    hb_buffer_t *hb_buffer;
    hb_buffer = hb_buffer_create();
    hb_buffer_add_utf16(hb_buffer, str->utf16String()+start, (int)len, 0, -1);
    hb_buffer_guess_segment_properties(hb_buffer);
    hb_buffer_set_direction(hb_buffer, HB_DIRECTION_LTR);
    
    hb_shape(hb_font, hb_buffer, NULL, 0);
    
    unsigned int count = hb_buffer_get_length(hb_buffer);
    hb_glyph_position_t *pos = hb_buffer_get_glyph_positions(hb_buffer, NULL);
    
    m_Frame.set(0, 0, 0, font->getHeight());
    for (unsigned int i = 0; i < count; i++)
    {
        m_Frame.size.width+=pos[i].x_advance / 64.0f;
    }
    
    if (m_HBBuffer) {
        hb_buffer_destroy(GX_CAST_R(hb_buffer_t*, m_HBBuffer));
    }
    m_HBBuffer = hb_buffer;
}

void* GTypist::Word::getHBInfo()
{
    return hb_buffer_get_glyph_infos (GX_CAST_R(hb_buffer_t*, m_HBBuffer), NULL);
}
void* GTypist::Word::getHBPosition()
{
    return hb_buffer_get_glyph_positions (GX_CAST_R(hb_buffer_t*, m_HBBuffer), NULL);
}

gint GTypist::Word::getLength()
{
    return GX_CAST_S(gint, m_Length);
}
void GTypist::Word::setX(float v)
{
    m_Frame.origin.x=v;
}
float GTypist::Word::getX() const
{
    return m_Frame.origin.x;
}
void GTypist::Word::setY(float v)
{
    m_Frame.origin.y=v;
}
float GTypist::Word::getY() const
{
    return m_Frame.origin.y;
}
float GTypist::Word::getWidth() const
{
    return m_Frame.size.width;
}
float GTypist::Word::getHeight() const
{
    return m_Frame.size.height;
}


GX_GOBJECT_IMPLEMENT(GTypist::Paint, GObject);

GTypist::Paint::Paint()
{
    m_Color.set(0xFF, 0xFF, 0xFF, 0xFF);
    m_OLColor.set(0, 0, 0, 0xFF);
    m_BlendMode=BlendModeDefault;
}

GTypist::Paint::~Paint()
{
    
}



#define M_HB_BUF() GX_CAST_R(hb_buffer_t*,m_HBBuffer)

GX_GOBJECT_IMPLEMENT(GTypist, GObject);

GTypist::GTypist()
{
    m_String=NULL;
	m_Font = NULL;
}

GTypist::~GTypist()
{
	GO::release(m_Font);
    GO::release(m_String);
}

void GTypist::setSingleLine(GString * str, GFont * font)
{
    GX_OBJECT_SET(m_String, str);
    GX_OBJECT_SET(m_Font, font);
    m_Words.removeAll();
    m_Size.set(0.0f, 0.0f);
    
    
    Word* wd=Word::alloc();
    wd->create(str, 0, -1, font);
    
    wd->setX(0.0f);
    wd->setY(0.0f);
    m_Size.width+=wd->getWidth();
    m_Size.height=wd->getHeight();
    
    m_Words.add(wd);
    GO::release(wd);
}

bool GTypist::print(Paper* paper,GPointF pos,const Paint* paint)
{
    if (!paper->isFontAvailable(m_Font)) {
        return false;
    }
    
    for (gint i=0; i<m_Words.getCount(); i++) {
        Word* wd=m_Words.get(i);
        
        hb_glyph_info_t *infoHB = GX_CAST_R(hb_glyph_info_t*, wd->getHBInfo());
        hb_glyph_position_t *posHB = GX_CAST_R(hb_glyph_position_t*, wd->getHBPosition());
        
        GPointF curPos(pos.x+wd->getX(),pos.y+wd->getY()+m_Font->getAscender()/64.0f);
        for (gint j=0; j<wd->getLength(); j++) {
            GFont::Glyph* glyph=m_Font->getGlyph(infoHB[j].codepoint);
            
            printf("%f %f\n",posHB[j].x_offset/64.0f,posHB[j].y_offset/64.0f);
            
            paper->printGlyph(glyph, GPointF::make(curPos.x+posHB[j].x_offset/64.0f, curPos.y+posHB[j].y_offset/64.0f),paint);
            
            curPos.x+=posHB[j].x_advance/64.0f;
            curPos.y+=posHB[j].y_advance/64.0f;
        }
    }
    
    return true;
}
