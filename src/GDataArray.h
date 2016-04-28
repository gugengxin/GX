#pragma once

#include "GXPrefix.h"
#include "GPieceData.h"

template <typename T,guint step>
class GDataArray : public GObject {
    GX_OBJECT(GDataArray);
public:
    
private:
    GPieceData m_Data;
};

GX_OBJECT_TEMPLATE_IMPLEMENT(typename T GX_COMMA guint step, GDataArray<T GX_COMMA step>, GObject);

template <typename T,guint step>
GDataArray<T,step>::GDataArray():
m_Data(sizeof(T)*step)
{

}
template <typename T,guint step>
GDataArray<T,step>::~GDataArray()
{
    
}
