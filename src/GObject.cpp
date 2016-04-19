//
//  GObject.cpp
//  GX
//
//  Created by Gengxin Gu on 16/4/19.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#include "GObject.h"


GClass GObject::gclass("GObject",sizeof(GObject),GX_CAST_R(GClass::Alloc,GObject::alloc),NULL);
static GClass::Initializer g_Initializer(&GObject::gclass);
GClass* GObject::getClass()
{
    return &gclass;
}
GObject* GObject::alloc()
{
    return new GObject();
}

GObject::GObject()
{
    m_RefCount=1;
}
GObject::~GObject()
{
    
}

const gchar* GObject::getClassName()
{
    return getClass()->getName();
}
bool  GObject::isMemberOfClass(GClass* pClass)
{
    return getClass()->isMemberOf(pClass);
}
bool  GObject::isMemberOfClass(GClass& cls)
{
    return getClass()->isMemberOf(&cls);
}
bool  GObject::isKindOfClass(GClass* pClass)
{
    return getClass()->isKindOf(pClass);
}

bool  GObject::isKindOfClass(GClass& cls)
{
    return getClass()->isKindOf(&cls);
}

void GXRetain(GObject* obj)
{
    if (obj) {
        ++obj->m_RefCount;
    }
}
void GXRelease(GObject* obj)
{
    if (obj) {
        --obj->m_RefCount;
        if (obj->m_RefCount<=0) {
            delete obj;
        }
    }
}