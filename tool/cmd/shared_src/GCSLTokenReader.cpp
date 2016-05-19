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
