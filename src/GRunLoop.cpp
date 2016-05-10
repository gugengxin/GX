//
//  GRunLoop.cpp
//  GX
//
//  Created by Gengxin Gu on 16/4/27.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#include "GRunLoop.h"
#include "GThread.h"

GRunLoop* GRunLoop::current()
{
	return GThread::current()->getRunLoop();
}

GRunLoop::GRunLoop(GThread* td)
{
	m_Thread = td;
}

GRunLoop::~GRunLoop()
{

}

