//
//  GXCoder.cpp
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#include "GXCoder.h"

namespace GX {

    gint bytesOfVI32(gint32 value)
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
    gint bytesOfVU32(guint32 value)
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
    gint bytesOfVI64(gint64 value)
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
    gint bytesOfVU64(guint64 value)
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

	UUID::UUID()
	{
#if GX_PTR_32BIT
		m_Bytes.u32[0] = 0;
		m_Bytes.u32[1] = 0;
		m_Bytes.u32[2] = 0;
		m_Bytes.u32[3] = 0;
#elif GX_PTR_64BIT
		m_Bytes.u64[0] = 0ULL;
		m_Bytes.u64[1] = 0ULL;
#endif
		
	}

	UUID::UUID(const UUID& other)
	{
		m_Bytes.u64[0] = other.m_Bytes.u64[0];
		m_Bytes.u64[1] = other.m_Bytes.u64[1];
	}

	UUID::UUID(guint32 u0, guint32 u1, guint32 u2, guint32 u3)
    {
		m_Bytes.u32[0] = u0;
		m_Bytes.u32[1] = u1;
		m_Bytes.u32[2] = u2;
		m_Bytes.u32[3] = u3;
    }

	UUID::UUID(guint64 u0, guint64 u1)
	{
		m_Bytes.u64[0] = u0;
		m_Bytes.u64[1] = u1;
	}

    UUID::~UUID()
    {

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

#define M_ENCODE(t,rt) \
    gint Encoder::encode##t(rt value)\
    {\
        return encode(&value, sizeof(rt));\
    }\
    gint Encoder::encode##t##s(const rt* values,guint count)\
    {\
        return encode(values, count*sizeof(rt));\
    }

    M_ENCODE(B8,bool);
    M_ENCODE(I8,gint8);
    M_ENCODE(U8,guint8);
    M_ENCODE(I16,gint16);
    M_ENCODE(U16,guint16);
    M_ENCODE(I32,gint32);
    M_ENCODE(U32,guint32);
    M_ENCODE(I64,gint64);
    M_ENCODE(U64,guint64);
    M_ENCODE(F32,gfloat32);
    M_ENCODE(F64,gfloat64);

#undef M_ENCODE

    gint Encoder::encodeVI32(gint32 value)
    {
        guint8 neg=0x0;
        if (value<0) {
            neg=0x40;
            value=-value;
        }
        for (gint i=0; i<5; i++) {
            if(value<=0x3F) {
                if(encodeU8((guint8)(neg|(value&0x3F)))<0) {
                    return -1;
                }
                return (i+1);
            }
            else {
                if(encodeU8((guint8)(0x80|(value&0x7F)))<0) {
                    return -1;
                }
            }
            value>>=7;
        }
        return -1;
    }
    gint Encoder::encodeVI32s(const gint32* values,guint count)
    {
        gint res=0;
        for (guint i=0; i<count; i++) {
            gint nTemp=encodeVI32(values[i]);
            if (nTemp<0) {
                return -1;
            }
            res+=nTemp;
        }
        return res;
    }
    
    gint Encoder::encodeVU32(guint32 value)
    {
        for (guint i=0; i<5; i++) {
            if (value<=0x7F) {
                if(encodeU8((guint8)((value&0x7F)))<0) {
                    return -1;
                }
                return (i+1);
            }
            else {
                if(encodeU8((guint8)(0x80|(value&0x7F)))<0) {
                    return -1;
                }
            }
            value>>=7;
        }
        return -1;
    }
    gint Encoder::encodeVU32s(const guint32* values,guint count)
    {
        gint res=0;
        for (guint i=0; i<count; i++) {
            gint nTemp=encodeVU32(values[i]);
            if (nTemp<0) {
                return -1;
            }
            res+=nTemp;
        }
        return res;
    }

    gint Encoder::encodeVI64(gint64 value)
    {
        guint8 neg=0x0;
        if (value<0) {
            neg=0x40;
            value=-value;
        }
        for (gint i=0; i<10; i++) {
            if(value<=0x3F) {
                if(encodeU8((guint8)(neg|(value&0x3F)))<0) {
                    return -1;
                }
                return (i+1);
            }
            else {
                if(encodeU8((guint8)(0x80|(value&0x7F)))<0) {
                    return -1;
                }
            }

            value>>=7;
        }
        return -1;
    }
    gint Encoder::encodeVI64s(const gint64* values,guint count)
    {
        gint res=0;
        for (guint i=0; i<count; i++) {
            gint nTemp=encodeVI64(values[i]);
            if (nTemp<0) {
                return -1;
            }
            res+=nTemp;
        }
        return res;
    }

    gint Encoder::encodeVU64(guint64 value)
    {
        for (guint i=0; i<10; i++) {
            if (value<=0x7F) {
                if(encodeU8((guint8)((value&0x7F)))<0) {
                    return -1;
                }
                return (i+1);
            }
            else {
                if(encodeU8((guint8)(0x80|(value&0x7F)))<0) {
                    return -1;
                }
            }
            value>>=7;
        }
        return -1;
    }
    gint Encoder::encodeVU64s(const guint64* values,guint count)
    {
        gint res=0;
        for (guint i=0; i<count; i++) {
            gint nTemp=encodeVU64(values[i]);
            if (nTemp<0) {
                return -1;
            }
            res+=nTemp;
        }
        return res;
    }

	gint Encoder::encodeUUID(UUID& value)
	{
		return encode(value.getPtr(), value.getBytes());
	}



    Decoder::Decoder(void* tagPtr) : Coder(tagPtr)
    {
    }

    Decoder::~Decoder()
    {
    }

#define M_DECODE(t,rt) \
    gint Decoder::decode##t(rt& valueOut)\
    {\
        return decode(&valueOut, sizeof(rt));\
    }\
    gint Decoder::decode##t##s(rt* valuesOut,guint count)\
    {\
        return decode(valuesOut, sizeof(rt)*count);\
    }

    M_DECODE(B8,bool);
    M_DECODE(I8,gint8);
    M_DECODE(U8,guint8);
    M_DECODE(I16,gint16);
    M_DECODE(U16,guint16);
    M_DECODE(I32,gint32);
    M_DECODE(U32,guint32);
    M_DECODE(I64,gint64);
    M_DECODE(U64,guint64);
    M_DECODE(F32,gfloat32);
    M_DECODE(F64,gfloat64);

#undef M_DECODE

    gint Decoder::decodeVI32(gint32& valueOut)
    {
        valueOut=0;
        for (gint i=0; i<5; i++) {
            guint8 uTemp;
            if (decodeU8(uTemp)<0) {
                return -1;
            }
            if (uTemp&0x80) {
                valueOut|=(((gint32)uTemp&0x7F)<<(i*7));
            }
            else {
                valueOut|=(((gint32)uTemp&0x3F)<<(i*7));
                if (uTemp&0x40) {
                    valueOut=-valueOut;
                }
                return (i+1);
            }
        }
        return -1;
    }
    gint Decoder::decodeVI32s(gint32* valuesOut,guint count)
    {
        gint res=0;
        for (guint i=0; i<count; i++) {
            gint nTemp=decodeVI32(valuesOut[i]);
            if (nTemp<0) {
                return -1;
            }
            res+=nTemp;
        }
        return res;
    }

    gint Decoder::decodeVU32(guint32& valueOut)
    {
        valueOut=0;
        for (gint i=0; i<5; i++) {
            guint8 uTemp;
            if (decodeU8(uTemp)<0) {
                return -1;
            }
            valueOut|=(((guint32)uTemp&0x7F)<<(i*7));

            if (!(uTemp&0x80)) {
                return (i+1);
            }
        }
        return -1;
    }
    gint Decoder::decodeVU32s(guint32* valuesOut,guint count)
    {
        gint res=0;
        for (guint i=0; i<count; i++) {
            gint nTemp=decodeVU32(valuesOut[i]);
            if (nTemp<0) {
                return -1;
            }
            res+=nTemp;
        }
        return res;
    }

    gint Decoder::decodeVI64(gint64& valueOut)
    {
        valueOut=0;
        for (gint i=0; i<10; i++) {
            guint8 uTemp;
            if (decodeU8(uTemp)<0) {
                return -1;
            }
            if (uTemp&0x80) {
                valueOut|=(((gint64)uTemp&0x7F)<<(i*7));
            }
            else {
                valueOut|=(((gint64)uTemp&0x3F)<<(i*7));
                if (uTemp&0x40) {
                    valueOut=-valueOut;
                }
                return (i+1);
            }
        }
        return -1;
    }
    gint Decoder::decodeVI64s(gint64* valuesOut,guint count)
    {
        gint res=0;
        for (guint i=0; i<count; i++) {
            gint nTemp=decodeVI64(valuesOut[i]);
            if (nTemp<0) {
                return -1;
            }
            res+=nTemp;
        }
        return res;
    }
    gint Decoder::decodeVU64(guint64& valueOut)
    {
        valueOut=0;
        for (gint i=0; i<10; i++) {
            guint8 uTemp;
            if (decodeU8(uTemp)<0) {
                return -1;
            }
            valueOut|=(((guint64)uTemp&0x7F)<<(i*7));

            if (!(uTemp&0x80)) {
                return (i+1);
            }
        }
        return -1;
    }
    gint Decoder::decodeVU64s(guint64* valuesOut,guint count)
    {
        gint res=0;
        for (guint i=0; i<count; i++) {
            gint nTemp=decodeVU64(valuesOut[i]);
            if (nTemp<0) {
                return -1;
            }
            res+=nTemp;
        }
        return res;
    }

	gint Decoder::decodeUUID(UUID& valueOut)
	{
		return decode((void*)valueOut.getPtr(), valueOut.getBytes());
	}

}




