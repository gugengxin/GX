//
//  GWString.cpp
//  GX
//
//  Created by Gengxin Gu on 16/5/4.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#include "GWString.h"
#include "GString.h"
#include "GXGObject.h"


GWString::Formater::Formater(GWString* str, gint cursor, gint cursorEnd) :
    GDataString<gwchar>::Formater(str, cursor, cursorEnd)
{

}



GX_GOBJECT_IMPLEMENT(GWString, GDataString<gwchar>);

GWString::GWString()
{
    
}

GWString::~GWString()
{
    
}

bool GWString::isEqual(GObject* obj) 
{
	if (obj->isKindOfClass(GWString::gclass)) {
		if (getHash() == obj->getHash()) {
			return getOWHashB() == GX_CAST_R(GWString*, obj)->getOWHashB() &&
				getOWHashC() == GX_CAST_R(GWString*, obj)->getOWHashC();
		}
	}
	else if (obj->isKindOfClass(GWString::gclass)) {
		if (getHash() == obj->getHash()) {
			return getOWHashB() == GX_CAST_R(GString*, obj)->getOWHashB() &&
				getOWHashC() == GX_CAST_R(GString*, obj)->getOWHashC();
		}
	}
	return false;
}

const gwchar* GWString::c_str()
{
	if (getLength() <= 0) {
		return L"";
	}
	return GX_CAST_R(const gwchar*, getDataPtr());
}

void GWString::set(gchar v, gint count)
{
	set((gwchar)v, count);
}
void GWString::append(gchar v, gint count)
{
	append((gwchar)v, count);
}
void GWString::insert(gint idx, gchar v, gint count)
{
	insert(idx, (gwchar)v, count);
}
void GWString::replace(gint idx, gint lenR, gchar v, gint count)
{
	replace(idx, lenR, (gwchar)v, count);
}

void GWString::set(gwchar v, gint count)
{
	if (count <= 0) {
		return;
	}
	if (changeCapability(count + 1)) {
		for (gint i = 0; i < count; i++) {
			getDataPtr()[i] = v;
		}
		setLength(count);
	}
}
void GWString::append(gwchar v, gint count)
{
	if (count <= 0) {
		return;
	}
	gint lenCur = getLength();
	if (changeCapability(lenCur + count + 1)) {
		for (gint i = 0; i < count; i++) {
			getDataPtr(lenCur)[i] = v;
		}
		setLength(lenCur + count);
	}
}
void GWString::insert(gint idx, gwchar v, gint count)
{
	replace(idx, 0, v, count);
}
void GWString::replace(gint idx, gint lenR, gwchar v, gint count)
{
	if (count <= 0) {
		return;
	}
	if (idx < 0 || lenR<0) {
		return;
	}
	gint lenCur = getLength();
	if (idx > lenCur) {
		return;
	}
	if (changeSize(idx,lenR,count)) {
		for (gint i = 0; i < count; i++) {
			getDataPtr(idx)[i] = v;
		}
		setLength(lenCur + count - lenR);
	}
}


void GWString::set(const gchar* v, gint len, gint count)
{
	if (count <= 0) {
		return;
	}
	if (len<0) {
		len = GX::strlen(v);
	}
	gint lenTo = GX::strUTF8toUTF16Count(v, len);
	if (changeCapability(lenTo*count + 1)) {
		GX::strUTF8toUTF16(v, len, getDataPtr(), lenTo);
		for (gint i = 1; i < count; i++) {
			memcpy(getDataPtr(i*lenTo), getDataPtr(), lenTo*sizeof(gwchar));
		}
		setLength(lenTo*count);
	}
}
void GWString::append(const gchar* v, gint len, gint count)
{
	if (count <= 0) {
		return;
	}
	if (len<0) {
		len = GX::strlen(v);
	}
	gint lenTo = GX::strUTF8toUTF16Count(v, len);
	gint lenCur = getLength();
	if (changeCapability(lenCur + lenTo*count + 1)) {
		GX::strUTF8toUTF16(v, len, getDataPtr(lenCur), lenTo);
		for (gint i = 1; i < count; i++) {
			memcpy(getDataPtr(lenCur+i*lenTo), getDataPtr(lenCur), lenTo*sizeof(gwchar));
		}
		setLength(lenCur + lenTo*count);
	}
}
void GWString::insert(gint idx, const gchar* v, gint len, gint count)
{
	replace(idx, 0, v, len, count);
}
void GWString::replace(gint idx, gint lenR, const gchar* v, gint len, gint count)
{
	if (count <= 0) {
		return;
	}
	if (idx < 0 || lenR<0) {
		return;
	}
	gint lenCur = getLength();
	if (idx > lenCur) {
		return;
	}
	if (len<0) {
		len = GX::strlen(v);
	}
	gint lenTo = GX::strUTF8toUTF16Count(v, len);
	if (changeSize(idx, lenR, lenTo*count)) {
		GX::strUTF8toUTF16(v, len, getDataPtr(idx), lenTo);
		for (gint i = 1; i < count; i++) {
			memcpy(getDataPtr(idx + i*lenTo), getDataPtr(idx), lenTo*sizeof(gwchar));
		}
		setLength(lenCur + lenTo*count - lenR);
	}
}
void GWString::replace(gint idx, gint lenR,
	gchar preChar, gint preCount,
	gchar sufChar, gint sufCount,
	const gchar* v, gint len, gint count)
{
	if (preCount <0 || count < 0 || sufCount<0 || preCount + count + sufCount <= 0) {
		return;
	}
	if (idx < 0 || lenR<0) {
		return;
	}
	gint lenCur = getLength();
	if (idx > lenCur) {
		return;
	}
	if (len<0) {
		len = GX::strlen(v);
	}
	gint lenTo = GX::strUTF8toUTF16Count(v, len);
	if (changeSize(idx, lenR, preCount + lenTo*count + sufCount)) {
		gint start = idx;
		for (gint i = 0; i < preCount; i++) {
			getDataPtr(start)[i] = preChar;
		}
		start += preCount;
		GX::strUTF8toUTF16(v, len, getDataPtr(start), lenTo);
		for (gint i = 1; i < count; i++) {
			memcpy(getDataPtr(start + i*lenTo), getDataPtr(start), lenTo*sizeof(gwchar));
		}
		start += lenTo*count;
		for (gint i = 0; i < sufCount; i++) {
			getDataPtr(start)[i] = sufChar;
		}
		start += sufCount;
		setLength(lenCur + start - lenR);
	}
}
void GWString::set(const gwchar* v, gint len, gint count)
{
	if (count <= 0) {
		return;
	}
	if (len<0) {
		len = GX::strlen(v);
	}
	if (changeCapability(len*count + 1)) {
		for (gint i = 0; i < count; i++) {
			memcpy(getDataPtr(i*len), v, len*sizeof(gwchar));
		}
		setLength(len*count);
	}
}
void GWString::append(const gwchar* v, gint len, gint count)
{
	if (count <= 0) {
		return;
	}
	if (len<0) {
		len = GX::strlen(v);
	}
	gint lenCur = getLength();
	if (changeCapability(lenCur + len*count + 1)) {
		for (gint i = 0; i < count; i++) {
			memcpy(getDataPtr(lenCur + i*len), v, len*sizeof(gwchar));
		}
		setLength(lenCur + len*count);
	}
}
void GWString::insert(gint idx, const gwchar* v, gint len, gint count)
{
	replace(idx, 0, v, len, count);
}

void GWString::replace(gint idx, gint lenR, const gwchar* v, gint len, gint count)
{
	if (count <= 0) {
		return;
	}
	if (idx < 0 || lenR<0) {
		return;
	}
	gint lenCur = getLength();
	if (idx > lenCur) {
		return;
	}
	if (len<0) {
		len = GX::strlen(v);
	}
	if (changeSize(idx, lenR, len*count)) {
		for (gint i = 0; i < count; i++) {
			memcpy(getDataPtr(idx + i*len), v, len*sizeof(gwchar));
		}
		setLength(lenCur + len*count - lenR);
	}
}
void GWString::replace(gint idx, gint lenR,
	gwchar preChar, gint preCount,
	gwchar sufChar, gint sufCount,
	const gwchar* v, gint len, gint count)
{
	if (preCount <0 || count < 0 || sufCount<0 || preCount + count + sufCount <= 0) {
		return;
	}
	if (idx < 0 || lenR<0) {
		return;
	}
	gint lenCur = getLength();
	if (idx > lenCur) {
		return;
	}
	if (len<0) {
		len = GX::strlen(v);
	}
	if (changeSize(idx, lenR, preCount + len*count + sufCount)) {
		gint start = idx;
		for (gint i = 0; i < preCount; i++) {
			getDataPtr(start)[i] = preChar;
		}
		start += preCount;
		for (gint i = 0; i < count; i++) {
			memcpy(getDataPtr(start + i*len), v, len*sizeof(gwchar));
		}
		start += len*count;
		for (gint i = 0; i < sufCount; i++) {
			getDataPtr(start)[i] = sufChar;
		}
		start += sufCount;
		setLength(lenCur + start - lenR);
	}
}


#define M_SET \
	if (vsLen < 0 && tempLen < -vsLen) {\
		set(fillChar, -vsLen - tempLen);\
		append(temp, tempLen);\
		}\
		else if (vsLen > 0 && tempLen < vsLen) {\
		set(temp, tempLen);\
		append(fillChar, vsLen - tempLen);\
	}\
		else {\
		set(temp, tempLen);\
	}
#define M_APPEND \
	if (vsLen < 0 && tempLen < -vsLen) {\
		append(fillChar, -vsLen - tempLen);\
		append(temp, tempLen);\
		}\
		else if (vsLen > 0 && tempLen < vsLen) {\
		append(temp, tempLen);\
		append(fillChar, vsLen - tempLen);\
	}\
		else {\
		append(temp, tempLen);\
	}
#define M_REPLACE \
	replace(idx, lenR, \
			fillChar, (vsLen < 0 && tempLen < -vsLen) ? -vsLen - tempLen : 0, \
			fillChar, (vsLen > 0 && tempLen < vsLen) ? vsLen - tempLen : 0, \
			temp, tempLen, 1);


void GWString::setInt16(gint16 v, GX::StringRadix radix, gint vsLen, gwchar fillChar)
{
	gwchar temp[16];
	gint tempLen = GX::gi16toa(v, temp, radix);
	M_SET
}
void GWString::appendInt16(gint16 v, GX::StringRadix radix, gint vsLen, gwchar fillChar)
{
	gwchar temp[16];
	gint tempLen = GX::gi16toa(v, temp, radix);
	M_APPEND
}
void GWString::insertInt16(gint idx, gint16 v, GX::StringRadix radix, gint vsLen, gwchar fillChar)
{
	replaceInt16(idx, 0, v, radix, vsLen, fillChar);
}
void GWString::replaceInt16(gint idx, gint lenR, gint16 v, GX::StringRadix radix, gint vsLen, gwchar fillChar)
{
	gwchar temp[16];
	gint tempLen = GX::gi16toa(v, temp, radix);
	M_REPLACE
}
void GWString::setUint16(guint16 v, GX::StringRadix radix, gint vsLen, gwchar fillChar)
{
	gwchar temp[16];
	gint tempLen = GX::gu16toa(v, temp, radix);
	M_SET
}
void GWString::appendUint16(guint16 v, GX::StringRadix radix, gint vsLen, gwchar fillChar)
{
	gwchar temp[16];
	gint tempLen = GX::gu16toa(v, temp, radix);
	M_APPEND
}
void GWString::insertUint16(gint idx, guint16 v, GX::StringRadix radix, gint vsLen, gwchar fillChar)
{
	replaceUint16(idx, 0, v, radix, vsLen, fillChar);
}
void GWString::replaceUint16(gint idx, gint lenR, guint16 v, GX::StringRadix radix, gint vsLen, gwchar fillChar)
{
	gwchar temp[16];
	gint tempLen = GX::gu16toa(v, temp, radix);
	M_REPLACE
}

void GWString::setInt32(gint32 v, GX::StringRadix radix, gint vsLen, gwchar fillChar)
{
	gwchar temp[32];
	gint tempLen = GX::gi32toa(v, temp, radix);
	M_SET
}
void GWString::appendInt32(gint32 v, GX::StringRadix radix, gint vsLen, gwchar fillChar)
{
	gwchar temp[32];
	gint tempLen = GX::gi32toa(v, temp, radix);
	M_APPEND
}
void GWString::insertInt32(gint idx, gint32 v, GX::StringRadix radix, gint vsLen, gwchar fillChar)
{
	replaceInt32(idx, 0, v, radix, vsLen, fillChar);
}
void GWString::replaceInt32(gint idx, gint lenR, gint32 v, GX::StringRadix radix, gint vsLen, gwchar fillChar)
{
	gwchar temp[32];
	gint tempLen = GX::gi32toa(v, temp, radix);
	M_REPLACE
}
void GWString::setUint32(guint32 v, GX::StringRadix radix, gint vsLen, gwchar fillChar)
{
	gwchar temp[32];
	gint tempLen = GX::gu32toa(v, temp, radix);
	M_SET
}
void GWString::appendUint32(guint32 v, GX::StringRadix radix, gint vsLen, gwchar fillChar)
{
	gwchar temp[32];
	gint tempLen = GX::gu32toa(v, temp, radix);
	M_APPEND
}
void GWString::insertUint32(gint idx, guint32 v, GX::StringRadix radix, gint vsLen, gwchar fillChar)
{
	replaceUint32(idx, 0, v, radix, vsLen, fillChar);
}
void GWString::replaceUint32(gint idx, gint lenR, guint32 v, GX::StringRadix radix, gint vsLen, gwchar fillChar)
{
	gwchar temp[32];
	gint tempLen = GX::gu32toa(v, temp, radix);
	M_REPLACE
}

void GWString::setInt64(gint64 v, GX::StringRadix radix, gint vsLen, gwchar fillChar)
{
	gwchar temp[64];
	gint tempLen = GX::gi64toa(v, temp, radix);
	M_SET
}
void GWString::appendInt64(gint64 v, GX::StringRadix radix, gint vsLen, gwchar fillChar)
{
	gwchar temp[64];
	gint tempLen = GX::gi64toa(v, temp, radix);
	M_APPEND
}
void GWString::insertInt64(gint idx, gint64 v, GX::StringRadix radix, gint vsLen, gwchar fillChar)
{
	replaceInt64(idx, 0, v, radix, vsLen, fillChar);
}
void GWString::replaceInt64(gint idx, gint lenR, gint64 v, GX::StringRadix radix, gint vsLen, gwchar fillChar)
{
	gwchar temp[64];
	gint tempLen = GX::gi64toa(v, temp, radix);
	M_REPLACE
}
void GWString::setUint64(guint64 v, GX::StringRadix radix, gint vsLen, gwchar fillChar)
{
	gwchar temp[64];
	gint tempLen = GX::gu64toa(v, temp, radix);
	M_SET
}
void GWString::appendUint64(guint64 v, GX::StringRadix radix, gint vsLen, gwchar fillChar)
{
	gwchar temp[64];
	gint tempLen = GX::gu64toa(v, temp, radix);
	M_APPEND
}
void GWString::insertUint64(gint idx, guint64 v, GX::StringRadix radix, gint vsLen, gwchar fillChar)
{
	replaceUint64(idx, 0, v, radix, vsLen, fillChar);
}
void GWString::replaceUint64(gint idx, gint lenR, guint64 v, GX::StringRadix radix, gint vsLen, gwchar fillChar)
{
	gwchar temp[64];
	gint tempLen = GX::gu64toa(v, temp, radix);
	M_REPLACE
}

void GWString::setFloat32(gfloat32 v, gint precision, gint vsLen, gwchar fillChar)
{
	gwchar temp[8 + 32];
	gint tempLen = GX::gf32toa(v, temp, precision);
	M_SET
}
void GWString::appendFloat32(gfloat32 v, gint precision, gint vsLen, gwchar fillChar)
{
	gwchar temp[8 + 32];
	gint tempLen = GX::gf32toa(v, temp, precision);
	M_APPEND
}
void GWString::insertFloat32(gint idx, gfloat32 v, gint precision, gint vsLen, gwchar fillChar)
{
	replaceFloat32(idx, 0, v, precision, vsLen, fillChar);
}
void GWString::replaceFloat32(gint idx, gint lenR, gfloat32 v, gint precision, gint vsLen, gwchar fillChar)
{
	if (precision > 30) {
		precision = 30;
	}
	gwchar temp[8 + 32];
	gint tempLen = GX::gf32toa(v, temp, precision);
	M_REPLACE
}

void GWString::setFloat64(gfloat64 v, gint precision, gint vsLen, gwchar fillChar)
{
	if (precision > 30) {
		precision = 30;
	}
	gwchar temp[17 + 32];
	gint tempLen = GX::gf64toa(v, temp, precision);
	M_SET
}
void GWString::appendFloat64(gfloat64 v, gint precision, gint vsLen, gwchar fillChar)
{
	if (precision > 30) {
		precision = 30;
	}
	gwchar temp[17 + 32];
	gint tempLen = GX::gf64toa(v, temp, precision);
	M_APPEND
}
void GWString::insertFloat64(gint idx, gfloat64 v, gint precision, gint vsLen, gwchar fillChar)
{
	replaceFloat64(idx, 0, v, precision, vsLen, fillChar);
}
void GWString::replaceFloat64(gint idx, gint lenR, gfloat64 v, gint precision, gint vsLen, gwchar fillChar)
{
	if (precision > 30) {
		precision = 30;
	}
	gwchar temp[17 + 32];
	gint tempLen = GX::gf64toa(v, temp, precision);
	M_REPLACE
}

#undef M_SET
#undef M_APPEND
#undef M_REPLACE

void GWString::setInt(gint v, GX::StringRadix radix, gint vsLen, gwchar fillChar)
{
#if GX_PTR_32BIT
	setInt32(v, radix, vsLen, fillChar);
#elif GX_PTR_64BIT
	setInt64(v, radix, vsLen, fillChar);
#endif
}
void GWString::appendInt(gint v, GX::StringRadix radix, gint vsLen, gwchar fillChar)
{
#if GX_PTR_32BIT
	appendInt32(v, radix, vsLen, fillChar);
#elif GX_PTR_64BIT
	appendInt64(v, radix, vsLen, fillChar);
#endif
}
void GWString::insertInt(gint idx, gint v, GX::StringRadix radix, gint vsLen, gwchar fillChar)
{
#if GX_PTR_32BIT
	insertInt32(idx, v, radix, vsLen, fillChar);
#elif GX_PTR_64BIT
	insertInt64(idx, v, radix, vsLen, fillChar);
#endif
}
void GWString::replaceInt(gint idx, gint lenR, gint v, GX::StringRadix radix, gint vsLen, gwchar fillChar)
{
#if GX_PTR_32BIT
	replaceInt32(idx, lenR, v, radix, vsLen, fillChar);
#elif GX_PTR_64BIT
	replaceInt64(idx, lenR, v, radix, vsLen, fillChar);
#endif
}

void GWString::setUint(guint v, GX::StringRadix radix, gint vsLen, gwchar fillChar)
{
#if GX_PTR_32BIT
	setUint32(v, radix, vsLen, fillChar);
#elif GX_PTR_64BIT
	setUint64(v, radix, vsLen, fillChar);
#endif
}
void GWString::appendUint(guint v, GX::StringRadix radix, gint vsLen, gwchar fillChar)
{
#if GX_PTR_32BIT
	appendUint32(v, radix, vsLen, fillChar);
#elif GX_PTR_64BIT
	appendUint64(v, radix, vsLen, fillChar);
#endif
}
void GWString::insertUint(gint idx, guint v, GX::StringRadix radix, gint vsLen, gwchar fillChar)
{
#if GX_PTR_32BIT
	insertUint32(idx, v, radix, vsLen, fillChar);
#elif GX_PTR_64BIT
	insertUint64(idx, v, radix, vsLen, fillChar);
#endif
}
void GWString::replaceUint(gint idx, gint lenR, guint v, GX::StringRadix radix, gint vsLen, gwchar fillChar)
{
#if GX_PTR_32BIT
	replaceUint32(idx, v, lenR, radix, vsLen, fillChar);
#elif GX_PTR_64BIT
	replaceUint64(idx, v, lenR, radix, vsLen, fillChar);
#endif
}

void GWString::setFloat(gfloat v, gint precision, gint vsLen, gwchar fillChar)
{
#if GX_PTR_32BIT
	setFloat32(v, precision, vsLen, fillChar);
#elif GX_PTR_64BIT
	setFloat64(v, precision, vsLen, fillChar);
#endif
}
void GWString::appendFloat(gfloat v, gint precision, gint vsLen, gwchar fillChar)
{
#if GX_PTR_32BIT
	appendFloat32(v, precision, vsLen, fillChar);
#elif GX_PTR_64BIT
	appendFloat64(v, precision, vsLen, fillChar);
#endif
}
void GWString::insertFloat(gint idx, gfloat v, gint precision, gint vsLen, gwchar fillChar)
{
#if GX_PTR_32BIT
	insertFloat32(idx, v, precision, vsLen, fillChar);
#elif GX_PTR_64BIT
	insertFloat64(idx, v, precision, vsLen, fillChar);
#endif
}
void GWString::replaceFloat(gint idx, gint lenR, gfloat v, gint precision, gint vsLen, gwchar fillChar)
{
#if GX_PTR_32BIT
	replaceFloat32(idx, lenR, v, precision, vsLen, fillChar);
#elif GX_PTR_64BIT
	replaceFloat64(idx, lenR, v, precision, vsLen, fillChar);
#endif
}


void GWString::setPtr(void* v, GX::StringRadix radix, gint vsLen, gwchar fillChar)
{
	setUint(GX_CAST_R(guint, v), radix, vsLen, fillChar);
}
void GWString::appendPtr(void* v, GX::StringRadix radix, gint vsLen, gwchar fillChar)
{
	appendUint(GX_CAST_R(guint, v), radix, vsLen, fillChar);
}
void GWString::insertPtr(gint idx, void* v, GX::StringRadix radix, gint vsLen, gwchar fillChar)
{
	insertUint(idx, GX_CAST_R(guint, v), radix, vsLen, fillChar);
}
void GWString::replacePtr(gint idx, gint lenR, void* v, GX::StringRadix radix, gint vsLen, gwchar fillChar)
{
	replaceUint(idx, lenR, GX_CAST_R(guint, v), radix, vsLen, fillChar);
}
