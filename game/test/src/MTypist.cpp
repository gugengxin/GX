//
//  MTypist.c
//  GXGameTest
//
//  Created by Gu Gengxin on 2017/6/1.
//  Copyright © 2017年 Gengxin Gu. All rights reserved.
//

#include "MTypist.h"

GX_OBJECT_IMPLEMENT(MTypist, Module);

void MTypist::init()
{
    Module::init();
    m_Data = GDataBuffer::alloc();
    
}

void MTypist::uninit()
{
    GO::release(m_Data);
    Module::uninit();
}

void MTypist::idle()
{
    
}
void MTypist::render3D(GCanvas* canvas,GContext& context)
{
    
}
void MTypist::render2D(GCanvas* canvas,GContext& context)
{
    
}

