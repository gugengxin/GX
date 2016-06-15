//
//  GClass.h
//  GX
//
//  Created by Gengxin Gu on 16/4/19.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GClass_h
#define GClass_h

#include "GXPrefix.h"

class GObject;

class GClass {
public:
    typedef GObject* (*Alloc)();
public:
    GClass(guint size,Alloc alloc,GClass* parent);
    ~GClass();
    
    inline guint getSize() {
        return m_Size;
    }
    inline GClass* getParent() {
        return m_Parent;
    }
public:
    bool isMemberOf(GClass* pClass);
    bool isKindOf(GClass* pClass);
public:
    GObject* alloc();
    
private:
    guint           m_Size;
    Alloc           m_Alloc;
    GClass*         m_Parent;
};


#define GX_OBJECT_DECLARE(cls,vis,avis) \
vis:\
    cls();\
    virtual ~cls();\
public:\
    static GClass   gclass;\
    virtual GClass* getClass() {\
		return &gclass;\
	}\
avis:\
    static cls* alloc() {\
		return new cls();\
	}\
    static cls* autoAlloc() {\
        cls* res=new cls();\
        GObject::autorelease(res);\
        return res;\
    }\
public:\
	void* operator new(size_t size) {\
		return GObject::gnew(size);\
	}\
	void operator delete(void* p) {\
		GObject::gdel(p);\
	}

#define GX_OBJECT(cls)        GX_OBJECT_DECLARE(cls,protected,public)
#define GX_OBJECT_FINAL(cls)  GX_OBJECT_DECLARE(cls,private,public)

#define GX_OBJECT_IMPLEMENT(cls,pc) \
GClass cls::gclass(sizeof(cls),GX_CAST_R(GClass::Alloc,cls::alloc),&(pc::gclass))

#define GX_OBJECT_TEMPLATE_IMPLEMENT(T,cls,pc) \
template <T> \
GClass cls::gclass(sizeof(cls),reinterpret_cast<GClass::Alloc>(cls::alloc),&(pc::gclass))

#endif /* GClass_h */
