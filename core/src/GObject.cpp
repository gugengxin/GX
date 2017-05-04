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
#include "GString.h"


static pthread_mutex_t g_Mutex;
static pthread_once_t key_once=PTHREAD_ONCE_INIT;

static void keyCreate()
{
    pthread_mutex_init(&g_Mutex, NULL);
}

typedef struct __ObjExData {
	gint32 refCount;
} _ObjExData;

static inline void _ObjExDataInit(_ObjExData* om)
{
	om->refCount = 1;
}

static inline void _ObjExDataFina(_ObjExData* om)
{
    GX_UNUSED(om)
}



void GObject::retain(GObject* obj)
{
	if (obj) {
		__ObjExData* p = GX_CAST_R(__ObjExData*, obj) - 1;
        
        pthread_once(&key_once,keyCreate);
        pthread_mutex_lock(&g_Mutex);
        
		++p->refCount;
        
        pthread_mutex_unlock(&g_Mutex);
	}
}
void GObject::release(GObject* obj)
{
	if (obj) {
		__ObjExData* p = GX_CAST_R(__ObjExData*, obj) - 1;
        
        pthread_once(&key_once,keyCreate);
        pthread_mutex_lock(&g_Mutex);
		
        --p->refCount;
		
        pthread_mutex_unlock(&g_Mutex);
        
        if (p->refCount <= 0) {
            obj->uninit();
			delete obj;
		}
	}
}
void GObject::autorelease(GObject* obj)
{
    if (obj) {
        GThread::current()->pushARObj(obj);
    }
}

gint32 GObject::refCount(GObject* obj)
{
	if (obj) {
		__ObjExData* p = GX_CAST_R(__ObjExData*, obj) - 1;
		return p->refCount;
	}
	return 0;
}

void* GObject::gmalloc(size_t size)
{
	void* p = malloc(size + sizeof(_ObjExData));
	_ObjExDataInit(GX_CAST_R(_ObjExData*,p));
	return GX_CAST_R(guint8*, p) + sizeof(_ObjExData);
}
void GObject::gfree(void* p)
{
	_ObjExData* exData = GX_CAST_R(_ObjExData*, p) - 1;
	_ObjExDataFina(exData);
	free(exData);
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
    GObject* res=alloc();
    autorelease(res);
    return res;
}
void* GObject::operator new(size_t size)
{
	return gmalloc(size);
}
void GObject::operator delete(void* p)
{
	gfree(p);
}

GObject::GObject()
{
    
}
GObject::~GObject()
{
    
}

void GObject::init()
{
    
}
void GObject::uninit()
{
    //不能做事情，因为引擎内部类没有调用init
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

GString* GObject::description()
{
    GString* res=GString::autoAlloc();
    res->format("%@(%@)").arg(getClass()->getName()).arg(GX_CAST_R(void*, this)).end();
    return res;
}





