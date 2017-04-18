#pragma once
#include "GXCore.h"

class AppDge : public GApplication::Delegate 
{
    GX_OBJECT(AppDge);
public:
	static AppDge* shared();
public:
    virtual void appDidFinishLaunching(GApplication* application,int argc, char *argv[]);
};

