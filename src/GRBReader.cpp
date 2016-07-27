//
//  GRBReader.cpp
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#include "GRBReader.h"
//Down include other h file

//Up include other h file
#include "GXGObject.h"

GX_GOBJECT_IMPLEMENT(GRBReader, GReader);

GRBReader::GRBReader()
{
    m_Reader=NULL;
    m_Cursor=0;
    m_RBClosed=0;
}

GRBReader::~GRBReader()
{
    GO::release(m_Reader);
}


bool GRBReader::open(GReader* reader)
{
    if (!reader) {
        return false;
    }
    GO::retain(reader);
    GO::release(m_Reader);
    m_Reader=reader;
    m_Data.freeSelf();
    m_RBClosed=0;
    return true;
}

void GRBReader::close()
{
    GO::release(m_Reader);
    m_Reader=NULL;
    m_Data.freeSelf();
    m_RBClosed=0;
}

bool GRBReader::hasData()
{
    if (m_RBClosed || m_Cursor>=m_Data.getBytes()) {
        return m_Reader->hasData();
    }
	return true;
}
gint GRBReader::read(void* buf, guint len)
{
    if (!m_RBClosed) {
        gint lenRes=0;
        if (len>0 && m_Cursor<m_Data.getBytes()) {
            guint lenTemp=m_Data.getBytes()-m_Cursor;
            if (lenTemp>len) {
                lenTemp=len;
            }
            memcpy(buf, m_Data.getPtr(m_Cursor), lenTemp);
            m_Cursor+=lenTemp;
            lenRes+=(gint)lenTemp;
            len-=lenTemp;
        }
        if (len>0) {
            if (!m_Data.changeBytes(m_Data.getBytes()+len)) {
                return -1;
            }
            gint nTemp=m_Reader->read(m_Data.getPtr(m_Cursor), len);
            if (nTemp<0) {
                return nTemp;
            }
            else if(nTemp>0) {
                memcpy(((guint8*)buf)+lenRes, m_Data.getPtr(m_Cursor), (size_t)nTemp);
                m_Cursor+=nTemp;
                lenRes+=nTemp;
            }
            
            if (m_Cursor<m_Data.getBytes()) {
                if (!m_Data.changeBytes(m_Cursor)) {
                    return -1;
                }
            }
        }
        
        return lenRes;
    }
	return m_Reader->read(buf, len);
}
bool GRBReader::skip(guint len)
{
    if (!m_RBClosed) {
        if (len>0 && m_Cursor<m_Data.getBytes()) {
            guint lenTemp=m_Data.getBytes()-m_Cursor;
            if (lenTemp>len) {
                lenTemp=len;
            }
            m_Cursor+=lenTemp;
            len-=lenTemp;
        }
        if (len>0) {
            if (!m_Data.changeBytes(m_Data.getBytes()+len)) {
                return false;
            }
            if (m_Reader->read(m_Data.getPtr(m_Cursor), len)!=(gint)len) {
                return false;
            }
            m_Cursor+=len;
        }
        return true;
    }
	return m_Reader->skip(len);
}
gint GRBReader::getBytes()
{
	return (gint)m_Cursor;
}

void GRBReader::closeRollback()
{
    if (!m_RBClosed) {
        m_RBClosed=1;
        m_Cursor=m_Data.getBytes();
        m_Data.freeSelf();
    }
}

bool GRBReader::canRollback()
{
	return !m_RBClosed;
}
bool GRBReader::rollback(guint len)
{
    if (m_RBClosed || m_Cursor<len) {
        return false;
    }
    m_Cursor-=len;
	return true;
}

bool GRBReader::canGetLength()
{
	return m_Reader->canGetLength();
}
gint GRBReader::getLength()
{
	return m_Reader->getLength();
}


