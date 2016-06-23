#include "GNotice.h"
#include "GXGObject.h"

GX_GOBJECT_IMPLEMENT(GNotice, GObject);

GNotice::GNotice()
{
	m_Key=NULL;
	m_Obj = NULL;
	m_ObsObj = NULL;
}


GNotice::~GNotice()
{
	GO::release(m_Key);
	GO::release(m_Obj);
	GO::release(m_ObsObj);
}


void GNotice::setKey(GObject* v)
{
	GO::retain(v);
	GO::release(m_Key);
	m_Key = v;
}
void GNotice::setObj(GObject* v)
{
	GO::retain(v);
	GO::release(m_Obj);
	m_Obj = v;
}
void GNotice::setObserverObj(GObject* v)
{
	GO::retain(v);
	GO::release(m_ObsObj);
	m_ObsObj = v;
}
