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
    virtual bool makeVS(MakeParam& param,QString& strOut,GCSLError* errOut);
    virtual bool makeFP(MakeParam& param,QString& strOut,GCSLError* errOut);



private:

};

#endif // GCSLWROOT_H
