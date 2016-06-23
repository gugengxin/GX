//
//  GZipReader.h
//  GX
//
//  Created by Gengxin Gu on 16/6/22.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GZipReader_h
#define GZipReader_h

#include "GXPrefix.h"
#include "GReader.h"

#include "GXGObject.h"

class GZipReader : public GReader {
	GX_GOBJECT(GZipReader);
public:
	bool open(const gtchar* path);
	virtual void close();
public:
	guint getOffset();
	bool setOffset(guint v);
	bool gotoFirstFile();
	bool gotoNextFile();
	bool gotoFile(const gchar* fileName);
	bool getCurrentFileName(gchar* buf, guint bufLen);

	bool openCurrentFile();
	inline bool isCurrentFileOpened() {
		return m_IsCFOpened;
	}
	bool closeCurrentFile();
public:
	virtual bool hasData();
	virtual gint read(void* buf, guint len);
	virtual bool skip(guint len);
	virtual gint getBytes();
	virtual bool canRollback();
	virtual bool canGetLength();
	virtual gint getLength();

private:
	void* m_ZipFile;
	bool m_IsCFOpened;
};

#include "GXGObjectUD.h"

#endif /* GZipReader_h */
