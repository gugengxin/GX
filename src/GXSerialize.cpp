//
//  GXSerialize.cpp
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#include "GXSerialize.h"


namespace GX {
    
    I32 bytesOfCI16(CI16 value)
    {
        if (value<0) {
            value=-value;
        }
        if (value<=0x3F) {
            return 1;
        }
        else if(value<=0x3FFF)
        {
            return 2;
        }
        return -1;
    }
    I32 bytesOfCU16(CU16 value)
    {
        if (value<=0x7F) {
            return 1;
        }
        else if(value<=0x7FFF)
        {
            return 2;
        }
        return -1;
    }
    I32 bytesOfCI32(CI32 value)
    {
        if (value<0) {
            value=-value;
        }
        if (value<=0x1F) {
            return 1;
        }
        else if(value<=0x1FFF) {
            return 2;
        }
        else if(value<=0x1FFFFF) {
            return 3;
        }
        else if(value<=0x1FFFFFFF)
        {
            return 4;
        }
        return -1;
    }
    I32 bytesOfCU32(CU32 value)
    {
        if (value<=0x3F) {
            return 1;
        }
        else if(value<=0x3FFF) {
            return 2;
        }
        else if(value<=0x3FFFFF) {
            return 3;
        }
        else if(value<=0x3FFFFFFF)
        {
            return 4;
        }
        return -1;
    }
    I32 bytesOfCI64(CI64 value)
    {
        if (value<0) {
            value=-value;
        }
        if (value<=0x1F) {
            return 1;
        }
        else if(value<=0x1FFF) {
            return 2;
        }
        else if(value<=0x1FFFFFFF) {
            return 4;
        }
        else if(value<=0x1FFFFFFFFFFFFFFFLL)
        {
            return 8;
        }
        return -1;
    }
    I32 bytesOfCU64(CU64 value)
    {
        if (value<=0x3F) {
            return 1;
        }
        else if(value<=0x3FFF) {
            return 2;
        }
        else if(value<=0x3FFFFFFF) {
            return 4;
        }
        else if(value<=0x3FFFFFFFFFFFFFFFLL)
        {
            return 8;
        }
        return -1;
    }
    
    I32 bytesOfCI16(U8 sign)
    {
        return (sign>>7)+1;
    }
    I32 bytesOfCU16(U8 sign)
    {
        return (sign>>7)+1;
    }
    I32 bytesOfCI32(U8 sign)
    {
        return (sign>>6)+1;
    }
    I32 bytesOfCU32(U8 sign)
    {
        return (sign>>6)+1;
    }
    I32 bytesOfCI64(U8 sign)
    {
        I8 res[]={1,2,4,8};
        return (I32)res[(sign>>6)];
    }
    I32 bytesOfCU64(U8 sign)
    {
        I8 res[]={1,2,4,8};
        return (I32)res[(sign>>6)];
    }
    
    
    B8 encodeCI16(CI16 value,U8* pBuf,U32 bufLen,U32* pLenOut)
    {
        U8 isNeg=0;
        if (value<0) {
            isNeg=0x40;
            value=-value;
        }
        
        if (value<=0x3F) {
            if (bufLen<1) {
                return false;
            }
            (*pBuf)=value|isNeg;
            (*pLenOut)=1;
        }
        else if(value<=0x3FFF) {
            if (bufLen<2) {
                return false;
            }
            pBuf[0]=0x80 | isNeg | (value>>8);
            pBuf[1]=value&0xFF;
            (*pLenOut)=2;
        }
        else {
            return false;
        }
        
        return true;
    }
    B8 encodeCU16(CU16 value,U8* pBuf,U32 bufLen,U32* pLenOut)
    {
        if (value<=0x7F) {
            if (bufLen<1) {
                return false;
            }
            (*pBuf)=(U8)value;
            (*pLenOut)=1;
        }
        else if(value<=0x7FFF) {
            if (bufLen<2) {
                return false;
            }
            pBuf[0]=0x80 | (value>>8);
            pBuf[1]=value&0xFF;
            (*pLenOut)=2;
        }
        else {
            return false;
        }
        return true;
    }
    B8 encodeCI32(CI32 value,U8* pBuf,U32 bufLen,U32* pLenOut)
    {
        U8 isNeg=0;
        if (value<0) {
            isNeg=0x20;
            value=-value;
        }
        
        if (value<=0x1F) {
            if (bufLen<1) {
                return false;
            }
            (*pBuf)=value|isNeg;
            (*pLenOut)=1;
        }
        else if(value<=0x1FFF) {
            if (bufLen<2) {
                return false;
            }
            pBuf[0]=0x40 | isNeg | (value>>8);
            pBuf[1]=value&0xFF;
            (*pLenOut)=2;
        }
        else if(value<=0x1FFFFF) {
            if (bufLen<3) {
                return false;
            }
            pBuf[0]=0x80 | isNeg | (value>>16);
            pBuf[1]=(value>>8)&0xFF;
            pBuf[2]=value&0xFF;
            (*pLenOut)=3;
        }
        else if(value<=0x1FFFFFFF) {
            if (bufLen<4) {
                return false;
            }
            pBuf[0]=0xC0 | isNeg | (value>>24);
            pBuf[1]=(value>>16)&0xFF;
            pBuf[2]=(value>>8)&0xFF;
            pBuf[3]=value&0xFF;
            (*pLenOut)=4;
        }
        else {
            return false;
        }
        
        return true;
    }
    B8 encodeCU32(CU32 value,U8* pBuf,U32 bufLen,U32* pLenOut)
    {
        if (value<=0x3F) {
            if (bufLen<1) {
                return false;
            }
            (*pBuf)=value;
            (*pLenOut)=1;
        }
        else if(value<=0x3FFF) {
            if (bufLen<2) {
                return false;
            }
            pBuf[0]=0x40 | (value>>8);
            pBuf[1]=value&0xFF;
            (*pLenOut)=2;
        }
        else if(value<=0x3FFFFF) {
            if (bufLen<3) {
                return false;
            }
            pBuf[0]=0x80 | (value>>16);
            pBuf[1]=(value>>8)&0xFF;
            pBuf[2]=value&0xFF;
            (*pLenOut)=3;
        }
        else if(value<=0x3FFFFFFF) {
            if (bufLen<4) {
                return false;
            }
            pBuf[0]=0xC0 | (value>>24);
            pBuf[1]=(value>>16)&0xFF;
            pBuf[2]=(value>>8)&0xFF;
            pBuf[3]=value&0xFF;
            (*pLenOut)=4;
        }
        else {
            return false;
        }
        return true;
    }
    B8 encodeCI64(CI64 value,U8* pBuf,U32 bufLen,U32* pLenOut)
    {
        U8 isNeg=0;
        if (value<0) {
            isNeg=0x20;
            value=-value;
        }
        
        if (value<=0x1F) {
            if (bufLen<1) {
                return false;
            }
            (*pBuf)=(U8)(value|isNeg);
            (*pLenOut)=1;
        }
        else if(value<=0x1FFF) {
            if (bufLen<2) {
                return false;
            }
            pBuf[0]=(U8)(0x40 | isNeg | (value>>8));
            pBuf[1]=value&0xFF;
            (*pLenOut)=2;
        }
        else if(value<=0x1FFFFFFF) {
            if (bufLen<4) {
                return false;
            }
            pBuf[0]=(U8)(0x80 | isNeg | (value>>24));
            pBuf[1]=(value>>16)&0xFF;
            pBuf[2]=(value>>8)&0xFF;
            pBuf[3]=value&0xFF;
            (*pLenOut)=4;
        }
        else if(value<=0x1FFFFFFFFFFFFFFFLL) {
            if (bufLen<8) {
                return false;
            }
            pBuf[0]=0xC0 | isNeg | (value>>56);
            pBuf[1]=(value>>48)&0xFF;
            pBuf[2]=(value>>40)&0xFF;
            pBuf[3]=(value>>32)&0xFF;
            pBuf[4]=(value>>24)&0xFF;
            pBuf[5]=(value>>16)&0xFF;
            pBuf[6]=(value>>8)&0xFF;
            pBuf[7]=value&0xFF;
            
            (*pLenOut)=8;
        }
        else {
            return false;
        }
        
        return true;
    }
    B8 encodeCU64(CU64 value,U8* pBuf,U32 bufLen,U32* pLenOut)
    {
        if (value<=0x3F) {
            if (bufLen<1) {
                return false;
            }
            (*pBuf)=(U8)value;
            (*pLenOut)=1;
        }
        else if(value<=0x3FFF) {
            if (bufLen<2) {
                return false;
            }
            pBuf[0]=(U8)(0x40 | (value>>8));
            pBuf[1]=value&0xFF;
            (*pLenOut)=2;
        }
        else if(value<=0x3FFFFFFF) {
            if (bufLen<4) {
                return false;
            }
            pBuf[0]=(U8)(0x80 | (value>>24));
            pBuf[1]=(value>>16)&0xFF;
            pBuf[2]=(value>>8)&0xFF;
            pBuf[3]=value&0xFF;
            (*pLenOut)=4;
        }
        else if(value<=0x3FFFFFFFFFFFFFFFLL) {
            if (bufLen<8) {
                return false;
            }
            pBuf[0]=0xC0 | (value>>56);
            pBuf[1]=(value>>48)&0xFF;
            pBuf[2]=(value>>40)&0xFF;
            pBuf[3]=(value>>32)&0xFF;
            pBuf[4]=(value>>24)&0xFF;
            pBuf[5]=(value>>16)&0xFF;
            pBuf[6]=(value>>8)&0xFF;
            pBuf[7]=value&0xFF;
            (*pLenOut)=8;
        }
        else {
            return false;
        }
        return true;
    }
    
    B8 decodeCI16(U8* pBuf,U32 bufLen,CI16* pValueOut,U32* pLenOut)
    {
        if (bufLen<1) {
            return false;
        }
        U8 num=((*pBuf)>>7);
        U8 isNeg=(((*pBuf)>>6)&1);
        
        if (num==0) {
            (*pLenOut)=1;
            (*pValueOut)=((*pBuf)&0x3F);
            if (isNeg) {
                (*pValueOut)=-(*pValueOut);
            }
        }
        else //if(num==1)
        {
            if (bufLen<2) {
                return false;
            }
            (*pLenOut)=2;
            (*pValueOut)= ((pBuf[0]&0x3F)<<8) | pBuf[1];
            if (isNeg) {
                (*pValueOut)=-(*pValueOut);
            }
        }
        return true;
    }
    B8 decodeCU16(U8* pBuf,U32 bufLen,CU16* pValueOut,U32* pLenOut)
    {
        if (bufLen<1) {
            return false;
        }
        U8 num=((*pBuf)>>7);
        
        if (num==0) {
            (*pLenOut)=1;
            (*pValueOut)=((*pBuf)&0x7F);
        }
        else if(num==1)
        {
            if (bufLen<2) {
                return false;
            }
            (*pLenOut)=2;
            (*pValueOut)= ((pBuf[0]&0x7F)<<8) | pBuf[1];
        }
        return true;
    }
    B8 decodeCI32(U8* pBuf,U32 bufLen,CI32* pValueOut,U32* pLenOut)
    {
        if (bufLen<1) {
            return false;
        }
        U8 num=((*pBuf)>>6);
        U8 isNeg=(((*pBuf)>>5)&1);
        
        if (num==0) {
            (*pLenOut)=1;
            (*pValueOut)=((*pBuf)&0x1F);
            if (isNeg) {
                (*pValueOut)=-(*pValueOut);
            }
        }
        else if(num==1) {
            if (bufLen<2) {
                return false;
            }
            (*pLenOut)=2;
            (*pValueOut)= ((pBuf[0]&0x1F)<<8) | pBuf[1];
            if (isNeg) {
                (*pValueOut)=-(*pValueOut);
            }
        }
        else if(num==2) {
            if (bufLen<3) {
                return false;
            }
            (*pLenOut)=3;
            (*pValueOut)= ((pBuf[0]&0x1F)<<16) | (pBuf[1]<<8) | pBuf[2];
            if (isNeg) {
                (*pValueOut)=-(*pValueOut);
            }
        }
        else {
            if (bufLen<4) {
                return false;
            }
            (*pLenOut)=4;
            (*pValueOut)= ((pBuf[0]&0x1F)<<24) | (pBuf[1]<<16) | (pBuf[2]<<8) | pBuf[3];
            if (isNeg) {
                (*pValueOut)=-(*pValueOut);
            }
        }
        return true;
    }
    B8 decodeCU32(U8* pBuf,U32 bufLen,CU32* pValueOut,U32* pLenOut)
    {
        if (bufLen<1) {
            return false;
        }
        U8 num=((*pBuf)>>6);
        
        if (num==0) {
            (*pLenOut)=1;
            (*pValueOut)=((*pBuf)&0x3F);
        }
        else if(num==1) {
            if (bufLen<2) {
                return false;
            }
            (*pLenOut)=2;
            (*pValueOut)= ((pBuf[0]&0x3F)<<8) | pBuf[1];
        }
        else if(num==2) {
            if (bufLen<3) {
                return false;
            }
            (*pLenOut)=3;
            (*pValueOut)= ((pBuf[0]&0x3F)<<16) | (pBuf[1]<<8) | pBuf[2];
        }
        else {
            if (bufLen<4) {
                return false;
            }
            (*pLenOut)=4;
            (*pValueOut)= ((pBuf[0]&0x3F)<<24) | (pBuf[1]<<16) | (pBuf[2]<<8) | pBuf[3];
        }
        return true;
    }
    B8 decodeCI64(U8* pBuf,U32 bufLen,CI64* pValueOut,U32* pLenOut)
    {
        if (bufLen<1) {
            return false;
        }
        U8 num=((*pBuf)>>6);
        U8 isNeg=(((*pBuf)>>5)&1);
        
        if (num==0) {
            (*pLenOut)=1;
            (*pValueOut)=((*pBuf)&0x1F);
            if (isNeg) {
                (*pValueOut)=-(*pValueOut);
            }
        }
        else if(num==1) {
            if (bufLen<2) {
                return false;
            }
            (*pLenOut)=2;
            (*pValueOut)= ((pBuf[0]&0x1F)<<8) | pBuf[1];
            if (isNeg) {
                (*pValueOut)=-(*pValueOut);
            }
        }
        else if(num==2) {
            if (bufLen<4) {
                return false;
            }
            (*pLenOut)=4;
            (*pValueOut)= ((pBuf[0]&0x1F)<<24) | (pBuf[1]<<16) | (pBuf[2]<<8) | pBuf[3];
            if (isNeg) {
                (*pValueOut)=-(*pValueOut);
            }
        }
        else {
            if (bufLen<8) {
                return false;
            }
            (*pLenOut)=8;
            (*pValueOut)= ((pBuf[0]&0x1FLL)<<56) |
            (((U64)pBuf[1])<<48) |
            (((U64)pBuf[2])<<40) |
            (((U64)pBuf[3])<<32) |
            (((U64)pBuf[4])<<24) |
            (((U64)pBuf[5])<<16) |
            (((U64)pBuf[6])<<8) |
            ((U64)pBuf[7]);
            if (isNeg) {
                (*pValueOut)=-(*pValueOut);
            }
        }
        return true;
    }
    B8 decodeCU64(U8* pBuf,U32 bufLen,CU64* pValueOut,U32* pLenOut)
    {
        if (bufLen<1) {
            return false;
        }
        U8 num=((*pBuf)>>6);
        
        if (num==0) {
            (*pLenOut)=1;
            (*pValueOut)=((*pBuf)&0x3F);
        }
        else if(num==1) {
            if (bufLen<2) {
                return false;
            }
            (*pLenOut)=2;
            (*pValueOut)= ((pBuf[0]&0x3F)<<8) | pBuf[1];
        }
        else if(num==2) {
            if (bufLen<4) {
                return false;
            }
            (*pLenOut)=4;
            (*pValueOut)= ((pBuf[0]&0x3F)<<24) | (pBuf[1]<<16) | (pBuf[2]<<8) | pBuf[3];
        }
        else {
            if (bufLen<8) {
                return false;
            }
            (*pLenOut)=8;
            (*pValueOut)= ((pBuf[0]&0x3FLL)<<56) |
            (((U64)pBuf[1])<<48) |
            (((U64)pBuf[2])<<40) |
            (((U64)pBuf[3])<<32) |
            (((U64)pBuf[4])<<24) |
            (((U64)pBuf[5])<<16) |
            (((U64)pBuf[6])<<8) |
            ((U64)pBuf[7]);
        }
        return true;
    }
    
}




