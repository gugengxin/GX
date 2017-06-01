//
//  Module.h
//  GXGameTest
//
//  Created by Gu Gengxin on 2017/6/1.
//  Copyright © 2017年 Gengxin Gu. All rights reserved.
//

#ifndef Module_h
#define Module_h

#include "GXGame.h"

class Game;

class Module : public GObject {
    GX_VIRTUAL_OBJECT(Module);
public:
    virtual Module* initWithGame(Game* game,GContext& context);
    virtual void idle();
    virtual void render3D(GCanvas* canvas,GContext& context);
    virtual void render2D(GCanvas* canvas,GContext& context);
};



#endif /* Module_h */
