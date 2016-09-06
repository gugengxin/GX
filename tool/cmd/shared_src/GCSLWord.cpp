#include "GCSLWord.h"

GCSLWord::GCSLWord(GCSLToken::Type tkt, const char *ID, QObject *parent) :
    QObject(parent)
{
    m_TkType=tkt;
    m_ID=ID;
    m_SLID[0]=m_ID;
    m_SLID[1]=m_ID;
    m_SLID[2]=m_ID;
    m_SLID[3]=m_ID;
}

GCSLWord::GCSLWord(GCSLToken::Type tkt, const QString &ID, QObject *parent) :
    QObject(parent)
{
    m_TkType=tkt;
    m_ID=ID;
    m_SLID[0]=m_ID;
    m_SLID[1]=m_ID;
    m_SLID[2]=m_ID;
    m_SLID[3]=m_ID;
}

GCSLWord::GCSLWord(GCSLToken::Type tkt,
                   const char *ID,
                   const char *glID,
                   const char *glesID,
                   const char *hlID,
                   const char *mID,
                   QObject *parent) :
    QObject(parent)
{
    m_TkType=tkt;
    m_ID=ID;
    m_SLID[0]=glID;
    m_SLID[1]=glesID;
    m_SLID[2]=hlID;
    m_SLID[3]=mID;
}
