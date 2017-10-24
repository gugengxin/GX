//
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
    static const GClass   gclass;\
    virtual const GClass* getClass() {\
		return &gclass;\
	}\
private:\
    static GClass::Initializer gclassInitializer;\
public:\
	void* operator new(size_t size) {\
		return GObject::gnew(size,&gclass);\
	}\
	void operator delete(void* p) {\
		GObject::gdel(p,&gclass);\
	}

#define GX_GOBJECT_DECLARE(cls,vis,avis) \
GX_GOBJECT_DECLARE_BASE(cls,vis)\
avis:\
    static cls* alloc() {\
        cls* res=new cls();\
        res->init();\
        return res;\
	}\
    static cls* autoAlloc() {\
        cls* res=alloc();\
        GObject::autorelease(res);\
        return res;\
    }

#define GX_PRIVATE_GOBJECT_DECLARE(cls,vis,avis) \
GX_GOBJECT_DECLARE_BASE(cls,vis)\
avis:\
	friend class GObject;\
    static cls* alloc() {\
        cls* res=new cls();\
        res->init();\
        return res;\
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
#define GX_FINAL_GOBJECT(cls)    GX_GOBJECT_DECLARE(cls,private,public)
#define GX_PRIVATE_GOBJECT(cls)  GX_PRIVATE_GOBJECT_DECLARE(cls,private,private)
#define GX_VIRTUAL_GOBJECT(cls)  GX_VIRTUAL_GOBJECT_DECLARE(cls,protected,public)

#define GX_GOBJECT_IMPLEMENT_SUGGEST_GNT(cls,pc,suggestGNT) \
const GClass cls::gclass(#cls,sizeof(cls),GX_CAST_R(GClass::Alloc,cls::alloc),&(pc::gclass),GClass::suggestGNT);\
GClass::Initializer cls::gclassInitializer(&cls::gclass)

#define GX_GOBJECT_TEMPLATE_IMPLEMENT_SUGGEST_GNT(T,cls,pc,suggestGNT) \
template <T> \
const GClass cls::gclass(sizeof(cls),reinterpret_cast<GClass::Alloc>(cls::alloc),&(pc::gclass),GClass::suggestGNT)

#define GX_GOBJECT_IMPLEMENT(cls,pc) \
const GClass cls::gclass(#cls,sizeof(cls),GX_CAST_R(GClass::Alloc,cls::alloc),&(pc::gclass),GClass::GNewTypeSmallObj);\
GClass::Initializer cls::gclassInitializer(&cls::gclass)

#define GX_GOBJECT_TEMPLATE_IMPLEMENT(T,cls,pc) \
template <T> \
const GClass cls::gclass(sizeof(cls),reinterpret_cast<GClass::Alloc>(cls::alloc),&(pc::gclass),GClass::GNewTypeSmallObj)




