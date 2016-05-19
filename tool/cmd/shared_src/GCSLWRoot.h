#ifndef GCSLWROOT_H
#define GCSLWROOT_H

#include "GCSLWriter.h"

class GCSLWRoot : public GCSLWriter
{
    Q_OBJECT
public:
    GCSLWRoot(QObject *parent);

    virtual bool compile(GCSLTokenReader& reader,GCSLError* errOut);
private:

};

#endif // GCSLWROOT_H
