//
//  GFileManager.cpp
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#include "GFileManager.h"
#include "GXGObject.h"

GFileManager* GFileManager::shared()
{
	static GFileManager g_Obj;
	return &g_Obj;
}

GFileManager::GFileManager()
{
	
}

GFileManager::~GFileManager()
{
}

bool GFileManager::fileExists(const gtchar* path, bool* isDirectory)
{
	return false;
}


