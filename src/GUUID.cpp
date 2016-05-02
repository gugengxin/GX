﻿//
//  GUUID.cpp
//  GX
//
//  Created by Gu Gengxin on 16/5/1.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#include "GUUID.h"
#if defined(GX_OS_APPLE)
#include <CoreFoundation/CoreFoundation.h>
#elif defined(GX_OS_ANDROID)
#include "GXJavaClass.h"
#include "GXJavaCAPI.h"
#elif defined(GX_OS_WINDOWS)
#include <objbase.h>
#endif

GX_OBJECT_IMPLEMENT(GUUID, GObject);

GUUID::GUUID()
{
#if defined(GX_OS_APPLE)
    CFUUIDRef uuid=CFUUIDCreate(NULL);
    (*((CFUUIDBytes*)&m_Bytes))=CFUUIDGetUUIDBytes(uuid);
    CFRelease(uuid);
#elif defined(GX_OS_ANDROID)
    GXJavaJNIEnvAutoPtr jniEnv;

    GXJavaCAPI::Shared()->UUIDCreate(jniEnv.Get(),m_Bytes);

#elif defined(GX_OS_MICROSOFT)
    //GUID guid;
    ::CoCreateGuid((GUID*)m_Bytes);
#endif
}

GUUID::~GUUID()
{

}