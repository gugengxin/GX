#ifndef GCSLWVSMAIN_H
#define GCSLWVSMAIN_H

#include "GCSLWriter.h"

class GCSLWVSMain : public GCSLWriter
{
    Q_OBJECT
public:
    explicit GCSLWVSMain(QObject *parent = 0);

    virtual bool compile(GCSLTokenReader& reader,GCSLError* errOut);
    virtual bool makeVS(MakeParam& param,QString& strOut,GCSLError* errOut);
    virtual bool makeFP(MakeParam& param,QString& strOut,GCSLError* errOut);
};

#endif // GCSLWVSMAIN_H
