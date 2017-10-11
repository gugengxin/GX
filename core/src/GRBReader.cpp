//
//  GRBReader.cpp
//  GX
//
//  Created by GuGengxin.
// Copyright by gxengine.com
//

#include "GRBReader.h"
//Down include other h file
#include "GXMemory.h"
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
    gint lenRes=0;
    if (len>0 && m_Cursor<m_Data.getBytes()) {
        guint lenTemp=m_Data.getBytes()-m_Cursor;
        if (lenTemp>len) {
            lenTemp=len;
        }
        GX::gmemcpy(((guint8*)buf)+lenRes, m_Data.getPtr(m_Cursor), lenTemp);
        m_Cursor+=lenTemp;
        lenRes+=(gint)lenTemp;
        len-=lenTemp;
    }
    
    if (len>0) {
        gint nTemp=m_Reader->read(((guint8*)buf)+lenRes, len);
        if (nTemp<0) {
            return nTemp;
        }
        else if(nTemp>0) {
            if (!m_RBClosed) {
                if (!m_Data.changeBytes(m_Cursor+nTemp)) {
                    return -1;
                }
                GX::gmemcpy(m_Data.getPtr(m_Cursor), ((guint8*)buf)+lenRes, nTemp);
            }
            
            lenRes+=nTemp;
        }
    }
    
    return lenRes;
}
bool GRBReader::skip(guint len)
{
    if (len>0 && m_Cursor<m_Data.getBytes()) {
        guint lenTemp=m_Data.getBytes()-m_Cursor;
        if (lenTemp>len) {
            lenTemp=len;
        }
        m_Cursor+=lenTemp;
        len-=lenTemp;
    }
    
    if (len>0) {
        if (!m_RBClosed) {
            if (!m_Data.changeBytes(m_Cursor+len)) {
                return false;
            }
            if (m_Reader->read(m_Data.getPtr(m_Cursor), len)!=(gint)len) {
                return false;
            }
            m_Cursor+=len;
        }
        else {
            return m_Reader->skip(len);
        }
    }
    
    return true;
}
gint GRBReader::getBytes()
{
	return m_Reader->getBytes();
}

void GRBReader::closeRollback()
{
    m_RBClosed=1;
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


