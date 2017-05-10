//
//  GFontManager.h
//  GX
//
//  Created by GuGengxin.
//  Copyright by gxengine.com
//

#ifndef GFontManager_h
#define GFontManager_h

#include "GXPrefix.h"
#include "GResourceManager.h"


class GFontManager : public GResourceManager
{
public:
    static GFontManager* shared();
private:
    GFontManager();
    virtual ~GFontManager();
public:
    typedef enum _Map {
        MapFT,
        MapCount,
    } Map;
    virtual GMap<GString, GObject>* getMap(gint index);
private:
    void* m_FTLibrary;
    GMap<GString,GObject> m_Maps[MapCount];
};

#endif /* GFontManager_h */
