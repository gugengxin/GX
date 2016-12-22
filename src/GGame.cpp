//
//  GGame.cpp
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#include "GGame.h"
//Down include other h file
#include "GWindow.h"
#include "GCanvas.h"
#include "GSystem.h"

//Up include other h file
#include "GXGObject.h"

GX_GOBJECT_IMPLEMENT(GGame, GObject);

GGame::GGame()
{
    m_Window=NULL;
    m_RunLastTime=0LL;
}

GGame::~GGame()
{
    
}

void GGame::init(GWindow* window)
{
    GObject::init();
    
    m_Window=window;
}
void GGame::uninit()
{
    
}

gint GGame::getFPS()
{
    return 30;
}

void GGame::idle()
{
    
}

void GGame::render(GCanvas* canvas)
{
    
}

void GGame::run()
{
    gint fps=getFPS();
    if (fps<=0) {
        fps=30;
    }
    if (GSystem::currentTimeMS()-m_RunLastTime>=1000/fps) {
        idle();
        m_Window->render();
    }
}


