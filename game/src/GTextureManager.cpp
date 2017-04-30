//
//  GTextureManager.cpp
//  GX
//
//  Created by GuGengxin.
//  Copyright by gxengine.com
//

#include "GTextureManager.h"
#include "GContext.h"


GTextureManager* GTextureManager::shared(GContext* context)
{
    return &(context->m_TextureManager);
}

GTextureManager::GTextureManager(GContext* context) : GResourceManager()
{
    m_Context=context;
}

GTextureManager::~GTextureManager()
{
    
}

GTexture2D* GTextureManager::load2D(GString* name,GString* exName)
{
    GTexture2D* res=NULL;
    
    GString* str=GString::alloc();
    
    str->format("%@");
    
    
    GO::release(str);
    return res;
}

GMap<GString, GObject>* GTextureManager::getMap(gint index)
{
    return &(m_Maps[index]);
}


