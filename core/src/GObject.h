//
//  GObject.h
//  GX
//
//  Created by Gengxin Gu on 16/4/19.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GObject_h
#define GObject_h

#include "GXPrefix.h"
#include "GClass.h"
#include "GXObject.h"

namespace GX {
	typedef void(GObject::*Selector)(GObject*);
	typedef void(*Callback)(GObject*);
}

class GString;

class GObject {
public:
    template <class T> static T* retain(T* obj) {
        return GX_CAST_R(T*, gretain(obj));
    }
    static void release(GObject* obj);
	static gint32 refCount(GObject* obj);
    
    template <class T> static T* autorelease(T* obj) {
        return GX_CAST_R(T*, gautorelease(obj));
    }
protected:
    static GObject* gretain(GObject* obj);
    static GObject* gautorelease(GObject* obj);
	static void* gnew(size_t size,const GClass* gclass);
	static void gdel(void* p,const GClass* gclass);
protected:
    GObject();
    virtual ~GObject();

    virtual void init();
    virtual void dealloc();
public:
    static const GClass gclass;
    virtual const GClass* getClass();
    static GObject* alloc();
    static GObject* autoAlloc();
	void* operator new(size_t size);
	void operator delete(void* p);
    
    bool isMemberOfClass(const GClass* pClass);
    bool isMemberOfClass(const GClass& cls);
    bool isKindOfClass(const GClass* pClass);
    bool isKindOfClass(const GClass& cls);
public:
    virtual guint getHash();
    virtual bool isEqual(GObject* obj);
    virtual GString* description();
};

typedef GObject GO;


#define GX_OBJECT_SET(name,value) GO::retain(value);GO::release(name);name=value
#define GX_MEMBER_GET(t,m) inline t* get##m() const {	return m_##m; }
#define GX_MEMBER_SET(t,m) inline void set##m(t* v) { GX_OBJECT_SET(m_##m,v); }
#define GX_MEMBER_GS(t,m) GX_MEMBER_GET(t,m);GX_MEMBER_SET(t,m)



#endif /* GObject_h */
