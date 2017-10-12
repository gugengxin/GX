//
//  GXCoder.h
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#ifndef GXCoder_h
#define GXCoder_h

#include "GXPrefix.h"


namespace GX {

    gint bytesOfVI32(gint32 value);//不会返回-1，即不会出错
    gint bytesOfVU32(guint32 value);//不会返回-1，即不会出错
    gint bytesOfVI64(gint64 value);//不会返回-1，即不会出错
    gint bytesOfVU64(guint64 value);//不会返回-1，即不会出错

    class UUID {
    public:
		UUID();
		UUID(const UUID& other);
        UUID(guint32 u0, guint32 u1, guint32 u2, guint32 u3);
		UUID(guint64 u0, guint64 u1);
        ~UUID();

		inline const guint8* getPtr() {
			return m_Bytes.u8;
		}
		inline guint getBytes() {
			return sizeof(m_Bytes);
		}

		inline bool operator == (const UUID& other) const {
			return m_Bytes.u64[0] == other.m_Bytes.u64[0] && m_Bytes.u64[1] == other.m_Bytes.u64[1];
		}

		inline bool operator != (const UUID& other) const {
			return m_Bytes.u64[0] != other.m_Bytes.u64[0] || m_Bytes.u64[1] != other.m_Bytes.u64[1];
		}

    private:
        union {
            guint8  u8[16];
            guint16 u16[8];
            guint32 u32[4];
            guint64 u64[2];
        } m_Bytes;
    };


    class Coder {
    public:
        Coder(void* tagPtr);
        ~Coder();

        inline void* getTagPtr() {
            return m_TagPtr;
        }
    private:
        void* m_TagPtr;
    };

    class Encoder : public Coder {
    public:
        Encoder(void* tagPtr);
        ~Encoder();

        virtual gint encode(const void* buf,guint len)=0;//小于len的值都算失败，返回-1
    public:
        gint encodeB8(bool value);
        gint encodeB8s(const bool* values,guint count);
        gint encodeI8(gint8 value);
        gint encodeI8s(const gint8* values,guint count);
        gint encodeU8(guint8 value);
        gint encodeU8s(const guint8* values,guint count);
        gint encodeI16(gint16 value);
        gint encodeI16s(const gint16* values,guint count);
        gint encodeU16(guint16 value);
        gint encodeU16s(const guint16* values,guint count);
        gint encodeI32(gint32 value);
        gint encodeI32s(const gint32* values,guint count);
        gint encodeU32(guint32 value);
        gint encodeU32s(const guint32* values,guint count);
        gint encodeI64(gint64 value);
        gint encodeI64s(const gint64* values,guint count);
        gint encodeU64(guint64 value);
        gint encodeU64s(const guint64* values,guint count);
        gint encodeF32(gfloat32 value);
        gint encodeF32s(const gfloat32* values,guint count);
        gint encodeF64(gfloat64 value);
        gint encodeF64s(const gfloat64* values,guint count);

        gint encodeVI32(gint32 value);//不会出错
        gint encodeVI32s(const gint32* values,guint count);//不会出错
        gint encodeVU32(guint32 value);//不会出错
        gint encodeVU32s(const guint32* values,guint count);//不会出错
        gint encodeVI64(gint64 value);//不会出错
        gint encodeVI64s(const gint64* values,guint count);//不会出错
        gint encodeVU64(guint64 value);//不会出错
        gint encodeVU64s(const guint64* values,guint count);//不会出错

		gint encodeUUID(UUID& value);
    };

    class Decoder : public Coder {
    public:
        Decoder(void* tagPtr);
        ~Decoder();
        
        virtual gint decode(void* buf,guint len)=0;//小于len的值都算失败，返回-1
    public:
        gint decodeB8(bool& valueOut);
        gint decodeB8s(bool* valuesOut,guint count);
        gint decodeI8(gint8& valueOut);
        gint decodeI8s(gint8* valuesOut,guint count);
        gint decodeU8(guint8& valueOut);
        gint decodeU8s(guint8* valuesOut,guint count);
        gint decodeI16(gint16& valueOut);
        gint decodeI16s(gint16* valuesOut,guint count);
        gint decodeU16(guint16& valueOut);
        gint decodeU16s(guint16* valuesOut,guint count);
        gint decodeI32(gint32& valueOut);
        gint decodeI32s(gint32* valuesOut,guint count);
        gint decodeU32(guint32& valueOut);
        gint decodeU32s(guint32* valuesOut,guint count);
        gint decodeI64(gint64& valueOut);
        gint decodeI64s(gint64* valuesOut,guint count);
        gint decodeU64(guint64& valueOut);
        gint decodeU64s(guint64* valuesOut,guint count);
        gint decodeF32(gfloat32& valueOut);
        gint decodeF32s(gfloat32* valuesOut,guint count);
        gint decodeF64(gfloat64& valueOut);
        gint decodeF64s(gfloat64* valuesOut,guint count);

        gint decodeVI32(gint32& valueOut);
        gint decodeVI32s(gint32* valuesOut,guint count);
        gint decodeVU32(guint32& valueOut);
        gint decodeVU32s(guint32* valuesOut,guint count);
        gint decodeVI64(gint64& valueOut);
        gint decodeVI64s(gint64* valuesOut,guint count);
        gint decodeVU64(guint64& valueOut);
        gint decodeVU64s(guint64* valuesOut,guint count);

		gint decodeUUID(UUID& valueOut);
    };

}











#endif /* GXCoder_h */
