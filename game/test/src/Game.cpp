//
// Created by Gengxin Gu on 2016/12/20.
//

#include "Game.h"
#include "MGraphics.h"
#include "MFrameBuffer.h"
#include "MTypist.h"
#include "MImage.h"

GX_OBJECT_IMPLEMENT(Game,GGame);

void Game::init()
{
    GGame::init();
    m_Modules=GArray<Module>::alloc();
}

void Game::dealloc()
{
    GO::release(m_Modules);
    GGame::dealloc();
}

void Game::eventStart()
{
    GGame::eventStart();
    
    GAppBundle* mb=GAppBundle::main();
    GReader* reader=mb->openReader(GS::chars("system_fonts.xml"));
    if (reader) {
        
        //GMap<GString, GString>* xmlObj=GXML::read(reader);
        
        mb->closeReader(reader);
    }
    
    
    
    getWindow()->getCanvas()->setBackgroundColor(1, 0, 1, 1);
    
    GContext& context=getWindow()->getContext();
    //m_Modules->add(MGraphics::autoAlloc()->initWithGame(this, context));
    //m_Modules->add(MFrameBuffer::autoAlloc()->initWithGame(this, context));
    m_Modules->add(MTypist::autoAlloc()->initWithGame(this, context));
    //m_Modules->add(MImage::autoAlloc()->initWithGame(this, context));
}

void Game::eventStop()
{

    GGame::eventStop();
}




void Game::idle()
{
    for (gint i=0; i<m_Modules->getCount(); i++) {
        m_Modules->get(i)->idle();
    }
}

void Game::render(GCanvas* canvas)
{
    GContext& context=getWindow()->getContext();
    
    canvas->enable3D(0, canvas->getWidth(), canvas->getHeight(), GX_PI / 3, 0.1f, 1000.0f);
    canvas->lookAt(0, 0.0f, 0.0f, 200.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    
    
    for (gint i=0; i<m_Modules->getCount(); i++) {
        m_Modules->get(i)->render3D(canvas, context);
    }
    
    canvas->enable2D(0, canvas->getWidth(), canvas->getHeight());
    
    for (gint i=0; i<m_Modules->getCount(); i++) {
        m_Modules->get(i)->render2D(canvas, context);
    }
}
