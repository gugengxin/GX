#pragma once

#include "GXPrefix.h"
#include "GObject.h"


#include "GXGObject.h"

class GPtr : public GObject
{
	GX_GOBJECT(GPtr);
public:
	inline void* get() {
		return m_Value;
	}
	inline void set(void* v) {
		m_Value = v;
	}

private:
	void* m_Value;
};

#include "GXGObjectUD.h"