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
        guint32 getCode() {
            return m_Code;
        }
        guint32 getIndex() {
            return m_Index;
        }
        virtual gint32 getAdvanceX()=0;
        virtual GRectN getCBox()=0;
        
    protected:
        void setCode(guint32 v) {
            m_Code=v;
        }
        void setIndex(guint32 v) {
            m_Index=v;
        }
    private:
        guint32 m_Code;
        guint32 m_Index;
    };
public:
    virtual gint32 getHeight()=0;
    virtual gint32 getAscender()=0;
    virtual bool hasKerning()=0;
    virtual gint32 getKerningX(guint32 index,guint32 next)=0;
    virtual guint32 getGlyphCount()=0;
    virtual Glyph* getGlyph(guint32 code)=0;
    
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
