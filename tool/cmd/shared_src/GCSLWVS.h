#ifndef GCSLWVS_H
#define GCSLWVS_H

#include "GCSLWriter.h"

class GCSLWVS : public GCSLWriter
{
    Q_OBJECT
public:
    explicit GCSLWVS(QObject *parent = 0);

    virtual bool compile(GCSLTokenReader& reader,GCSLError* errOut);
    virtual bool makeVS(MakeParam& param,QString& strOut,GCSLError* errOut);
    virtual bool makeFP(MakeParam& param,QString& strOut,GCSLError* errOut);

private:

};

#endif // GCSLWVS_H
