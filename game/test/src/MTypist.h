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
    virtual void idle();
    virtual void render3D(GCanvas* canvas,GContext& context);
    virtual void render2D(GCanvas* canvas,GContext& context);
private:
    GDataBuffer* m_Data;
};

#endif /* MTypist_h */
