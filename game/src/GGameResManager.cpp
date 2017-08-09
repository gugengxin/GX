//
//  GGameResManager.cpp
//  GX
//
//  Created by GuGengxin.
//  Copyright by gxengine.com
//

#include "GGameResManager.h"

GGameResManager * GGameResManager::shared()
{
	static GGameResManager g_Obj;
	return &g_Obj;
}

GGameResManager::GGameResManager()
{

}

GGameResManager::~GGameResManager()
{
}

GTexture2D* GGameResManager::loadTexture2D(GString* name, GDib::FileType suggestFT, GTexture2D::Parameter* param)
{
	GTexture2D* res = GX_CAST_R(GTexture2D*, findInMap(MapTex2D, name));
	if (!res) {
		GBundle* bundle = NULL;
		GReader* reader = openReader(name, bundle);
		if (reader) {
			res = GTexture2D::alloc();
			if (res->create(reader,suggestFT,param)) {
				closeReader(reader, bundle);

				addToMap(MapTex2D, name, res);
				GO::autorelease(res);
			}
			else {
				closeReader(reader, bundle);
				GO::release(res);
				res = NULL;
			}
		}
	}
	return res;
}

GMap<GString, GObject>* GGameResManager::getMap(gint index)
{
	return &m_Maps[index];
}

void GGameResManager::didReceivedMemoryWarning()
{
}
