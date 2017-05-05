//
//  GTextureManager.cpp
//  GX
//
//  Created by GuGengxin.
//  Copyright by gxengine.com
//

#include "GTextureManager.h"
#include "GContext.h"
#include "GWindow.h"


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

GTexture2D* GTextureManager::load2D(GString* name,GDib::FileType suggestFT,GTexture2D::Parameter* param)
{
    GTexture2D* res=GX_CAST_R(GTexture2D*, findInMap(MapTex2D, name));
    if (!res) {
        GBundle* bundle=NULL;
        GReader* reader=openReader(name, bundle);
        if (reader) {
            res=m_Context->loadTexture2D(reader, suggestFT, param);
            closeReader(reader, bundle);
            
            if (res) {
                addToMap(MapTex2D, name, res);
            }
        }
    }
    return res;
}

GMap<GString, GObject>* GTextureManager::getMap(gint index)
{
    return &(m_Maps[index]);
}


