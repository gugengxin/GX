#include "GObserver.h"

GObserver::GObserver()
{
	m_Target = NULL;
	memset(&m_Action, 0, sizeof(m_Action));
	m_Obj = NULL;
}


GObserver::~GObserver()
{
	GO::release(m_Obj);
}


void GObserver::set(GObject* target, GX::Selector sel, GObject* obj)
{
	m_Target = target;
	m_Action.sel = sel;
	GO::retain(obj);
	GO::release(m_Obj);
	m_Obj = obj;
}
void GObserver::set(GX::Callback cbk, GObject* obj)
{
	m_Target = NULL;
	m_Action.cbk = cbk;
	GO::retain(obj);
	GO::release(m_Obj);
	m_Obj = obj;
}
void GObserver::run(GObject* obj)
{
	if (m_Target) {
		(m_Target->*m_Action.sel)(obj);
	}
	else {
		m_Action.cbk(obj);
	}
}