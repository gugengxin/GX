#ifndef GCSLWROOT_H
#define GCSLWROOT_H

#include "GCSLWriter.h"
#include "GCSLWHT.h"

class GCSLWRoot : public GCSLWriter
{
    Q_OBJECT
public:
    GCSLWRoot(QObject *parent);

    virtual bool compile(GCSLTokenReader& reader,GCSLError* errOut);
    virtual bool make(QString& strWarp,QString& strOut,GCSLError* errOut);

    virtual void addMainWHTDef(GCSLWHTMDef* v);

private:
    QList<GCSLWHTMDef*> m_MainWHTDefs;
};

#endif // GCSLWROOT_H
