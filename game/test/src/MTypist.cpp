//
//  MTypist.c
//  GXGameTest
//
//  Created by Gu Gengxin on 2017/6/1.
//  Copyright © 2017年 Gengxin Gu. All rights reserved.
//

#include "MTypist.h"

GX_OBJECT_IMPLEMENT(MTypist, Module);

Module* MTypist::initWithGame(Game* game,GContext& context)
{
    Module::initWithGame(game,context);
    
    m_Data = GDataBuffer::alloc();
    typedef struct {
        GVector3 pos;
        GVector2 tc;
    } MD;
    MD md[4];
    md[0].pos.set(-100.0f, -100.0f, 0.0f);
    md[1].pos.set(100.0f, -100.0f, 0.0f);
    md[2].pos.set(-100.0f, 100.0f, 0.0f);
    md[3].pos.set(100.0f, 100.0f, 0.0f);
    md[0].tc.set(0.0f, 1.0f);
    md[1].tc.set(1.0f, 1.0f);
    md[2].tc.set(0.0f, 0.0f);
    md[3].tc.set(1.0f, 0.0f);
    m_Data->changeBytes(sizeof(md));
    void* p = m_Data->map();
    memcpy(p, &md[0], sizeof(md));
    m_Data->unmap();
    m_Data->setOffset(0);
    m_Data->setStride(sizeof(md[0]));
    
    return this;
}

void MTypist::dealloc()
{
    GO::release(m_Data);
    Module::dealloc();
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

