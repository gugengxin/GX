#include "GCSLWriter.h"
#include "GCSL.h"

GCSLWriter::GCSLWriter(QObject *parent) : QObject(parent)
{
    QObject* obj=parent;
    while (!obj->inherits("GCSL")) {
        obj=obj->parent();
    }
    m_SL=(GCSL*)obj;
}
