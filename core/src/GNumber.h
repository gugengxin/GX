#ifndef GNumber_h
#define GNumber_h

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
	} Type;
    
    inline Type getType() {
        return m_Type;
    }
public:
    void set(bool v);
    void set(gint8 v);
    void set(guint8 v);
    void set(gint16 v);
    void set(guint16 v);
    void set(gint32 v);
    void set(guint32 v);
    void set(gint64 v);
    void set(guint64 v);
    void set(gfloat32 v);
    void set(gfloat64 v);
    
    bool getBool();
    gint8 getInt8();
    guint8 getUint8();
    gint16 getInt16();
    guint16 getUint16();
    gint32 getInt32();
    guint32 getUint32();
    gint64 getInt64();
    guint64 getUint64();
    gfloat32 getFloat32();
    gfloat64 getFloat64();
    
public:
    gint getInt();
    guint getUint();
    gfloat getFloat();
    
public:
    virtual guint getHash();
    virtual bool isEqual(GObject* obj);
    virtual GString* description();
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
	} m_Value;
};


#include "GXGObjectUD.h"

#endif
