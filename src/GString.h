//
//  GString.h
//  GX
//
//  Created by Gengxin Gu on 16/4/29.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GString_h
#define GString_h

#include "GXPrefix.h"
#include "GDataString.h"

#include "GXGObject.h"

class GString : public GDataString<gchar> {
	friend class GOShader;
	friend class GZipReader;
    friend class GAppBundle;
    GX_GOBJECT(GString);
public:
	class Formater : public GDataString<gchar>::Formater {
		friend class GString;
	private:
		Formater(GString* str, gint cursor, gint cursorEnd);
	public:
		Formater& arg(gchar v,gint count=1);
        Formater& arg(gwchar v,gint count=1);
	};
public:
	virtual bool isEqual(GObject* obj);

	const gchar* c_str();

	void set(gchar v, gint count=1);
	void append(gchar v, gint count=1);
	void insert(gint idx, gchar v, gint count=1);
	void replace(gint idx, gint lenR, gchar v, gint count=1);

	void set(gwchar v, gint count=1);
	void append(gwchar v, gint count=1);
	void insert(gint idx, gwchar v, gint count=1);
	void replace(gint idx, gint lenR, gwchar v, gint count=1);

	void set(const gchar* v, gint len = -1, gint count = 1);
	void append(const gchar* v, gint len = -1, gint count = 1);
	void insert(gint idx, const gchar* v, gint len = -1, gint count = 1);
	void replace(gint idx, gint lenR, const gchar* v, gint len = -1, gint count = 1);
	void replace(gint idx, gint lenR, 
		gchar preChar, gint preCount,
		gchar sufChar, gint sufCount,
		const gchar* v, gint len=-1, gint count=1);

	void set(const gwchar* v, gint len = -1, gint count = 1);
	void append(const gwchar* v, gint len = -1, gint count = 1);
	void insert(gint idx, const gwchar* v, gint len = -1, gint count = 1);
	void replace(gint idx, gint lenR, const gwchar* v, gint len = -1, gint count = 1);
	void replace(gint idx, gint lenR,
		gwchar preChar, gint preCount,
		gwchar sufChar, gint sufCount,
		const gwchar* v, gint len = -1, gint count = 1);
	
	
	void setInt16(gint16 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
	void appendInt16(gint16 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
	void insertInt16(gint idx, gint16 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
	void replaceInt16(gint idx, gint lenR, gint16 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');

	void setUint16(guint16 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
	void appendUint16(guint16 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
	void insertUint16(gint idx, guint16 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
	void replaceUint16(gint idx, gint lenR, guint16 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');

	void setInt32(gint32 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
	void appendInt32(gint32 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
	void insertInt32(gint idx, gint32 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
	void replaceInt32(gint idx, gint lenR, gint32 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
	
	void setUint32(guint32 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
	void appendUint32(guint32 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
	void insertUint32(gint idx, guint32 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
	void replaceUint32(gint idx, gint lenR, guint32 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');

	void setInt64(gint64 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
	void appendInt64(gint64 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
	void insertInt64(gint idx, gint64 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
	void replaceInt64(gint idx, gint lenR, gint64 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
	
	void setUint64(guint64 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
	void appendUint64(guint64 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
	void insertUint64(gint idx, guint64 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
	void replaceUint64(gint idx, gint lenR, guint64 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');

	void setFloat32(gfloat32 v, gint precision = 6, gint vsLen = 0, gchar fillChar = ' ');
	void appendFloat32(gfloat32 v, gint precision = 6, gint vsLen = 0, gchar fillChar = ' ');
	void insertFloat32(gint idx, gfloat32 v, gint precision = 6, gint vsLen = 0, gchar fillChar = ' ');
	void replaceFloat32(gint idx, gint lenR, gfloat32 v, gint precision = 6, gint vsLen = 0, gchar fillChar = ' ');

	void setFloat64(gfloat64 v, gint precision = 6, gint vsLen = 0, gchar fillChar = ' ');
	void appendFloat64(gfloat64 v, gint precision = 6, gint vsLen = 0, gchar fillChar = ' ');
	void insertFloat64(gint idx, gfloat64 v, gint precision = 6, gint vsLen = 0, gchar fillChar = ' ');
	void replaceFloat64(gint idx, gint lenR, gfloat64 v, gint precision = 6, gint vsLen = 0, gchar fillChar = ' ');

	void setInt(gint v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
	void appendInt(gint v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
	void insertInt(gint idx, gint v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
	void replaceInt(gint idx, gint lenR, gint v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
	
	void setUint(guint v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
	void appendUint(guint v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
	void insertUint(gint idx, guint v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
	void replaceUint(gint idx, gint lenR, guint v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');

	void setFloat(gfloat v, gint precision = 6, gint vsLen = 0, gchar fillChar = ' ');
	void appendFloat(gfloat v, gint precision = 6, gint vsLen = 0, gchar fillChar = ' ');
	void insertFloat(gint idx, gfloat v, gint precision = 6, gint vsLen = 0, gchar fillChar = ' ');
	void replaceFloat(gint idx, gint lenR, gfloat v, gint precision = 6, gint vsLen = 0, gchar fillChar = ' ');

	void setPtr(void* v, GX::StringRadix radix = GX::SR_Hex, gint vsLen = 0, gchar fillChar = ' ');
	void appendPtr(void* v, GX::StringRadix radix = GX::SR_Hex, gint vsLen = 0, gchar fillChar = ' ');
	void insertPtr(gint idx, void* v, GX::StringRadix radix = GX::SR_Hex, gint vsLen = 0, gchar fillChar = ' ');
	void replacePtr(gint idx, gint lenR, void* v, GX::StringRadix radix = GX::SR_Hex, gint vsLen = 0, gchar fillChar = ' ');

	Formater format(const gchar* fmt, gint len = -1);
	Formater appendFormat(const gchar* fmt, gint len = -1);
	Formater insertFormat(gint idx, const gchar* fmt, gint len = -1);
	Formater replaceFormat(gint idx, gint lenR, const gchar* fmt, gint len = -1);

public:
	void appendPathComponent(const gchar* component, gint len = -1);
	void appendPathComponent(const gwchar* component, gint len = -1);
};

#include "GXGObjectUD.h"

#endif /* GString_h */
