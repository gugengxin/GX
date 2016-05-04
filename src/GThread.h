//
//  GThread.hpp
//  GX
//
//  Created by Gengxin Gu on 16/4/27.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GThread_h
#define GThread_h

#include "GXPrefix.h"
#include "GObject.h"
#include "GAutoreleasePool.h"
#include "GDataArray.h"
#include "GRunLoop.h"
#include "GXPthread.h"

class GThread {
    friend class GApplication;
    friend class GAutoreleasePool;
    friend class GObject;
public:
    static GThread* main();
    static GThread* current();
    
    GRunLoop* getRunLoop();
private:
    static void keyCreate();
    static void keyDestory(void* p);
    
    GThread();
    ~GThread();
    void setMain();

    void pushARObj(GObject* v);
    void popARObj(gint toCount);
    
private:
	GX::pthread_t m_ID;
    GPDArray<GObject*> m_ARObjs;
    GRunLoop* m_RunLoop;
};





#endif /* GThread_h */
