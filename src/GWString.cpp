//
//  GWString.cpp
//  GX
//
//  Created by Gengxin Gu on 16/5/4.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#include "GWString.h"


GX_OBJECT_IMPLEMENT(GWString, GDataString<gwchar>);

GWString::GWString()
{
    
}

GWString::~GWString()
{
    
}

void GWString::set(const gchar* v, gint len)
{
	if (len<0) {
		len = GX::strlen(v);
	}
	gint lenTo = GX::strUTF8toUTF16Count(v, len);
	if (changeCapability(lenTo + 1)) {
		GX::strUTF8toUTF16(v, len, getDataPtr(), lenTo);
		setLength(lenTo);
	}
}
void GWString::append(const gchar* v, gint len)
{
	if (len<0) {
		len = GX::strlen(v);
	}
	gint lenTo = GX::strUTF8toUTF16Count(v, len);
	gint lenCur = getLength();
	if (changeCapability(lenCur + lenTo + 1)) {
		GX::strUTF8toUTF16(v, len, getDataPtr(lenCur), lenTo);
		setLength(lenCur + lenTo);
	}
}
void GWString::insert(gint idx, const gchar* v, gint len)
{
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
	if (changeCapability(lenCur + lenTo + 1)) {
		memmove(getDataPtr(idx) + lenTo, getDataPtr(idx), (lenCur - idx)*sizeof(gwchar));
		GX::strUTF8toUTF16(v, len, getDataPtr(idx), lenTo);
		setLength(lenCur + lenTo);
	}
}




