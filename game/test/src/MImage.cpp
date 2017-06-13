//
//  MImage.c
//  GXGameTest
//
//  Created by Gu Gengxin on 2017/6/12.
//  Copyright © 2017年 Gengxin Gu. All rights reserved.
//

#include "MImage.h"


GX_OBJECT_IMPLEMENT(MImage, Module);

Module* MImage::initWithGame(Game* game,GContext& context)
{
    Module::initWithGame(game,context);
    
    m_Image=NULL;
    
    return this;
}

void MImage::dealloc()
{
    GO::release(m_Image);
    Module::dealloc();
}

void MImage::idle()
{
    
}
void MImage::render3D(GCanvas* canvas,GContext& context)
{
    
}
void MImage::render2D(GCanvas* canvas GX_UNUSE,GContext& context GX_UNUSE)
{
    
}
