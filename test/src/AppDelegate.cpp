#include "AppDelegate.h"


AppDelegate* AppDelegate::shared()
{
	static AppDelegate g_Obj;
	return &g_Obj;
}

AppDelegate::AppDelegate()
{
}


AppDelegate::~AppDelegate()
{
}
