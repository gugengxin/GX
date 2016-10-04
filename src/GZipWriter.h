//
//  GZipWriter.h
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#ifndef GZipWriter_h
#define GZipWriter_h

#include "GXPrefix.h"
#include "GWriter.h"



#include "GXGObject.h"
// Down can't include other h file

class GZipWriter : public GWriter
{
	GX_GOBJECT(GZipWriter);
public:
    typedef enum _Mode {
        ModeCreate=0,
        ModeCreateAfter,
        ModeAddInZip,
    } Mode;
    
    typedef enum _Level {
        LevelDefaultCompression =-1,
        LevelNoCompression=0,
        LevelBestSpeed=1,
        LevelBestCompression=9,
        Level0=LevelNoCompression,
        Level1=LevelBestSpeed,
        Level2=2,
        Level3=3,
        Level4=4,
        Level5=5,
        Level6=6,
        Level7=7,
        Level8=8,
        Level9=LevelBestCompression,
    } Level;
public:
    bool open(const gtchar* filePath,Mode mode);
    virtual void close();
    
    bool openNewFileInZip(const gchar* fileName,Level level);
    bool closeFileInZip();
public:
    virtual bool hasSpace();
    //<0:Error 0<=res<len:End >=len:Not end
    virtual gint write(const void* buf,guint len);
    virtual bool skip(guint len);
    virtual gint getBytes();
public:
    virtual bool canRollback();
    virtual bool rollback(guint len);
private:
    void*   m_ZipFile;
    gint    m_BytesWrite;
};

// Up can't include other h file
#include "GXGObjectUD.h"

#endif /* GZipWriter_h */
