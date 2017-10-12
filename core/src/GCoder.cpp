//
//  GCoder.cpp
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#include "GCoder.h"


GEncoder::GEncoder(GWriter* writer) : GX::Encoder(writer)
{
    GX_ASSERT(writer);
}

GEncoder::~GEncoder()
{

}

gint GEncoder::encode(const void* buf,guint len)
{
    gint res=getWriter()->write(buf, len);
    return res<(gint)len?-1:res;
}








GDecoder::GDecoder(GReader* reader) : GX::Decoder(reader)
{
    GX_ASSERT(reader);
}

GDecoder::~GDecoder()
{
}

gint GDecoder::decode(void* buf,guint len)
{
    return getReader()->read(buf, len);
}
