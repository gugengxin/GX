#include "GCSLWVS.h"

GCSLWVS::GCSLWVS(QObject *parent) : GCSLWriter(parent)
{

}

bool GCSLWVS::compile(GCSLTokenReader &reader, GCSLError *errOut)
{
    GCSLToken* token=reader.getToken();



    return true;
}
