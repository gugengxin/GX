//
//  GClass.cpp
//  GX
//
//  Created by Gengxin Gu on 16/4/19.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#include "GClass.h"
#include "GXMemory.h"

const GClass* GClass::map[]={NULL};
#define M_MAP_COUNT (sizeof(map)/sizeof(map[0]))

void GClass::registerToMap(const GClass* pClass)
{
    GX_ASSERT(pClass->m_Name!=NULL);
    
    gint cdIdx=pClass->m_NameCode.codeA%M_MAP_COUNT;
    
    if (map[cdIdx]==NULL) {
        map[cdIdx]=pClass;
    }
    else {
        const GClass* p=map[cdIdx];
        while (p->m_Next) {
            p=p->m_Next;
        }
        GX_CAST_C(GClass*, p)->m_Next=pClass;
    }
}

const GClass* GClass::findInMap(GOWHash::Code nameCode)
{
    const GClass* p=map[nameCode.codeA%M_MAP_COUNT];
    while (p) {
        if (p->m_NameCode.codeB==nameCode.codeB && p->m_NameCode.codeC==nameCode.codeC) {
            return p;
        }
        else {
            p=p->m_Next;
        }
    }
    return NULL;
}

const GClass* GClass::findInMap(const char* name)
{
    return findInMap(GOWHash::compute(name));
}

const GClass* GClass::findInMap(const char* name, gint len)
{
    return findInMap(GOWHash::compute(name,len));
}

GObject* GClass::allocObject(GOWHash::Code nameCode)
{
    const GClass* pClass=findInMap(nameCode);
    if (pClass) {
        return pClass->allocObject();
    }
    return NULL;
}
GObject* GClass::allocObject(const char* name)
{
    const GClass* pClass=findInMap(name);
    if (pClass) {
        return pClass->allocObject();
    }
    return NULL;
}
GObject* GClass::allocObject(const char* name, gint len)
{
    const GClass* pClass=findInMap(name,len);
    if (pClass) {
        return pClass->allocObject();
    }
    return NULL;
}

GClass::GClass(guint size,Alloc alloc,const GClass* parent)
{
    m_Name=NULL;
    GX::gmemset(&m_NameCode, 0, sizeof(m_NameCode));
    m_Size=size;
    m_Alloc=alloc;
    m_Parent=parent;
    m_Next=NULL;
}

GClass::GClass(const char* name,guint size,Alloc alloc,const GClass* parent)
{
    m_Name=name;
    m_NameCode=GOWHash::compute(m_Name);
    m_Size=size;
    m_Alloc=alloc;
    m_Parent=parent;
    m_Next=NULL;
}

GClass::~GClass()
{
}

bool GClass::isMemberOf(const GClass* pClass) const
{
    return this==pClass;
}
bool GClass::isKindOf(const GClass* pClass) const
{
    const GClass* p=this;
    do {
        if (p==pClass) {
            return true;
        }
        p=p->getParent();
    } while (p);
    
    return false;
}

GObject* GClass::allocObject() const
{
    return m_Alloc();
}

GClass::Initializer::Initializer(const GClass* pClass)
{
    GClass::registerToMap(pClass);
}

GClass::Initializer::Initializer()
{
    
}

GClass::Initializer::~Initializer()
{
    
}


