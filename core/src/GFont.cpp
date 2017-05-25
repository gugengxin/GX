//
//  GFont.cpp
//  GX
//
//  Created by GuGengxin.
//  Copyright by gxengine.com
//

#include "GFont.h"
//Down include other h file

//Up include other h file
#include "GXGObject.h"



#include <hb.h>
#include <hb-font-private.hh>


struct hb_gx_font_t
{
    GFont* font;
};

static hb_gx_font_t *
_hb_gx_font_create (GFont* font)
{
    hb_gx_font_t *res = (hb_gx_font_t *) calloc (1, sizeof (hb_gx_font_t));
    
    if (unlikely (!res))
        return NULL;
    
    res->font=font;
    
    return res;
}

static void
_hb_gx_font_destroy (hb_gx_font_t *gx_font)
{
    free (gx_font);
}

////////////////////////////////

static hb_bool_t
hb_gx_get_font_h_extents (hb_font_t *font HB_UNUSED,
                          void *font_data,
                          hb_font_extents_t *metrics,
                          void *user_data HB_UNUSED)
{
    const hb_gx_font_t *gx_font = (const hb_gx_font_t *) font_data;
    GFont* gf=gx_font->font;
    
    metrics->ascender=gf->getAscender();
    metrics->descender=gf->getDescender();
    metrics->line_gap=gf->getHeight()-(gf->getAscender()-gf->getDescender());
    
    if (font->y_scale < 0)
    {
        metrics->ascender = -metrics->ascender;
        metrics->descender = -metrics->descender;
        metrics->line_gap = -metrics->line_gap;
    }
    return true;
}

static hb_bool_t
hb_gx_get_nominal_glyph (hb_font_t *font HB_UNUSED,
                         void *font_data,
                         hb_codepoint_t unicode,
                         hb_codepoint_t *glyph,
                         void *user_data HB_UNUSED)
{
    const hb_gx_font_t *gx_font = (const hb_gx_font_t *) font_data;
    GFont* gf=gx_font->font;
    
    unsigned int g = gf->getIndex(unicode);
    
    if (unlikely (!g))
    {
        return false;
    }
    
    *glyph = g;
    return true;
}

static hb_bool_t
hb_gx_get_variation_glyph (hb_font_t *font HB_UNUSED,
                           void *font_data,
                           hb_codepoint_t unicode,
                           hb_codepoint_t variation_selector,
                           hb_codepoint_t *glyph,
                           void *user_data HB_UNUSED)
{
    const hb_gx_font_t *gx_font = (const hb_gx_font_t *) font_data;
    GFont* gf=gx_font->font;
    
    unsigned int g = gf->getVariantIndex(unicode, variation_selector);
    
    if (unlikely (!g))
        return false;
    
    *glyph = g;
    return true;
}

static hb_position_t
hb_gx_get_glyph_h_advance (hb_font_t *font HB_UNUSED,
                           void *font_data,
                           hb_codepoint_t glyph,
                           void *user_data HB_UNUSED)
{
    const hb_gx_font_t *gx_font = (const hb_gx_font_t *) font_data;
    GFont* gf=gx_font->font;
    
    signed long v=gf->getAdvanceH(glyph);
    if (v==0) {
        return 0;
    }
    
    if (font->x_scale < 0)
        v = -v;
    
    return (hb_position_t)((v + (1<<9)) >> 10);
}

static hb_position_t
hb_gx_get_glyph_v_advance (hb_font_t *font HB_UNUSED,
                           void *font_data,
                           hb_codepoint_t glyph,
                           void *user_data HB_UNUSED)
{
    const hb_gx_font_t *gx_font = (const hb_gx_font_t *) font_data;
    GFont* gf=gx_font->font;
    
    signed long v=gf->getAdvanceV(glyph);
    if (v==0) {
        return 0;
    }
    
    if (font->y_scale < 0)
        v = -v;
    
    /* Note: FreeType's vertical metrics grows downward while other FreeType coordinates
     * have a Y growing upward.  Hence the extra negation. */
    return (hb_position_t)((-v + (1<<9)) >> 10);
}

static hb_bool_t
hb_gx_get_glyph_v_origin (hb_font_t *font HB_UNUSED,
                          void *font_data,
                          hb_codepoint_t glyph,
                          hb_position_t *x,
                          hb_position_t *y,
                          void *user_data HB_UNUSED)
{
    const hb_gx_font_t *gx_font = (const hb_gx_font_t *) font_data;
    GFont* gf=gx_font->font;
    
    GFont::Glyph* gh=gf->getGlyph(glyph);
    if (!gh) {
        return false;
    }
    
    /* Note: FreeType's vertical metrics grows downward while other FreeType coordinates
     * have a Y growing upward.  Hence the extra negation. */
    *x = gh->getHoriBearingX() - gh->getVertBearingX();
    *y = gh->getHoriBearingY() - (-gh->getVertBearingY());
    
    if (font->x_scale < 0)
        *x = -*x;
    if (font->y_scale < 0)
        *y = -*y;
    
    return true;
}


////////////////////////////////


static hb_font_funcs_t *static_ft_funcs = NULL;

static hb_font_t* hb_gx_font_create(GFont* gf)
{
    hb_font_t* font=hb_font_create(hb_face_get_empty());
    
retry:
    hb_font_funcs_t *funcs = (hb_font_funcs_t *) hb_atomic_ptr_get (&static_ft_funcs);
    
    if (unlikely (!funcs))
    {
        funcs = hb_font_funcs_create ();
        
        hb_font_funcs_set_font_h_extents_func (funcs, hb_gx_get_font_h_extents, NULL, NULL);
        //hb_font_funcs_set_font_v_extents_func (funcs, hb_ft_get_font_v_extents, NULL, NULL);
        hb_font_funcs_set_nominal_glyph_func (funcs, hb_gx_get_nominal_glyph, NULL, NULL);
        hb_font_funcs_set_variation_glyph_func (funcs, hb_gx_get_variation_glyph, NULL, NULL);
        hb_font_funcs_set_glyph_h_advance_func (funcs, hb_gx_get_glyph_h_advance, NULL, NULL);
        hb_font_funcs_set_glyph_v_advance_func (funcs, hb_gx_get_glyph_v_advance, NULL, NULL);
        //hb_font_funcs_set_glyph_h_origin_func (funcs, hb_ft_get_glyph_h_origin, NULL, NULL);
        hb_font_funcs_set_glyph_v_origin_func (funcs, hb_gx_get_glyph_v_origin, NULL, NULL);
//        hb_font_funcs_set_glyph_h_kerning_func (funcs, hb_ft_get_glyph_h_kerning, NULL, NULL);
//        //hb_font_funcs_set_glyph_v_kerning_func (funcs, hb_ft_get_glyph_v_kerning, NULL, NULL);
//        hb_font_funcs_set_glyph_extents_func (funcs, hb_ft_get_glyph_extents, NULL, NULL);
//        hb_font_funcs_set_glyph_contour_point_func (funcs, hb_ft_get_glyph_contour_point, NULL, NULL);
//        hb_font_funcs_set_glyph_name_func (funcs, hb_ft_get_glyph_name, NULL, NULL);
//        hb_font_funcs_set_glyph_from_name_func (funcs, hb_ft_get_glyph_from_name, NULL, NULL);

        hb_font_funcs_make_immutable (funcs);
        
        if (!hb_atomic_ptr_cmpexch (&static_ft_funcs, NULL, funcs)) {
            hb_font_funcs_destroy (funcs);
            goto retry;
        }
    };
    
    hb_font_set_funcs (font,
                       funcs,
                       _hb_gx_font_create (gf),
                       (hb_destroy_func_t) _hb_gx_font_destroy);
    
    hb_font_set_scale(font, gf->getScaleX(), gf->getScaleY());
    
    return font;
}

static void hb_gx_font_destroy(hb_font_t* font)
{
    hb_font_destroy(font);
}

//////////////////////////////////////////////////////////////////




GX_GOBJECT_IMPLEMENT(GFont::Glyph, GObject);

GFont::Glyph::Glyph()
{
    m_Index=0u;
}

GFont::Glyph::~Glyph()
{
    
}


GX_GOBJECT_IMPLEMENT(GFont, GObject);

GFont::GFont()
{
	
}

GFont::~GFont()
{
}


