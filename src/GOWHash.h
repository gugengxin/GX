//
//  GOWHash.hpp
//  GX
//
//  Created by Gengxin Gu on 16/4/19.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GOWHash_hpp
#define GOWHash_hpp

#include "GXPrefix.h"

class GOWHash {
public:
    typedef struct _Code {
        gu32 codeA;
        gu32 codeB;
        gu32 codeC;
    } Code;
    
    typedef enum _Type {
        TypeA,
        TypeB,
        TypeC,
    } Type;
    
    static gu32 compute(const gchar* str,Type hashType);
    static Code compute(const gchar* str);
    static Code compute(const gwchar* str);
};

#endif /* GOWHash_hpp */
