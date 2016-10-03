//
//  GXSerialize.h
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#ifndef GXSerialize_h
#define GXSerialize_h


#define GX_CI16_MAX 0x3FFF
#define GX_CU16_MAX 0x7FFF

#define GX_CI32_MAX 0x1FFFFFFF
#define GX_CU32_MAX 0x3FFFFFFF

#define GX_CI64_MAX 0x1FFFFFFFFFFFFFFFLL
#define GX_CU64_MAX 0x3FFFFFFFFFFFFFFFLL


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
    
    typedef I16 CI16;
    typedef U16 CU16;
    typedef I32 CI32;
    typedef U32 CU32;
    typedef I64 CI64;
    typedef U64 CU64;
    
    
    I32 bytesOfCI16(CI16 value);
    I32 bytesOfCU16(CU16 value);
    I32 bytesOfCI32(CI32 value);
    I32 bytesOfCU32(CU32 value);
    I32 bytesOfCI64(CI64 value);
    I32 bytesOfCU64(CU64 value);
    
    I32 bytesOfCI16(U8 sign);
    I32 bytesOfCU16(U8 sign);
    I32 bytesOfCI32(U8 sign);
    I32 bytesOfCU32(U8 sign);
    I32 bytesOfCI64(U8 sign);
    I32 bytesOfCU64(U8 sign);
    
    B8 encodeCI16(CI16 value,U8* pBuf,U32 bufLen,U32* pLenOut);
    B8 encodeCU16(CU16 value,U8* pBuf,U32 bufLen,U32* pLenOut);
    B8 encodeCI32(CI32 value,U8* pBuf,U32 bufLen,U32* pLenOut);
    B8 encodeCU32(CU32 value,U8* pBuf,U32 bufLen,U32* pLenOut);
    B8 encodeCI64(CI64 value,U8* pBuf,U32 bufLen,U32* pLenOut);
    B8 encodeCU64(CU64 value,U8* pBuf,U32 bufLen,U32* pLenOut);
    
    B8 decodeCI16(U8* pBuf,U32 bufLen,CI16* pValueOut,U32* pLenOut);
    B8 decodeCU16(U8* pBuf,U32 bufLen,CU16* pValueOut,U32* pLenOut);
    B8 decodeCI32(U8* pBuf,U32 bufLen,CI32* pValueOut,U32* pLenOut);
    B8 decodeCU32(U8* pBuf,U32 bufLen,CU32* pValueOut,U32* pLenOut);
    B8 decodeCI64(U8* pBuf,U32 bufLen,CI64* pValueOut,U32* pLenOut);
    B8 decodeCU64(U8* pBuf,U32 bufLen,CU64* pValueOut,U32* pLenOut);
    
}




#endif /* GXSerialize_h */
