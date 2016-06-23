#pragma once
#include "GXPrefix.h"
#include "GObject.h"


#include "GXGObject.h"

class GNumber : public GObject
{
	GX_GOBJECT(GNumber);
public:
	typedef enum _Type {
		Bool,
		Int8,
		Uint8,
		Int16,
		Uint16,
		Int32,
		Uint32,
		Int64,
		Uint64,
		Float32,
		Float64,
		Pointer,
	} Type;
private:
	Type m_Type;
	union {
		bool	b8;
		gint8	i8;
		guint8	u8;
		gint16	i16;
		guint16 u16;
		gint32	i32;
		guint32 u32;
		gint64	i64;
		guint64 u64;
		gfloat32 f32;
		gfloat64 f64;
		void*	ptr;
	} m_Value;
};


#include "GXGObjectUD.h"