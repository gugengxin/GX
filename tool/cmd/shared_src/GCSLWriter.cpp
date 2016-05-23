#include "GCSLWriter.h"
#include "GCSL.h"
#include "GCSLWRoot.h"

GCSLWriter::GCSLWriter(QObject *parent) : QObject(parent)
{
    QObject* obj=parent;
    while (!obj->inherits("GCSL")) {
        obj=obj->parent();
    }
    m_SL=(GCSL*)obj;
}

bool GCSLWriter::make(QString &strWarp, QString &strOut, GCSLError *errOut)
{
    for(int i=0;i<m_SubWrites.length();i++) {
        if(!m_SubWrites[i]->make(strWarp,strOut,errOut)) {
            return false;
        }
    }
    return true;
}

void GCSLWriter::addMainWHTDef(GCSLWHTMDef *v)
{
    GCSLWriter* wr=(GCSLWriter*)this->parent();
    while(!inherits("GCSLWRoot")) {
        wr=(GCSLWriter*)wr->parent();
    }
    wr->addMainWHTDef(v);
}
