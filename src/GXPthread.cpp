//
//  GXPthread.cpp
//  GX
//
//  Created by Gengxin Gu on 16/4/27.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#include "GXPthread.h"
#include <pthread.h>
#ifdef GX_DEBUG
#include <assert.h>
namespace GX {
	static int _Test()
	{
		assert(sizeof(GX::pthread_t) == sizeof(::pthread_t));
		assert(sizeof(GX::pthread_mutex_t) == sizeof(::pthread_mutex_t));
		assert(sizeof(GX::pthread_cond_t) == sizeof(::pthread_cond_t));
		return 0;
	}
	int pthread_test = _Test();
}
#endif