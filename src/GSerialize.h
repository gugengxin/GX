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
#include "GArray.h"



class GSerialize {
public:
    static gint seBytesOfKeyAndData(guint32 key,guint len);
    static gint seBytesOfKeyAndObject(guint32 key,GSerialize* obj);
    template <typename T> static gint seBytesOfKeyAndObjects(guint32 key,GArray<T>* objs);
public:
    GSerialize();
    virtual ~GSerialize();

public:
    gint seEncode(GWriter* writer);
    gint seEncode(GEncoder& coder);

    gint seEncodeKeyAndData(GEncoder& coder,guint32 key,const void* buf,guint len);
    gint seEncodeKeyAndObject(GEncoder& coder,guint32 key,GSerialize* obj);
    template <typename T> gint seEncodeKeyAndObjects(GEncoder& coder,guint32 key,GArray<T>* objs);
    
protected:
	virtual const GX::UUID& seGetUUID()=0;
    virtual gint seGetBytes()=0;
    virtual gint seEncodeFields(GEncoder& coder)=0;
};


class GUnserialize {
public:
    GUnserialize();
	virtual ~GUnserialize();
public:
    gint ueDecode(GReader* reader);
    gint ueDecode(GDecoder& coder,guint32 len);

    gint ueDecodeData(GDecoder& coder,void* dataOut,guint dataBytes);
    template <typename T> gint ueDecodeObject(GDecoder& coder,T** objOut,guint32 len);
    template <typename T> gint ueDecodeObjects(GDecoder& coder,GArray<T>* objsOut,guint32 len);
    template <typename T> gint ueDecodeObjects(GDecoder& coder,GArray<T>** objsOut,guint32 len);
protected:
	virtual const GX::UUID& ueGetUUID() = 0;
    virtual gint ueDecodeField(GDecoder& coder,guint32 key,guint32 len)=0;///返回<0失败 0没有此Key >0成功
}; 



//////////////////////////

template <typename T>
gint GSerialize::seBytesOfKeyAndObjects(guint32 key,GArray<T>* objs)
{
    gint len=GX::bytesOfVU32((guint32)objs->getCount());
    for (gint i=0; i<objs->getCount(); i++) {
        gint lenTemp=0;
        T* obj=objs->get(i);
        if (obj) {
            lenTemp=obj->seGetBytes();
            if (lenTemp<0) {
                return -1;
            }
        }
        len+=GX::bytesOfVU32((guint32)lenTemp)+lenTemp;
    }
    return GX::bytesOfVU32(key)+GX::bytesOfVU32((guint32)len)+len;
}

template <typename T>
gint GSerialize::seEncodeKeyAndObjects(GEncoder& coder,guint32 key,GArray<T>* objs)
{
    gint res=coder.encodeVU32(key);

    gint count=objs->getCount();
    gint lenAll=GX::bytesOfVU32((guint32)count);

    gint* lens=new gint[count];
    for (gint i=0; i<count; i++) {
        T* obj=objs->get(i);
        if (obj) {
            lens[i]=obj->seGetBytes();
            if (lens[i]<0) {
                delete [] lens;
                return -1;
            }
        }
        else {
            lens[i]=0;
        }
        lenAll+=GX::bytesOfVU32((guint32)lens[i])+lens[i];
    }

    res+=coder.encodeVU32((guint32)lenAll);

    if (coder.encodeVU32((guint32)count)<0) {
        delete [] lens;
        return -1;
    }

    for (gint i=0; i<count; i++) {
        if (coder.encodeVU32((guint32)lens[i])) {
            delete [] lens;
            return -1;
        }
        if (objs->get(i)->seEncode(coder)!=lens[i]) {
            delete [] lens;
            return -1;
        }
    }

    delete [] lens;
    return res+lenAll;
}


template <typename T>
gint GUnserialize::ueDecodeObject(GDecoder& coder,T** objOut,guint32 len)
{
    (*objOut)=T::autoAlloc();
    return (*objOut)->ueDecode(coder,len);
}

template <typename T>
gint GUnserialize::ueDecodeObjects(GDecoder& coder,GArray<T>* objsOut,guint32 len)
{
    guint32 count=0;
    gint res=coder.decodeVU32(count);
    if (res<0) {
        return -1;
    }
    for (gint i=0; i<(gint)count; i++) {
        guint32 lenTemp=0;
        gint nTemp=coder.decodeVU32(lenTemp);
        if (nTemp<0) {
            return -1;
        }
        res+=nTemp;

        T* obj=T::autoAlloc();
        nTemp=obj->ueDecode(coder,lenTemp);
        if(nTemp!=(gint)lenTemp) {
            return -1;
        }
        if(!objsOut->add(obj)) {
            return -1;
        }
        res+=nTemp;
    }
    return res;
}

template <typename T>
gint GUnserialize::ueDecodeObjects(GDecoder& coder,GArray<T>** objsOut,guint32 len)
{
    (*objsOut)=GArray<T>::autoAlloc();
    return ueDecodeObjects(coder,(*objsOut),len);
}

#endif /* GSerialize_h */
