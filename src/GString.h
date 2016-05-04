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
#include "GXEncoding.h"


class GString : public GDataString<gchar> {
    GX_OBJECT(GString);
public:
    const gchar* c_str() {
        return GX_CAST_R(const gchar*, getDataPtr());
    }
    /*
    void format(const gchar* fmt,va_list va);
    void format(const gchar* fmt,...);
    void appendFormat(const gchar* fmt,va_list va);
    void appendFormat(const gchar* fmt,...);
    //*/
};

#endif /* GString_h */
