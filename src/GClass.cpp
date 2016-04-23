//
//  GClass.cpp
//  GX
//
//  Created by Gengxin Gu on 16/4/19.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#include "GClass.h"



GClass* GClass::map[163]={NULL};
#define M_MAP_COUNT ((guint32)(sizeof(map)/sizeof(map[0])))

GClass::GClass(const gchar* name,guint size,Alloc alloc,GClass* parent)
{
    m_Name=name;
    m_HashCode.codeA=0;
    m_HashCode.codeB=0;
    m_HashCode.codeC=0;
    m_Size=size;
    m_Alloc=alloc;
    m_Parent=parent;
    m_Next=NULL;
}

GClass::~GClass()
{
    
}

bool GClass::isMemberOf(GClass* pClass)
{
    return this==pClass;
}
bool GClass::isKindOf(GClass* pClass)
{
    GClass* p=this;
    do {
        if (p==pClass) {
            return true;
        }
        p=p->getParent();
    } while (p);
    
    return false;
}

GClass* GClass::find(const gchar* name)
{
    return find(GOWHash::compute(name));
}
GClass* GClass::find(GOWHash::Code hashCode)
{
    GClass* p=map[hashCode.codeA%M_MAP_COUNT];
    while (p) {
        if (p->m_HashCode.codeB==hashCode.codeB && p->m_HashCode.codeC==hashCode.codeC) {
            return p;
        }
        else {
            p=p->m_Next;
        }
    }
    return NULL;
}

GObject* GClass::alloc()
{
    return m_Alloc();
}

GObject* GClass::alloc(const gchar* name)
{
    GClass* cls=find(name);
    if (cls) {
        cls->m_Alloc();
    }
    return NULL;
}

GObject* GClass::alloc(GOWHash::Code hashCode)
{
    GClass* cls=find(hashCode);
    if (cls) {
        cls->m_Alloc();
    }
    return NULL;
}


GClass::Initializer::Initializer(GClass* cls)
{
    cls->m_HashCode=GOWHash::compute(cls->m_Name);
    
    guint32 cdIdx=cls->m_HashCode.codeA%M_MAP_COUNT;
    
    if (map[cdIdx]==NULL) {
        map[cdIdx]=cls;
    }
    else {
        GClass* p=map[cdIdx];
        while (p->m_Next) {
            p=p->m_Next;
        }
        p->m_Next=cls;
    }
}

GClass::Initializer::~Initializer()
{
    
}