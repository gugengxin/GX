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
    virtual GWindow* appCanCreateWindow(GApplication* application,void* osWindow);


};

