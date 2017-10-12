//
//  GJpeg.cpp
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#include "GJpeg.h"
#include "GReader.h"
#include "GXMemory.h"
#include <stdio.h>
#include "jpeglib.h"
#include <setjmp.h>

static bool _cmpHeader(unsigned char* header)
{
	//Start Marker  | JFIF Marker | Header Length | Identifier
	//0xff, 0xd8    | 0xff, 0xe0  |    2-bytes    | "JFIF\0"(0x4a 0x46 0x49 0x46 0x00) || "Exif\0"(0x45, 0x78, 0x69, 0x66, 0x00)
	/*
	unsigned char temp[]={0xff, 0xd8, 0xff, 0xe0, header[4], header[5]};
	if (memcmp(header, temp, sizeof(temp))==0) {
	}
	//*/
	unsigned char JFIF[] = { 0x4a, 0x46, 0x49, 0x46, 0x0 };
    if (GX::gmemcmp(header + 6, JFIF, sizeof(JFIF)) == 0) {
		return true;
	}
	else {
		unsigned char Exif[] = { 0x45, 0x78, 0x69, 0x66, 0x0 };
		if (GX::gmemcmp(header + 6, Exif, sizeof(Exif)) == 0) {
			return true;
		}
	}
	return false;
}

bool GJpeg::checkHeader(GReader* reader)
{
	unsigned char header[11];
	if (reader->read(header, sizeof(header)) == sizeof(header)) {
		return _cmpHeader(header);
	}
	return false;
}

struct my_error_mgr {
	struct jpeg_error_mgr pub;	/* "public" fields */

	jmp_buf setjmp_buffer;	/* for return to caller */
};

typedef struct my_error_mgr * my_error_ptr;

/*
* Here's the routine that will replace the standard error_exit method:
*/

METHODDEF(void)
my_error_exit(j_common_ptr cinfo)
{
	/* cinfo->err really points to a my_error_mgr struct, so coerce pointer */
	my_error_ptr myerr = (my_error_ptr)cinfo->err;

	/* Always display the message. */
	/* We could postpone this until after returning, if we chose. */
	(*cinfo->err->output_message) (cinfo);

	/* Return control to the setjmp point */
	longjmp(myerr->setjmp_buffer, 1);
}

static size_t my_jpeg_fun_src_fun(void* fundata, void* buffer, size_t bufsize)
{
	gint res = static_cast<GReader*>(fundata)->read(buffer, bufsize);
	return res > 0 ? res : 0;
}

GDib* GJpeg::read(GReader* reader)
{
    GDib* res=NULL;
    
	/* This struct contains the JPEG decompression parameters and pointers to
	* working space (which is allocated as needed by the JPEG library).
	*/
	struct jpeg_decompress_struct cinfo;
	/* We use our private extension JPEG error handler.
	* Note that this struct must live as long as the main JPEG parameter
	* struct, to avoid dangling-pointer problems.
	*/
	struct my_error_mgr jerr;

	int row_stride;		/* physical row width in output buffer */

	/* In this example we want to open the input file before doing anything else,
	* so that the setjmp() error recovery below can assume the file is open.
	* VERY IMPORTANT: use "b" option to fopen() if you are on a machine that
	* requires it in order to read binary files.
	*/

	/* Step 1: allocate and initialize JPEG decompression object */

	/* We set up the normal JPEG error routines, then override error_exit. */
	cinfo.err = jpeg_std_error(&jerr.pub);
	jerr.pub.error_exit = my_error_exit;
	/* Establish the setjmp return context for my_error_exit to use. */
	if (setjmp(jerr.setjmp_buffer)) {
		/* If we get here, the JPEG code has signaled an error.
		* We need to clean up the JPEG object, close the input file, and return.
		*/
		jpeg_destroy_decompress(&cinfo);
        GO::release(res);
		return NULL;
	}
	/* Now we can initialize the JPEG decompression object. */
	jpeg_create_decompress(&cinfo);

	/* Step 2: specify data source (eg, a file) */

	//jpeg_stdio_src(&cinfo, infile);
	jpeg_fun_src(&cinfo, my_jpeg_fun_src_fun, reader);

	/* Step 3: read file parameters with jpeg_read_header() */

	jpeg_read_header(&cinfo, TRUE);
	/* We can ignore the return value from jpeg_read_header since
	*   (a) suspension is not possible with the stdio data source, and
	*   (b) we passed TRUE to reject a tables-only JPEG file as an error.
	* See libjpeg.txt for more info.
	*/

	/* Step 4: set parameters for decompression */

	/* In this example, we don't need to change any of the defaults set by
	* jpeg_read_header(), so we do nothing here.
	*/

	/* Step 5: Start decompressor */

	jpeg_start_decompress(&cinfo);
	/* We can ignore the return value since suspension is not possible
	* with the stdio data source.
	*/

	/* We may need to do some setup of our own at this point before reading
	* the data.  After jpeg_start_decompress() we have the correct scaled
	* output image dimensions available, as well as the output colormap
	* if we asked for color quantization.
	* In this example, we need to make an output work buffer of the right size.
	*/
	/* JSAMPLEs per row in output buffer */
	row_stride = cinfo.output_width * cinfo.output_components;
	/* Make a one-row-high sample array that will go away when done with image */
    
    

	if (cinfo.output_components == 3) {
        res=GDib::alloc();
        
        if(res->changeDataBytes(cinfo.output_height*row_stride)) {
            
            res->setPixelFormat(GX::PixelFormatRGB888);
            res->setWidth(cinfo.output_width);
            res->setHeight(cinfo.output_height);
            res->setStride(cinfo.output_width * 3);
            
            //    JSAMPARRAY buffer = (*cinfo.mem->alloc_sarray)
            //    ((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);
            
            JSAMPROW buffer;		/* Output row buffer */
            buffer = ((JSAMPROW)(res->getDataPtr()));
            
            /* Step 6: while (scan lines remain to be read) */
            /*           jpeg_read_scanlines(...); */
            
            /* Here we use the library's state variable cinfo.output_scanline as the
             * loop counter, so that we don't have to keep track ourselves.
             */
            //JSAMPROW rowPtr=(JSAMPROW)(dataOut->GetDataPtr());
            while (cinfo.output_scanline < cinfo.output_height) {
                /* jpeg_read_scanlines expects an array of pointers to scanlines.
                 * Here the array is only one element long, but you could ask for
                 * more than one scanline at a time if that's more convenient.
                 */
                (void)jpeg_read_scanlines(&cinfo, &buffer, 1);
                buffer += row_stride;
            }
        }
        else {
            GO::release(res);
            res=NULL;
        }
	}
	else if (cinfo.output_components == 1) {
        res=GDib::alloc();
        
        if(res->changeDataBytes(cinfo.output_height*row_stride * 3)) {
            
            res->setPixelFormat(GX::PixelFormatRGB888);
            res->setWidth(cinfo.output_width);
            res->setHeight(cinfo.output_height);
            res->setStride(cinfo.output_width * 3);
            
            unsigned char* bufRow = (unsigned char*)malloc(row_stride);
            unsigned char* pData = (unsigned char*)res->getDataPtr();
            
            JSAMPROW buffer = ((JSAMPROW)bufRow);
            
            while (cinfo.output_scanline < cinfo.output_height) {
                jpeg_read_scanlines(&cinfo, &buffer, 1);
                for (int i = 0; i<row_stride; i++) {
                    pData[0] = bufRow[i];
                    pData[1] = bufRow[i];
                    pData[2] = bufRow[i];
                    pData += 3;
                }
            }
            
            free(bufRow);
        }
        else {
            GO::release(res);
            res=NULL;
        }
	}


	/* Step 7: Finish decompression */

	(void)jpeg_finish_decompress(&cinfo);
	/* We can ignore the return value since suspension is not possible
	* with the stdio data source.
	*/

	/* Step 8: Release JPEG decompression object */

	/* This is an important step since it will release a good deal of memory. */
	jpeg_destroy_decompress(&cinfo);
    
    GO::autorelease(res);
	return res;
}
