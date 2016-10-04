//
//  GXCoder.h
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#ifndef GXCoder_h
#define GXCoder_h


#if !defined(GX_PTR_32BIT) && !defined(GX_PTR_64BIT)
#if defined (__LP64__) || defined (__64BIT__) || defined (_LP64) || (__WORDSIZE == 64) || defined(WIN64)
#define GX_PTR_32BIT  0
#define GX_PTR_64BIT  1
#else
#define GX_PTR_32BIT  1
#define GX_PTR_64BIT  0
#endif
#endif


namespace GX {

    typedef bool                B8;
    typedef char                I8;
    typedef unsigned char       U8;
    typedef short               I16;
    typedef unsigned short      U16;
    typedef int                 I32;
    typedef unsigned int        U32;
    typedef long long           I64;
    typedef unsigned long long  U64;
    typedef float               F32;
    typedef double              F64;

    typedef I32 VI32;
    typedef U32 VU32;
    typedef I64 VI64;
    typedef U64 VU64;

#if GX_PTR_32BIT
    typedef I32 INT;
    typedef U32 UNT;
#elif GX_PTR_64BIT
    typedef I64 INT;
    typedef U64 UNT;
#endif

    INT bytesOfVI32(VI32 value);
    INT bytesOfVU32(VU32 value);
    INT bytesOfVI64(VI64 value);
    INT bytesOfVU64(VU64 value);


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

        virtual INT encode(const void* buf,UNT len)=0;//小于len的值都算失败，返回-1
    public:
        INT encodeB8(B8 value);
        INT encodeB8s(const B8* values,UNT count);
        INT encodeI8(I8 value);
        INT encodeI8s(const I8* values,UNT count);
        INT encodeU8(U8 value);
        INT encodeU8s(const U8* values,UNT count);
        INT encodeI16(I16 value);
        INT encodeI16s(const I16* values,UNT count);
        INT encodeU16(U16 value);
        INT encodeU16s(const U16* values,UNT count);
        INT encodeI32(I32 value);
        INT encodeI32s(const I32* values,UNT count);
        INT encodeU32(U32 value);
        INT encodeU32s(const U32* values,UNT count);
        INT encodeI64(I64 value);
        INT encodeI64s(const I64* values,UNT count);
        INT encodeU64(U64 value);
        INT encodeU64s(const U64* values,UNT count);
        INT encodeF32(F32 value);
        INT encodeF32s(const F32* values,UNT count);
        INT encodeF64(F64 value);
        INT encodeF64s(const F64* values,UNT count);

        INT encodeVI32(VI32 value);
        INT encodeVI32s(const VI32* values,UNT count);
        INT encodeVU32(VU32 value);
        INT encodeVU32s(const VU32* values,UNT count);
        INT encodeVI64(VI64 value);
        INT encodeVI64s(const VI64* values,UNT count);
        INT encodeVU64(VU64 value);
        INT encodeVU64s(const VU64* values,UNT count);
    };

    class Decoder : public Coder {
    public:
        Decoder(void* tagPtr);
        ~Decoder();
        
        virtual INT decode(void* buf,UNT len)=0;//小于len的值都算失败，返回-1
    public:
        INT decodeB8(B8& valueOut);
        INT decodeB8s(B8* valuesOut,UNT count);
        INT decodeI8(I8& valueOut);
        INT decodeI8s(I8* valuesOut,UNT count);
        INT decodeU8(U8& valueOut);
        INT decodeU8s(U8* valuesOut,UNT count);
        INT decodeI16(I16& valueOut);
        INT decodeI16s(I16* valuesOut,UNT count);
        INT decodeU16(U16& valueOut);
        INT decodeU16s(U16* valuesOut,UNT count);
        INT decodeI32(I32& valueOut);
        INT decodeI32s(I32* valuesOut,UNT count);
        INT decodeU32(U32& valueOut);
        INT decodeU32s(U32* valuesOut,UNT count);
        INT decodeI64(I64& valueOut);
        INT decodeI64s(I64* valuesOut,UNT count);
        INT decodeU64(U64& valueOut);
        INT decodeU64s(U64* valuesOut,UNT count);
        INT decodeF32(F32& valueOut);
        INT decodeF32s(F32* valuesOut,UNT count);
        INT decodeF64(F64& valueOut);
        INT decodeF64s(F64* valuesOut,UNT count);

        INT decodeVI32(VI32& valueOut);
        INT decodeVI32s(VI32* valuesOut,UNT count);
        INT decodeVU32(VU32& valueOut);
        INT decodeVU32s(VU32* valuesOut,UNT count);
        INT decodeVI64(VI64& valueOut);
        INT decodeVI64s(VI64* valuesOut,UNT count);
        INT decodeVU64(VU64& valueOut);
        INT decodeVU64s(VU64* valuesOut,UNT count);
    };

}











#endif /* GXCoder_h */
