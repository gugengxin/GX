//
//  GTypist.cpp
//  GX
//
//  Created by GuGengxin.
//  Copyright by gxengine.com
//

#include "GTypist.h"

#if __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#pragma clang diagnostic ignored "-Wshorten-64-to-32"
#endif
#include <hb.h>
#if __clang__
#pragma clang diagnostic pop
#endif

#include "GXGObject.h"

#define M_HB_BUF() GX_CAST_R(hb_buffer_t*,m_HBBuffer)

GX_GOBJECT_IMPLEMENT(GTypist, GObject);

GTypist::GTypist()
{
	m_Font = NULL;
	m_HBBuffer = NULL;
}

GTypist::~GTypist()
{
	if (m_HBBuffer) {
		hb_buffer_destroy(M_HB_BUF());
	}
	GO::release(m_Font);
}

void GTypist::singleLine(GString * str, GFont * font)
{
	hb_font_t* hb_font = GX_CAST_R(hb_font_t*, font->getHBFont());

	hb_buffer_t *hb_buffer;
	hb_buffer = hb_buffer_create();
	hb_buffer_add_utf16(hb_buffer, str->utf16String(), (int)str->getLength(), 0, -1);
	hb_buffer_guess_segment_properties(hb_buffer);

	hb_shape(hb_font, hb_buffer, NULL, 0);

	//*
	// Get glyph information and positions out of the buffer.
	unsigned int len = hb_buffer_get_length(hb_buffer);
	hb_glyph_info_t *info = hb_buffer_get_glyph_infos(hb_buffer, NULL);
	hb_glyph_position_t *pos = hb_buffer_get_glyph_positions(hb_buffer, NULL);

	// Print them out as is.
	printf("Raw buffer contents:\n");
	for (unsigned int i = 0; i < len; i++)
	{
		hb_codepoint_t gid = info[i].codepoint;
		unsigned int cluster = info[i].cluster;
		double x_advance = pos[i].x_advance / 64.;
		double y_advance = pos[i].y_advance / 64.;
		double x_offset = pos[i].x_offset / 64.;
		double y_offset = pos[i].y_offset / 64.;

		//char glyphname[32];
		//hb_font_get_glyph_name(hb_font, gid, glyphname, sizeof(glyphname));

		printf("gid=%d	cluster=%d	advance=(%g,%g)	offset=(%g,%g)\n",
			gid, cluster, x_advance, y_advance, x_offset, y_offset);
	}

	printf("Converted to absolute positions:\n");
	// And converted to absolute positions.
	{
		double current_x = 0;
		double current_y = 0;
		for (unsigned int i = 0; i < len; i++)
		{
			hb_codepoint_t gid = info[i].codepoint;
			unsigned int cluster = info[i].cluster;
			double x_position = current_x + pos[i].x_offset / 64.;
			double y_position = current_y + pos[i].y_offset / 64.;


			//char glyphname[32];
			//hb_font_get_glyph_name(hb_font, gid, glyphname, sizeof(glyphname));

			printf("gid=%d	cluster=%d	position=(%g,%g)\n",
				gid, cluster, x_position, y_position);

			current_x += pos[i].x_advance / 64.;
			current_y += pos[i].y_advance / 64.;
		}
	}
	//*/
	GX_OBJECT_SET(m_Font, font);
	if (m_HBBuffer) {
		hb_buffer_destroy(M_HB_BUF());
	}
	m_HBBuffer = hb_buffer;


}
