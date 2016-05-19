#ifndef GCSLWHT_H
#define GCSLWHT_H

#include "GCSLWriter.h"

class GCSLWHTDef : public GCSLWriter
{
public:
    GCSLWHTDef(QObject* parent);

    virtual bool compile(GCSLTokenReader& reader,GCSLError* errOut);

private:
    QString m_Name;
    int m_Index;
};



class GCSLWHTIf : public GCSLWriter
{
public:
    GCSLWHTIf(QObject* parent);

    virtual bool compile(GCSLTokenReader& reader,GCSLError* errOut);
private:
    QList<GCSLToken*> m_Conds;
};

#endif // GCSLWHT_H
