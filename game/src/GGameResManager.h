//
//  GGameResManager.h
//  GX
//
//  Created by GuGengxin.
//  Copyright by gxengine.com
//

#ifndef GGameResManager_h
#define GGameResManager_h

#include "GXPrefix.h"
#include "GX3DAPIType.h"
#include "GResourceManager.h"
#include "GMap.h"
#include "GTexture2D.h"

class GGameResManager : public GResourceManager
{
public:
	static GGameResManager* shared();
private:
	GGameResManager();
	virtual ~GGameResManager();
public:
	GTexture2D* loadTexture2D(GString* name, GDib::FileType suggestFT, GTexture2D::Parameter* param);
protected:
	typedef enum _Map {
		MapTex2D,
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
};

// Up can't include other h file
#include "GXGObjectUD.h"

#endif /* GGameResManager_h */
