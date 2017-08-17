//
//  GTypist.h
//  GX
//
//  Created by GuGengxin.
//  Copyright by gxengine.com
//

#ifndef GTypist_h
#define GTypist_h

#include "GXPrefix.h"
#include "GDataArray.h"
#include "GString.h"
#include "GFont.h"
#include "GGeometry.h"
#include "GColor.h"


#include "GXGObject.h"

class GTypist : public GObject {
	GX_GOBJECT(GTypist);
public:
    class Paint;
    
    class Paper {
        friend class GTypist;
    public:
        Paper();
        virtual ~Paper();
    protected:
        typedef void (*PrintGlyphSelector)(Paper* paper,GFont* font,GFont::Glyph* glyph,GPointF pos,GPointF offset,const Paint* paint);
        virtual bool isFlipped()=0;
        virtual PrintGlyphSelector printCheck(GFont* font)=0;
        virtual void printBegin(GFont* font,GPointF pos)=0;
        virtual void printEnd()=0;
        
    };
    
    class Word : public GObject {
        friend class GTypist;
        GX_GOBJECT(Word);
    private:
        void create(GString* str, gint start, gint len, GFont* font);
        void* getHBInfo();
        void* getHBPosition();
    public:
        gint getLength();
        void setX(float v);
        float getX() const;
        void setY(float v);
        float getY() const;
        float getWidth() const;
        float getHeight() const;
    private:
        GString* m_String;
        guint32 m_Start;
        guint32 m_Length;
        void* m_HBBuffer;
        GRectF m_Frame;
    };
    
    enum BlendMode {
        BlendModeDefault,
        BlendModeSaD1sa,
    };
    
    class Paint : public GObject {
        GX_GOBJECT(Paint);
    public:
        const GColor4& getColor() const {
            return m_Color;
        }
        void setColor(guint8 r,guint8 g,guint8 b,guint8 a) {
            m_Color.set(r, g, b, a);
        }
        const GColor4& getOutlineColor() const {
            return m_OLColor;
        }
        void setOutlineColor(guint8 r,guint8 g,guint8 b,guint8 a) {
            m_OLColor.set(r, g, b, a);
        }
        BlendMode getBlendMode() const {
            return m_BlendMode;
        }
        void setBlendMode(BlendMode v) {
            m_BlendMode=v;
        }
    private:
        GColor4     m_Color;
        GColor4     m_OLColor;
        BlendMode   m_BlendMode;
    };
public:
	void setSingleLine(GString* str, GFont* font);
public:
    bool print(Paper* paper,GPointF pos,const Paint* paint);
private:
    
private:
    GString* m_String;
	GFont*	m_Font;
    GArray<Word> m_Words;
	GSizeF	m_Size;
};

#include "GXGObjectUD.h"

#endif /* GTypist_h */
