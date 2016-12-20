//
// Created by Gengxin Gu on 2016/12/20.
//

#include "Game.h"


bool Game::init()
{
    if(!GObject::init()) {
        return false;
    }

    return true;
}

void Game::uninit()
{

    GObject::uninit();
}
