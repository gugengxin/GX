//
//  GXPthread.h
//  GX
//
//  Created by Gengxin Gu on 16/4/27.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GXPthread_h
#define GXPthread_h

#include "GXPrefix.h"

namespace GX {
    
    typedef struct _pthread_mutex_t {
        long __sig;
        char __opaque[56];
    } pthread_mutex_t;
    
    typedef struct _pthread_cond_t {
        long __sig;
        char __opaque[40];
    } pthread_cond_t;

#if defined(GX_OS_WINDOWS)
	typedef struct _ptw32_handle_t {
		void * p;      
		unsigned int x;
	} ptw32_handle_t;
#endif
}

#endif /* GXPthread_h */
