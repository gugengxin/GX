//
//  MTypist.c
//  GXGameTest
//
//  Created by Gu Gengxin on 2017/6/1.
//  Copyright © 2017年 Gengxin Gu. All rights reserved.
//

#include "MTypist.h"

#pragma pack(1)
typedef struct _MTypistData {
	GVector3 pos;
	GVector2 tc;
} MTypistData;
#pragma pack()

GX_OBJECT_IMPLEMENT(MTypist, Module);

Module* MTypist::initWithGame(Game* game,GContext& context)
{
    Module::initWithGame(game,context);
    
    m_Data = GBuffer::alloc();
    
	MTypistData md[4];
    md[0].pos.set(-100.0f, -100.0f, 0.0f);
    md[1].pos.set(100.0f, -100.0f, 0.0f);
    md[2].pos.set(-100.0f, 100.0f, 0.0f);
    md[3].pos.set(100.0f, 100.0f, 0.0f);
    md[0].tc.set(0.0f, 1.0f);
    md[1].tc.set(1.0f, 1.0f);
    md[2].tc.set(0.0f, 0.0f);
    md[3].tc.set(1.0f, 0.0f);

	m_Data->create(sizeof(md), GBuffer::UsageDefault, &md);
    
    
    GDib* dib=GDib::autoAlloc();
    dib->changeData(GX::PixelFormatRGBA8888, 512, 512);
    
    GFont* font=GFontManager::shared()->loadFTFont(GS::chars("STXINWEI.ttf"), 50, 2);
    GTypist* typist=GTypist::autoAlloc();
    typist->setSingleLine(GS::chars("谷更新 欢迎你 ！！！Welcome!!! abcdefghijklmnopqrstuvwxyz "), font);
    GTypist::Paint* paint=GTypist::Paint::autoAlloc();
    paint->setColor(0, 0xFF, 0, 0xFF);
    paint->setOutlineColor(0xFF, 0, 0, 0xFF);
    
    typist->print(dib, GPointF::make(0, 0), paint);
    
    m_Tex2D=GO::retain(context.loadTexture2D(dib, NULL));
    
    context.setCullFace(GX::DCullFaceBack);
    context.setBlend(GX::DBlendSsaAddD1msa);
    
    m_Angle=0.0f;
    return this;
}

void MTypist::dealloc()
{
    GO::release(m_Tex2D);
    GO::release(m_Data);
    Module::dealloc();
}

void MTypist::idle()
{
    m_Angle+=0.2f/(GX_PI*2);
}
void MTypist::render3D(GCanvas* canvas,GContext& context)
{
    canvas->pushMatrix();
    
    canvas->rotateY(m_Angle);
    
    GSRTexture2D* shader=GSRTexture2D::shared(false, true, GSRTexture2D::MM_None);
    shader->draw(canvas, m_Data, 0, sizeof(MTypistData), GSRTexture2D::IT_Float_Float, m_Tex2D, GX_TRIANGLE_STRIP, 0, 4, NULL);
    
    canvas->popMatrix();
}
void MTypist::render2D(GCanvas* canvas GX_UNUSE,GContext& context GX_UNUSE)
{
    
}

