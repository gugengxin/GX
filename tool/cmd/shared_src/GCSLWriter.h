﻿#ifndef GCSLWRITER_H
#define GCSLWRITER_H

#include <QObject>
#include <QList>
#include "GCSLReader.h"
#include "GCSLError.h"
#include "GCSLTokenReader.h"


class GCSL;
class GCSLWHTMDef;

class GCSLWriter : public QObject
{
    Q_OBJECT
public:
    GCSLWriter(QObject *parent);


    virtual bool compile(GCSLTokenReader& reader,GCSLError* errOut)=0;
    virtual bool make(QString& strWarp,QString& strOut,GCSLError* errOut);

    void addSubWrite(GCSLWriter* v) {
        v->setParent(this);
        m_SubWrites.append(v);
    }

    virtual void addMainWHTDef(GCSLWHTMDef *v);

    int getSubWriteCount() {
        return m_SubWrites.length();
    }

    GCSLWriter* getSubWrites(int idx) {
        return m_SubWrites[idx];
    }

private:
    GCSL* m_SL;
    QList<GCSLWriter*> m_SubWrites;
};

#endif // GCSLWRITER_H
