//
//  Module.c
//  GXGameTest
//
//  Created by Gu Gengxin on 2017/6/1.
//  Copyright © 2017年 Gengxin Gu. All rights reserved.
//

#include "Module.h"


GX_OBJECT_IMPLEMENT(Module, GObject);


Module* Module::initWithGame(Game* game,GContext& context)
{
    return this;
}

void Module::dealloc()
{
    
    GObject::dealloc();
}

void Module::idle()
{
    
}
void Module::render3D(GCanvas* canvas,GContext& context)
{
    
}
void Module::render2D(GCanvas* canvas,GContext& context)
{
    
}
