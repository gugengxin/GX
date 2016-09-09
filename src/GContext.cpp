//
// Created by Gengxin Gu on 16/5/9.
//

#include "GContext.h"
#include "GLog.h"
#include "GThread.h"


#include "GXGObject.h"

GX_GOBJECT_IMPLEMENT(GContext::T2DNodeLoadObj, GObject);

GContext::T2DNodeLoadObj::T2DNodeLoadObj()
{
}

GContext::T2DNodeLoadObj::~T2DNodeLoadObj()
{

}

GX_GOBJECT_IMPLEMENT(GContext::T2DNodeUnloadObj, GObject);

GContext::T2DNodeUnloadObj::T2DNodeUnloadObj()
{
}

GContext::T2DNodeUnloadObj::~T2DNodeUnloadObj()
{

}

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
    //GX_LOG_W(PrioINFO,"GContext","androidDestroy");
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
        m_Shaders[SRID_Graphics + srID] = new GSRGraphics(this,srID);
        doneShader();
	}
	return (GSRGraphics*)m_Shaders[SRID_Graphics + srID];
}

GSRTexture2D* GContext::getSRTexture2D(bool alphaOnly,bool colorMul,GSRTexture2D::MaskMode mm)
{
    gint idx=(alphaOnly*2+colorMul)*GSRTexture2D::MMCount+mm;
    if (!m_Shaders[SRID_Texture2D+idx]) {
        readyShader();
        
        doneShader();
    }
    return (GSRTexture2D*)m_Shaders[SRID_Texture2D + idx];
}


GTexture2D* GContext::loadTexture2D(GReader* reader,GDib::FileType suggestFT,GTexture2D::Parameter* param)
{
    GDib* dib=GDib::load(reader, suggestFT);
    if (dib) {
        GTexture::Node* node=new GTexture::Node();
        if(loadTexture2DNode(node, dib, param)) {
            GTexture2D* tex2d=GTexture2D::alloc();
            tex2d->config(node, dib, param);
            GO::autorelease(tex2d);
            return tex2d;
        }
        else {
            delete node;
        }
    }
    return NULL;
}

void GContext::addTextureNodeInMT(GTexture::Node* node)
{
	m_Textures.add(node);
}

void GContext::removeTextureNodeInMT(GTexture::Node* node)
{
	m_Textures.remove(node, false);
}

bool GContext::loadTexture2DNode(GTexture::Node* node, GDib* dib, GTexture2D::Parameter* param)
{
	dib = loadTexture2DNodeReadyDib(dib);
	if (!dib) {
		return false;
	}
	T2DNodeLoadObj* obj = T2DNodeLoadObj::alloc();
	obj->context = this;
	obj->dib = dib;
	obj->param = param;
	obj->nodeOut = node;
	if (GThread::current()->isMain()) {
		loadTexture2DNodeInMT(obj);
	}
	else {
		GThread::current()->getRunLoop()->perform(loadTexture2DNodeInMT, obj, 0, true);
	}
	GO::release(obj);

	return node->isValid();
}

void GContext::unloadTextureNode(GTexture::Node* node)
{
	T2DNodeUnloadObj* obj = T2DNodeUnloadObj::alloc();
	obj->context = this;
	obj->nodeOut = node;

	if (GThread::current()->isMain()) {
		unloadTextureNodeInMT(obj);
	}
	else {
		GThread::current()->getRunLoop()->perform(unloadTextureNodeInMT, obj, 0, true);
	}

	GO::release(obj);
}

