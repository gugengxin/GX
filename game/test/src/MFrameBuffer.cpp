//
//  MFrameBuffer.c
//  GXGameTest
//
//  Created by Gu Gengxin on 2017/6/7.
//  Copyright © 2017年 Gengxin Gu. All rights reserved.
//

#include "MFrameBuffer.h"


GX_OBJECT_IMPLEMENT(MFrameBuffer, Module);

Module* MFrameBuffer::initWithGame(Game* game,GContext& context)
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
    
    

    m_FB=NULL;
    m_Tex2D=NULL;
    
    //prepareTex2D(context);
    
    m_Angle=0.0f;
    
    context.setCullFace(GX::DCullFaceBack);
    return this;
}

void MFrameBuffer::dealloc()
{
    GO::release(m_FB);
    GO::release(m_Tex2D);
    GO::release(m_Data);
    Module::dealloc();
}

void MFrameBuffer::prepareTex2D(GContext& context)
{
    if (!m_FB) {
        m_FB=GO::retain(context.loadFrameBuffer(200, 200, NULL, GFrameBuffer::UseFor3D));
        m_Tex2D=GO::retain(GX_CAST_R(GTexture2D*, m_FB->getTexture()));
        
        if (m_FB->renderCheck()) {
            
            GTexture2D* tex=context.loadTexture2D(GS::chars("lena_rgb.jpg"), GDib::JPEG, NULL);
            
            m_FB->renderBegin();
            m_FB->setViewport(0, 0, m_FB->getWidth(), m_FB->getHeight(), 1.0f);
            
            m_FB->enable2D(m_FB->getWidth(), m_FB->getHeight());
            m_FB->translate(m_FB->getWidth()*0.5f, m_FB->getHeight()*0.5f, 0.0f);
            
            //m_FB->enable3D(m_FB->getWidth(), m_FB->getHeight(), GX_PI / 3, 0.1f, 1000.0f);
            //m_FB->lookAt(0.0f, 0.0f, 200.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
            
            m_FB->setCullFace(GX::DCullFaceBack);
            
            GSRTexture2D* shader=context.getSRTexture2D(false, false, GSRTexture2D::MM_None);
            shader->draw(m_FB, m_Data, GSRTexture2D::IT_Float_Float, tex, GX_TRIANGLE_STRIP, 0, 4, NULL);
            
            m_FB->renderEnd();
        }
    }
}

void MFrameBuffer::idle()
{
    m_Angle+=0.2f/(GX_PI*2);
}
void MFrameBuffer::render3D(GCanvas* canvas,GContext& context)
{
    prepareTex2D(context);
    
    canvas->pushMatrix();
    
    canvas->rotateY(m_Angle);
    
    GSRTexture2D* shader=context.getSRTexture2D(false, true, GSRTexture2D::MM_None);
    shader->draw(canvas, m_Data, GSRTexture2D::IT_Float_Float, m_Tex2D, GX_TRIANGLE_STRIP, 0, 4, NULL);
    
    canvas->popMatrix();
}
void MFrameBuffer::render2D(GCanvas* canvas GX_UNUSE,GContext& context GX_UNUSE)
{
    
}
