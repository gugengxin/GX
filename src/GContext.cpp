//
// Created by Gengxin Gu on 16/5/9.
//

#include "GContext.h"
#include "GLog.h"

//不用在这里初始化
GContext::GContext()
{
}
//不用在这里反初始化
GContext::~GContext()
{
}

//在这里初始化
bool GContext::create(GWindow *win)
{
    if(! GContextBase::create(win)) {
        return false;
    }
    memset(m_Shaders, 0, sizeof(m_Shaders));
    //GX_LOG_W(PrioINFO,"GContext","create");
    return true;
}
//在这里反初始化
void GContext::destroy()
{
    //GX_LOG_W(PrioINFO,"GContext","destroy");
    {
        GTexture::Node* p=GX_CAST_R(GTexture::Node*, m_Textures.last());
        while (p) {
            GTexture::Node* pTemp=GX_CAST_R(GTexture::Node*, p->getPrev());
            if (p->isValid()) {
                readyTexture();
                unloadTextureNodeForContext(p);
                doneTexture();
            }
            m_Textures.remove(p,false);
            p->m_Context=NULL;
            p=pTemp;
        }
    }
    for (gint i = 0; i < SRIDCount; i++) {
        readyShader();
        delete m_Shaders[i];
        m_Shaders[i]=NULL;
        doneShader();
    }
    GContextBase::destroy();
}

#if defined(GX_OS_ANDROID)
void GContext::androidDestroy()
{
    //TODO
    //GX_LOG_W(PrioINFO,"GContext","androidDestroy");iqi
    GContextBase::androidDestroy();
}
void GContext::androidRecreate(GWindow* win)
{
    //GX_LOG_W(PrioINFO,"GContext","androidRecreate");
    GContextBase::androidRecreate(win);
    //TODO
}
#endif

GSRGraphics* GContext::getSRGraphics(GSRGraphics::ID srID)
{
    //GX_LOG_W(PrioINFO,"GContext","getSRGraphics");
	if (!m_Shaders[SRID_Graphics + srID]) {
        readyShader();
        m_Shaders[SRID_Graphics + srID] = new GSRGraphics(srID);
        doneShader();
	}
	return (GSRGraphics*)m_Shaders[SRID_Graphics + srID];
}


GTexture2D* GContext::loadTexture2D(GReader* reader,GDib::FileType suggestFT)
{
    
    
    return NULL;
}

void GContext::addTextureNodeInMT(GTexture::Node* node)
{
    m_Textures.add(node);
}

void GContext::removeTextureNodeInMT(GTexture::Node* node)
{
    m_Textures.remove(node,false);
}


