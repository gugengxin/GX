//
//  GXCoder.cpp
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#include "GXCoder.h"

namespace GX {

    INT bytesOfVI32(VI32 value)
    {
        if (value<0) {
            value=-value;
        }
        if (value<=0x3F) {
            return 1;
        }
        else if(value<=0x1FFF) {
            return 2;
        }
        else if(value<=0xFFFFF) {
            return 3;
        }
        else if(value<=0x7FFFFFF) {
            return 4;
        }
        else {
            return 5;
        }
        return -1;
    }
    INT bytesOfVU32(VU32 value)
    {
        if (value<=0x7F) {
            return 1;
        }
        else if(value<=0x3FFF) {
            return 2;
        }
        else if(value<=0x1FFFFF) {
            return 3;
        }
        else if(value<=0xFFFFFFF) {
            return 4;
        }
        else {
            return 5;
        }
        return -1;
    }
    INT bytesOfVI64(VI64 value)
    {
        if (value<0) {
            value=-value;
        }
        if (value<=0x3F) {
            return 1;
        }
        else if(value<=0x1FFF) {
            return 2;
        }
        else if(value<=0xFFFFF) {
            return 3;
        }
        else if(value<=0x7FFFFFF) {
            return 4;
        }
        else if(value<=0x3FFFFFFFF) {
            return 5;
        }
        else if(value<=0x1FFFFFFFFFF) {
            return 6;
        }
        else if(value<=0xFFFFFFFFFFFF) {
            return 7;
        }
        else if(value<=0x7FFFFFFFFFFFFF) {
            return 8;
        }
        else if(value<=0x3FFFFFFFFFFFFFFF) {
            return 9;
        }
        else {
            return 10;
        }
        return -1;
    }
    INT bytesOfVU64(VU64 value)
    {
        if (value<=0x7F) {
            return 1;
        }
        else if(value<=0x3FFF) {
            return 2;
        }
        else if(value<=0x1FFFFF) {
            return 3;
        }
        else if(value<=0xFFFFFFF) {
            return 4;
        }
        else if(value<=0x7FFFFFFFF) {
            return 5;
        }
        else if(value<=0x3FFFFFFFFFF) {
            return 6;
        }
        else if(value<=0x1FFFFFFFFFFFF) {
            return 7;
        }
        else if(value<=0xFFFFFFFFFFFFFF) {
            return 8;
        }
        else if(value<=0x7FFFFFFFFFFFFFFF) {
            return 9;
        }
        else {
            return 10;
        }
        return -1;
    }






    Coder::Coder(void* tagPtr)
    {
        m_TagPtr=tagPtr;
    }

    Coder::~Coder()
    {
    }
    




    Encoder::Encoder(void* tagPtr) : Coder(tagPtr)
    {
    }

    Encoder::~Encoder()
    {
    }

#define M_ENCODE(t) \
    INT Encoder::encode##t(t value)\
    {\
        return encode(&value, sizeof(t));\
    }\
    INT Encoder::encode##t##s(const t* values,UNT count)\
    {\
        return encode(values, count*sizeof(t));\
    }

    M_ENCODE(B8);
    M_ENCODE(I8);
    M_ENCODE(U8);
    M_ENCODE(I16);
    M_ENCODE(U16);
    M_ENCODE(I32);
    M_ENCODE(U32);
    M_ENCODE(I64);
    M_ENCODE(U64);
    M_ENCODE(F32);
    M_ENCODE(F64);

#undef M_ENCODE

    INT Encoder::encodeVI32(VI32 value)
    {
        U8 neg=0x0;
        if (value<0) {
            neg=0x40;
            value=-value;
        }
        for (INT i=0; i<5; i++) {
            if(value<=0x3F) {
                if(encodeU8((U8)(neg|(value&0x3F)))<0) {
                    return -1;
                }
                return (i+1);
            }
            else {
                if(encodeU8((U8)(0x80|(value&0x7F)))<0) {
                    return -1;
                }
            }
            value>>=7;
        }
        return -1;
    }
    INT Encoder::encodeVI32s(const VI32* values,UNT count)
    {
        INT res=0;
        for (UNT i=0; i<count; i++) {
            INT nTemp=encodeVI32(values[i]);
            if (nTemp<0) {
                return -1;
            }
            res+=nTemp;
        }
        return res;
    }
    
    INT Encoder::encodeVU32(VU32 value)
    {
        for (UNT i=0; i<5; i++) {
            if (value<=0x7F) {
                if(encodeU8((U8)((value&0x7F)))<0) {
                    return -1;
                }
                return (i+1);
            }
            else {
                if(encodeU8((U8)(0x80|(value&0x7F)))<0) {
                    return -1;
                }
            }
            value>>=7;
        }
        return -1;
    }
    INT Encoder::encodeVU32s(const VU32* values,UNT count)
    {
        INT res=0;
        for (UNT i=0; i<count; i++) {
            INT nTemp=encodeVU32(values[i]);
            if (nTemp<0) {
                return -1;
            }
            res+=nTemp;
        }
        return res;
    }

    INT Encoder::encodeVI64(VI64 value)
    {
        U8 neg=0x0;
        if (value<0) {
            neg=0x40;
            value=-value;
        }
        for (INT i=0; i<10; i++) {
            if(value<=0x3F) {
                if(encodeU8((U8)(neg|(value&0x3F)))<0) {
                    return -1;
                }
                return (i+1);
            }
            else {
                if(encodeU8((U8)(0x80|(value&0x7F)))<0) {
                    return -1;
                }
            }

            value>>=7;
        }
        return -1;
    }
    INT Encoder::encodeVI64s(const VI64* values,UNT count)
    {
        INT res=0;
        for (UNT i=0; i<count; i++) {
            INT nTemp=encodeVI64(values[i]);
            if (nTemp<0) {
                return -1;
            }
            res+=nTemp;
        }
        return res;
    }

    INT Encoder::encodeVU64(VU64 value)
    {
        for (UNT i=0; i<10; i++) {
            if (value<=0x7F) {
                if(encodeU8((U8)((value&0x7F)))<0) {
                    return -1;
                }
                return (i+1);
            }
            else {
                if(encodeU8((U8)(0x80|(value&0x7F)))<0) {
                    return -1;
                }
            }
            value>>=7;
        }
        return -1;
    }
    INT Encoder::encodeVU64s(const VU64* values,UNT count)
    {
        INT res=0;
        for (UNT i=0; i<count; i++) {
            INT nTemp=encodeVU64(values[i]);
            if (nTemp<0) {
                return -1;
            }
            res+=nTemp;
        }
        return res;
    }





    Decoder::Decoder(void* tagPtr) : Coder(tagPtr)
    {
    }

    Decoder::~Decoder()
    {
    }

#define M_DECODE(t) \
    INT Decoder::decode##t(t& valueOut)\
    {\
        return decode(&valueOut, sizeof(t));\
    }\
    INT Decoder::decode##t##s(t* valuesOut,UNT count)\
    {\
        return decode(valuesOut, sizeof(t)*count);\
    }

    M_DECODE(B8);
    M_DECODE(I8);
    M_DECODE(U8);
    M_DECODE(I16);
    M_DECODE(U16);
    M_DECODE(I32);
    M_DECODE(U32);
    M_DECODE(I64);
    M_DECODE(U64);
    M_DECODE(F32);
    M_DECODE(F64);

#undef M_DECODE

    INT Decoder::decodeVI32(VI32& valueOut)
    {
        valueOut=0;
        for (INT i=0; i<5; i++) {
            U8 uTemp;
            if (decodeU8(uTemp)<0) {
                return -1;
            }
            if (uTemp&0x80) {
                valueOut|=(((VI32)uTemp&0x7F)<<(i*7));
            }
            else {
                valueOut|=(((VI32)uTemp&0x3F)<<(i*7));
                if (uTemp&0x40) {
                    valueOut=-valueOut;
                }
                return (i+1);
            }
        }
        return -1;
    }
    INT Decoder::decodeVI32s(VI32* valuesOut,UNT count)
    {
        INT res=0;
        for (UNT i=0; i<count; i++) {
            INT nTemp=decodeVI32(valuesOut[i]);
            if (nTemp<0) {
                return -1;
            }
            res+=nTemp;
        }
        return res;
    }

    INT Decoder::decodeVU32(VU32& valueOut)
    {
        valueOut=0;
        for (INT i=0; i<5; i++) {
            U8 uTemp;
            if (decodeU8(uTemp)<0) {
                return -1;
            }
            valueOut|=(((VU32)uTemp&0x7F)<<(i*7));

            if (!(uTemp&0x80)) {
                return (i+1);
            }
        }
        return -1;
    }
    INT Decoder::decodeVU32s(VU32* valuesOut,UNT count)
    {
        INT res=0;
        for (UNT i=0; i<count; i++) {
            INT nTemp=decodeVU32(valuesOut[i]);
            if (nTemp<0) {
                return -1;
            }
            res+=nTemp;
        }
        return res;
    }

    INT Decoder::decodeVI64(VI64& valueOut)
    {
        valueOut=0;
        for (INT i=0; i<10; i++) {
            U8 uTemp;
            if (decodeU8(uTemp)<0) {
                return -1;
            }
            if (uTemp&0x80) {
                valueOut|=(((VI64)uTemp&0x7F)<<(i*7));
            }
            else {
                valueOut|=(((VI64)uTemp&0x3F)<<(i*7));
                if (uTemp&0x40) {
                    valueOut=-valueOut;
                }
                return (i+1);
            }
        }
        return -1;
    }
    INT Decoder::decodeVI64s(VI64* valuesOut,UNT count)
    {
        INT res=0;
        for (UNT i=0; i<count; i++) {
            INT nTemp=decodeVI64(valuesOut[i]);
            if (nTemp<0) {
                return -1;
            }
            res+=nTemp;
        }
        return res;
    }
    INT Decoder::decodeVU64(VU64& valueOut)
    {
        valueOut=0;
        for (INT i=0; i<10; i++) {
            U8 uTemp;
            if (decodeU8(uTemp)<0) {
                return -1;
            }
            valueOut|=(((VU64)uTemp&0x7F)<<(i*7));

            if (!(uTemp&0x80)) {
                return (i+1);
            }
        }
        return -1;
    }
    INT Decoder::decodeVU64s(VU64* valuesOut,UNT count)
    {
        INT res=0;
        for (UNT i=0; i<count; i++) {
            INT nTemp=decodeVU64(valuesOut[i]);
            if (nTemp<0) {
                return -1;
            }
            res+=nTemp;
        }
        return res;
    }



}




