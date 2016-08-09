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
#include "GData.h"


#include "GXGObject.h"
// Down can't include other h file
class GReader;

class GDib : public GObject
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
    inline GX::PixelFormat getPixelFormat() {
        return m_PixelFormat;
    }
    void setPixelFormat(GX::PixelFormat v) {
        m_PixelFormat=v;
    }
    inline gint32 getWidth() {
        return m_Width;
    }
    void setWidth(gint32 v) {
        m_Width=v;
    }
    inline gint32 getHeight() {
        return m_Height;
    }
    void setHeight(gint32 v) {
        m_Height=v;
    }
    inline gint32 getStride() {
        return m_Stride;
    }
    void setStride(gint32 v) {
        m_Stride=v;
    }
    
    bool changeDataBytes(guint bytes);
    inline void* getDataPtr() {
        return m_Data.getPtr();
    }

private:
    GX::PixelFormat m_PixelFormat;
    gint32          m_Width;
    gint32          m_Height;
    gint32          m_Stride;
    GData           m_Data;
};

// Up can't include other h file
#include "GXGObjectUD.h"

#endif /* GDib_h */
