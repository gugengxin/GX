#ifndef GCSLWFPMAIN_H
#define GCSLWFPMAIN_H

#include "GCSLWriter.h"

class GCSLWFPMain : public GCSLWriter
{
    Q_OBJECT
public:
    explicit GCSLWFPMain(QObject *parent = 0);

    virtual bool compile(GCSLTokenReader& reader,GCSLError* errOut);
    virtual bool makeVS(MakeParam& param,QString& strOut,GCSLError* errOut);
    virtual bool makeFP(MakeParam& param,QString& strOut,GCSLError* errOut);
};

#endif // GCSLWFPMAIN_H
