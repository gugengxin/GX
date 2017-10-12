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
#include "GFTFont.h"
//Up include other h file
#include "GXGObject.h"

static bool (*g_CheckFuns[])(GReader*)={
    GPng::checkHeader,
    GJpeg::checkHeader,
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
    
    for (gint i=0; i<(gint)(sizeof(g_CheckFuns)/sizeof(g_CheckFuns[0])); i++) {
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
                return g_ReadFuns[ft](&rb);
            }
        }
    }
    
    return NULL;
}

#define M_CONVERT_START(PFFrom,PF) \
case PF:\
{\
	GDib* res = GDib::alloc();\
	if (res->changeDataBytes(dib->getWidth()*dib->getHeight()*GX_PIXEL_FORMAT_SIZE(PF))) {\
		res->setPixelFormat(PF);\
		res->setWidth(dib->getWidth());\
		res->setHeight(dib->getHeight());\
		res->setStride(res->getWidth()*GX_PIXEL_FORMAT_SIZE(PF));\
		for (gint32 i = 0; i<dib->getHeight(); i++) {\
			guint8* pS = ((guint8*)dib->getDataPtr()) + i*dib->getStride();\
			guint8* pD = ((guint8*)res->getDataPtr()) + i*res->getStride();\
			for (gint32 j = 0; j < dib->getWidth(); j++) {

#define M_CONVERT_END__(PFFrom,PF) \
				pS+=GX_PIXEL_FORMAT_SIZE(PFFrom);\
				pD+=GX_PIXEL_FORMAT_SIZE(PF);\
			}\
		}\
		GO::autorelease(res);\
		return res;\
	}\
	else {\
		GO::release(res);\
	}\
}\
break


GDib* GDib::convert(GDib* dib, GX::PixelFormat pfTo)
{
    if (dib->getPixelFormat() == pfTo) {
        return dib;
    }
    switch (dib->getPixelFormat()) {
        case GX::PixelFormatA8:
        {
            switch (pfTo)
            {
                    M_CONVERT_START(GX::PixelFormatA8,GX::PixelFormatRGB565);
                    (*(guint16*)pD) = (((*pS) & 0xF8) << 8) | (((*pS) & 0xFC) << 3) | ((*pS) >> 3);
                    M_CONVERT_END__(GX::PixelFormatA8, GX::PixelFormatRGB565);
                    
                    M_CONVERT_START(GX::PixelFormatA8, GX::PixelFormatBGR565);
                    (*(guint16*)pD) = (((*pS) & 0xF8) << 8) | (((*pS) & 0xFC) << 3) | ((*pS) >> 3);
                    M_CONVERT_END__(GX::PixelFormatA8, GX::PixelFormatBGR565);
                    
                    M_CONVERT_START(GX::PixelFormatA8, GX::PixelFormatRGBA4444);
                    (*(guint16*)pD) = (0xFFF0 | ((*pS) >> 4));
                    M_CONVERT_END__(GX::PixelFormatA8, GX::PixelFormatRGBA4444);
                    
                    M_CONVERT_START(GX::PixelFormatA8, GX::PixelFormatBGRA4444);
                    (*(guint16*)pD) = (0xFFF0 | ((*pS) >> 4));
                    M_CONVERT_END__(GX::PixelFormatA8, GX::PixelFormatBGRA4444);
                    
                    M_CONVERT_START(GX::PixelFormatA8, GX::PixelFormatRGBA5551);
                    (*(guint16*)pD) = (0xFFFE | ((*pS) >> 7));
                    M_CONVERT_END__(GX::PixelFormatA8, GX::PixelFormatRGBA5551);
                    
                    M_CONVERT_START(GX::PixelFormatA8, GX::PixelFormatBGRA5551);
                    (*(guint16*)pD) = (0xFFFE | ((*pS) >> 7));
                    M_CONVERT_END__(GX::PixelFormatA8, GX::PixelFormatBGRA5551);
                    
                    M_CONVERT_START(GX::PixelFormatA8, GX::PixelFormatRGB888);
                    pD[0] = (*pS);
                    pD[1] = (*pS);
                    pD[2] = (*pS);
                    M_CONVERT_END__(GX::PixelFormatA8, GX::PixelFormatRGB888);
                    
                    M_CONVERT_START(GX::PixelFormatA8, GX::PixelFormatRGBA8888);
                    (*(guint32*)pD) = 0xFFFFFF | ((*pS) << 24);
                    M_CONVERT_END__(GX::PixelFormatA8, GX::PixelFormatRGBA8888);
                    
                    M_CONVERT_START(GX::PixelFormatA8, GX::PixelFormatBGRA8888);
                    (*(guint32*)pD) = 0xFFFFFF | ((*pS) << 24);
                    M_CONVERT_END__(GX::PixelFormatA8, GX::PixelFormatBGRA8888);
                default:
                    break;
            }
        }
            break;
        case GX::PixelFormatRGB565:
        {
            switch (pfTo)
            {
                    M_CONVERT_START(GX::PixelFormatRGB565, GX::PixelFormatA8);
                    (*pD)=0xFF;
                    M_CONVERT_END__(GX::PixelFormatRGB565, GX::PixelFormatA8);
                    
                    M_CONVERT_START(GX::PixelFormatRGB565, GX::PixelFormatBGR565);
                    (*(guint16*)pD)=(((*(guint16*)pS)&0xF800)>>11) | ((*(guint16*)pS)&0x7E0) | (((*(guint16*)pS)&0x1F)<<11);
                    M_CONVERT_END__(GX::PixelFormatRGB565, GX::PixelFormatBGR565);
                    
                    M_CONVERT_START(GX::PixelFormatRGB565, GX::PixelFormatRGBA4444);
                    (*(guint16*)pD)=(((*(guint16*)pS)&0xF000) | (((*(guint16*)pS)&0x780)<<1) | (((*(guint16*)pS)&0x1E)<<3) | 0xF);
                    M_CONVERT_END__(GX::PixelFormatRGB565, GX::PixelFormatRGBA4444);
                    
                    M_CONVERT_START(GX::PixelFormatRGB565, GX::PixelFormatBGRA4444);
                    (*(guint16*)pD)=((((*(guint16*)pS)&0xF000)>>8) | (((*(guint16*)pS)&0x780)<<1) | (((*(guint16*)pS)&0x1E)<<11) | 0xF);
                    M_CONVERT_END__(GX::PixelFormatRGB565, GX::PixelFormatBGRA4444);
                    
                    M_CONVERT_START(GX::PixelFormatRGB565, GX::PixelFormatRGBA5551);
                    (*(guint16*)pD)=(((*(guint16*)pS)&0xFFC0) | (((*(guint16*)pS)&0x1F)<<1) | 0x1);
                    M_CONVERT_END__(GX::PixelFormatRGB565, GX::PixelFormatRGBA5551);
                    
                    M_CONVERT_START(GX::PixelFormatRGB565, GX::PixelFormatBGRA5551);
                    (*(guint16*)pD)=(((*(guint16*)pS)&0xF800)>>10) | ((*(guint16*)pS)&0x7C0) | (((*(guint16*)pS)&0x1F)<<11) | 0x1;
                    M_CONVERT_END__(GX::PixelFormatRGB565, GX::PixelFormatBGRA5551);
                    
                    M_CONVERT_START(GX::PixelFormatRGB565, GX::PixelFormatRGB888);
                    pD[0]=(((*(guint16*)pS)>>11)&0x1F)*0xFF/0x1F;
                    pD[1]=(((*(guint16*)pS)>>5)&0x3F)*0xFF/0x3F;
                    pD[2]=(((*(guint16*)pS)>>0)&0x1F)*0xFF/0x1F;
                    M_CONVERT_END__(GX::PixelFormatRGB565, GX::PixelFormatRGB888);
                    
                    M_CONVERT_START(GX::PixelFormatRGB565, GX::PixelFormatRGBA8888);
                    (*(guint32*)pD)=0xFF000000 |
                    ((((*(guint16*)pS)>>11)&0x1F)*0xFF/0x1F) |
                    (((((*(guint16*)pS)>>5)&0x3F)*0xFF/0x3F)<<8) |
                    ((((*(guint16*)pS)&0x1F)*0xFF/0x1F)<<16);
                    M_CONVERT_END__(GX::PixelFormatRGB565, GX::PixelFormatRGBA8888);
                    
                    M_CONVERT_START(GX::PixelFormatRGB565, GX::PixelFormatBGRA8888);
                    (*(guint32*)pD)=0xFF000000 |
                    (((((*(guint16*)pS)>>11)&0x1F)*0xFF/0x1F)<<16) |
                    (((((*(guint16*)pS)>>5)&0x3F)*0xFF/0x3F)<<8) |
                    (((*(guint16*)pS)&0x1F)*0xFF/0x1F);
                    M_CONVERT_END__(GX::PixelFormatRGB565, GX::PixelFormatBGRA8888);
                default:
                    break;
            }
        }
            break;
        case GX::PixelFormatBGR565:
        {
            switch (pfTo)
            {
                    M_CONVERT_START(GX::PixelFormatBGR565, GX::PixelFormatA8);
                    (*pD)=0xFF;
                    M_CONVERT_END__(GX::PixelFormatBGR565, GX::PixelFormatA8);
                    
                    M_CONVERT_START(GX::PixelFormatBGR565, GX::PixelFormatRGB565);
                    (*(guint16*)pD)=(((*(guint16*)pS)&0xF800)>>11) | ((*(guint16*)pS)&0x7E0) | (((*(guint16*)pS)&0x1F)<<11);
                    M_CONVERT_END__(GX::PixelFormatBGR565, GX::PixelFormatRGB565);
                    
                    M_CONVERT_START(GX::PixelFormatBGR565, GX::PixelFormatRGBA4444);
                    (*(guint16*)pD)=((((*(guint16*)pS)&0xF000)>>8) | (((*(guint16*)pS)&0x780)<<1) | (((*(guint16*)pS)&0x1E)<<11) | 0xF);
                    M_CONVERT_END__(GX::PixelFormatBGR565, GX::PixelFormatRGBA4444);
                    
                    M_CONVERT_START(GX::PixelFormatBGR565, GX::PixelFormatBGRA4444);
                    (*(guint16*)pD)=(((*(guint16*)pS)&0xF000) | (((*(guint16*)pS)&0x780)<<1) | (((*(guint16*)pS)&0x1E)<<3) | 0xF);
                    M_CONVERT_END__(GX::PixelFormatBGR565, GX::PixelFormatBGRA4444);
                    
                    M_CONVERT_START(GX::PixelFormatBGR565, GX::PixelFormatRGBA5551);
                    (*(guint16*)pD)=(((*(guint16*)pS)&0xF800)>>10) | ((*(guint16*)pS)&0x7C0) | (((*(guint16*)pS)&0x1F)<<11) | 0x1;
                    M_CONVERT_END__(GX::PixelFormatBGR565, GX::PixelFormatRGBA5551);
                    
                    M_CONVERT_START(GX::PixelFormatBGR565, GX::PixelFormatBGRA5551);
                    (*(guint16*)pD)=(((*(guint16*)pS)&0xFFC0) | (((*(guint16*)pS)&0x1F)<<1) | 0x1);
                    M_CONVERT_END__(GX::PixelFormatBGR565, GX::PixelFormatBGRA5551);
                    
                    M_CONVERT_START(GX::PixelFormatBGR565, GX::PixelFormatRGB888);
                    pD[0]=(((*(guint16*)pS)>>0)&0x1F)*0xFF/0x1F;
                    pD[1]=(((*(guint16*)pS)>>5)&0x3F)*0xFF/0x3F;
                    pD[2]=(((*(guint16*)pS)>>11)&0x1F)*0xFF/0x1F;
                    M_CONVERT_END__(GX::PixelFormatBGR565, GX::PixelFormatRGB888);
                    
                    M_CONVERT_START(GX::PixelFormatBGR565, GX::PixelFormatRGBA8888);
                    (*(guint32*)pD)=0xFF000000 |
                    (((((*(guint16*)pS)>>11)&0x1F)*0xFF/0x1F)<<16) |
                    (((((*(guint16*)pS)>>5)&0x3F)*0xFF/0x3F)<<8) |
                    (((*(guint16*)pS)&0x1F)*0xFF/0x1F);
                    M_CONVERT_END__(GX::PixelFormatBGR565, GX::PixelFormatRGBA8888);
                    M_CONVERT_START(GX::PixelFormatBGR565, GX::PixelFormatBGRA8888);
                    (*(guint32*)pD)=0xFF000000 |
                    ((((*(guint16*)pS)>>11)&0x1F)*0xFF/0x1F) |
                    (((((*(guint16*)pS)>>5)&0x3F)*0xFF/0x3F)<<8) |
                    ((((*(guint16*)pS)&0x1F)*0xFF/0x1F)<<16);
                    M_CONVERT_END__(GX::PixelFormatBGR565, GX::PixelFormatBGRA8888);
                default:
                    break;
            }
        }
            break;
        case GX::PixelFormatRGBA4444:
        {
            switch (pfTo)
            {
                    M_CONVERT_START(GX::PixelFormatRGBA4444, GX::PixelFormatA8);
                    (*pD)=((*(guint16*)pS)&0xF)*0xFF/0xF;
                    M_CONVERT_END__(GX::PixelFormatRGBA4444, GX::PixelFormatA8);
                    
                    M_CONVERT_START(GX::PixelFormatRGBA4444, GX::PixelFormatRGB565);
                    (*(guint16*)pD)=(((((*(guint16*)pS)>>12)&0xF)*0x1F/0xF)<<11) |
                    (((((*(guint16*)pS)>>8)&0xF)*0x3F/0xF)<<5) |
                    ((((*(guint16*)pS)>>4)&0xF)*0x1F/0xF);
                    M_CONVERT_END__(GX::PixelFormatRGBA4444, GX::PixelFormatRGB565);
                    
                    M_CONVERT_START(GX::PixelFormatRGBA4444, GX::PixelFormatBGR565);
                    (*(guint16*)pD)=((((*(guint16*)pS)>>12)&0xF)*0x1F/0xF) |
                    (((((*(guint16*)pS)>>8)&0xF)*0x3F/0xF)<<5) |
                    (((((*(guint16*)pS)>>4)&0xF)*0x1F/0xF)<<11);
                    M_CONVERT_END__(GX::PixelFormatRGBA4444, GX::PixelFormatBGR565);
                    
                    M_CONVERT_START(GX::PixelFormatRGBA4444, GX::PixelFormatBGRA4444);
                    (*(guint16*)pD)=(((*(guint16*)pS)&0xF000)>>8) | ((*(guint16*)pS)&0xF0F) | (((*(guint16*)pS)&0xF0)<<8);
                    M_CONVERT_END__(GX::PixelFormatRGBA4444, GX::PixelFormatBGRA4444);
                    
                    M_CONVERT_START(GX::PixelFormatRGBA4444, GX::PixelFormatRGBA5551);
                    (*(guint16*)pD) = (((((*(guint16*)pS)>>12)&0xF)*0x1F/0xF)<<11) |
                    (((((*(guint16*)pS)>>8)&0xF)*0x1F/0xF)<<6) |
                    (((((*(guint16*)pS)>>4)&0xF)*0x1F/0xF)<<1) |
                    (((*(guint16*)pS) & 0x8) >> 3);
                    M_CONVERT_END__(GX::PixelFormatRGBA4444, GX::PixelFormatRGBA5551);
                    
                    M_CONVERT_START(GX::PixelFormatRGBA4444, GX::PixelFormatBGRA5551);
                    (*(guint16*)pD) = (((((*(guint16*)pS)>>12)&0xF)*0x1F/0xF)<<1) |
                    (((((*(guint16*)pS)>>8)&0xF)*0x1F/0xF)<<6) |
                    (((((*(guint16*)pS)>>4)&0xF)*0x1F/0xF)<<11) |
                    (((*(guint16*)pS) & 0x8) >> 3);
                    M_CONVERT_END__(GX::PixelFormatRGBA4444, GX::PixelFormatBGRA5551);
                    
                    M_CONVERT_START(GX::PixelFormatRGBA4444, GX::PixelFormatRGB888);
                    pD[0] = ((((*(guint16*)pS)>>12)&0xF)*0xFF/0xF);
                    pD[1] = ((((*(guint16*)pS)>>8)&0xF)*0xFF/0xF);
                    pD[2] = ((((*(guint16*)pS)>>4)&0xF)*0xFF/0xF);
                    M_CONVERT_END__(GX::PixelFormatRGBA4444, GX::PixelFormatRGB888);
                    
                    M_CONVERT_START(GX::PixelFormatRGBA4444, GX::PixelFormatRGBA8888);
                    (*(guint32*)pD) = (((((*(guint16*)pS)>>12)&0xF)*0xFF/0xF)<<0) |
                    (((((*(guint16*)pS)>>8)&0xF)*0xFF/0xF)<<8) |
                    (((((*(guint16*)pS)>>4)&0xF)*0xFF/0xF)<<16) |
                    (((((*(guint16*)pS)>>0)&0xF)*0xFF/0xF)<<24);
                    M_CONVERT_END__(GX::PixelFormatRGBA4444, GX::PixelFormatRGBA8888);
                    
                    M_CONVERT_START(GX::PixelFormatRGBA4444, GX::PixelFormatBGRA8888);
                    (*(guint32*)pD) = (((((*(guint16*)pS)>>12)&0xF)*0xFF/0xF)<<16) |
                    (((((*(guint16*)pS)>>8)&0xF)*0xFF/0xF)<<8) |
                    (((((*(guint16*)pS)>>4)&0xF)*0xFF/0xF)<<0) |
                    (((((*(guint16*)pS)>>0)&0xF)*0xFF/0xF)<<24);
                    M_CONVERT_END__(GX::PixelFormatRGBA4444, GX::PixelFormatBGRA8888);
                default:
                    break;
            }
        }
            break;
        case GX::PixelFormatBGRA4444:
        {
            switch (pfTo)
            {
                    M_CONVERT_START(GX::PixelFormatBGRA4444, GX::PixelFormatA8);
                    (*pD)=((*(guint16*)pS)&0xF)*0xFF/0xF;
                    M_CONVERT_END__(GX::PixelFormatBGRA4444, GX::PixelFormatA8);
                    
                    M_CONVERT_START(GX::PixelFormatBGRA4444, GX::PixelFormatRGB565);
                    (*(guint16*)pD)=((((*(guint16*)pS)>>12)&0xF)*0x1F/0xF) |
                    (((((*(guint16*)pS)>>8)&0xF)*0x3F/0xF)<<5) |
                    (((((*(guint16*)pS)>>4)&0xF)*0x1F/0xF)<<11);
                    M_CONVERT_END__(GX::PixelFormatBGRA4444, GX::PixelFormatRGB565);
                    M_CONVERT_START(GX::PixelFormatBGRA4444, GX::PixelFormatBGR565);
                    (*(guint16*)pD)=(((((*(guint16*)pS)>>12)&0xF)*0x1F/0xF)<<11) |
                    (((((*(guint16*)pS)>>8)&0xF)*0x3F/0xF)<<5) |
                    ((((*(guint16*)pS)>>4)&0xF)*0x1F/0xF);
                    M_CONVERT_END__(GX::PixelFormatBGRA4444, GX::PixelFormatBGR565);
                    
                    M_CONVERT_START(GX::PixelFormatBGRA4444, GX::PixelFormatRGBA4444);
                    (*(guint16*)pD) = (((*(guint16*)pS) & 0xF000) >> 8) | ((*(guint16*)pS) & 0xF0F) | (((*(guint16*)pS) & 0xF0) << 8);
                    M_CONVERT_END__(GX::PixelFormatBGRA4444, GX::PixelFormatRGBA4444);
                    
                    M_CONVERT_START(GX::PixelFormatBGRA4444, GX::PixelFormatRGBA5551);
                    (*(guint16*)pD) = (((((*(guint16*)pS)>>12)&0xF)*0x1F/0xF)<<1) |
                    (((((*(guint16*)pS)>>8)&0xF)*0x1F/0xF)<<6) |
                    (((((*(guint16*)pS)>>4)&0xF)*0x1F/0xF)<<11) |
                    (((*(guint16*)pS) & 0x8) >> 3);
                    M_CONVERT_END__(GX::PixelFormatBGRA4444, GX::PixelFormatRGBA5551);
                    M_CONVERT_START(GX::PixelFormatBGRA4444, GX::PixelFormatBGRA5551);
                    (*(guint16*)pD) = (((((*(guint16*)pS)>>12)&0xF)*0x1F/0xF)<<11) |
                    (((((*(guint16*)pS)>>8)&0xF)*0x1F/0xF)<<6) |
                    (((((*(guint16*)pS)>>4)&0xF)*0x1F/0xF)<<1) |
                    (((*(guint16*)pS) & 0x8) >> 3);
                    M_CONVERT_END__(GX::PixelFormatBGRA4444, GX::PixelFormatBGRA5551);
                    
                    M_CONVERT_START(GX::PixelFormatBGRA4444, GX::PixelFormatRGB888);
                    pD[0] = ((((*(guint16*)pS)>>4)&0xF)*0xFF/0xF);
                    pD[1] = ((((*(guint16*)pS)>>8)&0xF)*0xFF/0xF);
                    pD[2] = ((((*(guint16*)pS)>>12)&0xF)*0xFF/0xF);
                    M_CONVERT_END__(GX::PixelFormatBGRA4444, GX::PixelFormatRGB888);
                    
                    M_CONVERT_START(GX::PixelFormatBGRA4444, GX::PixelFormatRGBA8888);
                    (*(guint32*)pD) = (((((*(guint16*)pS)>>12)&0xF)*0xFF/0xF)<<16) |
                    (((((*(guint16*)pS)>>8)&0xF)*0xFF/0xF)<<8) |
                    (((((*(guint16*)pS)>>4)&0xF)*0xFF/0xF)<<0) |
                    (((((*(guint16*)pS)>>0)&0xF)*0xFF/0xF)<<24);
                    M_CONVERT_END__(GX::PixelFormatBGRA4444, GX::PixelFormatRGBA8888);
                    M_CONVERT_START(GX::PixelFormatBGRA4444, GX::PixelFormatBGRA8888);
                    (*(guint32*)pD) = (((((*(guint16*)pS)>>12)&0xF)*0xFF/0xF)<<0) |
                    (((((*(guint16*)pS)>>8)&0xF)*0xFF/0xF)<<8) |
                    (((((*(guint16*)pS)>>4)&0xF)*0xFF/0xF)<<16) |
                    (((((*(guint16*)pS)>>0)&0xF)*0xFF/0xF)<<24);
                    M_CONVERT_END__(GX::PixelFormatBGRA4444, GX::PixelFormatBGRA8888);
                default:
                    break;
            }
        }
            break;
        case GX::PixelFormatRGBA5551:
        {
            switch (pfTo)
            {
                    M_CONVERT_START(GX::PixelFormatRGBA5551, GX::PixelFormatA8);
                    (*pD)=((*(guint16*)pS)&0x1)*0xFF;
                    M_CONVERT_END__(GX::PixelFormatRGBA5551, GX::PixelFormatA8);
                    
                    M_CONVERT_START(GX::PixelFormatRGBA5551, GX::PixelFormatRGB565);
                    (*(guint16*)pD)=((*(guint16*)pS)&0xF800) | (((((*(guint16*)pS)>>6)&0x1F)*0x3F/0x1F)<<5) | (((*(guint16*)pS)&0x3E)>>1);
                    M_CONVERT_END__(GX::PixelFormatRGBA5551, GX::PixelFormatRGB565);
                    M_CONVERT_START(GX::PixelFormatRGBA5551, GX::PixelFormatBGR565);
                    (*(guint16*)pD)=(((*(guint16*)pS)&0xF800)>>11) | (((((*(guint16*)pS)>>6)&0x1F)*0x3F/0x1F)<<5) | (((*(guint16*)pS)&0x3E)<<10);
                    M_CONVERT_END__(GX::PixelFormatRGBA5551, GX::PixelFormatBGR565);
                    
                    M_CONVERT_START(GX::PixelFormatRGBA5551, GX::PixelFormatRGBA4444);
                    (*(guint16*)pD)=((*(guint16*)pS)&0xF000) | (((*(guint16*)pS)&0x780)<<1) | (((*(guint16*)pS)&0x3C)<<2) | (((*(guint16*)pS)&0x1)*0xF);
                    M_CONVERT_END__(GX::PixelFormatRGBA5551, GX::PixelFormatRGBA4444);
                    M_CONVERT_START(GX::PixelFormatRGBA5551, GX::PixelFormatBGRA4444);
                    (*(guint16*)pD)=(((*(guint16*)pS)&0xF000)>>8) | (((*(guint16*)pS)&0x780)<<1) | (((*(guint16*)pS)&0x3C)<<10) | (((*(guint16*)pS)&0x1)*0xF);
                    M_CONVERT_END__(GX::PixelFormatRGBA5551, GX::PixelFormatBGRA4444);
                    
                    M_CONVERT_START(GX::PixelFormatRGBA5551, GX::PixelFormatBGRA5551);
                    (*(guint16*)pD)=(((*(guint16*)pS)&0xF800)>>10) | (((*(guint16*)pS)&0x3E)<<10) | ((*(guint16*)pS)&0x7C1);
                    M_CONVERT_END__(GX::PixelFormatRGBA5551, GX::PixelFormatBGRA5551);
                    
                    M_CONVERT_START(GX::PixelFormatRGBA5551, GX::PixelFormatRGB888);
                    pD[0] = ((((*(guint16*)pS)>>11)&0x1F)*0xFF/0x1F);
                    pD[1] = ((((*(guint16*)pS)>>6)&0x1F)*0xFF/0x1F);
                    pD[2] = ((((*(guint16*)pS)>>1)&0x1F)*0xFF/0x1F);
                    M_CONVERT_END__(GX::PixelFormatRGBA5551, GX::PixelFormatRGB888);
                    
                    M_CONVERT_START(GX::PixelFormatRGBA5551, GX::PixelFormatRGBA8888);
                    (*(guint32*)pD)=((((*(guint16*)pS)>>11)&0x1F)*0xFF/0x1F) |
                    (((((*(guint16*)pS)>>6)&0x1F)*0xFF/0x1F)<<8) |
                    (((((*(guint16*)pS)>>1)&0x1F)*0xFF/0x1F)<<16) |
                    ((((*(guint16*)pS)&0x1)*0xFF)<<24);
                    M_CONVERT_END__(GX::PixelFormatRGBA5551, GX::PixelFormatRGBA8888);
                    M_CONVERT_START(GX::PixelFormatRGBA5551, GX::PixelFormatBGRA8888);
                    (*(guint32*)pD)=(((((*(guint16*)pS)>>11)&0x1F)*0xFF/0x1F)<<16) |
                    (((((*(guint16*)pS)>>6)&0x1F)*0xFF/0x1F)<<8) |
                    ((((*(guint16*)pS)>>1)&0x1F)*0xFF/0x1F) |
                    ((((*(guint16*)pS)&0x1)*0xFF)<<24);
                    M_CONVERT_END__(GX::PixelFormatRGBA5551, GX::PixelFormatBGRA8888);
                default:
                    break;
            }
        }
            break;
        case GX::PixelFormatBGRA5551:
        {
            switch (pfTo)
            {
                    M_CONVERT_START(GX::PixelFormatBGRA5551, GX::PixelFormatA8);
                    (*pD)=((*(guint16*)pS)&0x1)*0xFF;
                    M_CONVERT_END__(GX::PixelFormatBGRA5551, GX::PixelFormatA8);
                    
                    M_CONVERT_START(GX::PixelFormatBGRA5551, GX::PixelFormatRGB565);
                    (*(guint16*)pD)=(((*(guint16*)pS)&0xF800)>>11) | (((((*(guint16*)pS)>>6)&0x1F)*0x3F/0x1F)<<5) | (((*(guint16*)pS)&0x3E)<<10);
                    M_CONVERT_END__(GX::PixelFormatBGRA5551, GX::PixelFormatRGB565);
                    M_CONVERT_START(GX::PixelFormatBGRA5551, GX::PixelFormatBGR565);
                    (*(guint16*)pD)=((*(guint16*)pS)&0xF800) | (((((*(guint16*)pS)>>6)&0x1F)*0x3F/0x1F)<<5) | (((*(guint16*)pS)&0x3E)>>1);
                    M_CONVERT_END__(GX::PixelFormatBGRA5551, GX::PixelFormatBGR565);
                    
                    M_CONVERT_START(GX::PixelFormatBGRA5551, GX::PixelFormatRGBA4444);
                    (*(guint16*)pD)=(((*(guint16*)pS)&0xF000)>>8) | (((*(guint16*)pS)&0x780)<<1) | (((*(guint16*)pS)&0x3C)<<10) | (((*(guint16*)pS)&0x1)*0xF);
                    M_CONVERT_END__(GX::PixelFormatBGRA5551, GX::PixelFormatRGBA4444);
                    M_CONVERT_START(GX::PixelFormatBGRA5551, GX::PixelFormatBGRA4444);
                    (*(guint16*)pD)=((*(guint16*)pS)&0xF000) | (((*(guint16*)pS)&0x780)<<1) | (((*(guint16*)pS)&0x3C)<<2) | (((*(guint16*)pS)&0x1)*0xF);
                    M_CONVERT_END__(GX::PixelFormatBGRA5551, GX::PixelFormatBGRA4444);
                    
                    M_CONVERT_START(GX::PixelFormatBGRA5551, GX::PixelFormatRGBA5551);
                    (*(guint16*)pD)=(((*(guint16*)pS)&0xF800)>>10) | (((*(guint16*)pS)&0x3E)<<10) | ((*(guint16*)pS)&0x7C1);
                    M_CONVERT_END__(GX::PixelFormatBGRA5551, GX::PixelFormatRGBA5551);
                    
                    M_CONVERT_START(GX::PixelFormatBGRA5551, GX::PixelFormatRGB888);
                    pD[0] = ((((*(guint16*)pS)>>1)&0x1F)*0xFF/0x1F);
                    pD[1] = ((((*(guint16*)pS)>>6)&0x1F)*0xFF/0x1F);
                    pD[2] = ((((*(guint16*)pS)>>11)&0x1F)*0xFF/0x1F);
                    M_CONVERT_END__(GX::PixelFormatBGRA5551, GX::PixelFormatRGB888);
                    
                    M_CONVERT_START(GX::PixelFormatBGRA5551, GX::PixelFormatRGBA8888);
                    (*(guint32*)pD)=(((((*(guint16*)pS)>>11)&0x1F)*0xFF/0x1F)<<16) |
                    (((((*(guint16*)pS)>>6)&0x1F)*0xFF/0x1F)<<8) |
                    ((((*(guint16*)pS)>>1)&0x1F)*0xFF/0x1F) |
                    ((((*(guint16*)pS)&0x1)*0xFF)<<24);
                    M_CONVERT_END__(GX::PixelFormatBGRA5551, GX::PixelFormatRGBA8888);
                    M_CONVERT_START(GX::PixelFormatBGRA5551, GX::PixelFormatBGRA8888);
                    (*(guint32*)pD)=((((*(guint16*)pS)>>11)&0x1F)*0xFF/0x1F) |
                    (((((*(guint16*)pS)>>6)&0x1F)*0xFF/0x1F)<<8) |
                    (((((*(guint16*)pS)>>1)&0x1F)*0xFF/0x1F)<<16) |
                    ((((*(guint16*)pS)&0x1)*0xFF)<<24);
                    M_CONVERT_END__(GX::PixelFormatBGRA5551, GX::PixelFormatBGRA8888);
                default:
                    break;
            }
        }
            break;
        case GX::PixelFormatRGB888:
        {
            switch (pfTo)
            {
                    M_CONVERT_START(GX::PixelFormatRGB888, GX::PixelFormatA8);
                    (*pD)=0xFF;
                    M_CONVERT_END__(GX::PixelFormatRGB888, GX::PixelFormatA8);
                    
                    M_CONVERT_START(GX::PixelFormatRGB888, GX::PixelFormatRGB565);
                    (*(guint16*)pD)=((pS[0]&0xF8)<<8) | ((pS[1]&0xFC)<<3) | ((pS[2]&0xF8)>>3);
                    M_CONVERT_END__(GX::PixelFormatRGB888, GX::PixelFormatRGB565);
                    M_CONVERT_START(GX::PixelFormatRGB888, GX::PixelFormatBGR565);
                    (*(guint16*)pD)=((pS[0]&0xF8)>>3) | ((pS[1]&0xFC)<<3) | ((pS[2]&0xF8)<<8);
                    M_CONVERT_END__(GX::PixelFormatRGB888, GX::PixelFormatBGR565);
                    
                    M_CONVERT_START(GX::PixelFormatRGB888, GX::PixelFormatRGBA4444);
                    (*(guint16*)pD)=((pS[0]&0xF0)<<8) | ((pS[1]&0xF0)<<4) | ((pS[2]&0xF0)<<0) | 0xF;
                    M_CONVERT_END__(GX::PixelFormatRGB888, GX::PixelFormatRGBA4444);
                    M_CONVERT_START(GX::PixelFormatRGB888, GX::PixelFormatBGRA4444);
                    (*(guint16*)pD)=((pS[0]&0xF0)<<0) | ((pS[1]&0xF0)<<4) | ((pS[2]&0xF0)<<8) | 0xF;
                    M_CONVERT_END__(GX::PixelFormatRGB888, GX::PixelFormatBGRA4444);
                    
                    M_CONVERT_START(GX::PixelFormatRGB888, GX::PixelFormatRGBA5551);
                    (*(guint16*)pD)=((pS[0]&0xF8)<<8) | ((pS[1]&0xF8)<<3) | ((pS[2]&0xF8)>>2) | 0x1;
                    M_CONVERT_END__(GX::PixelFormatRGB888, GX::PixelFormatRGBA5551);
                    M_CONVERT_START(GX::PixelFormatRGB888, GX::PixelFormatBGRA5551);
                    (*(guint16*)pD)=((pS[0]&0xF8)>>2) | ((pS[1]&0xF8)<<3) | ((pS[2]&0xF8)<<8) | 0x1;
                    M_CONVERT_END__(GX::PixelFormatRGB888, GX::PixelFormatBGRA5551);
                    
                    M_CONVERT_START(GX::PixelFormatRGB888, GX::PixelFormatRGBA8888);
                    (*(guint32*)pD)=0xFF000000 | pS[0] | (pS[1]<<8) | (pS[2]<<16);
                    M_CONVERT_END__(GX::PixelFormatRGB888, GX::PixelFormatRGBA8888);
                    
                    M_CONVERT_START(GX::PixelFormatRGB888, GX::PixelFormatBGRA8888);
                    (*(guint32*)pD)=0xFF000000 | (pS[0]<<16) | (pS[1]<<8) | pS[2];
                    M_CONVERT_END__(GX::PixelFormatRGB888, GX::PixelFormatBGRA8888);
                default:
                    break;
            }
        }
            break;
        case GX::PixelFormatRGBA8888:
        {
            switch (pfTo)
            {
                    M_CONVERT_START(GX::PixelFormatRGBA8888, GX::PixelFormatA8);
                    (*pD)=pS[3];
                    M_CONVERT_END__(GX::PixelFormatRGBA8888, GX::PixelFormatA8);
                    
                    M_CONVERT_START(GX::PixelFormatRGBA8888, GX::PixelFormatRGB565);
                    (*(guint16*)pD)=((pS[0]&0xF8)<<8) | ((pS[1]&0xFC)<<3) | ((pS[2]&0xF8)>>3);
                    M_CONVERT_END__(GX::PixelFormatRGBA8888, GX::PixelFormatRGB565);
                    M_CONVERT_START(GX::PixelFormatRGBA8888, GX::PixelFormatBGR565);
                    (*(guint16*)pD)=((pS[0]&0xF8)>>3) | ((pS[1]&0xFC)<<3) | ((pS[2]&0xF8)<<8);
                    M_CONVERT_END__(GX::PixelFormatRGBA8888, GX::PixelFormatBGR565);
                    
                    M_CONVERT_START(GX::PixelFormatRGBA8888, GX::PixelFormatRGBA4444);
                    (*(guint16*)pD)=((pS[0]&0xF0)<<8) | ((pS[1]&0xF0)<<4) | ((pS[2]&0xF0)<<0) | ((pS[3]&0xF0)>>4);
                    M_CONVERT_END__(GX::PixelFormatRGBA8888, GX::PixelFormatRGBA4444);
                    M_CONVERT_START(GX::PixelFormatRGBA8888, GX::PixelFormatBGRA4444);
                    (*(guint16*)pD)=((pS[0]&0xF0)<<0) | ((pS[1]&0xF0)<<4) | ((pS[2]&0xF0)<<8) | ((pS[3]&0xF0)>>4);
                    M_CONVERT_END__(GX::PixelFormatRGBA8888, GX::PixelFormatBGRA4444);
                    
                    M_CONVERT_START(GX::PixelFormatRGBA8888, GX::PixelFormatRGBA5551);
                    (*(guint16*)pD)=((pS[0]&0xF8)<<8) | ((pS[1]&0xF8)<<3) | ((pS[2]&0xF8)>>2) | ((pS[3]&0x80)>>7);
                    M_CONVERT_END__(GX::PixelFormatRGBA8888, GX::PixelFormatRGBA5551);
                    M_CONVERT_START(GX::PixelFormatRGBA8888, GX::PixelFormatBGRA5551);
                    (*(guint16*)pD)=((pS[0]&0xF8)>>2) | ((pS[1]&0xF8)<<3) | ((pS[2]&0xF8)<<8) | ((pS[3]&0x80)>>7);
                    M_CONVERT_END__(GX::PixelFormatRGBA8888, GX::PixelFormatBGRA5551);
                    
                    M_CONVERT_START(GX::PixelFormatRGBA8888, GX::PixelFormatRGB888);
                    pD[0]=pS[0];
                    pD[1]=pS[1];
                    pD[2]=pS[2];
                    M_CONVERT_END__(GX::PixelFormatRGBA8888, GX::PixelFormatRGB888);
                    
                    M_CONVERT_START(GX::PixelFormatRGBA8888, GX::PixelFormatBGRA8888);
                    pD[0]=pS[2];
                    pD[1]=pS[1];
                    pD[2]=pS[0];
                    pD[3]=pS[3];
                    M_CONVERT_END__(GX::PixelFormatRGBA8888, GX::PixelFormatBGRA8888);
                default:
                    break;
            }
        }
            break;
        case GX::PixelFormatBGRA8888:
        {
            switch (pfTo)
            {
                    M_CONVERT_START(GX::PixelFormatBGRA8888, GX::PixelFormatA8);
                    (*pD)=pS[3];
                    M_CONVERT_END__(GX::PixelFormatBGRA8888, GX::PixelFormatA8);
                    
                    M_CONVERT_START(GX::PixelFormatBGRA8888, GX::PixelFormatRGB565);
                    (*(guint16*)pD)=((pS[0]&0xF8)>>3) | ((pS[1]&0xFC)<<3) | ((pS[2]&0xF8)<<8);
                    M_CONVERT_END__(GX::PixelFormatBGRA8888, GX::PixelFormatRGB565);
                    M_CONVERT_START(GX::PixelFormatBGRA8888, GX::PixelFormatBGR565);
                    (*(guint16*)pD)=((pS[0]&0xF8)<<8) | ((pS[1]&0xFC)<<3) | ((pS[2]&0xF8)>>3);
                    M_CONVERT_END__(GX::PixelFormatBGRA8888, GX::PixelFormatBGR565);
                    
                    M_CONVERT_START(GX::PixelFormatBGRA8888, GX::PixelFormatRGBA4444);
                    (*(guint16*)pD)=((pS[0]&0xF0)<<0) | ((pS[1]&0xF0)<<4) | ((pS[2]&0xF0)<<8) | ((pS[3]&0xF0)>>4);
                    M_CONVERT_END__(GX::PixelFormatBGRA8888, GX::PixelFormatRGBA4444);
                    M_CONVERT_START(GX::PixelFormatBGRA8888, GX::PixelFormatBGRA4444);
                    (*(guint16*)pD)=((pS[0]&0xF0)<<8) | ((pS[1]&0xF0)<<4) | ((pS[2]&0xF0)<<0) | ((pS[3]&0xF0)>>4);
                    M_CONVERT_END__(GX::PixelFormatBGRA8888, GX::PixelFormatBGRA4444);
                    
                    M_CONVERT_START(GX::PixelFormatBGRA8888, GX::PixelFormatRGBA5551);
                    (*(guint16*)pD)=((pS[0]&0xF8)>>2) | ((pS[1]&0xF8)<<3) | ((pS[2]&0xF8)<<8) | ((pS[3]&0x80)>>7);
                    M_CONVERT_END__(GX::PixelFormatBGRA8888, GX::PixelFormatRGBA5551);
                    M_CONVERT_START(GX::PixelFormatBGRA8888, GX::PixelFormatBGRA5551);
                    (*(guint16*)pD)=((pS[0]&0xF8)<<8) | ((pS[1]&0xF8)<<3) | ((pS[2]&0xF8)>>2) | ((pS[3]&0x80)>>7);
                    M_CONVERT_END__(GX::PixelFormatBGRA8888, GX::PixelFormatBGRA5551);
                    
                    M_CONVERT_START(GX::PixelFormatBGRA8888, GX::PixelFormatRGB888);
                    pD[0]=pS[2];
                    pD[1]=pS[1];
                    pD[2]=pS[0];
                    M_CONVERT_END__(GX::PixelFormatBGRA8888, GX::PixelFormatRGB888);
                    
                    M_CONVERT_START(GX::PixelFormatBGRA8888, GX::PixelFormatRGBA8888);
                    pD[0]=pS[2];
                    pD[1]=pS[1];
                    pD[2]=pS[0];
                    pD[3]=pS[3];
                    M_CONVERT_END__(GX::PixelFormatBGRA8888, GX::PixelFormatRGBA8888);
                default:
                    break;
            }
        }
            break;
        default:
            break;
    }
    return NULL;
}

#undef M_CONVERT_START
#undef M_CONVERT_END__


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
    if(m_Data.changeBytes(bytes)) {
        m_Data.zeroSelf();
        return true;
    }
    return false;
}

void GDib::setStaticData(const void* data, guint bytes)
{
    m_Data.setStatic(data, bytes);
}

void GDib::changeData(GX::PixelFormat pf,gint32 w,gint32 h,gint32 stride)
{
    m_PixelFormat=pf;
    m_Width=w;
    m_Height=h;
    m_Stride=stride;
    if(m_Data.changeBytes(stride*h)) {
        m_Data.zeroSelf();
    }
}

void GDib::changeData(GX::PixelFormat pf,gint32 w,gint32 h)
{
    changeData(pf, w, h, w*GX_PIXEL_FORMAT_SIZE(pf));
}


typedef enum __DrawState {
    _DrawStateText,
    _DrawStateOL,
    _DrawStateOLText,
} _DrawState;

static void _DrawFTDib(GDib* context,_DrawState ds,GDib* dib,gint32 x,gint32 y,const GTypist::Paint* paint)
{
    GX_ASSERT(dib->getPixelFormat()==GX::PixelFormatA8);
    
    if (x>=context->getWidth() || x+dib->getWidth()<=0 || y>=context->getHeight() || y+dib->getHeight()<=0) {
        return;
    }
    
    
    gint32 rowWide=x+dib->getWidth() > context->getWidth() ? context->getWidth()-x:dib->getWidth();
    gint32 rowNum=y+dib->getHeight() > context->getHeight()? context->getHeight()-y:dib->getHeight();
    gint32 sx=0,sy=0;
    if (x<0) {
        rowWide+=x;
        sx=-x;
        x=0;
    }
    if (y<0) {
        rowNum+=y;
        sy=-y;
        y=0;
    }
    gint32 srcPitch=dib->getStride();
    guint8* srcData=(guint8*)dib->getDataPtr(sx,sy);
    gint32 dstPitch=context->getStride();
    guint8* dstData=(guint8*)context->getDataPtr(x,y);
    
    GX::PixelFormat pf=context->getPixelFormat();
    
    switch (pf) {
        case GX::PixelFormatA8:
        {
            for (gint32 j=0; j<rowNum; j++) {
                GX::gmemcpy(dstData, srcData, rowWide);
                srcData+=srcPitch;
                dstData+=dstPitch;
            }
        }
            break;
        case GX::PixelFormatRGBA8888:
        {
            GColor4 clr;
            GTypist::BlendMode bm;
            if (ds>=_DrawStateOL) {
                if (ds==_DrawStateOL) {
                    clr=paint->getOutlineColor();
                    bm=paint->getBlendMode();
                }
                else {
                    clr=paint->getColor();
                    bm=GTypist::BlendModeSaD1sa;
                }
            }
            else {
                clr=paint->getColor();
                bm=paint->getBlendMode();
            }
            
            switch (bm) {
                case GTypist::BlendModeDefault:
                default:
                {
                    guint8 a;
                    for (gint32 j=0; j<rowNum; j++) {
                        for (gint32 i=0; i<rowWide; i++) {
                            a=(guint8)(clr.a*(gint32)(srcData[i])/0xFF);
                            if (a>0) {
                                dstData[i*4+0]=clr.r;
                                dstData[i*4+1]=clr.g;
                                dstData[i*4+2]=clr.b;
                                dstData[i*4+3]=a;
                            }
                        }
                        srcData+=srcPitch;
                        dstData+=dstPitch;
                    }
                }
                    break;
                case GTypist::BlendModeSaD1sa:
                {
                    float r,g,b,a,sa,da;
                    for (gint32 j=0; j<rowNum; j++) {
                        for (gint32 i=0; i<rowWide; i++) {
                            
                            sa=(float)clr.a*(float)srcData[i]/255.0f;
                            da=(float)dstData[i*4+3];
                            
                            r=(float)clr.r;
                            r=dstData[i*4+0]+(r-dstData[i*4+0])*sa/255.0f;
                            
                            g=(float)clr.g;
                            g=dstData[i*4+1]+(g-dstData[i*4+1])*sa/255.0f;
                            
                            b=(float)clr.b;
                            b=dstData[i*4+2]+(b-dstData[i*4+2])*sa/255.0f;
                            
                            a=sa+da;
                            if (a>255.0f) {
                                a=255.0f;
                            }
                            
                            dstData[i*4+0]=(guint8)(r);
                            dstData[i*4+1]=(guint8)(g);
                            dstData[i*4+2]=(guint8)(b);
                            dstData[i*4+3]=(guint8)(a);
                        }
                        srcData+=srcPitch;
                        dstData+=dstPitch;
                    }
                }
                    break;
            }
            
        }
            break;
        default:
            break;
    }
}

bool GDib::isFlipped()
{
    return true;
}

GTypist::Paper::PrintGlyphSelector GDib::printCheck(GFont* font)
{
    if (font->isKindOfClass(GFTFont::gclass)) {
        return printFTFontGlyph;
    }
    return NULL;
}
void GDib::printBegin(GFont* font,GPointF pos)
{
    GX_UNUSED(font);
    GX_UNUSED(pos);
}
void GDib::printFTFontGlyph(GTypist::Paper* paper,GFont* font,GFont::Glyph* glyph,GPointF pos,GPointF offset,const GTypist::Paint* paint)
{
    GX_UNUSED(offset);
    if (glyph->isBlank()) {
        return;
    }
    
    pos.y+=font->getAscender()/64.0f;
    
    GFTFont::Glyph* ghFT=GX_CAST_R(GFTFont::Glyph*, glyph);
    
    GDib* dib=ghFT->getDib();
    GDib* dibOL=ghFT->getOutlineDib();
    if (dibOL) {
        float olSize=ghFT->getOutlineSize()/64.0f;
        _DrawFTDib(GX_CAST_S(GDib*, paper), _DrawStateOL, dibOL, (gint32)GX::round(pos.x), (gint32)GX::round(pos.y), paint);
        _DrawFTDib(GX_CAST_S(GDib*, paper), _DrawStateOLText, dib, (gint32)GX::round(pos.x+olSize), (gint32)GX::round(pos.y+olSize), paint);
    }
    else {
        _DrawFTDib(GX_CAST_S(GDib*, paper), _DrawStateText, dib, (gint32)GX::round(pos.x), (gint32)GX::round(pos.y), paint);
    }
}
void GDib::printEnd()
{
    
}
