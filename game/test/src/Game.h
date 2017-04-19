//
// Created by Gengxin Gu on 2016/12/20.
//

#ifndef AS_GAME_H
#define AS_GAME_H

#include "GXGame.h"

class Game : public GGame {
    GX_OBJECT(Game);
protected:
    virtual void eventStart(GWindow* window);
    virtual void eventStop();
public:
    virtual void idle();
    virtual void render(GCanvas* canvas);
private:

};


#endif //AS_GAME_H
