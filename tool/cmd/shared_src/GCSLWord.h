#ifndef GCSLWORD_H
#define GCSLWORD_H

#include <QObject>
#include "GCSLToken.h"

class GCSLWord : public QObject
{
    Q_OBJECT
public:
    GCSLWord(GCSLToken::Type tkt,const char* ID,QObject* parent);
    GCSLWord(GCSLToken::Type tkt,const QString& ID,QObject* parent);
    GCSLWord(GCSLToken::Type tkt,
             const char* ID,
             const char* glID,
             const char* glesID,
             const char* hlID,
             const char* mID,
             QObject* parent);

    GCSLToken::Type getTokenType() {
        return m_TkType;
    }
    QString& getID() {
        return m_ID;
    }
    QString& getSLID(int i) {
        return m_SLID[i];
    }

private:
    GCSLToken::Type m_TkType;
    QString m_ID;

    QString m_SLID[4];
};

#endif // GCSLWORD_H
