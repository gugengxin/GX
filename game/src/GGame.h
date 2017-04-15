//
//  GGame.h
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#ifndef GGame_h
#define GGame_h

#include "GXPrefix.h"
#include "GObject.h"
#include "GCanvas.h"


#include "GXGObject.h"
// Down can't include other h file

class GWindow;

class GGame : public GObject
{
    friend class GWindow;
	GX_VIRTUAL_GOBJECT(GGame);
protected:
    virtual void eventStart(GWindow* window);
    virtual void eventStop();
public:
    inline GWindow* getWindow() {
        return m_Window;
    }
    virtual gint getFPS();//默认=30
    virtual void idle();
    virtual void render(GCanvas* canvas);
private:
    void run();
private:
    GWindow* m_Window;
    gint64	 m_RunLastTime;
};

// Up can't include other h file
#include "GXGObjectUD.h"

#endif /* GGame_h */
