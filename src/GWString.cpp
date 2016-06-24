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
	else if (obj->isKindOfClass(GString::gclass)) {
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
	gint lenTo = GX::strUTF8toUTF16Count(v, len);
	if (changeCapability(lenCur + lenTo*count + 1)) {
		memmove(getDataPtr(idx) + lenTo*count, getDataPtr(idx), (lenCur - idx)*sizeof(gwchar));
		GX::strUTF8toUTF16(v, len, getDataPtr(idx), lenTo);
		for (gint i = 1; i < count; i++) {
			memcpy(getDataPtr(idx + i*lenTo), getDataPtr(idx), lenTo*sizeof(gwchar));
		}
		setLength(lenCur + lenTo*count);
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
		memmove(getDataPtr(idx) + len*count, getDataPtr(idx), (lenCur - idx)*sizeof(gwchar));
		for (gint i = 0; i < count; i++) {
			memcpy(getDataPtr(idx + i*len), v, len*sizeof(gwchar));
		}
		setLength(lenCur + len*count);
	}
}

void GWString::set(gchar v, gint count)
{

}
void GWString::append(gchar v, gint count)
{

}
void GWString::insert(gint idx, gchar v, gint count)
{

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
	if (changeCapability(lenCur + count + 1)) {
		memmove(getDataPtr(idx) + count, getDataPtr(idx), (lenCur - idx)*sizeof(gwchar));
		for (gint i = 0; i < count; i++) {
			getDataPtr(idx)[i] = v;
		}
		setLength(lenCur + count);
	}
}
