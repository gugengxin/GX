//
//  GRBReader.h
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#ifndef GRBReader_h
#define GRBReader_h

#include "GXPrefix.h"
#include "GReader.h"
#include "GPieceData.h"


#include "GXGObject.h"
// Down can't include other h file

class GRBReader : public GReader
{
	GX_GOBJECT(GRBReader);
public:
    bool open(GReader* reader);
	virtual void close();
public:
	virtual bool hasData();
	virtual gint read(void* buf, guint len);
	virtual bool skip(guint len);
	virtual gint getBytes();
public:
    void closeRollback();
	virtual bool canRollback();
	virtual bool rollback(guint len);
public:
	virtual bool canGetLength();
	virtual gint getLength();
private:
    GReader*    m_Reader;
    GPieceData  m_Data;
#if GX_PTR_32BIT
    guint       m_Cursor:31;
#elif GX_PTR_64BIT
    guint       m_Cursor:63;
#endif
    guint       m_RBClosed:1;
};

// Up can't include other h file
#include "GXGObjectUD.h"

#endif /* GRBReader_h */
