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
#if defined(GX_NO_PTHREAD_H)
#include <Windows.h>
#define M_PID_SELF() (*GX_CAST_R(GX::pthread_t*, &pthread_self()))
#define M_PID(pid) (*GX_CAST_R(GX::pthread_t*, &(pid)))
#else
#define M_PID_SELF() GX_CAST_R(GX::pthread_t, pthread_self())
#define M_PID(pid) GX_CAST_R(GX::pthread_t, pid))
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



class _HelperObjData {
public:
	_HelperObjData(GObject* target, GObject::Selector selector, GObject* obj) {
		GO::retain(target);
		m_Target = target;
		m_Selector = selector;
		GO::retain(obj);
		m_Obj = obj;
	}
	~_HelperObjData() {
		GO::release(m_Obj);
		GO::release(m_Target);
	}
	inline void run() {
		(m_Target->*m_Selector)(m_Obj);
	}
private:
	GObject* m_Target;
	GObject::Selector m_Selector;
	GObject* m_Obj;
};

class _HelperFunData {
public:
	_HelperFunData(GThread::Fun fun, GObject* obj) {
		m_Fun = fun;
		GO::retain(obj);
		m_Obj = obj;
	}
	~_HelperFunData() {
		GO::release(m_Obj);
	}
	inline void run() {
		m_Fun(m_Obj);
	}

private:
	GThread::Fun m_Fun;
	GObject* m_Obj;
};

class _CreateData {
public:
	_CreateData(GThread::Holder* holder, GCondition* cond) {
		m_Holder = holder;
		m_Cond = cond;
	}
	~_CreateData() {

	}

	void check

private:
	GThread::Holder* m_Holder;
	GCondition* m_Cond;
};

class _CreateHelperObjData : public _HelperObjData, public _CreateData {
public:
	_CreateHelperObjData(GObject* target, GObject::Selector selector, GObject* obj, GThread::Holder* holder, GCondition* cond) :
		_HelperObjData(target, selector, obj),
		_CreateData(holder, cond)
	{

	}
	~_CreateHelperObjData() {

	}
};

class _CreateHelperFunData : public _HelperFunData, public _CreateData {
public:
	_CreateHelperFunData(GThread::Fun fun, GObject* obj, GThread::Holder* holder, GCondition* cond) :
		_HelperFunData(fun, obj),
		_CreateData(holder, cond)
	{

	}
	~_CreateHelperFunData() {

	}
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
#if defined(GX_OS_WINDOWS)
	::Sleep((DWORD)ms);
#else
	usleep((useconds_t)ms * 1000L);
#endif
}


void GThread::detch(GObject* target, GObject::Selector selector, GObject* obj)
{
	_HelperObjData* data = new _HelperObjData(target, selector, obj);

	pthread_t thread_id;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_create(&thread_id, &attr, GThread::detchHelperObj, data);
	pthread_attr_destroy(&attr);
}
void* GThread::detchHelperObj(void* data)
{
	GX_CAST_R(_HelperObjData*, data)->run();
	delete GX_CAST_R(_HelperObjData*, data);
}


void GThread::detch(Fun fun, GObject* obj)
{
	_HelperFunData* data = new _HelperFunData(fun, obj);

	pthread_t thread_id;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_create(&thread_id, &attr, GThread::detchHelperFun, data);
	pthread_attr_destroy(&attr);
}
void* GThread::detchHelperFun(void* data)
{
	GX_CAST_R(_HelperFunData*, data)->run();
	delete GX_CAST_R(_HelperFunData*, data);
}

GThread::Holder* GThread::create(GObject* target, GObject::Selector selector, GObject* obj, bool waitRun)
{
	Holder* holder = Holder::autoAlloc();

	if (waitRun) {
		GCondition cond;
		_CreateHelperObjData* data = new _CreateHelperObjData(target, selector, obj, holder, &cond);
		pthread_create(GX_CAST_R(pthread_t*, &(holder->m_TID)), NULL, GThread::createHelperObj, data);
		cond.wait();
	}
	else {
		_CreateHelperObjData* data = new _CreateHelperObjData(target, selector, obj, holder, NULL);
		pthread_create(GX_CAST_R(pthread_t*, &(holder->m_TID)), NULL, GThread::createHelperObj, data);
	}

	return holder;
}
void* GThread::createHelperObj(void* data)
{
	if (GX_CAST_R(_CreateHelperObjData*, data)->cond) {
		GX_CAST_R(_CreateHelperObjData*, data)->holder->m_Thread = current();
		GX_CAST_R(_CreateHelperObjData*, data)->cond->signal();
	}
	(GX_CAST_R(_CreateHelperObjData*, data)->run();
	delete (GX_CAST_R(_CreateHelperObjData*, data);
}


GThread::Holder* GThread::create(Fun fun, GObject* obj, bool waitRun)
{
	Holder* holder = Holder::autoAlloc();

	_CreateHelperFunData* data = new _CreateHelperFunData;
	data->fun = fun;
	data->obj = obj;
	data->holder = holder;

	GO::retain(obj);

	if (waitRun) {
		GCondition cond;
		data->cond = &cond;
		pthread_create(GX_CAST_R(pthread_t*, &(holder->m_TID)), NULL, GThread::createHelperFun, data);
		cond.wait();
	}
	else {
		pthread_create(GX_CAST_R(pthread_t*, &(holder->m_TID)), NULL, GThread::createHelperFun, data);
	}

	return holder;
}
void* GThread::createHelperFun(void* data)
{
	if (GX_CAST_R(_CreateHelperFunData*, data)->cond) {
		GX_CAST_R(_CreateHelperFunData*, data)->holder->m_Thread = current();
		GX_CAST_R(_CreateHelperFunData*, data)->cond->signal();
	}
	GX_CAST_R(_CreateHelperFunData*, data)->fun(GX_CAST_R(_CreateHelperFunData*, data)->obj);
	GO::release(GX_CAST_R(_CreateHelperFunData*, data)->obj);
	delete 
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





