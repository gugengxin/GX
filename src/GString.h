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
    GX_GOBJECT(GString);
public:
	class Formater {
		friend class GString;
	private:
		Formater(GString* str, gint cursor) {
			m_String = str;
			m_Cursor = cursor;
		}
	public:
		Formater& arg(gchar v,gint count);
	private:
		GString* m_String;
		gint m_Cursor;
	};
public:
	virtual bool isEqual(GObject* obj);

	const gchar* c_str();

	void set(gchar v, gint count);
	void append(gchar v, gint count);
	void insert(gint idx, gchar v, gint count);
	void replace(gint idx, gint lenR, gchar v, gint count);

	void set(gwchar v, gint count);
	void append(gwchar v, gint count);
	void insert(gint idx, gwchar v, gint count);
	void replace(gint idx, gwchar v, gint count);

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

	void setInt32(gint32 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
	void appendInt32(gint32 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
	void insertInt32(gint idx, gint32 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
	void setUint32(guint32 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
	void appendUint32(guint32 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
	void insertUint32(gint idx, guint32 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');

	void setInt64(gint64 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
	void appendInt64(gint64 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
	void insertInt64(gint idx, gint64 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
	void setUint64(guint64 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
	void appendUint64(guint64 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
	void insertUint64(gint idx, guint64 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');

	void setFloat32(gfloat32 v, gint precision = 6, gint vsLen = 0, gchar fillChar = ' ');
	void appendFloat32(gfloat32 v, gint precision = 6, gint vsLen = 0, gchar fillChar = ' ');
	void insertFloat32(gint idx, gfloat32 v, gint precision = 6, gint vsLen = 0, gchar fillChar = ' ');

	void setFloat64(gfloat64 v, gint precision = 6, gint vsLen = 0, gchar fillChar = ' ');
	void appendFloat64(gfloat64 v, gint precision = 6, gint vsLen = 0, gchar fillChar = ' ');
	void insertFloat64(gint idx, gfloat64 v, gint precision = 6, gint vsLen = 0, gchar fillChar = ' ');

	void setInt(gint v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
	void appendInt(gint v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
	void insertInt(gint idx, gint v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
	void setUint(guint v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
	void appendUint(guint v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');
	void insertUint(gint idx, guint v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gchar fillChar = ' ');

	void setPtr(void* v, GX::StringRadix radix = GX::SR_Hex, gint vsLen = 0, gchar fillChar = ' ');
	void appendPtr(void* v, GX::StringRadix radix = GX::SR_Hex, gint vsLen = 0, gchar fillChar = ' ');
	void insertPtr(gint idx, void* v, GX::StringRadix radix = GX::SR_Hex, gint vsLen = 0, gchar fillChar = ' ');

	Formater format(const gchar* fmt, gint len = -1);
};

#include "GXGObjectUD.h"

#endif /* GString_h */
