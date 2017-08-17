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

//尺寸都是26.6
class GFont : public GObject
{
	friend class GTypist;
	GX_VIRTUAL_GOBJECT(GFont);
public:
    class Glyph : public GObject {
        GX_VIRTUAL_GOBJECT(Glyph);
    public:
        guint32 getIndex() {
            return m_Index;
        }
        bool isBlank() {
            return getWidth()<=0 || getHeight()<=0;
        }
    public:
		virtual gint32 getWidth() = 0;
		virtual gint32 getHeight() = 0;
        virtual gint32 getHoriBearingX()=0;
        virtual gint32 getHoriBearingY()=0;
        virtual gint32 getVertBearingX()=0;
        virtual gint32 getVertBearingY()=0;
        virtual gint32 getOutlineSize()=0;
		virtual guint32 getOutlinePointCount() = 0;
		virtual gint32 getOutlinePointX(guint32 index) = 0;
		virtual gint32 getOutlinePointY(guint32 index) = 0;
        
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
protected:
	void create(gint32 size);
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
	virtual bool hasOutline()=0;
	virtual gint32 getOutlineSize()=0;
public:
    virtual guint32 getIndex(guint32 code)=0;
    virtual guint32 getVariantIndex(guint32 code,guint32 variation_selector)=0;
    virtual guint32 getGlyphCount()=0;
    virtual Glyph* getGlyph(guint32 index)=0;
	virtual bool getGlyphName(guint32 index, char* name, guint32 size)=0;
	virtual bool getGlyphNameIndex(guint32* idxOut, const char *name, gint32 len)=0;
public:
    inline gint32 getSize() {
        return m_Size;
    }
protected:
	void* getHBFont() {
		return m_HBFont;
	}
private:
    gint32 m_Size;
	void*  m_HBFont;
};

// Up can't include other h file
#include "GXGObjectUD.h"

#endif /* GFont_h */
