#pragma once
#include "GXGame.h"

class AppDge : public GApplication::Delegate 
{
public:
	static AppDge* shared();
private:
	AppDge();
	~AppDge();
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

