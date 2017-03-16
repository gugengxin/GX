//
//  GOWHash.h
//  GX
//
//  Created by Gengxin Gu on 16/4/19.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GOWHash_h
#define GOWHash_h

#include "GXPrefix.h"

class GOWHash {
public:
    typedef struct _Code {
        guint32 codeA;
        guint32 codeB;
        guint32 codeC;
    } Code;
    
    typedef enum _Type {
        TypeA,
        TypeB,
        TypeC,
    } Type;
    
    static guint32 compute(const gchar* str,Type hashType);
    static Code compute(const gchar* str);
    static Code compute(const gwchar* str);
    static Code compute(const guchar* str);
    static bool compare(Code& code0,Code& code1);
};

#endif /* GOWHash_h */
