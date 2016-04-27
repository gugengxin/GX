//
//  GThread.hpp
//  GX
//
//  Created by Gengxin Gu on 16/4/27.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GThread_hpp
#define GThread_hpp

#include "GXPrefix.h"
#include "GObject.h"



class GThread : public GObject {
    GX_OBJECT(GThread);
public:
    
    
private:
    guint m_ID;
};





#endif /* GThread_hpp */
