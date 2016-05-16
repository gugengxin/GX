﻿//
//  GObject.hpp
//  GX
//
//  Created by Gengxin Gu on 16/4/19.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GObject_hpp
#define GObject_hpp

#include "GXPrefix.h"
#include "GClass.h"

namespace GX {
	typedef void(GObject::*Selector)(GObject*);
	typedef void(*Callback)(GObject*);
}

class GObject {
public:
	static void retain(GObject* obj);
	static void release(GObject* obj);
    static void autorelease(GObject* obj);
	static gint32 refCount(GObject* obj);
protected:
	static void* gnew(size_t size);
	static void gdel(void* p);

    GObject();
    virtual ~GObject();
public:
    static GClass   gclass;
    virtual GClass* getClass();
    static GObject* alloc();
    static GObject* autoAlloc();
	void* operator new(size_t size);
	void operator delete(void* p);
    
    bool  isMemberOfClass(GClass* pClass);
    bool  isMemberOfClass(GClass& cls);
    bool  isKindOfClass(GClass* pClass);
    bool  isKindOfClass(GClass& cls);
public:
    virtual guint getHash();
    virtual bool isEqual(GObject* obj);
public:
//	void exLock();
//	void exUnlock();
};

typedef GObject GO;



#endif /* GObject_hpp */
