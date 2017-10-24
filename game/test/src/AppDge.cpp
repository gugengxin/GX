#include "AppDge.h"
#include "Game.h"

static gint32 g_I=0;

class A : public GObject {
    GX_OBJECT_DIT(A);
public:

    gint32 i;
};

GX_OBJECT_IMPLEMENT(A, GObject);

void A::init()
{
    GObject::init();
    i=g_I++;
    GX_LOG_P1(PrioDEBUG, "A", "A::init %d", i);
}

void A::dealloc()
{
    GX_LOG_P1(PrioDEBUG, "A", "A::dealloc %d", i);
    GObject::dealloc();
}

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
    for (gint i=0; i<2000; i++) {
        A::autoAlloc();
    }
    GThread::current();
}

void AppDge::appDidFinishLaunching(GApplication* application,int argc, char *argv[])
{
    GX_UNUSED(application);
    GX_UNUSED(argc);
    GX_UNUSED(argv);


    for (gint i=0; i<2222; i++) {
        A::autoAlloc();
    }


    GThread::detch(_test_thread_main, NULL);
}
