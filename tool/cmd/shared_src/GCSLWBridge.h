#ifndef GCSLWBRIDGE_H
#define GCSLWBRIDGE_H

#include "GCSLWriter.h"

class GCSLWBridge : public GCSLWriter
{
    Q_OBJECT
public:
    explicit GCSLWBridge(QObject *parent = 0);
    virtual bool compile(GCSLTokenReader& reader,GCSLError* errOut);
private:

};


class GCSLWBridgeVar : public GCSLWriter
{
    Q_OBJECT
public:
    explicit GCSLWBridgeVar(QObject *parent = 0);

    virtual bool compile(GCSLTokenReader& reader,GCSLError* errOut);

private:
    GCSLToken*  m_LMH;
    GCSLToken*  m_Type;
    QString     m_Name;
};

#endif // GCSLWBRIDGE_H
