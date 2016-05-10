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

	typedef void(*Fun)(GObject*);

	class Holder : public GObject
	{
		friend class GThread;
		GX_OBJECT(Holder);
	public:

	private:
		GX::pthread_t	m_TID;
		GThread*		m_Thread;
	};
public:
    static GThread* main();
    static GThread* current();
	static void sleep(gint ms);

	static void detch(GObject* target, GObject::Selector selector, GObject* obj);
	static void detch(Fun fun, GObject* obj);
	static Holder* create(GObject* target, GObject::Selector selector, GObject* obj,bool waitRun);
	static Holder* create(Fun fun, GObject* obj, bool waitRun);
private:
	static void* detchHelperObj(void*);
	static void* detchHelperFun(void*);
	static void* createHelperObj(void*);
	static void* createHelperFun(void*);

public:
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
