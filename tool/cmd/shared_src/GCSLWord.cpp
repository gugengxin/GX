#include "GCSLWord.h"

GCSLWord::GCSLWord(GCSLToken::Type tkt, const char *ID, QObject *parent) :
    QObject(parent)
{
    m_TkType=tkt;
    m_ID=ID;
}

GCSLWord::GCSLWord(GCSLToken::Type tkt, const QString &ID, QObject *parent) :
    QObject(parent)
{
    m_TkType=tkt;
    m_ID=ID;
}
