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
	m_Action = NULL;
	m_RunTime = 0L;
	m_Cond = NULL;
	m_Cancelled=false;
	m_Done=false;
}

GRunLoop::Action::~Action()
{
	delete m_Action;
}

void GRunLoop::Action::setAction(GAction* v)
{
	m_Action = v;
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

void GRunLoop::perform(GAction* action, gint delayMS, bool waitUntilDone)
{
	GThread* curTD = GThread::current();
	if (m_Thread == curTD) {
		if (delayMS <= 0) {
			action->run();
		}
		else {
			Action* act = Action::alloc();
			act->setAction(action);
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
		act->setAction(action);
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
void GRunLoop::perform(GObject* target, GX::Selector selector, GObject* obj, gint delayMS, bool waitUntilDone)
{
	GAction* action = new GAction;
	action->set(target, selector, obj);
	perform(action, delayMS, waitUntilDone);
}
void GRunLoop::perform(GX::Callback cbk, GObject* obj, gint delayMS, bool waitUntilDone)
{
	GAction* action = new GAction;
	action->set(cbk, obj);
	perform(action, delayMS, waitUntilDone);
}

void GRunLoop::cancel(GObject* target, GX::Selector selector)
{
	m_Mutex.lock();
	for (gint i = m_ActsReady.getCount() - 1; i >= 0; --i) {
		Action* act = m_ActsReady.get(i);
		if (act->getAction()->getTarget() == target && act->getAction()->getSelector() == selector) {
			m_ActsReady.remove(i);
		}
	}
	for (gint i = 0; i<m_ActsRunning.getCount(); i++) {
		Action* act = m_ActsRunning.get(i);
		if (act->getAction()->getTarget() == target && act->getAction()->getSelector() == selector) {
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
		if (act->getAction()->getTarget() == target) {
			m_ActsReady.remove(i);
		}
	}
	for (gint i = 0; i<m_ActsRunning.getCount(); i++) {
		Action* act = m_ActsRunning.get(i);
		if (act->getAction()->getTarget() == target) {
			act->setCancelled();
		}
	}
	m_Mutex.unlock();
}

void GRunLoop::cancel(GX::Callback cbk)
{
	m_Mutex.lock();
	for (gint i = m_ActsReady.getCount() - 1; i >= 0; --i) {
		Action* act = m_ActsReady.get(i);
		if (act->getAction()->getTarget() == NULL && act->getAction()->getCallback() == cbk) {
			m_ActsReady.remove(i);
		}
	}
	for (gint i = 0; i<m_ActsRunning.getCount(); i++) {
		Action* act = m_ActsRunning.get(i);
		if (act->getAction()->getTarget() == NULL && act->getAction()->getCallback() == cbk) {
			act->setCancelled();
		}
	}
	m_Mutex.unlock();
}