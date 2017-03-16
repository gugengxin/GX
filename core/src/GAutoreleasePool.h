//
//  GAutoreleasePool.h
//  GX
//
//  Created by Gengxin Gu on 16/5/3.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GAutoreleasePool_h
#define GAutoreleasePool_h

#include "GXPrefix.h"
#include "GDataArray.h"


class GAutoreleasePool {
public:
    GAutoreleasePool();
    ~GAutoreleasePool();
private:
    gint m_KeyCount;
};

#endif /* GAutoreleasePool_h */
