#include "AppDge.h"


AppDge* AppDge::shared()
{
	static AppDge g_Obj;
	return &g_Obj;
}

AppDge::AppDge()
{
}


AppDge::~AppDge()
{
}

void AppDge::appCanCreateWindow(GApplication* application,void* osWindow)
{
	application->addWindow(osWindow);
}
