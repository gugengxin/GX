#include "GCSLReader.h"

GCSLReader::GCSLReader(QString *pText, QObject *parent) :
    QObject(parent)
{
    m_Text=pText;
    m_CurIdx=0;
    m_Row=0;
    m_Column=-1;
}

QChar GCSLReader::getChar()
{
    if(m_CurIdx>=m_Text->length()) {
        return '\0';
    }
    m_Column++;
    return m_Text->at(m_CurIdx++);
}

void GCSLReader::ungetChar()
{
    m_CurIdx--;
    m_Column--;
    if(m_Column<0) {
        m_Row--;
        m_Column=m_ColList.last();
        m_ColList.removeLast();
    }
}

void GCSLReader::ungetChar(int num)
{
    for(int i=0;i<num;i++) {
        ungetChar();
    }
}

void GCSLReader::wrap()
{
    m_Row++;
    m_ColList.append(m_Column);
    m_Column=-1;
}
