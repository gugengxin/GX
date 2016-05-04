//
//  GTString.h
//  GX
//
//  Created by Gengxin Gu on 16/5/4.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GTString_h
#define GTString_h

#include "GXPrefix.h"
#include "GString.h"
#include "GWString.h"

#ifdef GX_PATH_IS_CHAR
#define GX_TSTRING_BASE_CLASS GString
#elif defined(GX_PATH_IS_WCHAR)
#define GX_TSTRING_BASE_CLASS GWString
#endif

class GTString : public GX_TSTRING_BASE_CLASS {
    GX_OBJECT(GTString);
    
public:
    
};



#endif /* GTString_h */
