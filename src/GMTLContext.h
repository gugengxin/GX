//
//  GMTLContext.hpp
//  GX
//
//  Created by Gu Gengxin on 16/8/20.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GMTLContext_h
#define GMTLContext_h

#include "GXPrefix.h"

#if defined(GX_METAL)



class GMTLContext {
protected:
    GMTLContext();
    virtual ~GMTLContext();

public:


private:
    
};



typedef GMTLContext GContextBase;

#endif


#endif /* GMTLContext_h */
