//
//  GFT.h
//  GX
//
//  Created by GuGengxin.
//  Copyright by gxengine.com
//

#ifndef GFT_h
#define GFT_h

#include "GXPrefix.h"
#include "GObject.h"
#include "GData.h"
#include "GArray.h"
#include "GGeometry.h"
#include "GArray.h"

#include "GXGObject.h"
// Down can't include other h file

class GFT
{
public:
    class Glyph : public GObject {
        GX_GOBJECT(Glyph);
    public:
        
    private:
        guint32  m_Code;
        guint32  m_UseNumber;
        guint32  m_Index;
        void*    m_Glyph;
        void*    m_OLGlyph;
        gint32   m_OLSize;
        void*    m_OLData;
        GRectN   m_CBox;
    };
    
    
    class Font : public GObject {
        GX_GOBJECT(Font);
    public:
        inline gint32 getSize() const {
            return m_Size;
        }
    private:
        GData*  m_Data;
        void*   m_Face;
        void*   m_Stroker;
        gint32  m_Size;
        gint32  m_OLSize;
        GArray<Glyph> m_GlyphCache;
    };
    
};

// Up can't include other h file
#include "GXGObjectUD.h"

#endif /* GFT_h */
