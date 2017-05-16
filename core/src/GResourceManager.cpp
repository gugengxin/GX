//
//  GResourceManager.cpp
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#include "GResourceManager.h"
#include "GNoticeCenter.h"
#include "GApplication.h"


GResourceManager::GResourceManager()
{
    m_MainBundle=GAppBundle::main();
    
    GNoticeCenter::current()->addObserver((GObject*)GApplication::memoryWarningNotification,
                                          GX_CAST_R(GObject*, this),
                                          GX_CAST_R(GX::Selector, &GResourceManager::eventReceivedMemoryWarning));
}

GResourceManager::~GResourceManager()
{
    GNoticeCenter::current()->removeObserver(GX_CAST_R(GObject*, this));
}

bool GResourceManager::addBundle(GBundle* v)
{
    if (!v->isOpened()) {
        return false;
    }
    if (v==GAppBundle::main()) {
        m_MainBundle=GX_CAST_R(GAppBundle*, v);
    }
    else {
        m_Bundles.add(v);
    }
    return true;
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

bool GResourceManager::addFileBundle(const gtchar* path)
{
    bool res=false;
    GFileBundle* bundle=GFileBundle::alloc();
    if (bundle->open(path)) {
        addBundle(bundle);
        res=true;
    }
    GO::release(bundle);
    return res;
}

bool GResourceManager::addZipBundle(const gtchar* path,bool createMap)
{
    bool res=false;
    GZipBundle* bundle=GZipBundle::alloc();
    if (bundle->open(path,createMap)) {
        addBundle(bundle);
        res=true;
    }
    GO::release(bundle);
    return res;
}

GReader* GResourceManager::openReader(GString* fileName,GBundle*& bundleOut)
{
    GReader* res=NULL;
    if (m_MainBundle) {
        res=m_MainBundle->openReader(fileName);
        if (res) {
            bundleOut=m_MainBundle;
            return res;
        }
    }
    
    gint count=m_Bundles.getCount();
    for (gint i=0; i<count; ++i) {
        GBundle* bundle=m_Bundles.get(i);
        res=bundle->openReader(fileName);
        if (res) {
            bundleOut=bundle;
            break;
        }
    }
    
    return res;
}

void GResourceManager::closeReader(GReader* reader,GBundle* bundle)
{
    bundle->closeReader(reader);
}


GObject* GResourceManager::findInMap(gint index,GString* key)
{
    return getMap(index)->get(key);
}

void GResourceManager::addToMap(gint index,GString* key,GObject* obj)
{
    getMap(index)->set(key, obj);
}

void GResourceManager::eventReceivedMemoryWarning(GObject* obj)
{
    gint count=getMapCount();
    for (gint i=0; i<count; i++) {
        getMap(i)->removeAll();
    }
    didReceivedMemoryWarning();
}

