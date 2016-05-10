//
//  GRunLoop.cpp
//  GX
//
//  Created by Gengxin Gu on 16/4/27.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#include "GRunLoop.h"
#include "GThread.h"
#include "GSystem.h"

GX_OBJECT_IMPLEMENT(GRunLoop::Action, GObject);

GRunLoop::Action::Action()
{
	m_Target=NULL;
	memset(&m_Action, 0, sizeof(m_Action));
	m_Obj=NULL;
	m_RunTime = 0L;
	m_Cond = NULL;
	m_Cancelled=false;
	m_Done=false;
}

GRunLoop::Action::~Action()
{
	GO::release(m_Target);
	GO::release(m_Obj);
}

void GRunLoop::Action::set(GObject* target, GObject::Selector sel, GObject* obj)
{
	GO::retain(target);
	GO::release(m_Target);
	m_Target = target;
	m_Action.sel = sel;
	GO::retain(obj);
	GO::release(m_Obj);
	m_Obj = obj;
}

void GRunLoop::Action::set(GObject::Fun fun, GObject* obj)
{
	m_Action.fun = fun;;
	GO::retain(obj);
	GO::release(m_Obj);
	m_Obj = obj;
}

void GRunLoop::Action::run()
{
	if (m_Target) {
		(m_Target->*m_Action.sel)(m_Obj);
	}
	else {
		m_Action.fun(m_Obj);
	}
	m_Done = true;
}

void GRunLoop::Action::signalIfNeed()
{
	if (m_Cond) {
		m_Cond->signal();
	}
}




GRunLoop* GRunLoop::current()
{
	return GThread::current()->getRunLoop();
}

GRunLoop::GRunLoop(GThread* td)
{
	m_Thread = td;
}

GRunLoop::~GRunLoop()
{

}

void GRunLoop::run()
{
	m_Mutex.lock();
	m_Actions.add(&m_ActsReady);
	m_ActsReady.removeAll();
	m_ActsRunning.add(&m_Actions);
	m_Mutex.unlock();

	for (gint i = 0; i < m_Actions.getCount(); i++) {
		Action* act = m_Actions.get(i);
		if (act->isCancelled()) {
			m_Actions.remove(i);
			--i;
		}
		else {
			if (GSystem::currentTimeMS() >= act->getRunTime()) {
				act->run();
				act->signalIfNeed();
				m_Actions.remove(i);
				--i;
			}
		}
	}

	m_Mutex.lock();
	m_ActsRunning.removeAll();
	m_ActsReady.add(&m_Actions);
	m_Mutex.unlock();

	m_Thread->popARObj(0);
}

void GRunLoop::perform(GObject* target, GObject::Selector selector, GObject* obj, gint delayMS, bool waitUntilDone)
{
	GThread* curTD = GThread::current();
	if (m_Thread == curTD) {
		if (delayMS <= 0) {
			(target->*selector)(obj);
		}
		else {
			Action* act = Action::alloc();
			act->set(target, selector, obj);
			act->setRunTime(GSystem::currentTimeMS() + delayMS);

			m_Mutex.lock();
			m_ActsReady.add(act);
			m_Mutex.unlock();
			
			if (waitUntilDone) {
				while (!act->isDone()) {
					run();
				}
			}

			GO::release(act);
		}
	}
	else {
		Action* act = Action::alloc();
		act->set(target, selector, obj);
		act->setRunTime(GSystem::currentTimeMS() + delayMS);

		if (waitUntilDone) {
			GCondition cond;
			act->setCond(&cond);

			m_Mutex.lock();
			m_ActsReady.add(act);
			GO::release(act);
			m_Mutex.unlock();

			cond.wait();
		}
		else {
			m_Mutex.lock();
			m_ActsReady.add(act);
			GO::release(act);
			m_Mutex.unlock();
		}
	}
}
void GRunLoop::perform(GObject::Fun fun, GObject* obj, gint delayMS, bool waitUntilDone)
{
	GThread* curTD = GThread::current();
	if (m_Thread == curTD) {
		if (delayMS <= 0) {
			fun(obj);
		}
		else {
			Action* act = Action::alloc();
			act->set(fun, obj);
			act->setRunTime(GSystem::currentTimeMS() + delayMS);

			m_Mutex.lock();
			m_ActsReady.add(act);
			m_Mutex.unlock();

			if (waitUntilDone) {
				while (!act->isDone()) {
					run();
				}
			}

			GO::release(act);
		}
	}
	else {
		Action* act = Action::alloc();
		act->set(fun, obj);
		act->setRunTime(GSystem::currentTimeMS() + delayMS);

		if (waitUntilDone) {
			GCondition cond;
			act->setCond(&cond);

			m_Mutex.lock();
			m_ActsReady.add(act);
			GO::release(act);
			m_Mutex.unlock();

			cond.wait();
		}
		else {
			m_Mutex.lock();
			m_ActsReady.add(act);
			GO::release(act);
			m_Mutex.unlock();
		}
	}
}

void GRunLoop::cancel(GObject* target, GObject::Selector selector)
{
	m_Mutex.lock();
	for (gint i = m_ActsReady.getCount() - 1; i >= 0; --i) {
		Action* act = m_ActsReady.get(i);
		if (act->getTarget() == target && act->getSel() == selector) {
			m_ActsReady.remove(i);
		}
	}
	for (gint i = 0; i<m_ActsRunning.getCount(); i++) {
		Action* act = m_ActsRunning.get(i);
		if (act->getTarget() == target && act->getSel() == selector) {
			act->setCancelled();
		}
	}
	m_Mutex.unlock();
}
void GRunLoop::cancel(GObject* target)
{
	m_Mutex.lock();
	for (gint i = m_ActsReady.getCount() - 1; i >= 0; --i) {
		Action* act = m_ActsReady.get(i);
		if (act->getTarget() == target) {
			m_ActsReady.remove(i);
		}
	}
	for (gint i = 0; i<m_ActsRunning.getCount(); i++) {
		Action* act = m_ActsRunning.get(i);
		if (act->getTarget() == target) {
			act->setCancelled();
		}
	}
	m_Mutex.unlock();
}

void GRunLoop::cancel(GObject::Fun fun)
{
	m_Mutex.lock();
	for (gint i = m_ActsReady.getCount() - 1; i >= 0; --i) {
		Action* act = m_ActsReady.get(i);
		if (act->getTarget() == NULL && act->getFun() == fun) {
			m_ActsReady.remove(i);
		}
	}
	for (gint i = 0; i<m_ActsRunning.getCount(); i++) {
		Action* act = m_ActsRunning.get(i);
		if (act->getTarget() == NULL && act->getFun() == fun) {
			act->setCancelled();
		}
	}
	m_Mutex.unlock();
}