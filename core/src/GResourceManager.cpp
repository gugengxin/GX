//
//  GResourceManager.cpp
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#include "GResourceManager.h"


GResourceManager::GResourceManager()
{
    m_MainBundle=GAppBundle::main();
}

GResourceManager::~GResourceManager()
{
    
}

void GResourceManager::addBundle(GBundle* v)
{
    if (v==GAppBundle::main()) {
        m_MainBundle=GX_CAST_R(GAppBundle*, v);
    }
    else {
        m_Bundles.add(v);
    }
}

void GResourceManager::removeBundle(GBundle* v)
{
    if (v==GAppBundle::main()) {
        m_MainBundle=NULL;
    }
    else {
        m_Bundles.remove(v);
    }
}


GObject* GResourceManager::findInMap(gint index,GString* key)
{
    return getMap(index)->get(key);
}

void GResourceManager::addToMap(gint index,GString* key,GObject* obj)
{
    getMap(index)->set(key, obj);
}


