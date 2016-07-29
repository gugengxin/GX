//
//  GPng.cpp
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#include "GPng.h"
#include "png.h"
#include "pngstruct.h"
#include "GReader.h"

#define PNG_SIG_BYTES 8

static void _reader_png_read_data(png_structp pPng, png_bytep data, png_size_t length)
{
	if (pPng == NULL)
		return;

	gint check = static_cast<GReader*>(pPng->io_ptr)->read(data, length);

	if (check != length)
		png_error(pPng, "Read Error");
}

bool GPng::check(GReader* reader)
{
	unsigned char header[PNG_SIG_BYTES];
	if (reader->read(header, sizeof(header)) == sizeof(header)) {
		return png_sig_cmp(header, 0, PNG_SIG_BYTES) == 0;
	}
	return false;
}

GDib* GPng::read(GReader* reader)
{
	unsigned char header[PNG_SIG_BYTES];
	if (reader->read(&header, PNG_SIG_BYTES) != sizeof(header)) {
		return NULL;
	}

	if (png_sig_cmp(header, 0, PNG_SIG_BYTES)) {
		return NULL;
	}

	png_uint_32 pngWidth, pngHeight;

	int bits = 0;

	png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	png_infop info_ptr = png_create_info_struct(png_ptr);
	png_infop end_info = png_create_info_struct(png_ptr);
	if (png_ptr == NULL || info_ptr == NULL || end_info == NULL)
	{
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		return NULL;
	}

	if (setjmp(png_jmpbuf(png_ptr))) {
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		return NULL;
	}

	//png_init_io(png_ptr, png_file);
	png_set_read_fn(png_ptr, reader, _reader_png_read_data);

	png_set_sig_bytes(png_ptr, PNG_SIG_BYTES);
	png_read_info(png_ptr, info_ptr);

	pngWidth = png_get_image_width(png_ptr, info_ptr);
	pngHeight = png_get_image_height(png_ptr, info_ptr);

	int bit_depth, color_type;
	bit_depth = png_get_bit_depth(png_ptr, info_ptr);
	color_type = png_get_color_type(png_ptr, info_ptr);

	if (color_type == PNG_COLOR_TYPE_PALETTE) {
		png_set_palette_to_rgb(png_ptr);
	}

	if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
		png_set_expand_gray_1_2_4_to_8(png_ptr);

	if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS)) {
		png_set_tRNS_to_alpha(png_ptr);
	}

	if (bit_depth == 16)
		png_set_strip_16(png_ptr);

	else if (bit_depth < 8)
		png_set_packing(png_ptr);

	png_read_update_info(png_ptr, info_ptr);

	png_get_IHDR(png_ptr, info_ptr,
		&pngWidth, &pngHeight, &bit_depth, &color_type,
		NULL, NULL, NULL);

	GX::PixelFormat pf;
	switch (color_type)
	{
	case PNG_COLOR_TYPE_GRAY:
	{
		pf = GX::PixelFormatA8;
		bits = 1;
	}
	break;
	case PNG_COLOR_TYPE_RGB:
	{
		pf = GX::PixelFormatRGB888;
		bits = 3;
	}
	break;
	case PNG_COLOR_TYPE_RGB_ALPHA:
	{
		pf = GX::PixelFormatRGBA8888;
		bits = 4;
	}
	break;
	case PNG_COLOR_TYPE_GRAY_ALPHA:
	default:
	{
		pf = GX::PixelFormatUnknown;
	}
	break;
	}
    
    GDib* res=NULL;
	if (pf != GX::PixelFormatUnknown) {
        res=GDib::alloc();
        
        if(res->changeDataBytes(pngWidth*pngHeight*bits)) {
            
            png_byte* pixels = (png_byte*)res->getDataPtr();
            png_byte** row_ptrs = (png_byte**)malloc(pngHeight * sizeof(png_bytep));
            
            for (int i = 0; i<(int)pngHeight; i++)
                row_ptrs[i] = pixels + i*pngWidth*bits;
            
            png_read_image(png_ptr, row_ptrs);
            
            free(row_ptrs);
            
            res->setPixelFormat(pf);
            res->setWidth(pngWidth);
            res->setHeight(pngHeight);
            res->setStride(pngWidth*bits);
        }
        else {
            GO::release(res);
            res=NULL;
        }

	}
	png_read_end(png_ptr, end_info);
	png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
    
    GO::autorelease(res);
	return res;
}

