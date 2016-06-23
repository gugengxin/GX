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


};

#include "GXGObjectUD.h"

#endif /* GWString_h */
