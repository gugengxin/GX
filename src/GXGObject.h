﻿//
//  GXGObject.h
//  GX
//
//  Created by Gengxin Gu on 16/6/23.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#define GX_GOBJECT_DECLARE_BASE(cls,vis) \
vis:\
    cls();\
    virtual ~cls();\
public:\
    static GClass   gclass;\
    virtual GClass* getClass() {\
		return &gclass;\
	}\
public:\
	void* operator new(size_t size) {\
		return GObject::gnew(size);\
	}\
	void operator delete(void* p) {\
		GObject::gdel(p);\
	}

#define GX_GOBJECT_DECLARE(cls,vis,avis) \
GX_GOBJECT_DECLARE_BASE(cls,vis)\
avis:\
    static cls* alloc() {\
        return new cls();\
	}\
    static cls* autoAlloc() {\
        cls* res=alloc();\
        GObject::autorelease(res);\
        return res;\
    }

#define GX_VIRTUAL_GOBJECT_DECLARE(cls,vis,avis) \
GX_GOBJECT_DECLARE_BASE(cls,vis)\
avis:\
    static cls* alloc() {\
		return NULL;\
	}\
    static cls* autoAlloc() {\
        return NULL;\
    }


#define GX_GOBJECT(cls)          GX_GOBJECT_DECLARE(cls,protected,public)
#define GX_GOBJECT_FINAL(cls)    GX_GOBJECT_DECLARE(cls,private,public)
#define GX_VIRTUAL_GOBJECT(cls)  GX_VIRTUAL_GOBJECT_DECLARE(cls,protected,public)

#define GX_GOBJECT_IMPLEMENT(cls,pc) \
GClass cls::gclass(sizeof(cls),GX_CAST_R(GClass::Alloc,cls::alloc),&(pc::gclass))

#define GX_GOBJECT_TEMPLATE_IMPLEMENT(T,cls,pc) \
template <T> \
GClass cls::gclass(sizeof(cls),reinterpret_cast<GClass::Alloc>(cls::alloc),&(pc::gclass))
