#ifndef GCSLWHT_H
#define GCSLWHT_H

#include "GCSLWriter.h"

class GCSLWHT
{
public:
    static bool compile(GCSLWriter* parent,GCSLToken* token,GCSLTokenReader& reader,GCSLError* errOut);
};

class GCSLWHTMDef : public GCSLWriter
{
    Q_OBJECT
public:
    GCSLWHTMDef(QObject* parent);

    virtual bool compile(GCSLTokenReader& reader,GCSLError* errOut);

private:
    QString m_Name;
    int m_Index;
};

class GCSLWHTDef : public GCSLWriter
{
    Q_OBJECT
public:
    GCSLWHTDef(QObject* parent);

    virtual bool compile(GCSLTokenReader& reader,GCSLError* errOut);

private:
    QString m_Name;
};

class GCSLWHTIf : public GCSLWriter
{
    Q_OBJECT
public:
    GCSLWHTIf(QObject* parent);

    virtual bool compile(GCSLTokenReader& reader,GCSLError* errOut);
private:
    QList<GCSLToken*> m_Conds;
};

class GCSLWHTElif : public GCSLWriter
{
    Q_OBJECT
public:
    GCSLWHTElif(QObject* parent);

    virtual bool compile(GCSLTokenReader& reader,GCSLError* errOut);
private:
    QList<GCSLToken*> m_Conds;
};

class GCSLWHTElse : public GCSLWriter
{
    Q_OBJECT
public:
    GCSLWHTElse(QObject* parent);

    virtual bool compile(GCSLTokenReader& reader,GCSLError* errOut);
};

class GCSLWHTEnd : public GCSLWriter
{
    Q_OBJECT
public:
    GCSLWHTEnd(QObject* parent);

    virtual bool compile(GCSLTokenReader& reader,GCSLError* errOut);
};




#endif // GCSLWHT_H
