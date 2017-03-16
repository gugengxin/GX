//
//  GClass.cpp
//  GX
//
//  Created by Gengxin Gu on 16/4/19.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#include "GClass.h"

GClass::GClass(guint size,Alloc alloc,GClass* parent)
{
    m_Size=size;
    m_Alloc=alloc;
    m_Parent=parent;
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

GObject* GClass::alloc()
{
    return m_Alloc();
}
