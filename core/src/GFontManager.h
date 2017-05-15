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
#include "GFT.h"



class GFontManager : public GResourceManager
{
public:
    static GFontManager* shared();
private:
    GFontManager();
    virtual ~GFontManager();
public:
    GFT::Font* loadFTFont(GString* name, gint size, gint outlineSize);
    
protected:
    typedef enum _Map {
        MapFT,
        MapCount,
    } Map;
    virtual GMap<GString, GObject>* getMap(gint index);
private:
    GMap<GString, GObject> m_Maps[MapCount];
    GMap<GString, GObject> m_SystemFontNames;
    void* m_FTLibrary;
    GMap<GString, GData> m_FTDataMap;
};

#endif /* GFontManager_h */
