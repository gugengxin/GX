#include "GShader.h"
#include "GContext.h"


GShader::GShader(guint8 idxA, guint8 idxB, guint8 idxC, guint8 idxD) :
#if defined(GX_OPENGL)
GOShader()
#elif defined(GX_DIRECTX)
GDShader()
#endif
{
	m_Index[0] = idxA;
	m_Index[1] = idxB;
	m_Index[2] = idxC;
	m_Index[3] = idxD;
}


GShader::~GShader()
{
}