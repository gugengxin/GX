#include "AppDge.h"
#include "Game.h"


AppDge* AppDge::shared()
{
    return GX_CAST_R(AppDge*, GApplication::sharedDelegate());
}

AppDge::AppDge()
{
}


AppDge::~AppDge()
{
}

void AppDge::appDidFinishLaunching(GApplication* application,int argc, char *argv[])
{
    
}
