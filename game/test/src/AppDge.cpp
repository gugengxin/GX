#include "AppDge.h"
#include "Game.h"

GX_OBJECT_IMPLEMENT(AppDge, GApplication::Delegate);

AppDge* AppDge::shared()
{
    return GX_CAST_R(AppDge*, GApplication::sharedDelegate());
}

void AppDge::init()
{
    GApplication::Delegate::init();
    
}

void AppDge::dealloc()
{
    
    GApplication::Delegate::dealloc();
}

static void _test_thread_main(GObject* )
{

    GThread::current();
}

void AppDge::appDidFinishLaunching(GApplication* application,int argc, char *argv[])
{
    GX_UNUSED(application);
    GX_UNUSED(argc);
    GX_UNUSED(argv);


    GThread::detch(_test_thread_main, NULL);
}
