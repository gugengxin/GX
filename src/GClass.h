//
//  GClass.hpp
//  GX
//
//  Created by Gengxin Gu on 16/4/19.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GClass_hpp
#define GClass_hpp

#include "GOWHash.h"

class GObject;

class GClass {
public:
    class Initializer {
    public:
        Initializer(GClass* cls);
        ~Initializer();
    };
    friend class GClass::Initializer;
    
    typedef GObject* (*Alloc)();
    
public:
    GClass(const gchar* name,guint size,Alloc alloc,GClass* parent);
    ~GClass();
    
    inline const gchar* getName() {
        return m_Name;
    }
    inline guint getSize() {
        return m_Size;
    }
    inline GClass* getNext() {
        return m_Next;
    }
    inline GClass* getParent() {
        return m_Parent;
    }
public:
    bool isMemberOf(GClass* pClass);
    bool isKindOf(GClass* pClass);
public:
    static GClass* find(const gchar* name);
    static GClass* find(GOWHash::Code hashCode);
    GObject* alloc();
    static GObject* alloc(const gchar* name);
    static GObject* alloc(GOWHash::Code hashCode);
    
private:
    static GClass* map[163];
    
private:
    const gchar*    m_Name;
    GOWHash::Code   m_HashCode;
    guint           m_Size;
    Alloc           m_Alloc;
    GClass*         m_Parent;
    GClass*         m_Next;
};


#define GX_OBJECT_DECLARE(cls,vis) \
vis:\
    cls();\
    virtual ~cls();\
public:\
    static GClass   gclass;\
    virtual GClass* getClass() {\
		return &gclass;\
	}\
    static cls* alloc() {\
		return new cls();\
	}\
	void* operator new(size_t size) {\
		return GObject::gnew(size);\
	}\
	void operator delete(void* p) {\
		GObject::gdel(p);\
	}

#define GX_OBJECT(cls)        GX_OBJECT_DECLARE(cls,protected)
#define GX_OBJECT_FINAL(cls)  GX_OBJECT_DECLARE(cls,private)

#define GX_OBJECT_IMPLEMENT(cls,pc) \
GClass cls::gclass(#cls,sizeof(cls),GX_CAST_R(GClass::Alloc,cls::alloc),&(pc::gclass));\
static GClass::Initializer g_Initializer(&cls::gclass)




#endif /* GClass_hpp */
