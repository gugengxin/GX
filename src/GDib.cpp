//
//  GDib.cpp
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#include "GDib.h"
//Down include other h file
#include "GRBReader.h"
#include "GPng.h"
#include "GJpeg.h"
//Up include other h file
#include "GXGObject.h"

static bool (*g_CheckFuns[])(GReader*)={
    GPng::check,
    GJpeg::check,
};
static GDib* (*g_ReadFuns[])(GReader*)={
    GPng::read,
    GJpeg::read,
};

//reader必须可以rollback
static GDib::FileType _CheckFileType(GReader* reader,GDib::FileType suggestFT)
{
    gint bytesStart=reader->getBytes();
    bool bTF=g_CheckFuns[suggestFT](reader);
    reader->rollback(reader->getBytes()-bytesStart);
    if (bTF) {
        return suggestFT;
    }
    
    for (gint i=0; i<sizeof(g_CheckFuns)/sizeof(g_CheckFuns[0]); i++) {
        if (i!=suggestFT) {
            bTF=g_CheckFuns[i](reader);
            reader->rollback(reader->getBytes()-bytesStart);
            if (bTF) {
                return (GDib::FileType)i;
            }
        }
    }
    return GDib::Unsupport;
}


GX_GOBJECT_IMPLEMENT(GDib, GObject);

GDib* GDib::load(GReader* reader,FileType suggestFT)
{
    FileType ft=Unsupport;
    if (reader->canRollback()) {
        ft=_CheckFileType(reader,suggestFT);
        if (ft!=Unsupport) {
            return g_ReadFuns[ft](reader);
        }
    }
    else {
        GRBReader rb;
        if(rb.open(reader)) {
            ft=_CheckFileType(&rb, suggestFT);
            if (ft!=Unsupport) {
                rb.closeRollback();
                return g_ReadFuns[ft](reader);
            }
        }
    }
    
    return NULL;
}

GDib::GDib()
{
    m_PixelFormat=GX::PixelFormatUnknown;
    m_Width=0;
    m_Height=0;
    m_Stride=0;
}

GDib::~GDib()
{
    
}

bool GDib::changeDataBytes(guint bytes)
{
    return m_Data.changeBytes(bytes);
}


