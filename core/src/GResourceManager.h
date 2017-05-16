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
    bool addBundle(GBundle* v);
    void removeBundle(GBundle* v);
public:
    bool addFileBundle(const gtchar* path);
    bool addZipBundle(const gtchar* path,bool createMap=true);
protected:
    GReader* openReader(GString* fileName,GBundle*& bundleOut);
    void closeReader(GReader* reader,GBundle* bundle);
public:
    
protected:
    virtual gint getMapCount()=0;
    virtual GMap<GString, GObject>* getMap(gint index)=0;
    GObject* findInMap(gint index,GString* key);
    void addToMap(gint index,GString* key,GObject* obj);
private:
    void eventReceivedMemoryWarning(GObject* obj);
protected:
    virtual void didReceivedMemoryWarning()=0;
private:
    GAppBundle*     m_MainBundle;
    GArray<GBundle> m_Bundles;
};

#endif /* GResourceManager_h */
