//
//  GUUID.h
//  GX
//
//  Created by Gu Gengxin on 16/5/1.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GUUID_h
#define GUUID_h

#include "GXPrefix.h"
#include "GObject.h"

class GUUID : public GObject {
    GX_OBJECT(GUUID);
public:

private:
    guint8 m_Bytes[16];
};


#endif /* GUUID_h */
