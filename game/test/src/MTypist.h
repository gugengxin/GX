//
//  MTypist.h
//  GXGameTest
//
//  Created by Gu Gengxin on 2017/6/1.
//  Copyright © 2017年 Gengxin Gu. All rights reserved.
//

#ifndef MTypist_h
#define MTypist_h

#include "Module.h"

class MTypist : public Module {
    GX_OBJECT(MTypist);
public:
    virtual Module* initWithGame(Game* game,GContext& context);
    virtual void idle();
    virtual void render3D(GCanvas* canvas,GContext& context);
    virtual void render2D(GCanvas* canvas,GContext& context);
private:
    float m_Angle;
    GBuffer* m_Data;
    GTexture2D* m_Tex2D;
    GTypist* m_Typist;
};

#endif /* MTypist_h */
