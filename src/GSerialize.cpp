//
//  GSerialize.cpp
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#include "GSerialize.h"


gint GSerialize::seBytesOfKeyAndData(guint32 key,guint len)
{
    return GX::bytesOfVU32(key)+GX::bytesOfVU32((guint32)len)+(gint)len;
}

gint GSerialize::seBytesOfKeyAndObject(guint32 key,GSerialize* obj)
{
    gint res=obj->seGetBytes();
    if (res<0) {
        return -1;
    }
    return GX::bytesOfVU32(key)+GX::bytesOfVU32((guint32)res)+res;
}



GSerialize::GSerialize()
{
    
}

GSerialize::~GSerialize()
{
    
}

gint GSerialize::seEncode(GWriter* writer)
{
    GEncoder coder(writer);

	const GX::UUID& uuid = seGetUUID();

    gint len=seGetBytes();
    if (len<0) {
        return -1;
    }

    gint res=0;

	gint nTemp = coder.encodeUUID(*(GX::UUID*)&uuid);
	if (nTemp!=(gint)(*(GX::UUID*)&uuid).getBytes()) {
		return -1;
	}
	res += nTemp;

    nTemp=coder.encodeVU32((guint32)len);
    if (nTemp<0) {
        return -1;
    }
    res+=nTemp;

    nTemp=seEncode(coder);
    if (nTemp!=len) {
        return -1;
    }
    res+=nTemp;

    return res;
}

gint GSerialize::seEncode(GEncoder& coder)
{
    return seEncodeFields(coder);
}

gint GSerialize::seEncodeKeyAndData(GEncoder& coder,guint32 key,const void* buf,guint len)
{
    gint res=coder.encodeVU32(key);
    res+=coder.encodeVU32((guint32)len);
    gint nTemp=coder.encode(buf, len);
    if (nTemp!=(gint)len) {
        return -1;
    }
    return res+nTemp;
}

gint GSerialize::seEncodeKeyAndObject(GEncoder& coder,guint32 key,GSerialize* obj)
{
    gint res=coder.encodeVU32(key);
    gint lenTemp=obj->seGetBytes();
    if (lenTemp<0) {
        return -1;
    }
    res+=coder.encodeVU32((guint32)lenTemp);

    if (obj->seEncode(coder)!=lenTemp) {
        return -1;
    }
    return res+lenTemp;
}




GUnserialize::GUnserialize()
{

}

GUnserialize::~GUnserialize()
{

}

gint GUnserialize::ueDecode(GReader* reader)
{
    GDecoder coder(reader);

    gint res=0;

	GX::UUID uuid;
	gint nTemp = coder.decodeUUID(uuid);
	if (nTemp != (gint)uuid.getBytes()) {
		return -1;
	}
	if (uuid != ueGetUUID()) {
		return -1;
	}
	res += nTemp;

    guint32 len=0;
    nTemp = coder.decodeVU32(len);
    if (nTemp<0) {
        return -1;
    }
    res+=nTemp;
    nTemp=ueDecode(coder, len);
    if (nTemp!=(gint)len) {
        return -1;
    }
    res+=nTemp;

    return res;
}

gint GUnserialize::ueDecode(GDecoder& coder,guint32 len)
{
    guint32 key=0,lenOne=0;
    gint res=0;
    while (((guint32)res)<len) {
        gint lenTemp=coder.decodeVU32(key);
        if (lenTemp<0) {
            return -1;
        }
        res+=lenTemp;
        if (((guint32)res)>=len) {
            return -1;
        }
        lenTemp=coder.decodeVU32(lenOne);
        if (lenTemp<0) {
            return -1;
        }
        res+=lenTemp;
        if (((guint32)res)>len) {
            return -1;
        }
        if (lenOne>0) {
            lenTemp=ueDecodeField(coder, key, lenOne);
            if (lenTemp!=(gint)lenOne) {
                return -1;
            }
            res+=lenTemp;
        }
    }
    if (((guint32)res)!=len) {
        return -1;
    }
    return res;
}

gint GUnserialize::ueDecodeData(GDecoder& coder,void* dataOut,guint dataBytes)
{
    return coder.decode(dataOut, dataBytes);
}





