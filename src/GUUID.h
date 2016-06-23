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
#if defined(GX_OS_WINDOWS)
#include "GXCWnd.h"
#endif


#include "GXGObject.h"

class GUUID : public GObject {
#if defined(GX_OS_WINDOWS)
	friend class GX::CWnd;
#endif
	GX_GOBJECT(GUUID);
public:
    inline guint8* getPtr() {
        return m_Bytes;
    }

private:
    guint8 m_Bytes[16];
};

#include "GXGObjectUD.h"

#endif /* GUUID_h */
