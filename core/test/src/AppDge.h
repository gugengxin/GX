#pragma once
#include "GXCore.h"

class AppDge : public GApplication::Delegate 
{
public:
	static AppDge* shared();
private:
	AppDge();
	~AppDge();
public:
    virtual void appDidFinishLaunching(GApplication* application);
};

