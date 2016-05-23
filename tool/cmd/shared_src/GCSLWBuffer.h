#ifndef GCSLWBUFFER_H
#define GCSLWBUFFER_H

#include "GCSLWriter.h"

class GCSLWBuffer : public GCSLWriter
{
    Q_OBJECT
public:
    explicit GCSLWBuffer(QObject *parent = 0);

    virtual bool compile(GCSLTokenReader& reader,GCSLError* errOut);

private:
    int m_Slot;
};

class GCSLWBufferVar : public GCSLWriter
{
    Q_OBJECT
public:
    explicit GCSLWBufferVar(QObject *parent = 0);

    virtual bool compile(GCSLTokenReader& reader,GCSLError* errOut);

private:
    GCSLToken*  m_LMH;
    GCSLToken*  m_Type;
    QString     m_Name;
};

#endif // GCSLWBUFFER_H
