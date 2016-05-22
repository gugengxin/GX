#ifndef GCSLWHT_H
#define GCSLWHT_H

#include "GCSLWriter.h"

class GCSLWHT
{
public:
    static bool tokenIsHT(GCSLToken* token) {

    }
};


class GCSLWHTDef : public GCSLWriter
{
    Q_OBJECT
public:
    GCSLWHTDef(QObject* parent);

    virtual bool compile(GCSLTokenReader& reader,GCSLError* errOut);

private:
    QString m_Name;
    int m_Index;
};



class GCSLWHTIf : public GCSLWriter
{
    Q_OBJECT
public:
    GCSLWHTIf(QObject* parent);

    virtual bool compile(GCSLTokenReader& reader,GCSLError* errOut);
private:
    QList<GCSLToken*> m_Conds;
};


class GCSLWHTElif : public GCSLWriter
{
    Q_OBJECT
public:
    GCSLWHTElif(QObject* parent);

    virtual bool compile(GCSLTokenReader& reader,GCSLError* errOut);
private:
    QList<GCSLToken*> m_Conds;
};






#endif // GCSLWHT_H
