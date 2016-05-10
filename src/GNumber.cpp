#include "GNumber.h"

GX_OBJECT_IMPLEMENT(GNumber, GObject);

GNumber::GNumber()
{
	m_Type = (Type)0;
	memset(&m_Value, 0, sizeof(m_Value));
}


GNumber::~GNumber()
{
}
