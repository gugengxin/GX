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
	virtual bool isEqual(GObject* obj);

	const gwchar* c_str();

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

	void set(gchar v, gint count);
	void append(gchar v, gint count);
	void insert(gint idx, gchar v, gint count);
	void set(gwchar v, gint count);
	void append(gwchar v, gint count);
	void insert(gint idx, gwchar v, gint count);
};

#include "GXGObjectUD.h"

#endif /* GWString_h */
