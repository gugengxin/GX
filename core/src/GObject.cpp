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
#include "GXMemory.h"


static pthread_mutex_t g_Mutex;
static pthread_once_t key_once=PTHREAD_ONCE_INIT;

static void keyCreate()
{
    pthread_mutex_init(&g_Mutex, NULL);
}

static inline void keyLock()
{
    pthread_once(&key_once,keyCreate);
    pthread_mutex_lock(&g_Mutex);
}

static inline void keyUnlock()
{
    pthread_mutex_unlock(&g_Mutex);
}

///////////////////////////////////////

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

void GObject::release(GObject* obj)
{
    if (obj) {
        __ObjExData* p = GX_CAST_R(__ObjExData*, obj) - 1;
        
        keyLock();
        
        gint32 rc=p->refCount-1;
        if (rc>=0) {
            p->refCount=rc;
        }
        
        keyUnlock();
        
        if (rc == 0) {
            obj->dealloc();
            delete obj;
        }
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

GObject* GObject::gretain(GObject* obj)
{
    if (obj) {
        __ObjExData* p = GX_CAST_R(__ObjExData*, obj) - 1;
        
        keyLock();
        
        ++p->refCount;
        
        keyUnlock();
    }
    return obj;
}

GObject* GObject::gautorelease(GObject* obj)
{
    if (obj) {
        GThread::current()->pushARObj(obj);
    }
    return obj;
}

void* GObject::gnew(size_t size,const GClass* gclass)
{
    void* p = GX_CAST_C(GClass*, gclass)->gnew(size + sizeof(_ObjExData));
	_ObjExDataInit(GX_CAST_R(_ObjExData*,p));
	return GX_CAST_R(guint8*, p) + sizeof(_ObjExData);
}
void GObject::gdel(void* p,const GClass* gclass)
{
	_ObjExData* exData = GX_CAST_R(_ObjExData*, p) - 1;
	_ObjExDataFina(exData);
	GX_CAST_C(GClass*, gclass)->gdel(exData);
}


const GClass GObject::gclass(sizeof(GObject),GX_CAST_R(GClass::Alloc,GObject::alloc),NULL,GClass::GNewTypeDefault);
const GClass* GObject::getClass()
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
	return gnew(size,&gclass);
}
void GObject::operator delete(void* p)
{
	gdel(p,&gclass);
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
void GObject::dealloc()
{
    //不能做事情，因为引擎内部类没有调用init
}

bool  GObject::isMemberOfClass(const GClass* pClass)
{
    return getClass()->isMemberOf(pClass);
}
bool  GObject::isMemberOfClass(const GClass& cls)
{
    return getClass()->isMemberOf(&cls);
}
bool  GObject::isKindOfClass(const GClass* pClass)
{
    return getClass()->isKindOf(pClass);
}

bool  GObject::isKindOfClass(const GClass& cls)
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





