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
#include "GObject.h"
#include "GPieceData.h"

class GString : public GObject {
    GX_OBJECT(GString);
public:
    
    
private:
    GPieceData m_Data;
};

#endif /* GString_h */
