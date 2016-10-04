//
//  GSerialize.h
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#ifndef GSerialize_h
#define GSerialize_h

#include "GXPrefix.h"
#include "GCoder.h"



class GSerialize {
public:
    static gint bytesOfData(guint32 key,guint len);
public:
    GSerialize();
    ~GSerialize();

public:
    gint seEncode(GWriter* writer);
    gint seEncode(GX::Encoder& coder);
protected:
    virtual guint32 seGetVersion()=0;
    virtual gint  seGetBytes()=0;
    virtual gint  seEncodeFields(GX::Encoder& coder,guint32 version)=0;
};


class GUnserialize {
public:
    GUnserialize();
    ~GUnserialize();
    

public:
    gint ueDecode(GReader* reader,guint32 lenAll);

protected:
    virtual guint32 ueGetVersion()=0;
    virtual gint ueDecodeField(GReader* reader,guint32 version,guint32 key,guint32 len)=0;///返回<0失败 0没有此Key >0成功
};

#endif /* GSerialize_h */
