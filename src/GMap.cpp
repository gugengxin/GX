//
//  GMap.cpp
//  GX
//
//  Created by Gengxin Gu on 16/4/29.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#include "GMap.h"
#include "GXGObject.h"

GX_GOBJECT_IMPLEMENT(GMapBase, GObject);

GMapBase::GMapBase()
{
    
}

GMapBase::~GMapBase()
{
    
}

const gint GMapBase::capabilitys[]={
    7,
    17,
    37,
    79,
    163,
    331,
    673,
    1361,
    2729,
    5471,
    10949,
    21911,
    43853,
    87719,
    175447,
    350899,
    701819,
    1403641,
    2807303,
    5614657,
    11229331,
    22458671,
    44917381,
    89834777,
    179669557,
    359339171,
    718678369,
    1437356741,
    2147483647,
    0,
};