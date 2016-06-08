//
//  GThread.cpp
//  GX
//
//  Created by Gengxin Gu on 16/4/27.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#include "GThread.h"
#include <pthread.h>
#include "GCondition.h"

#if defined(GX_OS_WINDOWS) || defined(Q_OS_WIN)
#include <Windows.h>
#define M_PID_SELF() (*GX_CAST_R(GX::pthread_t*, &pthread_self()))
#define M_TO_PID(pid) (*GX_CAST_R(::pthread_t*, &(pid)))
#else
#include <unistd.h>
#define M_PID_SELF() GX_CAST_R(GX::pthread_t, pthread_self())
#define M_TO_PID(pid) GX_CAST_R(::pthread_t, pid)
#endif

static GThread* g_MT=NULL;
static pthread_key_t tsd_key=0;


GX_OBJECT_IMPLEMENT(GThread::Holder, GObject);

GThread::Holder::Holder()
{
	memset(&m_TID, 0, sizeof(m_TID));
	m_Thread=NULL;
}

GThread::Holder::~Holder()
{
}

void GThread::Holder::detchThread()
{
	pthread_detach(M_TO_PID(m_TID));
}



class _HelperCreateData
{
public:
	_HelperCreateData(GAction* action, GThread::Holder* holder, GCondition* cond) {
		GO::retain(action);
		m_Action = action;
		GO::retain(holder);
		m_Holder = holder;
		m_Cond = cond;
	}
	~_HelperCreateData() {
		GO::release(m_Action);
		GO::release(m_Holder);
	}

	inline void run() {
		m_Action->run();
	}
	
	void setThread() {
		if (m_Cond) {
			m_Holder->m_Thread = GThread::current();
			m_Cond->signal();
		}
	}
private:
	GAction* m_Action;
	GThread::Holder* m_Holder;
	GCondition* m_Cond;
};



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

void GThread::sleep(gint ms)
{
#if defined(GX_OS_WINDOWS) || defined(Q_OS_WIN)
	::Sleep((DWORD)ms);
#else
	usleep((useconds_t)ms * 1000L);
#endif
}


void GThread::detch(GAction* action)
{
	GO::retain(action);

	pthread_t thread_id;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_create(&thread_id, &attr, GThread::detchHelper, action);
	pthread_attr_destroy(&attr);
}
void* GThread::detchHelper(void* action)
{
	GX_CAST_R(GAction*, action)->run();
	GO::release(GX_CAST_R(GAction*, action));
	return NULL;
}
void GThread::detch(GObject* target, GX::Selector selector, GObject* obj)
{
	GAction* action = GAction::alloc();
	action->set(target, selector, obj);
	detch(action);
	GO::release(action);
}
void GThread::detch(GX::Callback cbk, GObject* obj)
{
	GAction* action = GAction::alloc();
	action->set(cbk, obj);
	detch(action);
	GO::release(action);
}

GThread::Holder* GThread::create(GAction* action, bool waitRun)
{
	Holder* holder = Holder::autoAlloc();
	
	if (waitRun) {
		GCondition cond;
		_HelperCreateData* data = new _HelperCreateData(action, holder, &cond);
		pthread_create(GX_CAST_R(pthread_t*, &(holder->m_TID)), NULL, GThread::createHelper, data);
		cond.wait();
	}
	else {
		_HelperCreateData* data = new _HelperCreateData(action, holder, NULL);
		pthread_create(GX_CAST_R(pthread_t*, &(holder->m_TID)), NULL, GThread::createHelper, data);
	}

	return holder;
}
void* GThread::createHelper(void* data)
{
	GX_CAST_R(_HelperCreateData*, data)->setThread();
	GX_CAST_R(_HelperCreateData*, data)->run();
	delete GX_CAST_R(_HelperCreateData*, data);
	return NULL;
}
GThread::Holder* GThread::create(GObject* target, GX::Selector selector, GObject* obj, bool waitRun)
{
	GAction* action = GAction::alloc();
	action->set(target, selector, obj);
	GThread::Holder* res = create(action,waitRun);
	GO::release(action);
	return res;
}
GThread::Holder* GThread::create(GX::Callback cbk, GObject* obj, bool waitRun)
{
	GAction* action = GAction::alloc();
	action->set(cbk, obj);
	GThread::Holder* res = create(action, waitRun);
	GO::release(action);
	return res;
}


void GThread::keyCreate()
{
    pthread_key_create(&tsd_key,keyDestroy);
}
void GThread::keyDestroy(void* p)
{
    delete GX_CAST_R(GThread*, p);
}

GThread::GThread()
{
	m_ID = M_PID_SELF();
    m_RunLoop=NULL;
	m_NoteCenter = NULL;
}

GThread::~GThread()
{
    for (gint i=m_ARObjs.getCount()-1; i>=0; i--) {
        GO::release(m_ARObjs.get(i));
    }
    delete m_RunLoop;
	delete m_NoteCenter;
}

void GThread::setMain()
{
    g_MT=this;
#if defined(GX_NO_PTHREAD_H)
#ifdef GX_DEBUG
	int test=GX::pthread_test;
	test++;
#endif
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
        m_RunLoop=new GRunLoop(this);
    }
    return m_RunLoop;
}

GNoticeCenter* GThread::getNoticeCenter()
{
	if (!m_NoteCenter) {
		m_NoteCenter = new GNoticeCenter();
	}
	return m_NoteCenter;
}





