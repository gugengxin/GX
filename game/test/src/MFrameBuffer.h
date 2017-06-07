//
//  MFrameBuffer.h
//  GXGameTest
//
//  Created by Gu Gengxin on 2017/6/7.
//  Copyright © 2017年 Gengxin Gu. All rights reserved.
//

#ifndef MFrameBuffer_h
#define MFrameBuffer_h

#include "Module.h"

class MFrameBuffer : public Module {
    GX_OBJECT(MFrameBuffer);
public:
    virtual Module* initWithGame(Game* game,GContext& context);
    virtual void idle();
    virtual void render3D(GCanvas* canvas,GContext& context);
    virtual void render2D(GCanvas* canvas,GContext& context);
private:
    void prepareTex2D(GContext& context);
private:
    float m_Angle;
    GDataBuffer* m_Data;
    GTexture2D* m_Tex2D;
    GFrameBuffer* m_FB;
};

#endif /* MFrameBuffer_h */
