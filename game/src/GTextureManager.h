//
//  GTextureManager.h
//  GX
//
//  Created by GuGengxin.
//  Copyright by gxengine.com
//

#ifndef GTextureManager_h
#define GTextureManager_h

#include "GXPrefix.h"
#include "GResourceManager.h"
#include "GTexture2D.h"

class GContext;

class GTextureManager : public GResourceManager
{
    friend class GContext;
public:
    static GTextureManager* shared(GContext* context);
private:
    GTextureManager(GContext* context);
    virtual ~GTextureManager();
public:
    GTexture2D* load2D(GString* name,GString* exName);
protected:
    typedef enum _Map {
        MapTex2D,
        MapCount,
    } Map;
    virtual GMap<GString, GObject>* getMap(gint index);
private:
    GContext* m_Context;
    GMap<GString,GObject> m_Maps[MapCount];
};

#endif /* GTextureManager_h */
