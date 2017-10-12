
#ifndef GXFILE_h
#define GXFILE_h

#include "GXPrefix.h"


namespace GX {

    class File {
    public:
        typedef enum _Mode {
            ModeRead,
            ModeWrite,
            ModeWriteAppend,
            ModeRW,
        } Mode;
        typedef enum _Seek {
            SeekSet,
            SeekCur,
            SeekEnd,
        } Seek;
    public:
        File();
        ~File();

        bool open(const gtchar* path, Mode mode);
        void close();
        gint tell();
        bool seek(gint offset, Seek origin);
        gint read(void* buf, guint len);
        gint write(const void* buf,guint len);
        
    private:
        void* m_FILE;
    };

}

#endif /* GXFILE_h */
