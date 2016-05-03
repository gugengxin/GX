//
//  GApplication.h
//  GX
//
//  Created by Gu Gengxin on 16/5/1.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GApplication_h
#define GApplication_h

#include "GXPrefix.h"
#include "GArray.h"
#include "GWindow.h"


class GApplication {
public:
    class Delegate {
    public:

    };
public:
    static GApplication* shared();
    static void main(Delegate* dge);
private:
    GApplication();
    ~GApplication();
    
    void idle();
    
    void didFinishLaunching();
    void didBecomeActive();
    void willResignActive();
    void didEnterBackground();
    void willEnterForeground();
    void willTerminate();
    void didReceiveMemoryWarning();
public:

private:
    Delegate* m_Delegate;
    GArray<GWindow> m_Windows;
    
#if defined(GX_OS_APPLE)
    friend class _AppTimerBridge;
    void* m_Timer;
#endif
};



#endif /* GApplication_h */
