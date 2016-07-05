//
//  GWString.h
//  GX
//
//  Created by Gengxin Gu on 16/5/4.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GWString_h
#define GWString_h

#include "GXPrefix.h"
#include "GDataString.h"


#include "GXGObject.h"

class GWString : public GDataString<gwchar> {
    GX_GOBJECT(GWString);
public:
	class Formater : public GDataString<gwchar>::Formater {
		friend class GWString;
	private:
		Formater(GWString* str, gint cursor);
	public:
	};
public:
	virtual bool isEqual(GObject* obj);

	const gwchar* c_str();

	void set(gchar v, gint count=1);
	void append(gchar v, gint count=1);
	void insert(gint idx, gchar v, gint count=1);
	void replace(gint idx, gint lenR, gchar v, gint count=1);

	void set(gwchar v, gint count=1);
	void append(gwchar v, gint count=1);
	void insert(gint idx, gwchar v, gint count=1);
	void replace(gint idx, gint lenR, gwchar v, gint count=1);

	void set(const gchar* v, gint len = -1, gint count=1);
	void append(const gchar* v, gint len = -1, gint count = 1);
	void insert(gint idx, const gchar* v, gint len = -1, gint count = 1);
	void replace(gint idx, gint lenR, const gchar* v, gint len = -1, gint count = 1); \
		void replace(gint idx, gint lenR,
		gchar preChar, gint preCount,
		gchar sufChar, gint sufCount,
		const gchar* v, gint len = -1, gint count = 1);
	void set(const gwchar* v, gint len = -1, gint count = 1);
	void append(const gwchar* v, gint len = -1, gint count = 1);
	void insert(gint idx, const gwchar* v, gint len = -1, gint count = 1);
	void replace(gint idx, gint lenR, const gwchar* v, gint len = -1, gint count = 1);
	void replace(gint idx, gint lenR,
		gwchar preChar, gint preCount,
		gwchar sufChar, gint sufCount,
		const gwchar* v, gint len = -1, gint count = 1);

	void setInt16(gint16 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
	void appendInt16(gint16 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
	void insertInt16(gint idx, gint16 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
	void replaceInt16(gint idx, gint lenR, gint16 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');

	void setUint16(guint16 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
	void appendUint16(guint16 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
	void insertUint16(gint idx, guint16 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
	void replaceUint16(gint idx, gint lenR, guint16 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');

	void setInt32(gint32 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
	void appendInt32(gint32 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
	void insertInt32(gint idx, gint32 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
	void replaceInt32(gint idx, gint lenR, gint32 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');

	void setUint32(guint32 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
	void appendUint32(guint32 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
	void insertUint32(gint idx, guint32 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
	void replaceUint32(gint idx, gint lenR, guint32 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');

	void setInt64(gint64 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
	void appendInt64(gint64 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
	void insertInt64(gint idx, gint64 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
	void replaceInt64(gint idx, gint lenR, gint64 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');

	void setUint64(guint64 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
	void appendUint64(guint64 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
	void insertUint64(gint idx, guint64 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
	void replaceUint64(gint idx, gint lenR, guint64 v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');

	void setFloat32(gfloat32 v, gint precision = 6, gint vsLen = 0, gwchar fillChar = L' ');
	void appendFloat32(gfloat32 v, gint precision = 6, gint vsLen = 0, gwchar fillChar = L' ');
	void insertFloat32(gint idx, gfloat32 v, gint precision = 6, gint vsLen = 0, gwchar fillChar = L' ');
	void replaceFloat32(gint idx, gint lenR, gfloat32 v, gint precision = 6, gint vsLen = 0, gwchar fillChar = L' ');

	void setFloat64(gfloat64 v, gint precision = 6, gint vsLen = 0, gwchar fillChar = L' ');
	void appendFloat64(gfloat64 v, gint precision = 6, gint vsLen = 0, gwchar fillChar = L' ');
	void insertFloat64(gint idx, gfloat64 v, gint precision = 6, gint vsLen = 0, gwchar fillChar = L' ');
	void replaceFloat64(gint idx, gint lenR, gfloat64 v, gint precision = 6, gint vsLen = 0, gwchar fillChar = L' ');


	void setInt(gint v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
	void appendInt(gint v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
	void insertInt(gint idx, gint v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
	void replaceInt(gint idx, gint lenR, gint v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');

	void setUint(guint v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
	void appendUint(guint v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
	void insertUint(gint idx, guint v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');
	void replaceUint(gint idx, gint lenR, guint v, GX::StringRadix radix = GX::SR_Decimal, gint vsLen = 0, gwchar fillChar = L' ');

	void setFloat(gfloat v, gint precision = 6, gint vsLen = 0, gwchar fillChar = L' ');
	void appendFloat(gfloat v, gint precision = 6, gint vsLen = 0, gwchar fillChar = L' ');
	void insertFloat(gint idx, gfloat v, gint precision = 6, gint vsLen = 0, gwchar fillChar = L' ');
	void replaceFloat(gint idx, gint lenR, gfloat v, gint precision = 6, gint vsLen = 0, gwchar fillChar = L' ');

	void setPtr(void* v, GX::StringRadix radix = GX::SR_Hex, gint vsLen = 0, gwchar fillChar = L' ');
	void appendPtr(void* v, GX::StringRadix radix = GX::SR_Hex, gint vsLen = 0, gwchar fillChar = L' ');
	void insertPtr(gint idx, void* v, GX::StringRadix radix = GX::SR_Hex, gint vsLen = 0, gwchar fillChar = L' ');
	void replacePtr(gint idx, gint lenR, void* v, GX::StringRadix radix = GX::SR_Hex, gint vsLen = 0, gwchar fillChar = L' ');
};

#include "GXGObjectUD.h"

#endif /* GWString_h */
