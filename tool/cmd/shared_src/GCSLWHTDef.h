#ifndef GCSLWHTDEF_H
#define GCSLWHTDEF_H

#include "GCSLWriter.h"

class GCSLWHTDef : public GCSLWriter
{
public:
    GCSLWHTDef();

    virtual bool compile(GCSLTokenReader& reader,GCSLError* errOut);

private:
    int m_Index;
};

#endif // GCSLWHTDEF_H
