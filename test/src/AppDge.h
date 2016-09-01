#pragma once
#include "GX.h"

class AppDge : public GApplication::Delegate 
{
public:
	static AppDge* shared();
private:
	AppDge();
	~AppDge();
public:
    virtual void appCanCreateWindow(GApplication* application,void* osWindow);

    virtual gint windowsSuggestedSamples() {
        return 0;
    }
    virtual gint windowsSuggestedDepth() {
        return 24;
    }
    virtual gint windowsSuggestedStencil() {
        return 8;
    }
};

