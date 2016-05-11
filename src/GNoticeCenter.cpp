#include "GNoticeCenter.h"
#include "GThread.h"

GX_OBJECT_IMPLEMENT(GNoticeCenter::Observer, GObject);

GNoticeCenter::Observer::Observer()
{
	m_Key = NULL;
}

GNoticeCenter::Observer::~Observer()
{
	GO::release(m_Key);
}

void GNoticeCenter::Observer::removeObs(GObserver* obs)
{
	for (gint i = m_Observers.getCount() - 1; i >= 0; i--) {
		if (m_Observers.get(i) == obs) {
			m_Observers.remove(i);
		}
	}
}
void GNoticeCenter::Observer::removeObs(GObject* target, GX::Selector sel)
{
	for (gint i = m_Observers.getCount() - 1; i >= 0; i--) {
		GObserver* obs = m_Observers.get(i);
		if (obs->getTarget() == target && obs->getSelector()==sel) {
			m_Observers.remove(i);
		}
	}
}
void GNoticeCenter::Observer::removeObs(GObject* target)
{
	for (gint i = m_Observers.getCount() - 1; i >= 0; i--) {
		GObserver* obs = m_Observers.get(i);
		if (obs->getTarget() == target) {
			m_Observers.remove(i);
		}
	}
}
void GNoticeCenter::Observer::removeObs(GX::Callback cbk)
{
	for (gint i = m_Observers.getCount() - 1; i >= 0; i--) {
		GObserver* obs = m_Observers.get(i);
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

void GNoticeCenter::addObserver(GObject* key, GObserver* obs)
{
	Observer* observer=m_Observers.get(key);
	if (!observer) {
		observer = Observer::alloc();
		observer->setKey(key);
		m_Observers.set(key, observer);
		GO::release(observer);
	}
	observer->add(obs);
}

void GNoticeCenter::removeObserver(GObserver* obs)
{
	GArray<Observer>* arr = m_Observers.getAllObjects();

	for (gint i = 0; i < arr->getCount(); i++) {
		Observer* observer = arr->get(i);
		observer->removeObs(obs);
		if (observer->getObsCount() <= 0) {
			m_Observers.remove(observer->getKey());
		}
	}

}
void GNoticeCenter::removeObserver(GObject* target, GX::Selector sel)
{
	GArray<Observer>* arr = m_Observers.getAllObjects();

	for (gint i = 0; i < arr->getCount(); i++) {
		Observer* observer = arr->get(i);
		observer->removeObs(target,sel);
		if (observer->getObsCount() <= 0) {
			m_Observers.remove(observer->getKey());
		}
	}
}
void GNoticeCenter::removeObserver(GObject* target)
{
	GArray<Observer>* arr = m_Observers.getAllObjects();

	for (gint i = 0; i < arr->getCount(); i++) {
		Observer* observer = arr->get(i);
		observer->removeObs(target);
		if (observer->getObsCount() <= 0) {
			m_Observers.remove(observer->getKey());
		}
	}
}
void GNoticeCenter::removeObserver(GX::Callback cbk)
{
	GArray<Observer>* arr = m_Observers.getAllObjects();

	for (gint i = 0; i < arr->getCount(); i++) {
		Observer* observer = arr->get(i);
		observer->removeObs(cbk);
		if (observer->getObsCount() <= 0) {
			m_Observers.remove(observer->getKey());
		}
	}
}

void GNoticeCenter::postNotice(GNotice* note)
{
	Observer* observer = m_Observers.get(note->getKey());
	if (observer) {
		for (gint i = 0; i < observer->getObsCount(); i++) {
			GObserver* obs = observer->getObs(i);
			note->setObserverObj(obs->getObj());
			obs->run(note);
		}
	}
}
