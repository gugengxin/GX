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
#include "GFTFont.h"
#include "GData.h"



class GFontManager : public GResourceManager
{
public:
    static GFontManager* shared();
private:
    GFontManager();
    virtual ~GFontManager();
public:
    GFTFont* loadFTFont(GString* name, gint32 size, gint32 outlineSize);
    
protected:
    typedef enum _Map {
        MapFT,
        MapCount,
    } Map;
    virtual gint getMapCount() {
        return MapCount;
    }
    virtual GMap<GString, GObject>* getMap(gint index);
protected:
    virtual void didReceivedMemoryWarning();
private:
    GMap<GString, GObject> m_Maps[MapCount];
    GMap<GString, GObject> m_SystemFontNames;
    void* m_FTLibrary;
    GMap<GString, GData> m_FTDataMap;
};

#endif /* GFontManager_h */
