//
// Created by Gengxin Gu on 2016/12/20.
//

#ifndef AS_GAME_H
#define AS_GAME_H

#include "GXGame.h"
#include "Module.h"

class Game : public GGame {
    GX_OBJECT_DIT(Game);
protected:
    virtual void eventStart();
    virtual void eventStop();
public:
    virtual void idle();
    virtual void render(GCanvas* canvas);
private:
    GArray<Module>* m_Modules;
};


#endif //AS_GAME_H
