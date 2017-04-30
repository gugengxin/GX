//
//  GResourceManager.h
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#ifndef GResourceManager_h
#define GResourceManager_h

#include "GXPrefix.h"
#include "GArray.h"
#include "GBundle.h"
#include "GAppBundle.h"
#include "GMap.h"
#include "GString.h"

class GResourceManager
{
protected:
    GResourceManager();
    virtual ~GResourceManager();
public:
    void addBundle(GBundle* v);
    void removeBundle(GBundle* v);
public:
    
protected:
    virtual GMap<GString, GObject>* getMap(gint index)=0;
    GObject* findInMap(gint index,GString* key);
    void addToMap(gint index,GString* key,GObject* obj);
    
    
private:
    GAppBundle*     m_MainBundle;
    GArray<GBundle> m_Bundles;
};

#endif /* GResourceManager_h */
