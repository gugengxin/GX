#ifndef GCSLWBUFFER_H
#define GCSLWBUFFER_H

#include "GCSLWriter.h"

class GCSLWBuffer : public GCSLWriter
{
    Q_OBJECT
public:
    explicit GCSLWBuffer(QObject *parent = 0);

    virtual bool compile(GCSLTokenReader& reader,GCSLError* errOut);
    virtual bool makeVS(MakeParam& param,QString& strOut,GCSLError* errOut);
    virtual bool makeFP(MakeParam& param,QString& strOut,GCSLError* errOut);
};

class GCSLWBufferVar : public GCSLWriter
{
    Q_OBJECT
public:
    explicit GCSLWBufferVar(QObject *parent = 0);

    virtual bool compile(GCSLTokenReader& reader,GCSLError* errOut);
    virtual bool makeVS(MakeParam& param,QString& strOut,GCSLError* errOut);
    virtual bool makeFP(MakeParam& param,QString& strOut,GCSLError* errOut);
private:
    GCSLToken*  m_LMH;
    GCSLToken*  m_Type;
    QString     m_Name;
};

#endif // GCSLWBUFFER_H
