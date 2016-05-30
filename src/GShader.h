#pragma once

#include "GXPrefix.h"
#include "GOShader.h"
#include "GDShader.h"


class GShader : public
#if defined(GX_OPENGL)
	GOShader
#elif defined(GX_DIRECTX)
	GDShader
#endif
{
	friend class GContext;
protected:
	GShader(guint8 idxA, guint8 idxB, guint8 idxC, guint8 idxD);
	virtual ~GShader();

private:
    guint8 m_Index[4];
};

