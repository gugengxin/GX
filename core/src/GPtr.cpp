#include "GPtr.h"
#include "GXGObject.h"

GX_GOBJECT_IMPLEMENT(GPtr, GObject);

GPtr::GPtr()
{
	m_Value = NULL;
}


GPtr::~GPtr()
{
}
