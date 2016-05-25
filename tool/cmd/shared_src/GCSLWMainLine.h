#ifndef GCSLWMAINLINE_H
#define GCSLWMAINLINE_H

#include "GCSLWriter.h"

class GCSLWMainLine : public GCSLWriter
{
    Q_OBJECT
public:
    explicit GCSLWMainLine(QObject *parent = 0);

    virtual bool compile(GCSLTokenReader& reader,GCSLError* errOut);
    virtual bool makeVS(MakeParam& param,QString& strOut,GCSLError* errOut);
    virtual bool makeFP(MakeParam& param,QString& strOut,GCSLError* errOut);

private:
    bool make(GCSLWriter::MakeParam &param,GCSLTokenReader& reader,QString &strOut, GCSLError *errOut);
private:
    QList<GCSLToken*> m_Tokens;
};

#endif // GCSLWMAINLINE_H
