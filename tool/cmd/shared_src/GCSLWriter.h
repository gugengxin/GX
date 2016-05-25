#ifndef GCSLWRITER_H
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
    typedef enum _SLType {
        SLT_GLSL=0,
        SLT_GLSL_ES,
        SLT_HLSL,
    } SLType;

    class MakeParam {
    public:
        MakeParam(SLType slt,const QString& sw) {
            slType=slt;
            strWarp=sw;
            lineLevel=0;
        }

        SLType slType;
        QString strWarp;
        int lineLevel;
    };
    static void strAppend(QString& qs,const char* str,int count);
    static void strAppendTab(QString& qs,int count);
public:
    GCSLWriter(QObject *parent);

    void addSubWrite(GCSLWriter* v) {
        v->setParent(this);
        m_SubWrites.append(v);
    }
    virtual void addMainWHTDef(GCSLWHTMDef *v);
    void insertSubWrites(int idx,GCSLWriter* v) {
        v->setParent(this);
        m_SubWrites.insert(idx,v);
    }

    int getSubWriteCount() {
        return m_SubWrites.length();
    }
    GCSLWriter* getSubWrites(int idx) {
        return m_SubWrites[idx];
    }

    QString &getWordSLID(GCSLToken* token,SLType slt);


    virtual bool compile(GCSLTokenReader& reader,GCSLError* errOut)=0;
    virtual bool makeVS(MakeParam& param,QString& strOut,GCSLError* errOut);
    virtual bool makeFP(MakeParam& param,QString& strOut,GCSLError* errOut);

private:
    GCSL* m_SL;
    QList<GCSLWriter*> m_SubWrites;
};

#endif // GCSLWRITER_H
