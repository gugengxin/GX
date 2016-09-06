#ifndef GCSLWLAYOUT_H
#define GCSLWLAYOUT_H

#include "GCSLWriter.h"

class GCSLWLayout : public GCSLWriter
{
    Q_OBJECT
public:
    explicit GCSLWLayout(QObject *parent = 0);

    virtual bool compile(GCSLTokenReader& reader,GCSLError* errOut);
    virtual bool makeVS(MakeParam& param,QString& strOut,GCSLError* errOut);
    virtual bool makeFP(MakeParam& param,QString& strOut,GCSLError* errOut);
};


class GCSLWLayoutVar : public GCSLWriter
{
    Q_OBJECT
public:
    explicit GCSLWLayoutVar(QObject *parent = 0);

    virtual bool compile(GCSLTokenReader& reader,GCSLError* errOut);
    virtual bool makeVS(MakeParam& param,QString& strOut,GCSLError* errOut);
    virtual bool makeFP(MakeParam& param,QString& strOut,GCSLError* errOut);
private:
    GCSLToken*  m_LMH;
    GCSLToken*  m_Type;
    QString     m_Name;
    GCSLToken*  m_SemanticName; //for hlsl
    int         m_SemanticIndex;

    GCSLToken*  m_AttributeName; //for msl
    int         m_AttributeIndex;
};


#endif // GCSLWLAYOUT_H
