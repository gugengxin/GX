#include "GCSLError.h"

GCSLError::GCSLError(QObject *parent) : QObject(parent)
{
    m_Code=C_None;
    m_Row=-1;
    m_Column=-1;
}
