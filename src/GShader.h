#pragma once

#include "GXPrefix.h"

class GShader
{
	friend class GContext;
protected:
	GShader();
	virtual ~GShader();

    void setIndex(guint8 idx0,guint8 idx1,guint8 idx2,guint8 idx3);

private:
    guint8 m_Index[4];
};

