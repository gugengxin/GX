//
//  GCondition.cpp
//  GX
//
//  Created by Gengxin Gu on 16/4/27.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#include "GCondition.h"
#include <pthread.h>


GX_OBJECT_IMPLEMENT(GCondition, GMutex);

GCondition::GCondition()
{
    pthread_cond_init(GX_CAST_R(pthread_cond_t*, &m_PData), NULL);
}

GCondition::~GCondition()
{
    pthread_cond_destroy(GX_CAST_R(pthread_cond_t*, &m_PData));
}

void GCondition::wait()
{
    lock();
    pthread_cond_wait(GX_CAST_R(pthread_cond_t*, &m_PData), GX_CAST_R(pthread_mutex_t*, getMutexPtr()));
    unlock();
}

void GCondition::signal()
{
    lock();
    pthread_cond_signal(GX_CAST_R(pthread_cond_t*, &m_PData));
    unlock();
}