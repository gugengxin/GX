//
//  GRunLoop.h
//  GX
//
//  Created by Gengxin Gu on 16/4/27.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GRunLoop_h
#define GRunLoop_h

#include "GXPrefix.h"
#include "GObject.h"

class GRunLoop {
    friend class GThread;
public:
	static GRunLoop* current();
private:
	GRunLoop(GThread* td);
    ~GRunLoop();
    
private:
	GThread* m_Thread;
};





#endif /* GRunLoop_h */
