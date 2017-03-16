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

#if defined(GX_OS_WINDOWS) || defined(GX_OS_QT_WINDOWS)
#define GX_NO_PTHREAD_H
#else
#include <pthread.h>
#endif

namespace GX {


#if defined(GX_NO_PTHREAD_H)

#ifdef GX_DEBUG
    extern int pthread_test;
#endif

#if defined(GX_OS_WINDOWS) || defined(GX_OS_QT_WINDOWS)
    typedef struct _pthread_t {
        void * p;
        unsigned int x;
    } pthread_t;
    typedef void* pthread_mutex_t;
    typedef void* pthread_cond_t;
#endif

#else

    typedef ::pthread_t pthread_t;
    typedef ::pthread_mutex_t pthread_mutex_t;
    typedef ::pthread_cond_t pthread_cond_t;

#endif


}

#endif /* GXPthread_h */
