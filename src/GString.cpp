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



GString::Formater& GString::Formater::arg(gchar v, gint count)
{
	
	

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
	return replace(idx, 0, v, count);
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
	if (changeSize(idx, lenR, lenCur + count)) {
		for (gint i = 0; i < count; i++) {
			getDataPtr(idx)[i] = v;
		}
		setLength(lenCur + count - lenR);
	}
}
void GString::set(gwchar v, gint count)
{

//TODO
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
			memset(getDataPtr(), buf[0], count);
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
			for (gint i = 0; i<count; i++) {
				p[0] = buf[0];
				p++;
			}
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
	if (count <= 0) {
		return;
	}
	if (idx < 0) {
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

	if (changeCapability(lenCur + count*len + 1)) {
		memmove(getDataPtr(idx) + count*len, getDataPtr(idx), (lenCur - idx)*sizeof(gchar));
		gchar* p = getDataPtr(idx);
		if (len <= 1) {
			for (gint i = 0; i<count; i++) {
				p[0] = buf[0];
				p++;
			}
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
	if (count <= 0) {
		return;
	}
	if (idx < 0) {
		return;
	}
	gint lenCur = getLength();
	if (idx > lenCur) {
		return;
	}
	if (len<0) {
		len = GX::strlen(v);
	}
	if (changeCapability(lenCur + len*count + 1)) {
		memmove(getDataPtr(idx) + len*count, getDataPtr(idx), (lenCur - idx)*sizeof(gchar));
		for (gint i = 0; i < count; i++) {
			memcpy(getDataPtr(idx + i*len), v, len*sizeof(gchar));
		}
		setLength(lenCur + len*count);
	}
}
void GString::replace(gint idx, gint lenR, const gchar* v, gint len, gint count)
{
	if (count <= 0) {
		return;
	}
	if (idx < 0) {
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
	if (idx < 0) {
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
			memcpy(getDataPtr(start + i*len), v, len*sizeof(gchar));
		}
		start += len*count;
		for (gint i = 0; i < sufCount; i++) {
			getDataPtr(start)[i] = sufChar;
		}
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
	if (count <= 0) {
		return;
	}
	if (idx < 0) {
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
	if (changeCapability(lenCur + lenTo*count + 1)) {
		memmove(getDataPtr(idx) + lenTo*count, getDataPtr(idx), (lenCur - idx)*sizeof(gchar));
		GX::strUTF16toUTF8(v, len, getDataPtr(idx), lenTo);
		for (gint i = 1; i < count; i++) {
			memcpy(getDataPtr(idx + i*lenTo), getDataPtr(idx), lenTo*sizeof(gchar));
		}
		setLength(lenCur + lenTo*count);
	}
}
void GString::replace(gint idx, gint lenR, const gwchar* v, gint len, gint count)
{
	if (count <= 0) {
		return;
	}
	if (idx < 0) {
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
	if (idx < 0) {
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
			for (gint i = 0; i<preCount; i++) {
				p[0] = preBuf[0];
				p++;
			}
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
			for (gint i = 0; i<sufCount; i++) {
				p[0] = sufBuf[0];
				p++;
			}
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
#define M_INSERT \
	if (vsLen < 0 && tempLen < -vsLen) {\
		insert(idx, fillChar, -vsLen - tempLen);\
		insert(idx - vsLen - tempLen, temp, tempLen);\
	}\
	else if (vsLen > 0 && tempLen < vsLen) {\
		insert(idx, temp, tempLen);\
		insert(idx + tempLen, fillChar, vsLen - tempLen);\
	}\
	else {\
		insert(idx, temp, tempLen);\
	}

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
	gchar temp[16];
	gint tempLen = GX::gi16toa(v, temp, radix);
	M_INSERT
}
void GString::replaceInt16(gint idx, gint lenR, gint16 v, GX::StringRadix radix, gint vsLen, gchar fillChar)
{

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
	gchar temp[16];
	gint tempLen = GX::gu16toa(v, temp, radix);
	M_INSERT
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
	gchar temp[32];
	gint tempLen = GX::gi32toa(v, temp, radix);
	M_INSERT
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
	gchar temp[32];
	gint tempLen = GX::gu32toa(v, temp, radix);
	M_INSERT
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
	gchar temp[64];
	gint tempLen = GX::gi64toa(v, temp, radix);
	M_INSERT
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
	gchar temp[64];
	gint tempLen = GX::gu64toa(v, temp, radix);
	M_INSERT
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
	if (precision > 30) {
		precision = 30;
	}
	gchar temp[8 + 32];
	gint tempLen = GX::gf32toa(v, temp, precision);
	M_INSERT
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
	if (precision > 30) {
		precision = 30;
	}
	gchar temp[17 + 32];
	gint tempLen = GX::gf64toa(v, temp, precision);
	M_INSERT
}

#undef M_SET
#undef M_APPEND
#undef M_INSERT

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




GString::Formater GString::format(const gchar* fmt, gint len)
{
	set(fmt, len);
	return Formater(this, 0);
}




