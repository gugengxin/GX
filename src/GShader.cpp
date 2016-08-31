#include "GShader.h"
#include "GContext.h"


GShader::GShader(GContext* ctx,guint8 idxA, guint8 idxB, guint8 idxC, guint8 idxD)
{
    m_Context=ctx;
	m_Index[0] = idxA;
	m_Index[1] = idxB;
	m_Index[2] = idxC;
	m_Index[3] = idxD;
}


GShader::~GShader()
{
}