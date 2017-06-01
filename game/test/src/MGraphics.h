//
//  MGraphics.h
//  GXGameTest
//
//  Created by Gu Gengxin on 2017/6/1.
//  Copyright © 2017年 Gengxin Gu. All rights reserved.
//

#ifndef MGraphics_h
#define MGraphics_h

#include "Module.h"


class MGraphics : public Module {
    GX_OBJECT(MGraphics);
public:
    virtual void idle();
    virtual void render3D(GCanvas* canvas,GContext& context);
    virtual void render2D(GCanvas* canvas,GContext& context);
private:
    GDataBuffer* m_Data;
};



#endif /* MGraphics_h */
