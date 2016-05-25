#include "GCSLWriter.h"
#include "GCSL.h"
#include "GCSLWRoot.h"

void GCSLWriter::strAppend(QString &qs, const char *str, int count)
{
    for(int i=0;i<count;i++) {
        qs.append(str);
    }
}

void GCSLWriter::strAppendTab(QString &qs, int count)
{
    strAppend(qs,"\t",count);
}

GCSLWriter::GCSLWriter(QObject *parent) : QObject(parent)
{
    QObject* obj=parent;
    while (!obj->inherits("GCSL")) {
        obj=obj->parent();
    }
    m_SL=(GCSL*)obj;
}

void GCSLWriter::addMainWHTDef(GCSLWHTMDef *v)
{
    GCSLWriter* wr=(GCSLWriter*)this->parent();
    while(!inherits("GCSLWRoot")) {
        wr=(GCSLWriter*)wr->parent();
    }
    wr->addMainWHTDef(v);
}

QString &GCSLWriter::getWordSLID(GCSLToken *token, GCSLWriter::SLType slt)
{
    return m_SL->getWord(token->getID())->getSLID(slt);
}


bool GCSLWriter::makeVS(MakeParam& param, QString &strOut, GCSLError *errOut)
{
    for(int i=0;i<m_SubWrites.length();i++) {
        if(!m_SubWrites[i]->makeVS(param,strOut,errOut)) {
            return false;
        }
    }
    return true;
}

bool GCSLWriter::makeFP(MakeParam& param, QString &strOut, GCSLError *errOut)
{
    for(int i=0;i<m_SubWrites.length();i++) {
        if(!m_SubWrites[i]->makeFP(param,strOut,errOut)) {
            return false;
        }
    }
    return true;
}
