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


GX_OBJECT_IMPLEMENT(GString, GDataString<gchar>);


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

/*
void GString::format(const gchar* fmt,va_list va)
{
    if (getLength()>0) {
        clear();
    }
    appendFormat(fmt, va);
}

void GString::format(const gchar* fmt,...)
{
    va_list va;
    va_start(va, fmt);
    format(fmt, va);
    va_end(va);
}
void GString::appendFormat(const gchar* fmt,va_list va)
{
    gint iLast=0;
    gint i=0;
    while (true) {
        if (fmt[i]=='\0') {
            if (iLast<i-1) {
                append(&fmt[iLast],i-iLast);
            }
            break;
        }
        else if (fmt[i]=='%') {
            if (iLast<i-1) {
                append(&fmt[iLast],i-iLast);
                iLast=i;
            }
            if (fmt[i+1]=='%') {
                append(&fmt[i],1);
                i+=2;
                iLast=i;
            }
            else {
                gint j=i+1;
                
                while (true) {
                    if (fmt[j]=='d') {
                        
                    }
                    else if(fmt[j]=='u') {
                        
                    }
                    else if(fmt[j]=='x') {
                        
                    }
                    else if(fmt[j]=='X') {
                        
                    }
                    else if(fmt[j]=='f') {
                        
                    }
                    else if(fmt[j]=='s') {
                        
                    }
                    else {
                        j++;
                    }
                }
                
            }
        }
        else {
            i++;
        }
    }
}
void GString::appendFormat(const gchar* fmt,...)
{
    va_list va;
    va_start(va, fmt);
    appendFormat(fmt, va);
    va_end(va);
}
//*/




