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
