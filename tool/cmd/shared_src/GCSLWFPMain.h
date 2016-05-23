#ifndef GCSLWFPMAIN_H
#define GCSLWFPMAIN_H

#include "GCSLWriter.h"

class GCSLWFPMain : public GCSLWriter
{
    Q_OBJECT
public:
    explicit GCSLWFPMain(QObject *parent = 0);

    virtual bool compile(GCSLTokenReader& reader,GCSLError* errOut);
};

#endif // GCSLWFPMAIN_H
