//
//  GObject.cpp
//  GX
//
//  Created by Gengxin Gu on 16/4/19.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#include "GObject.h"
#include "GThread.h"
#include <pthread.h>

class _ObjMutex {
public:
	_ObjMutex() {
		pthread_mutex_init(&m_PData, NULL);
	}
	~_ObjMutex() {
		pthread_mutex_destroy(&m_PData);
	}
	inline void lock() {
		pthread_mutex_lock(GX_CAST_R(pthread_mutex_t*, &m_PData));
	}
	inline void unlock() {
		pthread_mutex_unlock(GX_CAST_R(pthread_mutex_t*, &m_PData));
	}
private:
	pthread_mutex_t m_PData;
};

static _ObjMutex g_ObjMutex;


void GObject::retain(GObject* obj)
{
	g_ObjMutex.lock();
	if (obj) {
		++(*((GX_CAST_R(gint32*, obj) - 1)));
	}
	g_ObjMutex.unlock();
}
void GObject::release(GObject* obj)
{
	g_ObjMutex.lock();
	if (obj) {
		gint32* p = GX_CAST_R(gint32*, obj) - 1;
		--(*p);
		if ((*p) <= 0) {
			delete obj;
		}
	}
	g_ObjMutex.unlock();
}
void GObject::autorelease(GObject* obj)
{
    if (obj) {
        GThread::current()->pushARObj(obj);
    }
}
void* GObject::gnew(size_t size)
{
	void* p = malloc(size+sizeof(gint32));
	*GX_CAST_R(gint32*, p) = 1;
	return GX_CAST_R(gint32*, p) + 1;
}
void GObject::gdel(void* p)
{
	free(GX_CAST_R(gint32*, p) - 1);
}


GClass GObject::gclass(sizeof(GObject),GX_CAST_R(GClass::Alloc,GObject::alloc),NULL);
GClass* GObject::getClass()
{
    return &gclass;
}
GObject* GObject::alloc()
{
    return new GObject();
}
GObject* GObject::autoAlloc()
{
    GObject* res=new GObject();
    autorelease(res);
    return res;
}
void* GObject::operator new(size_t size)
{
	return gnew(size);
}
void GObject::operator delete(void* p)
{
	gdel(p);
}

GObject::GObject()
{
    
}
GObject::~GObject()
{
    
}

bool  GObject::isMemberOfClass(GClass* pClass)
{
    return getClass()->isMemberOf(pClass);
}
bool  GObject::isMemberOfClass(GClass& cls)
{
    return getClass()->isMemberOf(&cls);
}
bool  GObject::isKindOfClass(GClass* pClass)
{
    return getClass()->isKindOf(pClass);
}

bool  GObject::isKindOfClass(GClass& cls)
{
    return getClass()->isKindOf(&cls);
}

guint GObject::getHash()
{
    return GX_CAST_R(guint, this);
}

bool GObject::isEqual(GObject* obj)
{
    return this==obj;
}








