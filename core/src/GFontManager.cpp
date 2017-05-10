//
//  GFontManager.cpp
//  GX
//
//  Created by GuGengxin.
//  Copyright by gxengine.com
//

#include "GFontManager.h"

//-Wdocumentation
#include <ft2build.h>
#include FT_FREETYPE_H


#define M_FT_LIBRARY() GX_CAST_R(FT_Library, m_FTLibrary)


GFontManager* GFontManager::shared()
{
    static GFontManager g_Obj;
    return &g_Obj;
}


GFontManager::GFontManager()
{
    FT_Init_FreeType(GX_CAST_R(FT_Library*, &m_FTLibrary));
}

GFontManager::~GFontManager()
{
    FT_Done_FreeType(M_FT_LIBRARY());
}

GMap<GString, GObject>* GFontManager::getMap(gint index)
{
    return &m_Maps[index];
}


