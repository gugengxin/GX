//
//  MGraphics.c
//  GXGameTest
//
//  Created by Gu Gengxin on 2017/6/1.
//  Copyright © 2017年 Gengxin Gu. All rights reserved.
//

#include "MGraphics.h"

#pragma pack(1)
typedef struct _MGraphicsData {
	GVector3 pos;
	GColor4 clr;
} MGraphicsData;
#pragma pack()

GX_OBJECT_IMPLEMENT(MGraphics, Module);

Module* MGraphics::initWithGame(Game* game,GContext& context)
{
    Module::initWithGame(game,context);
    
    m_Data = GBuffer::alloc();
    
	MGraphicsData md[4];
    md[0].pos.set(-100.0f, -100.0f, 0.0f);
    md[1].pos.set(100.0f, -100.0f, 0.0f);
    md[2].pos.set(-100.0f, 100.0f, 0.0f);
    md[3].pos.set(100.0f, 100.0f, 0.0f);
    md[0].clr.set(0xFF, 0, 0, 0xFF);
    md[1].clr.set(0, 0xFF, 0, 0xFF);
    md[2].clr.set(0, 0, 0xFF, 0xFF);
    md[3].clr.set(0xFF, 0xFF, 0xFF, 0xFF);
    
	m_Data->create(sizeof(md), GBuffer::UsageDefault, &md);
    
    return this;
}

void MGraphics::dealloc()
{
    GO::release(m_Data);
    Module::dealloc();
}

void MGraphics::idle()
{
    
}
void MGraphics::render3D(GCanvas* canvas,GContext& context)
{
    GX_UNUSED(context);
    GSRGraphics* graph = GSRGraphics::shared(GSRGraphics::ID_Color);
    canvas->setColorMul(0, 0.0f, 1, 1, 1.0f);
    graph->draw(canvas, m_Data, 0, sizeof(MGraphicsData), GSRGraphics::IT_Float, GX_TRIANGLE_STRIP, 0, 4);
}
void MGraphics::render2D(GCanvas* canvas GX_UNUSE,GContext& context GX_UNUSE)
{
    
}
