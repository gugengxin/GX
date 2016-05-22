#ifndef GCSLWFP_H
#define GCSLWFP_H

#include "GCSLWriter.h"

class GCSLWFP : public GCSLWriter
{
    Q_OBJECT
public:
    explicit GCSLWFP(QObject *parent = 0);

    virtual bool compile(GCSLTokenReader& reader,GCSLError* errOut);
};

#endif // GCSLWFP_H
