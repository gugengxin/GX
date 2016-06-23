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

#include "GXGObject.h"

class GCondition : public GMutex {
	friend class GThread;
	friend class GRunLoop;
    GX_GOBJECT(GCondition);
public:
    void wait();
    void signal();
private:
    GX::pthread_cond_t m_PData;
};

#include "GXGObjectUD.h"

#endif /* GCondition_h */
