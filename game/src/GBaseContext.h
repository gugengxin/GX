//
//  GBaseContext.h
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#ifndef GBaseContext_h
#define GBaseContext_h

#include "GXPrefix.h"
#include "GX3DAPI.h"

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
    
public:
	GWindow* getWindow() const;
	GX::DCullFace getCullFace() const;
	virtual void setCullFace(GX::DCullFace v);
private:
    GWindow* m_Window;
	GX::DCullFace m_DCullFace;
};

// Up can't include other h file
#include "GXGObjectUD.h"

#endif /* GBaseContext_h */
