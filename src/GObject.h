//
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

class GObject {
public:
	static void retain(GObject* obj);
	static void release(GObject* obj);
protected:
	static void* gnew(size_t size);
	static void gdel(void* p);

    GObject();
    virtual ~GObject();
public:
    static GClass   gclass;
    virtual GClass* getClass();
    static GObject* alloc();
	void* operator new(size_t size);
	void operator delete(void* p);
    
    const gchar* getClassName();
    bool  isMemberOfClass(GClass* pClass);
    bool  isMemberOfClass(GClass& cls);
    bool  isKindOfClass(GClass* pClass);
    bool  isKindOfClass(GClass& cls);
};

typedef GObject GO;



#endif /* GObject_hpp */
