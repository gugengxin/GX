//
//  GDib.h
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#ifndef GDib_h
#define GDib_h

#include "GXPrefix.h"
#include "GObject.h"
#include "GXPixel.h"
#include "GXData.h"
#include "GTypist.h"


#include "GXGObject.h"
// Down can't include other h file
class GReader;

class GDib : public GObject, public GTypist::Paper
{
	GX_GOBJECT(GDib);
public:
    typedef enum _FileType {
        Unsupport=-1,
        PNG=0,
        JPEG,
    } FileType;
    static GDib* load(GReader* reader,FileType suggestFT);
    
	static GDib* convert(GDib* dib, GX::PixelFormat pfTo);
public:
    inline GX::PixelFormat getPixelFormat() const {
        return m_PixelFormat;
    }
    void setPixelFormat(GX::PixelFormat v) {
        m_PixelFormat=v;
    }
    inline gint32 getWidth() const {
        return m_Width;
    }
    void setWidth(gint32 v) {
        m_Width=v;
    }
    inline gint32 getHeight() const {
        return m_Height;
    }
    void setHeight(gint32 v) {
        m_Height=v;
    }
    inline gint32 getStride() const {
        return m_Stride;
    }
    void setStride(gint32 v) {
        m_Stride=v;
    }
    inline void* getDataPtr() const {
        return m_Data.getPtr();
    }
    inline void* getDataPtr(gint32 x,gint32 y) {
        return GX_CAST_R(guint8*, m_Data.getPtr())+y*m_Stride+x*GX_PIXEL_FORMAT_SIZE(m_PixelFormat);
    }
    bool changeDataBytes(guint bytes);
    void setStaticData(const void* data, guint bytes);
    
    void changeData(GX::PixelFormat pf,gint32 w,gint32 h,gint32 stride);
    void changeData(GX::PixelFormat pf,gint32 w,gint32 h);
    
protected:
    virtual GTypist::Paper::PrintGlyphSelector printCheck(GFont* font);
    virtual void printBegin(GPointF pos);
    void printFTFontGlyph(GFont::Glyph* glyph,GPointF pos,GPointF offset,const GTypist::Paint* paint);
    virtual void printEnd();
private:
    GX::PixelFormat m_PixelFormat;
    gint32          m_Width;
    gint32          m_Height;
    gint32          m_Stride;
    GX::Data        m_Data;
};

// Up can't include other h file
#include "GXGObjectUD.h"

#endif /* GDib_h */
