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

void AppDge::AppDidFinishLaunching(GApplication* application, GApplication::InitData* initData)
{
	GWindow* win = GWindow::autoAlloc();
	win->create(initData->getOSWindow());
	application->addWindow(win);
}
