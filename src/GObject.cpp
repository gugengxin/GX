//
//  GObject.cpp
//  GX
//
//  Created by Gengxin Gu on 16/4/19.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#include "GObject.h"



void GObject::retain(GObject* obj)
{
	if (obj) {
		++(*((GX_CAST_R(gi32*, obj) - 1)));
	}
}
void GObject::release(GObject* obj)
{
	if (obj) {
		gi32* p = GX_CAST_R(gi32*, obj) - 1;
		--(*p);
		if ((*p) <= 0) {
			delete obj;
		}
	}
}
void* GObject::gnew(size_t size)
{
	void* p = malloc(size+sizeof(gi32));
	*GX_CAST_R(gi32*, p) = 1;
	return GX_CAST_R(gi32*, p) + 1;
}
void GObject::gdel(void* p)
{
	free(GX_CAST_R(gi32*, p) - 1);
}


GClass GObject::gclass("GObject",sizeof(GObject),GX_CAST_R(GClass::Alloc,GObject::alloc),NULL);
static GClass::Initializer g_Initializer(&GObject::gclass);
GClass* GObject::getClass()
{
    return &gclass;
}
GObject* GObject::alloc()
{
    return new GObject();
}
void* GObject::operator new(size_t size)
{
	return gnew(size);
}
void GObject::operator delete(void* p)
{
	gdel(p);
}

GObject::GObject()
{
    
}
GObject::~GObject()
{
    
}

const gchar* GObject::getClassName()
{
    return getClass()->getName();
}
bool  GObject::isMemberOfClass(GClass* pClass)
{
    return getClass()->isMemberOf(pClass);
}
bool  GObject::isMemberOfClass(GClass& cls)
{
    return getClass()->isMemberOf(&cls);
}
bool  GObject::isKindOfClass(GClass* pClass)
{
    return getClass()->isKindOf(pClass);
}

bool  GObject::isKindOfClass(GClass& cls)
{
    return getClass()->isKindOf(&cls);
}