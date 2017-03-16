//
//  GAutoreleasePool.cpp
//  GX
//
//  Created by Gengxin Gu on 16/5/3.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#include "GAutoreleasePool.h"
#include "GThread.h"


GAutoreleasePool::GAutoreleasePool()
{
    m_KeyCount=GThread::current()->m_ARObjs.getCount();
}

GAutoreleasePool::~GAutoreleasePool()
{
    GThread::current()->popARObj(m_KeyCount);
}


