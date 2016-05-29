#include "GShader.h"


GShader::GShader()
{
    m_Index[0]=0;
    m_Index[1]=0;
    m_Index[2]=0;
    m_Index[3]=0;
}


GShader::~GShader()
{
}


void GShader::setIndex(guint8 idx0,guint8 idx1,guint8 idx2,guint8 idx3)
{
    m_Index[0]=idx0;
    m_Index[1]=idx1;
    m_Index[2]=idx2;
    m_Index[3]=idx3;
}