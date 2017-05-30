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



#include "GXGObject.h"

class GTypist : public GObject {
	GX_GOBJECT(GTypist);
public:
    class Paper {
    public:
        Paper();
        virtual ~Paper();
    };
    
    class Word : public GObject {
        friend class GTypist;
        GX_GOBJECT(Word);
    private:
        void create(GString* str, gint start, gint len, GFont* font);
    public:
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
public:
	void setSingleLine(GString* str, GFont* font);
private:
    
private:
    GString* m_String;
	GFont*	m_Font;
    GArray<Word> m_Words;
	GSizeF	m_Size;
};

#include "GXGObjectUD.h"

#endif /* GTypist_h */
