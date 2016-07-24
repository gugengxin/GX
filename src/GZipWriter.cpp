//
//  GZipWriter.cpp
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#include "GZipWriter.h"
#include "GXGObject.h"
#include "zlib.h"
#include "zip.h"
#if defined(GX_OS_WINDOWS) || defined(GX_OS_QT_WINDOWS)
#include "iowin32.h"
#endif

#if GX_PTR_32BIT

#define M_OPENZIP(path,append,def)			zipOpen2((const char*)path,append,0,def)
#define M_FILEFUNC_DEF						zlib_filefunc_def
#define M_FILL_FILEFUNC						fill_fopen_filefunc
#define M_FILL_WIN32_FILEFUNC				fill_win32_filefunc
#define M_OPEN_NEWFILE(file,filename,level) zipOpenNewFileInZip(file,filename,0,0,0,0,0,0,0,level)

#elif GX_PTR_64BIT

#define M_OPENZIP(path,append,def)			zipOpen2_64((const void*)path,append,0,def)
#define M_FILEFUNC_DEF						zlib_filefunc64_def
#define M_FILL_FILEFUNC						fill_fopen64_filefunc
#define M_FILL_WIN32_FILEFUNC				fill_win32_filefunc64
#define M_OPEN_NEWFILE(file,filename,level) zipOpenNewFileInZip64(file,filename,0,0,0,0,0,0,0,level,1)

#endif

#define M_ZIPFILE() ((zipFile)m_ZipFile)

GX_GOBJECT_IMPLEMENT(GZipWriter, GWriter);

GZipWriter::GZipWriter()
{
    m_ZipFile=NULL;
    m_BytesWrite=0;
}

GZipWriter::~GZipWriter()
{
    if (m_ZipFile) {
        zipCloseFileInZip(M_ZIPFILE());
        zipClose(M_ZIPFILE(),NULL);
    }
}

bool GZipWriter::open(const gtchar* filePath,Mode mode)
{
    M_FILEFUNC_DEF funDef;
#ifdef GX_OS_MICROSOFT
    M_FILL_WIN32_FILEFUNC(&funDef);
#else
    M_FILL_FILEFUNC(&funDef);
#endif
    m_ZipFile=M_OPENZIP(filePath,mode,&funDef);
    if (m_ZipFile) {
        return true;
    }
    return false;
}

void GZipWriter::close()
{
    if (m_ZipFile) {
        zipClose(M_ZIPFILE(),NULL);
        m_ZipFile=NULL;
    }
    m_BytesWrite=0;
}

bool GZipWriter::openNewFileInZip(const gchar* fileName,Level level)
{
    if (M_OPEN_NEWFILE(M_ZIPFILE(),fileName,(int)level)==ZIP_OK) {
        m_BytesWrite=0;
        return true;
    }
    return false;
}

bool GZipWriter::closeFileInZip()
{
    return zipCloseFileInZip(M_ZIPFILE())==ZIP_OK;
}

bool GZipWriter::hasSpace()
{
    return true;
}

gint GZipWriter::write(void* buf,guint len)
{
    if(zipWriteInFileInZip(M_ZIPFILE(), buf, (unsigned)len)==ZIP_OK) {
        m_BytesWrite+=(gint)len;
        return (gint)len;
    }
    return -1;
}

bool GZipWriter::skip(guint len)
{
    guint8 buffer[256]={0};
    int bytes;
    while (len>0) {
        if (len<sizeof(buffer)) {
            if(zipWriteInFileInZip(M_ZIPFILE(), buffer, (unsigned)len)==ZIP_OK) {
                bytes=(int)len;
            }
            else {
                bytes=-1;
            }
        }
        else {
            if(zipWriteInFileInZip(M_ZIPFILE(), buffer, (unsigned)sizeof(buffer))==ZIP_OK) {
                bytes=(int)sizeof(buffer);
            }
            else {
                bytes=-1;
            }
        }
        if (bytes>=0) {
            m_BytesWrite+=bytes;
            len-=(guint)bytes;
        }
        else {
            return false;
        }
    }
    return true;
}

gint GZipWriter::getBytes()
{
    return m_BytesWrite;
}

bool GZipWriter::canRollback()
{
    return false;
}

bool GZipWriter::rollback(guint len)
{
    GX_UNUSED(len);
    return false;
}

