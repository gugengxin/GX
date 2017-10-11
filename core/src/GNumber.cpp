#include "GNumber.h"
#include "GXGObject.h"
#include "GXMemory.h"

GX_GOBJECT_IMPLEMENT(GNumber, GObject);

GNumber::GNumber()
{
	m_Type = (Type)0;
	GX::gmemset(&m_Value, 0, sizeof(m_Value));
}


GNumber::~GNumber()
{
}

void GNumber::set(bool v)
{
    m_Type=Bool;
    m_Value.b8=v;
}
void GNumber::set(gint8 v)
{
    m_Type=Int8;
    m_Value.i8=v;
}
void GNumber::set(guint8 v)
{
    m_Type=Uint8;
    m_Value.u8=v;
}
void GNumber::set(gint16 v)
{
    m_Type=Int16;
    m_Value.i16=v;
}
void GNumber::set(guint16 v)
{
    m_Type=Uint16;
    m_Value.u16=v;
}
void GNumber::set(gint32 v)
{
    m_Type=Int32;
    m_Value.i32=v;
}
void GNumber::set(guint32 v)
{
    m_Type=Uint32;
    m_Value.u32=v;
}
void GNumber::set(gint64 v)
{
    m_Type=Int64;
    m_Value.i64=v;
}
void GNumber::set(guint64 v)
{
    m_Type=Uint64;
    m_Value.u64=v;
}
void GNumber::set(gfloat32 v)
{
    m_Type=Float32;
    m_Value.f32=v;
}
void GNumber::set(gfloat64 v)
{
    m_Type=Float64;
    m_Value.f64=v;
}


bool GNumber::getBool()
{
    switch (m_Type) {
        case Bool:
            return m_Value.b8;
#define M_CASE(t,v) \
        case t:\
            return m_Value.v!=0
            M_CASE(Int8,i8);
            M_CASE(Uint8,u8);
            M_CASE(Int16,i16);
            M_CASE(Uint16,u16);
            M_CASE(Int32,i32);
            M_CASE(Uint32,u32);
            M_CASE(Int64,i64);
            M_CASE(Uint64,u64);
#undef M_CASE
        case Float32:
            return m_Value.f32!=0.0f;
        case Float64:
            return m_Value.f64!=0.0;
        default:
            break;
    }
    return false;
}

#define M_CASE(vt,t,v) \
case t:\
    return GX_CAST_S(vt,m_Value.v)

#define M_FUN(vt,t,v,r) \
vt GNumber::get##t()\
{\
    switch (m_Type) {\
            M_CASE(vt,Bool,b8);\
            M_CASE(vt,Int8,i8);\
            M_CASE(vt,Uint8,u8);\
            M_CASE(vt,Int16,i16);\
            M_CASE(vt,Uint16,u16);\
            M_CASE(vt,Int32,i32);\
            M_CASE(vt,Uint32,u32);\
            M_CASE(vt,Int64,i64);\
            M_CASE(vt,Uint64,u64);\
            M_CASE(vt,Float32,f32);\
            M_CASE(vt,Float64,f64);\
        default:\
            break;\
    }\
    return r;\
}

M_FUN(gint8, Int8, i8, 0)
M_FUN(guint8, Uint8, u8, 0)
M_FUN(gint16, Int16, i16, 0)
M_FUN(guint16, Uint16, u16, 0)
M_FUN(gint32, Int32, i32, 0)
M_FUN(guint32, Uint32, u32, 0)
M_FUN(gint64, Int64, i64, 0LL)
M_FUN(guint64, Uint64, u64, 0LL)
M_FUN(gfloat32, Float32, f32, 0.0f)
M_FUN(gfloat64, Float64, f64, 0.0)

#undef M_CASE

gint GNumber::getInt()
{
#if GX_PTR_32BIT
    return getInt32();
#elif GX_PTR_64BIT
    return getInt64();
#endif
}
guint GNumber::getUint()
{
#if GX_PTR_32BIT
    return getUint32();
#elif GX_PTR_64BIT
    return getUint64();
#endif
}
gfloat GNumber::getFloat()
{
#if GX_PTR_32BIT
    return getFloat32();
#elif GX_PTR_64BIT
    return getFloat64();
#endif
}


guint GNumber::getHash()
{
    return getUint();
}
bool GNumber::isEqual(GObject* obj)
{
    if (obj->isMemberOfClass(GNumber::gclass)) {
        return getFloat64()==GX_CAST_R(GNumber*, obj)->getFloat64();
    }
    return false;
}
GString* GNumber::description()
{
    return GObject::description();
}
