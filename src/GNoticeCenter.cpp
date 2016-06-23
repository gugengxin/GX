#include "GNoticeCenter.h"
#include "GThread.h"
#include "GXGObject.h"

GX_GOBJECT_IMPLEMENT(GNCObserver, GObject);

GNCObserver::GNCObserver()
{
	m_Key = NULL;
}

GNCObserver::~GNCObserver()
{
	GO::release(m_Key);
}

void GNCObserver::removeObs(GAction* obs)
{
	for (gint i = m_Observers.getCount() - 1; i >= 0; i--) {
		if (m_Observers.get(i) == obs) {
			m_Observers.remove(i);
		}
	}
}
void GNCObserver::removeObs(GObject* target, GX::Selector sel)
{
	for (gint i = m_Observers.getCount() - 1; i >= 0; i--) {
		GAction* obs = m_Observers.get(i);
		if (obs->getTarget() == target && obs->getSelector()==sel) {
			m_Observers.remove(i);
		}
	}
}
void GNCObserver::removeObs(GObject* target)
{
	for (gint i = m_Observers.getCount() - 1; i >= 0; i--) {
		GAction* obs = m_Observers.get(i);
		if (obs->getTarget() == target) {
			m_Observers.remove(i);
		}
	}
}
void GNCObserver::removeObs(GX::Callback cbk)
{
	for (gint i = m_Observers.getCount() - 1; i >= 0; i--) {
		GAction* obs = m_Observers.get(i);
		if (obs->getTarget() == NULL && obs->getCallback()==cbk) {
			m_Observers.remove(i);
		}
	}
}



GNoticeCenter* current()
{
	return GThread::current()->getNoticeCenter();
}

GNoticeCenter::GNoticeCenter()
{

}

GNoticeCenter::~GNoticeCenter()
{
}

void GNoticeCenter::addObserver(GObject* key, GAction* obs)
{
	GNCObserver* observer = m_Observers.get(key);
	if (!observer) {
		observer = GNCObserver::alloc();
		observer->setKey(key);
		m_Observers.set(key, observer);
		GO::release(observer);
	}
	observer->add(obs);
}

void GNoticeCenter::removeObserver(GAction* obs)
{
	GArray<GNCObserver>* arr = m_Observers.getAllObjects();

	for (gint i = 0; i < arr->getCount(); i++) {
		GNCObserver* observer = arr->get(i);
		observer->removeObs(obs);
		if (observer->getObsCount() <= 0) {
			m_Observers.remove(observer->getKey());
		}
	}

}
void GNoticeCenter::removeObserver(GObject* target, GX::Selector sel)
{
	GArray<GNCObserver>* arr = m_Observers.getAllObjects();

	for (gint i = 0; i < arr->getCount(); i++) {
		GNCObserver* observer = arr->get(i);
		observer->removeObs(target,sel);
		if (observer->getObsCount() <= 0) {
			m_Observers.remove(observer->getKey());
		}
	}
}
void GNoticeCenter::removeObserver(GObject* target)
{
	GArray<GNCObserver>* arr = m_Observers.getAllObjects();

	for (gint i = 0; i < arr->getCount(); i++) {
		GNCObserver* observer = arr->get(i);
		observer->removeObs(target);
		if (observer->getObsCount() <= 0) {
			m_Observers.remove(observer->getKey());
		}
	}
}
void GNoticeCenter::removeObserver(GX::Callback cbk)
{
	GArray<GNCObserver>* arr = m_Observers.getAllObjects();

	for (gint i = 0; i < arr->getCount(); i++) {
		GNCObserver* observer = arr->get(i);
		observer->removeObs(cbk);
		if (observer->getObsCount() <= 0) {
			m_Observers.remove(observer->getKey());
		}
	}
}

void GNoticeCenter::postNotice(GNotice* note)
{
	GNCObserver* observer = m_Observers.get(note->getKey());
	if (observer) {
		for (gint i = 0; i < observer->getObsCount(); i++) {
			GAction* obs = observer->getObs(i);
			note->setObserverObj(obs->getObj());
			obs->run(note);
		}
	}
}
