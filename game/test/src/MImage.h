//
//  MImage.h
//  GXGameTest
//
//  Created by Gu Gengxin on 2017/6/12.
//  Copyright © 2017年 Gengxin Gu. All rights reserved.
//

#ifndef MImage_h
#define MImage_h

#include "Module.h"


class MImage : public Module {
    GX_OBJECT(MImage);
public:
    virtual Module* initWithGame(Game* game,GContext& context);
    
    virtual void idle();
    virtual void render3D(GCanvas* canvas,GContext& context);
    virtual void render2D(GCanvas* canvas,GContext& context);
private:
    //GImage* m_Image;
};

#endif /* MImage_h */
