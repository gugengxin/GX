﻿//
//  GBaseContext.h
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#ifndef GBaseContext_h
#define GBaseContext_h

#include "GXPrefix.h"

#include "GXGObject.h"
// Down can't include other h file

class GWindow;

class GBaseContext {
protected:
    GBaseContext();
    virtual ~GBaseContext();
protected:
    virtual bool create(GWindow* win);
    virtual void destroy();
    
protected:
    inline GWindow* getWindow() {
        return m_Window;
    }
private:
    GWindow* m_Window;
};

// Up can't include other h file
#include "GXGObjectUD.h"

#endif /* GBaseContext_h */
