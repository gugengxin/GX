//
//  GGameResManager.cpp
//  GX
//
//  Created by GuGengxin.
//  Copyright by gxengine.com
//

#include "GGameResManager.h"
#include "GFontManager.h"

GGameResManager * GGameResManager::shared()
{
	static GGameResManager g_Obj;
	return &g_Obj;
}

GGameResManager::GGameResManager()
{

}

GGameResManager::~GGameResManager()
{
}

GTexture2D* GGameResManager::loadTexture2D(GString* name, GDib::FileType suggestFT, GTexture2D::Parameter* param)
{
	GTexture2D* res = GX_CAST_R(GTexture2D*, findInMap(MapTex2D, name));
	if (!res) {
		GBundle* bundle = NULL;
		GReader* reader = openReader(name, bundle);
		if (reader) {
			res = GTexture2D::alloc();
			if (res->create(reader,suggestFT,param)) {
				closeReader(reader, bundle);

				addToMap(MapTex2D, name, res);
				GO::autorelease(res);
			}
			else {
				closeReader(reader, bundle);
				GO::release(res);
				res = NULL;
			}
		}
	}
	return res;
}

GTex2DFont* GGameResManager::loadTex2DFont(GString* name, gint32 size, gint32 outlineSize, float density)
{
    if (size<=0) {
        size=12;
    }
    if (outlineSize<0) {
        outlineSize=0;
    }
    GString* key=GString::alloc();
    key->format("%@_%@_%@_%@").arg(name).arg(size).arg(outlineSize).arg(density).end();
    
    GTex2DFont* res=GX_CAST_R(GTex2DFont*, findInMap(MapTex2DFont, key));
    if (!res) {
        GFTFont* ftFont=GFontManager::shared()->loadFTFont(name, size, outlineSize);
        if (ftFont) {
            res=GTex2DFont::alloc();
            res->create(ftFont,density);
            addToMap(MapTex2DFont, key, res);
            GO::autorelease(res);
        }
    }
    
    GO::release(key);
    return res;
}

GMap<GString, GObject>* GGameResManager::getMap(gint index)
{
	return &m_Maps[index];
}

void GGameResManager::didReceivedMemoryWarning()
{
}
