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
	virtual void AppDidFinishLaunching(GApplication* application, GApplication::InitData* initData);


};

