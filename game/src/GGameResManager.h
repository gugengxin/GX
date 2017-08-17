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
#include "GTexture2D.h"
#include "GTex2DFont.h"

class GGameResManager : public GResourceManager
{
public:
	static GGameResManager* shared();
private:
	GGameResManager();
	virtual ~GGameResManager();
public:
	GTexture2D* loadTexture2D(GString* name, GDib::FileType suggestFT, GTexture2D::Parameter* param);
    GTex2DFont* loadTex2DFont(GString* name, gint32 size, gint32 outlineSize, float density);
protected:
	typedef enum _Map {
		MapTex2D,
        MapTex2DFont,
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
