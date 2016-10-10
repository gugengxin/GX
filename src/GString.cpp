//
//  GString.cpp
//  GX
//
//  Created by Gengxin Gu on 16/4/29.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#include "GString.h"
#include <memory.h>
#include "GWString.h"
#include "GXGObject.h"


#define M_FMT_STRING() GX_CAST_R(GString*, getString())


GString::Formater::Formater(GString* str, gint cursor, gint cursorEnd) :
	GDataString<gchar>::Formater(str, cursor, cursorEnd)
{

}

GString::Formater& GString::Formater::arg(gchar v, gint count)
{
    if (moveCursor()) {
        gint lastLen=replaceStart();
        M_FMT_STRING()->replace(getCursor(), 1, v, count);
        replaceEnd(lastLen);
    }
	return *this;
}

GString::Formater& GString::Formater::arg(gwchar v,gint count)
{
    if (moveCursor()) {
        gint lastLen=replaceStart();
        M_FMT_STRING()->replace(getCursor(), 1, v, count);
        replaceEnd(lastLen);
    }
    return *this;
}



GX_GOBJECT_IMPLEMENT(GString, GDataString<gchar>);

GString::GString()
{

}

GString::~GString()
{

}

bool GString::isEqual(GObject* obj) {
	if (obj->isKindOfClass(GString::gclass)) {
		if (getHash() == obj->getHash()) {
			return getOWHashB() == GX_CAST_R(GString*, obj)->getOWHashB() &&
				getOWHashC() == GX_CAST_R(GString*, obj)->getOWHashC();
		}
	}
	else if (obj->isKindOfClass(GWString::gclass)) {
		if (getHash() == obj->getHash()) {
			return getOWHashB() == GX_CAST_R(GWString*, obj)->getOWHashB() &&
				getOWHashC() == GX_CAST_R(GWString*, obj)->getOWHashC();
		}
	}
	return false;
}

const gchar* GString::c_str() 
{
	if (getLength() <= 0) {
		return "";
	}
	return GX_CAST_R(const gchar*, getDataPtr());
}

void GString::set(gchar v, gint count)
{
	if (count <= 0) {
		return;
	}
	if (changeCapability(count + 1)) {
		memset(getDataPtr(), v, count);
		setLength(count);
	}
}
void GString::append(gchar v, gint count)
{
	if (count <= 0) {
		return;
	}
	gint lenCur = getLength();
	if (changeCapability(lenCur + count + 1)) {
		memset(getDataPtr(lenCur), v, count);
		setLength(lenCur + count);
	}
}
void GString::insert(gint idx, gchar v, gint count)
{
	replace(idx, 0, v, count);
}
void GString::replace(gint idx, gint lenR, gchar v, gint count)
{
	if (idx < 0 || lenR<0) {
		return;
	}
	if (count <= 0) {
		return;
	}
	gint lenCur = getLength();
	if (idx > lenCur) {
		return;
	}
	if (changeSize(idx, lenR, count)) {
		memset(getDataPtr(idx), v, count);
		setLength(lenCur + count - lenR);
	}
}
void GString::set(gwchar v, gint count)
{
	if (count<=0) {
		return;
	}
	gchar buf[3];
	gint len = GX::strUTF16OneChartoUTF8(v, buf);
	if (len <= 0) {
		return;
	}
	if (changeCapability(count*len + 1)) {
		char* p = getDataPtr();
		if (len <= 1) {
			memset(p, buf[0], count);
		}
		else if (len == 2) {
			for (gint i = 0; i<count; i++) {
				p[0] = buf[0];
				p[1] = buf[1];
				p += 2;
			}
		}
		else if (len >= 3) {
			for (gint i = 0; i<count; i++) {
				p[0] = buf[0];
				p[1] = buf[1];
				p[2] = buf[2];
				p += 3;
			}
		}
		setLength(count*len);
	}

}
void GString::append(gwchar v, gint count)
{
	if (count <= 0) {
		return;
	}
	gchar buf[3];
	gint len = GX::strUTF16OneChartoUTF8(v, buf);
	if (len <= 0) {
		return;
	}
	gint lenCur = getLength();
	if (changeCapability(lenCur + count*len + 1)) {
		gchar* p = getDataPtr(lenCur);
		if (len <= 1) {
			memset(p, buf[0], count);
		}
		else if (len == 2) {
			for (gint i = 0; i<count; i++) {
				p[0] = buf[0];
				p[1] = buf[1];
				p += 2;
			}
		}
		else if (len >= 3) {
			for (gint i = 0; i<count; i++) {
				p[0] = buf[0];
				p[1] = buf[1];
				p[2] = buf[2];
				p += 3;
			}
		}
		setLength(lenCur + count*len);
	}
}
void GString::insert(gint idx, gwchar v, gint count)
{
	replace(idx, 0, v, count);
}
void GString::replace(gint idx, gint lenR, gwchar v, gint count)
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
	gchar buf[3];
	gint len = GX::strUTF16OneChartoUTF8(v, buf);
	if (len <= 0) {
		return;
	}

	if (changeSize(idx,lenR,count*len)) {
		gchar* p = getDataPtr(idx);
		if (len <= 1) {
			memset(p, buf[0], count);
		}
		else if (len == 2) {
			for (gint i = 0; i<count; i++) {
				p[0] = buf[0];
				p[1] = buf[1];
				p += 2;
			}
		}
		else if (len >= 3) {
			for (gint i = 0; i<count; i++) {
				p[0] = buf[0];
				p[1] = buf[1];
				p[2] = buf[2];
				p += 3;
			}
		}
		setLength(lenCur + count*len - lenR);
	}
}


void GString::set(const gchar* v, gint len, gint count)
{
	if (count <= 0) {
		return;
	}
	if (len<0) {
		len = GX::strlen(v);
	}
	if (changeCapability(len*count + 1)) {
		for (gint i = 0; i < count; i++) {
			memcpy(getDataPtr(i*len), v, len*sizeof(gchar));
		}
		setLength(len*count);
	}
}
void GString::append(const gchar* v, gint len, gint count)
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
			memcpy(getDataPtr(lenCur + i*len), v, len*sizeof(gchar));
		}
		setLength(lenCur + len*count);
	}
}
void GString::insert(gint idx, const gchar* v, gint len, gint count)
{
	replace(idx,0, v, len, count);
}
void GString::replace(gint idx, gint lenR, const gchar* v, gint len, gint count)
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
			memcpy(getDataPtr(idx + i*len), v, len*sizeof(gchar));
		}
		setLength(lenCur + len*count - lenR);
	}
}
void GString::replace(gint idx, gint lenR,
	gchar preChar, gint preCount,
	gchar sufChar, gint sufCount,
	const gchar* v, gint len, gint count)
{
	if (preCount <0 || count < 0 || sufCount<0 || preCount+count+sufCount<=0) {
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
		memset(getDataPtr(start), preChar, preCount);
		start += preCount;
		for (gint i = 0; i < count; i++) {
			memcpy(getDataPtr(start + i*len), v, len*sizeof(gchar));
		}
		start += len*count;
		memset(getDataPtr(start), sufChar, sufCount);
		start += sufCount;
		setLength(lenCur + start - lenR);
	}
}

void GString::set(const gwchar* v, gint len, gint count)
{
	if (count <= 0) {
		return;
	}
	if (len<0) {
		len = GX::strlen(v);
	}
	gint lenTo = GX::strUTF16toUTF8Count(v, len);
	if (changeCapability(lenTo*count + 1)) {
		GX::strUTF16toUTF8(v, len, getDataPtr(), lenTo);
		for (gint i = 1; i < count; i++) {
			memcpy(getDataPtr(i*lenTo), getDataPtr(), lenTo*sizeof(gchar));
		}
		setLength(lenTo*count);
	}
}
void GString::append(const gwchar* v, gint len, gint count)
{
	if (count <= 0) {
		return;
	}
	if (len<0) {
		len = GX::strlen(v);
	}
	gint lenTo = GX::strUTF16toUTF8Count(v, len);
	gint lenCur = getLength();
	if (changeCapability(lenCur + lenTo*count + 1)) {
		GX::strUTF16toUTF8(v, len, getDataPtr(lenCur), lenTo);
		for (gint i = 1; i < count; i++) {
			memcpy(getDataPtr(lenCur + i*lenTo), getDataPtr(lenCur), lenTo*sizeof(gchar));
		}
		setLength(lenCur + lenTo*count);
	}
}
void GString::insert(gint idx, const gwchar* v, gint len, gint count)
{
	replace(idx, 0, v, len, count);
}
void GString::replace(gint idx, gint lenR, const gwchar* v, gint len, gint count)
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
	gint lenTo = GX::strUTF16toUTF8Count(v, len);
	if (changeSize(idx,lenR,lenTo*count)) {
		GX::strUTF16toUTF8(v, len, getDataPtr(idx), lenTo);
		for (gint i = 1; i < count; i++) {
			memcpy(getDataPtr(idx + i*lenTo), getDataPtr(idx), lenTo*sizeof(gchar));
		}
		setLength(lenCur + lenTo*count -lenR);
	}
}
void GString::replace(gint idx, gint lenR,
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
	gchar preBuf[3], sufBuf[3];
	gint preTo = GX::strUTF16OneChartoUTF8(preChar, preBuf);
	gint sufTo = GX::strUTF16OneChartoUTF8(sufChar, sufBuf);
	gint lenTo = GX::strUTF16toUTF8Count(v, len);

	if (changeSize(idx, lenR, preTo*preCount + lenTo*count + sufTo*sufCount)) {
		gint start = idx;
		gchar* p = getDataPtr(start);
		if (preTo <= 1) {
			memset(p, preBuf[0], preCount);
		}
		else if (preTo == 2) {
			for (gint i = 0; i<preCount; i++) {
				p[0] = preBuf[0];
				p[1] = preBuf[1];
				p += 2;
			}
		}
		else if (preTo >= 3) {
			for (gint i = 0; i<preCount; i++) {
				p[0] = preBuf[0];
				p[1] = preBuf[1];
				p[2] = preBuf[2];
				p += 3;
			}
		}

		start += preTo*preCount;
		GX::strUTF16toUTF8(v, len, getDataPtr(start), lenTo);
		for (gint i = 1; i < count; i++) {
			memcpy(getDataPtr(start + i*lenTo), getDataPtr(start), lenTo*sizeof(gchar));
		}

		start += lenTo*count;
		p = getDataPtr(start);
		if (sufTo <= 1) {
			memset(p, sufBuf[0], sufCount);
		}
		else if (sufTo == 2) {
			for (gint i = 0; i<sufCount; i++) {
				p[0] = sufBuf[0];
				p[1] = sufBuf[1];
				p += 2;
			}
		}
		else if (sufTo >= 3) {
			for (gint i = 0; i<sufCount; i++) {
				p[0] = sufBuf[0];
				p[1] = sufBuf[1];
				p[2] = sufBuf[2];
				p += 3;
			}
		}

		start += sufTo*sufCount;
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


void GString::setInt16(gint16 v, GX::StringRadix radix, gint vsLen, gchar fillChar) 
{
	gchar temp[16];
	gint tempLen = GX::gi16toa(v, temp, radix);
	M_SET
}
void GString::appendInt16(gint16 v, GX::StringRadix radix, gint vsLen, gchar fillChar) 
{
	gchar temp[16];
	gint tempLen = GX::gi16toa(v, temp, radix);
	M_APPEND
}
void GString::insertInt16(gint idx, gint16 v, GX::StringRadix radix, gint vsLen, gchar fillChar) 
{
	replaceInt16(idx, 0, v, radix, vsLen, fillChar);
}
void GString::replaceInt16(gint idx, gint lenR, gint16 v, GX::StringRadix radix, gint vsLen, gchar fillChar)
{
	gchar temp[16];
	gint tempLen = GX::gi16toa(v, temp, radix);
	M_REPLACE
}
void GString::setUint16(guint16 v, GX::StringRadix radix, gint vsLen, gchar fillChar) 
{
	gchar temp[16];
	gint tempLen = GX::gu16toa(v, temp, radix);
	M_SET
}
void GString::appendUint16(guint16 v, GX::StringRadix radix, gint vsLen, gchar fillChar) 
{
	gchar temp[16];
	gint tempLen = GX::gu16toa(v, temp, radix);
	M_APPEND
}
void GString::insertUint16(gint idx, guint16 v, GX::StringRadix radix, gint vsLen, gchar fillChar) 
{
	replaceUint16(idx, 0, v, radix, vsLen, fillChar);
}
void GString::replaceUint16(gint idx, gint lenR, guint16 v, GX::StringRadix radix, gint vsLen, gchar fillChar)
{
	gchar temp[16];
	gint tempLen = GX::gu16toa(v, temp, radix);
	M_REPLACE
}

void GString::setInt32(gint32 v, GX::StringRadix radix, gint vsLen, gchar fillChar) 
{
	gchar temp[32];
	gint tempLen = GX::gi32toa(v, temp, radix);
	M_SET
}
void GString::appendInt32(gint32 v, GX::StringRadix radix, gint vsLen, gchar fillChar)
{
	gchar temp[32];
	gint tempLen = GX::gi32toa(v, temp, radix);
	M_APPEND
}
void GString::insertInt32(gint idx, gint32 v, GX::StringRadix radix, gint vsLen, gchar fillChar)
{
	replaceInt32(idx, 0, v, radix, vsLen, fillChar);
}
void GString::replaceInt32(gint idx, gint lenR, gint32 v, GX::StringRadix radix, gint vsLen, gchar fillChar)
{
	gchar temp[32];
	gint tempLen = GX::gi32toa(v, temp, radix);
	M_REPLACE
}
void GString::setUint32(guint32 v, GX::StringRadix radix, gint vsLen, gchar fillChar) 
{
	gchar temp[32];
	gint tempLen = GX::gu32toa(v, temp, radix);
	M_SET
}
void GString::appendUint32(guint32 v, GX::StringRadix radix, gint vsLen, gchar fillChar) 
{
	gchar temp[32];
	gint tempLen = GX::gu32toa(v, temp, radix);
	M_APPEND
}
void GString::insertUint32(gint idx, guint32 v, GX::StringRadix radix, gint vsLen, gchar fillChar)
{
	replaceUint32(idx, 0, v, radix, vsLen, fillChar);
}
void GString::replaceUint32(gint idx, gint lenR, guint32 v, GX::StringRadix radix, gint vsLen, gchar fillChar)
{
	gchar temp[32];
	gint tempLen = GX::gu32toa(v, temp, radix);
	M_REPLACE
}

void GString::setInt64(gint64 v, GX::StringRadix radix, gint vsLen, gchar fillChar) 
{
	gchar temp[64];
	gint tempLen = GX::gi64toa(v, temp, radix);
	M_SET
}
void GString::appendInt64(gint64 v, GX::StringRadix radix, gint vsLen, gchar fillChar) 
{
	gchar temp[64];
	gint tempLen = GX::gi64toa(v, temp, radix);
	M_APPEND
}
void GString::insertInt64(gint idx, gint64 v, GX::StringRadix radix, gint vsLen, gchar fillChar)
{
	replaceInt64(idx, 0, v, radix, vsLen, fillChar);
}
void GString::replaceInt64(gint idx, gint lenR, gint64 v, GX::StringRadix radix, gint vsLen, gchar fillChar)
{
	gchar temp[64];
	gint tempLen = GX::gi64toa(v, temp, radix);
	M_REPLACE
}
void GString::setUint64(guint64 v, GX::StringRadix radix, gint vsLen, gchar fillChar) 
{
	gchar temp[64];
	gint tempLen = GX::gu64toa(v, temp, radix);
	M_SET
}
void GString::appendUint64(guint64 v, GX::StringRadix radix, gint vsLen, gchar fillChar) 
{
	gchar temp[64];
	gint tempLen = GX::gu64toa(v, temp, radix);
	M_APPEND
}
void GString::insertUint64(gint idx, guint64 v, GX::StringRadix radix, gint vsLen, gchar fillChar)
{
	replaceUint64(idx, 0, v, radix, vsLen, fillChar);
}
void GString::replaceUint64(gint idx, gint lenR, guint64 v, GX::StringRadix radix, gint vsLen, gchar fillChar)
{
	gchar temp[64];
	gint tempLen = GX::gu64toa(v, temp, radix);
	M_REPLACE
}

void GString::setFloat32(gfloat32 v, gint precision, gint vsLen, gchar fillChar) 
{
	gchar temp[8 + 32];
	gint tempLen = GX::gf32toa(v, temp, precision);
	M_SET
}
void GString::appendFloat32(gfloat32 v, gint precision, gint vsLen, gchar fillChar) 
{
	gchar temp[8 + 32];
	gint tempLen = GX::gf32toa(v, temp, precision);
	M_APPEND
}
void GString::insertFloat32(gint idx, gfloat32 v, gint precision, gint vsLen, gchar fillChar)
{
	replaceFloat32(idx, 0, v, precision, vsLen, fillChar);
}
void GString::replaceFloat32(gint idx, gint lenR, gfloat32 v, gint precision, gint vsLen, gchar fillChar)
{
	if (precision > 30) {
		precision = 30;
	}
	gchar temp[8 + 32];
	gint tempLen = GX::gf32toa(v, temp, precision);
	M_REPLACE
}

void GString::setFloat64(gfloat64 v, gint precision, gint vsLen, gchar fillChar)
{
	if (precision > 30) {
		precision = 30;
	}
	gchar temp[17 + 32];
	gint tempLen = GX::gf64toa(v, temp, precision);
	M_SET
}
void GString::appendFloat64(gfloat64 v, gint precision, gint vsLen, gchar fillChar) 
{
	if (precision > 30) {
		precision = 30;
	}
	gchar temp[17 + 32];
	gint tempLen = GX::gf64toa(v, temp, precision);
	M_APPEND
}
void GString::insertFloat64(gint idx, gfloat64 v, gint precision, gint vsLen, gchar fillChar)
{
	replaceFloat64(idx, 0, v, precision, vsLen, fillChar);
}
void GString::replaceFloat64(gint idx, gint lenR, gfloat64 v, gint precision, gint vsLen, gchar fillChar)
{
	if (precision > 30) {
		precision = 30;
	}
	gchar temp[17 + 32];
	gint tempLen = GX::gf64toa(v, temp, precision);
	M_REPLACE
}

#undef M_SET
#undef M_APPEND
#undef M_REPLACE

void GString::setInt(gint v, GX::StringRadix radix, gint vsLen, gchar fillChar)
{
#if GX_PTR_32BIT
	setInt32(v, radix, vsLen, fillChar);
#elif GX_PTR_64BIT
	setInt64(v, radix, vsLen, fillChar);
#endif
}
void GString::appendInt(gint v, GX::StringRadix radix, gint vsLen, gchar fillChar) 
{
#if GX_PTR_32BIT
	appendInt32(v, radix, vsLen, fillChar);
#elif GX_PTR_64BIT
	appendInt64(v, radix, vsLen, fillChar);
#endif
}
void GString::insertInt(gint idx, gint v, GX::StringRadix radix, gint vsLen, gchar fillChar) 
{
#if GX_PTR_32BIT
	insertInt32(idx, v, radix, vsLen, fillChar);
#elif GX_PTR_64BIT
	insertInt64(idx, v, radix, vsLen, fillChar);
#endif
}
void GString::replaceInt(gint idx, gint lenR, gint v, GX::StringRadix radix, gint vsLen, gchar fillChar)
{
#if GX_PTR_32BIT
	replaceInt32(idx, lenR, v, radix, vsLen, fillChar);
#elif GX_PTR_64BIT
	replaceInt64(idx, lenR, v, radix, vsLen, fillChar);
#endif
}

void GString::setUint(guint v, GX::StringRadix radix, gint vsLen, gchar fillChar) 
{
#if GX_PTR_32BIT
	setUint32(v, radix, vsLen, fillChar);
#elif GX_PTR_64BIT
	setUint64(v, radix, vsLen, fillChar);
#endif
}
void GString::appendUint(guint v, GX::StringRadix radix, gint vsLen, gchar fillChar)
{
#if GX_PTR_32BIT
	appendUint32(v, radix, vsLen, fillChar);
#elif GX_PTR_64BIT
	appendUint64(v, radix, vsLen, fillChar);
#endif
}
void GString::insertUint(gint idx, guint v, GX::StringRadix radix, gint vsLen, gchar fillChar) 
{
#if GX_PTR_32BIT
	insertUint32(idx, v, radix, vsLen, fillChar);
#elif GX_PTR_64BIT
	insertUint64(idx, v, radix, vsLen, fillChar);
#endif
}
void GString::replaceUint(gint idx, gint lenR, guint v, GX::StringRadix radix, gint vsLen, gchar fillChar)
{
#if GX_PTR_32BIT
	replaceUint32(idx, v, lenR, radix, vsLen, fillChar);
#elif GX_PTR_64BIT
	replaceUint64(idx, v, lenR, radix, vsLen, fillChar);
#endif
}

void GString::setFloat(gfloat v, gint precision, gint vsLen, gchar fillChar)
{
#if GX_PTR_32BIT
	setFloat32(v, precision, vsLen, fillChar);
#elif GX_PTR_64BIT
	setFloat64(v, precision, vsLen, fillChar);
#endif
}
void GString::appendFloat(gfloat v, gint precision, gint vsLen, gchar fillChar)
{
#if GX_PTR_32BIT
	appendFloat32(v, precision, vsLen, fillChar);
#elif GX_PTR_64BIT
	appendFloat64(v, precision, vsLen, fillChar);
#endif
}
void GString::insertFloat(gint idx, gfloat v, gint precision, gint vsLen, gchar fillChar)
{
#if GX_PTR_32BIT
	insertFloat32(idx, v, precision, vsLen, fillChar);
#elif GX_PTR_64BIT
	insertFloat64(idx, v, precision, vsLen, fillChar);
#endif
}
void GString::replaceFloat(gint idx, gint lenR, gfloat v, gint precision, gint vsLen, gchar fillChar)
{
#if GX_PTR_32BIT
	replaceFloat32(idx, lenR, v, precision, vsLen, fillChar);
#elif GX_PTR_64BIT
	replaceFloat64(idx, lenR, v, precision, vsLen, fillChar);
#endif
}


void GString::setPtr(void* v, GX::StringRadix radix, gint vsLen, gchar fillChar)
{
	setUint(GX_CAST_R(guint, v), radix, vsLen, fillChar);
}
void GString::appendPtr(void* v, GX::StringRadix radix, gint vsLen, gchar fillChar) 
{
	appendUint(GX_CAST_R(guint, v), radix, vsLen, fillChar);
}
void GString::insertPtr(gint idx, void* v, GX::StringRadix radix, gint vsLen, gchar fillChar) 
{
	insertUint(idx, GX_CAST_R(guint, v), radix, vsLen, fillChar);
}
void GString::replacePtr(gint idx, gint lenR, void* v, GX::StringRadix radix, gint vsLen, gchar fillChar)
{
	replaceUint(idx, lenR, GX_CAST_R(guint, v), radix, vsLen, fillChar);
}




GString::Formater GString::format(const gchar* fmt, gint len)
{
	set(fmt, len);
	return Formater(this, 0, 0);
}

GString::Formater GString::appendFormat(const gchar* fmt, gint len)
{
	gint lenCur = getLength();
	append(fmt,len);
	return Formater(this, lenCur, 0);
}
GString::Formater GString::insertFormat(gint idx, const gchar* fmt, gint len)
{
	gint lenTemp = getLength() - idx;
	insert(idx, fmt, len);
	return Formater(this, idx, lenTemp);
}
GString::Formater GString::replaceFormat(gint idx, gint lenR, const gchar* fmt, gint len)
{
	gint lenTemp = getLength() - idx - lenR;
	replace(idx, lenR, fmt, len);
	return Formater(this, idx, lenTemp);
}



void GString::appendPathComponent(const gchar* component, gint len)
{
	if (lastIsSeparator()) {
		if (component[0] == '/' || component[0] == '\\') {
			if (len < 0) {
				len = GX::strlen(component);
			}
			append(component + 1, len - 1);
		}
		else {
			append(component, len);
		}
	}
	else {
		if (component[0] == '/' || component[0] == '\\') {
			append(component, len);
		}
		else {
#if defined(GX_OS_WINDOWS) || defined(GX_OS_QT_WINDOWS)
            append('\\');
#else
            append('/');
#endif
			append(component, len);
		}
	}
}

void GString::appendPathComponent(const gwchar* component, gint len)
{
	if (lastIsSeparator()) {
		if (component[0] == L'/' || component[0] == L'\\') {
			if (len < 0) {
				len = GX::strlen(component);
			}
			append(component + 1, len - 1);
		}
		else {
			append(component, len);
		}
	}
	else {
		if (component[0] == L'/' || component[0] == L'\\') {
			append(component, len);
		}
		else {
#if defined(GX_OS_WINDOWS) || defined(GX_OS_QT_WINDOWS)
            append(L'\\');
#else
            append(L'/');
#endif
			append(component, len);
		}
	}
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const GX::UUID g_UUID(0x3932637B, 0x36333461, 0x32652D33, 0x342D6134);

const GX::UUID& GString::seGetUUID()
{
	return g_UUID;
}
gint GString::seGetBytes()
{
	gint res = seBytesOfKeyAndData(SKBuf, (guint)getLength());
	return res;
}
gint GString::seEncodeFields(GEncoder& coder)
{
	gint res = seEncodeKeyAndData(coder, SKBuf, getDataPtr(), (guint)getLength()*sizeof(gchar));
	return res;
}


const GX::UUID& GString::ueGetUUID()
{
	return g_UUID;
}

gint GString::ueDecodeField(GDecoder& coder, guint32 key, guint32 len)
{
	switch (key)
	{
	case SKBuf:
	{
		gint count = (gint)len;
		if (changeCapability(count)) {
			gint res=ueDecodeData(coder, getDataPtr(), (guint)len);
			if (res < 0) {
				return -1;
			}
			setLength(count);
			return res;
		}
		return -1;
	}
	break;
	default:
		return 0;
	}
}