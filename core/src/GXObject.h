//
//  GXObject.h
//  GX
//
//  Created by Gengxin Gu on 16/6/23.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GXObject_h
#define GXObject_h

#define GX_OBJECT_INIT_DECLARE  virtual void init();

#define GX_OBJECT_DECLARE_BASE(cls,vis,it) \
vis:\
    cls() {}\
    virtual ~cls() {}\
protected:\
    it\
    virtual void dealloc();\
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

#define GX_OBJECT_DECLARE(cls,vis,avis,it) \
GX_OBJECT_DECLARE_BASE(cls,vis,it)\
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

#define GX_PRIVATE_OBJECT_DECLARE(cls,vis,avis,it) \
GX_OBJECT_DECLARE_BASE(cls,vis,it)\
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

#define GX_VIRTUAL_OBJECT_DECLARE(cls,vis,avis,it) \
GX_OBJECT_DECLARE_BASE(cls,vis,it)\
avis:\
    static cls* alloc() {\
		return NULL;\
	}\
    static cls* autoAlloc() {\
        return NULL;\
    }


#define GX_OBJECT(cls)          GX_OBJECT_DECLARE(cls,protected,public,)
#define GX_FINAL_OBJECT(cls)    GX_OBJECT_DECLARE(cls,private,public,)
#define GX_PRIVATE_OBJECT(cls)  GX_PRIVATE_OBJECT_DECLARE(cls,private,private,)
#define GX_VIRTUAL_OBJECT(cls)  GX_VIRTUAL_OBJECT_DECLARE(cls,protected,public,)

#define GX_OBJECT_DIT(cls)          GX_OBJECT_DECLARE(cls,protected,public,GX_OBJECT_INIT_DECLARE)
#define GX_FINAL_OBJECT_DIT(cls)    GX_OBJECT_DECLARE(cls,private,public,GX_OBJECT_INIT_DECLARE)
#define GX_PRIVATE_OBJECT_DIT(cls)  GX_PRIVATE_OBJECT_DECLARE(cls,private,private,GX_OBJECT_INIT_DECLARE)
#define GX_VIRTUAL_OBJECT_DIT(cls)  GX_VIRTUAL_OBJECT_DECLARE(cls,protected,public,GX_OBJECT_INIT_DECLARE)

#define GX_OBJECT_IMPLEMENT_SUGGEST_GNT(cls,pc,suggestGNT) \
const GClass cls::gclass(#cls,sizeof(cls),GX_CAST_R(GClass::Alloc,cls::alloc),&(pc::gclass),suggestGNT);\
GClass::Initializer cls::gclassInitializer(&cls::gclass)

#define GX_OBJECT_TEMPLATE_IMPLEMENT_SUGGEST_GNT(T,cls,pc,suggestGNT) \
template <T> \
const GClass cls::gclass(sizeof(cls),reinterpret_cast<GClass::Alloc>(cls::alloc),&(pc::gclass),suggestGNT)

#define GX_OBJECT_IMPLEMENT(cls,pc) \
const GClass cls::gclass(#cls,sizeof(cls),GX_CAST_R(GClass::Alloc,cls::alloc),&(pc::gclass),GClass::GNewTypeSmallObj);\
GClass::Initializer cls::gclassInitializer(&cls::gclass)

#define GX_OBJECT_TEMPLATE_IMPLEMENT(T,cls,pc) \
template <T> \
const GClass cls::gclass(sizeof(cls),reinterpret_cast<GClass::Alloc>(cls::alloc),&(pc::gclass),GClass::GNewTypeSmallObj)



#endif /* GXObject_h */
