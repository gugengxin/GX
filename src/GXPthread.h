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
#ifdef GX_DEBUG
	extern int pthread_test;
#endif
#if defined(GX_OS_WINDOWS)
    typedef struct _pthread_t {
        void * p;
        unsigned int x;
    } pthread_t;
#else
    typedef void* pthread_t;
#endif
    
#if defined(GX_OS_WINDOWS)
	typedef void* pthread_mutex_t;
#else
    typedef struct _pthread_mutex_t {
        long __sig;
#if GX_PTR_32BIT
        char __opaque[40];
#elif GX_PTR_64BIT
        char __opaque[56];
#endif
    } pthread_mutex_t;
#endif
    
#if defined(GX_OS_WINDOWS)
	typedef void* pthread_cond_t;
#else
    typedef struct _pthread_cond_t {
        long __sig;
#if GX_PTR_32BIT
        char __opaque[24];
#elif GX_PTR_64BIT
        char __opaque[40];
#endif
    } pthread_cond_t;
#endif


}

#endif /* GXPthread_h */
