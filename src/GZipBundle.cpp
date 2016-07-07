﻿//
//  GZipBundle.cpp
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#include "GZipBundle.h"
#include "GZipReader.h"

#include "GXGObject.h"

GX_GOBJECT_IMPLEMENT(GZipBundle, GBundle);

GZipBundle::GZipBundle()
{
    m_Reader=NULL;
}

GZipBundle::~GZipBundle()
{
    GO::release(m_Reader);
}


bool GZipBundle::open(const gtchar* path,bool createMap)
{
    m_Reader=GZipReader::alloc();
    if (!m_Reader->open(path,createMap)) {
        GO::release(m_Reader);
        m_Reader=NULL;
        return false;
    }
    m_RootPath.set(path);
    return true;
}

void GZipBundle::close()
{
    m_Reader.close();
    m_RootPath.clear();
}

GReader* GZipBundle::openReader(const gchar* fileName)
{
    GZipReader* res=NULL;
    
    m_Mutex.lock();
    if (!m_Reader->IsCurrentFileOpened()) {
        if (m_Reader->gotoFile(fileName) && m_Reader->openCurrentFile()) {
            res=m_Reader;
        }
        m_Mutex.unlock();
    }
    else {
        m_Mutex.unlock();
        
        res=GZipReader::alloc();
        if (res->open(m_RootPath.c_str(),false)) {
            if (m_Reader->getMap()) {
                res->setMap(m_Reader->getMap());
            }
            if (!res->gotoFile(sPath) || !res->openCurrentFile()) {
                GO::release(res);
                res=NULL;
            }
        }
        else {
            GO::release(res);
            res=NULL;
        }
    }
    return res;
}
void GZipBundle::closeReader(GReader* reader)
{
    if (reader==m_Reader) {
        m_Mutex.lock();
        m_Reader->closeCurrentFile();
        m_Mutex.unlock();
    }
    else {
        GX_CAST_R(GZipReader*, reader)->closeCurrentFile();
        reader->close();
        GO::release(reader);
    }
}

