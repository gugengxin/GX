#ifndef GCSLWTEXTURE_H
#define GCSLWTEXTURE_H

#include "GCSLWriter.h"

class GCSLWTexture : public GCSLWriter
{
    Q_OBJECT
public:
    explicit GCSLWTexture(QObject *parent = 0);

    virtual bool compile(GCSLTokenReader& reader,GCSLError* errOut);

};

class GCSLWTextureVar : public GCSLWriter
{
    Q_OBJECT
public:
    explicit GCSLWTextureVar(QObject *parent = 0);

    virtual bool compile(GCSLTokenReader& reader,GCSLError* errOut);

private:
    GCSLToken*  m_LMH;
    GCSLToken*  m_Type;
    QString     m_Name;
    int         m_Slot;
};

#endif // GCSLWTEXTURE_H
