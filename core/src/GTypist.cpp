//
//  GTypist.cpp
//  GX
//
//  Created by GuGengxin.
//  Copyright by gxengine.com
//

#include "GTypist.h"

GSizeF GTypist::sizeOfString(GString * str, GFont * font)
{
    GSizeF res(0.0f, font->getHeight());
    gint len=str->getLength();
    if (len>0) {
        bool use_kerning=font->hasKerning();
        guint32 previous=0;
        guint32 glyph_index;
        
        for (gint i=0; i<len; i++) {
            GFont::Glyph* glyph=GX_CAST_R(GFont::Glyph*, font->getGlyph(str->at(i)));
            if (!glyph) {
                continue;
            }
            glyph_index=glyph->getIndex();
            
            if (use_kerning && previous && glyph_index ) {
                res.width += font->getKerningX(previous, glyph_index);
            }
            
            res.width+=glyph->getAdvanceX();
            previous=glyph_index;
        }
    }
    
    return res;
}
