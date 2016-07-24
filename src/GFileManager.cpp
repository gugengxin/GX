//
//  GFileManager.cpp
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#include "GFileManager.h"
#if defined(GX_OS_APPLE)
#import <Foundation/Foundation.h>
#elif defined(GX_OS_MICROSOFT)
#include <Windows.h>
#elif defined(GX_OS_ANDROID)
#include <sys/stat.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <utime.h>
#include <fcntl.h>
#elif defined(GX_OS_QT)
#include <QFileInfo>
#endif
#include "GDataString.h"

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
#if defined(GX_OS_APPLE)
    gint len = GX::strlen(path);

    NSString* strPath = [[NSString alloc] initWithBytesNoCopy:(void*)path length:(NSUInteger)len encoding:NSUTF8StringEncoding freeWhenDone:NO];
	BOOL isDir = NO;
    BOOL exist=[[NSFileManager defaultManager] fileExistsAtPath:strPath isDirectory:&isDir];
    [strPath release];
	if (exist) {
		if (isDirectory) {
			(*isDirectory) = isDir;
		}
		return true;
	}
	return false;
#elif defined(GX_OS_MICROSOFT)
	DWORD res = ::GetFileAttributes(path);
	if (res != INVALID_FILE_ATTRIBUTES) {
		if (isDirectory) {
			(*isDirectory) = ((res&FILE_ATTRIBUTE_DIRECTORY) != 0);
		}
		return true;
	}
	return false;
#elif defined(GX_OS_ANDROID)
	struct stat file_info;
	if (stat(path, &file_info) == 0) {
		if (isDirectory) {
			(*isDirectory) = (S_ISDIR(file_info.st_mode) != 0);
		}
		return true;
	}
	return false;
#elif defined(GX_OS_QT)
    QFileInfo fi(path);
    if(fi.exists()) {
        if(isDirectory) {
            (*isDirectory)=fi.isDir();
        }
        return true;
    }
    return false;
#else
#error
#endif
}


