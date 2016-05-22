#include "GCSLTokenReader.h"

GCSLTokenReader::GCSLTokenReader(QList<GCSLToken *> *tlist, QObject *parent) : QObject(parent)
{
    m_Tokens=tlist;
    m_Index=0;
}

GCSLToken *GCSLTokenReader::getToken()
{
    if(m_Index>=m_Tokens->length()) {
        return NULL;
    }
    return (*m_Tokens)[m_Index++];
}

void GCSLTokenReader::ungetToken()
{
    m_Index--;
}

bool GCSLTokenReader::currentIsWarpped()
{
    return m_Index>0 && (*m_Tokens)[m_Index]->getRow() > (*m_Tokens)[m_Index-1]->getRow();
}

bool GCSLTokenReader::nextIsWarpped()
{
    return m_Index<m_Tokens->length()-1 && (*m_Tokens)[m_Index]->getRow() < (*m_Tokens)[m_Index+1]->getRow();
}

int GCSLTokenReader::getRow()
{
    return (*m_Tokens)[m_Index]->getRow();
}

int GCSLTokenReader::getColumn()
{
    return (*m_Tokens)[m_Index]->getColumn();
}
