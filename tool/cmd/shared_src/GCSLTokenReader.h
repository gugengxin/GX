#ifndef GCSLTOKENREADER_H
#define GCSLTOKENREADER_H

#include <QObject>
#include <QList>
#include "GCSLToken.h"

class GCSLTokenReader : public QObject
{
    Q_OBJECT
public:
    explicit GCSLTokenReader(QList<GCSLToken*>* tlist,QObject *parent = 0);

    GCSLToken* getToken();
    void ungetToken();

private:
    QList<GCSLToken*>* m_Tokens;
    int m_Index;
};

#endif // GCSLTOKENREADER_H
