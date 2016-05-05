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


class GWString : public GDataString<gwchar> {
    GX_OBJECT(GWString);
public:
    const gwchar* c_str() {
        return GX_CAST_R(const gwchar*, getDataPtr());
    }
	void set(const gchar* v, gint len = -1, gint count=1);
	void append(const gchar* v, gint len = -1, gint count = 1);
	void insert(gint idx, const gchar* v, gint len = -1, gint count = 1);


};

#endif /* GWString_h */
