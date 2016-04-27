//
//  GMutex.cpp
//  GX
//
//  Created by Gengxin Gu on 16/4/27.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#include "GMutex.h"
#include <pthread.h>


GX_OBJECT_IMPLEMENT(GMutex, GObject);

GMutex::GMutex()
{
    pthread_mutex_init(GX_CAST_R(pthread_mutex_t*, &m_PData), NULL);
}

GMutex::~GMutex()
{
    pthread_mutex_destroy(GX_CAST_R(pthread_mutex_t*, &m_PData));
}


void GMutex::lock()
{
    pthread_mutex_lock(GX_CAST_R(pthread_mutex_t*, &m_PData));
}
void GMutex::unlock()
{
    pthread_mutex_unlock(GX_CAST_R(pthread_mutex_t*, &m_PData));
}


