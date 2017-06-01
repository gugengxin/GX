#pragma once
#include "GXGame.h"

class AppDge : public GApplication::Delegate 
{
    GX_OBJECT_DIT(AppDge);
public:
	static AppDge* shared();
public:
    virtual void appDidFinishLaunching(GApplication* application,int argc, char *argv[]);

    virtual gint windowsSuggestedSamples() {
        return 0;
    }
    virtual gint windowsSuggestedDepth() {
        return 24;
    }
    virtual gint windowsSuggestedStencil() {
        return 0;
    }
};

