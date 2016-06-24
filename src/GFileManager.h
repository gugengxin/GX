//
//  GFileManager.h
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#ifndef GFileManager_h
#define GFileManager_h

#include "GXPrefix.h"

class GFileManager {
public:
	static GFileManager* shared();
private:
	GFileManager();
	~GFileManager();
public:
	bool fileExists(const gtchar* path, bool* isDirectory);

private:

};

#endif /* GFileManager_h */
