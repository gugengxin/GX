//
//  GThread.cpp
//  GX
//
//  Created by Gengxin Gu on 16/4/27.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#include "GThread.h"
#include <pthread.h>

#if defined(GX_OS_WINDOWS)
#define M_PID_SELF() (*GX_CAST_R(GX::pthread_t*, &pthread_self()))
#else
#define M_PID_SELF() GX_CAST_R(GX::pthread_t, pthread_self())
#endif

static GThread* g_MT=NULL;
static pthread_key_t tsd_key=0;

GThread* GThread::main()
{
    return g_MT;
}

GThread* GThread::current()
{
    static pthread_once_t key_once=PTHREAD_ONCE_INIT;
    pthread_once(&key_once,keyCreate);
    GThread* cur=GX_CAST_R(GThread*, pthread_getspecific(tsd_key));
    if (!cur) {
        cur=new GThread;
        pthread_setspecific(tsd_key, cur);
    }
    
    return cur;
}

void GThread::keyCreate()
{
    pthread_key_create(&tsd_key,keyDestory);
}
void GThread::keyDestory(void* p)
{
    delete GX_CAST_R(GThread*, p);
}

GThread::GThread()
{
	m_ID = M_PID_SELF();
    m_RunLoop=NULL;
}

GThread::~GThread()
{
    for (gint i=m_ARObjs.getCount()-1; i>=0; i--) {
        GO::release(m_ARObjs.get(i));
    }
    delete m_RunLoop;
}

void GThread::setMain()
{
    g_MT=this;
#ifdef GX_DEBUG
	int test=GX::pthread_test;
	test++;
#endif
}

void GThread::pushARObj(GObject* v)
{
    m_ARObjs.add(v);
}

void GThread::popARObj(gint toCount)
{
    for (gint i=m_ARObjs.getCount()-1; i>=toCount; i--) {
        GO::release(m_ARObjs.get(i));
    }
    m_ARObjs.removeFrom(toCount);
}

GRunLoop* GThread::getRunLoop()
{
    if (!m_RunLoop) {
        m_RunLoop=new GRunLoop();
    }
    return m_RunLoop;
}





