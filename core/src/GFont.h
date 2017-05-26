//
//  GFont.h
//  GX
//
//  Created by GuGengxin.
//  Copyright by gxengine.com
//

#ifndef GFont_h
#define GFont_h

#include "GXPrefix.h"
#include "GObject.h"
#include "GGeometry.h"


#include "GXGObject.h"
// Down can't include other h file

class GFont : public GObject
{
	GX_VIRTUAL_GOBJECT(GFont);
public:
    class Glyph : public GObject {
        GX_VIRTUAL_GOBJECT(Glyph);
    public:
        guint32 getIndex() {
            return m_Index;
        }
    public:
		virtual gint32 getWidth() = 0;
		virtual gint32 getHeight() = 0;
        virtual gint32 getHoriBearingX()=0;
        virtual gint32 getHoriBearingY()=0;
        virtual gint32 getVertBearingX()=0;
        virtual gint32 getVertBearingY()=0;
        
    protected:
        void setIndex(guint32 v) {
            m_Index=v;
        }
        inline GFont* getFont() const {
            return m_Font;
        }
        inline void setFont(GFont* v) {
            m_Font=v;
        }
    private:
        GFont*  m_Font;
        guint32 m_Index;
    };
public:
    virtual gint32 getScaleX()=0;
    virtual gint32 getScaleY()=0;
    virtual gint32 getHeight()=0;
    virtual gint32 getAscender()=0;
    virtual gint32 getDescender()=0;
    virtual gint32 getAdvanceH(guint32 index)=0;
    virtual gint32 getAdvanceV(guint32 index)=0;
    virtual bool hasKerning()=0;
    virtual gint32 getKerningX(guint32 index,guint32 next)=0;
	virtual bool hasOutline() = 0;
	virtual gint32 getOutlineSize() = 0;
public:
    virtual guint32 getIndex(guint32 code)=0;
    virtual guint32 getVariantIndex(guint32 code,guint32 variation_selector)=0;
    virtual guint32 getGlyphCount()=0;
    virtual Glyph* getGlyph(guint32 index)=0;
    
    inline gint32 getSize() {
        return m_Size;
    }
protected:
    inline void setSize(gint32 v) {
        m_Size=v;
    }
private:
    gint32 m_Size;
};

// Up can't include other h file
#include "GXGObjectUD.h"

#endif /* GFont_h */
