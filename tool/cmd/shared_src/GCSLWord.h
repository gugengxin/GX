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

    GCSLToken::Type getTokenType() {
        return m_TkType;
    }
    QString& getID() {
        return m_ID;
    }

private:
    GCSLToken::Type m_TkType;
    QString m_ID;
};

#endif // GCSLWORD_H
