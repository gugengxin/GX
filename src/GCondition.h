//
//  GCondition.h
//  GX
//
//  Created by Gengxin Gu on 16/4/27.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GCondition_h
#define GCondition_h

#include "GXPrefix.h"
#include "GMutex.h"

class GCondition : protected GMutex {
	friend class GThread;
    GX_OBJECT(GCondition);
public:
    void wait();
    void signal();
private:
    GX::pthread_cond_t m_PData;
};

#endif /* GCondition_h */
