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
    
    //m_Image=GImage::alloc();
    //m_Image->setTexture(context.loadTexture2D(GS::chars("png-0029.png"), GDib::PNG, NULL));
//    m_Image->changeDataCount(4);
//    m_Image->setDataPT(0, GVector2(-100.0f,100.0f), GVector2());
//    md[0].pos.set(-100.0f, -100.0f, 0.0f);
//    md[1].pos.set(100.0f, -100.0f, 0.0f);
//    md[2].pos.set(-100.0f, 100.0f, 0.0f);
//    md[3].pos.set(100.0f, 100.0f, 0.0f);
//    md[0].tc.set(0.0f, 1.0f);
//    md[1].tc.set(1.0f, 1.0f);
//    md[2].tc.set(0.0f, 0.0f);
//    md[3].tc.set(1.0f, 0.0f);
    
    
    return this;
}

void MImage::dealloc()
{
    //GO::release(m_Image);
    Module::dealloc();
}

void MImage::idle()
{
    
}
void MImage::render3D(GCanvas* canvas,GContext& context)
{
    canvas->pushMatrix();
    
    //m_Image->draw(context, canvas);
    
    canvas->popMatrix();
}
void MImage::render2D(GCanvas* canvas GX_UNUSE,GContext& context GX_UNUSE)
{
    
}
