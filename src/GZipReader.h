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
#include "GMap.h"
#include "GString.h"

#include "GXGObject.h"

class GZipReader : public GReader {
	friend class GZipBundle;
	GX_GOBJECT(GZipReader);
public:
	class FileInfo : public GObject {
		friend class GZipReader;
		GX_GOBJECT_DECLARE(FileInfo, private, private);
	public:

	private:
		struct {
#if GX_PTR_32BIT
			unsigned long version;              
			unsigned long version_needed;       
			unsigned long flag;                 
			unsigned long compression_method;   
			unsigned long dosDate;              
			unsigned long crc;                  
			unsigned long compressed_size;      
			unsigned long uncompressed_size;    
			unsigned long size_filename;        
			unsigned long size_file_extra;      
			unsigned long size_file_comment;    
			unsigned long disk_num_start;       
			unsigned long internal_fa;          
			unsigned long external_fa;          
#elif GX_PTR_64BIT
			unsigned long version;              
			unsigned long version_needed;       
			unsigned long flag;                 
			unsigned long compression_method;   
			unsigned long dosDate;              
			unsigned long crc;                  
			unsigned long long int compressed_size;   
			unsigned long long int uncompressed_size; 
			unsigned long size_filename;        
			unsigned long size_file_extra;      
			unsigned long size_file_comment;    
			unsigned long disk_num_start;       
			unsigned long internal_fa;          
			unsigned long external_fa;          
#endif
			struct {
				unsigned int tm_sec;            
				unsigned int tm_min;            
				unsigned int tm_hour;           
				unsigned int tm_mday;           
				unsigned int tm_mon;            
				unsigned int tm_year;           
			} tmu_date;
		} m_Data;
	};
private:
	class Node : public GObject {
		friend class GZipReader;
		GX_GOBJECT(Node);
	public:
		inline guint getOffset() {
			return m_Offset;
		}
	private:
		inline void setOffset(guint v) {
			m_Offset = v;
		}
	private:
		guint m_Offset;
	};
	typedef GMap<GString, Node> Map;
public:
	bool open(const gtchar* path, bool createMap = true);
	virtual void close();
public:
    inline Map* getMap() {
        return m_Map;
    }
    inline void setMap(Map* v) {
        GO::retain(v);
        GO::release(m_Map);
        m_Map=v;
    }
	guint getOffset();
	bool setOffset(guint v);
	bool gotoFirstFile();
	bool gotoNextFile();
	bool gotoFile(const gchar* fileName);
	FileInfo* currentFileInfo();
	GString* currentFileName();
    

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
	void*	m_ZipFile;
	bool	m_IsCFOpened;
	Map*	m_Map;
};

#include "GXGObjectUD.h"

#endif /* GZipReader_h */
