//
//  GCoder.h
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#ifndef GCoder_h
#define GCoder_h

#include "GXPrefix.h"
#include "GXCoder.h"
#include "GReader.h"
#include "GWriter.h"


class GEncoder : public GX::Encoder {
public:
    GEncoder(GWriter* writer);
    ~GEncoder();

    virtual GX::INT encode(const void* buf,GX::UNT len);
private:
    inline GWriter* getWriter() {
        return GX_CAST_R(GWriter*, getTagPtr());
    }
};


class GDecoder : public GX::Decoder {
public:
    GDecoder(GReader* reader);
    ~GDecoder();

    virtual GX::INT decode(void* buf,GX::UNT len);
private:
    inline GReader* getReader() {
        return GX_CAST_R(GReader*, getTagPtr());
    }
};





#endif /* GCoder_h */
