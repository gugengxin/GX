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
	virtual bool isEqual(GObject* obj);

	const gchar* c_str();

	void set(const gchar* v, gint len = -1, gint count = 1);
	void append(const gchar* v, gint len = -1, gint count = 1);
	void insert(gint idx, const gchar* v, gint len = -1, gint count = 1);
	void set(const gwchar* v, gint len = -1, gint count = 1);
	void append(const gwchar* v, gint len = -1, gint count = 1);
	void insert(gint idx, const gwchar* v, gint len = -1, gint count = 1);
	
	void set(gchar v, gint count);
	void append(gchar v, gint count);
	void insert(gint idx, gchar v, gint count);
	void set(gwchar v, gint count);
	void append(gwchar v, gint count);
	void insert(gint idx, gwchar v, gint count);

	void format(const gchar* fmt, va_list va);
	void format(const gchar* fmt, ...);
	void appendFormat(const gchar* fmt, va_list va);
	void appendFormat(const gchar* fmt, ...);
};

#include "GXGObjectUD.h"

#endif /* GString_h */
